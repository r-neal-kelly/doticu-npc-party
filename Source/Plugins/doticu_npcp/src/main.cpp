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
#include <thread>
#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_head_data.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/armor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/color.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_armors.h"
#include "doticu_skylib/const_furnitures.h"
#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/const_spells.h"
#include "doticu_skylib/const_voice_types.h"
#include "doticu_skylib/const_weapons.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/location.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/os.h"
#include "doticu_skylib/package.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/voice_type.h"
#include "doticu_skylib/weapon.h"
#include "doticu_skylib/worldspace.h"

#include "chests.h"
#include "party_followers.h"
#include "party_member.h"
#include "party_member_suit_template.h"
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

    void Main_t::State::Validate()
    {
        this->party->Validate();
        this->hotkeys->Validate();
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
        this->state->Validate();
    }

    void Main_t::Create_State(const Version_t<u16> version_to_update)
    {
        Delete_State();
        this->state = new State(version_to_update);
        this->state->Validate();
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
        Party::Followers_t& followers = party.Followers();

        members.Do_Change_Suits_Automatically(true);
        members.Do_Fill_Suits_Automatically(true);
        members.Do_Fill_Suits_Strictly(true);
        members.Has_Untouchable_Invulnerables(false);

        members.Reset_Fill_Suit_Probabilities();

        some<Actor_Base_t*> vici = static_cast<Actor_Base_t*>(skylib::Game_t::Form(0x1327a)());
        for (size_t idx = 0, end = 16; idx < end; idx += 1) {
            members.Add_Member(vici);
        }

        for (size_t idx = 0, end = 1024; idx < end; idx += 1) {
            Party::Member_t member(idx);
            if (member) {
                if (doticu_skylib::Is_Odd(idx)) {
                    member.Is_Banished(false);
                    member.Is_Reanimated(false);
                    member.Is_Sneak(true);
                    member.Name(" Dark Elf Commoner ");
                    member.Combat_Style(Party::Member_Combat_Style_e::ARCHER);
                    //member.Ghost_Ability(skylib::Const::Spell::Ghost_Ability_Soul_Cairn()());
                    member.Ghost_Ability(none<Spell_t*>());
                    member.Voice_Type(skylib::Const::Voice_Type::Female_Sultry()());
                    member.Relation(Party::Member_Relation_e::ALLY);
                    member.Vitality(Party::Member_Vitality_e::INVULNERABLE);
                    member.Alpha(1.0f);

                    /*settlers.Add<Party::Sandboxer_t>(idx);
                    settlers.Allow_Hellos_To_Player<Party::Sandboxer_t>(idx, false);
                    settlers.Speed<Party::Sandboxer_t>(idx, Party::Settler_Speed_e::RUN);

                    settlers.Add<Party::Sleeper_t>(idx);
                    settlers.Bed<Party::Sleeper_t>(idx, skylib::Const::Furniture::Bedroll_01_FLR());
                    settlers.Duration_Hours<Party::Sleeper_t>(idx, 7);
                    settlers.Allow_Sitting<Party::Sleeper_t>(idx, false);

                    settlers.Add<Party::Sitter_t>(idx);

                    settlers.Add<Party::Eater_t>(idx);

                    settlers.Add<Party::Guard_t>(idx);*/

                    member.Add_Suit(Party::Member_Suit_Type_e::MEMBER, Party::Member_Suit_Template_t::Archer());

                    //followers.Add_Follower(idx);
                } else {
                    member.Is_Banished(false);
                    member.Is_Reanimated(true);
                    member.Is_Sneak(true);
                    member.Name(" Serana ");
                    member.Combat_Style(Party::Member_Combat_Style_e::ARCHER);
                    member.Ghost_Ability(none<Spell_t*>());
                    member.Voice_Type(skylib::Const::Voice_Type::Female_Unique_Serana()());
                    member.Relation(Party::Member_Relation_e::ARCHNEMESIS);
                    member.Vitality(Party::Member_Vitality_e::MORTAL);

                    member.Add_Suit(Party::Member_Suit_Type_e::MEMBER, Party::Member_Suit_Template_t::Archer());
                    member.Add_Suit(Party::Member_Suit_Type_e::SETTLEMENT, Party::Member_Suit_Template_t::Thrall());
                    member.Add_Suit(Party::Member_Suit_Type_e::HOME, Party::Member_Suit_Template_t::Member());
                    member.Add_Suit(Party::Member_Suit_Type_e::INN, Party::Member_Suit_Template_t::Member());

                    //followers.Add_Follower(idx);
                }
            }
        }

        // changed packages should be reverted in settlers type, upon state creation/deletion.

        // we should add an option to change the update interval from 2 seconds to something like 5 seconds, in case it matters.

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
            }
        };
        V::Utility_t::Wait_Out_Of_Menu(2.0f, new Wait_Callback(this));
    }
    //

}
