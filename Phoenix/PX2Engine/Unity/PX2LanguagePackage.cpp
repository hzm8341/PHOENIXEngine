// PX2LanguagePackage.cpp

#include "PX2LanguagePackage.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2CSVParser.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
bool LanguagePackage::Load(const std::string &filename)
{
	CSVParser csv;

	if (csv.Load(filename))
	{
		mLanguages.Clear();

		// language start form 2
		for (int i = 2; i < csv.GetNumLines(); i++)
		{
			std::string key = csv[i][0].String();

			LanguageTableIterator it = mLanguages.Insert(key.c_str());
			if (it)
			{
				it->value.clear();

				for (int j = 1; j < csv.GetNumCols(); j++)
				{
					it->value.push_back(csv[i][j].String());
				}
			}
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool LanguagePackage::Add(const std::string &filename)
{
	CSVParser csv;

	if (csv.Load(filename))
	{
		for (int i = 2; i < csv.GetNumLines(); i++)
		{
			std::string key = csv[i][0].String();
			LanguageTableIterator it = mLanguages.Insert(key.c_str());
			if (it)
			{
				it->value.clear();

				for (int j = 1; j < csv.GetNumCols(); j++)
				{
					it->value.push_back(csv[i][j].String());
				}
			}
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void LanguagePackage::AddItem(const std::string &key, const std::string &langauge0,
	const std::string &langauge1)
{
	LanguageTableIterator it = mLanguages.Insert(key.c_str());
	if (it)
	{
		it->value.clear();

		it->value.push_back(langauge0);
		it->value.push_back(langauge1);
	}
}
//----------------------------------------------------------------------------
void LanguagePackage::AddItem1(const std::string &key, const std::string &langauge0)
{
	LanguageTableIterator it = mLanguages.Insert(key.c_str());
	if (it)
	{
		it->value.clear();

		it->value.push_back(langauge0);
		it->value.push_back(key);
	}
}
//----------------------------------------------------------------------------
void LanguagePackage::SetLanguage(int index)
{
	mLanguageIndex = index;
}
//----------------------------------------------------------------------------
bool LanguagePackage::HasValue(const std::string &key) const
{
	LanguageTableIterator it = mLanguages.Find(key.c_str());
	return 0 != it;
}
//----------------------------------------------------------------------------
const std::string &LanguagePackage::GetValue(const std::string &key)
{
	LanguageTableIterator it = mLanguages.Find(key.c_str());
	if (it)
	{
		if (mLanguageIndex < (int)it->value.size())
		{
			return it->value[mLanguageIndex];
		}
	}

	assertion(false, "language key %s does not exist.", key.c_str());
	PX2_LOG_ERROR("language key %s does not exist.", key.c_str());

	return mEmptyStr;
}
//----------------------------------------------------------------------------
const std::string &LanguagePackage::GetValueNoAssert(const std::string &key)
{
	LanguageTableIterator it = mLanguages.Find(key.c_str());
	if (it)
	{
		if (mLanguageIndex < (int)it->value.size())
		{
			return it->value[mLanguageIndex];
		}
	}

	return mEmptyStr;
}
//----------------------------------------------------------------------------
const std::string &LanguagePackage::GetValue(const std::string &key, int index)
{
	LanguageTableIterator it = mLanguages.Find(key.c_str());
	if (it)
	{
		if (mLanguageIndex < (int)it->value.size())
		{
			return it->value[index];
		}
	}

	assertion(false, "language key %s does not exist.", key.c_str());
	PX2_LOG_ERROR("language key %s does not exist.", key.c_str());

	return mEmptyStr;
}
//----------------------------------------------------------------------------
const std::string &LanguagePackage::V(const std::string &key)
{
	return GetValue(key);
}
//----------------------------------------------------------------------------
const std::string &LanguagePackage::V(const std::string &key, int index)
{
	return GetValue(key, index);
}
//----------------------------------------------------------------------------
LanguagePackage::LanguagePackage()
	:
	mLanguageIndex(0),
	mLanguages(1023)
{
}
//----------------------------------------------------------------------------
LanguagePackage::~LanguagePackage()
{
	Clear();
}
//----------------------------------------------------------------------------
void LanguagePackage::Clear()
{
	mLanguages.Clear();
}
//----------------------------------------------------------------------------