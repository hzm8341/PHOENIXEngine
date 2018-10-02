/*
** Lua binding: BBlocks
** Generated automatically by tolua++-1.0.92 on 02/24/18 18:34:08.
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

static int tolua_collect_BBlockSprite (lua_State* tolua_S)
{
 BBlockSprite* self = (BBlockSprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_BProject (lua_State* tolua_S)
{
 BProject* self = (BProject*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_BBlock (lua_State* tolua_S)
{
 BBlock* self = (BBlock*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

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

static int tolua_collect_BBManager (lua_State* tolua_S)
{
 BBManager* self = (BBManager*) tolua_tousertype(tolua_S,1,0);
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
 tolua_usertype(tolua_S,"BBlockSprite");
 tolua_usertype(tolua_S,"CameraPlayController");
 tolua_usertype(tolua_S,"Event");
 tolua_usertype(tolua_S,"LBlock");
 tolua_usertype(tolua_S,"UIFrame");
 tolua_usertype(tolua_S,"UIBBlockPanels");
 tolua_usertype(tolua_S,"UIBBlockEditToolFrame");
 tolua_usertype(tolua_S,"UICheckButton");
 tolua_usertype(tolua_S,"std::vector<Pointer0<BBlockConnector> >");
 tolua_usertype(tolua_S,"BBlockConnector");
 tolua_usertype(tolua_S,"Float4");
 tolua_usertype(tolua_S,"Scene");
 tolua_usertype(tolua_S,"Float2");
 tolua_usertype(tolua_S,"Controller");
 tolua_usertype(tolua_S,"BBlock");
 tolua_usertype(tolua_S,"BProject");
 tolua_usertype(tolua_S,"UIButton");
 tolua_usertype(tolua_S,"UIBBlockCataFrame");
 tolua_usertype(tolua_S,"CameraNode");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"UIBBlockEdit");
 tolua_usertype(tolua_S,"LFile");
 tolua_usertype(tolua_S,"BBlockSystem");
 tolua_usertype(tolua_S,"BBManager");
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

/* method: SetShowType of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_SetShowType00
static int tolua_BBlocks_UIBBlockEditToolFrame_SetShowType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBBlockEditToolFrame* self = (UIBBlockEditToolFrame*)  tolua_tousertype(tolua_S,1,0);
  UIBBlockEditToolFrame::ShowType st = ((UIBBlockEditToolFrame::ShowType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowType'", NULL);
#endif
  {
   self->SetShowType(st);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShowType of class  UIBBlockEditToolFrame */
