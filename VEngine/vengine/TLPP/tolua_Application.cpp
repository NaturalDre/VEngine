/*
** Lua binding: Application
** Generated automatically by tolua++-1.0.92 on 03/06/12 02:04:50.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Application_open (lua_State* tolua_S);

#include "vengine/Application.h"
using namespace VE;
/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CApplication");
}

/* method: GetGameState of class  CApplication */
#ifndef TOLUA_DISABLE_tolua_Application_CApplication_GetGameState00
static int tolua_Application_CApplication_GetGameState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CApplication",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CApplication* self = (CApplication*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGameState'", NULL);
#endif
  {
   GAMESTATE tolua_ret = (GAMESTATE)  self->GetGameState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGameState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeltaTime of class  CApplication */
#ifndef TOLUA_DISABLE_tolua_Application_CApplication_DeltaTime00
static int tolua_Application_CApplication_DeltaTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CApplication",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CApplication* self = (const CApplication*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeltaTime'", NULL);
#endif
  {
   double tolua_ret = (double)  self->DeltaTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeltaTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIngameTicks of class  CApplication */
#ifndef TOLUA_DISABLE_tolua_Application_CApplication_GetIngameTicks00
static int tolua_Application_CApplication_GetIngameTicks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CApplication",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CApplication* self = (const CApplication*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIngameTicks'", NULL);
#endif
  {
   double tolua_ret = (double)  self->GetIngameTicks();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIngameTicks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Application_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"MAINMENU",MAINMENU);
  tolua_constant(tolua_S,"GAMEPAUSED",GAMEPAUSED);
  tolua_constant(tolua_S,"GAMEINPROGRESS",GAMEINPROGRESS);
  tolua_cclass(tolua_S,"CApplication","CApplication","",NULL);
  tolua_beginmodule(tolua_S,"CApplication");
   tolua_function(tolua_S,"GetGameState",tolua_Application_CApplication_GetGameState00);
   tolua_function(tolua_S,"DeltaTime",tolua_Application_CApplication_DeltaTime00);
   tolua_function(tolua_S,"GetIngameTicks",tolua_Application_CApplication_GetIngameTicks00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Application (lua_State* tolua_S) {
 return tolua_Application_open(tolua_S);
};
#endif

