// PX2ProjectEvent.cpp

#include "PX2ProjectEvent.hpp"
using namespace PX2;

PX2_IMPLEMENT_EVENT(ProjectES);
std::string ProjectES::EventStrs[E_QUANTITY] =
{
	"NewProject",
	"LoadedProject",
	"SavedProject",
	"CloseProject",
	"NewScene",
	"SavedScene",
	"CloseScene",
	"NewUI",
	"CloseUI",
	"NewLP",
	"CloseLP",
	"Play",
	"Stop",
	"SceneCanvasSizeChanged",
	"UICanvasSizeChanged"
};

PX2_IMPLEMENT_EVENT(ProjectES_Internal);
std::string ProjectES_Internal::EventStrs[E_QUANTITY] =
{
	"SceneUICamerasChanged",
	"UISizeChanged"
};

