/*
** Lua binding: Nirvana
** Generated automatically by tolua++-1.0.92 on 05/26/17 18:49:39.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Nirvana_open (lua_State* tolua_S);

#include "PX2NirvanaToLua.hpp"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"EffectableController");
 tolua_usertype(tolua_S,"NirMan");
 tolua_usertype(tolua_S,"wxMenuItem");
 tolua_usertype(tolua_S,"PX2wxAuiToolBar");
 tolua_usertype(tolua_S,"wxMenu");
}

/* method: Initlize of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_Initlize00
static int tolua_Nirvana_NirMan_Initlize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Initlize'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Initlize();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Initlize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Ternamate of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_Ternamate00
static int tolua_Nirvana_NirMan_Ternamate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ternamate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Ternamate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ternamate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurMenu of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_SetCurMenu00
static int tolua_Nirvana_NirMan_SetCurMenu00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"wxMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  wxMenu* menu = ((wxMenu*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurMenu'", NULL);
#endif
  {
   self->SetCurMenu(menu);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurMenu'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurMenu of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_GetCurMenu00
static int tolua_Nirvana_NirMan_GetCurMenu00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurMenu'", NULL);
#endif
  {
   wxMenu* tolua_ret = (wxMenu*)  self->GetCurMenu();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"wxMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurMenu'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSubMenu of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddSubMenu00
static int tolua_Nirvana_NirMan_AddSubMenu00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"wxMenu",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  wxMenu* menu = ((wxMenu*)  tolua_tousertype(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSubMenu'", NULL);
#endif
  {
   wxMenu* tolua_ret = (wxMenu*)  self->AddSubMenu(menu,title);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"wxMenu");
   tolua_pushcppstring(tolua_S,(const char*)title);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSubMenu'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddMenuItem of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddMenuItem00
static int tolua_Nirvana_NirMan_AddMenuItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"wxMenu",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  wxMenu* menu = ((wxMenu*)  tolua_tousertype(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string script = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string scriptParam = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddMenuItem'", NULL);
#endif
  {
   wxMenuItem* tolua_ret = (wxMenuItem*)  self->AddMenuItem(menu,title,script,scriptParam);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"wxMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)scriptParam);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddMenuItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSeparater of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddSeparater00
static int tolua_Nirvana_NirMan_AddSeparater00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"wxMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  wxMenu* menu = ((wxMenu*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSeparater'", NULL);
#endif
  {
   self->AddSeparater(menu);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSeparater'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RefreshEffectableControllerModules of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_RefreshEffectableControllerModules00
static int tolua_Nirvana_NirMan_RefreshEffectableControllerModules00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"wxMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"EffectableController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  wxMenu* menu = ((wxMenu*)  tolua_tousertype(tolua_S,2,0));
  EffectableController* eftCtrl = ((EffectableController*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RefreshEffectableControllerModules'", NULL);
#endif
  {
   self->RefreshEffectableControllerModules(menu,eftCtrl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RefreshEffectableControllerModules'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateEffectableControllerModule of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_CreateEffectableControllerModule00
static int tolua_Nirvana_NirMan_CreateEffectableControllerModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string typeStr = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateEffectableControllerModule'", NULL);
#endif
  {
   self->CreateEffectableControllerModule(typeStr);
   tolua_pushcppstring(tolua_S,(const char*)typeStr);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateEffectableControllerModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurToolBar of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_SetCurToolBar00
static int tolua_Nirvana_NirMan_SetCurToolBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"PX2wxAuiToolBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  PX2wxAuiToolBar* toolBar = ((PX2wxAuiToolBar*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurToolBar'", NULL);
#endif
  {
   self->SetCurToolBar(toolBar);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurToolBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurToolBar of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_GetCurToolBar00
static int tolua_Nirvana_NirMan_GetCurToolBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurToolBar'", NULL);
#endif
  {
   PX2wxAuiToolBar* tolua_ret = (PX2wxAuiToolBar*)  self->GetCurToolBar();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PX2wxAuiToolBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurToolBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddTool of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddTool00
static int tolua_Nirvana_NirMan_AddTool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string icon = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string script = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddTool'", NULL);
#endif
  {
   self->AddTool(icon,script);
   tolua_pushcppstring(tolua_S,(const char*)icon);
   tolua_pushcppstring(tolua_S,(const char*)script);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddTool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddTool of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddTool01
static int tolua_Nirvana_NirMan_AddTool01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string icon = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string script = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string helpStr = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  int type = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddTool'", NULL);
#endif
  {
   self->AddTool(icon,script,helpStr,type);
   tolua_pushcppstring(tolua_S,(const char*)icon);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)helpStr);
  }
 }
 return 3;
tolua_lerror:
 return tolua_Nirvana_NirMan_AddTool00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolChoose of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolChoose00
static int tolua_Nirvana_NirMan_AddToolChoose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string script = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string choose0 = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolChoose'", NULL);
#endif
  {
   self->AddToolChoose(script,choose0);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)choose0);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddToolChoose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolChoose of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolChoose01
static int tolua_Nirvana_NirMan_AddToolChoose01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string script = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string choose0 = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string choose1 = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolChoose'", NULL);
#endif
  {
   self->AddToolChoose(script,choose0,choose1);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)choose0);
   tolua_pushcppstring(tolua_S,(const char*)choose1);
  }
 }
 return 3;
tolua_lerror:
 return tolua_Nirvana_NirMan_AddToolChoose00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolChoose of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolChoose02
static int tolua_Nirvana_NirMan_AddToolChoose02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string script = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string choose0 = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string choose1 = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string choose2 = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolChoose'", NULL);
#endif
  {
   self->AddToolChoose(script,choose0,choose1,choose2);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)choose0);
   tolua_pushcppstring(tolua_S,(const char*)choose1);
   tolua_pushcppstring(tolua_S,(const char*)choose2);
  }
 }
 return 4;
tolua_lerror:
 return tolua_Nirvana_NirMan_AddToolChoose01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolChoose of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolChoose03
static int tolua_Nirvana_NirMan_AddToolChoose03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string script = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string choose0 = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string choose1 = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string choose2 = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string choose3 = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolChoose'", NULL);
#endif
  {
   self->AddToolChoose(script,choose0,choose1,choose2,choose3);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)choose0);
   tolua_pushcppstring(tolua_S,(const char*)choose1);
   tolua_pushcppstring(tolua_S,(const char*)choose2);
   tolua_pushcppstring(tolua_S,(const char*)choose3);
  }
 }
 return 5;
tolua_lerror:
 return tolua_Nirvana_NirMan_AddToolChoose02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolChoose of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolChoose04
static int tolua_Nirvana_NirMan_AddToolChoose04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string script = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string choose0 = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string choose1 = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string choose2 = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string choose3 = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  const std::string choose4 = ((const std::string)  tolua_tocppstring(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolChoose'", NULL);
#endif
  {
   self->AddToolChoose(script,choose0,choose1,choose2,choose3,choose4);
   tolua_pushcppstring(tolua_S,(const char*)script);
   tolua_pushcppstring(tolua_S,(const char*)choose0);
   tolua_pushcppstring(tolua_S,(const char*)choose1);
   tolua_pushcppstring(tolua_S,(const char*)choose2);
   tolua_pushcppstring(tolua_S,(const char*)choose3);
   tolua_pushcppstring(tolua_S,(const char*)choose4);
  }
 }
 return 6;
tolua_lerror:
 return tolua_Nirvana_NirMan_AddToolChoose03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolSeparater of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolSeparater00
static int tolua_Nirvana_NirMan_AddToolSeparater00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolSeparater'", NULL);
#endif
  {
   self->AddToolSeparater();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddToolSeparater'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddToolStretch of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_AddToolStretch00
static int tolua_Nirvana_NirMan_AddToolStretch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddToolStretch'", NULL);
#endif
  {
   self->AddToolStretch();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddToolStretch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MessageBox of class  NirMan */
