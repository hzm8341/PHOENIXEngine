// PX2Application.cpp

#if defined (__LINUX__)

#ifdef PX2_USE_OPENGL
#include "PX2OpenGLRendererInput.hpp"
#include "PX2OpenGLRendererData.hpp"
#elif defined PX2_USE_OPENGLES
#include "PX2OpenGLESRendererInput.hpp"
#include "PX2OpenGLESRendererData.hpp"
#endif

#endif

#include "PX2App.hpp"
#include "PX2IMEDispatcher.hpp"
#include "PX2Application.hpp"
#include "PX2InputManager.hpp"
#include "PX2UISizeExtendControl.hpp"
#include "PX2ProjectEvent.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)

static std::queue<int> s_isUniChar;
static BYTE s_lobyte;
static BYTE s_hibyte;

#define GET_WHEEL_DELTA_WPARAM(wParam) ((short)HIWORD(wParam))

/*
* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
* 0x40 : unassigned
* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
*/
//----------------------------------------------------------------------------
KeyCode ConverKeyCode(WPARAM wParam)
{
	KeyCode code = KC_UNASSIGNED;
	if (0x41 == wParam) code = KC_A;
	else if (0x42 == wParam) code = KC_B;
	else if (0x43 == wParam) code = KC_C;
	else if (0x44 == wParam) code = KC_D;
	else if (0x45 == wParam) code = KC_E;
	else if (0x46 == wParam) code = KC_F;
	else if (0x47 == wParam) code = KC_G;
	else if (0x48 == wParam) code = KC_H;
	else if (0x49 == wParam) code = KC_I;
	else if (0x4A == wParam) code = KC_J;
	else if (0x4B == wParam) code = KC_K;
	else if (0x4C == wParam) code = KC_L;
	else if (0x4D == wParam) code = KC_M;
	else if (0x4E == wParam) code = KC_N;
	else if (0x4F == wParam) code = KC_O;
	else if (0x50 == wParam) code = KC_P;
	else if (0x51 == wParam) code = KC_Q;
	else if (0x52 == wParam) code = KC_R;
	else if (0x53 == wParam) code = KC_S;
	else if (0x54 == wParam) code = KC_T;
	else if (0x55 == wParam) code = KC_U;
	else if (0x56 == wParam) code = KC_V;
	else if (0x57 == wParam) code = KC_W;
	else if (0x58 == wParam) code = KC_X;
	else if (0x59 == wParam) code = KC_Y;
	else if (0x5A == wParam) code = KC_Z;
	return code;
}

