// PX2LFile.hpp

#ifndef PX2LFILE_HPP
#define PX2LFILE_HPP

#include "PX2LogicPre.hpp"
#include "PX2Object.hpp"
#include "PX2LBlock.hpp"
#include "PX2LogicDefine.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM LFile : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LFile);

	public:
		LFile();
		virtual ~LFile();

		LBlock * GetBlockProgram();

		void SetPlatformType(LogicFilePlatformType pt);
		LogicFilePlatformType GetPlatformType() const;

		const std::string &Compile();
		std::vector<std::string> PreCompiledParams;
		bool IsPreCompiledParam(const std::string &paramName);

	protected:
		LogicFilePlatformType mPlatformType;
		LBlockPtr mBlockProgram;
		std::string mCompiledString;
	};

	PX2_REGISTER_STREAM(LFile);
	typedef Pointer0<LFile> LFilePtr;

}

#endif