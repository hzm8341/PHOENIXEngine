// PX2BBlockSprite.hpp

#ifndef PX2BBLOCKSPRITE_HPP
#define PX2BBLOCKSPRITE_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIFText.hpp"
#include "PX2UIEditBox.hpp"
#include "PX2UIComboBox.hpp"
#include "PX2UIRound.hpp"
#include "PX2UIWebFrame.hpp"
#include "PX2BBlockScriptGenController.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BBlockSprite : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BBlockSprite);
		PX2_DECLARE_STREAM(BBlockSprite);

	public:
		enum SpriteType
		{
			ST_FRAME,
			ST_PICBOX,
			ST_BUTTON,
			ST_TEXT,
			ST_EDITBOX,
			ST_COMBOXBOX,
			ST_PROGRESS,
			ST_WEBVIEW,
			ST_ROUND,
			ST_SLIDER,
			ST_FRAMELIST,
			ST_ARDUINO,
			ST_PHOENIXFRAME,
			ST_EAI,
			ST_MAX_TYPE
		};
		BBlockSprite(SpriteType st = ST_PICBOX);
		virtual ~BBlockSprite();

		static BBlockSprite *New(SpriteType st);

		SpriteType GetSpriteType() const;
		std::string GetSpriteTypeStr() const;

		enum HorLayOutType
		{
			HLOT_LEFT,
			HLOT_RIGHT,
			HLOT_CENTER,
			HLOT_STRATCH,
			HLOT_MAX_TYPE
		};
		void SetHorLayOutType(HorLayOutType type);
		HorLayOutType GetHorLayOutType() const;
		void SetLayoutParamHor(float param0);
		float GetLayoutParamHor() const;

		enum VerLayoutType
		{
			VLOT_BOTTOM,
			VLOT_TOP,
			VLOT_CENTER,
			VLOT_STRATCH,
			VLOT_MAX_TYPE
		};
		void SetVerLayoutType(VerLayoutType type);
		VerLayoutType GetVerLayoutType() const;
		void SetLayoutParamVer(float param0);
		float GetLayoutParamVer() const;

		virtual void SetName(const std::string &name);
		
		virtual void Enable(bool enable);

		void SetDragable(bool dragable); // 是否在编辑器你可拖动
		bool IsDragable() const;

		void SetDoPickFrameObject(bool pick);
		bool IsDoPickFrameObject() const;

		void SetLookImage(const std::string &image, bool isUse9Grid=false);
		void SetLookImage1(const std::string &image, bool isUse9Grid = false);
		virtual void AutoMakeSizeFixable();

		BBlockScriptGenController *GetScriptGenController();

		virtual void OnEvent(Event *ent);

	protected:
		virtual void UpdateWorldData(double applicationTime, double elapsedTime);
		virtual void OnWidgetPicked(const CanvasInputData &inputData);
		virtual void OnSizeNodeNotPicked(const CanvasInputData &inputData);

		SpriteType mSpriteType;
		BBlockScriptGenControllerPtr mScriptCtrl;
		UIFramePtr mFrameObject;
		bool mIsDragable;
		bool mIsDoPickFrameObject;

		HorLayOutType mHorLayOutType;
		VerLayoutType mVerLayoutType;
		float mHorLayoutParam;
		float mVerLayoutParam;
		
		// general operators
	public:
		// base
		void setName(const std::string &name);
		const std::string &getName() const;

		void attachChild(BBlockSprite *sprite);
		void detachChild(BBlockSprite *sprite);
		void detachChildByName(const std::string &name);

		void setFixUpdateFPS(int fps);
		int getFixUpdateFPS() const;

		// view
		void show(bool show);
		bool isShow() const;
		void setColor(int r, int g, int b);
		void setAlpha(float a);

		void setText(const std::string &str);
		void setTextFontSize(int size);
		std::string getText();
		void setValue(float val);
		float getValue() const;

		// transform
		void setScale(float val);
		float getScale() const;
		void setScaleXZ(float scaleX, float scaleZ);
		void setScaleX(float val);
		void setScaleZ(float val);
		float getScaleX() const;
		float getScaleZ() const;
		void addScale(float scale);

		void setRotateXYZ(float x, float y, float z);
		void setRotateX(float degree);
		void setRotateY(float degree);
		void setRotateZ(float degree);
		float getRotateX() const;
		float getRotateY() const;
		float getRotateZ() const;
		void addRotate(float degree);

		void setLayout(float horA, float horB, float horParamA, float horParamB,
			float verA, float verB, float verParamA, float verParamB,
			float pivotX, float pivotY, float width, float height);
		void setPostion(float posX, float posZ);
		void setAnchorHor(float valA, float valB);
		void setAnchorParamHor(float valA, float valB);
		void setAnchorVer(float valA, float valB);
		void setAnchorParamVer(float valA, float valB);
		void move(float moveX, float moveZ);
		void setLayer(int layer);
		int getLayer() const;

		void setPivot(float pivotX, float pivotY);
		void setSize(float size);
		void setSize1(float size);
		void setSizeWidthHeight(float width, float height);

		// round
		float getDragingDirX() const;
		float getDragingDirY() const;
		int getDragingDirSimple() const;
		float getDragingPercent() const;

		int getDragingLeftMoveType() const;
		float getDragingLeftMoveSpeed() const;
		int getDragingRightMoveType() const;
		float getDragingRightMoveSpeed() const;

		// slider
		void setSliderPercent(float perc = 0.5f);
		void setSlider100(int val = 50);
		void setSlider180(int val = 90);
		float getSliderPercent() const;
		int getSlider100() const;
		int getSlider180() const;
		int getSlider360() const;

		// combo
		void addChooseString(const std::string &str);
		void chooseString(const std::string &str);
		void chooseIndex(int index);
		std::string getChooseString();
		int getChooseIndex();

		// web
		void setURL(const std::string &url);

	protected:
		void _SetFrameCallback();
		void _UICallback(UIFrame *frame, UICallType type);

		int mFixUpdateFPS;

		int mLayerIndex;
		APoint mRotate;
		APoint mScale;

		float mValue;

		int mRoundCurDragingDirSimple;

		// looks
	public:
		void AddLook(const std::string &filename);
		void RemoveLook(int index);
		int GetNumLooks() const;
		UIFPicBox *GetLook(int index);

		void SetCurLookIndex(int index);
		int GetCurLookIndex() const;

		UIFPicBox *GetCurLook();

		void playLook(bool play);
		bool isPlayingLook() const;
		void setLookPlaySpeed(float speed);

	protected:
		std::vector<UIFPicBoxPtr> mLooks;
		float mPlayLookSpeed;

		int mCurLookIndex;
		bool mIsPlayingLook;
		float mLookPlayedTime;
	};

#include "PX2BBlockSprite.inl"
	PX2_REGISTER_STREAM(BBlockSprite);
	typedef Pointer0<BBlockSprite> BBlockSpritePtr;

}

#endif