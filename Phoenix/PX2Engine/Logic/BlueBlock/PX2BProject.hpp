// PX2BProject.hpp

#ifndef PX2BPROJECT_HPP
#define PX2BPROJECT_HPP

#include "PX2BBlockPre.hpp"
#include "PX2Object.hpp"
#include "PX2UIFrame.hpp"
#include "PX2Scene.hpp"
#include "PX2CameraNode.hpp"
#include "PX2CameraPlayController.hpp"
#include "PX2Canvas.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BProject : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BProject);
		PX2_DECLARE_STREAM(BProject);

	public:
		BProject();
		virtual ~BProject();

		std::string DateStr;
		std::string Desc;

		UIFrame *GetContentFrame();
		Scene *GetScene();
		CameraNode *GetCameraNode();
		CameraPlayController *GetCameraPlayController();
		
		UIFrame *GetSmallFrame();
		Canvas *GetSmallCanvas();

		enum TemplateType
		{
			TT_GAMEPAD,
			TT_MAX_TYPE
		};
		void CreateTemplate(TemplateType tt);

	protected:
		UIFramePtr mContentFrame;
		ScenePtr mScene;
		CameraNodePtr mCameraNode;
		CameraPlayerControllerPtr mCameraPlayCtrl;

		UIFramePtr mSmallFrame;
		CanvasPtr mSmallCanvas;
	};
	PX2_REGISTER_STREAM(BProject);
	typedef Pointer0<BProject> BProjectPtr;

}

#endif