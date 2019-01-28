// PX2BSprite.inl

//----------------------------------------------------------------------------
inline bool BBlockSprite::IsDragable() const
{
	return mIsDragable;
}
//----------------------------------------------------------------------------
inline bool BBlockSprite::IsDoPickFrameObject() const
{
	return mIsDoPickFrameObject;
}
//----------------------------------------------------------------------------
inline BBlockSprite::SpriteType BBlockSprite::GetSpriteType() const
{
	return mSpriteType;
}
//----------------------------------------------------------------------------
inline BBlockScriptGenController *BBlockSprite::GetScriptGenController()
{
	return mScriptCtrl;
}
//----------------------------------------------------------------------------