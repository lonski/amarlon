#ifndef CONVERTERS
#define CONVERTERS

#include <libtcod.hpp>
#include <damage_type.h>
#include <character_class_type.h>
#include <target_type.h>
#include <actor_type.h>
#include <trap_id.h>
#include <utils.h>
#include <skill_id.h>
#include <luabind/detail/policy.hpp>
#include <modifier_type.h>
#include <fsm_state_type.h>
#include <actor_action_result.h>

/**
  * Use this mactro for quick luabind converter creating for an Enum Class
  */
#define LUABIND_DEFINE_ENUMCLASS( ENUM_TYPE ) \
    template <>\
    struct default_converter<ENUM_TYPE>\
      : native_converter_base<ENUM_TYPE>\
    {\
        static int compute_score(lua_State* L, int index)\
        {\
            return lua_type(L, index) == LUA_TNUMBER ? 0 : -1;\
        }\
        ENUM_TYPE from(lua_State* L, int index)\
        {\
            return  static_cast<ENUM_TYPE>(lua_tonumber(L, index));\
        }\
        void to(lua_State* L, ENUM_TYPE const& e)\
        {\
            lua_pushnumber(L, static_cast<int>(e));\
        }\
    };\
    template <>\
    struct default_converter<ENUM_TYPE const&>\
      : default_converter<ENUM_TYPE>\
    {};\

namespace luabind
{
    LUABIND_DEFINE_ENUMCLASS(amarlon::DamageType)
    LUABIND_DEFINE_ENUMCLASS(amarlon::CharacterClassType)
    LUABIND_DEFINE_ENUMCLASS(amarlon::TargetType)
    LUABIND_DEFINE_ENUMCLASS(amarlon::ActorType)
    LUABIND_DEFINE_ENUMCLASS(amarlon::TrapId)
    LUABIND_DEFINE_ENUMCLASS(amarlon::SkillId)
    LUABIND_DEFINE_ENUMCLASS(amarlon::GenericModifier)
    LUABIND_DEFINE_ENUMCLASS(amarlon::FSMStateType)
    LUABIND_DEFINE_ENUMCLASS(amarlon::ActorActionResult)

    //Converter for TCODColor
    template <>
    struct default_converter<TCODColor>
      : native_converter_base<TCODColor>
    {
        static int compute_score(lua_State* L, int index)
        {
            return lua_type(L, index) == LUA_TSTRING ? 0 : -1;
        }

        TCODColor from(lua_State* L, int index)
        {
            return amarlon::strToColor(lua_tostring(L, index));
        }

        void to(lua_State* L, TCODColor const& color)
        {
            lua_pushstring(L, amarlon::colorToStr(color).c_str());
        }
    };

    template <>
    struct default_converter<TCODColor const&>
      : default_converter<TCODColor>
    {};

}

#endif // CONVERTERS

