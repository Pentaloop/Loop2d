// luaGen.cpp : Defines the entry point for the console application.//#include <string>#include "Event.h"extern "C"{#include "lua.h"#include "lualib.h"	//#include "lapi.h"#include "lauxlib.h"#include "tolua++.h"}#ifndef __CALLBACK_H__#define __CALLBACK_H__template <typename T1, typename T2>class  Duo {};// type that represents unused type parametersclass  NullT {};class LuaCallBase{	public:    LuaCallBase(lua_State *luaState, int func_ref)	{			L = luaState;			m_func = func_ref;	}        	LuaCallBase(lua_State *luaState, const std::string& functionName)	{		if (functionName.empty()) {			L = luaState;			if (lua_isfunction(L, -1)) {				//lua_tocfunction(L, -1)				m_func = luaL_ref(L ,LUA_REGISTRYINDEX);				/*				 lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);				 m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);				 */			}		} else {			L = luaState;						lua_getfield(L, LUA_GLOBALSINDEX, functionName.c_str());			// ensure it's a function			if (!lua_isfunction(L, -1)) {				// throw an exception; you'd use your own exception class here				// of course, but for sake of simplicity i use runtime_error				lua_pop(L, 1);				//throw std::runtime_error("not a valid function");			}			// store it in registry for later use			m_func = luaL_ref(L, LUA_REGISTRYINDEX);			/*			 lua_getglobal(L, functionName.c_str());			 */					}			}				~LuaCallBase()    {        // delete the reference from registry        luaL_unref(L, LUA_REGISTRYINDEX, m_func);    }		protected:		void push(const int &value)	{		lua_pushinteger(L, value);	}		void push(const float &value)	{		lua_pushnumber(L, value);	}		void push(const double &value)	{		lua_pushnumber(L, value);	}		void push(const std::string &value)	{		lua_pushstring(L, value.c_str());	}		void push(Event* value)	{		lua_newtable(L);		if (value) {			std::vector<std::string> keys = value->allKeys();					for (unsigned int i = 0; i < keys.size(); i++)			{				_TypedObject* pObject = value->objectForKey(keys[i]);					lua_pushstring(L, keys[i].c_str());				switch (pObject->valueType) {					case ValueTypeInt: {						push(pObject->intValue); 					}							break;					case ValueTypeFloat: {						push(pObject->floatValue); 					}							break;					case ValueTypeDouble: {						push(pObject->doubleValue); 					}							break;					case ValueTypeString: {						push(pObject->strValue); 					}							break;					default: {						tolua_pushusertype(L, pObject->object, pObject->type.c_str());					}						break;				}				lua_settable(L, -3);            }		}	}			void get(int &value) const	{		value = lua_tointeger(L, -1);	}		void get(float &value) const	{		value = lua_tonumber(L, -1);	}		void get(double &value) const	{		value = lua_tonumber(L, -1);	}		void get(std::string &value) const 	{		value = (char*)lua_tostring(L, -1);	}		void get(NullT &value) const 	{	}	protected:		lua_State *L;	int m_func;};template <typename TR,typename T1 = NullT,typename T2 = NullT,typename T3 = NullT,typename T4 = NullT>class  LuaCall : public Duo<TR, LuaCall<T1, T2, T3, T4, NullT> > , public LuaCallBase{public:		LuaCall(lua_State *L, const std::string& functionName)	: LuaCallBase(L, functionName)	{			}		TR call(T1 a1, T2 a2, T3 a3, T4 a4)	{		TR returnValue;		lua_rawgeti(L, LUA_REGISTRYINDEX, m_func);				push(a1);		push(a2);		push(a3);		push(a4);				int ret = lua_pcall(L, 4, 1, 0);		if(ret != 0)		{			throw std::string(lua_tostring(L, -1));		}				get(returnValue);				return returnValue;	}	};template <typename TR, typename T1, typename T2, typename T3>class  LuaCall<TR,T1,T2,T3,NullT> : public Duo<TR,T1> , public LuaCallBase{public:	LuaCall(lua_State *L, const std::string& functionName)	: LuaCallBase(L, functionName)	{			}		TR call(T1 a1, T2 a2, T3 a3)	{		TR returnValue;		lua_rawgeti(L, LUA_REGISTRYINDEX, m_func);				push(a1);		push(a2);		push(a3);				int ret = lua_pcall(L, 3, 1, 0);		if(ret != 0)		{			CCLog("Loop2d Error: %s", lua_tostring(L, -1));			throw std::string(lua_tostring(L, -1));		}						get(returnValue);				return returnValue;	}};// specialization to end deriving recursiontemplate <typename TR, typename T1, typename T2>class  LuaCall<TR,T1,T2,NullT,NullT> : public Duo<TR,T1> , public LuaCallBase{public:	LuaCall(lua_State *L, const std::string& functionName)	: LuaCallBase(L, functionName)	{			}		TR call(T1 a1, T2 a2)	{		TR returnValue;		lua_rawgeti(L, LUA_REGISTRYINDEX, m_func);				push(a1);		push(a2);				int ret = lua_pcall(L, 2, 1, 0);		if(ret != 0)		{			CCLog("Loop2d Error: %s", lua_tostring(L, -1));			throw std::string(lua_tostring(L, -1));		}				get(returnValue);				return returnValue;	}};// specialization to end deriving recursiontemplate <typename TR, typename T1>class  LuaCall<TR,T1,NullT,NullT,NullT> : public Duo<TR,T1> , public LuaCallBase{public:	LuaCall(lua_State *L, const std::string& functionName) : LuaCallBase(L, functionName)	{			}		TR call(T1 a1)	{		TR returnValue;		lua_rawgeti(L, LUA_REGISTRYINDEX, m_func);		push(a1);				int ret = lua_pcall(L, 1, 1, 0);		if(ret != 0)		{			CCLog("Loop2d Error: %s", lua_tostring(L, -1));			throw std::string(lua_tostring(L, -1));		}				get(returnValue);				return returnValue;	}};template <typename TR>class  LuaCall<TR,NullT,NullT,NullT,NullT> : public Duo<TR,NullT> , public LuaCallBase{public:	LuaCall(lua_State *L, const std::string& functionName)	: LuaCallBase(L, functionName)	{	}		TR call(void)	{		TR returnValue;		lua_rawgeti(L, LUA_REGISTRYINDEX, m_func);				int ret = lua_pcall(L, 0, 1, 0);		if(ret != 0)		{			CCLog("Loop2d Error: %s", lua_tostring(L, -1));			throw std::string(lua_tostring(L, -1));		}				get(returnValue);				return returnValue;	}};template <>class  LuaCall<NullT,NullT,NullT,NullT,NullT> : public LuaCallBase{public:	LuaCall(lua_State *L, const std::string& functionName)	: LuaCallBase(L, functionName)	{	}		void call(void)	{		lua_rawgeti(L, LUA_REGISTRYINDEX, m_func);		int ret = lua_pcall(L, 0, 1, 0);		if(ret != 0)		{			CCLog("Loop2d Error: %s", lua_tostring(L, -1));			throw std::string(lua_tostring(L, -1));		}	}};/* #include <iostream>  int main() {  try {	 lua_State *L;  L = luaL_newstate();  if(luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0)) { throw std::string(std::string(lua_tostring(L, -1))); }  std::cout << LuaCall<float, int, float, int, int>(L, "sum4").call(5, 1.5, 5, 5) << std::endl; std::cout << LuaCall<std::string, std::string, std::string>(L, "catenate").call("Renato", "Bianca") << std::endl; LuaCall<NullT, int>(L, "incVar").call(10); std::cout << LuaCall<int>(L, "getVar").call() << std::endl;   if(L != NULL) { lua_close(L); } } catch (const std::string &e) { std::cout << e << std::endl; }   return 0; } */#endif