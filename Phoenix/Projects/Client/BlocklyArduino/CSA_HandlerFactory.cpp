// CSA_HandlerFactory.cpp

#include "CSA_HandlerFactory.hpp"
#include "PX2DateTime.hpp"
#include "PX2Base64.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2FileIO.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
HandlerFactory::HandlerFactory()
{
}
//----------------------------------------------------------------------------
HTTPRequestHandler * HandlerFactory::CreateRequestHandler(
	const HTTPServerRequest &request)
{
	return new0 CSA_RequestHandler();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
CSA_RequestHandler::CSA_RequestHandler()
{
}
//----------------------------------------------------------------------------
CSA_RequestHandler::~CSA_RequestHandler()
{
}
//----------------------------------------------------------------------------
void CSA_RequestHandler::HandleRequest(HTTPServerRequest& request,
	HTTPServerResponse& response)
{
	std::string method = request.GetMethod();
	std::string url = request.GetURI();
	StringTokenizer stkQuestion(url, "?");
	if (stkQuestion.Count() > 1)
	{
		std::string valStr = Base64::Decode(stkQuestion[1]);

		StringTokenizer stkEqual(valStr, "$");
		if (stkEqual.Count() > 1)
		{
			std::string valStr0 = stkEqual[0];
			std::string contentStr = stkEqual[1];

			StringTokenizer stk_(valStr0, "_");
			if (stk_.Count() > 1)
			{
				std::string valStrCMD = stk_[0];
				std::string valStrFilename = stk_[1];

				if ("loadXML" == valStrCMD)
				{

				}
				else if ("saveXML" == valStrCMD)
				{
					FileIO::Save(valStrFilename, false,
						contentStr.length(), contentStr.c_str());
				}
				else if ("saveArduino" == valStrCMD)
				{
					std::string outPath;
					std::string fileName;
					std::string outBaseName;
					std::string outExt;
					StringHelp::SplitFullFilename(valStrFilename, outPath, 
						outBaseName, outExt);
					std::string adjugeStr = valStrFilename.substr(outPath.length() - outBaseName.length() - 1, outBaseName.length());
					if (adjugeStr == outBaseName)
					{
						// not need create folder
						std::string dstFilename = valStrFilename;
						FileIO::Save(dstFilename, false,
							contentStr.length(), contentStr.c_str());
					}
					else
					{
						PX2_RM.CreateFloder(outPath, outBaseName + "/");
						std::string dstFilename = outPath + outBaseName + "/" +
							outBaseName + "." + outExt;
						FileIO::Save(dstFilename, false,
							contentStr.length(), contentStr.c_str());
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------