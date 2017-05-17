// PX2EU_WebView.hpp

#ifndef PX2EU_WEBVIEW_HPP
#define PX2EU_WEBVIEW_HPP

#include "PX2EditorPre.hpp"
#include "PX2UIWebFrame.hpp"

namespace PX2
{

	class PX2_EDITOR_ITEM EU_WebFrame : public UIWebFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_STREAM(EU_WebFrame);
		PX2_NEW(EU_WebFrame);

	public:
		EU_WebFrame();
		virtual ~EU_WebFrame();

		void SetToOpenString(const std::string &toOpenStr);
		void Save();

	protected:
		std::string mToOpenString;
	};

	PX2_REGISTER_STREAM(EU_WebFrame);
	typedef Pointer0<EU_WebFrame> EU_WebFramePtr;

}

#endif