/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/virtual_latent_id.h"
#include "doticu_skylib/virtual_macros.h"

#include "hotkeys.h"

namespace doticu_npcp {

    String_t Hotkeys_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_hotkeys");
    }

    some<V::Class_t*> Hotkeys_t::Class()
    {
        DEFINE_CLASS();
    }

    void Hotkeys_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)      \
        SKYLIB_M                                                                        \
            BIND_METHOD(machine, class_name, Hotkeys_t, METHOD_NAME_, WAITS_FOR_FRAME_, \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        METHOD("OnKeyDown", false, void, On_Key_Down, Int_t);
        METHOD("OnKeyUp", false, void, On_Key_Up, Int_t, Float_t);

        #undef METHOD
    }

    void Hotkeys_t::Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = some<unique<Callback_i<Bool_t>>>;

        class Is_In_Menu_Mode_Callback :
            public V::Callback_t
        {
        public:
            Callback callback;

        public:
            Is_In_Menu_Mode_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(V::Variable_t* result) override
            {
                Bool_t is_in_menu_mode = result ? result->As<Bool_t>() : false;
                (*this->callback)(!is_in_menu_mode);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        if (UI_t::Is_Menu_Open("Dialogue Menu")) {
            (*callback)(false);
        } else {
            UI_t::Is_In_Menu_Mode(new Is_In_Menu_Mode_Callback(std::move(callback)));
        }
    }

    Hotkeys_t::Hotkeys_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest), currently_pressed_key(-1)
    {
        // we need to as some point register for base keys. might only be necessary after load game.
        this->quest->Register_Key_Event(52, none<V::Callback_i*>());
    }

    Hotkeys_t::Hotkeys_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        Hotkeys_t(quest, false)
    {
    }

    Hotkeys_t::~Hotkeys_t()
    {
        this->currently_pressed_key = -1;
    }

    some<V::Object_t*> Hotkeys_t::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    Bool_t Hotkeys_t::On_Key_Down(V::Stack_ID_t stack_id, Int_t key_code)
    {
        const V::Latent_ID_t latent_id(stack_id);

        V::Debug_t::Create_Notification("Working.", none<V::Callback_i*>());

        return true;
    }

    Bool_t Hotkeys_t::On_Key_Up(V::Stack_ID_t stack_id, Int_t key_code, Float_t time_held)
    {
        const V::Latent_ID_t latent_id(stack_id);

        return true;
    }

    void Hotkeys_t::Before_Save()
    {
    }

    void Hotkeys_t::After_Save()
    {
    }

    void Hotkeys_t::Validate()
    {
    }

}
