// PX2ObjectInspector.hpp

#ifndef PX2OBJECTINSPECTOR_HPP
#define PX2OBJECTINSPECTOR_HPP

#include "PX2N_Pre.hpp"
#include "PX2N_ObjectInspector.hpp"
#include "PX2N_ObjectPropertyGrid.hpp"
#include "PX2N_MakingWindow.hpp"

namespace NA
{

	class ObjectInspector : public wxWindow
	{
	public:
		ObjectInspector(wxWindow *parent);
		~ObjectInspector();

		void OnSize(wxSizeEvent& e);

		void SetObject(PX2::Object *obj);

		void ChangeShowWindow(int windowType);//1 ObjectProperty 2 Making

	protected:
		DECLARE_EVENT_TABLE()

		ObjectInspector();

		bool mInitSized;
		PX2::ObjectPtr mObject;
		ObjectPropertyGrid *mObjectPropGrid;
		MakingWindow *mMakingWindow;
	};

}

#endif