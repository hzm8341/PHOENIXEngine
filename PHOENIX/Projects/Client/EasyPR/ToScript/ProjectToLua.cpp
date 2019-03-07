/*
** Lua binding: Project
** Generated automatically by tolua++-1.0.92 on 03/08/19 02:27:05.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Project_open (lua_State* tolua_S);

#include "ProjectToLua.hpp"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_EasyPRManager (lua_State* tolua_S)
{
 EasyPRManager* self = (EasyPRManager*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Arduino");
 tolua_usertype(tolua_S,"GeneralClientConnector");
 tolua_usertype(tolua_S,"EasyPRManager");
 tolua_usertype(tolua_S,"DistTestPtr");
}

/* method: new of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_new00
static int tolua_Project_EasyPRManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EasyPRManager* tolua_ret = (EasyPRManager*)  Mtolua_new((EasyPRManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EasyPRManager");
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

/* method: new_local of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_new00_local
static int tolua_Project_EasyPRManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EasyPRManager* tolua_ret = (EasyPRManager*)  Mtolua_new((EasyPRManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EasyPRManager");
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

/* method: delete of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_delete00
static int tolua_Project_EasyPRManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Initlize of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_Initlize00
static int tolua_Project_EasyPRManager_Initlize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Ternimate of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_Ternimate00
static int tolua_Project_EasyPRManager_Ternimate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ternimate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Ternimate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ternimate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetArduino of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_GetArduino00
static int tolua_Project_EasyPRManager_GetArduino00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetArduino'", NULL);
#endif
  {
   Arduino* tolua_ret = (Arduino*)  self->GetArduino();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Arduino");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetArduino'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetURL0 of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetURL000
static int tolua_Project_EasyPRManager_SetURL000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string url0 = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetURL0'", NULL);
#endif
  {
   self->SetURL0(url0);
   tolua_pushcppstring(tolua_S,(const char*)url0);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetURL0'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetURl1 of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetURl100
static int tolua_Project_EasyPRManager_SetURl100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string url1 = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetURl1'", NULL);
#endif
  {
   self->SetURl1(url1);
   tolua_pushcppstring(tolua_S,(const char*)url1);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetURl1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_Update00
static int tolua_Project_EasyPRManager_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  float appSeconds = ((float)  tolua_tonumber(tolua_S,2,0));
  float elapsedSeconds = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(appSeconds,elapsedSeconds);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_Run00
static int tolua_Project_EasyPRManager_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'", NULL);
#endif
  {
   self->Run();
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

/* method: SetDoorState of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetDoorState00
static int tolua_Project_EasyPRManager_SetDoorState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  EasyPRManager::DoorState state = ((EasyPRManager::DoorState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoorState'", NULL);
#endif
  {
   self->SetDoorState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoorState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDoorState of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_GetDoorState00
static int tolua_Project_EasyPRManager_GetDoorState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const EasyPRManager* self = (const EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDoorState'", NULL);
#endif
  {
   EasyPRManager::DoorState tolua_ret = (EasyPRManager::DoorState)  self->GetDoorState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDoorState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoorToDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetDoorToDist00
static int tolua_Project_EasyPRManager_SetDoorToDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  float dist = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoorToDist'", NULL);
#endif
  {
   self->SetDoorToDist(dist);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoorToDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAutoAdjustingDoor of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_IsAutoAdjustingDoor00
static int tolua_Project_EasyPRManager_IsAutoAdjustingDoor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const EasyPRManager* self = (const EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAutoAdjustingDoor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAutoAdjustingDoor();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAutoAdjustingDoor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoorToPercent of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetDoorToPercent00
static int tolua_Project_EasyPRManager_SetDoorToPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  float perc = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoorToPercent'", NULL);
#endif
  {
   self->SetDoorToPercent(perc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoorToPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClosedDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetClosedDist00
static int tolua_Project_EasyPRManager_SetClosedDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  float dist = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClosedDist'", NULL);
#endif
  {
   self->SetClosedDist(dist);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClosedDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOpenedDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SetOpenedDist00
static int tolua_Project_EasyPRManager_SetOpenedDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  float dist = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOpenedDist'", NULL);
#endif
  {
   self->SetOpenedDist(dist);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOpenedDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_GetCurDist00
static int tolua_Project_EasyPRManager_GetCurDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const EasyPRManager* self = (const EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurDist'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurDist();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurDistFloat of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_GetCurDistFloat00
static int tolua_Project_EasyPRManager_GetCurDistFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const EasyPRManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const EasyPRManager* self = (const EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurDistFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCurDistFloat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurDistFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: _SetCurDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager__SetCurDist00
static int tolua_Project_EasyPRManager__SetCurDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  int dist = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function '_SetCurDist'", NULL);
#endif
  {
   self->_SetCurDist(dist);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '_SetCurDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mDistTest of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mDistTest
static int tolua_get_EasyPRManager_mDistTest(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mDistTest'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->mDistTest,"DistTestPtr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mDistTest of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mDistTest
static int tolua_set_EasyPRManager_mDistTest(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mDistTest'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DistTestPtr",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mDistTest = *((DistTestPtr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mCurDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mCurDist
static int tolua_get_EasyPRManager_mCurDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mCurDist'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mCurDist);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mCurDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mCurDist
static int tolua_set_EasyPRManager_mCurDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mCurDist'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mCurDist = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mCurDistFloat of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mCurDistFloat
static int tolua_get_EasyPRManager_mCurDistFloat(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mCurDistFloat'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mCurDistFloat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mCurDistFloat of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mCurDistFloat
static int tolua_set_EasyPRManager_mCurDistFloat(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mCurDistFloat'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mCurDistFloat = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mToDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mToDist
static int tolua_get_EasyPRManager_mToDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mToDist'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mToDist);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mToDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mToDist
static int tolua_set_EasyPRManager_mToDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mToDist'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mToDist = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mDoorState of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mDoorState
static int tolua_get_EasyPRManager_mDoorState(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mDoorState'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mDoorState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mDoorState of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mDoorState
static int tolua_set_EasyPRManager_mDoorState(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mDoorState'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mDoorState = ((EasyPRManager::DoorState) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mIsAutoAdjustingDoor of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mIsAutoAdjustingDoor
static int tolua_get_EasyPRManager_mIsAutoAdjustingDoor(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mIsAutoAdjustingDoor'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->mIsAutoAdjustingDoor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mIsAutoAdjustingDoor of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mIsAutoAdjustingDoor
static int tolua_set_EasyPRManager_mIsAutoAdjustingDoor(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mIsAutoAdjustingDoor'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mIsAutoAdjustingDoor = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mAllClosedDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mAllClosedDist
static int tolua_get_EasyPRManager_mAllClosedDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mAllClosedDist'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mAllClosedDist);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mAllClosedDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mAllClosedDist
static int tolua_set_EasyPRManager_mAllClosedDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mAllClosedDist'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mAllClosedDist = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mAllOpenedDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mAllOpenedDist
static int tolua_get_EasyPRManager_mAllOpenedDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mAllOpenedDist'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mAllOpenedDist);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mAllOpenedDist of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mAllOpenedDist
static int tolua_set_EasyPRManager_mAllOpenedDist(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mAllOpenedDist'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mAllOpenedDist = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendScreenStr of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_Project_EasyPRManager_SendScreenStr00
static int tolua_Project_EasyPRManager_SendScreenStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EasyPRManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string screen = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendScreenStr'", NULL);
#endif
  {
   self->SendScreenStr(screen);
   tolua_pushcppstring(tolua_S,(const char*)screen);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendScreenStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mGeneralClientConnector of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_get_EasyPRManager_mGeneralClientConnector_ptr
static int tolua_get_EasyPRManager_mGeneralClientConnector_ptr(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mGeneralClientConnector'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->mGeneralClientConnector,"GeneralClientConnector");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mGeneralClientConnector of class  EasyPRManager */
#ifndef TOLUA_DISABLE_tolua_set_EasyPRManager_mGeneralClientConnector_ptr
static int tolua_set_EasyPRManager_mGeneralClientConnector_ptr(lua_State* tolua_S)
{
  EasyPRManager* self = (EasyPRManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mGeneralClientConnector'",NULL);
  if (!tolua_isusertype(tolua_S,2,"GeneralClientConnector",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mGeneralClientConnector = ((GeneralClientConnector*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Project_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"EasyPRManager","EasyPRManager","",tolua_collect_EasyPRManager);
  #else
  tolua_cclass(tolua_S,"EasyPRManager","EasyPRManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"EasyPRManager");
   tolua_function(tolua_S,"new",tolua_Project_EasyPRManager_new00);
   tolua_function(tolua_S,"new_local",tolua_Project_EasyPRManager_new00_local);
   tolua_function(tolua_S,".call",tolua_Project_EasyPRManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_Project_EasyPRManager_delete00);
   tolua_function(tolua_S,"Initlize",tolua_Project_EasyPRManager_Initlize00);
   tolua_function(tolua_S,"Ternimate",tolua_Project_EasyPRManager_Ternimate00);
   tolua_function(tolua_S,"GetArduino",tolua_Project_EasyPRManager_GetArduino00);
   tolua_function(tolua_S,"SetURL0",tolua_Project_EasyPRManager_SetURL000);
   tolua_function(tolua_S,"SetURl1",tolua_Project_EasyPRManager_SetURl100);
   tolua_function(tolua_S,"Update",tolua_Project_EasyPRManager_Update00);
   tolua_function(tolua_S,"Run",tolua_Project_EasyPRManager_Run00);
   tolua_constant(tolua_S,"DS_STOP",EasyPRManager::DS_STOP);
   tolua_constant(tolua_S,"DS_OPENING",EasyPRManager::DS_OPENING);
   tolua_constant(tolua_S,"DS_CLOSEING",EasyPRManager::DS_CLOSEING);
   tolua_constant(tolua_S,"DS_MAX_TYPE",EasyPRManager::DS_MAX_TYPE);
   tolua_function(tolua_S,"SetDoorState",tolua_Project_EasyPRManager_SetDoorState00);
   tolua_function(tolua_S,"GetDoorState",tolua_Project_EasyPRManager_GetDoorState00);
   tolua_function(tolua_S,"SetDoorToDist",tolua_Project_EasyPRManager_SetDoorToDist00);
   tolua_function(tolua_S,"IsAutoAdjustingDoor",tolua_Project_EasyPRManager_IsAutoAdjustingDoor00);
   tolua_function(tolua_S,"SetDoorToPercent",tolua_Project_EasyPRManager_SetDoorToPercent00);
   tolua_function(tolua_S,"SetClosedDist",tolua_Project_EasyPRManager_SetClosedDist00);
   tolua_function(tolua_S,"SetOpenedDist",tolua_Project_EasyPRManager_SetOpenedDist00);
   tolua_function(tolua_S,"GetCurDist",tolua_Project_EasyPRManager_GetCurDist00);
   tolua_function(tolua_S,"GetCurDistFloat",tolua_Project_EasyPRManager_GetCurDistFloat00);
   tolua_function(tolua_S,"_SetCurDist",tolua_Project_EasyPRManager__SetCurDist00);
   tolua_variable(tolua_S,"mDistTest",tolua_get_EasyPRManager_mDistTest,tolua_set_EasyPRManager_mDistTest);
   tolua_variable(tolua_S,"mCurDist",tolua_get_EasyPRManager_mCurDist,tolua_set_EasyPRManager_mCurDist);
   tolua_variable(tolua_S,"mCurDistFloat",tolua_get_EasyPRManager_mCurDistFloat,tolua_set_EasyPRManager_mCurDistFloat);
   tolua_variable(tolua_S,"mToDist",tolua_get_EasyPRManager_mToDist,tolua_set_EasyPRManager_mToDist);
   tolua_variable(tolua_S,"mDoorState",tolua_get_EasyPRManager_mDoorState,tolua_set_EasyPRManager_mDoorState);
   tolua_variable(tolua_S,"mIsAutoAdjustingDoor",tolua_get_EasyPRManager_mIsAutoAdjustingDoor,tolua_set_EasyPRManager_mIsAutoAdjustingDoor);
   tolua_variable(tolua_S,"mAllClosedDist",tolua_get_EasyPRManager_mAllClosedDist,tolua_set_EasyPRManager_mAllClosedDist);
   tolua_variable(tolua_S,"mAllOpenedDist",tolua_get_EasyPRManager_mAllOpenedDist,tolua_set_EasyPRManager_mAllOpenedDist);
   tolua_function(tolua_S,"SendScreenStr",tolua_Project_EasyPRManager_SendScreenStr00);
   tolua_variable(tolua_S,"mGeneralClientConnector",tolua_get_EasyPRManager_mGeneralClientConnector_ptr,tolua_set_EasyPRManager_mGeneralClientConnector_ptr);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Project (lua_State* tolua_S) {
 return tolua_Project_open(tolua_S);
};
#endif

