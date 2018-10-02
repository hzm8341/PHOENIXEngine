// PX2BBManager.hpp

#ifndef PX2BBMANAGER_HPP
#define PX2BBMANAGER_HPP

#include "PX2BBlockPre.hpp"
#include "PX2LogicPre.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2BBlock.hpp"
#include "PX2Float4.hpp"
#include "PX2BBlockSprite.hpp"
#include "PX2BProject.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BBManager : public EventHandler, public Singleton<BBManager>
	{
	public:
		BBManager();
		virtual ~BBManager();

		virtual void OnEvent(Event *ent);

		std::map<std::string, Float4> CateColors;
		Float3 GetParamTypeColor(FunParamType fpt);

		void SetPlatformTag(const std::string &platTag);
		const std::string &GetPlatformTag() const;

		void SetProductTag(const std::string &productTag);
		const std::string &GetProductTag() const;

		// 主目录是否是竖直排列模式
		void SetSideCata(bool isSideCata);
		bool IsSideCata() const;

		void Clear();
		void Update(float elapsedTime);

		void SetEditorPressingBBlock(BBlock *block);
		BBlock *GetEditorPressingBBlock();

		void SetDragingBBlock(BBlock *block);
		BBlock *GetDragingBBlock();

		void SetSelectBBlockCata(BBlock *block);
		BBlock *GetSelectBBlockCata();

		void SetSelectBBlockEditor(BBlock *block);
		BBlock *GetSelectBBlockEditor();

		void SetCopyBBlock(BBlock *block);
		BBlock *GetCopyBBlock();

		void SetRecycleButton(UIButton *but);
		UIButton *GetRecycleButton();

		void ShowBlockCata(const std::string &cata);

		void SetNeedCompileScript(bool cmp);
		void CompileSetGenScript();

		void SetSelectSprite(BBlockSprite *sprite);
		BBlockSprite *GetSelectSprite();

		void _GenDefaultParams(BBlock* block);

	protected:
		std::string mPloatformTag;
		std::string mProductTag;

		bool mIsSideCata;

		BBlockPtr mPressingBBlock;
		BBlockPtr mDragingBBlock;

		BBlockPtr mSelectBBlockCata;
		BBlockPtr mSelectBBlockEditor;

		BBlockPtr mCopyBBlock;

		UIButtonPtr mRecycleButton;
		bool mIsNeedCompileScirpt;

		BBlockSpritePtr mSelectSprite;

	public:
		void SetStageFrame(UIFrame *stageFrame);
		UIFrame *GetStageFrame();

		void SetSmallFrame(UIFrame *smallFrame);
		UIFrame *GetSmallFrame();

		void GetLocalProjects(const std::string &appName);

		BProject *GetCurProject();
		
		int GetNumProject() const;
		std::string GetProjectName(int i) const;
		BProject *GetProject(int i) const;

		int NewProject(const std::string &appName, const std::string &projName);
		void SaveProject();
		void SaveProject(const std::string &name, const std::string &date, const std::string &desc);
		bool LoadProject(const std::string &appName, const std::string &projName);
		const std::string &GetAppName() const;
		const std::string &GetProjectName() const;

		bool IsHasProject(const std::string &projName);
		void CloseProject();

		void DeleteProject(const std::string &appName, const std::string &projName);

	private:
		void _CheckCreateProjectPath(const std::string &appName,
			const std::string &projName);
		std::string _GetWritePath(const std::string &appName);
		void _CreateSaveProjsectsXML(const std::string &appName);

		UIFramePtr mStageFrame;
		UIFramePtr mSmallFrame;

		std::string mAppName;
		std::vector<BProjectPtr> mProjects;
		BProjectPtr mProject;
	};

#define PX2_BBM BBManager::GetSingleton()

}

#endif