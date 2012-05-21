/*
 *  Callback.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/16/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lapi.h"
#include "lauxlib.h"
#include "tolua++.h"
}

namespace detail
{
    // we overload push_value instead of specializing
    // because this way we can also push values that
    // are implicitly convertible to one of the types
	
    void push_value(lua_State *vm, lua_Integer n)
    {
        lua_pushinteger(vm, n);
    }
	
    void push_value(lua_State *vm, lua_Number n)
    {
        lua_pushnumber(vm, n);
    }
	
    void push_value(lua_State *vm, bool b)
    {
        lua_pushboolean(vm, b);
    }
	
    void push_value(lua_State *vm, const std::string& s)
    {
        lua_pushstring(vm, s.c_str());
    }
	
    // other overloads, for stuff like userdata or C functions
	
    // for extracting return values, we specialize a simple struct
    // as overloading on return type does not work, and we only need
    // to support a specific set of return types, as the return type
    // of a function is always specified explicitly
	
    template <typename T>
    struct value_extractor
    {
    };
	
    template <>
    struct value_extractor<lua_Integer>
    {
        static lua_Integer get(lua_State *vm)
        {
            lua_Integer val = lua_tointeger(vm, -1);
            lua_pop(vm, 1);
            return val;
        }
    };
	
    template <>
    struct value_extractor<lua_Number>
    {
        static lua_Number get(lua_State *vm)
        {
            lua_Number val = lua_tonumber(vm, -1);
            lua_pop(vm, 1);
            return val;
        }
    };
	
    template <>
    struct value_extractor<bool>
    {
        static bool get(lua_State *vm)
        {
            bool val = lua_toboolean(vm, -1);
            lua_pop(vm, 1);
            return val;
        }
    };
	
    template <>
    struct value_extractor<std::string>
    {
        static std::string get(lua_State *vm)
        {
            std::string val = lua_tostring(vm, -1);
            lua_pop(vm, 1);
            return val;
        }
    };
	
    // other specializations, for stuff like userdata or C functions
}

// the base function wrapper class
class lua_function_base
{
public:
    lua_function_base(lua_State *vm, const std::string& func)
	: m_vm(vm)
    {
        // get the function
        lua_getfield(m_vm, LUA_GLOBALSINDEX, func.c_str());
        // ensure it's a function
        if (!lua_isfunction(m_vm, -1)) {
            // throw an exception; you'd use your own exception class here
            // of course, but for sake of simplicity i use runtime_error
            lua_pop(m_vm, 1);
            //throw std::runtime_error("not a valid function");
        }
        // store it in registry for later use
        m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
    }
	
    lua_function_base(const lua_function_base& func)
	: m_vm(func.m_vm)
    {
        // copy the registry reference
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);
        m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
    }
	
    ~lua_function_base()
    {
        // delete the reference from registry
        luaL_unref(m_vm, LUA_REGISTRYINDEX, m_func);
    }
	
    lua_function_base& operator=(const lua_function_base& func)
    {
        if (this != &func) {
            m_vm = func.m_vm;
            lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);
            m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
        }
        return *this;
    }
protected:
    // the virtual machine and the registry reference to the function
    lua_State *m_vm;
    int m_func;
	
    // call the function, throws an exception on error
    void call(int args, int results)
    {
        // call it with no return values
        int status = lua_pcall(m_vm, args, results, 0);
        if (status != 0) {
            // call failed; throw an exception
            std::string error = lua_tostring(m_vm, -1);
            lua_pop(m_vm, 1);
            // in reality you'd want to use your own exception class here
            //throw std::runtime_error(error.c_str());
        }
    }
};

// the function wrapper class
template <typename Ret>
class lua_function : public lua_function_base
{
public:
    lua_function(lua_State *vm, const std::string& func)
	: lua_function_base(vm, func)
    {
    }
	
    Ret operator()()
    {
        // push the function from the registry
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        // call the function on top of the stack (throws exception on error)
        call(0);
        // return the value
        return detail::value_extractor<Ret>::get(m_vm);
    }
	
    template <typename T1>
    Ret operator()(const T1& p1)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        // push the argument and call with 1 arg
        detail::push_value(m_vm, p1);
        call(1);
        return detail::value_extractor<Ret>::get(m_vm);
    }
	
    template <typename T1, typename T2>
    Ret operator()(const T1& p1, const T2& p2)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        // push the arguments and call with 2 args
        detail::push_value(m_vm, p1);
        detail::push_value(m_vm, p2);
        call(2);
        return detail::value_extractor<Ret>::get(m_vm);
    }
	
    template <typename T1, typename T2, typename T3>
    Ret operator()(const T1& p1, const T2& p2, const T3& p3)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        detail::push_value(m_vm, p1);
        detail::push_value(m_vm, p2);
        detail::push_value(m_vm, p3);
        call(3);
        return detail::value_extractor<Ret>::get(m_vm);
    }
	
    // et cetera, provide as many overloads as you need
};

// we need to specialize the function for void return type
// as the other class would fail to compile with void as return type
template <>
class lua_function<void> : public lua_function_base
{
public:
    lua_function(lua_State *vm, const std::string& func)
	: lua_function_base(vm, func)
    {
    }
	
    void operator()()
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        call(0);
    }
	
    template <typename T1>
    void operator()(const T1& p1)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        detail::push_value(m_vm, p1);
        call(1);
    }
	
    template <typename T1, typename T2>
    void operator()(const T1& p1, const T2& p2)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        detail::push_value(m_vm, p1);
        detail::push_value(m_vm, p2);
        call(2);
    }
	
    template <typename T1, typename T2, typename T3>
    void operator()(const T1& p1, const T2& p2, const T3& p3)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        detail::push_value(m_vm, p1);
        detail::push_value(m_vm, p2);
        detail::push_value(m_vm, p3);
        call(3);
    }
	
    // et cetera, provide as many overloads as you need
};
