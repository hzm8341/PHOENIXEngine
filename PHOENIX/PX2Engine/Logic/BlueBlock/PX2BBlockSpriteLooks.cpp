// PX2BBlockSpriteLooks.cpp

#include "PX2BBlockSprite.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void BBlockSprite::AddLook(const std::string &filename)
{
	if (ST_FRAMELIST == mSpriteType)
	{
		UIFPicBox *picBox = new0 UIFPicBox();
		mFrameObject->AttachChild(picBox);
		picBox->SetAnchorHor(0.0f, 1.0f);
		picBox->SetAnchorVer(0.0f, 1.0f);
		picBox->GetUIPicBox()->SetTexture(filename);
		Texture2D *tex2D = DynamicCast<Texture2D>(picBox->GetUIPicBox()
			->GetTexture());
		if (tex2D)
			SetSize((float)tex2D->GetWidth(), (float)tex2D->GetHeight());

		picBox->Show(false);
		mLooks.push_back(picBox);

		if (1 == mLooks.size())
		{
			SetCurLookIndex(0);
		}
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::RemoveLook(int index)
{
	if (0 <= index && index < (int)mLooks.size())
	{
		mLooks[index] = 0;
	}

	auto it = mLooks.begin();
	for (; it != mLooks.end();)
	{
		if (0 == *it)
		{
			it = mLooks.erase(it);
		}
		else
		{
			it++;
		}
	}

	SetCurLookIndex(mCurLookIndex);
}
//----------------------------------------------------------------------------
int BBlockSprite::GetNumLooks() const
{
	return (int)mLooks.size();
}
//----------------------------------------------------------------------------
UIFPicBox *BBlockSprite::GetLook(int index)
{
	if (0 <= index && index < (int)mLooks.size())
	{
		return mLooks[index];
	}

	return 0;
}
//----------------------------------------------------------------------------
void BBlockSprite::SetCurLookIndex(int index)
{
	mCurLookIndex = index;

	if (mCurLookIndex < 0 || mCurLookIndex >= (int)mLooks.size())
	{
		mCurLookIndex = 0;
	}

	for (int i = 0; i < (int)mLooks.size(); i++)
	{
		if (i == mCurLookIndex)
		{
			mLooks[i]->Show(true);
		}
		else
		{
			mLooks[i]->Show(false);
		}
	}
}
//----------------------------------------------------------------------------
int BBlockSprite::GetCurLookIndex() const
{
	return mCurLookIndex;
}
//----------------------------------------------------------------------------
UIFPicBox *BBlockSprite::GetCurLook()
{
	if (0 <= mCurLookIndex && mCurLookIndex < (int)mLooks.size())
	{
		return mLooks[mCurLookIndex];
	}

	return 0;
}
//----------------------------------------------------------------------------
void BBlockSprite::playLook(bool play)
{
	if (play)
	{
		mIsPlayingLook = true;
		mLookPlayedTime = 0.0f;
	}
	else
	{
		mIsPlayingLook = false;
		mLookPlayedTime = 0.0f;
	}
}
//----------------------------------------------------------------------------
bool BBlockSprite::isPlayingLook() const
{
	return mIsPlayingLook;
}
//----------------------------------------------------------------------------
void BBlockSprite::setLookPlaySpeed(float speed)
{
	mPlayLookSpeed = speed;

	if (mPlayLookSpeed <= 0.0f)
		mPlayLookSpeed = 0.1f;
}
//----------------------------------------------------------------------------