#ifndef TOLUA_DISABLE_tolua_Nirvana_NirMan_MessageBox00
static int tolua_Nirvana_NirMan_MessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NirMan",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NirMan* self = (NirMan*)  tolua_tousertype(tolua_S,1,0);
  const std::string caption = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string content = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  int type = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MessageBox'", NULL);
#endif
  {
   int tolua_ret = (int)  self->MessageBox(caption,content,type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)caption);
   tolua_pushcppstring(tolua_S,(const char*)content);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Nirvana_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"NirMan","NirMan","",NULL);
  tolua_beginmodule(tolua_S,"NirMan");
   tolua_function(tolua_S,"Initlize",tolua_Nirvana_NirMan_Initlize00);
   tolua_function(tolua_S,"Ternamate",tolua_Nirvana_NirMan_Ternamate00);
   tolua_function(tolua_S,"SetCurMenu",tolua_Nirvana_NirMan_SetCurMenu00);
   tolua_function(tolua_S,"GetCurMenu",tolua_Nirvana_NirMan_GetCurMenu00);
   tolua_function(tolua_S,"AddSubMenu",tolua_Nirvana_NirMan_AddSubMenu00);
   tolua_function(tolua_S,"AddMenuItem",tolua_Nirvana_NirMan_AddMenuItem00);
   tolua_function(tolua_S,"AddSeparater",tolua_Nirvana_NirMan_AddSeparater00);
   tolua_function(tolua_S,"RefreshEffectableControllerModules",tolua_Nirvana_NirMan_RefreshEffectableControllerModules00);
   tolua_function(tolua_S,"CreateEffectableControllerModule",tolua_Nirvana_NirMan_CreateEffectableControllerModule00);
   tolua_function(tolua_S,"SetCurToolBar",tolua_Nirvana_NirMan_SetCurToolBar00);
   tolua_function(tolua_S,"GetCurToolBar",tolua_Nirvana_NirMan_GetCurToolBar00);
   tolua_function(tolua_S,"AddTool",tolua_Nirvana_NirMan_AddTool00);
   tolua_function(tolua_S,"AddTool",tolua_Nirvana_NirMan_AddTool01);
   tolua_function(tolua_S,"AddToolChoose",tolua_Nirvana_NirMan_AddToolChoose00);
   tolua_function(tolua_S,"AddToolChoose",tolua_Nirvana_NirMan_AddToolChoose01);
   tolua_function(tolua_S,"AddToolChoose",tolua_Nirvana_NirMan_AddToolChoose02);
   tolua_function(tolua_S,"AddToolChoose",tolua_Nirvana_NirMan_AddToolChoose03);
   tolua_function(tolua_S,"AddToolChoose",tolua_Nirvana_NirMan_AddToolChoose04);
   tolua_function(tolua_S,"AddToolSeparater",tolua_Nirvana_NirMan_AddToolSeparater00);
   tolua_function(tolua_S,"AddToolStretch",tolua_Nirvana_NirMan_AddToolStretch00);
   tolua_function(tolua_S,"MessageBox",tolua_Nirvana_NirMan_MessageBox00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
  int luaopen_Nirvana (lua_State* tolua_S) {
 return tolua_Nirvana_open(tolua_S);
};
#endif

