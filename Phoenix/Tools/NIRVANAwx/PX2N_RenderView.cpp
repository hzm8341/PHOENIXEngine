// PX2N_RenderView.cpp

#include "PX2N_RenderView.hpp"
#include "PX2InputManager.hpp"
#include "PX2Edit.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditEventData.hpp"
#include "PX2N_Frame.hpp"
#include "PX2Time.hpp"
#include "PX2Application.hpp"
#include "PX2Selection.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2Application.hpp"
#include "PX2StringHelp.hpp"
using namespace NA;
using namespace PX2;

BEGIN_EVENT_TABLE(RenderView, wxWindow)
EVT_SIZE(RenderView::OnSize)
EVT_PAINT(RenderView::OnPaint)
EVT_ERASE_BACKGROUND(RenderView::OnEraseBackground)
EVT_ENTER_WINDOW(RenderView::OnEnterWindow)
EVT_LEAVE_WINDOW(RenderView::OnLeaveWindow)
EVT_LEFT_DOWN(RenderView::OnLeftDown)
EVT_LEFT_UP(RenderView::OnLeftUp)
EVT_LEFT_DCLICK(RenderView::OnLeftDoubleClick)
EVT_MIDDLE_DOWN(RenderView::OnMiddleDown)
EVT_MIDDLE_UP(RenderView::OnMiddleUp)
EVT_MIDDLE_DCLICK(RenderView::OnMiddleDoubleClick)
EVT_MOUSEWHEEL(RenderView::OnMouseWheel)
EVT_MOTION(RenderView::OnMotion)
EVT_RIGHT_DOWN(RenderView::OnRightDown)
EVT_RIGHT_UP(RenderView::OnRightUp)
EVT_RIGHT_DCLICK(RenderView::OnRightDoubleClick)
EVT_KEY_DOWN(RenderView::OnKeyDown)
EVT_KEY_UP(RenderView::OnKeyUp)
EVT_CHAR(RenderView::OnChar)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
RenderView::RenderView()
{
}
//----------------------------------------------------------------------------
RenderView::RenderView(RenderWindow *rw, wxWindow *parent) :
	wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
