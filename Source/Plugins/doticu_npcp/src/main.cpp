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
#include "hotkeys.h"
#include "main.h"
#include "mcm_main.h"
#include "npcp.h"
#include "party_main.h"
#include "strings.h"

//temp
#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_head_data.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/color.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_furnitures.h"
#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/const_spells.h"
#include "doticu_skylib/const_voice_types.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/location.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/os.h"
#include "doticu_skylib/package.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/voice_type.h"

#include "chests.h"
#include "party_member_suitcase.h"
#include "party_members.h"
#include "party_settlers.inl"
//

namespace doticu_npcp {

    Main_t::State::State(Bool_t is_new_game) :
        party(new Party::Main_t(is_new_game)),
        hotkeys(new Hotkeys_t(Consts_t::NPCP::Quest::Control(), is_new_game))
    {
    }

    Main_t::State::State(const Version_t<u16> version_to_update) :
        party(new Party::Main_t(version_to_update)),
        hotkeys(new Hotkeys_t(Consts_t::NPCP::Quest::Control(), version_to_update))
    {
    }

    Main_t::State::~State()
    {
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

        Party::Main_t::Register_Me(machine);
        Hotkeys_t::Register_Me(machine);
    }

    Main_t::Main_t(some<Quest_t*> quest) :
        quest(quest), state(none<State*>())
    {
    }

    Main_t::~Main_t()
    {
        // this needs to leak, as it's only called at the end of
        // program's life when forms are already unloaded.
        // we would crash if we tried to call its destructor.
        this->state = none<State*>();
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

    void Main_t::Create_State(Bool_t is_new_game)
    {
        Delete_State();
        this->state = new State(is_new_game);
    }

    void Main_t::Create_State(const Version_t<u16> version_to_update)
    {
        Delete_State();
        this->state = new State(version_to_update);
    }

    void Main_t::Delete_State()
    {
        if (this->state) {
            delete this->state();
            this->state = none<State*>();
        }
    }

    Party::Main_t& Main_t::Party()
    {
        SKYLIB_ASSERT_SOME(this->state);

        return *this->state->party;
    }

    Hotkeys_t& Main_t::Hotkeys()
    {
        SKYLIB_ASSERT_SOME(this->state);

        return *this->state->hotkeys;
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
                Party().Before_Save();
                Hotkeys().Before_Save();
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
                        self.Party().After_Save();
                        self.Hotkeys().After_Save();
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

            SKYLIB_LOG(NPCP_PRINT_HEAD + "Loaded.");

            Temp(); //temp
        } else {
            New_Game();
        }
    }

