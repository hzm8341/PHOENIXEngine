// PX2Creater.hpp

#ifndef PX2CREATER_HPP
#define PX2CREATER_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "PX2Object.hpp"
#include "PX2APoint.hpp"
#include "PX2CameraNode.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2UIFText.hpp"
#include "PX2UIButton.hpp"
#include "PX2UICheckButton.hpp"
#include "PX2UIComboBox.hpp"
#include "PX2UIEditBox.hpp"
#include "PX2UIProgressBar.hpp"
#include "PX2UIRound.hpp"
#include "PX2UIVlc.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2Billboard.hpp"
#include "PX2BeamEmitter.hpp"
#include "PX2RibbonEmitter.hpp"
#include "PX2Soundable.hpp"
#include "PX2ScriptController.hpp"
#include "PX2InterpCurveAlphaCtrl.hpp"
#include "PX2InterpCurveColorCtrl.hpp"
#include "PX2InterpCurveUniformScaleCtrl.hpp"
#include "PX2InterpCurveScaleCtrl.hpp"
#include "PX2InterpCurveRotateCtrl.hpp"
#include "PX2InterpCurveTranslateCtrl.hpp"
#include "PX2TriggerController.hpp"
#include "PX2CameraPlayController.hpp"
using namespace PX2;

namespace PX2
{

	class Scene;

	class PX2_ENGINE_ITEM Creater : public Singleton<Creater>
	{
	public:
		Creater();
		virtual ~Creater();

		// general
		Movable *CreateMovable_Box();
		Movable *CreateMovable_Sphere();
		Movable *CreateMovable_Rectangle();
		Node *CreateBlockFrame(int num, float halfExtend, const std::string &image);

		Node *CreateNode();
		CameraNode *CreateNode_Camera(bool createCamera = true);
		Node *CreateNode_Model(const std::string &filename);
		Node *CreateNode_Model(Movable *movable);
		Movable *CreateMovable_FromRes(const std::string &filename);
		ScriptController *CreateScriptController_FromRes(const std::string &filename);
		ScriptController *CreateScriptController_FromBuffer(const std::string &bufStr, 
			const std::string &className);

		// sky
		Movable *CreateSkyBox(const std::string &skyDirPath);

		// Terrain
		Movable *CreateTerrain();

		// effect
		ParticleEmitter *CreateParticleEmitter();
		Billboard *CreateBillboard();
		BeamEmitter *CreateBeamEmitter();
		RibbonEmitter *CreateRibbonEmitter();
		Soundable *CreateSoundable();
		EffectModule *CreateEffectModule(const std::string &typeName);

		// ui
		UIFrame *CreateUIFrame();
		UIFPicBox *CreateUIFPicBox();
		UIFText *CreateUIFText();
		UIButton *CreateUIButton();
		UICheckButton *CreateUICheckButton();
		UIComboBox *CreateUIComboBox();
		UIEditBox *CreateUIEditBox();
		UIProgressBar *CreateUIProgressBar();
		UIRound *CreateUIRound();
		UIVlc *CreateUIVlc();

		// controller
		InterpCurveAlphaController *CreateICC_Alpha();
		InterpCurveColorController *CreateICC_Color();
		InterpCurveUniformScaleController *CreateICC_UniformScale();
		InterpCurveScaleController *CreateICC_Scale();
		InterpCurveRotateController *CreateICC_Rotate();
		InterpCurveTranslateController *CreateICC_Translate();
		TriggerController *CreateTriggerController();
		CameraPlayController *CreateCameraPlayController();

	public:
		void AddObject(Object *parent, Object *obj,
			bool command = true);
		bool RemoveObject(Object *obj, bool command = true);
	};

#define PX2_CREATER Creater::GetSingleton()

}

#endif