#ifndef TOLUA_DISABLE_tolua_BBlocks_UIBBlockEditToolFrame_GetShowType00
static int tolua_BBlocks_UIBBlockEditToolFrame_GetShowType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIBBlockEditToolFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIBBlockEditToolFrame* self = (const UIBBlockEditToolFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShowType'", NULL);
#endif
  {
   UIBBlockEditToolFrame::ShowType tolua_ret = (UIBBlockEditToolFrame::ShowType)  self->GetShowType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShowType'.",&tolua_err);
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

/* method: GetSpriteTypeStr of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetSpriteTypeStr00
static int tolua_BBlocks_BBlockSprite_GetSpriteTypeStr00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpriteTypeStr'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetSpriteTypeStr();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpriteTypeStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHorLayOutType of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetHorLayOutType00
static int tolua_BBlocks_BBlockSprite_SetHorLayOutType00(lua_State* tolua_S)
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
  BBlockSprite::HorLayOutType type = ((BBlockSprite::HorLayOutType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHorLayOutType'", NULL);
#endif
  {
   self->SetHorLayOutType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHorLayOutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHorLayOutType of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetHorLayOutType00
static int tolua_BBlocks_BBlockSprite_GetHorLayOutType00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHorLayOutType'", NULL);
#endif
  {
   BBlockSprite::HorLayOutType tolua_ret = (BBlockSprite::HorLayOutType)  self->GetHorLayOutType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHorLayOutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayoutParamHor of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetLayoutParamHor00
static int tolua_BBlocks_BBlockSprite_SetLayoutParamHor00(lua_State* tolua_S)
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
  float param0 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayoutParamHor'", NULL);
#endif
  {
   self->SetLayoutParamHor(param0);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayoutParamHor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayoutParamHor of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetLayoutParamHor00
static int tolua_BBlocks_BBlockSprite_GetLayoutParamHor00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutParamHor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLayoutParamHor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutParamHor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVerLayoutType of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetVerLayoutType00
static int tolua_BBlocks_BBlockSprite_SetVerLayoutType00(lua_State* tolua_S)
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
  BBlockSprite::VerLayoutType type = ((BBlockSprite::VerLayoutType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVerLayoutType'", NULL);
#endif
  {
   self->SetVerLayoutType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVerLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVerLayoutType of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetVerLayoutType00
static int tolua_BBlocks_BBlockSprite_GetVerLayoutType00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVerLayoutType'", NULL);
#endif
  {
   BBlockSprite::VerLayoutType tolua_ret = (BBlockSprite::VerLayoutType)  self->GetVerLayoutType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVerLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayoutParamVer of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetLayoutParamVer00
static int tolua_BBlocks_BBlockSprite_SetLayoutParamVer00(lua_State* tolua_S)
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
  float param0 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayoutParamVer'", NULL);
#endif
  {
   self->SetLayoutParamVer(param0);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayoutParamVer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayoutParamVer of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_GetLayoutParamVer00
static int tolua_BBlocks_BBlockSprite_GetLayoutParamVer00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutParamVer'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLayoutParamVer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutParamVer'.",&tolua_err);
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

/* method: SetDragable of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetDragable00
static int tolua_BBlocks_BBlockSprite_SetDragable00(lua_State* tolua_S)
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
  bool dragable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDragable'", NULL);
#endif
  {
   self->SetDragable(dragable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDragable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDragable of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_IsDragable00
static int tolua_BBlocks_BBlockSprite_IsDragable00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDragable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDragable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDragable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoPickFrameObject of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetDoPickFrameObject00
static int tolua_BBlocks_BBlockSprite_SetDoPickFrameObject00(lua_State* tolua_S)
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
  bool pick = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoPickFrameObject'", NULL);
#endif
  {
   self->SetDoPickFrameObject(pick);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoPickFrameObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDoPickFrameObject of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_IsDoPickFrameObject00
static int tolua_BBlocks_BBlockSprite_IsDoPickFrameObject00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDoPickFrameObject'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDoPickFrameObject();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDoPickFrameObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLookImage of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetLookImage00
static int tolua_BBlocks_BBlockSprite_SetLookImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string image = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  bool isUse9Grid = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLookImage'", NULL);
#endif
  {
   self->SetLookImage(image,isUse9Grid);
   tolua_pushcppstring(tolua_S,(const char*)image);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLookImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLookImage1 of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_SetLookImage100
static int tolua_BBlocks_BBlockSprite_SetLookImage100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string image = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  bool isUse9Grid = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLookImage1'", NULL);
#endif
  {
   self->SetLookImage1(image,isUse9Grid);
   tolua_pushcppstring(tolua_S,(const char*)image);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLookImage1'.",&tolua_err);
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

/* method: setColor of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setColor00
static int tolua_BBlocks_BBlockSprite_setColor00(lua_State* tolua_S)
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
  int r = ((int)  tolua_tonumber(tolua_S,2,0));
  int g = ((int)  tolua_tonumber(tolua_S,3,0));
  int b = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(r,g,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAlpha of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setAlpha00
static int tolua_BBlocks_BBlockSprite_setAlpha00(lua_State* tolua_S)
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
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAlpha'", NULL);
#endif
  {
   self->setAlpha(a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFixUpdateFPS of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setFixUpdateFPS00
static int tolua_BBlocks_BBlockSprite_setFixUpdateFPS00(lua_State* tolua_S)
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
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFixUpdateFPS'", NULL);
#endif
  {
   self->setFixUpdateFPS(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFixUpdateFPS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFixUpdateFPS of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getFixUpdateFPS00
static int tolua_BBlocks_BBlockSprite_getFixUpdateFPS00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFixUpdateFPS'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFixUpdateFPS();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFixUpdateFPS'.",&tolua_err);
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

/* method: setTextFontSize of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setTextFontSize00
static int tolua_BBlocks_BBlockSprite_setTextFontSize00(lua_State* tolua_S)
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
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextFontSize'", NULL);
#endif
  {
   self->setTextFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextFontSize'.",&tolua_err);
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

/* method: setValue of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setValue00
static int tolua_BBlocks_BBlockSprite_setValue00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValue of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getValue00
static int tolua_BBlocks_BBlockSprite_getValue00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
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

/* method: setSize1 of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setSize100
static int tolua_BBlocks_BBlockSprite_setSize100(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize1'", NULL);
#endif
  {
   self->setSize1(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize1'.",&tolua_err);
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

/* method: setSliderPercent of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setSliderPercent00
static int tolua_BBlocks_BBlockSprite_setSliderPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  float perc = ((float)  tolua_tonumber(tolua_S,2,0.5f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSliderPercent'", NULL);
#endif
  {
   self->setSliderPercent(perc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSliderPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlider100 of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setSlider10000
static int tolua_BBlocks_BBlockSprite_setSlider10000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,50));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlider100'", NULL);
#endif
  {
   self->setSlider100(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlider100'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlider180 of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_setSlider18000
static int tolua_BBlocks_BBlockSprite_setSlider18000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSprite* self = (BBlockSprite*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,90));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlider180'", NULL);
#endif
  {
   self->setSlider180(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlider180'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSliderPercent of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getSliderPercent00
static int tolua_BBlocks_BBlockSprite_getSliderPercent00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSliderPercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSliderPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSliderPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlider100 of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getSlider10000
static int tolua_BBlocks_BBlockSprite_getSlider10000(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlider100'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSlider100();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlider100'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlider180 of class  BBlockSprite */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSprite_getSlider18000
static int tolua_BBlocks_BBlockSprite_getSlider18000(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlider180'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSlider180();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlider180'.",&tolua_err);
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

/* method: Initlize of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_Initlize00
static int tolua_BBlocks_BBlockSystem_Initlize00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Initlize'", NULL);
#endif
  {
   self->Initlize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Initlize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_Run00
static int tolua_BBlocks_BBlockSystem_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  bool run = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'", NULL);
#endif
  {
   self->Run(run);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReStart of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_ReStart00
static int tolua_BBlocks_BBlockSystem_ReStart00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReStart'", NULL);
#endif
  {
   self->ReStart();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRunning of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_IsRunning00
static int tolua_BBlocks_BBlockSystem_IsRunning00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRunning'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsRunning();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRunning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSysType of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_SetSysType00
static int tolua_BBlocks_BBlockSystem_SetSysType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::SysType st = ((BBlockSystem::SysType) (int)  tolua_tonumber(tolua_S,2,0));
  int robotID = ((int)  tolua_tonumber(tolua_S,3,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSysType'", NULL);
#endif
  {
   self->SetSysType(st,robotID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSysType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSysType of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_SetSysType01
static int tolua_BBlocks_BBlockSystem_SetSysType01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::SysType st = ((BBlockSystem::SysType) (int)  tolua_tonumber(tolua_S,2,0));
  int robotID = ((int)  tolua_tonumber(tolua_S,3,0));
  const std::string serialPort = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  int baudrate = ((int)  tolua_tonumber(tolua_S,5,9600));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSysType'", NULL);
#endif
  {
   self->SetSysType(st,robotID,serialPort,baudrate);
   tolua_pushcppstring(tolua_S,(const char*)serialPort);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BBlocks_BBlockSystem_SetSysType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSysType of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_GetSysType00
static int tolua_BBlocks_BBlockSystem_GetSysType00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSysType'", NULL);
#endif
  {
   BBlockSystem::SysType tolua_ret = (BBlockSystem::SysType)  self->GetSysType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSysType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setName00
static int tolua_BBlocks_BBlockSystem_setName00(lua_State* tolua_S)
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

/* method: getName of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getName00
static int tolua_BBlocks_BBlockSystem_getName00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
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

/* method: setFixUpdateFPS of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setFixUpdateFPS00
static int tolua_BBlocks_BBlockSystem_setFixUpdateFPS00(lua_State* tolua_S)
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
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFixUpdateFPS'", NULL);
#endif
  {
   self->setFixUpdateFPS(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFixUpdateFPS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFixUpdateFPS of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getFixUpdateFPS00
static int tolua_BBlocks_BBlockSystem_getFixUpdateFPS00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFixUpdateFPS'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFixUpdateFPS();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFixUpdateFPS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_show00
static int tolua_BBlocks_BBlockSystem_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isShow of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_isShow00
static int tolua_BBlocks_BBlockSystem_isShow00(lua_State* tolua_S)
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

/* method: setText of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setText00
static int tolua_BBlocks_BBlockSystem_setText00(lua_State* tolua_S)
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

/* method: getText of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getText00
static int tolua_BBlocks_BBlockSystem_getText00(lua_State* tolua_S)
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

/* method: setScale of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setScale00
static int tolua_BBlocks_BBlockSystem_setScale00(lua_State* tolua_S)
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

/* method: getScale of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getScale00
static int tolua_BBlocks_BBlockSystem_getScale00(lua_State* tolua_S)
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

/* method: setScaleXZ of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setScaleXZ00
static int tolua_BBlocks_BBlockSystem_setScaleXZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setScaleX of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setScaleX00
static int tolua_BBlocks_BBlockSystem_setScaleX00(lua_State* tolua_S)
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

/* method: setScaleZ of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setScaleZ00
static int tolua_BBlocks_BBlockSystem_setScaleZ00(lua_State* tolua_S)
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

/* method: getScaleX of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getScaleX00
static int tolua_BBlocks_BBlockSystem_getScaleX00(lua_State* tolua_S)
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

/* method: getScaleZ of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getScaleZ00
static int tolua_BBlocks_BBlockSystem_getScaleZ00(lua_State* tolua_S)
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

/* method: addScale of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_addScale00
static int tolua_BBlocks_BBlockSystem_addScale00(lua_State* tolua_S)
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

/* method: setRotateXYZ of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setRotateXYZ00
static int tolua_BBlocks_BBlockSystem_setRotateXYZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setRotateX of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setRotateX00
static int tolua_BBlocks_BBlockSystem_setRotateX00(lua_State* tolua_S)
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

/* method: setRotateY of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setRotateY00
static int tolua_BBlocks_BBlockSystem_setRotateY00(lua_State* tolua_S)
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

/* method: setRotateZ of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setRotateZ00
static int tolua_BBlocks_BBlockSystem_setRotateZ00(lua_State* tolua_S)
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

/* method: getRotateX of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getRotateX00
static int tolua_BBlocks_BBlockSystem_getRotateX00(lua_State* tolua_S)
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

/* method: getRotateY of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getRotateY00
static int tolua_BBlocks_BBlockSystem_getRotateY00(lua_State* tolua_S)
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

/* method: getRotateZ of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getRotateZ00
static int tolua_BBlocks_BBlockSystem_getRotateZ00(lua_State* tolua_S)
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

/* method: addRotate of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_addRotate00
static int tolua_BBlocks_BBlockSystem_addRotate00(lua_State* tolua_S)
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

/* method: setLayout of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setLayout00
static int tolua_BBlocks_BBlockSystem_setLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
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
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPostion of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setPostion00
static int tolua_BBlocks_BBlockSystem_setPostion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorHor of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setAnchorHor00
static int tolua_BBlocks_BBlockSystem_setAnchorHor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorParamHor of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setAnchorParamHor00
static int tolua_BBlocks_BBlockSystem_setAnchorParamHor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorVer of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setAnchorVer00
static int tolua_BBlocks_BBlockSystem_setAnchorVer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorParamVer of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setAnchorParamVer00
static int tolua_BBlocks_BBlockSystem_setAnchorParamVer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: move of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_move00
static int tolua_BBlocks_BBlockSystem_move00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setLayer of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setLayer00
static int tolua_BBlocks_BBlockSystem_setLayer00(lua_State* tolua_S)
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

/* method: getLayer of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getLayer00
static int tolua_BBlocks_BBlockSystem_getLayer00(lua_State* tolua_S)
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

/* method: setPivot of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setPivot00
static int tolua_BBlocks_BBlockSystem_setPivot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSize of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSize00
static int tolua_BBlocks_BBlockSystem_setSize00(lua_State* tolua_S)
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

/* method: setSizeWidthHeight of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSizeWidthHeight00
static int tolua_BBlocks_BBlockSystem_setSizeWidthHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDragingDirX of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingDirX00
static int tolua_BBlocks_BBlockSystem_getDragingDirX00(lua_State* tolua_S)
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

/* method: getDragingDirY of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingDirY00
static int tolua_BBlocks_BBlockSystem_getDragingDirY00(lua_State* tolua_S)
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

/* method: getDragingDirSimple of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingDirSimple00
static int tolua_BBlocks_BBlockSystem_getDragingDirSimple00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingDirSimple'", NULL);
#endif
  {
   BBlockSystem::SimpleDirectionType tolua_ret = (BBlockSystem::SimpleDirectionType)  self->getDragingDirSimple();
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

/* method: getDragingPercent of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingPercent00
static int tolua_BBlocks_BBlockSystem_getDragingPercent00(lua_State* tolua_S)
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

/* method: getDragingLeftMoveType of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingLeftMoveType00
static int tolua_BBlocks_BBlockSystem_getDragingLeftMoveType00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingLeftMoveType'", NULL);
#endif
  {
   BBlockSystem::DirectionType tolua_ret = (BBlockSystem::DirectionType)  self->getDragingLeftMoveType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingLeftMoveType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingLeftMoveSpeed of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingLeftMoveSpeed00
static int tolua_BBlocks_BBlockSystem_getDragingLeftMoveSpeed00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingLeftMoveSpeed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDragingLeftMoveSpeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingLeftMoveSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingRightMoveType of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingRightMoveType00
static int tolua_BBlocks_BBlockSystem_getDragingRightMoveType00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingRightMoveType'", NULL);
#endif
  {
   BBlockSystem::DirectionType tolua_ret = (BBlockSystem::DirectionType)  self->getDragingRightMoveType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingRightMoveType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragingRightMoveSpeed of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDragingRightMoveSpeed00
static int tolua_BBlocks_BBlockSystem_getDragingRightMoveSpeed00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragingRightMoveSpeed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDragingRightMoveSpeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragingRightMoveSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSliderPercent of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSliderPercent00
static int tolua_BBlocks_BBlockSystem_setSliderPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  float perc = ((float)  tolua_tonumber(tolua_S,2,0.5f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSliderPercent'", NULL);
#endif
  {
   self->setSliderPercent(perc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSliderPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlider100 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSlider10000
static int tolua_BBlocks_BBlockSystem_setSlider10000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,50));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlider100'", NULL);
#endif
  {
   self->setSlider100(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlider100'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlider180 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSlider18000
static int tolua_BBlocks_BBlockSystem_setSlider18000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,90));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlider180'", NULL);
#endif
  {
   self->setSlider180(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlider180'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSliderPercent of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getSliderPercent00
static int tolua_BBlocks_BBlockSystem_getSliderPercent00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSliderPercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSliderPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSliderPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlider100 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getSlider10000
static int tolua_BBlocks_BBlockSystem_getSlider10000(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlider100'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSlider100();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlider100'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlider180 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getSlider18000
static int tolua_BBlocks_BBlockSystem_getSlider18000(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlider180'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSlider180();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlider180'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlider360 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getSlider36000
static int tolua_BBlocks_BBlockSystem_getSlider36000(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlider360'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSlider360();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlider360'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChooseString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_addChooseString00
static int tolua_BBlocks_BBlockSystem_addChooseString00(lua_State* tolua_S)
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

/* method: chooseString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_chooseString00
static int tolua_BBlocks_BBlockSystem_chooseString00(lua_State* tolua_S)
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

/* method: chooseIndex of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_chooseIndex00
static int tolua_BBlocks_BBlockSystem_chooseIndex00(lua_State* tolua_S)
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

/* method: getChooseString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getChooseString00
static int tolua_BBlocks_BBlockSystem_getChooseString00(lua_State* tolua_S)
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

/* method: getChooseIndex of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getChooseIndex00
static int tolua_BBlocks_BBlockSystem_getChooseIndex00(lua_State* tolua_S)
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

/* method: setURL of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setURL00
static int tolua_BBlocks_BBlockSystem_setURL00(lua_State* tolua_S)
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

/* method: pinMode of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_pinMode00
static int tolua_BBlocks_BBlockSystem_pinMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::Pin pin = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
  BBlockSystem::PMode mode = ((BBlockSystem::PMode) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pinMode'", NULL);
#endif
  {
   self->pinMode(pin,mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pinMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: digitalWrite of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_digitalWrite00
static int tolua_BBlocks_BBlockSystem_digitalWrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::Pin pin = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
  bool isHigh = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'digitalWrite'", NULL);
#endif
  {
   self->digitalWrite(pin,isHigh);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'digitalWrite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: analogWrite of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_analogWrite00
static int tolua_BBlocks_BBlockSystem_analogWrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::Pin pin = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
  int val = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'analogWrite'", NULL);
#endif
  {
   self->analogWrite(pin,val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'analogWrite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: digitalRead of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_digitalRead00
static int tolua_BBlocks_BBlockSystem_digitalRead00(lua_State* tolua_S)
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
  BBlockSystem::Pin pin = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'digitalRead'", NULL);
#endif
  {
   int tolua_ret = (int)  self->digitalRead(pin);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'digitalRead'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: analogRead of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_analogRead00
static int tolua_BBlocks_BBlockSystem_analogRead00(lua_State* tolua_S)
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
  BBlockSystem::Pin pin = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'analogRead'", NULL);
#endif
  {
   int tolua_ret = (int)  self->analogRead(pin);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'analogRead'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serverInit of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_serverInit00
static int tolua_BBlocks_BBlockSystem_serverInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  BBlockSystem::Pin pin = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serverInit'", NULL);
#endif
  {
   self->serverInit(index,pin);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serverInit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serverWrite of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_serverWrite00
static int tolua_BBlocks_BBlockSystem_serverWrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int val = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serverWrite'", NULL);
#endif
  {
   self->serverWrite(index,val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serverWrite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distInit of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_distInit00
static int tolua_BBlocks_BBlockSystem_distInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::Pin pinTrig = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
  BBlockSystem::Pin pinEcho = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distInit'", NULL);
#endif
  {
   self->distInit(pinTrig,pinEcho);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distInit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distTest of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_distTest00
static int tolua_BBlocks_BBlockSystem_distTest00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distTest'", NULL);
#endif
  {
   self->distTest();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDist of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDist00
static int tolua_BBlocks_BBlockSystem_getDist00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDist'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDist();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleInitMotoBoard of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleInitMotoBoard00
static int tolua_BBlocks_BBlockSystem_vehicleInitMotoBoard00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleInitMotoBoard'", NULL);
#endif
  {
   self->vehicleInitMotoBoard();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleInitMotoBoard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleInitMotoBoard4567 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleInitMotoBoard456700
static int tolua_BBlocks_BBlockSystem_vehicleInitMotoBoard456700(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleInitMotoBoard4567'", NULL);
#endif
  {
   self->vehicleInitMotoBoard4567();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleInitMotoBoard4567'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleRun of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleRun00
static int tolua_BBlocks_BBlockSystem_vehicleRun00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  BBlockSystem::DirectionType type = ((BBlockSystem::DirectionType) (int)  tolua_tonumber(tolua_S,3,0));
  int speed = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleRun'", NULL);
#endif
  {
   self->vehicleRun(index,type,speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleRun'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleRunSimple of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleRunSimple00
static int tolua_BBlocks_BBlockSystem_vehicleRunSimple00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::SimpleDirectionType type = ((BBlockSystem::SimpleDirectionType) (int)  tolua_tonumber(tolua_S,2,0));
  int speed = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleRunSimple'", NULL);
#endif
  {
   self->vehicleRunSimple(type,speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleRunSimple'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleStop of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleStop00
static int tolua_BBlocks_BBlockSystem_vehicleStop00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleStop'", NULL);
#endif
  {
   self->vehicleStop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleStop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleSpeedInit of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleSpeedInit00
static int tolua_BBlocks_BBlockSystem_vehicleSpeedInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::Pin pinLA = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
  BBlockSystem::Pin pinLB = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,3,0));
  BBlockSystem::Pin pinRA = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,4,0));
  BBlockSystem::Pin pinRB = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleSpeedInit'", NULL);
#endif
  {
   self->vehicleSpeedInit(pinLA,pinLB,pinRA,pinRB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleSpeedInit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vehicleGetSpeed of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_vehicleGetSpeed00
static int tolua_BBlocks_BBlockSystem_vehicleGetSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlockSystem* self = (const BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int motoIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vehicleGetSpeed'", NULL);
#endif
  {
   int tolua_ret = (int)  self->vehicleGetSpeed(motoIndex);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vehicleGetSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: irSend of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_irSend00
static int tolua_BBlocks_BBlockSystem_irSend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,100));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'irSend'", NULL);
#endif
  {
   self->irSend(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'irSend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: irRecvInit of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_irRecvInit00
static int tolua_BBlocks_BBlockSystem_irRecvInit00(lua_State* tolua_S)
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
  BBlockSystem::Pin pinReceive = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'irRecvInit'", NULL);
#endif
  {
   self->irRecvInit(pinReceive);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'irRecvInit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIRReceive of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getIRReceive00
static int tolua_BBlocks_BBlockSystem_getIRReceive00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIRReceive'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIRReceive();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIRReceive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurBBlockSprite of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setCurBBlockSprite00
static int tolua_BBlocks_BBlockSystem_setCurBBlockSprite00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurBBlockSprite'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->setCurBBlockSprite(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurBBlockSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurBBlockSprite of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getCurBBlockSprite00
static int tolua_BBlocks_BBlockSystem_getCurBBlockSprite00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurBBlockSprite'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->getCurBBlockSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurBBlockSprite'.",&tolua_err);
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

/* method: setBluetooth of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setBluetooth00
static int tolua_BBlocks_BBlockSystem_setBluetooth00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBluetooth'", NULL);
#endif
  {
   self->setBluetooth();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBluetooth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSerial of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSerial00
static int tolua_BBlocks_BBlockSystem_setSerial00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSerial'", NULL);
#endif
  {
   self->setSerial();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSerial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSerial of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setSerial01
static int tolua_BBlocks_BBlockSystem_setSerial01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string port = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSerial'", NULL);
#endif
  {
   self->setSerial(port);
   tolua_pushcppstring(tolua_S,(const char*)port);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BBlocks_BBlockSystem_setSerial00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWifiRobot of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setWifiRobot00
static int tolua_BBlocks_BBlockSystem_setWifiRobot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int robotID = ((int)  tolua_tonumber(tolua_S,2,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWifiRobot'", NULL);
#endif
  {
   self->setWifiRobot(robotID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWifiRobot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDeviceID of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_setDeviceID00
static int tolua_BBlocks_BBlockSystem_setDeviceID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDeviceID'", NULL);
#endif
  {
   self->setDeviceID(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDeviceID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeviceID of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDeviceID00
static int tolua_BBlocks_BBlockSystem_getDeviceID00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDeviceID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDeviceID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeviceID'.",&tolua_err);
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

/* method: stringAdd of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_stringAdd00
static int tolua_BBlocks_BBlockSystem_stringAdd00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stringAdd'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->stringAdd();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stringAdd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stringAdd of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_stringAdd01
static int tolua_BBlocks_BBlockSystem_stringAdd01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str0 = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stringAdd'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->stringAdd(str0);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)str0);
  }
 }
 return 2;
tolua_lerror:
 return tolua_BBlocks_BBlockSystem_stringAdd00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: stringAdd of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_stringAdd02
static int tolua_BBlocks_BBlockSystem_stringAdd02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str0 = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string str1 = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stringAdd'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->stringAdd(str0,str1);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)str0);
   tolua_pushcppstring(tolua_S,(const char*)str1);
  }
 }
 return 3;
tolua_lerror:
 return tolua_BBlocks_BBlockSystem_stringAdd01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getYear of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getYear00
static int tolua_BBlocks_BBlockSystem_getYear00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getYear'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getYear();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getYear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMonth of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getMonth00
static int tolua_BBlocks_BBlockSystem_getMonth00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMonth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMonth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMonth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWeek of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getWeek00
static int tolua_BBlocks_BBlockSystem_getWeek00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWeek'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWeek();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWeek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDay of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDay00
static int tolua_BBlocks_BBlockSystem_getDay00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDay'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDay();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDayOfWeek of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getDayOfWeek00
static int tolua_BBlocks_BBlockSystem_getDayOfWeek00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDayOfWeek'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDayOfWeek();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDayOfWeek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeHour of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getTimeHour00
static int tolua_BBlocks_BBlockSystem_getTimeHour00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeHour'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTimeHour();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeHour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeMinute of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getTimeMinute00
static int tolua_BBlocks_BBlockSystem_getTimeMinute00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeMinute'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTimeMinute();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeMinute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeSecond of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getTimeSecond00
static int tolua_BBlocks_BBlockSystem_getTimeSecond00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeSecond'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTimeSecond();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeSecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeString of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getTimeString00
static int tolua_BBlocks_BBlockSystem_getTimeString00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getTimeString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rand255 of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_rand25500
static int tolua_BBlocks_BBlockSystem_rand25500(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rand255'", NULL);
#endif
  {
   int tolua_ret = (int)  self->rand255();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rand255'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: randZeroOne of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_randZeroOne00
static int tolua_BBlocks_BBlockSystem_randZeroOne00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'randZeroOne'", NULL);
#endif
  {
   int tolua_ret = (int)  self->randZeroOne();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'randZeroOne'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: randZero2One of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_randZero2One00
static int tolua_BBlocks_BBlockSystem_randZero2One00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'randZero2One'", NULL);
#endif
  {
   float tolua_ret = (float)  self->randZero2One();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'randZero2One'.",&tolua_err);
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

/* method: playCam of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_playCam00
static int tolua_BBlocks_BBlockSystem_playCam00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playCam'", NULL);
#endif
  {
   self->playCam();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playCam'.",&tolua_err);
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

/* method: getEventDataFloat of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_getEventDataFloat00
static int tolua_BBlocks_BBlockSystem_getEventDataFloat00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEventDataFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getEventDataFloat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEventDataFloat'.",&tolua_err);
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

/* method: voiceSpeak of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_voiceSpeak00
static int tolua_BBlocks_BBlockSystem_voiceSpeak00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'voiceSpeak'", NULL);
#endif
  {
   self->voiceSpeak();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'voiceSpeak'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: voiceSpeak of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_voiceSpeak01
static int tolua_BBlocks_BBlockSystem_voiceSpeak01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  const std::string str = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'voiceSpeak'", NULL);
#endif
  {
   self->voiceSpeak(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BBlocks_BBlockSystem_voiceSpeak00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: voiceAutoSpeakEnable of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_voiceAutoSpeakEnable00
static int tolua_BBlocks_BBlockSystem_voiceAutoSpeakEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'voiceAutoSpeakEnable'", NULL);
#endif
  {
   self->voiceAutoSpeakEnable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'voiceAutoSpeakEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: voiceIsAutoSpeakEnable of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_voiceIsAutoSpeakEnable00
static int tolua_BBlocks_BBlockSystem_voiceIsAutoSpeakEnable00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'voiceIsAutoSpeakEnable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->voiceIsAutoSpeakEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'voiceIsAutoSpeakEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mp3Init of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_mp3Init00
static int tolua_BBlocks_BBlockSystem_mp3Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlockSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlockSystem* self = (BBlockSystem*)  tolua_tousertype(tolua_S,1,0);
  BBlockSystem::Pin pinR = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,2,0));
  BBlockSystem::Pin pinT = ((BBlockSystem::Pin) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mp3Init'", NULL);
#endif
  {
   self->mp3Init(pinR,pinT);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mp3Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mp3Play of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_mp3Play00
static int tolua_BBlocks_BBlockSystem_mp3Play00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mp3Play'", NULL);
#endif
  {
   self->mp3Play();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mp3Play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mp3PlayNext of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_mp3PlayNext00
static int tolua_BBlocks_BBlockSystem_mp3PlayNext00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mp3PlayNext'", NULL);
#endif
  {
   self->mp3PlayNext();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mp3PlayNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mp3PlayAtIndex of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_mp3PlayAtIndex00
static int tolua_BBlocks_BBlockSystem_mp3PlayAtIndex00(lua_State* tolua_S)
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
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mp3PlayAtIndex'", NULL);
#endif
  {
   self->mp3PlayAtIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mp3PlayAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mp3SetVolume of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_mp3SetVolume00
static int tolua_BBlocks_BBlockSystem_mp3SetVolume00(lua_State* tolua_S)
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
  int volume = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mp3SetVolume'", NULL);
#endif
  {
   self->mp3SetVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mp3SetVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mp3Stop of class  BBlockSystem */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlockSystem_mp3Stop00
static int tolua_BBlocks_BBlockSystem_mp3Stop00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mp3Stop'", NULL);
#endif
  {
   self->mp3Stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mp3Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_new00
static int tolua_BBlocks_BBManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBManager* tolua_ret = (BBManager*)  Mtolua_new((BBManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBManager");
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

/* method: new_local of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_new00_local
static int tolua_BBlocks_BBManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBManager* tolua_ret = (BBManager*)  Mtolua_new((BBManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBManager");
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

/* method: delete of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_delete00
static int tolua_BBlocks_BBManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetPlatformTag of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SetPlatformTag00
static int tolua_BBlocks_BBManager_SetPlatformTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string platTag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlatformTag'", NULL);
#endif
  {
   self->SetPlatformTag(platTag);
   tolua_pushcppstring(tolua_S,(const char*)platTag);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlatformTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlatformTag of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetPlatformTag00
static int tolua_BBlocks_BBManager_GetPlatformTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlatformTag'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetPlatformTag();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlatformTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetProductTag of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SetProductTag00
static int tolua_BBlocks_BBManager_SetProductTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string productTag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProductTag'", NULL);
#endif
  {
   self->SetProductTag(productTag);
   tolua_pushcppstring(tolua_S,(const char*)productTag);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProductTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProductTag of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetProductTag00
static int tolua_BBlocks_BBManager_GetProductTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProductTag'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetProductTag();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProductTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelectSprite of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SetSelectSprite00
static int tolua_BBlocks_BBManager_SetSelectSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"BBlockSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  BBlockSprite* sprite = ((BBlockSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelectSprite'", NULL);
#endif
  {
   self->SetSelectSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelectSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectSprite of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetSelectSprite00
static int tolua_BBlocks_BBManager_GetSelectSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectSprite'", NULL);
#endif
  {
   BBlockSprite* tolua_ret = (BBlockSprite*)  self->GetSelectSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelectBBlockEditor of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SetSelectBBlockEditor00
static int tolua_BBlocks_BBManager_SetSelectBBlockEditor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  BBlock* block = ((BBlock*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelectBBlockEditor'", NULL);
#endif
  {
   self->SetSelectBBlockEditor(block);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelectBBlockEditor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectBBlockEditor of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetSelectBBlockEditor00
static int tolua_BBlocks_BBManager_GetSelectBBlockEditor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectBBlockEditor'", NULL);
#endif
  {
   BBlock* tolua_ret = (BBlock*)  self->GetSelectBBlockEditor();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlock");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectBBlockEditor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetCurProject00
static int tolua_BBlocks_BBManager_GetCurProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurProject'", NULL);
#endif
  {
   BProject* tolua_ret = (BProject*)  self->GetCurProject();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BProject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStageFrame of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SetStageFrame00
static int tolua_BBlocks_BBManager_SetStageFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  UIFrame* stageFrame = ((UIFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStageFrame'", NULL);
#endif
  {
   self->SetStageFrame(stageFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStageFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStageFrame of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetStageFrame00
static int tolua_BBlocks_BBManager_GetStageFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStageFrame'", NULL);
#endif
  {
   UIFrame* tolua_ret = (UIFrame*)  self->GetStageFrame();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStageFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSmallFrame of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SetSmallFrame00
static int tolua_BBlocks_BBManager_SetSmallFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  UIFrame* smallFrame = ((UIFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSmallFrame'", NULL);
#endif
  {
   self->SetSmallFrame(smallFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSmallFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSmallFrame of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetSmallFrame00
static int tolua_BBlocks_BBManager_GetSmallFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSmallFrame'", NULL);
#endif
  {
   UIFrame* tolua_ret = (UIFrame*)  self->GetSmallFrame();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSmallFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalProjects of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetLocalProjects00
static int tolua_BBlocks_BBManager_GetLocalProjects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string appName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalProjects'", NULL);
#endif
  {
   self->GetLocalProjects(appName);
   tolua_pushcppstring(tolua_S,(const char*)appName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalProjects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetNumProject00
static int tolua_BBlocks_BBManager_GetNumProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumProject'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumProject();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProjectName of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetProjectName00
static int tolua_BBlocks_BBManager_GetProjectName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProjectName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetProjectName(i);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProjectName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetProject00
static int tolua_BBlocks_BBManager_GetProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProject'", NULL);
#endif
  {
   BProject* tolua_ret = (BProject*)  self->GetProject(i);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BProject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_NewProject00
static int tolua_BBlocks_BBManager_NewProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string appName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string projName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewProject'", NULL);
#endif
  {
   int tolua_ret = (int)  self->NewProject(appName,projName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)appName);
   tolua_pushcppstring(tolua_S,(const char*)projName);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_SaveProject00
static int tolua_BBlocks_BBManager_SaveProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveProject'", NULL);
#endif
  {
   self->SaveProject();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_LoadProject00
static int tolua_BBlocks_BBManager_LoadProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string appName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string projName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadProject'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadProject(appName,projName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)appName);
   tolua_pushcppstring(tolua_S,(const char*)projName);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAppName of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetAppName00
static int tolua_BBlocks_BBManager_GetAppName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAppName'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetAppName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAppName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProjectName of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_GetProjectName01
static int tolua_BBlocks_BBManager_GetProjectName01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const BBManager* self = (const BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProjectName'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetProjectName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_BBlocks_BBManager_GetProjectName00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsHasProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_IsHasProject00
static int tolua_BBlocks_BBManager_IsHasProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string projName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsHasProject'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsHasProject(projName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)projName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsHasProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CloseProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_CloseProject00
static int tolua_BBlocks_BBManager_CloseProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CloseProject'", NULL);
#endif
  {
   self->CloseProject();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CloseProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeleteProject of class  BBManager */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBManager_DeleteProject00
static int tolua_BBlocks_BBManager_DeleteProject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBManager* self = (BBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string appName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string projName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeleteProject'", NULL);
#endif
  {
   self->DeleteProject(appName,projName);
   tolua_pushcppstring(tolua_S,(const char*)appName);
   tolua_pushcppstring(tolua_S,(const char*)projName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteProject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_new00
static int tolua_BBlocks_BProject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BProject* tolua_ret = (BProject*)  Mtolua_new((BProject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BProject");
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

/* method: new_local of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_new00_local
static int tolua_BBlocks_BProject_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BProject* tolua_ret = (BProject*)  Mtolua_new((BProject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BProject");
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

/* method: delete of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_delete00
static int tolua_BBlocks_BProject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: DateStr of class  BProject */
#ifndef TOLUA_DISABLE_tolua_get_BProject_DateStr
static int tolua_get_BProject_DateStr(lua_State* tolua_S)
{
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DateStr'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->DateStr);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: DateStr of class  BProject */
#ifndef TOLUA_DISABLE_tolua_set_BProject_DateStr
static int tolua_set_BProject_DateStr(lua_State* tolua_S)
{
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DateStr'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DateStr = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Desc of class  BProject */
#ifndef TOLUA_DISABLE_tolua_get_BProject_Desc
static int tolua_get_BProject_Desc(lua_State* tolua_S)
{
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Desc'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Desc);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Desc of class  BProject */
#ifndef TOLUA_DISABLE_tolua_set_BProject_Desc
static int tolua_set_BProject_Desc(lua_State* tolua_S)
{
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Desc'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Desc = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetContentFrame of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_GetContentFrame00
static int tolua_BBlocks_BProject_GetContentFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetContentFrame'", NULL);
#endif
  {
   UIFrame* tolua_ret = (UIFrame*)  self->GetContentFrame();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetContentFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_GetScene00
static int tolua_BBlocks_BProject_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
  {
   Scene* tolua_ret = (Scene*)  self->GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCameraNode of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_GetCameraNode00
static int tolua_BBlocks_BProject_GetCameraNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCameraNode'", NULL);
#endif
  {
   CameraNode* tolua_ret = (CameraNode*)  self->GetCameraNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CameraNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCameraNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCameraPlayController of class  BProject */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BProject_GetCameraPlayController00
static int tolua_BBlocks_BProject_GetCameraPlayController00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BProject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BProject* self = (BProject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCameraPlayController'", NULL);
#endif
  {
   CameraPlayController* tolua_ret = (CameraPlayController*)  self->GetCameraPlayController();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CameraPlayController");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCameraPlayController'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_new00
static int tolua_BBlocks_BBlock_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBlock* tolua_ret = (BBlock*)  Mtolua_new((BBlock)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlock");
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

/* method: new_local of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_new00_local
static int tolua_BBlocks_BBlock_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BBlock* tolua_ret = (BBlock*)  Mtolua_new((BBlock)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlock");
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

/* method: delete of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_delete00
static int tolua_BBlocks_BBlock_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetState of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetState00
static int tolua_BBlocks_BBlock_SetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  BBlock::BlockState state = ((BBlock::BlockState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetState'", NULL);
#endif
  {
   self->SetState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetState of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetState00
static int tolua_BBlocks_BBlock_GetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlock* self = (const BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetState'", NULL);
#endif
  {
   BBlock::BlockState tolua_ret = (BBlock::BlockState)  self->GetState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAttachedToBlockConnector of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_IsAttachedToBlockConnector00
static int tolua_BBlocks_BBlock_IsAttachedToBlockConnector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAttachedToBlockConnector'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAttachedToBlockConnector();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAttachedToBlockConnector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEditState of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetEditState00
static int tolua_BBlocks_BBlock_SetEditState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  BBlock::EditState state = ((BBlock::EditState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEditState'", NULL);
#endif
  {
   self->SetEditState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEditState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEditState of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetEditState00
static int tolua_BBlocks_BBlock_GetEditState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlock* self = (const BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEditState'", NULL);
#endif
  {
   BBlock::EditState tolua_ret = (BBlock::EditState)  self->GetEditState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEditState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CopyAll of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_CopyAll00
static int tolua_BBlocks_BBlock_CopyAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  BBlock::EditState editState = ((BBlock::EditState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CopyAll'", NULL);
#endif
  {
   BBlock* tolua_ret = (BBlock*)  self->CopyAll(editState);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlock");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CopyAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLBlock of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetLBlock00
static int tolua_BBlocks_BBlock_SetLBlock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"LBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  LBlock* block = ((LBlock*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLBlock'", NULL);
#endif
  {
   self->SetLBlock(block);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLBlock'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetBlock of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_ResetBlock00
static int tolua_BBlocks_BBlock_ResetBlock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetBlock'", NULL);
#endif
  {
   self->ResetBlock();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetBlock'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLBlock of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetLBlock00
static int tolua_BBlocks_BBlock_GetLBlock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLBlock'", NULL);
#endif
  {
   LBlock* tolua_ret = (LBlock*)  self->GetLBlock();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LBlock");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLBlock'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSelect of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_OnSelect00
static int tolua_BBlocks_BBlock_OnSelect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  bool select = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSelect'", NULL);
#endif
  {
   self->OnSelect(select);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSelect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPickingOffset of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetPickingOffset00
static int tolua_BBlocks_BBlock_SetPickingOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Float2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  const Float2* offset = ((const Float2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPickingOffset'", NULL);
#endif
  {
   self->SetPickingOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPickingOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPickingOffset of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetPickingOffset00
static int tolua_BBlocks_BBlock_GetPickingOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlock* self = (const BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPickingOffset'", NULL);
#endif
  {
   const Float2& tolua_ret = (const Float2&)  self->GetPickingOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Float2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPickingOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShapeType of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetShapeType00
static int tolua_BBlocks_BBlock_SetShapeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  BBlock::ShapeType st = ((BBlock::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShapeType'", NULL);
#endif
  {
   self->SetShapeType(st);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShapeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShapeType of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetShapeType00
static int tolua_BBlocks_BBlock_GetShapeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlock* self = (const BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShapeType'", NULL);
#endif
  {
   BBlock::ShapeType tolua_ret = (BBlock::ShapeType)  self->GetShapeType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShapeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBoardColor of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetBoardColor00
static int tolua_BBlocks_BBlock_SetBoardColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Float4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  const Float4* color = ((const Float4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBoardColor'", NULL);
#endif
  {
   self->SetBoardColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBoardColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBoardColor of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetBoardColor00
static int tolua_BBlocks_BBlock_GetBoardColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BBlock* self = (const BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoardColor'", NULL);
#endif
  {
   const Float4& tolua_ret = (const Float4&)  self->GetBoardColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Float4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBoardColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBlockConnectorByName of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetBlockConnectorByName00
static int tolua_BBlocks_BBlock_GetBlockConnectorByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBlockConnectorByName'", NULL);
#endif
  {
   BBlockConnector* tolua_ret = (BBlockConnector*)  self->GetBlockConnectorByName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockConnector");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBlockConnectorByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCloestConnector of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetCloestConnector00
static int tolua_BBlocks_BBlock_GetCloestConnector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  BBlock* block = ((BBlock*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCloestConnector'", NULL);
#endif
  {
   BBlockConnector* tolua_ret = (BBlockConnector*)  self->GetCloestConnector(block);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BBlockConnector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCloestConnector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetConnectors of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetConnectors00
static int tolua_BBlocks_BBlock_GetConnectors00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetConnectors'", NULL);
#endif
  {
   std::vector<Pointer0<BBlockConnector> >& tolua_ret = (std::vector<Pointer0<BBlockConnector> >&)  self->GetConnectors();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"std::vector<Pointer0<BBlockConnector> >");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConnectors'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCheckButtonUseThisPointer of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_GetCheckButtonUseThisPointer00
static int tolua_BBlocks_BBlock_GetCheckButtonUseThisPointer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCheckButtonUseThisPointer'", NULL);
#endif
  {
   UICheckButton* tolua_ret = (UICheckButton*)  self->GetCheckButtonUseThisPointer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UICheckButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCheckButtonUseThisPointer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoReset of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_SetDoReset00
static int tolua_BBlocks_BBlock_SetDoReset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoReset'", NULL);
#endif
  {
   self->SetDoReset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoReset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnEvent of class  BBlock */
#ifndef TOLUA_DISABLE_tolua_BBlocks_BBlock_OnEvent00
static int tolua_BBlocks_BBlock_OnEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BBlock",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Event",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BBlock* self = (BBlock*)  tolua_tousertype(tolua_S,1,0);
  Event* ent = ((Event*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnEvent'", NULL);
#endif
  {
   self->OnEvent(ent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnEvent'.",&tolua_err);
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
   tolua_constant(tolua_S,"CT_VER_BOTTOM",UIBBlockCataFrame::CT_VER_BOTTOM);
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
   tolua_constant(tolua_S,"ST_NORMAL",UIBBlockEditToolFrame::ST_NORMAL);
   tolua_constant(tolua_S,"ST_RECYCLE",UIBBlockEditToolFrame::ST_RECYCLE);
   tolua_constant(tolua_S,"ST_MAX_TYPE",UIBBlockEditToolFrame::ST_MAX_TYPE);
   tolua_function(tolua_S,"SetShowType",tolua_BBlocks_UIBBlockEditToolFrame_SetShowType00);
   tolua_function(tolua_S,"GetShowType",tolua_BBlocks_UIBBlockEditToolFrame_GetShowType00);
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
   tolua_constant(tolua_S,"ST_PROGRESS",BBlockSprite::ST_PROGRESS);
   tolua_constant(tolua_S,"ST_WEBVIEW",BBlockSprite::ST_WEBVIEW);
   tolua_constant(tolua_S,"ST_ROUND",BBlockSprite::ST_ROUND);
   tolua_constant(tolua_S,"ST_SLIDER",BBlockSprite::ST_SLIDER);
   tolua_constant(tolua_S,"ST_FRAMELIST",BBlockSprite::ST_FRAMELIST);
   tolua_constant(tolua_S,"ST_ARDUINO",BBlockSprite::ST_ARDUINO);
   tolua_constant(tolua_S,"ST_PHOENIXFRAME",BBlockSprite::ST_PHOENIXFRAME);
   tolua_constant(tolua_S,"ST_EAI",BBlockSprite::ST_EAI);
   tolua_constant(tolua_S,"ST_MAX_TYPE",BBlockSprite::ST_MAX_TYPE);
   tolua_function(tolua_S,"new",tolua_BBlocks_BBlockSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_BBlockSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_BBlockSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_BBlockSprite_delete00);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockSprite_New00);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockSprite_New01);
   tolua_function(tolua_S,"New",tolua_BBlocks_BBlockSprite_New02);
   tolua_function(tolua_S,"GetSpriteType",tolua_BBlocks_BBlockSprite_GetSpriteType00);
   tolua_function(tolua_S,"GetSpriteTypeStr",tolua_BBlocks_BBlockSprite_GetSpriteTypeStr00);
   tolua_constant(tolua_S,"HLOT_LEFT",BBlockSprite::HLOT_LEFT);
   tolua_constant(tolua_S,"HLOT_RIGHT",BBlockSprite::HLOT_RIGHT);
   tolua_constant(tolua_S,"HLOT_CENTER",BBlockSprite::HLOT_CENTER);
   tolua_constant(tolua_S,"HLOT_STRATCH",BBlockSprite::HLOT_STRATCH);
   tolua_constant(tolua_S,"HLOT_MAX_TYPE",BBlockSprite::HLOT_MAX_TYPE);
   tolua_function(tolua_S,"SetHorLayOutType",tolua_BBlocks_BBlockSprite_SetHorLayOutType00);
   tolua_function(tolua_S,"GetHorLayOutType",tolua_BBlocks_BBlockSprite_GetHorLayOutType00);
   tolua_function(tolua_S,"SetLayoutParamHor",tolua_BBlocks_BBlockSprite_SetLayoutParamHor00);
   tolua_function(tolua_S,"GetLayoutParamHor",tolua_BBlocks_BBlockSprite_GetLayoutParamHor00);
   tolua_constant(tolua_S,"VLOT_BOTTOM",BBlockSprite::VLOT_BOTTOM);
   tolua_constant(tolua_S,"VLOT_TOP",BBlockSprite::VLOT_TOP);
   tolua_constant(tolua_S,"VLOT_CENTER",BBlockSprite::VLOT_CENTER);
   tolua_constant(tolua_S,"VLOT_STRATCH",BBlockSprite::VLOT_STRATCH);
   tolua_constant(tolua_S,"VLOT_MAX_TYPE",BBlockSprite::VLOT_MAX_TYPE);
   tolua_function(tolua_S,"SetVerLayoutType",tolua_BBlocks_BBlockSprite_SetVerLayoutType00);
   tolua_function(tolua_S,"GetVerLayoutType",tolua_BBlocks_BBlockSprite_GetVerLayoutType00);
   tolua_function(tolua_S,"SetLayoutParamVer",tolua_BBlocks_BBlockSprite_SetLayoutParamVer00);
   tolua_function(tolua_S,"GetLayoutParamVer",tolua_BBlocks_BBlockSprite_GetLayoutParamVer00);
   tolua_function(tolua_S,"SetName",tolua_BBlocks_BBlockSprite_SetName00);
   tolua_function(tolua_S,"SetDragable",tolua_BBlocks_BBlockSprite_SetDragable00);
   tolua_function(tolua_S,"IsDragable",tolua_BBlocks_BBlockSprite_IsDragable00);
   tolua_function(tolua_S,"SetDoPickFrameObject",tolua_BBlocks_BBlockSprite_SetDoPickFrameObject00);
   tolua_function(tolua_S,"IsDoPickFrameObject",tolua_BBlocks_BBlockSprite_IsDoPickFrameObject00);
   tolua_function(tolua_S,"SetLookImage",tolua_BBlocks_BBlockSprite_SetLookImage00);
   tolua_function(tolua_S,"SetLookImage1",tolua_BBlocks_BBlockSprite_SetLookImage100);
   tolua_function(tolua_S,"GetScriptGenController",tolua_BBlocks_BBlockSprite_GetScriptGenController00);
   tolua_function(tolua_S,"setName",tolua_BBlocks_BBlockSprite_setName00);
   tolua_function(tolua_S,"getName",tolua_BBlocks_BBlockSprite_getName00);
   tolua_function(tolua_S,"attachChild",tolua_BBlocks_BBlockSprite_attachChild00);
   tolua_function(tolua_S,"detachChild",tolua_BBlocks_BBlockSprite_detachChild00);
   tolua_function(tolua_S,"detachChildByName",tolua_BBlocks_BBlockSprite_detachChildByName00);
   tolua_function(tolua_S,"show",tolua_BBlocks_BBlockSprite_show00);
   tolua_function(tolua_S,"isShow",tolua_BBlocks_BBlockSprite_isShow00);
   tolua_function(tolua_S,"setColor",tolua_BBlocks_BBlockSprite_setColor00);
   tolua_function(tolua_S,"setAlpha",tolua_BBlocks_BBlockSprite_setAlpha00);
   tolua_function(tolua_S,"setFixUpdateFPS",tolua_BBlocks_BBlockSprite_setFixUpdateFPS00);
   tolua_function(tolua_S,"getFixUpdateFPS",tolua_BBlocks_BBlockSprite_getFixUpdateFPS00);
   tolua_function(tolua_S,"setText",tolua_BBlocks_BBlockSprite_setText00);
   tolua_function(tolua_S,"setTextFontSize",tolua_BBlocks_BBlockSprite_setTextFontSize00);
   tolua_function(tolua_S,"getText",tolua_BBlocks_BBlockSprite_getText00);
   tolua_function(tolua_S,"setValue",tolua_BBlocks_BBlockSprite_setValue00);
   tolua_function(tolua_S,"getValue",tolua_BBlocks_BBlockSprite_getValue00);
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
   tolua_function(tolua_S,"setSize1",tolua_BBlocks_BBlockSprite_setSize100);
   tolua_function(tolua_S,"setSizeWidthHeight",tolua_BBlocks_BBlockSprite_setSizeWidthHeight00);
   tolua_function(tolua_S,"getDragingDirX",tolua_BBlocks_BBlockSprite_getDragingDirX00);
   tolua_function(tolua_S,"getDragingDirY",tolua_BBlocks_BBlockSprite_getDragingDirY00);
   tolua_function(tolua_S,"getDragingDirSimple",tolua_BBlocks_BBlockSprite_getDragingDirSimple00);
   tolua_function(tolua_S,"getDragingPercent",tolua_BBlocks_BBlockSprite_getDragingPercent00);
   tolua_function(tolua_S,"setSliderPercent",tolua_BBlocks_BBlockSprite_setSliderPercent00);
   tolua_function(tolua_S,"setSlider100",tolua_BBlocks_BBlockSprite_setSlider10000);
   tolua_function(tolua_S,"setSlider180",tolua_BBlocks_BBlockSprite_setSlider18000);
   tolua_function(tolua_S,"getSliderPercent",tolua_BBlocks_BBlockSprite_getSliderPercent00);
   tolua_function(tolua_S,"getSlider100",tolua_BBlocks_BBlockSprite_getSlider10000);
   tolua_function(tolua_S,"getSlider180",tolua_BBlocks_BBlockSprite_getSlider18000);
   tolua_function(tolua_S,"addChooseString",tolua_BBlocks_BBlockSprite_addChooseString00);
   tolua_function(tolua_S,"chooseString",tolua_BBlocks_BBlockSprite_chooseString00);
   tolua_function(tolua_S,"chooseIndex",tolua_BBlocks_BBlockSprite_chooseIndex00);
   tolua_function(tolua_S,"getChooseString",tolua_BBlocks_BBlockSprite_getChooseString00);
   tolua_function(tolua_S,"getChooseIndex",tolua_BBlocks_BBlockSprite_getChooseIndex00);
   tolua_function(tolua_S,"setURL",tolua_BBlocks_BBlockSprite_setURL00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BBlockSystem","BBlockSystem","",NULL);
  tolua_beginmodule(tolua_S,"BBlockSystem");
   tolua_function(tolua_S,"Initlize",tolua_BBlocks_BBlockSystem_Initlize00);
   tolua_function(tolua_S,"Run",tolua_BBlocks_BBlockSystem_Run00);
   tolua_function(tolua_S,"ReStart",tolua_BBlocks_BBlockSystem_ReStart00);
   tolua_function(tolua_S,"IsRunning",tolua_BBlocks_BBlockSystem_IsRunning00);
   tolua_constant(tolua_S,"ST_BLUETOOTH",BBlockSystem::ST_BLUETOOTH);
   tolua_constant(tolua_S,"ST_SERIAL",BBlockSystem::ST_SERIAL);
   tolua_constant(tolua_S,"ST_WIFI_ROBOT",BBlockSystem::ST_WIFI_ROBOT);
   tolua_constant(tolua_S,"ST_MAX_TYPE",BBlockSystem::ST_MAX_TYPE);
   tolua_function(tolua_S,"SetSysType",tolua_BBlocks_BBlockSystem_SetSysType00);
   tolua_function(tolua_S,"SetSysType",tolua_BBlocks_BBlockSystem_SetSysType01);
   tolua_function(tolua_S,"GetSysType",tolua_BBlocks_BBlockSystem_GetSysType00);
   tolua_function(tolua_S,"setName",tolua_BBlocks_BBlockSystem_setName00);
   tolua_function(tolua_S,"getName",tolua_BBlocks_BBlockSystem_getName00);
   tolua_function(tolua_S,"setFixUpdateFPS",tolua_BBlocks_BBlockSystem_setFixUpdateFPS00);
   tolua_function(tolua_S,"getFixUpdateFPS",tolua_BBlocks_BBlockSystem_getFixUpdateFPS00);
   tolua_function(tolua_S,"show",tolua_BBlocks_BBlockSystem_show00);
   tolua_function(tolua_S,"isShow",tolua_BBlocks_BBlockSystem_isShow00);
   tolua_function(tolua_S,"setText",tolua_BBlocks_BBlockSystem_setText00);
   tolua_function(tolua_S,"getText",tolua_BBlocks_BBlockSystem_getText00);
   tolua_function(tolua_S,"setScale",tolua_BBlocks_BBlockSystem_setScale00);
   tolua_function(tolua_S,"getScale",tolua_BBlocks_BBlockSystem_getScale00);
   tolua_function(tolua_S,"setScaleXZ",tolua_BBlocks_BBlockSystem_setScaleXZ00);
   tolua_function(tolua_S,"setScaleX",tolua_BBlocks_BBlockSystem_setScaleX00);
   tolua_function(tolua_S,"setScaleZ",tolua_BBlocks_BBlockSystem_setScaleZ00);
   tolua_function(tolua_S,"getScaleX",tolua_BBlocks_BBlockSystem_getScaleX00);
   tolua_function(tolua_S,"getScaleZ",tolua_BBlocks_BBlockSystem_getScaleZ00);
   tolua_function(tolua_S,"addScale",tolua_BBlocks_BBlockSystem_addScale00);
   tolua_function(tolua_S,"setRotateXYZ",tolua_BBlocks_BBlockSystem_setRotateXYZ00);
   tolua_function(tolua_S,"setRotateX",tolua_BBlocks_BBlockSystem_setRotateX00);
   tolua_function(tolua_S,"setRotateY",tolua_BBlocks_BBlockSystem_setRotateY00);
   tolua_function(tolua_S,"setRotateZ",tolua_BBlocks_BBlockSystem_setRotateZ00);
   tolua_function(tolua_S,"getRotateX",tolua_BBlocks_BBlockSystem_getRotateX00);
   tolua_function(tolua_S,"getRotateY",tolua_BBlocks_BBlockSystem_getRotateY00);
   tolua_function(tolua_S,"getRotateZ",tolua_BBlocks_BBlockSystem_getRotateZ00);
   tolua_function(tolua_S,"addRotate",tolua_BBlocks_BBlockSystem_addRotate00);
   tolua_function(tolua_S,"setLayout",tolua_BBlocks_BBlockSystem_setLayout00);
   tolua_function(tolua_S,"setPostion",tolua_BBlocks_BBlockSystem_setPostion00);
   tolua_function(tolua_S,"setAnchorHor",tolua_BBlocks_BBlockSystem_setAnchorHor00);
   tolua_function(tolua_S,"setAnchorParamHor",tolua_BBlocks_BBlockSystem_setAnchorParamHor00);
   tolua_function(tolua_S,"setAnchorVer",tolua_BBlocks_BBlockSystem_setAnchorVer00);
   tolua_function(tolua_S,"setAnchorParamVer",tolua_BBlocks_BBlockSystem_setAnchorParamVer00);
   tolua_function(tolua_S,"move",tolua_BBlocks_BBlockSystem_move00);
   tolua_function(tolua_S,"setLayer",tolua_BBlocks_BBlockSystem_setLayer00);
   tolua_function(tolua_S,"getLayer",tolua_BBlocks_BBlockSystem_getLayer00);
   tolua_function(tolua_S,"setPivot",tolua_BBlocks_BBlockSystem_setPivot00);
   tolua_function(tolua_S,"setSize",tolua_BBlocks_BBlockSystem_setSize00);
   tolua_function(tolua_S,"setSizeWidthHeight",tolua_BBlocks_BBlockSystem_setSizeWidthHeight00);
   tolua_function(tolua_S,"getDragingDirX",tolua_BBlocks_BBlockSystem_getDragingDirX00);
   tolua_function(tolua_S,"getDragingDirY",tolua_BBlocks_BBlockSystem_getDragingDirY00);
   tolua_constant(tolua_S,"SDT_NONE",BBlockSystem::SDT_NONE);
   tolua_constant(tolua_S,"SDT_FORWARD",BBlockSystem::SDT_FORWARD);
   tolua_constant(tolua_S,"SDT_BACKWARD",BBlockSystem::SDT_BACKWARD);
   tolua_constant(tolua_S,"SDT_LEFT",BBlockSystem::SDT_LEFT);
   tolua_constant(tolua_S,"SDT_RIGHT",BBlockSystem::SDT_RIGHT);
   tolua_constant(tolua_S,"SDT_MAX_TYPE",BBlockSystem::SDT_MAX_TYPE);
   tolua_function(tolua_S,"getDragingDirSimple",tolua_BBlocks_BBlockSystem_getDragingDirSimple00);
   tolua_function(tolua_S,"getDragingPercent",tolua_BBlocks_BBlockSystem_getDragingPercent00);
   tolua_constant(tolua_S,"DT_NONE",BBlockSystem::DT_NONE);
   tolua_constant(tolua_S,"DT_FORWARD",BBlockSystem::DT_FORWARD);
   tolua_constant(tolua_S,"DT_BACKWARD",BBlockSystem::DT_BACKWARD);
   tolua_constant(tolua_S,"DT_MAX_TYPE",BBlockSystem::DT_MAX_TYPE);
   tolua_function(tolua_S,"getDragingLeftMoveType",tolua_BBlocks_BBlockSystem_getDragingLeftMoveType00);
   tolua_function(tolua_S,"getDragingLeftMoveSpeed",tolua_BBlocks_BBlockSystem_getDragingLeftMoveSpeed00);
   tolua_function(tolua_S,"getDragingRightMoveType",tolua_BBlocks_BBlockSystem_getDragingRightMoveType00);
   tolua_function(tolua_S,"getDragingRightMoveSpeed",tolua_BBlocks_BBlockSystem_getDragingRightMoveSpeed00);
   tolua_function(tolua_S,"setSliderPercent",tolua_BBlocks_BBlockSystem_setSliderPercent00);
   tolua_function(tolua_S,"setSlider100",tolua_BBlocks_BBlockSystem_setSlider10000);
   tolua_function(tolua_S,"setSlider180",tolua_BBlocks_BBlockSystem_setSlider18000);
   tolua_function(tolua_S,"getSliderPercent",tolua_BBlocks_BBlockSystem_getSliderPercent00);
   tolua_function(tolua_S,"getSlider100",tolua_BBlocks_BBlockSystem_getSlider10000);
   tolua_function(tolua_S,"getSlider180",tolua_BBlocks_BBlockSystem_getSlider18000);
   tolua_function(tolua_S,"getSlider360",tolua_BBlocks_BBlockSystem_getSlider36000);
   tolua_function(tolua_S,"addChooseString",tolua_BBlocks_BBlockSystem_addChooseString00);
   tolua_function(tolua_S,"chooseString",tolua_BBlocks_BBlockSystem_chooseString00);
   tolua_function(tolua_S,"chooseIndex",tolua_BBlocks_BBlockSystem_chooseIndex00);
   tolua_function(tolua_S,"getChooseString",tolua_BBlocks_BBlockSystem_getChooseString00);
   tolua_function(tolua_S,"getChooseIndex",tolua_BBlocks_BBlockSystem_getChooseIndex00);
   tolua_function(tolua_S,"setURL",tolua_BBlocks_BBlockSystem_setURL00);
   tolua_constant(tolua_S,"P_0",BBlockSystem::P_0);
   tolua_constant(tolua_S,"P_1",BBlockSystem::P_1);
   tolua_constant(tolua_S,"P_2",BBlockSystem::P_2);
   tolua_constant(tolua_S,"P_3",BBlockSystem::P_3);
   tolua_constant(tolua_S,"P_4",BBlockSystem::P_4);
   tolua_constant(tolua_S,"P_5",BBlockSystem::P_5);
   tolua_constant(tolua_S,"P_6",BBlockSystem::P_6);
   tolua_constant(tolua_S,"P_7",BBlockSystem::P_7);
   tolua_constant(tolua_S,"P_8",BBlockSystem::P_8);
   tolua_constant(tolua_S,"P_9",BBlockSystem::P_9);
   tolua_constant(tolua_S,"P_10",BBlockSystem::P_10);
   tolua_constant(tolua_S,"P_11",BBlockSystem::P_11);
   tolua_constant(tolua_S,"P_12",BBlockSystem::P_12);
   tolua_constant(tolua_S,"P_13",BBlockSystem::P_13);
   tolua_constant(tolua_S,"P_A0",BBlockSystem::P_A0);
   tolua_constant(tolua_S,"P_A1",BBlockSystem::P_A1);
   tolua_constant(tolua_S,"P_A2",BBlockSystem::P_A2);
   tolua_constant(tolua_S,"P_A3",BBlockSystem::P_A3);
   tolua_constant(tolua_S,"P_A4",BBlockSystem::P_A4);
   tolua_constant(tolua_S,"P_A5",BBlockSystem::P_A5);
   tolua_constant(tolua_S,"P_MAX_TYPE",BBlockSystem::P_MAX_TYPE);
   tolua_constant(tolua_S,"PM_INPUT",BBlockSystem::PM_INPUT);
   tolua_constant(tolua_S,"PM_OUTPUT",BBlockSystem::PM_OUTPUT);
   tolua_constant(tolua_S,"PM_MAX_TYPE",BBlockSystem::PM_MAX_TYPE);
   tolua_function(tolua_S,"pinMode",tolua_BBlocks_BBlockSystem_pinMode00);
   tolua_function(tolua_S,"digitalWrite",tolua_BBlocks_BBlockSystem_digitalWrite00);
   tolua_function(tolua_S,"analogWrite",tolua_BBlocks_BBlockSystem_analogWrite00);
   tolua_function(tolua_S,"digitalRead",tolua_BBlocks_BBlockSystem_digitalRead00);
   tolua_function(tolua_S,"analogRead",tolua_BBlocks_BBlockSystem_analogRead00);
   tolua_function(tolua_S,"serverInit",tolua_BBlocks_BBlockSystem_serverInit00);
   tolua_function(tolua_S,"serverWrite",tolua_BBlocks_BBlockSystem_serverWrite00);
   tolua_function(tolua_S,"distInit",tolua_BBlocks_BBlockSystem_distInit00);
   tolua_function(tolua_S,"distTest",tolua_BBlocks_BBlockSystem_distTest00);
   tolua_function(tolua_S,"getDist",tolua_BBlocks_BBlockSystem_getDist00);
   tolua_constant(tolua_S,"DT_NONE",BBlockSystem::DT_NONE);
   tolua_constant(tolua_S,"DT_FORWARD",BBlockSystem::DT_FORWARD);
   tolua_constant(tolua_S,"DT_BACKWARD",BBlockSystem::DT_BACKWARD);
   tolua_constant(tolua_S,"DT_MAX_TYPE",BBlockSystem::DT_MAX_TYPE);
   tolua_constant(tolua_S,"SDT_NONE",BBlockSystem::SDT_NONE);
   tolua_constant(tolua_S,"SDT_FORWARD",BBlockSystem::SDT_FORWARD);
   tolua_constant(tolua_S,"SDT_BACKWARD",BBlockSystem::SDT_BACKWARD);
   tolua_constant(tolua_S,"SDT_LEFT",BBlockSystem::SDT_LEFT);
   tolua_constant(tolua_S,"SDT_RIGHT",BBlockSystem::SDT_RIGHT);
   tolua_constant(tolua_S,"SDT_MAX_TYPE",BBlockSystem::SDT_MAX_TYPE);
   tolua_function(tolua_S,"vehicleInitMotoBoard",tolua_BBlocks_BBlockSystem_vehicleInitMotoBoard00);
   tolua_function(tolua_S,"vehicleInitMotoBoard4567",tolua_BBlocks_BBlockSystem_vehicleInitMotoBoard456700);
   tolua_function(tolua_S,"vehicleRun",tolua_BBlocks_BBlockSystem_vehicleRun00);
   tolua_function(tolua_S,"vehicleRunSimple",tolua_BBlocks_BBlockSystem_vehicleRunSimple00);
   tolua_function(tolua_S,"vehicleStop",tolua_BBlocks_BBlockSystem_vehicleStop00);
   tolua_function(tolua_S,"vehicleSpeedInit",tolua_BBlocks_BBlockSystem_vehicleSpeedInit00);
   tolua_function(tolua_S,"vehicleGetSpeed",tolua_BBlocks_BBlockSystem_vehicleGetSpeed00);
   tolua_function(tolua_S,"irSend",tolua_BBlocks_BBlockSystem_irSend00);
   tolua_function(tolua_S,"irRecvInit",tolua_BBlocks_BBlockSystem_irRecvInit00);
   tolua_function(tolua_S,"getIRReceive",tolua_BBlocks_BBlockSystem_getIRReceive00);
   tolua_function(tolua_S,"setCurBBlockSprite",tolua_BBlocks_BBlockSystem_setCurBBlockSprite00);
   tolua_function(tolua_S,"getCurBBlockSprite",tolua_BBlocks_BBlockSystem_getCurBBlockSprite00);
   tolua_function(tolua_S,"createSpriteFrame",tolua_BBlocks_BBlockSystem_createSpriteFrame00);
   tolua_function(tolua_S,"createSpritePicBox",tolua_BBlocks_BBlockSystem_createSpritePicBox00);
   tolua_function(tolua_S,"createSpriteButton",tolua_BBlocks_BBlockSystem_createSpriteButton00);
   tolua_function(tolua_S,"createSpriteText",tolua_BBlocks_BBlockSystem_createSpriteText00);
   tolua_function(tolua_S,"createSpriteEditBox",tolua_BBlocks_BBlockSystem_createSpriteEditBox00);
   tolua_function(tolua_S,"createSpriteComboBox",tolua_BBlocks_BBlockSystem_createSpriteComboBox00);
   tolua_function(tolua_S,"createSpriteWebView",tolua_BBlocks_BBlockSystem_createSpriteWebView00);
   tolua_function(tolua_S,"createSpriteRound",tolua_BBlocks_BBlockSystem_createSpriteRound00);
   tolua_function(tolua_S,"setBluetooth",tolua_BBlocks_BBlockSystem_setBluetooth00);
   tolua_function(tolua_S,"setSerial",tolua_BBlocks_BBlockSystem_setSerial00);
   tolua_function(tolua_S,"setSerial",tolua_BBlocks_BBlockSystem_setSerial01);
   tolua_function(tolua_S,"setWifiRobot",tolua_BBlocks_BBlockSystem_setWifiRobot00);
   tolua_function(tolua_S,"setDeviceID",tolua_BBlocks_BBlockSystem_setDeviceID00);
   tolua_function(tolua_S,"getDeviceID",tolua_BBlocks_BBlockSystem_getDeviceID00);
   tolua_function(tolua_S,"log",tolua_BBlocks_BBlockSystem_log00);
   tolua_function(tolua_S,"stringToInt",tolua_BBlocks_BBlockSystem_stringToInt00);
   tolua_function(tolua_S,"stringToFloat",tolua_BBlocks_BBlockSystem_stringToFloat00);
   tolua_function(tolua_S,"intToString",tolua_BBlocks_BBlockSystem_intToString00);
   tolua_function(tolua_S,"floatToString",tolua_BBlocks_BBlockSystem_floatToString00);
   tolua_function(tolua_S,"getStringParam",tolua_BBlocks_BBlockSystem_getStringParam00);
   tolua_function(tolua_S,"stringAdd",tolua_BBlocks_BBlockSystem_stringAdd00);
   tolua_function(tolua_S,"stringAdd",tolua_BBlocks_BBlockSystem_stringAdd01);
   tolua_function(tolua_S,"stringAdd",tolua_BBlocks_BBlockSystem_stringAdd02);
   tolua_function(tolua_S,"getYear",tolua_BBlocks_BBlockSystem_getYear00);
   tolua_function(tolua_S,"getMonth",tolua_BBlocks_BBlockSystem_getMonth00);
   tolua_function(tolua_S,"getWeek",tolua_BBlocks_BBlockSystem_getWeek00);
   tolua_function(tolua_S,"getDay",tolua_BBlocks_BBlockSystem_getDay00);
   tolua_function(tolua_S,"getDayOfWeek",tolua_BBlocks_BBlockSystem_getDayOfWeek00);
   tolua_function(tolua_S,"getTimeHour",tolua_BBlocks_BBlockSystem_getTimeHour00);
   tolua_function(tolua_S,"getTimeMinute",tolua_BBlocks_BBlockSystem_getTimeMinute00);
   tolua_function(tolua_S,"getTimeSecond",tolua_BBlocks_BBlockSystem_getTimeSecond00);
   tolua_function(tolua_S,"getTimeString",tolua_BBlocks_BBlockSystem_getTimeString00);
   tolua_function(tolua_S,"rand255",tolua_BBlocks_BBlockSystem_rand25500);
   tolua_function(tolua_S,"randZeroOne",tolua_BBlocks_BBlockSystem_randZeroOne00);
   tolua_function(tolua_S,"randZero2One",tolua_BBlocks_BBlockSystem_randZero2One00);
   tolua_function(tolua_S,"playMusic",tolua_BBlocks_BBlockSystem_playMusic00);
   tolua_function(tolua_S,"stopMusic",tolua_BBlocks_BBlockSystem_stopMusic00);
   tolua_function(tolua_S,"playCam",tolua_BBlocks_BBlockSystem_playCam00);
   tolua_function(tolua_S,"sendEvent",tolua_BBlocks_BBlockSystem_sendEvent00);
   tolua_function(tolua_S,"getEventObjectName",tolua_BBlocks_BBlockSystem_getEventObjectName00);
   tolua_function(tolua_S,"getEventDataFloat",tolua_BBlocks_BBlockSystem_getEventDataFloat00);
   tolua_function(tolua_S,"getEventDataString",tolua_BBlocks_BBlockSystem_getEventDataString00);
   tolua_function(tolua_S,"bluetoothSendString",tolua_BBlocks_BBlockSystem_bluetoothSendString00);
   tolua_function(tolua_S,"voiceStart",tolua_BBlocks_BBlockSystem_voiceStart00);
   tolua_function(tolua_S,"voiceEnd",tolua_BBlocks_BBlockSystem_voiceEnd00);
   tolua_function(tolua_S,"voiceSpeak",tolua_BBlocks_BBlockSystem_voiceSpeak00);
   tolua_function(tolua_S,"voiceSpeak",tolua_BBlocks_BBlockSystem_voiceSpeak01);
   tolua_function(tolua_S,"voiceAutoSpeakEnable",tolua_BBlocks_BBlockSystem_voiceAutoSpeakEnable00);
   tolua_function(tolua_S,"voiceIsAutoSpeakEnable",tolua_BBlocks_BBlockSystem_voiceIsAutoSpeakEnable00);
   tolua_function(tolua_S,"mp3Init",tolua_BBlocks_BBlockSystem_mp3Init00);
   tolua_function(tolua_S,"mp3Play",tolua_BBlocks_BBlockSystem_mp3Play00);
   tolua_function(tolua_S,"mp3PlayNext",tolua_BBlocks_BBlockSystem_mp3PlayNext00);
   tolua_function(tolua_S,"mp3PlayAtIndex",tolua_BBlocks_BBlockSystem_mp3PlayAtIndex00);
   tolua_function(tolua_S,"mp3SetVolume",tolua_BBlocks_BBlockSystem_mp3SetVolume00);
   tolua_function(tolua_S,"mp3Stop",tolua_BBlocks_BBlockSystem_mp3Stop00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BBManager","BBManager","",tolua_collect_BBManager);
  #else
  tolua_cclass(tolua_S,"BBManager","BBManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BBManager");
   tolua_function(tolua_S,"new",tolua_BBlocks_BBManager_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_BBManager_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_BBManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_BBManager_delete00);
   tolua_function(tolua_S,"SetPlatformTag",tolua_BBlocks_BBManager_SetPlatformTag00);
   tolua_function(tolua_S,"GetPlatformTag",tolua_BBlocks_BBManager_GetPlatformTag00);
   tolua_function(tolua_S,"SetProductTag",tolua_BBlocks_BBManager_SetProductTag00);
   tolua_function(tolua_S,"GetProductTag",tolua_BBlocks_BBManager_GetProductTag00);
   tolua_function(tolua_S,"SetSelectSprite",tolua_BBlocks_BBManager_SetSelectSprite00);
   tolua_function(tolua_S,"GetSelectSprite",tolua_BBlocks_BBManager_GetSelectSprite00);
   tolua_function(tolua_S,"SetSelectBBlockEditor",tolua_BBlocks_BBManager_SetSelectBBlockEditor00);
   tolua_function(tolua_S,"GetSelectBBlockEditor",tolua_BBlocks_BBManager_GetSelectBBlockEditor00);
   tolua_function(tolua_S,"GetCurProject",tolua_BBlocks_BBManager_GetCurProject00);
   tolua_function(tolua_S,"SetStageFrame",tolua_BBlocks_BBManager_SetStageFrame00);
   tolua_function(tolua_S,"GetStageFrame",tolua_BBlocks_BBManager_GetStageFrame00);
   tolua_function(tolua_S,"SetSmallFrame",tolua_BBlocks_BBManager_SetSmallFrame00);
   tolua_function(tolua_S,"GetSmallFrame",tolua_BBlocks_BBManager_GetSmallFrame00);
   tolua_function(tolua_S,"GetLocalProjects",tolua_BBlocks_BBManager_GetLocalProjects00);
   tolua_function(tolua_S,"GetNumProject",tolua_BBlocks_BBManager_GetNumProject00);
   tolua_function(tolua_S,"GetProjectName",tolua_BBlocks_BBManager_GetProjectName00);
   tolua_function(tolua_S,"GetProject",tolua_BBlocks_BBManager_GetProject00);
   tolua_function(tolua_S,"NewProject",tolua_BBlocks_BBManager_NewProject00);
   tolua_function(tolua_S,"SaveProject",tolua_BBlocks_BBManager_SaveProject00);
   tolua_function(tolua_S,"LoadProject",tolua_BBlocks_BBManager_LoadProject00);
   tolua_function(tolua_S,"GetAppName",tolua_BBlocks_BBManager_GetAppName00);
   tolua_function(tolua_S,"GetProjectName",tolua_BBlocks_BBManager_GetProjectName01);
   tolua_function(tolua_S,"IsHasProject",tolua_BBlocks_BBManager_IsHasProject00);
   tolua_function(tolua_S,"CloseProject",tolua_BBlocks_BBManager_CloseProject00);
   tolua_function(tolua_S,"DeleteProject",tolua_BBlocks_BBManager_DeleteProject00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BProject","BProject","Object",tolua_collect_BProject);
  #else
  tolua_cclass(tolua_S,"BProject","BProject","Object",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BProject");
   tolua_function(tolua_S,"new",tolua_BBlocks_BProject_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_BProject_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_BProject_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_BProject_delete00);
   tolua_variable(tolua_S,"DateStr",tolua_get_BProject_DateStr,tolua_set_BProject_DateStr);
   tolua_variable(tolua_S,"Desc",tolua_get_BProject_Desc,tolua_set_BProject_Desc);
   tolua_function(tolua_S,"GetContentFrame",tolua_BBlocks_BProject_GetContentFrame00);
   tolua_function(tolua_S,"GetScene",tolua_BBlocks_BProject_GetScene00);
   tolua_function(tolua_S,"GetCameraNode",tolua_BBlocks_BProject_GetCameraNode00);
   tolua_function(tolua_S,"GetCameraPlayController",tolua_BBlocks_BProject_GetCameraPlayController00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BBlock","BBlock","UIFrame",tolua_collect_BBlock);
  #else
  tolua_cclass(tolua_S,"BBlock","BBlock","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BBlock");
   tolua_function(tolua_S,"new",tolua_BBlocks_BBlock_new00);
   tolua_function(tolua_S,"new_local",tolua_BBlocks_BBlock_new00_local);
   tolua_function(tolua_S,".call",tolua_BBlocks_BBlock_new00_local);
   tolua_function(tolua_S,"delete",tolua_BBlocks_BBlock_delete00);
   tolua_constant(tolua_S,"BS_NORMAL",BBlock::BS_NORMAL);
   tolua_constant(tolua_S,"BS_PRESSED",BBlock::BS_PRESSED);
   tolua_constant(tolua_S,"BS_MAX_STEATE",BBlock::BS_MAX_STEATE);
   tolua_function(tolua_S,"SetState",tolua_BBlocks_BBlock_SetState00);
   tolua_function(tolua_S,"GetState",tolua_BBlocks_BBlock_GetState00);
   tolua_function(tolua_S,"IsAttachedToBlockConnector",tolua_BBlocks_BBlock_IsAttachedToBlockConnector00);
   tolua_constant(tolua_S,"ES_INIT",BBlock::ES_INIT);
   tolua_constant(tolua_S,"ES_PRE_EDITOR",BBlock::ES_PRE_EDITOR);
   tolua_constant(tolua_S,"ES_EDITOR",BBlock::ES_EDITOR);
   tolua_function(tolua_S,"SetEditState",tolua_BBlocks_BBlock_SetEditState00);
   tolua_function(tolua_S,"GetEditState",tolua_BBlocks_BBlock_GetEditState00);
   tolua_function(tolua_S,"CopyAll",tolua_BBlocks_BBlock_CopyAll00);
   tolua_function(tolua_S,"SetLBlock",tolua_BBlocks_BBlock_SetLBlock00);
   tolua_function(tolua_S,"ResetBlock",tolua_BBlocks_BBlock_ResetBlock00);
   tolua_function(tolua_S,"GetLBlock",tolua_BBlocks_BBlock_GetLBlock00);
   tolua_function(tolua_S,"OnSelect",tolua_BBlocks_BBlock_OnSelect00);
   tolua_function(tolua_S,"SetPickingOffset",tolua_BBlocks_BBlock_SetPickingOffset00);
   tolua_function(tolua_S,"GetPickingOffset",tolua_BBlocks_BBlock_GetPickingOffset00);
   tolua_constant(tolua_S,"ST_EVENT",BBlock::ST_EVENT);
   tolua_constant(tolua_S,"ST_FUN",BBlock::ST_FUN);
   tolua_constant(tolua_S,"ST_FUN_OUTPUT",BBlock::ST_FUN_OUTPUT);
   tolua_constant(tolua_S,"ST_FUN_OPERATOR",BBlock::ST_FUN_OPERATOR);
   tolua_constant(tolua_S,"ST_PARAM",BBlock::ST_PARAM);
   tolua_constant(tolua_S,"ST_IF",BBlock::ST_IF);
   tolua_constant(tolua_S,"ST_IFELSE",BBlock::ST_IFELSE);
   tolua_constant(tolua_S,"ST_WHILE",BBlock::ST_WHILE);
   tolua_constant(tolua_S,"ST_PROGRAM",BBlock::ST_PROGRAM);
   tolua_constant(tolua_S,"ST_PROGRAMSTART",BBlock::ST_PROGRAMSTART);
   tolua_constant(tolua_S,"ST_COROUTINE",BBlock::ST_COROUTINE);
   tolua_constant(tolua_S,"BST_MAX_TYPE",BBlock::BST_MAX_TYPE);
   tolua_function(tolua_S,"SetShapeType",tolua_BBlocks_BBlock_SetShapeType00);
   tolua_function(tolua_S,"GetShapeType",tolua_BBlocks_BBlock_GetShapeType00);
   tolua_function(tolua_S,"SetBoardColor",tolua_BBlocks_BBlock_SetBoardColor00);
   tolua_function(tolua_S,"GetBoardColor",tolua_BBlocks_BBlock_GetBoardColor00);
   tolua_function(tolua_S,"GetBlockConnectorByName",tolua_BBlocks_BBlock_GetBlockConnectorByName00);
   tolua_function(tolua_S,"GetCloestConnector",tolua_BBlocks_BBlock_GetCloestConnector00);
   tolua_function(tolua_S,"GetConnectors",tolua_BBlocks_BBlock_GetConnectors00);
   tolua_function(tolua_S,"GetCheckButtonUseThisPointer",tolua_BBlocks_BBlock_GetCheckButtonUseThisPointer00);
   tolua_function(tolua_S,"SetDoReset",tolua_BBlocks_BBlock_SetDoReset00);
   tolua_function(tolua_S,"OnEvent",tolua_BBlocks_BBlock_OnEvent00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_BBlocks (lua_State* tolua_S) {
 return tolua_BBlocks_open(tolua_S);
};
#endif

