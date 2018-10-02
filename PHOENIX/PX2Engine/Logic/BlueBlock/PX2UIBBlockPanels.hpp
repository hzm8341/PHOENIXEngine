// PX2UIBBlockPanels.hpp

#ifndef PX2UIPADBLOCKSPANELS_HPP
#define PX2UIPADBLOCKSPANELS_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockPanels : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIBBlockPanels);
		PX2_DECLARE_STREAM(UIBBlockPanels);

	public:
		UIBBlockPanels();
		virtual ~UIBBlockPanels();

		void ShowPanel(const std::string &panelName);

		virtual void OnEvent(Event *ent);

		void OnSizeNodeNotPicked(const CanvasInputData &inputData);

	protected:
		std::map<std::string, UIFramePtr> mBlocksPanel;
	};

	PX2_REGISTER_STREAM(UIBBlockPanels);
	typedef Pointer0<UIBBlockPanels> UIPadBlocksPanelPtr;

}

#endif