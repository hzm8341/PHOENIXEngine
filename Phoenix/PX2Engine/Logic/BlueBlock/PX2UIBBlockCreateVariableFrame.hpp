// PX2UIBBlockCreateVariableFrame.hpp

#ifndef PX2UIBBLOCKCREATEVARIABLEFRAME_HPP
#define PX2UIBBLOCKCREATEVARIABLEFRAME_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIEditBox.hpp"
#include "PX2UIComboBox.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BUICreateVariableFrame : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BUICreateVariableFrame);
		PX2_DECLARE_STREAM(BUICreateVariableFrame);

	public:
		BUICreateVariableFrame();
		virtual ~BUICreateVariableFrame();

	protected:
		void _ButCallback(UIFrame *frame, UICallType type);
		UIEditBoxPtr mEditBoxVariable;

		UIComboBoxPtr mComboParamType;
	};

	PX2_REGISTER_STREAM(BUICreateVariableFrame);
	typedef Pointer0<BUICreateVariableFrame> BUICreateVariableFramePtr;



}

#endif