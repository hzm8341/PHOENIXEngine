// PX2Project.cpp

#include "PX2Project.hpp"
#include "PX2XMLData.hpp"
#include "PX2StringHelp.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Renderer.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Application.hpp"
#include "PX2ProjectEvent.hpp"
#if defined __ANDROID__
#include "AppPlayJNI.hpp"
#endif
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, Project);

//----------------------------------------------------------------------------
Project::Project() :
mEdit_UICameraPercent(1.0f),
mScreenOrientation(SO_LANDSCAPE),
mIsPublish(false)
{
	mBackgroundColor = Float4(0.5f, 0.5f, 0.5f, 1.0f);
	mProjBackgroundColor = Float4::WHITE;

	mUI = new0 UI();

	mLProject = new0 LProject();

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
Project::~Project()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void Project::SetName(const std::string &name)
{
	Object::SetName(name);
}
//----------------------------------------------------------------------------
void Project::Destory()
{
	if (PX2_APP.TheProject)
	{
		PX2_APP.TheProject = 0;
		Project::Set(0);
	}
}
//----------------------------------------------------------------------------
void Project::SetScreenOrientation(ScreenOrientation so)
{
	mScreenOrientation = so;

	if (SO_LANDSCAPE == mScreenOrientation)
	{
#if defined __ANDROID__
	//	SetScreenOrientate(1);
#endif
	}
	else
	{
#if defined __ANDROID__
	//	SetScreenOrientate(0);
#endif
	}
}
//----------------------------------------------------------------------------
Project::ScreenOrientation Project::_FromSOStr(const std::string &str)
{
	if ("landscape" == str) return SO_LANDSCAPE;
	else if ("portrait" == str) return SO_PORTRAIT;

	return SO_PORTRAIT;
}
//----------------------------------------------------------------------------
std::string Project::_ToSOStr(Project::ScreenOrientation so)
{
	if (SO_LANDSCAPE == so) return "landscape";
	else if (SO_PORTRAIT == so) return "portrait";

	return "portrait";
}
//----------------------------------------------------------------------------
bool Project::Save(const std::string &filename)
{
	if (!SaveConfig(filename))
		return false;

	std::string outPath;
	std::string outBaseName;
	std::string outExt;
	StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExt);

	if (mUI)
	{
		std::string outName = outPath + outBaseName + "_ui.px2obj";

		OutStream output;
		output.Insert(mUI);
		output.Save(outName);
	}

	if (mLProject)
	{
		std::string outName = outPath + outBaseName + "_bp.px2obj";

		OutStream output;
		output.Insert(mLProject);
		output.Save(outName);
	}

	return false;
}
//----------------------------------------------------------------------------
bool Project::SaveConfig(const std::string &filename)
{
	// xml
	XMLData data;
	data.Create();

	XMLNode projNode = data.NewChild("project");

	// general
	XMLNode generalNode = projNode.NewChild("general");
	generalNode.SetAttributeString("name", GetName().c_str());
	generalNode.SetAttributeString("screenorientation", _ToSOStr(mScreenOrientation));
	generalNode.SetAttributeInt("width", (int)mSize.Width);
	generalNode.SetAttributeInt("height", (int)mSize.Height);
	std::string colorStr =
		StringHelp::IntToString((int)(mBackgroundColor[0] * 255.0f)) + "," +
		StringHelp::IntToString((int)(mBackgroundColor[1] * 255.0f)) + "," +
		StringHelp::IntToString((int)(mBackgroundColor[2] * 255.0f)) + "," +
		StringHelp::IntToString((int)(mBackgroundColor[3] * 255.0f));
	generalNode.SetAttributeString("backcolor", colorStr);
	std::string projColorStr =
		StringHelp::IntToString((int)(mProjBackgroundColor[0] * 255.0f)) + "," +
		StringHelp::IntToString((int)(mProjBackgroundColor[1] * 255.0f)) + "," +
		StringHelp::IntToString((int)(mProjBackgroundColor[2] * 255.0f)) + "," +
		StringHelp::IntToString((int)(mProjBackgroundColor[3] * 255.0f));
	generalNode.SetAttributeString("projcolor", projColorStr);

	// scene
	XMLNode sceneNode = projNode.NewChild("scene");
	sceneNode.SetAttributeString("filename", mSceneFilename.c_str());

	// render setting
	XMLNode renderNode = projNode.NewChild("render_setting");

	// language
	XMLNode languageNode = projNode.NewChild("language");

	// publish
	XMLNode publish = projNode.NewChild("publish");
	publish.SetAttributeBool("ispublish", IsPublish());

	// setting
	XMLNode settingNode = projNode.NewChild("edit_setting");
	settingNode.SetAttributeFloat("uicamerapercent", mEdit_UICameraPercent);

	if (data.SaveFile(filename))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool Project::Load(const std::string &filename)
{
#if defined (_WIN32) || defined(WIN32)
	if (!PX2_RM.IsFileFloderExist(filename))
		return false;
#endif

	std::string name;
	int height = 0;
	std::string sceneFilename;
	int width = 0;
	std::string uiFilename;
	std::string languageFilename;

	char *buffer = 0;
	int bufferSize = 0;
	if (PX2_RM.LoadBuffer(filename, bufferSize, buffer))
	{
		XMLData data;
		if (data.LoadBuffer(buffer, bufferSize))
		{
			XMLNode rootNode = data.GetRootNode();

			// general
			XMLNode generalNode = rootNode.GetChild("general");
			if (!generalNode.IsNull())
			{
				name = generalNode.AttributeToString("name");

				SetScreenOrientation(_FromSOStr(generalNode.AttributeToString("screenorientation")));

				width = generalNode.AttributeToInt("width");
				height = generalNode.AttributeToInt("height");

				std::string colorStr = generalNode.AttributeToString("backcolor");
				StringTokenizer stk(colorStr, ",");
				Float4 color = Float4::MakeColor(
					StringHelp::StringToInt(stk[0]),
					StringHelp::StringToInt(stk[1]),
					StringHelp::StringToInt(stk[2]),
					StringHelp::StringToInt(stk[3]));

				std::string projcolorStr = generalNode.AttributeToString("projcolor");
				StringTokenizer stkprojcolor(projcolorStr, ",");
				Float4 projcolor = Float4::MakeColor(
					StringHelp::StringToInt(stkprojcolor[0]),
					StringHelp::StringToInt(stkprojcolor[1]),
					StringHelp::StringToInt(stkprojcolor[2]),
					StringHelp::StringToInt(stkprojcolor[3]));

				Sizef size = Sizef((float)width, (float)height);
				SetName(name);
				SetSize(size);
				SetBackgroundColor(color);
				SetProjBackgroundColor(projcolor);
			}

			// scene
			XMLNode sceneNode = rootNode.GetChild("scene");
			if (!sceneNode.IsNull())
			{
				sceneFilename = sceneNode.AttributeToString("filename");
				SetSceneFilename(sceneFilename);
			}

			XMLNode renderNode = rootNode.GetChild("render_setting");
			if (!renderNode.IsNull())
			{
			}

			// language
			XMLNode languageNode = rootNode.GetChild("language");

			// publish
			XMLNode publishNode = rootNode.GetChild("publish");
			if (!publishNode.IsNull())
			{
				if (publishNode.HasAttribute("ispublish"))
				{
					mIsPublish = publishNode.AttributeToBool("ispublish");
				}
			}

			// setting
			XMLNode settingNode = rootNode.GetChild("setting");
			if (!settingNode.IsNull())
			{
				if (settingNode.HasAttribute("uicamerapercent"))
					mEdit_UICameraPercent = settingNode.AttributeToFloat("uicamerapercent");
			}

			// split file names
			std::string outPath;
			std::string outBaseName;
			std::string outExt;
			StringHelp::SplitFullFilename(filename, outPath, outBaseName, outExt);

			// ui
			mUIFilename = outPath + outBaseName + "_ui.px2obj";

			// bp
			mLFilename = outPath + outBaseName + "_logic.px2obj";
		}
	}
	else
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
void Project::SetScene(Scene *scene)
{
	if (mScene)
	{
		Scene *sceneOrigin = mScene;

		mScene->GoOutEventWorld();
		mScene = 0;

		Event *ent = PX2_CREATEEVENTEX(ProjectES, CloseScene);
		ent->SetData<Scene*>(sceneOrigin);
		PX2_EW.BroadcastingLocalEvent(ent);
	}

	mScene = scene;

	if (mScene)
	{
		mScene->WorldTransformIsCurrent = true;

		Event *ent = PX2_CREATEEVENTEX(ProjectES, NewScene);
		ent->SetData<Scene*>((Scene*)mScene);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void Project::SetSceneFilename(const std::string &scenefilename)
{
	mSceneFilename = scenefilename;
}
//----------------------------------------------------------------------------
void Project::SetUI(UI *ui)
{
	UIPtr ui1 = ui;

	if (mUI)
	{
		UI *uiBefore = mUI;

		mUI = 0;
		Event *ent = PX2_CREATEEVENTEX(ProjectES, CloseUI);
		ent->SetData<UI*>(uiBefore);
		PX2_EW.BroadcastingLocalEvent(ent);
	}

	mUI = ui1;

	if (mUI)
	{
		mUI->SetSize(mSize);

		Event *ent = PX2_CREATEEVENTEX(ProjectES, NewUI);
		ent->SetData<UI*>((UI*)mUI);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
UI *Project::GetUI()
{
	return mUI;
}
//----------------------------------------------------------------------------
void Project::SetLProject(LProject *package)
{
	if (mLProject)
	{
		LProject *bpBefore = mLProject;

		mLProject = 0;
		Event *ent = PX2_CREATEEVENTEX(ProjectES, CloseLP);
		ent->SetData<LProject*>(bpBefore);
		PX2_EW.BroadcastingLocalEvent(ent);
	}

	mLProject = package;

	if (mLProject)
	{
		Event *ent = PX2_CREATEEVENTEX(ProjectES, NewLP);
		ent->SetData<LProject*>((LProject*)mLProject);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void Project::SetSize(float width, float height)
{
	SetSize(Sizef(width, height));
}
//----------------------------------------------------------------------------
void Project::SetSize(const Sizef &size)
{
	mSize = size;

	if (mUI)
	{
		mUI->SetSize(mSize);
	}
}
//----------------------------------------------------------------------------
void Project::SetBackgroundColor(const Float4 &color)
{
	mBackgroundColor = color;
}
//----------------------------------------------------------------------------
const Float4 &Project::GetBackgroundColor() const
{
	return mBackgroundColor;
}
//----------------------------------------------------------------------------
void Project::SetProjBackgroundColor(const Float4 &color)
{
	mProjBackgroundColor = color;
}
//----------------------------------------------------------------------------
const Float4 &Project::GetProjBackgroundColor() const
{
	return mProjBackgroundColor;
}
//----------------------------------------------------------------------------
void Project::SetPublish(bool pub)
{
	mIsPublish = pub;
}
//----------------------------------------------------------------------------
bool Project::IsPublish() const
{
	return mIsPublish;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Project::RegistProperties()
{
	Object::RegistProperties();

	AddPropertyClass("Project");

	std::vector<std::string> screenOrientations;
	screenOrientations.push_back("SO_LANDSCAPE");
	screenOrientations.push_back("SO_PORTRAIT");

	AddPropertyEnum("ScreenOrientation", (int)mScreenOrientation,
		screenOrientations);

	AddProperty("Size", PT_SIZE, mSize);

	Float3 color(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[1]);
	AddProperty("BackgroundColor", PT_COLOR3FLOAT3, color);

	Float3 colorProj(mProjBackgroundColor[0], mProjBackgroundColor[1],
		mProjBackgroundColor[2]);
	AddProperty("ProjBackgroundColor", PT_COLOR3FLOAT3, colorProj);
}
//----------------------------------------------------------------------------
void Project::OnPropertyChanged(const PropertyObject &obj)
{
	Object::OnPropertyChanged(obj);

	if ("ScreenOrientation" == obj.Name)
	{
		SetScreenOrientation((ScreenOrientation)PX2_ANY_AS(obj.Data, int));
	}
	else if ("Size" == obj.Name)
	{
		SetSize(PX2_ANY_AS(obj.Data, Sizef));
	}
	else if ("BackgroundColor" == obj.Name)
	{
		Float3 backColor = PX2_ANY_AS(obj.Data, Float3);
		mBackgroundColor = Float4(backColor[0], backColor[1], backColor[2],
			1.0f);
	}
	else if ("ProjBackgroundColor" == obj.Name)
	{
		Float3 progBackColor = PX2_ANY_AS(obj.Data, Float3);
		mProjBackgroundColor = Float4(progBackColor[0], progBackColor[1],
			progBackColor[2], 1.0f);
	}
}
