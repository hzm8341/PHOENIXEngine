// PX2Scene.inl

//----------------------------------------------------------------------------
inline EnvirParamController *Scene::GetEnvirParamController()
{
	return mEnvirParam;
}
//----------------------------------------------------------------------------
inline AmbientRegionController *Scene::GetAmbientRegionController()
{
	return mAmbientRegionController;
}
//----------------------------------------------------------------------------
inline std::vector<CameraPtr> &Scene::GetCameras()
{
	return mCameras;
}
//----------------------------------------------------------------------------