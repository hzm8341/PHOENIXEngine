// PX2EU_PreView.hpp

#ifndef EU_PREVIEWFRAME_HPP
#define EU_PREVIEWFRAME_HPP

#include "PX2EditorPre.hpp"
#include "PX2EU_CanvasPreView.hpp"

namespace PX2
{

	class PX2_EDITOR_ITEM EU_ContentFrame : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_STREAM(EU_ContentFrame);
		PX2_NEW(EU_ContentFrame);

	public:
		EU_ContentFrame();
		virtual ~EU_ContentFrame();

		virtual void SetActive(bool act);

		enum ContentType
		{
			CT_TEXT,
			CT_STRING,
			CT_PREVIEW,
			CT_MAX_TYPE
		};
		void SetCont(ContentType type, const std::string &filename);
		void SetContString(const std::string &str);
		void SetContAcceptKeyboardInput(bool accept);

		virtual void OnEvent(Event *ent);

	protected:
		ContentType mContentType;
		std::string mContentFilename;
		SizeNodePtr mTheNode;
	};

	PX2_REGISTER_STREAM(EU_ContentFrame);
	typedef Pointer0<EU_ContentFrame> EU_PreViewFramePtr;

}

#endif