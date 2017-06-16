/*
** Lua binding: BBlocks
** Generated automatically by tolua++-1.0.92 on 05/04/17 18:54:44.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_BBlocks_open (lua_State* tolua_S);

#include "PX2BBlueBlockToLua.hpp"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_UIBBlockCataFrame (lua_State* tolua_S)
{
 UIBBlockCataFrame* self = (UIBBlockCataFrame*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIBBlockEdit (lua_State* tolua_S)
{
 UIBBlockEdit* self = (UIBBlockEdit*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIBBlockPanels (lua_State* tolua_S)
{
 UIBBlockPanels* self = (UIBBlockPanels*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIBBlockEditToolFrame (lua_State* tolua_S)
{
 UIBBlockEditToolFrame* self = (UIBBlockEditToolFrame*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_BBlockSprite (lua_State* tolua_S)
{
 BBlockSprite* self = (BBlockSprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_BBlockScriptGenController (lua_State* tolua_S)
{
 BBlockScriptGenController* self = (BBlockScriptGenController*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"UIBBlockCataFrame");
 tolua_usertype(tolua_S,"BBlockSystem");
 tolua_usertype(tolua_S,"Controller");
 tolua_usertype(tolua_S,"UIButton");
 tolua_usertype(tolua_S,"BBlockSprite");
 tolua_usertype(tolua_S,"LFile");
 tolua_usertype(tolua_S,"UIBBlockEdit");
 tolua_usertype(tolua_S,"UIBBlockPanels");
 tolua_usertype(tolua_S,"UIBBlockEditToolFrame");
 tolua_usertype(tolua_S,"UIFrame");
 tolua_usertype(tolua_S,"BBlockScriptGenController");
}

/* method: new of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_new00
static int tolua_BBlocks_UIBBlockCataFrame_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockCataFrame* tolua_ret = (UIBBlockCataFrame*)  Mtolua_new((UIBBlockCataFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockCataFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_new00_local
static int tolua_BBlocks_UIBBlockCataFrame_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockCataFrame* tolua_ret = (UIBBlockCataFrame*)  Mtolua_new((UIBBlockCataFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockCataFrame");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_delete00
static int tolua_BBlocks_UIBBlockCataFrame_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockCataFrame* self = (UIBBlockCataFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_New00
static int tolua_BBlocks_UIBBlockCataFrame_New00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockCataFrame* tolua_ret = (UIBBlockCataFrame*)  UIBBlockCataFrame::New();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockCataFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'New'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_New01
static int tolua_BBlocks_UIBBlockCataFrame_New01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   UIBBlockCataFrame* tolua_ret = (UIBBlockCataFrame*)  UIBBlockCataFrame::New(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockCataFrame");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_UIBBlockCataFrame_New00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCataType of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_SetCataType00
static int tolua_BBlocks_UIBBlockCataFrame_SetCataType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockCataFrame* self = (UIBBlockCataFrame*)  tolua_tousertype(tolua_S,1,0);
  UIBBlockCataFrame::CataType cataType = ((UIBBlockCataFrame::CataType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCataType'", NULL);
#endif
  {
   self->SetCataType(cataType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCataType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCataType of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_GetCataType00
static int tolua_BBlocks_UIBBlockCataFrame_GetCataType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIBBlockCataFrame* self = (const UIBBlockCataFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCataType'", NULL);
#endif
  {
   UIBBlockCataFrame::CataType tolua_ret = (UIBBlockCataFrame::CataType)  self->GetCataType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCataType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateCataButs of class  UIBBlockCataFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockCataFrame_CreateCataButs00
static int tolua_BBlocks_UIBBlockCataFrame_CreateCataButs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockCataFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockCataFrame* self = (UIBBlockCataFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateCataButs'", NULL);
#endif
  {
   self->CreateCataButs();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateCataButs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIBBlockPanels */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockPanels_new00
static int tolua_BBlocks_UIBBlockPanels_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockPanels",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockPanels* tolua_ret = (UIBBlockPanels*)  Mtolua_new((UIBBlockPanels)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockPanels");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIBBlockPanels */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockPanels_new00_local
static int tolua_BBlocks_UIBBlockPanels_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockPanels",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockPanels* tolua_ret = (UIBBlockPanels*)  Mtolua_new((UIBBlockPanels)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockPanels");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIBBlockPanels */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockPanels_delete00
static int tolua_BBlocks_UIBBlockPanels_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockPanels",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockPanels* self = (UIBBlockPanels*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockPanels */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockPanels_New00
static int tolua_BBlocks_UIBBlockPanels_New00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockPanels",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockPanels* tolua_ret = (UIBBlockPanels*)  UIBBlockPanels::New();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockPanels");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'New'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockPanels */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockPanels_New01
static int tolua_BBlocks_UIBBlockPanels_New01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockPanels",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   UIBBlockPanels* tolua_ret = (UIBBlockPanels*)  UIBBlockPanels::New(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockPanels");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_UIBBlockPanels_New00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowPanel of class  UIBBlockPanels */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockPanels_ShowPanel00
static int tolua_BBlocks_UIBBlockPanels_ShowPanel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockPanels",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockPanels* self = (UIBBlockPanels*)  tolua_tousertype(tolua_S,1,0);
  const std::string panelName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowPanel'", NULL);
