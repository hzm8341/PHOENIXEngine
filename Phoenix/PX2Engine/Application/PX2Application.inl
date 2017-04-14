// PX2Application.inl

//----------------------------------------------------------------------------
inline const Sizef &Application::GetBoostSize() const
{
	return mBoostSize;
}
//----------------------------------------------------------------------------
inline const std::string &Application::GetBoostProjectName() const
{
	return mBoostProjectName;
}
//----------------------------------------------------------------------------
inline const std::string &Application::GetProjectFilePath() const
{
	return mProjectFilePath;
}
//----------------------------------------------------------------------------
inline const Sizef &Application::GetScreenSize() const
{
	return mScreenSize;
}
//----------------------------------------------------------------------------
inline Application::PlayLogicMode Application::GetPlayLogicMode() const
{
	return mPlayLogicMode;
}
//----------------------------------------------------------------------------
inline Canvas *Application::GetEngineCanvas()
{
	return mEngineCanvas;
}
//----------------------------------------------------------------------------
inline Application::PlayType Application::GetPlayType() const
{
	return mPlayType;
}
//----------------------------------------------------------------------------