static APoint sMousePos;
LRESULT CALLBACK MsWindowEventHandler (HWND handle, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	int sizeX = 0;
	int sizeY = 0;
	static bool firsttime = true;
	static bool isCreated = false;
	float wheeldelta = 0.0f;
	KeyCode keyCode = KC_UNASSIGNED;

	switch (message) 
	{
	case WM_CREATE:
		isCreated = true;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		sizeX = LOWORD(lParam);
		sizeY = HIWORD(lParam);

		if (isCreated)
			AppBase::msApplication->OnSize(sizeX, sizeY);

		switch (wParam)
		{
		case SIZE_RESTORED:
			if (AppBase::msApplication->IsInitlized())
				AppBase::msApplication->WillEnterForeground(firsttime);
			firsttime = false;
			break;
		case SIZE_MINIMIZED:
			if (AppBase::msApplication->IsInitlized())
				AppBase::msApplication->DidEnterBackground();
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		if (MK_LBUTTON == wParam)
		{
			POINT point = { (short)LOWORD(lParam), (short)HIWORD(lParam) };

			PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_LEFT, 
				APoint((float)point.x, 0.0f,
				PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)point.y));
		}
		break;
	case WM_LBUTTONUP:

		PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_LEFT,
			APoint((float)LOWORD(lParam), 0.0f, 
			PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)HIWORD(lParam)));

		break;
	case WM_RBUTTONDOWN:
		if (MK_RBUTTON == wParam)
		{
			POINT point = { (short)LOWORD(lParam), (short)HIWORD(lParam) };

			PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_RIGHT,
				APoint((float)point.x, 0.0f, 
				PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)point.y));
		}
		break;
	case WM_RBUTTONUP:

		PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_RIGHT,
			APoint((float)LOWORD(lParam), 0.0f, 
			PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)HIWORD(lParam)));

		break;
	case WM_MBUTTONDOWN:
		PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_MIDDLE,
			APoint((float)LOWORD(lParam), 0.0f,
			PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)HIWORD(lParam)));

		break;
	case WM_MBUTTONUP:
		PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_MIDDLE,
			APoint((float)LOWORD(lParam), 0.0f,
			PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)HIWORD(lParam)));

		break;
	case WM_MOUSEMOVE:
		sMousePos = APoint((float)LOWORD(lParam), 0.0f,
			PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height - (float)HIWORD(lParam));
		PX2_INPUTMAN.GetDefaultListener()->MouseMoved(sMousePos);

		break;
	case WM_MOUSEWHEEL:
		wheeldelta = (float)GET_WHEEL_DELTA_WPARAM(wParam);
		PX2_INPUTMAN.GetDefaultListener()->MouseWheeled(wheeldelta, sMousePos);
		break;
	case WM_KEYDOWN:
		keyCode = ConverKeyCode(wParam);
		PX2_INPUTMAN.GetDefaultListener()->KeyPressed(keyCode);

		break;
	case WM_KEYUP:
		keyCode = ConverKeyCode(wParam);
		PX2_INPUTMAN.GetDefaultListener()->KeyReleased(keyCode);

		break;
	case WM_IME_CHAR:	
		if (wParam > 0x7f) 
		{
			s_isUniChar.push(2);
		}
		else 
		{
			s_isUniChar.push(0);
		}
		break;
	case WM_CHAR:
		if (s_isUniChar.empty())
		{
			if (wParam < 0x20)
			{
				if (VK_BACK == wParam)
				{
					IMEDispatcher::GetSingleton().DispathDeleteBackward();
				}
				else if (VK_RETURN == wParam)
				{
					IMEDispatcher::GetSingleton().DispathInsertText("\n", 1);
				}
				else if (VK_TAB == wParam)
				{
					// tab input
				}
				else if (VK_ESCAPE == wParam)
				{
					// ESC input
				}
			}
			else if (wParam < 128)
			{
				IMEDispatcher::GetSingleton().DispathInsertText((const char*)&wParam, 1);
			}
		}
		else
		{
			int& rate = s_isUniChar.front();
			if (rate == 2) 
			{
				--rate;
				s_lobyte = (BYTE)wParam;
				break;
			}
			else if (rate == 1)
			{
				s_isUniChar.pop();
				s_hibyte = (BYTE)wParam;
				DWORD wideChar = MAKEWORD(s_lobyte, s_hibyte);

				wchar_t s_ch[3] = {0};
				int nUTF16Size = ::MultiByteToWideChar(
					CP_ACP,
					0,
					(LPCSTR)&wideChar,
					4,
					s_ch,
					3);
				if (nUTF16Size == 0) 
				{
					return -1;
				}

				int u8Len = ::WideCharToMultiByte(CP_UTF8, 0, s_ch, nUTF16Size, 0, 0, 0, 0);

				char szUtf8[8] = {0};
				int length = WideCharToMultiByte(CP_UTF8, 0, s_ch, nUTF16Size, szUtf8, u8Len, 0, 0);
				PX2_UNUSED(length);
				IMEDispatcher::GetSingleton().DispathInsertText(szUtf8, 3);
			}
			else 
			{
				s_isUniChar.pop();
			}
		}
		break;
	default:
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
#endif

