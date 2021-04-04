/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest.h"
#include "doticu_skylib/virtual_macros.h"

#include "party_displays.h"

namespace doticu_npcp { namespace Party {

    Displays_t::Save_State::Save_State(const some<Quest_t*> quest) :
        quest(quest),

        limit(DEFAULT_LIMIT)
    {
    }

    Displays_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Displays_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    V::Variable_tt<Int_t>& Displays_t::Save_State::Limit()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "limit");
    }

    void Displays_t::Save_State::Read()
    {
        this->limit = Limit();
    }

    void Displays_t::Save_State::Write()
    {
        Limit() = static_cast<Int_t>(this->limit);
    }

    String_t Displays_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_party_displays");
    }

    some<V::Class_t*> Displays_t::Class()
    {
        DEFINE_CLASS();
    }

    void Displays_t::Register_Me(some<V::Machine_t*> machine)
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
            BIND_METHOD(machine, class_name, Displays_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                                \
        SKYLIB_W

        #undef METHOD
    }

    Displays_t::Displays_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        save_state(quest)
    {
        if (is_new_game) {

        } else {
            this->save_state.Read();
            Validate();
        }
    }

    Displays_t::Displays_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest)
    {
        // update code goes here

        this->save_state.Read();
        Validate();
    }

    Displays_t::~Displays_t()
    {
    }

    void Displays_t::Before_Save()
    {
        this->save_state.Write();
    }

    void Displays_t::After_Save()
    {
    }

    void Displays_t::Validate()
    {
        if (this->save_state.limit < 1) {
            this->save_state.limit = 1;
        } else if (this->save_state.limit > MAX_DISPLAYS) {
            this->save_state.limit = MAX_DISPLAYS;
        }
    }

}}