    //temp
    void Main_t::Temp()
    {
        Party::Main_t& party = Party();
        Party::Members_t& members = party.Members();
        Party::Settlers_t& settlers = party.Settlers();

        members.Has_Untouchable_Invulnerables(false);

        some<Actor_Base_t*> vici = static_cast<Actor_Base_t*>(skylib::Game_t::Form(0x1327a)());
        some<Actor_Base_t*> katria = static_cast<Actor_Base_t*>(skylib::Game_t::Form(0x02004D0C)());
        some<Actor_Base_t*> maven = static_cast<Actor_Base_t*>(skylib::Game_t::Form(0x1336a)());
        some<Actor_Base_t*> fjori = static_cast<Actor_Base_t*>(skylib::Game_t::Form(0x0003D725)());
        for (size_t idx = 0, end = 2; idx < end; idx += 1) {
            members.Add_Member(vici);
        }

        for (size_t idx = 0, end = 1024; idx < end; idx += 1) {
            if (members.Has_Member(idx)) {
                if (doticu_skylib::Is_Odd(idx)) {
                    members.Is_Banished(idx, false);
                    members.Is_Reanimated(idx, false);
                    members.Name(idx, " Dark Elf Commoner ");
                    members.Combat_Style(idx, Party::Member_Combat_Style_e::ARCHER);
                    members.Ghost_Ability(idx, skylib::Const::Spell::Ghost_Ability_Soul_Cairn()());
                    members.Voice_Type(idx, skylib::Const::Voice_Type::Female_Sultry()());
                    members.Relation(idx, Party::Member_Relation_e::ALLY);
                    members.Vitality(idx, Party::Member_Vitality_e::INVULNERABLE);
                    members.Alpha(idx, 0.4f);

                    settlers.Add<Party::Sandboxer_t>(idx);
                    settlers.Allow_Hellos_To_Player<Party::Sandboxer_t>(idx, false);
                    settlers.Always_Sneak<Party::Sandboxer_t>(idx, true);
                    settlers.Speed<Party::Sandboxer_t>(idx, Party::Settler_Speed_e::RUN);

                    settlers.Add<Party::Sleeper_t>(idx);
                    settlers.Always_Sneak<Party::Sleeper_t>(idx, false);
                    settlers.Bed<Party::Sleeper_t>(idx, skylib::Const::Furniture::Bedroll_01_FLR());
                    settlers.Duration_Hours<Party::Sleeper_t>(idx, 7);
                    settlers.Allow_Sitting<Party::Sleeper_t>(idx, false);

                    settlers.Add<Party::Sitter_t>(idx);

                    settlers.Add<Party::Eater_t>(idx);

                    settlers.Add<Party::Guard_t>(idx);
                } else {
                    members.Is_Banished(idx, false);
                    members.Is_Reanimated(idx, true);
                    members.Name(idx, " Serana ");
                    members.Combat_Style(idx, Party::Member_Combat_Style_e::COWARD);
                    members.Ghost_Ability(idx, none<Spell_t*>());
                    members.Voice_Type(idx, skylib::Const::Voice_Type::Female_Unique_Serana()());
                    members.Relation(idx, Party::Member_Relation_e::ARCHNEMESIS);
                    members.Vitality(idx, Party::Member_Vitality_e::MORTAL);
                }

                some<Party::Member_Suitcase_t*> suitcase = members.Suitcase(idx);
                suitcase->Copy_From(skylib::Const::Actor::Player(), Party::Member_Suit_Type_e::FOLLOWER, true);
            }
        }

        // changed packages should be reverted in settlers type, upon state creation/deletion.

        Party().Enforce();

        class Wait_Callback :
            public V::Callback_t
        {
        public:
            some<Main_t*> self;

        public:
            Wait_Callback(some<Main_t*> self) :
                self(self)
            {
            }

        public:
            virtual void operator ()(V::Variable_t*) override
            {
                self->Party().Enforce();
                V::Utility_t::Wait_Out_Of_Menu(2.0f, new Wait_Callback(self));

                Party::Members_t& members = self->Party().Members();
                for (size_t idx = 0, end = 1024; idx < end; idx += 1) {
                    if (members.Has_Member(idx)) {
                        members.Suitcase(idx)->Apply_Unto(
                            members.Actor(idx),
                            Party::Member_Suit_Type_e::FOLLOWER,
                            true,
                            false,
                            members.Pack(idx)
                        );
                        Reference_Container_t(members.Pack(idx)).Log();
                    }
                }

                //temp
                maybe<Cell_t*> cell = skylib::Const::Actor::Player()->Cell();
                if (cell) {
                    maybe<Location_t*> location = cell->Location();
                    if (location) {
                        if (location->Has_Keyword(skylib::Const::Keyword::Location_Type_City())) {
                            V::Debug_t::Create_Notification("in city", none<V::Callback_i*>());
                        } else if (location->Is_Likely_Dangerous()) {
                            V::Debug_t::Create_Notification("dangerous", none<V::Callback_i*>());
                        }
                    }
                }
                //
            }
        };
        V::Utility_t::Wait_Out_Of_Menu(2.0f, new Wait_Callback(this));
    }
    //

}
