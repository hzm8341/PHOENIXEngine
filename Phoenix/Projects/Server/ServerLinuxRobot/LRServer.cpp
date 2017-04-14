// LRServer.cpp

#include "LRServer.hpp"
#include "PX2Log.hpp"
#include "LRDefine.hpp"
#include "PX2GPIO.hpp"
#include "PX2StringHelp.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2GPIO.hpp"
#include "PX2SoundSystem.hpp"
using namespace PX2;

const int PinLeft0 = 13;
const int PinLeft1 = 19;
const int PinLeftSpeed = 26;

const int PinRight0 = 16;
const int PinRight1 = 20;
const int PinRightSpeed = 21;
//----------------------------------------------------------------------------
LRServer::LRServer(Server::ServerType serverType, int port,
	int numMaxConnects, int numMaxMsgHandlers) :
	Server(serverType, port, numMaxConnects, numMaxMsgHandlers),
	mNextUID(1)
{
	RegisterHandler(StringMsgID, (Server::MsgHandleFunc)&LRServer::OnString);

	//mGPIOLeft0.Set(PinLeft0, GPIO::DT_OUT);
	//mGPIOLeft1.Set(PinLeft1, GPIO::DT_OUT);
	//mGPIOLeftSpeed.Set(PinLeftSpeed, GPIO::DT_OUT);

	//mGPIORight0.Set(PinRight0, GPIO::DT_OUT);
	//mGPIORight1.Set(PinRight1, GPIO::DT_OUT);
	//mGPIORightSpeed.Set(PinRightSpeed, GPIO::DT_OUT);

	std::string strCOM = "COM7";
#if defined (__LINUX__)
	strCOM = "/dev/ttyACM0";
#endif

	if (!mSerial.Init(strCOM, 9600))
	{
		PX2_LOG_INFO("Serial open failed!");
	}
	else
	{
		PX2_LOG_INFO("Serial open suc!");
	}
}
//----------------------------------------------------------------------------
LRServer::~LRServer()
{
	mSerial.Close();
}
//----------------------------------------------------------------------------
unsigned int LRServer::GetNextUID()
{
	return mNextUID++;
}
//----------------------------------------------------------------------------
int LRServer::OnConnect(unsigned int clientid)
{
	PX2_LOG_INFO("client: %d connected", clientid);

	ClientContext *context = GetClientContext(clientid);
	if (context)
	{
		SocketAddress addr = context->TheSocket.GetImpl()->GetPeerAddress();
		std::string ip = addr.ToString();
		PX2_LOG_INFO("Connected %s", ip.c_str());
	}

	return 0;
}
//----------------------------------------------------------------------------
int LRServer::OnDisconnect(unsigned int clientid)
{
	PX2_LOG_INFO("client: %d disconnected", clientid);

	return 0;
}
//----------------------------------------------------------------------------
int LRServer::OnString(unsigned int clientid, const void *pbuffer, int buflen)
{
	std::string strBuf((const char*)pbuffer, buflen);

	PX2_LOG_INFO("recved %s", strBuf.c_str());

	OnProcessString(clientid, strBuf);

	return 0;
}
//----------------------------------------------------------------------------
void LRServer::SendString(unsigned int clientid, const std::string &str)
{
	if (!str.empty() && clientid > 0)
	{
		SendMsgToClientBuffer(clientid, StringMsgID, str.c_str(),
			str.length());
	}
}
//----------------------------------------------------------------------------
int LRServer::OnProcessString(int clientid, const std::string &buf)
{
	int ret = 0;
	std::string cmd;
	StringTokenizer tokenizer(buf, " ");
	int count = tokenizer.Count();
	if (count > 0)
	{
		cmd = tokenizer[0];
		if ("quit" == cmd && count == 1)
		{
			ret = 1;
		}
		else if ("robot" == cmd && count == 1)
		{
			_RefreshRobot(clientid);
		}
		else if ("playfarcam" == cmd && count == 2)
		{
			std::string strRet = tokenizer[1];
			if ("true" == strRet)
			{
				ClientContext *context = GetClientContext(clientid);
				if (context)
				{
					SocketAddress addr = context->TheSocket.GetImpl()->GetPeerAddress();
					std::string ip = addr.GetHost().ToString();
					
					std::string strCMD;
					strCMD += "export LD_LIBRARY_PATH=/usr/local/lib\n";
					strCMD += "mjpg_streamer - i \"input_uvc.so\" - o \"output_http.so -w ./www\"";
					PX2_LOG_INFO("playfarcam cktool:%s", strCMD.c_str());

					/*
					std::string strCMD = "cktool -s 15 -a " + ip + " -p 8888 -f 80";
					PX2_LOG_INFO("playfarcam cktool:%s", strCKTool.c_str());
					*/

#if defined (__LINUX__)
					system("sh ");
					//popen(strCMD.c_str(), "r");
#endif
					SendString(clientid, "playfarcam true");
				}
			}
			else if ("false" == strRet)
			{
				SendString(clientid, "playfarcam false");
			}
		}
		else if ("playmusic" == cmd && count == 2)
		{
			std::string strPlayMusic = tokenizer[1];
			_PlayMusic("true" == strPlayMusic);
		}
		else if ("move" == cmd && count == 3)
		{
			std::string strLeftRight = tokenizer[1];
			std::string strGoBack = tokenizer[2];

			std::string sendStr = "move " + strLeftRight + " " + strGoBack + "\n";

			PX2_LOG_INFO("Send str %s", sendStr.c_str());
			mSerial.Send(sendStr);
		}
		else if ("speed" == cmd)
		{
			std::string strLeftRight = tokenizer[1];
			std::string strSpeed = tokenizer[2];

			std::string sendStr = "speed " + strLeftRight + " " + strSpeed + "\n";
			PX2_LOG_INFO("Send str %s", sendStr.c_str());
			mSerial.Send(sendStr);
		}
	}

	return ret;
}
//----------------------------------------------------------------------------
void LRServer::_PlayMusic(bool play)
{
	if (play)
	{
		PX2_SS.PlayMusic(0, "DataServer/LinuxRobot/tsyj.mp3", true, 0.0f);
	}
	else
	{
		PX2_SS.PlayMusic(0, 0, true, 0.0f);
	}
}
//----------------------------------------------------------------------------
void LRServer::_RefreshRobot(int clientID)
{

	SendString(clientID, "robot ok");
}
//----------------------------------------------------------------------------
void LRServer::_SetMove(const std::string &leftRight, const std::string &goBack)
{
	if ("left" == leftRight)
	{
		if ("go" == goBack)
		{
			//mGPIOLeft0.SetHigh();
			//mGPIOLeft1.SetLow();

			//mGPIOLeftSpeed.SetValue(1);

			mSerial.Send("w");
		}
		else if ("back" == goBack)
		{
			//mGPIOLeft0.SetLow();
			//mGPIOLeft1.SetHigh();

			//mGPIOLeftSpeed.SetValue(1);

			mSerial.Send("s");
		}
		else if ("stop" == goBack)
		{
			//mGPIOLeft0.SetLow();
			//mGPIOLeft1.SetLow();

			//mGPIOLeftSpeed.SetValue(0);

			mSerial.Send("x");
		}
	}
	else if ("right" == leftRight)
	{
		if ("go" == goBack)
		{
			//mGPIORight0.SetHigh();
			//mGPIORight1.SetLow();

			//mGPIORightSpeed.SetValue(1);

			mSerial.Send("w");
		}
		else if ("back" == goBack)
		{
			//mGPIORight0.SetLow();
			//mGPIORight1.SetHigh();

			//mGPIORightSpeed.SetValue(1);

			mSerial.Send("s");
		}
		else if ("stop" == goBack)
		{
			//mGPIORight0.SetLow();
			//mGPIORight1.SetLow();

			//mGPIORightSpeed.SetValue(0);

			mSerial.Send("x");
		}
	}
}
//----------------------------------------------------------------------------
void LRServer::_LogGPIOVal(int pin)
{
	GPIO::Export(pin);
	int val = 0;
	GPIO::GetValue(pin, val);
	PX2_LOG_INFO("GPIO:%d Val:%d", pin, val);
	GPIO::Unexport(pin);
}
//----------------------------------------------------------------------------
void LRServer::_SetSpeed(const std::string &leftRight, const std::string &speedVal)
{
	int val = StringHelp::StringToInt(speedVal);

	if ("left" == leftRight)
	{
		mGPIOLeftSpeed.SetValue(val);
	}
	else if ("right" == leftRight)
	{
		mGPIORightSpeed.SetValue(val);
	}
}
//----------------------------------------------------------------------------