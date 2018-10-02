// main.cpp

#include "PX2Net.hpp"
#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Application.hpp"
#include "PX2Log.hpp"
#include "PX2ServerInfoManager.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Dir.hpp"
#include "PX2HostEntry.hpp"
#include "PX2DNS.hpp"
#include "PX2MD5.hpp"
using namespace PX2;
using namespace std;

Mutex sServerMutex;
bool isShutdownServer = false;

static std::string sCmdString;
static std::vector<std::string> sCmdParams;
static bool sIsHasInput = false;
static bool sIsDoQuit = false;
//----------------------------------------------------------------------------
void InputThreadProc(void* data)
{
	PX2_UNUSED(data);

	while (!sIsDoQuit)
	{
		if (!sIsHasInput)
		{
			std::cout << "please input your commond:\n";
			char buffer[256];
			std::cin.getline(buffer, 256);
			std::string cmdbuf(buffer);
			sCmdString = cmdbuf;
			sCmdParams.resize(0);

			ScopedCS cs(&sServerMutex);
			sIsHasInput = true;
		}
	}
}
//----------------------------------------------------------------------------
std::string _GetMD5(const std::string &strBuffer)
{
	char buffer[17], out[33];
	memset(buffer, 0, sizeof(buffer));
	memset(out, 0, sizeof(out));

	Md5HashBuffer(buffer, strBuffer.c_str(), (int)strBuffer.length());
	Md5HexString(buffer, out);

	return std::string(out);
}
//----------------------------------------------------------------------------
void _RefreshDir(XMLNode node, const std::string &pathName)
{
	std::string eachFilename;
	Dir d;
	if (d.Open(pathName))
	{
		if (!d.HasFiles() && !d.HasSubDirs())
			return;

		int flags = Dir::DIR_DIRS | Dir::DIR_FILES;

		if (d.GetFirst(&eachFilename, "", flags))
		{
			do
			{
				if ((eachFilename != ".") && (eachFilename != ".."))
				{
					_RefreshDir(node, pathName + "/" + eachFilename);
				}

			} while (d.GetNext(&eachFilename));
		}
	}
	else
	{
		if (pathName.find("filelist") == std::string::npos)
		{
			XMLNode childNode = node.NewChild("file");
			childNode.SetAttributeString("filename", pathName);

			char *buffer = 0;
			int bufferSize = 0;
			if (FileIO::Load(pathName, true, bufferSize, buffer))
			{
				std::string strBuf = _GetMD5(std::string(buffer, bufferSize));
				delete1(buffer);
				bufferSize = 0;

				childNode.SetAttributeString("md5", strBuf);
			}
			else
			{
				childNode.SetAttributeString("md5", "");
			}
		}
	}
}
//----------------------------------------------------------------------------
void _GenFileList(const std::string &projName)
{
	std::string dataPath = "Data/" + projName;

	XMLData data;
	data.Create();

	XMLNode rootNode = data.NewChild("filelist");
	rootNode.SetAttributeString("version", "1.0.0");
	_RefreshDir(rootNode, dataPath);

	std::string savePath = dataPath + "/filelist.xml";
	data.SaveFile(savePath);
}
//----------------------------------------------------------------------------
int _ProcessInputString(const std::string &strBuf)
{
	StringTokenizer stk(strBuf, " ");
	int numTok = stk.Count();

	int ret = 0;
	std::string cmdStr;
	std::string paramStr0;
	std::string paramStr1;
	if (numTok >= 1)
		cmdStr = stk[0];
	if (numTok >= 2)
		paramStr0 = stk[1];
	if (numTok >= 3)
		paramStr1 = stk[2];

	if ("quit" == cmdStr)
	{
		ret = 1;
	}
	else if (CMD_PushProject == cmdStr)
	{
		std::string projName = paramStr0;
		if (!projName.empty())
		{
			_GenFileList(projName);

			EngineServer *es = PX2_APP.GetEngineServer();
			es->BroadCastPushProject(projName);
		}
	}
	else if ("genprojectfilelist" == cmdStr)
	{
		std::string projName = paramStr0;
		if (!projName.empty())
		{
			_GenFileList(projName);
		}
	}
	else if ("broadcast" == cmdStr)
	{
		EngineServer *es = PX2_APP.GetEngineServer();

		std::string strSend = paramStr0;
		if (numTok == 3)
			strSend = paramStr0 + " " + paramStr1;
		es->BroadCastString(strSend);
	}

	return ret;
}
//----------------------------------------------------------------------------
int main(int numArguments, char** arguments)
{
	Application *app = new Application();
	app->SetBoostMode(Application::BM_SERVER);
	isShutdownServer = false;

	if (app->Initlize())
	{
		Logger *logger = Logger::GetSingletonPtr();
		logger->CloseLogger();

#if defined(_WIN32) || defined(WIN32) || defined(__LINUX__)
		logger->AddFileHandler("log_serverplayer.txt", LT_INFO | LT_ERROR | LT_USER);
#endif
		logger->AddOutputWindowHandler(LT_INFO | LT_ERROR | LT_USER);
		logger->AddConsoleHandler(LT_INFO | LT_ERROR | LT_USER);
		logger->SetLogFileInfo(false);
		logger->StartLogger();

		ThreadPtr inputThread = new0 Thread();
		inputThread->Start(InputThreadProc);

		EngineServer *es = PX2_APP.GetEngineServer();
		es->Start();
		std::string ipStr;
		int port = es->GetPort();
#if defined (__ANDROID__)
		ipStr = HostEntry::GetAndroidIP();
#else
		HostEntry hostEntry = DNS::GetThisHost();
		HostEntry::AddressList addressList = hostEntry.GetAddresses();
		for (int i = 0; i < (int)addressList.size(); i++)
		{
			IPAddress ipAddress = addressList[i];
			ipStr = ipAddress.ToString();
			PX2_LOG_INFO("EngineServer started ip:%s port:%d", ipStr.c_str(), port);
		}
#endif

		while (!isShutdownServer)
		{
			app->Update();

			if (sIsHasInput)
			{
				int ret = _ProcessInputString(sCmdString);
				if (0 == ret)
				{
					ScopedCS cs(&sServerMutex);
					sIsHasInput = false;
				}
				if (1 == ret)
				{
					sIsDoQuit = true;
					isShutdownServer = true;

					PX2_LOG_INFO("quit...");
				}
			}

			System::SleepSeconds(0.03f);
		}

		System::SleepSeconds(1.0f);

		inputThread = 0;

		PX2_LOG_INFO("EngineServer shutdown");

		app->Terminate();
	}

	delete(app);

	return 0;
}
//----------------------------------------------------------------------------