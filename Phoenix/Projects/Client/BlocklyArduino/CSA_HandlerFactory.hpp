// CSA_HandlerFactory.hpp

#ifndef CSA_HANDLERFACTORY_HPP
#define CSA_HANDLERFACTORY_HPP

#include "PX2HTTPRequestHandlerFactory.hpp"
#include "PX2HTTPRequestHandler.hpp"
#include "PX2HTTPServerResponse.hpp"
#include "PX2HTTPServerRequest.hpp"

namespace PX2
{

	class HandlerFactory : public HTTPRequestHandlerFactory
	{
	public:
		HandlerFactory();

		HTTPRequestHandler * CreateRequestHandler(const HTTPServerRequest &request);
	};

	class CSA_RequestHandler : public HTTPRequestHandler
	{
	public:
		CSA_RequestHandler();
		virtual ~CSA_RequestHandler();

		virtual void HandleRequest(HTTPServerRequest& request,
			HTTPServerResponse& response);
	};

}

#endif