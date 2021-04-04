/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest.h"
#include "doticu_skylib/virtual_macros.h"

#include "party_followers.h"

namespace doticu_npcp { namespace Party {

    Followers_t::Save_State::Save_State(const some<Quest_t*> quest) :
        quest(quest)
    {
    }

    Followers_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Followers_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    void Followers_t::Save_State::Read()
    {
    }

    void Followers_t::Save_State::Write()
    {
    }

    String_t Followers_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_party_followers");
    }

    some<V::Class_t*> Followers_t::Class()
    {
        DEFINE_CLASS();
    }

    void Followers_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)          \
        SKYLIB_M                                                                            \
            BIND_METHOD(machine, class_name, Followers_t, METHOD_NAME_, WAITS_FOR_FRAME_,   \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                                \
        SKYLIB_W

        #undef METHOD
    }

    Followers_t::Followers_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        save_state(quest)
    {
        if (is_new_game) {

        } else {
            this->save_state.Read();
            Validate();
        }
    }

    Followers_t::Followers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest)
    {
        // update code goes here

        this->save_state.Read();
        Validate();
    }

    Followers_t::~Followers_t()
    {
    }

    void Followers_t::Before_Save()
    {
        this->save_state.Write();
    }

    void Followers_t::After_Save()
    {
    }

    void Followers_t::Validate()
    {
    }

}}