#endif
  {
   self->ShowPanel(panelName);
   tolua_pushcppstring(tolua_S,(const char*)panelName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowPanel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIBBlockEdit */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEdit_new00
static int tolua_BBlocks_UIBBlockEdit_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockEdit* tolua_ret = (UIBBlockEdit*)  Mtolua_new((UIBBlockEdit)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIBBlockEdit */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEdit_new00_local
static int tolua_BBlocks_UIBBlockEdit_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockEdit* tolua_ret = (UIBBlockEdit*)  Mtolua_new((UIBBlockEdit)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEdit");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIBBlockEdit */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEdit_delete00
static int tolua_BBlocks_UIBBlockEdit_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockEdit* self = (UIBBlockEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockEdit */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEdit_New00
static int tolua_BBlocks_UIBBlockEdit_New00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockEdit* tolua_ret = (UIBBlockEdit*)  UIBBlockEdit::New();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'New'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockEdit */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEdit_New01
static int tolua_BBlocks_UIBBlockEdit_New01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEdit",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   UIBBlockEdit* tolua_ret = (UIBBlockEdit*)  UIBBlockEdit::New(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEdit");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_UIBBlockEdit_New00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_new00
static int tolua_BBlocks_UIBBlockEditToolFrame_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockEditToolFrame* tolua_ret = (UIBBlockEditToolFrame*)  Mtolua_new((UIBBlockEditToolFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEditToolFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_new00_local
static int tolua_BBlocks_UIBBlockEditToolFrame_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockEditToolFrame* tolua_ret = (UIBBlockEditToolFrame*)  Mtolua_new((UIBBlockEditToolFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEditToolFrame");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_delete00
static int tolua_BBlocks_UIBBlockEditToolFrame_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockEditToolFrame* self = (UIBBlockEditToolFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_New00
static int tolua_BBlocks_UIBBlockEditToolFrame_New00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBBlockEditToolFrame* tolua_ret = (UIBBlockEditToolFrame*)  UIBBlockEditToolFrame::New();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEditToolFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'New'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_New01
static int tolua_BBlocks_UIBBlockEditToolFrame_New01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   UIBBlockEditToolFrame* tolua_ret = (UIBBlockEditToolFrame*)  UIBBlockEditToolFrame::New(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBBlockEditToolFrame");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_UIBBlockEditToolFrame_New00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetButtonRecycle of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_GetButtonRecycle00
static int tolua_BBlocks_UIBBlockEditToolFrame_GetButtonRecycle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockEditToolFrame* self = (UIBBlockEditToolFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetButtonRecycle'", NULL);
#endif
  {
   UIButton* tolua_ret = (UIButton*)  self->GetButtonRecycle();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetButtonRecycle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_new00
static int tolua_BBlocks_BBlockScriptGenController_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBlockScriptGenController* tolua_ret = (BBlockScriptGenController*)  Mtolua_new((BBlockScriptGenController)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockScriptGenController");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_new00_local
static int tolua_BBlocks_BBlockScriptGenController_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBlockScriptGenController* tolua_ret = (BBlockScriptGenController*)  Mtolua_new((BBlockScriptGenController)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockScriptGenController");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_delete00
static int tolua_BBlocks_BBlockScriptGenController_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockScriptGenController* self = (BBlockScriptGenController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_New00
static int tolua_BBlocks_BBlockScriptGenController_New00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBlockScriptGenController* tolua_ret = (BBlockScriptGenController*)  BBlockScriptGenController::New();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockScriptGenController");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'New'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_New01
static int tolua_BBlocks_BBlockScriptGenController_New01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   BBlockScriptGenController* tolua_ret = (BBlockScriptGenController*)  BBlockScriptGenController::New(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockScriptGenController");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_BBlockScriptGenController_New00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_SetName00
static int tolua_BBlocks_BBlockScriptGenController_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockScriptGenController* self = (BBlockScriptGenController*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGenerateType of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_SetGenerateType00
static int tolua_BBlocks_BBlockScriptGenController_SetGenerateType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockScriptGenController* self = (BBlockScriptGenController*)  tolua_tousertype(tolua_S,1,0);
  BBlockScriptGenController::GenerateType at = ((BBlockScriptGenController::GenerateType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGenerateType'", NULL);
#endif
  {
   self->SetGenerateType(at);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGenerateType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGenerateType of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_GetGenerateType00
static int tolua_BBlocks_BBlockScriptGenController_GetGenerateType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockScriptGenController* self = (const BBlockScriptGenController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGenerateType'", NULL);
#endif
  {
   BBlockScriptGenController::GenerateType tolua_ret = (BBlockScriptGenController::GenerateType)  self->GetGenerateType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGenerateType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLFile of class  BBlockScriptGenController */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockScriptGenController_GetLFile00
static int tolua_BBlocks_BBlockScriptGenController_GetLFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockScriptGenController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockScriptGenController* self = (BBlockScriptGenController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLFile'", NULL);
#endif
  {
   LFile* tolua_ret = (LFile*)  self->GetLFile();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LFile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_new00
static int tolua_BBlocks_BBlockSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite::SpriteType st = ((BBlockSprite::SpriteType) (int)  tolua_tonumber(tolua_S,2,BBlockSprite::ST_PICBOX));
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  Mtolua_new((BBlockSprite)(st));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_new00_local
static int tolua_BBlocks_BBlockSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite::SpriteType st = ((BBlockSprite::SpriteType) (int)  tolua_tonumber(tolua_S,2,BBlockSprite::ST_PICBOX));
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  Mtolua_new((BBlockSprite)(st));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_delete00
static int tolua_BBlocks_BBlockSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_New00
static int tolua_BBlocks_BBlockSprite_New00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  BBlockSprite::New();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'New'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_New01
static int tolua_BBlocks_BBlockSprite_New01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  BBlockSprite::New(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_BBlockSprite_New00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: New of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_New02
static int tolua_BBlocks_BBlockSprite_New02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BBlockSprite::SpriteType st = ((BBlockSprite::SpriteType) (int)  tolua_tonumber(tolua_S,2,0));
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  BBlockSprite::New(st);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_BBlocks_BBlockSprite_New01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpriteType of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetSpriteType00
static int tolua_BBlocks_BBlockSprite_GetSpriteType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpriteType'", NULL);
#endif
  {
   BBlockSprite::SpriteType tolua_ret = (BBlockSprite::SpriteType)  self->GetSpriteType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpriteType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetName00
static int tolua_BBlocks_BBlockSprite_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScriptGenController of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetScriptGenController00
static int tolua_BBlocks_BBlockSprite_GetScriptGenController00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScriptGenController'", NULL);
#endif
  {
   BBlockScriptGenController* tolua_ret = (BBlockScriptGenController*)  self->GetScriptGenController();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockScriptGenController");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScriptGenController'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setName00
static int tolua_BBlocks_BBlockSprite_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getName00
static int tolua_BBlocks_BBlockSprite_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachChild of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_attachChild00
static int tolua_BBlocks_BBlockSprite_attachChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  BBlockSprite* sprite = ((BBlockSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachChild'", NULL);
#endif
  {
   self->attachChild(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detachChild of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_detachChild00
static int tolua_BBlocks_BBlockSprite_detachChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  BBlockSprite* sprite = ((BBlockSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detachChild'", NULL);
#endif
  {
   self->detachChild(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detachChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detachChildByName of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_detachChildByName00
static int tolua_BBlocks_BBlockSprite_detachChildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detachChildByName'", NULL);
#endif
  {
   self->detachChildByName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detachChildByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_show00
static int tolua_BBlocks_BBlockSprite_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'", NULL);
#endif
  {
   self->show(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isShow of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_isShow00
static int tolua_BBlocks_BBlockSprite_isShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShow'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isShow();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setText00
static int tolua_BBlocks_BBlockSprite_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getText of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getText00
static int tolua_BBlocks_BBlockSprite_getText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getText'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getText();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setScale00
static int tolua_BBlocks_BBlockSprite_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale'", NULL);
#endif
  {
   self->setScale(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScale of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getScale00
static int tolua_BBlocks_BBlockSprite_getScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleXZ of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setScaleXZ00
static int tolua_BBlocks_BBlockSprite_setScaleXZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float scaleX = ((float)  tolua_tonumber(tolua_S,2,0));
  float scaleZ = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleXZ'", NULL);
#endif
  {
   self->setScaleXZ(scaleX,scaleZ);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleXZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleX of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setScaleX00
static int tolua_BBlocks_BBlockSprite_setScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleX'", NULL);
#endif
  {
   self->setScaleX(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleZ of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setScaleZ00
static int tolua_BBlocks_BBlockSprite_setScaleZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleZ'", NULL);
#endif
  {
   self->setScaleZ(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleX of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getScaleX00
static int tolua_BBlocks_BBlockSprite_getScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleZ of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getScaleZ00
static int tolua_BBlocks_BBlockSprite_getScaleZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleZ'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addScale of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_addScale00
static int tolua_BBlocks_BBlockSprite_addScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addScale'", NULL);
#endif
  {
   self->addScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotateXYZ of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setRotateXYZ00
static int tolua_BBlocks_BBlockSprite_setRotateXYZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotateXYZ'", NULL);
#endif
  {
   self->setRotateXYZ(x,y,z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotateXYZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotateX of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setRotateX00
static int tolua_BBlocks_BBlockSprite_setRotateX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float degree = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotateX'", NULL);
#endif
  {
   self->setRotateX(degree);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotateX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotateY of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setRotateY00
static int tolua_BBlocks_BBlockSprite_setRotateY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float degree = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotateY'", NULL);
#endif
  {
   self->setRotateY(degree);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotateY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotateZ of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setRotateZ00
static int tolua_BBlocks_BBlockSprite_setRotateZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float degree = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotateZ'", NULL);
#endif
  {
   self->setRotateZ(degree);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotateZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotateX of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getRotateX00
static int tolua_BBlocks_BBlockSprite_getRotateX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotateX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotateX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotateX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotateY of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getRotateY00
static int tolua_BBlocks_BBlockSprite_getRotateY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotateY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotateY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotateY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotateZ of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getRotateZ00
static int tolua_BBlocks_BBlockSprite_getRotateZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotateZ'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotateZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotateZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addRotate of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_addRotate00
static int tolua_BBlocks_BBlockSprite_addRotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float degree = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addRotate'", NULL);
#endif
  {
   self->addRotate(degree);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addRotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayout of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setLayout00
static int tolua_BBlocks_BBlockSprite_setLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,14,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float horA = ((float)  tolua_tonumber(tolua_S,2,0));
  float horB = ((float)  tolua_tonumber(tolua_S,3,0));
  float horParamA = ((float)  tolua_tonumber(tolua_S,4,0));
  float horParamB = ((float)  tolua_tonumber(tolua_S,5,0));
  float verA = ((float)  tolua_tonumber(tolua_S,6,0));
  float verB = ((float)  tolua_tonumber(tolua_S,7,0));
  float verParamA = ((float)  tolua_tonumber(tolua_S,8,0));
  float verParamB = ((float)  tolua_tonumber(tolua_S,9,0));
  float pivotX = ((float)  tolua_tonumber(tolua_S,10,0));
  float pivotY = ((float)  tolua_tonumber(tolua_S,11,0));
  float width = ((float)  tolua_tonumber(tolua_S,12,0));
  float height = ((float)  tolua_tonumber(tolua_S,13,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayout'", NULL);
#endif
  {
   self->setLayout(horA,horB,horParamA,horParamB,verA,verB,verParamA,verParamB,pivotX,pivotY,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPostion of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setPostion00
static int tolua_BBlocks_BBlockSprite_setPostion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float posX = ((float)  tolua_tonumber(tolua_S,2,0));
  float posZ = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPostion'", NULL);
#endif
  {
   self->setPostion(posX,posZ);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPostion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorHor of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setAnchorHor00
static int tolua_BBlocks_BBlockSprite_setAnchorHor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float valA = ((float)  tolua_tonumber(tolua_S,2,0));
  float valB = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorHor'", NULL);
#endif
  {
   self->setAnchorHor(valA,valB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorHor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorParamHor of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setAnchorParamHor00
static int tolua_BBlocks_BBlockSprite_setAnchorParamHor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float valA = ((float)  tolua_tonumber(tolua_S,2,0));
  float valB = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorParamHor'", NULL);
#endif
  {
   self->setAnchorParamHor(valA,valB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorParamHor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorVer of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setAnchorVer00
static int tolua_BBlocks_BBlockSprite_setAnchorVer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float valA = ((float)  tolua_tonumber(tolua_S,2,0));
  float valB = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorVer'", NULL);
#endif
  {
   self->setAnchorVer(valA,valB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorVer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorParamVer of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setAnchorParamVer00
static int tolua_BBlocks_BBlockSprite_setAnchorParamVer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float valA = ((float)  tolua_tonumber(tolua_S,2,0));
  float valB = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorParamVer'", NULL);
#endif
  {
   self->setAnchorParamVer(valA,valB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorParamVer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: move of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_move00
static int tolua_BBlocks_BBlockSprite_move00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float moveX = ((float)  tolua_tonumber(tolua_S,2,0));
  float moveZ = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'move'", NULL);
#endif
  {
   self->move(moveX,moveZ);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'move'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayer of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setLayer00
static int tolua_BBlocks_BBlockSprite_setLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  int layer = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayer'", NULL);
#endif
  {
   self->setLayer(layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayer of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getLayer00
static int tolua_BBlocks_BBlockSprite_getLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPivot of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setPivot00
static int tolua_BBlocks_BBlockSprite_setPivot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float pivotX = ((float)  tolua_tonumber(tolua_S,2,0));
  float pivotY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPivot'", NULL);
#endif
  {
   self->setPivot(pivotX,pivotY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPivot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setSize00
static int tolua_BBlocks_BBlockSprite_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'", NULL);
#endif
  {
   self->setSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSizeWidthHeight of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setSizeWidthHeight00
static int tolua_BBlocks_BBlockSprite_setSizeWidthHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSizeWidthHeight'", NULL);
#endif
  {
   self->setSizeWidthHeight(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSizeWidthHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingDirX of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getDragingDirX00
static int tolua_BBlocks_BBlockSprite_getDragingDirX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingDirX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDragingDirX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingDirX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingDirY of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getDragingDirY00
static int tolua_BBlocks_BBlockSprite_getDragingDirY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingDirY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDragingDirY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingDirY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingDirSimple of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getDragingDirSimple00
static int tolua_BBlocks_BBlockSprite_getDragingDirSimple00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingDirSimple'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDragingDirSimple();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingDirSimple'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingPercent of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getDragingPercent00
static int tolua_BBlocks_BBlockSprite_getDragingPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSprite* self = (const BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingPercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDragingPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChooseString of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_addChooseString00
static int tolua_BBlocks_BBlockSprite_addChooseString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChooseString'", NULL);
#endif
  {
   self->addChooseString(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChooseString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: chooseString of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_chooseString00
static int tolua_BBlocks_BBlockSprite_chooseString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'chooseString'", NULL);
#endif
  {
   self->chooseString(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'chooseString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: chooseIndex of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_chooseIndex00
static int tolua_BBlocks_BBlockSprite_chooseIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'chooseIndex'", NULL);
#endif
  {
   self->chooseIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'chooseIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChooseString of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getChooseString00
static int tolua_BBlocks_BBlockSprite_getChooseString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChooseString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getChooseString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChooseString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChooseIndex of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getChooseIndex00
static int tolua_BBlocks_BBlockSprite_getChooseIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChooseIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getChooseIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChooseIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setURL of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setURL00
static int tolua_BBlocks_BBlockSprite_setURL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string url = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setURL'", NULL);
#endif
  {
   self->setURL(url);
   tolua_pushcppstring(tolua_S,(const char*)url);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setURL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteFrame of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteFrame00
static int tolua_BBlocks_BBlockSystem_createSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteFrame'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteFrame();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpritePicBox of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpritePicBox00
static int tolua_BBlocks_BBlockSystem_createSpritePicBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpritePicBox'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpritePicBox();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpritePicBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteButton of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteButton00
static int tolua_BBlocks_BBlockSystem_createSpriteButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteButton'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteButton();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteText of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteText00
static int tolua_BBlocks_BBlockSystem_createSpriteText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteText'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteText();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteEditBox of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteEditBox00
static int tolua_BBlocks_BBlockSystem_createSpriteEditBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteEditBox'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteEditBox();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteEditBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteComboBox of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteComboBox00
static int tolua_BBlocks_BBlockSystem_createSpriteComboBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteComboBox'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteComboBox();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteComboBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteWebView of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteWebView00
static int tolua_BBlocks_BBlockSystem_createSpriteWebView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteWebView'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteWebView();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteWebView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSpriteRound of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_createSpriteRound00
static int tolua_BBlocks_BBlockSystem_createSpriteRound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSpriteRound'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->createSpriteRound();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSpriteRound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastCreateSprite of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getLastCreateSprite00
static int tolua_BBlocks_BBlockSystem_getLastCreateSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastCreateSprite'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->getLastCreateSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastCreateSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSpriteOfName of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getSpriteOfName00
static int tolua_BBlocks_BBlockSystem_getSpriteOfName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSpriteOfName'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->getSpriteOfName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSpriteOfName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: log of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_log00
static int tolua_BBlocks_BBlockSystem_log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'log'", NULL);
#endif
  {
   self->log(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playMusic of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_playMusic00
static int tolua_BBlocks_BBlockSystem_playMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playMusic'", NULL);
#endif
  {
   self->playMusic(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopMusic of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_stopMusic00
static int tolua_BBlocks_BBlockSystem_stopMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopMusic'", NULL);
#endif
  {
   self->stopMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stringToInt of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_stringToInt00
static int tolua_BBlocks_BBlockSystem_stringToInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stringToInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->stringToInt(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stringToInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stringToFloat of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_stringToFloat00
static int tolua_BBlocks_BBlockSystem_stringToFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stringToFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->stringToFloat(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stringToFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intToString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_intToString00
static int tolua_BBlocks_BBlockSystem_intToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intToString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->intToString(val);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: floatToString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_floatToString00
static int tolua_BBlocks_BBlockSystem_floatToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'floatToString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->floatToString(val);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'floatToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringParam of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getStringParam00
static int tolua_BBlocks_BBlockSystem_getStringParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string paramStr = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringParam'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getStringParam(paramStr,index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)paramStr);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendEvent of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_sendEvent00
static int tolua_BBlocks_BBlockSystem_sendEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendEvent'", NULL);
#endif
  {
   self->sendEvent(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEventObjectName of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getEventObjectName00
static int tolua_BBlocks_BBlockSystem_getEventObjectName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSystem* self = (const BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEventObjectName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getEventObjectName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEventObjectName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEventDataInt of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getEventDataInt00
static int tolua_BBlocks_BBlockSystem_getEventDataInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSystem* self = (const BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEventDataInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getEventDataInt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEventDataInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEventDataString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getEventDataString00
static int tolua_BBlocks_BBlockSystem_getEventDataString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSystem* self = (const BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEventDataString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getEventDataString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEventDataString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: netCreateServer of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_netCreateServer00
static int tolua_BBlocks_BBlockSystem_netCreateServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int port = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'netCreateServer'", NULL);
#endif
  {
   self->netCreateServer(port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'netCreateServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: netServerSendString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_netServerSendString00
static int tolua_BBlocks_BBlockSystem_netServerSendString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int clientID = ((int)  tolua_tonumber(tolua_S,2,0));
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'netServerSendString'", NULL);
#endif
  {
   self->netServerSendString(clientID,str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'netServerSendString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: netCreateClientConnector of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_netCreateClientConnector00
static int tolua_BBlocks_BBlockSystem_netCreateClientConnector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'netCreateClientConnector'", NULL);
#endif
  {
   self->netCreateClientConnector();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'netCreateClientConnector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: netClientSendString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_netClientSendString00
static int tolua_BBlocks_BBlockSystem_netClientSendString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'netClientSendString'", NULL);
#endif
  {
   self->netClientSendString(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'netClientSendString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bluetoothSendString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_bluetoothSendString00
static int tolua_BBlocks_BBlockSystem_bluetoothSendString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bluetoothSendString'", NULL);
#endif
  {
   self->bluetoothSendString(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bluetoothSendString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serialOpen of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_serialOpen00
static int tolua_BBlocks_BBlockSystem_serialOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string portStr = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int baudrate = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serialOpen'", NULL);
#endif
  {
   self->serialOpen(portStr,baudrate);
   tolua_pushcppstring(tolua_S,(const char*)portStr);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serialOpen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serialClose of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_serialClose00
static int tolua_BBlocks_BBlockSystem_serialClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serialClose'", NULL);
#endif
  {
   self->serialClose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serialClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serialSend of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_serialSend00
static int tolua_BBlocks_BBlockSystem_serialSend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serialSend'", NULL);
#endif
  {
   self->serialSend(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serialSend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: voiceStart of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_voiceStart00
static int tolua_BBlocks_BBlockSystem_voiceStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'voiceStart'", NULL);
#endif
  {
   self->voiceStart();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'voiceStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: voiceEnd of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_voiceEnd00
static int tolua_BBlocks_BBlockSystem_voiceEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'voiceEnd'", NULL);
#endif
  {
   self->voiceEnd();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'voiceEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_BBlocks_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIBBlockCataFrame","UIBBlockCataFrame","UIFrame",tolua_collect_UIBBlockCataFrame);
  #else
  tolua_cclass(tolua_S,"UIBBlockCataFrame","UIBBlockCataFrame","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIBBlockCataFrame");
   tolua_function(tolua_S,"new",tolua_BBlocks_UIBBlockCataFrame_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_UIBBlockCataFrame_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_UIBBlockCataFrame_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_UIBBlockCataFrame_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockCataFrame_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockCataFrame_New01);
   tolua_constant(tolua_S,"CT_NORMAL",UIBBlockCataFrame::CT_NORMAL);
   tolua_constant(tolua_S,"CT_VER",UIBBlockCataFrame::CT_VER);
   tolua_constant(tolua_S,"CT_MAX_TYPE",UIBBlockCataFrame::CT_MAX_TYPE);
   tolua_function(tolua_S,"SetCataType",tolua_BBlocks_UIBBlockCataFrame_SetCataType00);
   tolua_function(tolua_S,"GetCataType",tolua_BBlocks_UIBBlockCataFrame_GetCataType00);
   tolua_function(tolua_S,"CreateCataButs",tolua_BBlocks_UIBBlockCataFrame_CreateCataButs00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIBBlockPanels","UIBBlockPanels","UIFrame",tolua_collect_UIBBlockPanels);
  #else
  tolua_cclass(tolua_S,"UIBBlockPanels","UIBBlockPanels","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIBBlockPanels");
   tolua_function(tolua_S,"new",tolua_BBlocks_UIBBlockPanels_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_UIBBlockPanels_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_UIBBlockPanels_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_UIBBlockPanels_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockPanels_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockPanels_New01);
   tolua_function(tolua_S,"ShowPanel",tolua_BBlocks_UIBBlockPanels_ShowPanel00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIBBlockEdit","UIBBlockEdit","UIFrame",tolua_collect_UIBBlockEdit);
  #else
  tolua_cclass(tolua_S,"UIBBlockEdit","UIBBlockEdit","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIBBlockEdit");
   tolua_function(tolua_S,"new",tolua_BBlocks_UIBBlockEdit_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_UIBBlockEdit_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_UIBBlockEdit_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_UIBBlockEdit_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockEdit_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockEdit_New01);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIBBlockEditToolFrame","UIBBlockEditToolFrame","UIFrame",tolua_collect_UIBBlockEditToolFrame);
  #else
  tolua_cclass(tolua_S,"UIBBlockEditToolFrame","UIBBlockEditToolFrame","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIBBlockEditToolFrame");
   tolua_function(tolua_S,"new",tolua_BBlocks_UIBBlockEditToolFrame_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_UIBBlockEditToolFrame_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_UIBBlockEditToolFrame_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_UIBBlockEditToolFrame_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockEditToolFrame_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_UIBBlockEditToolFrame_New01);
   tolua_function(tolua_S,"GetButtonRecycle",tolua_BBlocks_UIBBlockEditToolFrame_GetButtonRecycle00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BBlockScriptGenController","BBlockScriptGenController","Controller",tolua_collect_BBlockScriptGenController);
  #else
  tolua_cclass(tolua_S,"BBlockScriptGenController","BBlockScriptGenController","Controller",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BBlockScriptGenController");
   tolua_function(tolua_S,"new",tolua_BBlocks_BBlockScriptGenController_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_BBlockScriptGenController_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_BBlockScriptGenController_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_BBlockScriptGenController_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockScriptGenController_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockScriptGenController_New01);
   tolua_function(tolua_S,"SetName",tolua_BBlocks_BBlockScriptGenController_SetName00);
   tolua_constant(tolua_S,"GT_ENGINE",BBlockScriptGenController::GT_ENGINE);
   tolua_constant(tolua_S,"GT_ARDUINO",BBlockScriptGenController::GT_ARDUINO);
   tolua_constant(tolua_S,"GT_NODEMCU",BBlockScriptGenController::GT_NODEMCU);
   tolua_constant(tolua_S,"GT_RASPBERRY",BBlockScriptGenController::GT_RASPBERRY);
   tolua_constant(tolua_S,"GT_MAX_TYPE",BBlockScriptGenController::GT_MAX_TYPE);
   tolua_function(tolua_S,"SetGenerateType",tolua_BBlocks_BBlockScriptGenController_SetGenerateType00);
   tolua_function(tolua_S,"GetGenerateType",tolua_BBlocks_BBlockScriptGenController_GetGenerateType00);
   tolua_function(tolua_S,"GetLFile",tolua_BBlocks_BBlockScriptGenController_GetLFile00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BBlockSprite","BBlockSprite","UIFrame",tolua_collect_BBlockSprite);
  #else
  tolua_cclass(tolua_S,"BBlockSprite","BBlockSprite","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BBlockSprite");
   tolua_constant(tolua_S,"ST_FRAME",BBlockSprite::ST_FRAME);
   tolua_constant(tolua_S,"ST_PICBOX",BBlockSprite::ST_PICBOX);
   tolua_constant(tolua_S,"ST_BUTTON",BBlockSprite::ST_BUTTON);
   tolua_constant(tolua_S,"ST_TEXT",BBlockSprite::ST_TEXT);
   tolua_constant(tolua_S,"ST_EDITBOX",BBlockSprite::ST_EDITBOX);
   tolua_constant(tolua_S,"ST_COMBOXBOX",BBlockSprite::ST_COMBOXBOX);
   tolua_constant(tolua_S,"ST_WEBVIEW",BBlockSprite::ST_WEBVIEW);
   tolua_constant(tolua_S,"ST_ROUND",BBlockSprite::ST_ROUND);
   tolua_constant(tolua_S,"ST_MAX_TYPE",BBlockSprite::ST_MAX_TYPE);
   tolua_function(tolua_S,"new",tolua_BBlocks_BBlockSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_BBlockSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_BBlockSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_BBlockSprite_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockSprite_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockSprite_New01);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockSprite_New02);
   tolua_function(tolua_S,"GetSpriteType",tolua_BBlocks_BBlockSprite_GetSpriteType00);
   tolua_function(tolua_S,"SetName",tolua_BBlocks_BBlockSprite_SetName00);
   tolua_function(tolua_S,"GetScriptGenController",tolua_BBlocks_BBlockSprite_GetScriptGenController00);
   tolua_function(tolua_S,"setName",tolua_BBlocks_BBlockSprite_setName00);
   tolua_function(tolua_S,"getName",tolua_BBlocks_BBlockSprite_getName00);
   tolua_function(tolua_S,"attachChild",tolua_BBlocks_BBlockSprite_attachChild00);
   tolua_function(tolua_S,"detachChild",tolua_BBlocks_BBlockSprite_detachChild00);
   tolua_function(tolua_S,"detachChildByName",tolua_BBlocks_BBlockSprite_detachChildByName00);
   tolua_function(tolua_S,"show",tolua_BBlocks_BBlockSprite_show00);
   tolua_function(tolua_S,"isShow",tolua_BBlocks_BBlockSprite_isShow00);
   tolua_function(tolua_S,"setText",tolua_BBlocks_BBlockSprite_setText00);
   tolua_function(tolua_S,"getText",tolua_BBlocks_BBlockSprite_getText00);
   tolua_function(tolua_S,"setScale",tolua_BBlocks_BBlockSprite_setScale00);
   tolua_function(tolua_S,"getScale",tolua_BBlocks_BBlockSprite_getScale00);
   tolua_function(tolua_S,"setScaleXZ",tolua_BBlocks_BBlockSprite_setScaleXZ00);
   tolua_function(tolua_S,"setScaleX",tolua_BBlocks_BBlockSprite_setScaleX00);
   tolua_function(tolua_S,"setScaleZ",tolua_BBlocks_BBlockSprite_setScaleZ00);
   tolua_function(tolua_S,"getScaleX",tolua_BBlocks_BBlockSprite_getScaleX00);
   tolua_function(tolua_S,"getScaleZ",tolua_BBlocks_BBlockSprite_getScaleZ00);
   tolua_function(tolua_S,"addScale",tolua_BBlocks_BBlockSprite_addScale00);
   tolua_function(tolua_S,"setRotateXYZ",tolua_BBlocks_BBlockSprite_setRotateXYZ00);
   tolua_function(tolua_S,"setRotateX",tolua_BBlocks_BBlockSprite_setRotateX00);
   tolua_function(tolua_S,"setRotateY",tolua_BBlocks_BBlockSprite_setRotateY00);
   tolua_function(tolua_S,"setRotateZ",tolua_BBlocks_BBlockSprite_setRotateZ00);
   tolua_function(tolua_S,"getRotateX",tolua_BBlocks_BBlockSprite_getRotateX00);
   tolua_function(tolua_S,"getRotateY",tolua_BBlocks_BBlockSprite_getRotateY00);
   tolua_function(tolua_S,"getRotateZ",tolua_BBlocks_BBlockSprite_getRotateZ00);
   tolua_function(tolua_S,"addRotate",tolua_BBlocks_BBlockSprite_addRotate00);
   tolua_function(tolua_S,"setLayout",tolua_BBlocks_BBlockSprite_setLayout00);
   tolua_function(tolua_S,"setPostion",tolua_BBlocks_BBlockSprite_setPostion00);
   tolua_function(tolua_S,"setAnchorHor",tolua_BBlocks_BBlockSprite_setAnchorHor00);
   tolua_function(tolua_S,"setAnchorParamHor",tolua_BBlocks_BBlockSprite_setAnchorParamHor00);
   tolua_function(tolua_S,"setAnchorVer",tolua_BBlocks_BBlockSprite_setAnchorVer00);
   tolua_function(tolua_S,"setAnchorParamVer",tolua_BBlocks_BBlockSprite_setAnchorParamVer00);
   tolua_function(tolua_S,"move",tolua_BBlocks_BBlockSprite_move00);
   tolua_function(tolua_S,"setLayer",tolua_BBlocks_BBlockSprite_setLayer00);
   tolua_function(tolua_S,"getLayer",tolua_BBlocks_BBlockSprite_getLayer00);
   tolua_function(tolua_S,"setPivot",tolua_BBlocks_BBlockSprite_setPivot00);
   tolua_function(tolua_S,"setSize",tolua_BBlocks_BBlockSprite_setSize00);
   tolua_function(tolua_S,"setSizeWidthHeight",tolua_BBlocks_BBlockSprite_setSizeWidthHeight00);
   tolua_function(tolua_S,"getDragingDirX",tolua_BBlocks_BBlockSprite_getDragingDirX00);
   tolua_function(tolua_S,"getDragingDirY",tolua_BBlocks_BBlockSprite_getDragingDirY00);
   tolua_function(tolua_S,"getDragingDirSimple",tolua_BBlocks_BBlockSprite_getDragingDirSimple00);
   tolua_function(tolua_S,"getDragingPercent",tolua_BBlocks_BBlockSprite_getDragingPercent00);
   tolua_function(tolua_S,"addChooseString",tolua_BBlocks_BBlockSprite_addChooseString00);
   tolua_function(tolua_S,"chooseString",tolua_BBlocks_BBlockSprite_chooseString00);
   tolua_function(tolua_S,"chooseIndex",tolua_BBlocks_BBlockSprite_chooseIndex00);
   tolua_function(tolua_S,"getChooseString",tolua_BBlocks_BBlockSprite_getChooseString00);
   tolua_function(tolua_S,"getChooseIndex",tolua_BBlocks_BBlockSprite_getChooseIndex00);
   tolua_function(tolua_S,"setURL",tolua_BBlocks_BBlockSprite_setURL00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BBlockSystem","BBlockSystem","",NULL);
  tolua_beginmodule(tolua_S,"BBlockSystem");
   tolua_function(tolua_S,"createSpriteFrame",tolua_BBlocks_BBlockSystem_createSpriteFrame00);
   tolua_function(tolua_S,"createSpritePicBox",tolua_BBlocks_BBlockSystem_createSpritePicBox00);
   tolua_function(tolua_S,"createSpriteButton",tolua_BBlocks_BBlockSystem_createSpriteButton00);
   tolua_function(tolua_S,"createSpriteText",tolua_BBlocks_BBlockSystem_createSpriteText00);
   tolua_function(tolua_S,"createSpriteEditBox",tolua_BBlocks_BBlockSystem_createSpriteEditBox00);
   tolua_function(tolua_S,"createSpriteComboBox",tolua_BBlocks_BBlockSystem_createSpriteComboBox00);
   tolua_function(tolua_S,"createSpriteWebView",tolua_BBlocks_BBlockSystem_createSpriteWebView00);
   tolua_function(tolua_S,"createSpriteRound",tolua_BBlocks_BBlockSystem_createSpriteRound00);
   tolua_function(tolua_S,"getLastCreateSprite",tolua_BBlocks_BBlockSystem_getLastCreateSprite00);
   tolua_function(tolua_S,"getSpriteOfName",tolua_BBlocks_BBlockSystem_getSpriteOfName00);
   tolua_function(tolua_S,"log",tolua_BBlocks_BBlockSystem_log00);
   tolua_function(tolua_S,"playMusic",tolua_BBlocks_BBlockSystem_playMusic00);
   tolua_function(tolua_S,"stopMusic",tolua_BBlocks_BBlockSystem_stopMusic00);
   tolua_function(tolua_S,"stringToInt",tolua_BBlocks_BBlockSystem_stringToInt00);
   tolua_function(tolua_S,"stringToFloat",tolua_BBlocks_BBlockSystem_stringToFloat00);
   tolua_function(tolua_S,"intToString",tolua_BBlocks_BBlockSystem_intToString00);
   tolua_function(tolua_S,"floatToString",tolua_BBlocks_BBlockSystem_floatToString00);
   tolua_function(tolua_S,"getStringParam",tolua_BBlocks_BBlockSystem_getStringParam00);
   tolua_function(tolua_S,"sendEvent",tolua_BBlocks_BBlockSystem_sendEvent00);
   tolua_function(tolua_S,"getEventObjectName",tolua_BBlocks_BBlockSystem_getEventObjectName00);
   tolua_function(tolua_S,"getEventDataInt",tolua_BBlocks_BBlockSystem_getEventDataInt00);
   tolua_function(tolua_S,"getEventDataString",tolua_BBlocks_BBlockSystem_getEventDataString00);
   tolua_function(tolua_S,"netCreateServer",tolua_BBlocks_BBlockSystem_netCreateServer00);
   tolua_function(tolua_S,"netServerSendString",tolua_BBlocks_BBlockSystem_netServerSendString00);
   tolua_function(tolua_S,"netCreateClientConnector",tolua_BBlocks_BBlockSystem_netCreateClientConnector00);
   tolua_function(tolua_S,"netClientSendString",tolua_BBlocks_BBlockSystem_netClientSendString00);
   tolua_function(tolua_S,"bluetoothSendString",tolua_BBlocks_BBlockSystem_bluetoothSendString00);
   tolua_function(tolua_S,"serialOpen",tolua_BBlocks_BBlockSystem_serialOpen00);
   tolua_function(tolua_S,"serialClose",tolua_BBlocks_BBlockSystem_serialClose00);
   tolua_function(tolua_S,"serialSend",tolua_BBlocks_BBlockSystem_serialSend00);
   tolua_function(tolua_S,"voiceStart",tolua_BBlocks_BBlockSystem_voiceStart00);
   tolua_function(tolua_S,"voiceEnd",tolua_BBlocks_BBlockSystem_voiceEnd00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_BBlocks (lua_State* tolua_S) {
 return tolua_BBlocks_open(tolua_S);
};
#endif

