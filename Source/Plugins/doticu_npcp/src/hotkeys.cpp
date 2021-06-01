/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/virtual_latent_id.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "hotkeys.h"

namespace doticu_skylib { namespace doticu_npcp {

    Hotkeys_t::Save_t::Save_t() :
        global_dialogue_menu{ 0, 0, 0, 0 },

        actor_toggle_member{ 0, 0, 0, 0 },
        actor_toggle_move{ 0, 0, 0, 0 },
        actor_move_nearer{ 0, 0, 0, 0 },
        actor_move_farther{ 0, 0, 0, 0 },
        actor_move_rotate_left{ 0, 0, 0, 0 },
        actor_move_rotate_right{ 0, 0, 0, 0 },
        actor_has_base{ 0, 0, 0, 0 },
        actor_count_base{ 0, 0, 0, 0 },
        actor_has_head{ 0, 0, 0, 0 },
        actor_count_heads{ 0, 0, 0, 0 },

        member_toggle_clone{ 0, 0, 0, 0 },
        member_toggle_settler{ 0, 0, 0, 0 },
        member_toggle_thrall{ 0, 0, 0, 0 },
        member_toggle_immobile{ 0, 0, 0, 0 },
        member_toggle_paralyzed{ 0, 0, 0, 0 },
        member_toggle_follower{ 0, 0, 0, 0 },

        follower_toggle_sneak{ 0, 0, 0, 0 },
        follower_toggle_saddler{ 0, 0, 0, 0 },

        members_toggle_display{ 0, 0, 0, 0 },
        members_display_previous{ 0, 0, 0, 0 },
        members_display_next{ 0, 0, 0, 0 },

        followers_summon_all{ 0, 0, 0, 0 },
        followers_summon_mobile{ 0, 0, 0, 0 },
        followers_summon_immobile{ 0, 0, 0, 0 },
        followers_settle{ 0, 0, 0, 0 },
        followers_unsettle{ 0, 0, 0, 0 },
        followers_mobilize{ 0, 0, 0, 0 },
        followers_immobilize{ 0, 0, 0, 0 },
        followers_sneak{ 0, 0, 0, 0 },
        followers_unsneak{ 0, 0, 0, 0 },
        followers_saddle{ 0, 0, 0, 0 },
        followers_unsaddle{ 0, 0, 0, 0 },
        followers_resurrect{ 0, 0, 0, 0 }
    {
    }

    Hotkeys_t::Save_t::~Save_t()
    {
    }

    Hotkeys_t::State_t::State_t() :
        save(),

        quest(Consts_t::NPCP::Quest::Control()),
        currently_pressed_key(0)
    {
    }

    Hotkeys_t::State_t::~State_t()
    {
    }

    String_t Hotkeys_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_hotkeys");
    }

    some<Virtual::Class_t*> Hotkeys_t::Class()
    {
        DEFINE_CLASS();
    }

    void Hotkeys_t::Register_Me(some<Virtual::Machine_t*> machine)
    {
        using Type_t = Hotkeys_t;

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
            BIND_METHOD(machine, class_name, Type_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
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
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Is_In_Menu_Mode_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t* result) override
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

    Hotkeys_t::Hotkeys_t() :
        state()
    {
        // we need to as some point register for base keys. might only be necessary after load game.
        State().quest->Register_Key_Event(52, none<Virtual::Callback_i*>());
    }

    Hotkeys_t::~Hotkeys_t()
    {
    }

    void Hotkeys_t::On_After_New_Game()
    {
    }

    void Hotkeys_t::On_Before_Save_Game(std::ofstream& file)
    {
        file.write(reinterpret_cast<char*>(&State().save), sizeof(Save_t));
    }

    void Hotkeys_t::On_After_Save_Game()
    {
    }

    void Hotkeys_t::On_Before_Load_Game()
    {
    }

    void Hotkeys_t::On_After_Load_Game(std::ifstream& file)
    {
        file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t));
    }

    void Hotkeys_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        On_After_Load_Game(file);
    }

    void Hotkeys_t::On_Update()
    {
    }

    Hotkeys_t::State_t& Hotkeys_t::State()
    {
        return this->state;
    }

    some<Virtual::Object_t*> Hotkeys_t::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(State().quest());
    }

    Bool_t Hotkeys_t::On_Key_Down(Virtual::Stack_ID_t stack_id, Int_t key_code)
    {
        const Virtual::Latent_ID_t latent_id(stack_id);

        Virtual::Debug_t::Create_Notification("Working.", none<Virtual::Callback_i*>());

        return true;
    }

    Bool_t Hotkeys_t::On_Key_Up(Virtual::Stack_ID_t stack_id, Int_t key_code, Float_t time_held)
    {
        const Virtual::Latent_ID_t latent_id(stack_id);

        return true;
    }

}}
