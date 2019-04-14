// PX2Slam.inl

//----------------------------------------------------------------------------
inline const AVector &Robot::GetOffset() const
{
	return mOffset;
}
//----------------------------------------------------------------------------
inline const AVector &Robot::GetDirection() const
{
	return mDirection;
}
//----------------------------------------------------------------------------
inline const AVector &Robot::GetUp() const
{
	return mUp;
}
//----------------------------------------------------------------------------
inline const AVector &Robot::GetRight() const
{
	return mRight;
}
//----------------------------------------------------------------------------
inline const HMatrix &Robot::GetMatrix() const
{
	return mMatrix;
}
//----------------------------------------------------------------------------
inline float Robot::GetSlam2DDegree() const
{
	return m2DSlameAngle;
}
//----------------------------------------------------------------------------
inline const AVector &Robot::GetMoveDirection() const
{
	return mMapSlam2DMoveDirection;
}
//----------------------------------------------------------------------------
inline float Robot::GetMoveDirectionDegree() const
{
	return mMoveDirectionDegreeWithFirst;
}
//----------------------------------------------------------------------------
inline void Robot::SetSlamMapUpdate(bool update)
{
	mIsSlamMapUpdate = update;
}
//----------------------------------------------------------------------------
inline bool Robot::IsSlamMapUpdate() const
{
	return mIsSlamMapUpdate;
}
//----------------------------------------------------------------------------
inline void Robot::SetCurMapUsingAxisWithOffset(float yDegree)
{
	mCurMapUsingAxisWithOffset = yDegree;
}
//----------------------------------------------------------------------------
inline Texture2D *Robot::GetTextureMap()
{
	return mTextureMap;
}
//----------------------------------------------------------------------------
inline UIFPicBox *Robot::GetUIFPicBoxMap()
{
	return mPicBoxMap;
}
//----------------------------------------------------------------------------
inline PathingGraph *Robot::GetPathingGraph()
{
	return mPathGraph;
}
//----------------------------------------------------------------------------
inline Robot::RoleType Robot::GetRoleType() const
{
	return mRoleType;
}
//----------------------------------------------------------------------------
inline LiDar *Robot::GetLidar()
{
	return mLiDar;
}
//----------------------------------------------------------------------------
inline Arduino *Robot::GetArduino()
{
	return mArduino;
}
//----------------------------------------------------------------------------