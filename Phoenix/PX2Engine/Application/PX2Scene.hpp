// PX2Scene.hpp

#ifndef PX2SCENE_HPP
#define PX2SCENE_HPP

#include "PX2Node.hpp"
#include "PX2EnvirParamController.hpp"
#include "PX2AmbientRegionController.hpp"
#include "PX2CameraNode.hpp"
#include "PX2Terrain.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM Scene : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_NEW(Scene);
		PX2_DECLARE_STREAM(Scene);

	public:
		Scene();
		virtual ~Scene();

		EnvirParamController *GetEnvirParamController();
		AmbientRegionController *GetAmbientRegionController();

		void SetTerrain(Terrain *terrain);
		Terrain *GetTerrain();

		std::vector<CameraPtr> &GetCameras();

		void SetMainCameraNode(CameraNode *camNode);
		CameraNode *GetMainCameraNode();

		void AdjustCameraFrustum(const Sizef &canvasSize);

	protected:
		static void _CollectCameras(Scene *scene, Node *node);

		bool AddCamera(Camera *camera);
		void ClearCameras();
		bool RemoveCamera(Camera *camera);
		virtual void UpdateWorldData(double applicationTime, 
			double elapsedTime);

		EnvirParamControllerPtr mEnvirParam;
		AmbientRegionControllerPtr mAmbientRegionController;
		TerrainPtr mTerrain;
		std::vector<CameraPtr> mCameras;
		CameraNodePtr mMainCameraNode;

		bool mIsNeedReCalCameras;

	public:
		void OnEvent(Event *ent);
	};

#include "PX2Scene.inl"
	PX2_REGISTER_STREAM(Scene);
	typedef Pointer0<Scene> ScenePtr;

}

#endif