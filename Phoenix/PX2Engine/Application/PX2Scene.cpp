// PX2Scene.cpp

#include "PX2Scene.hpp"
#include "PX2Creater.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2GraphicsEventData.hpp"
#include "PX2Float2.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2GraphicsRoot.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, Scene);
PX2_IMPLEMENT_STREAM(Scene);
PX2_IMPLEMENT_FACTORY(Scene);
PX2_IMPLEMENT_DEFAULT_NAMES(Node, Scene);

//----------------------------------------------------------------------------
Scene::Scene() 
{
	ComeInEventWorld();

	SetName("Scene");

	mEnvirParam = new0 EnvirParamController();
	AttachController(mEnvirParam);
	mEnvirParam->ResetPlay();

	mAmbientRegionController = new0 AmbientRegionController();
	AttachController(mAmbientRegionController);
	mAmbientRegionController->ResetPlay();

	CameraNode *camNode = PX2_CREATER.CreateNode_Camera();
	AttachChild(camNode);
	camNode->SetName("MainCameraNode");
	camNode->GetCamera()->SetClearColor(Float4::WHITE);
	camNode->LocalTransform.SetTranslate(-10.0f, -10.0f, 10.0f);
	camNode->LookAt(APoint(0.0f, 0.0f, 0.0f));
	SetMainCameraNode(camNode);

	mIsNeedReCalCameras = true;
}
//----------------------------------------------------------------------------
Scene::~Scene()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void Scene::SetTerrain(Terrain *terrain)
{
	mTerrain = terrain;
}
//----------------------------------------------------------------------------
Terrain *Scene::GetTerrain()
{
	return mTerrain;
}
//----------------------------------------------------------------------------
void Scene::SetMainCameraNode(CameraNode *camNode)
{
	mMainCameraNode = camNode;
}
//----------------------------------------------------------------------------
CameraNode *Scene::GetMainCameraNode()
{
	return mMainCameraNode;
}
//----------------------------------------------------------------------------
bool Scene::AddCamera(Camera *camera)
{
	if (!camera)
		return false;

	for (int i = 0; i < (int)mCameras.size(); i++)
	{
		if (mCameras[i] == camera)
			return false;
	}

	mCameras.push_back(camera);

	Event *event = PX2_CREATEEVENTEX(ProjectES_Internal,
		SceneUICamerasChanged);
	event->SetData<Object*>(this);
	PX2_EW.BroadcastingLocalEvent(event);

	return true;
}
//----------------------------------------------------------------------------
void Scene::ClearCameras()
{
	mCameras.clear();

	Event *event = PX2_CREATEEVENTEX(ProjectES_Internal, 
		SceneUICamerasChanged);
	event->SetData<Object*>(this);
	PX2_EW.BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool Scene::RemoveCamera(Camera *camera)
{
	if (!camera)
		return false;

	auto it = mCameras.begin();
	for (; it != mCameras.end(); it++)
	{
		if (camera == *it)
		{
			it = mCameras.erase(it);

			Event *event = PX2_CREATEEVENTEX(ProjectES_Internal, 
				SceneUICamerasChanged);
			event->SetData<Object*>(this);
			PX2_EW.BroadcastingLocalEvent(event);

			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void Scene::_CollectCameras(Scene *scene, Node *node)
{
	Scene *sc = DynamicCast<Scene>(node);
	CameraNode *camNode = DynamicCast<CameraNode>(node);
	if (sc)
	{
		EnvirParamController *epc = sc->GetEnvirParamController();
		Projector *projector = epc->GetLight_Dir_Projector();
		if (projector)
		{
			scene->AddCamera(projector);
		}
	}
	else if (camNode)
	{
		Camera *camera = camNode->GetCamera();
		if (camera)
		{
			scene->AddCamera(camera);
		}
	}

	for (int i = 0; i < node->GetNumChildren(); i++)
	{
		Movable *mov = node->GetChild(i);
		Node *childNode = DynamicCast<Node>(mov);
		if (childNode)
		{
			_CollectCameras(scene, childNode);
		}
	}
}
//----------------------------------------------------------------------------
void Scene::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Node::UpdateWorldData(applicationTime, elapsedTime);

	if (mIsNeedReCalCameras)
	{
		ClearCameras();

		_CollectCameras(this, this);

		mIsNeedReCalCameras = false;
	}
}
//----------------------------------------------------------------------------
void Scene::OnEvent(Event *ent)
{
	if (GraphicsES::IsEqual(ent, GraphicsES::AddObject))
	{
		AddObjectData data = ent->GetData<AddObjectData>();
		CameraNode *camNode = DynamicCast<CameraNode>(data.Obj);
		Terrain *terrain = DynamicCast<Terrain>(data.Obj);
		if (camNode)
		{
			mIsNeedReCalCameras = true;
		}
		else if (terrain)
		{
			SetTerrain(terrain);
		}
	}
	else if (GraphicsES::IsEqual(ent, GraphicsES::RemoveObject))
	{
		Object *obj = ent->GetData<Object*>();
		CameraNode *camNode = DynamicCast<CameraNode>(obj);
		if (camNode)
		{
			mIsNeedReCalCameras = true;
		}
	}
	else if (ProjectES::IsEqual(ent, ProjectES::SceneCanvasSizeChanged))
	{
		Sizef size = ent->GetData<Sizef>();
		AdjustCameraFrustum(size);
	}
}
//----------------------------------------------------------------------------
void Scene::AdjustCameraFrustum(const Sizef &canvasSize)
{
	for (int i = 0; i < (int)mCameras.size(); i++)
	{
		Camera *cam = mCameras[i];
		Projector *projector = DynamicCast<Projector>(cam);

		float upFovDegrees = 0.0f;
		float aspectRation = 0.0f;
		float dMin = 0.0f;
		float dMax = 0.0f;
		cam->GetFrustum(upFovDegrees, aspectRation, dMin, dMax);

		aspectRation = canvasSize.Width / canvasSize.Height;
		if (projector)
		{
			if (!mEnvirParam->IsShadowRenderTargetSizeSameWithCanvas())
				aspectRation = 1.0f;

			upFovDegrees = 50.0f;
		}

		cam->SetFrustum(upFovDegrees, aspectRation, dMin, dMax);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Scene::RegistProperties()
{
	Node::RegistProperties();

	AddPropertyClass("Scene");
}
//----------------------------------------------------------------------------
void Scene::OnPropertyChanged(const PropertyObject &obj)
{
	Node::OnPropertyChanged(obj);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Scene::Scene(LoadConstructor value) :
Node(value)
{
	ComeInEventWorld();
}
//----------------------------------------------------------------------------
void Scene::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadPointer(mEnvirParam);
	source.ReadPointer(mAmbientRegionController);
	source.ReadPointer(mMainCameraNode);

	PX2_END_DEBUG_STREAM_LOAD(Scene, source);
}
//----------------------------------------------------------------------------
void Scene::Link(InStream& source)
{
	Node::Link(source);

	if (mEnvirParam)
		source.ResolveLink(mEnvirParam);

	if (mAmbientRegionController)
		source.ResolveLink(mAmbientRegionController);

	if (mMainCameraNode)
		source.ResolveLink(mMainCameraNode);
}
//----------------------------------------------------------------------------
void Scene::PostLink()
{
	Node::PostLink();

	if (mEnvirParam)
		mEnvirParam->PostLink();

	if (mEnvirParam)
		mEnvirParam->ResetPlay();

	if (mAmbientRegionController)
		mAmbientRegionController->PostLink();

	if (mAmbientRegionController)
		mAmbientRegionController->ResetPlay();

	if (mMainCameraNode)
		mMainCameraNode->PostLink();
}
//----------------------------------------------------------------------------
bool Scene::Register(OutStream& target) const
{
	if (Node::Register(target))
	{
		if (mEnvirParam)
		{
			mEnvirParam->Register(target);
		}

		if (mAmbientRegionController)
		{
			mAmbientRegionController->Register(target);
		}

		if (mMainCameraNode)
		{
			mMainCameraNode->Register(target);
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Scene::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);
	PX2_VERSION_SAVE(target);

	target.WritePointer(mEnvirParam);
	target.WritePointer(mAmbientRegionController);
	target.WritePointer(mMainCameraNode);

	PX2_END_DEBUG_STREAM_SAVE(Scene, target);
}
//----------------------------------------------------------------------------
int Scene::GetStreamingSize(Stream &stream) const
{
	int size = Node::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_POINTERSIZE(mEnvirParam);
	size += PX2_POINTERSIZE(mAmbientRegionController);
	size += PX2_BOOLSIZE(mMainCameraNode);
	
	return size;
}
//----------------------------------------------------------------------------