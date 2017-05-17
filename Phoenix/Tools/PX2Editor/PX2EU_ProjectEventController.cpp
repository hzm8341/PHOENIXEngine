//PX2EU_ProjectEventController.cpp

#include "PX2EU_ProjectEventController.hpp"
#include "PX2EU_CanvasStage.hpp"
#include "PX2EU_CanvasStageUI.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2Scene.hpp"
#include "PX2Canvas.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UI.hpp"
#include "PX2Project.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
EU_ProjectEventController::EU_ProjectEventController()
{
	ComeInEventWorld();
}
//----------------------------------------------------------------------------
EU_ProjectEventController::~EU_ProjectEventController()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void EU_ProjectEventController::OnEvent(Event *event)
{
	Canvas *canvas = DynamicCast<Canvas>(GetControlledable());
	if (canvas)
	{
		const std::string &name = canvas->GetName();

		if ("SceneCanvas" == name)
		{
			if (ProjectES::IsEqual(event, ProjectES::NewScene))
			{
				Scene *scene = event->GetData<Scene*>();

				canvas->RemoveAllCameras();
				std::vector<CameraPtr> &cams = scene->GetCameras();
				for (int i = 0; i < (int)cams.size(); i++)
				{
					canvas->AddCamera(cams[i]);
				}

				canvas->SetRenderNode(scene);
				canvas->SetRenderNodeUpdate(false);

				EU_CanvasStage::GetSingleton().Enable(true);
				EU_CanvasStage::GetSingleton().ShowContent(true);
			}
			else if (ProjectES::IsEqual(event, ProjectES::CloseScene))
			{
				canvas->SetRenderNode(0);
				canvas->RemoveAllCameras();

				EU_CanvasStage::GetSingleton().Enable(false);
				EU_CanvasStage::GetSingleton().ShowContent(false);
			}

			if (ProjectES_Internal::IsEqual(event,
				ProjectES_Internal::SceneUICamerasChanged))
			{
				Object *obj = event->GetData<Object*>();
				Scene *scene = DynamicCast<Scene>(obj);
				if (scene)
				{
					canvas->RemoveAllCameras();
					std::vector<CameraPtr> &cams = scene->GetCameras();
					for (int i = 0; i < (int)cams.size(); i++)
					{
						canvas->AddCamera(cams[i]);
					}
				}
			}
		}
		else if ("UICanvas" == name)
		{
			if (ProjectES::IsEqual(event, ProjectES::NewUI))
			{
				UI *ui = event->GetData<UI*>();
				ui->SetSize(PX2_PROJ.GetSize());

				canvas->RemoveAllCameras();
				canvas->SetRenderNode(ui);
				canvas->SetRenderNodeUpdate(false);

				EU_CanvasStageUI::GetSingleton().Enable(true);
			}
			else if (ProjectES::IsEqual(event, ProjectES::CloseUI))
			{
				canvas->SetRenderNode(0);
				canvas->RemoveAllCameras();

				EU_CanvasStageUI::GetSingleton().Enable(false);
			}

			if (ProjectES_Internal::IsEqual(event,
				ProjectES_Internal::SceneUICamerasChanged))
			{
				Object *obj = event->GetData<Object*>();
				UI *ui = DynamicCast<UI>(obj);
				if (ui)
				{
					canvas->RemoveAllCameras();
				}
			}
		}
	}
}
//----------------------------------------------------------------------------