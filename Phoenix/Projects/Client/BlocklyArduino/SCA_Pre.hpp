// SCA_Pre.hpp

#ifndef SCA_PRE_HPP
#define SCA_PRE_HPP

#include "PX2CorePre.hpp"

#if defined(SCA_DLL_EXPORT)
#define SCA_DLL_ITEM __declspec(dllexport)
#elif defined(SCA_DLL_IMPORT)
#define SCA_DLL_ITEM __declspec(dllimport)
#else
#define SCA_DLL_ITEM
#endif

#endif