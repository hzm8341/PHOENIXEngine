// Slam2DPlugin_Pre.hpp

#ifndef SLAM2DPLUGIN_PRE_HPP
#define SLAM2DPLUGIN_PRE_HPP

#include "PX2CorePre.hpp"

#define SLAM2D_DLL_EXPORT
#if defined(SLAM2D_DLL_EXPORT)
#define SLAM2D_DLL_ITEM __declspec(dllexport)
#elif defined(SLAM2D_DLL_IMPORT)
#define SLAM2D_DLL_ITEM __declspec(dllimport)
#else
#define SLAM2D_DLL_ITEM
#endif

#endif