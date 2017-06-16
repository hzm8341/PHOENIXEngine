// PX2NirvanaToLua.hpp

#ifndef PX2NIRVANATOLUA_HPP
#define PX2NIRVANATOLUA_HPP

#include "PX2CorePre.hpp"
using namespace PX2;

#define PX2_LUA

#if defined (PX2_LUA)

#if (defined(_WIN32) || defined(WIN32)) && defined(_DEBUG)
#pragma warning (disable:4800)
#pragma warning (disable:4505)
#endif

struct lua_State;
extern int tolua_Nirvana_open (lua_State* tolua_S);

#endif

#endif