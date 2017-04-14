// PX2LanguageManager.cpp

#include "PX2LanguageManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
LanguageManager::LanguageManager()
{
	mPackageEditor = new0 LanguagePackage();
	mPackageApp = new0 LanguagePackage();
	mPackageApp1 = new0 LanguagePackage();
}
//----------------------------------------------------------------------------
LanguageManager::~LanguageManager()
{
}
//----------------------------------------------------------------------------
LanguagePackage *LanguageManager::GetPackageEditor()
{
	return mPackageEditor;
}
//----------------------------------------------------------------------------
LanguagePackage *LanguageManager::GetPackageApp()
{
	return mPackageApp;
}
//----------------------------------------------------------------------------
LanguagePackage *LanguageManager::GetPackageApp1()
{
	return mPackageApp1;
}
//----------------------------------------------------------------------------