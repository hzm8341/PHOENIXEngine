// PX2BBlockScriptGenController.hpp

#ifndef PX2BBLOCKSCRIPTGENCONTROLLER_HPP
#define PX2BBLOCKSCRIPTGENCONTROLLER_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UITabFrame.hpp"
#include "PX2LFile.hpp"
#include "PX2Controller.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BBlockScriptGenController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BBlockScriptGenController);
		PX2_DECLARE_STREAM(BBlockScriptGenController);

	public:
		BBlockScriptGenController();
		virtual ~BBlockScriptGenController();

		virtual void SetName(const std::string& name);

		enum GenerateType
		{
			GT_ENGINE,
			GT_ARDUINO,
			GT_NODEMCU,
			GT_RASPBERRY,
			GT_MAX_TYPE
		};
		void SetGenerateType(GenerateType at);
		GenerateType GetGenerateType() const;

		LFile *GetLFile();

		virtual void OnEvent(Event *ent);

	protected:
		void _RemoveScriptCtrl();

		GenerateType mGenerateType;
		LFilePtr mLFile;
	};

	PX2_REGISTER_STREAM(BBlockScriptGenController);
	typedef Pointer0<BBlockScriptGenController> BBlockScriptGenControllerPtr;

}

#endif