wxNO_BORDER),
mTimerID(-1),
mIsInited(false),
mRenderWindow(rw)
{
	std::string name;
	if (rw)
	{
		name = rw->GetName();
		SetName(name);

		mRenderWindowID = rw->GetID();
	}

	mTimerID = 6001 + mRenderWindowID;
	Connect(mTimerID, wxEVT_TIMER, wxTimerEventHandler(RenderView::OnTimer));

	mTimer.SetOwner(this, mTimerID);
	mTimer.Start(20);

	PX2_EW.ComeIn(this);

	SetFocus();

	if ("Main" == name)
	{

	}
	else
	{
		PX2_INPUTMAN.CreateAddListener(mRenderWindowID);
	}

	if (rw)
	{
		const Sizef &size = rw->GetScreenSize();
		mSize.SetWidth((int)size.Width);
		mSize.SetHeight((int)size.Height);
		SetClientSize(mSize);
	}
}
//----------------------------------------------------------------------------
RenderView::~RenderView()
{
}
//----------------------------------------------------------------------------
void RenderView::OnTimer(wxTimerEvent& event)
{
	if (mTimerID == event.GetId())
	{
		std::string name = GetName();
		if ("Main" == name)
		{
			Edit *edit = Edit::GetSingletonPtr();
			if (edit)
			{
				PX2_EDIT.IsAltDown = wxGetKeyState(WXK_ALT);
				PX2_EDIT.IsCtrlDown = wxGetKeyState(WXK_CONTROL);
				PX2_EDIT.IsShiftDown = wxGetKeyState(WXK_SHIFT);

				PX2_EDIT.IsKeyDown_W = wxGetKeyState((wxKeyCode)87) || wxGetKeyState((wxKeyCode)119);
				PX2_EDIT.IsKeyDown_S = wxGetKeyState((wxKeyCode)83) || wxGetKeyState((wxKeyCode)115);
				PX2_EDIT.IsKeyDown_A = wxGetKeyState((wxKeyCode)65) || wxGetKeyState((wxKeyCode)97);
				PX2_EDIT.IsKeyDown_D = wxGetKeyState((wxKeyCode)68) || wxGetKeyState((wxKeyCode)100);

				PX2_EDIT.IsLeftMouseDown = wxGetMouseState().LeftIsDown();
				PX2_EDIT.IsRightMouseDown = wxGetMouseState().RightIsDown();
				PX2_EDIT.IsMidMouseDown = wxGetMouseState().MiddleIsDown();

				PX2_APP.Update();
			}
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnSize(wxSizeEvent& e)
{
	PX2_UNUSED(e);

	mSize = GetClientSize();
	Sizef sz = Sizef((float)mSize.GetWidth(), (float)mSize.GetHeight());
	std::string name = GetName();

	if (mRenderWindow)
	{
		mRenderWindow->SetScreenSize(sz);
	}
}
//----------------------------------------------------------------------------
void RenderView::OnPaint(wxPaintEvent& e)
{
	wxPaintDC dc(this);
	PX2_UNUSED(e);
}
//----------------------------------------------------------------------------
void RenderView::OnEraseBackground(wxEraseEvent& e)
{
	if (!mIsInited) return;
	PX2_UNUSED(e);
}
//----------------------------------------------------------------------------
void RenderView::OnEnterWindow(wxMouseEvent& e)
{
	PX2_UNUSED(e);
}
//----------------------------------------------------------------------------
void RenderView::OnLeaveWindow(wxMouseEvent& e)
{
	PX2_UNUSED(e);
}
//----------------------------------------------------------------------------
PX2::APoint wxPointToAPointRightAxis(wxPoint &point, wxSize &size)
{
	return PX2::APoint((float)point.x, 0.0f, (float)(size.GetHeight() - point.y));
}
//----------------------------------------------------------------------------
void RenderView::OnLeftDown(wxMouseEvent& e)
{
	SetFocus();

	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(0, true);
			PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_LEFT, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MousePressed(MBID_LEFT, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnLeftUp(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(0, false);
			PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_LEFT, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseReleased(MBID_LEFT, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnLeftDoubleClick(wxMouseEvent& e)
{
	SetFocus();

	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(0, true);
			PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_LEFT, pos);
			PX2_INPUTMAN.GetDefaultListener()->MouseDoublePressed(MBID_LEFT, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MousePressed(MBID_LEFT, pos);
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseDoublePressed(MBID_LEFT, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnMiddleDown(wxMouseEvent& e)
{
	SetFocus();

	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(2, true);
			PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_MIDDLE, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MousePressed(MBID_MIDDLE, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnMiddleUp(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(2, false);
			PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_MIDDLE, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseReleased(MBID_MIDDLE, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnMiddleDoubleClick(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(2, true);
			PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_MIDDLE, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseReleased(MBID_MIDDLE, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnMouseWheel(wxMouseEvent& e)
{
	float delta = (float)e.GetWheelRotation()*0.1f;
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetDefaultListener()->MouseWheeled(delta, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseWheeled(delta, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnRightDown(wxMouseEvent& e)
{
	SetFocus();

	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(1, true);
			PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_RIGHT, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MousePressed(MBID_RIGHT, pos);
		}
	}

	SetFocus();
}
//----------------------------------------------------------------------------
void RenderView::OnRightUp(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(1, false);
			PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_RIGHT, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseReleased(MBID_RIGHT, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnRightDoubleClick(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			RenderWindow::SetMouseDown(1, true);
			PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_RIGHT, pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseReleased(MBID_RIGHT, pos);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnMotion(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();
	APoint pos = wxPointToAPointRightAxis(mousePos, mSize);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetDefaultListener()->MouseMoved(pos);
		}
	}
	else
	{
		if (InputManager::GetSingletonPtr())
		{
			PX2_INPUTMAN.GetInputListener(mRenderWindowID)->MouseMoved(pos);
		}
	}
}
//----------------------------------------------------------------------------
KeyCode ConverKeyCode(int wParam)
{
	KeyCode code = KC_UNASSIGNED;
	if (0x41 <= wParam && wParam <= 0x5A)
	{
		int dist = wParam - 0x41;

		if (0 == dist)
			code = KC_A;
		else if (1 == dist)
			code = KC_B;
		else if (2 == dist)
			code = KC_C;
		else if (3 == dist)
			code = KC_D;
		else if (4 == dist)
			code = KC_E;
		else if (5 == dist)
			code = KC_F;
		else if (6 == dist)
			code = KC_G;
		else if (7 == dist)
			code = KC_H;
		else if (8 == dist)
			code = KC_I;
		else if (9 == dist)
			code = KC_J;
		else if (10 == dist)
			code = KC_K;
		else if (11 == dist)
			code = KC_L;
		else if (12 == dist)
			code = KC_M;
		else if (13 == dist)
			code = KC_N;
		else if (14 == dist)
			code = KC_O;
		else if (15 == dist)
			code = KC_P;
		else if (16 == dist)
			code = KC_Q;
		else if (17 == dist)
			code = KC_R;
		else if (18 == dist)
			code = KC_S;
		else if (19 == dist)
			code = KC_T;
		else if (20 == dist)
			code = KC_U;
		else if (21 == dist)
			code = KC_V;
		else if (22 == dist)
			code = KC_W;
		else if (23 == dist)
			code = KC_X;
		else if (24 == dist)
			code = KC_Y;
		else if (25 == dist)
			code = KC_Z;
	}
	else if (0x61 <= wParam && wParam <= 0x7A)
	{
		int dist = wParam - 0x61;

		if (0 == dist)
			code = KC_A;
		else if (1 == dist)
			code = KC_B;
		else if (2 == dist)
			code = KC_C;
		else if (3 == dist)
			code = KC_D;
		else if (4 == dist)
			code = KC_E;
		else if (5 == dist)
			code = KC_F;
		else if (6 == dist)
			code = KC_G;
		else if (7 == dist)
			code = KC_H;
		else if (8 == dist)
			code = KC_I;
		else if (9 == dist)
			code = KC_J;
		else if (10 == dist)
			code = KC_K;
		else if (11 == dist)
			code = KC_L;
		else if (12 == dist)
			code = KC_M;
		else if (13 == dist)
			code = KC_N;
		else if (14 == dist)
			code = KC_O;
		else if (15 == dist)
			code = KC_P;
		else if (16 == dist)
			code = KC_Q;
		else if (17 == dist)
			code = KC_R;
		else if (18 == dist)
			code = KC_S;
		else if (19 == dist)
			code = KC_T;
		else if (20 == dist)
			code = KC_U;
		else if (21 == dist)
			code = KC_V;
		else if (22 == dist)
			code = KC_W;
		else if (23 == dist)
			code = KC_X;
		else if (24 == dist)
			code = KC_Y;
		else if (25 == dist)
			code = KC_Z;
	}
	else if (WXK_BACK == wParam)
	{
		code = KC_BACK;
	}
	else if (WXK_TAB == wParam)
	{
		code = KC_TAB;
	}
	else if (WXK_RETURN == wParam)
	{
		code = KC_RETURN;
	}
	else if (WXK_ESCAPE == wParam)
	{
		code = KC_ESCAPE;
	}
	else if (WXK_SPACE == wParam)
	{
		code = KC_SPACE;
	}
	else if (WXK_DELETE == wParam)
	{
		code = KC_DELETE;
	}
	else if (WXK_LEFT == wParam)
	{
		code = KC_LEFT;
	}
	else if (WXK_RIGHT == wParam)
	{
		code = KC_RIGHT;
	}
	else if (WXK_DOWN == wParam)
	{
		code = KC_DOWN;
	}
	else if (WXK_UP == wParam)
	{
		code = KC_UP;
	}
	else if (WXK_CONTROL == wParam)
	{
		code = KC_LCONTROL;
	}
	else if (WXK_NUMLOCK == wParam)
	{
		code = KC_NUMLOCK;
	}
	else if (WXK_SCROLL == wParam)
	{
		code = KC_SCROLL;
	}
	else if (WXK_PAGEUP == wParam)
	{
		code = KC_PGUP;
	}
	else if (WXK_PAGEDOWN == wParam)
	{
		code = KC_PGDOWN;
	}
	else if (WXK_ESCAPE == wParam)
	{
		code = KC_ESCAPE;
	}
	else if (WXK_DELETE == wParam)
	{
		code = KC_DELETE;
	}

	return code;
}
//----------------------------------------------------------------------------
void RenderView::OnKeyDown(wxKeyEvent& e)
{
	int keyCode = e.GetKeyCode();

	KeyCode kc = ConverKeyCode(keyCode);

	std::string name = GetName();
	if ("Main" == name)
	{
		PX2_INPUTMAN.GetDefaultListener()->KeyPressed(kc);
	}
	else
	{
		PX2_INPUTMAN.GetInputListener(mRenderWindowID)->KeyPressed(kc);
	}

	e.Skip();
}
//----------------------------------------------------------------------------
void RenderView::OnKeyUp(wxKeyEvent& e)
{
	int keyCode = e.GetKeyCode();

	KeyCode kc = ConverKeyCode(keyCode);
	std::string name = GetName();
	
	if ("Main" == name)
	{
		PX2_INPUTMAN.GetDefaultListener()->KeyReleased(kc);
		if (WXK_DELETE == keyCode)
		{
			IMEDispatcher::GetSingleton().DispathDelete();
		}
	}
	else
	{
		PX2_INPUTMAN.GetInputListener(mRenderWindowID)->KeyReleased(kc);
		if (WXK_DELETE == keyCode)
		{
			IMEDispatcher::GetSingleton().DispathDelete();
		}

	}

	e.Skip();
}
//----------------------------------------------------------------------------
void RenderView::OnChar(wxKeyEvent& e)
{
	int keyCode = e.GetKeyCode();
	wxChar chara = e.GetUnicodeKey();
	wchar_t charas[2];
	charas[0] = chara;
	charas[1] = '\0';
	std::wstring str(charas);
	PX2_INPUTMAN.GetDefaultListener()->KeyChar(str);

	if (keyCode < 32)
	{
		if (WXK_BACK == keyCode)
		{
			IMEDispatcher::GetSingleton().DispathDeleteBackward();
		}
		else if (WXK_RETURN == keyCode)
		{
			IMEDispatcher::GetSingleton().DispathInsertText("\n", 1);
		}
		else if (WXK_TAB == keyCode)
		{
			// tab input
		}
		else if (WXK_ESCAPE == keyCode)
		{
			// ESC input
		}
	}
	else if (keyCode < 128)
	{
		IMEDispatcher::GetSingleton().DispathInsertText((const char*)&keyCode, 1);
	}
	else
	{
		if (WXK_LEFT == keyCode)
		{
			IMEDispatcher::GetSingleton().DispathArrow(0);
		}
		else  if (WXK_RIGHT == keyCode)
		{
			IMEDispatcher::GetSingleton().DispathArrow(1);
		}
	}
}
//----------------------------------------------------------------------------
void RenderView::OnEvent(PX2::Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------