//----------------------------------------------------------------------------
App::App ()
{
#if defined(_WIN32) || defined(WIN32)
	mhWnd = 0;
#elif defined(__LINUX__)
	mDisplay = 0;
#endif
}
//----------------------------------------------------------------------------
App::~App ()
{
}
//----------------------------------------------------------------------------
int App::Entry (int numArguments, char** arguments)
{
	App* theApp = (App*)msApplication;
	return theApp->Main(numArguments, arguments);
}
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
int App::Main (int numArguments, char** arguments)
{
	AppBase::Main(numArguments, arguments);

	Initlize ();

	// ��ʾ����
	ShowWindow(mhWnd, SW_SHOWNORMAL);
	UpdateWindow(mhWnd);

	// ��Ϣѭ��
	while (!PX2_APP.IsQuit())
	{
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				PX2_APP.SetQuit(true);
				continue;
			}

			HACCEL accel = 0;
			if (!TranslateAccelerator(mhWnd, accel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{
			OnIdle();
		}
	}

	Terminate ();

	return 0;
}
#elif defined(__LINUX__)
#define GLXAPP_BUTTONDOWN   0
#define GLXAPP_SHIFTDOWN    8 
#define GLXAPP_CONTROLDOWN  9 
#define GLXAPP_ALTDOWN     10
#define GLXAPP_COMMANDDOWN 11

const int MOUSE_LEFT_BUTTON      = 0x0001;
const int MOUSE_MIDDLE_BUTTON    = 0x0002;
const int MOUSE_RIGHT_BUTTON     = 0x0003;
const int MOUSE_DOWN             = 0x0004;
const int MOUSE_UP               = 0x0005;

const int MODIFIER_CONTROL       = 0x0004;
const int MODIFIER_LBUTTON       = 0x0001;
const int MODIFIER_MBUTTON       = 0x0002;
const int MODIFIER_RBUTTON       = 0x0003;
const int MODIFIER_SHIFT         = 0x0001;

int App::Main (int numArguments, char** arguments)
{
	AppBase::Main(numArguments, arguments);

	Initlize();

	while (!PX2_APP.IsQuit())
	{
		if (!XPending(mDisplay))
		{
			OnIdle();
			continue;
		}

		XEvent evt;
		XNextEvent(mDisplay, &evt);

		if (evt.type == ButtonPress || evt.type == ButtonRelease)
		{	
			if (evt.type == ButtonPress)
			{
				if(1 == evt.xbutton.button) 
				{
					PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_LEFT, 
						APoint((float)evt.xbutton.x, 0.0f,
						PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
				}
				else if(2 == evt.xbutton.button) 
				{
					PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_MIDDLE, 
						APoint((float)evt.xbutton.x, 0.0f,
						PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
				}
				else if(3 == evt.xbutton.button) 
				{
					PX2_INPUTMAN.GetDefaultListener()->MousePressed(MBID_RIGHT, 
						APoint((float)evt.xbutton.x, 0.0f, 
						PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
				}
			}
			else
			{
				if(1 == evt.xbutton.button) 
				{
					PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_LEFT, 
						APoint((float)evt.xbutton.x, 0.0f, 
						PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
				}
				else if(2 == evt.xbutton.button) 
				{
					PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_MIDDLE, 
						APoint((float)evt.xbutton.x, 0.0f, 
						PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
				}
				else if(3 == evt.xbutton.button) 
				{
					PX2_INPUTMAN.GetDefaultListener()->MouseReleased(MBID_RIGHT, 
						APoint((float)evt.xbutton.x, 0.0f, 
						PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
				}
			}

			continue;
		}
		if (evt.type == MotionNotify)
		{
			PX2_INPUTMAN.GetDefaultListener()->MouseMoved(APoint((float)evt.xbutton.x, 0.0f, 
				PX2_INPUTMAN.GetDefaultListener()->GetViewSize().Height-(float)evt.xbutton.y));
			continue;
		}

		if (evt.type == KeyPress || evt.type == KeyRelease)
		{
			int keysyms_per_keycode_return;
			KeySym* pKeySym = XGetKeyboardMapping(mDisplay,
				evt.xkey.keycode, 1, &keysyms_per_keycode_return);
			KeySym& keySym = *pKeySym;

			int key = (keySym & 0x00FF);

			// Quit application if the KEY_TERMINATE key is pressed.
			if (key == 0x1B)
			{
				PX2_LOG_INFO("ClientMessage 0x1B");

				XDestroyWindow(mDisplay, mWindow);
				PX2_APP.SetQuit(true);
				XFree(pKeySym);
				continue;
			}

			// Adjust for special keys that exist on the key pad and on
			// the number pad.
			if ((keySym & 0xFF00) != 0)
			{
				unsigned char ucKey = (unsigned char)key;

				if (evt.type == KeyPress)
				{
				//	PX2_INPUTMAN.GetDefaultListener()->KeyPressed(ucKey);
				}
				else
				{
				//	PX2_INPUTMAN.GetDefaultListener()->KeyReleased(ucKey);
				}
			}
			XFree(pKeySym);
			continue;
		}
		if (evt.type == ConfigureNotify)
		{
			if (AppBase::msApplication)
				AppBase::msApplication->OnSize(evt.xconfigure.width, evt.xconfigure.height);

			continue;
		}
		if (evt.type == ClientMessage
			&&  evt.xclient.data.l[0] == mPX2DeleteWindow)
		{
			XDestroyWindow(mDisplay, mWindow);
			PX2_APP.SetQuit(true);

			continue;
		}
	}

	Terminate ();

	return 0;
}
#endif
//----------------------------------------------------------------------------
bool App::OnIdle ()
{
	return AppBase::OnIdle();
}
//----------------------------------------------------------------------------
#if defined __ANDROID__ || defined __IOS__
int App::Main (int numArguments, char** arguments)
{
	return 0;
}
#endif
//----------------------------------------------------------------------------
bool App::Initlize()
{
	if (msIsInitlized)
		return true;

	AppBase::Initlize();

	PX2_APP.Initlize();

	PX2_EW.ComeIn(this);

	RenderWindow *rw = PX2_GR.GetMainWindow();
	Canvas *canvasMain = DynamicCast<Canvas>(rw->GetMainCanvas());
	PX2_APP.InitlizeDefaultEngineCanvas(canvasMain);

	// boost
	Sizef boostSize(960, 640);
    boostSize = PX2_APP.GetBoostSize();
	mWidth = (int)boostSize.Width;
	mHeight = (int)boostSize.Height;
	PX2_APP.SetPt_Size(boostSize);

	PX2_LOG_INFO("PX2_APP.SetPt_Size");

#if defined(_WIN32) || defined(WIN32)
	static char sWindowClass[] = "Phoenix3DApplicationBase";
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = MsWindowEventHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = 0;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = sWindowClass;
	wc.lpszMenuName = 0;
	RegisterClass(&wc);

	DWORD dwStyle;
	if (mAllowResize)
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	}

	// �����ض��ͻ�����С�Ĵ��ڴ�С
	RECT rect = { 0, 0, mWidth - 1, mHeight - 1 };
	AdjustWindowRect(&rect, dwStyle, FALSE);

	// ��������
	mhWnd = CreateWindow(sWindowClass, mWindowTitle.c_str(),
		dwStyle, mXPosition, mYPosition,
		rect.right - rect.left + 1, rect.bottom - rect.top + 1, 0, 0, 0, 0);

	rw->SetWindowHandle(mhWnd);
	PX2_APP.SetPt_Data(mhWnd);

	// ����
	RECT rcDesktop, rcWindow;
	GetWindowRect(GetDesktopWindow(), &rcDesktop);

	HWND hTaskBar = FindWindow(TEXT("Shell_TrayWnd"), NULL);
	if (hTaskBar != NULL)
	{
		APPBARDATA abd;

		abd.cbSize = sizeof(APPBARDATA);
		abd.hWnd = hTaskBar;

		SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
		SubtractRect(&rcDesktop, &rcDesktop, &abd.rc);
	}
	GetWindowRect(mhWnd, &rcWindow);
	int offsetX = (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
	offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
	int offsetY = (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
	offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;
	SetWindowPos(mhWnd, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	mXPosition = offsetX;
	mYPosition = offsetY; 

	PX2_APP.InitlizeRenderer();
	PX2_APP.SetInEditor(false);
	PX2_APP.SetScreenSize(boostSize);	

#elif defined(__LINUX__)

	App *app = (App*)msApplication;

	// Connect to the X server.

	int xPos = app->GetXPosition();
	int yPos = app->GetYPosition();
	unsigned int width = (unsigned int)app->GetWidth();
	unsigned int height = (unsigned int)app->GetHeight();

	const char* displayName = 0;
	Display* display = XOpenDisplay(displayName);
	mDisplay = display;
	if (!display)
	{
		PX2_LOG_ERROR("XOpenDisplay");
		return -2;
	}

#if defined (PX2_USE_OPENGL)
	
	// Make sure the X server has OpenGL GLX extensions.
	int errorBase, eventBase;
	Bool success = glXQueryExtension(mDisplay, &errorBase, &eventBase);
	assertion(success == True, "GLX extensions not found.\n");
	if (!success)
	{
		PX2_LOG_ERROR("glXQueryExtension failed.");
		return -3;
	}
#endif

	// Create an X Window with the visual information created by the renderer
	// constructor.  The visual information might not be the default, so
	// create an X colormap to use.

	Window rootWindow = RootWindow(mDisplay, XDefaultScreen(mDisplay));

#if defined (PX2_USE_OPENGL)
	int attributes[256];
	// colorFormat is ignored, create 32-bit RGBA buffer.
	int i = 0;
	attributes[i++] = GLX_RGBA;
	attributes[i++] = GLX_RED_SIZE;
	attributes[i++] = 8;
	attributes[i++] = GLX_GREEN_SIZE;
	attributes[i++] = 8;
	attributes[i++] = GLX_BLUE_SIZE;
	attributes[i++] = 8;
	attributes[i++] = GLX_ALPHA_SIZE;
	attributes[i++] = 8;
	// depthStencilFormat is ignored, create 24-8 depthstencil buffer.
	attributes[i++] = GLX_DEPTH_SIZE;
	attributes[i++] = 24;
	attributes[i++] = GLX_STENCIL_SIZE;
	attributes[i++] = 8;
	// Use double buffering.
	attributes[i++] = GLX_DOUBLEBUFFER;
	attributes[i++] = 1;
	// Request multisampling.
	int numMultisamples = 0;
	if (numMultisamples == 2 || numMultisamples == 4)
	{
		attributes[i++] = GLX_SAMPLE_BUFFERS_ARB;
		attributes[i++] = 1;
		attributes[i++] = GLX_SAMPLES_ARB;
		attributes[i++] = numMultisamples;
	}

	// The list is zero terminated.
	attributes[i] = 0;

	// Get an OpenGL-capable visual.
	XVisualInfo *x11Visual = glXChooseVisual(mDisplay, DefaultScreen(mDisplay), attributes);
	if (!x11Visual)
	{
		PX2_LOG_ERROR("Error: Unable to acquire visual\n");
	}

#else
	int iDepth = DefaultDepth(mDisplay, XDefaultScreen(mDisplay));
	XVisualInfo *x11Visual = new XVisualInfo;
	XMatchVisualInfo(mDisplay, XDefaultScreen(mDisplay), iDepth, TrueColor, x11Visual);
	if (!x11Visual)
	{
		PX2_LOG_ERROR("Error: Unable to acquire visual\n");
	}
#endif

	Colormap cMap = XCreateColormap(mDisplay, rootWindow, x11Visual->visual, AllocNone);

	// Set the event mask to include exposure (paint), button presses (mouse),
	// and key presses (keyboard).
	XSetWindowAttributes windowAttributes;
	windowAttributes.colormap = cMap;
	windowAttributes.border_pixel = 0;
	windowAttributes.event_mask =
		ButtonPressMask |
		ButtonReleaseMask |
		PointerMotionMask |
		Button1MotionMask |
		Button2MotionMask |
		Button3MotionMask |
		KeyPressMask |
		KeyReleaseMask |
		ExposureMask |
		StructureNotifyMask;

	unsigned int borderWidth = 0;
	unsigned long valueMask = CWBorderPixel | CWColormap | CWEventMask;

	PX2_LOG_INFO("Begin XCreateWindow");
	Window window = XCreateWindow(mDisplay, rootWindow, xPos, yPos, width,
		height, borderWidth, x11Visual->depth, InputOutput,
		x11Visual->visual, valueMask, &windowAttributes);
	PX2_LOG_INFO("End XCreateWindow");
	mWindow = window;

	XSizeHints hints;
	hints.flags = PPosition | PSize;
	hints.x = xPos;
	hints.y = yPos;
	hints.width = width;
	hints.height = height;
	XSetNormalHints(mDisplay, window, &hints);

	std::string title = app->GetTitle();
	Pixmap iconPixmap = None;
	XSetStandardProperties(mDisplay, window, title.c_str(),
		title.c_str(), iconPixmap, mArguments, mNumArguments, &hints);

	// Intercept the close-window event when the user selects the
	// window close button.  The event is a "client message".
	mPX2DeleteWindow = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(mDisplay, window, &mPX2DeleteWindow, 1);

	PX2_APP.SetPt_Data(mDisplay);
	PX2_APP.SetPt_Data1(&window);
	PX2_APP.SetPt_Data2(x11Visual);
	PX2_APP.SetPt_Size(Sizef(width, height));
	Renderer *renderer = PX2_APP.InitlizeRenderer();
	PX2_APP.SetScreenSize(boostSize);	
	PX2_APP.SetInEditor(false);

	XMapWindow(mDisplay, window);

#else
	PX2_APP.InitlizeRenderer();
	PX2_APP.SetScreenSize(boostSize);
	PX2_APP.SetInEditor(false);
#endif

	msIsInitlized = true;

	PX2_LOG_INFO("End App::Initlize.");

	return true;
}
//----------------------------------------------------------------------------
bool App::Terminate()
{
	PX2_EW.GoOut(this);

	bool ret = AppBase::Terminate();

#if defined(__LINUX__)
	XCloseDisplay(mDisplay);
#endif

	return ret;
}
//----------------------------------------------------------------------------
void App::OnEvent(Event *ent)
{
	if (ProjectES::IsEqual(ent, ProjectES::NewProject))
	{
		const std::string &projName = PX2_PROJ.GetName();
		SetTitle(GetTitleProj(projName));
	}
	else if (ProjectES::IsEqual(ent, ProjectES::LoadedProject))
	{
		const std::string &projName = PX2_PROJ.GetName();
		SetTitle(GetTitleProj(projName));
	}
	else if (ProjectES::IsEqual(ent, ProjectES::CloseProject))
	{
		SetTitle(GetTitleProj(""));
	}
}
//----------------------------------------------------------------------------
void App::SetTitle(const std::string &title)
{
	AppBase::SetTitle(title);

#if defined(_WIN32) || defined(WIN32)
	if (0 != mhWnd)
	{
		::SetWindowText(mhWnd, title.c_str());
	}
#elif defined (__LINUX__)
#endif
}
//----------------------------------------------------------------------------