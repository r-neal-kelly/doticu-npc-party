/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/global.inl"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_macros.h"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

#include "consts.h"
#include "main.h"
#include "npcp.h"
#include "strings.h"

namespace doticu_npcp {

    Main_t::State_t::State_t(Bool_t is_new_game) :
        party_members(Consts_t::NPCP::Quest::Members(), is_new_game),
        hotkeys(Consts_t::NPCP::Quest::Control(), is_new_game)
    {
    }

    Main_t::State_t::State_t(const Version_t<u16> version_to_update) :
        party_members(Consts_t::NPCP::Quest::Members(), version_to_update),
        hotkeys(Consts_t::NPCP::Quest::Control(), version_to_update)
    {
    }

    Main_t::State_t::~State_t()
    {
    }

    void Main_t::State_t::Before_Save()
    {
        this->party_members.Before_Save();
        this->hotkeys.Before_Save();
    }

    void Main_t::State_t::After_Save()
    {
        this->party_members.After_Save();
        this->hotkeys.After_Save();
    }

    String_t Main_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_main");
    }

    some<V::Class_t*> Main_t::Class()
    {
        DEFINE_CLASS();
    }

    void Main_t::Register_Me(some<V::Machine_t*> machine)
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
            BIND_METHOD(machine, class_name, Main_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        #undef METHOD

        Party::Members_t::Register_Me(machine);
        Hotkeys_t::Register_Me(machine);
        //MCM::Main_t::Register_Me(machine);
    }

    Main_t::Main_t(some<Quest_t*> quest) :
        quest(quest), state(none<State_t*>())
    {
    }

    Main_t::~Main_t()
    {
    }

    some<V::Object_t*> Main_t::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    V::Variable_tt<Bool_t>& Main_t::Is_Initialized()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "is_initialized");
    }

    V::Variable_tt<Int_t>& Main_t::Major_Version()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "major_version");
    }

    V::Variable_tt<Int_t>& Main_t::Minor_Version()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "minor_version");
    }

    V::Variable_tt<Int_t>& Main_t::Patch_Version()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "patch_version");
    }

    const Version_t<u16> Main_t::Static_Version()
    {
        return Consts_t::NPCP::Version::Current();
    }

    const Version_t<u16> Main_t::Dynamic_Version()
    {
        return Version_t<u16>(static_cast<u16>(Major_Version()),
                              static_cast<u16>(Minor_Version()),
                              static_cast<u16>(Patch_Version()));
    }

    void Main_t::Dynamic_Version(const Version_t<u16> dynamic_version)
    {
        Major_Version() = static_cast<Int_t>(dynamic_version.major);
        Minor_Version() = static_cast<Int_t>(dynamic_version.minor);
        Patch_Version() = static_cast<Int_t>(dynamic_version.patch);
    }

    Vector_t<some<Quest_t*>> Main_t::Logic_Quests()
    {
        Vector_t<some<Quest_t*>> results;

        results.push_back(Consts_t::NPCP::Quest::Main());
        results.push_back(Consts_t::NPCP::Quest::Funcs());
        results.push_back(Consts_t::NPCP::Quest::Members());
        results.push_back(Consts_t::NPCP::Quest::Followers());
        results.push_back(Consts_t::NPCP::Quest::Control());

        return results;
    }

    void Main_t::Create_State(Bool_t is_new_game)
    {
        Delete_State();
        this->state = new State_t(is_new_game);
    }

    void Main_t::Create_State(const Version_t<u16> version_to_update)
    {
        Delete_State();
        this->state = new State_t(version_to_update);
    }

    void Main_t::Delete_State()
    {
        if (this->state) {
            delete this->state();
            this->state = none<State_t*>();
        }
    }

    void Main_t::New_Game()
    {
        if (!Is_Initialized()) {
            SKYLIB_LOG(NPCP_PRINT_HEAD + "Initializing...");

            Create_State(true);
            Dynamic_Version(Static_Version());
            Is_Initialized() = true;

            class Wait_Callback :
                public Callback_i<>
            {
            public:
                virtual void operator ()() override
                {
                    UI_t::Create_Notification(Strings_t::THANK_YOU_FOR_INSTALLING, none<V::Callback_i*>());
                }
            };
            some<Wait_Callback*> wait_callback = new Wait_Callback();
            V::Utility_t::Wait_Out_Of_Menu(1.0f, wait_callback());
            (*wait_callback)();

            SKYLIB_LOG(NPCP_PRINT_HEAD + "Initialized.");
        }
    }

    void Main_t::Before_Save()
    {
        if (Is_Initialized()) {
            if (this->state) {
                SKYLIB_LOG(NPCP_PRINT_HEAD + "Saving...");
                this->state->Before_Save();
                After_Save();
            } else {
                SKYLIB_LOG(NPCP_PRINT_HEAD + "Missing state, cannot save NPC Party data.");
            }
        }
    }

    void Main_t::After_Save()
    {
        class Wait_Callback :
            public V::Callback_t
        {
        public:
            virtual void operator ()(V::Variable_t*) override
            {
                Main_t& self = NPCP.Main();
                if (self.Is_Initialized()) {
                    if (self.state) {
                        self.state->After_Save();
                        SKYLIB_LOG(NPCP_PRINT_HEAD + "Saved.");
                    } else {
                        SKYLIB_LOG(NPCP_PRINT_HEAD + "Missing state, cannot finish saving NPC Party data.");
                    }
                }
            }
        };
        V::Utility_t::Wait_Even_In_Menu(0.1f, new Wait_Callback());
    }

    void Main_t::Before_Load()
    {
        Delete_State();
    }

    void Main_t::After_Load()
    {
        if (Is_Initialized()) {
            SKYLIB_LOG(NPCP_PRINT_HEAD + "Loading...");

            const Version_t<u16> static_version = Static_Version();
            const Version_t<u16> dynamic_version = Dynamic_Version();
            if (dynamic_version < static_version) {
                Create_State(dynamic_version);
                Dynamic_Version(static_version);
                UI_t::Create_Notification(NPCP_PRINT_HEAD + "Updated to version " +
                                          std::to_string(static_version.major) + "." +
                                          std::to_string(static_version.minor) + "." +
                                          std::to_string(static_version.patch),
                                          none<V::Callback_i*>());
            } else {
                Create_State(false);
            }

            SKYLIB_LOG(NPCP_PRINT_HEAD + "Loaded...");
        } else {
            New_Game();
        }
    }

}
