// General_Pre.hpp

#ifndef GENERAL_PRE_HPP
#define GENERAL_PRE_HPP

#include "PX2CorePre.hpp"

#if defined(GENERAL_DLL_EXPORT)
#define GENERAL_DLL_ITEM __declspec(dllexport)
#elif defined(GENERAL_DLL_IMPORT)
#define GENERAL_DLL_ITEM __declspec(dllimport)
#else
#define GENERAL_DLL_ITEM
#endif

#endif