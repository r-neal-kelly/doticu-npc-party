/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/os.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_utility.h"

#include "consts.h"
#include "hotkeys.h"
#include "npcp.h"
#include "party_main.h"
#include "strings.h"

namespace doticu_skylib { namespace doticu_npcp {

    NPCP_t::Save_t::Save_t() :
        version_major(0),
        version_minor(0),
        version_patch(0),
        version_build(0)
    {
    }

    NPCP_t::Save_t::~Save_t()
    {
    }

    void NPCP_t::Save_t::Read(std::ifstream& save)
    {
        save >> version_major;
        save >> version_minor;
        save >> version_patch;
        save >> version_build;
    }

    void NPCP_t::Save_t::Write(std::ofstream& save)
    {

    }

    NPCP_t::State_t::State_t() :
        save(),

        party(new Party::Main_t()),
        hotkeys(new Hotkeys_t())
    {
    }

    NPCP_t::State_t::~State_t()
    {
    }

    NPCP_t::NPCP_t() :
        SKSE_Plugin_t("doticu_npcp",
                      Consts_t::Skyrim::Version::Required(),
                      Operator_e::EQUAL_TO,
                      Consts_t::SKSE::Version::Minimum(),
                      Operator_e::GREATER_THAN_OR_EQUAL_TO),
        state(none<State_t*>())
    {
        SKYLIB_LOG("doticu_npc_party log:\n");
    }

    NPCP_t::~NPCP_t()
    {
        // this needs to leak, as it's only called at the end of
        // program's life when forms are already unloaded.
        // we would crash if we tried to call its destructor,
        // because some types dtors rely on those forms to be in memory.
        if (this->state) {
            this->state = none<State_t*>();
        }
    }

    Bool_t NPCP_t::On_Register(some<Virtual::Machine_t*> v_machine)
    {
        SKYLIB_ASSERT_SOME(v_machine);

        Party::Main_t::Register_Me(v_machine);
        Hotkeys_t::Register_Me(v_machine);

        return true;
    }

    void NPCP_t::On_After_Load_Data()
    {
        if (Is_Active()) {
            Start_Updating(std::chrono::milliseconds(2000));
        }
    }

    void NPCP_t::On_After_New_Game()
    {
        if (Is_Active()) {
            SKYLIB_LOG("NPC Party: Initializing...");

            Create_State();

            Version(Consts_t::NPCP::Version::Current());

            Party().On_After_New_Game();
            Hotkeys().On_After_New_Game();

            class Wait_Callback :
                public Callback_i<>
            {
            public:
                virtual void operator ()() override
                {
                    UI_t::Create_Notification(Strings_t::THANK_YOU_FOR_INSTALLING, none<Virtual::Callback_i*>());
                }
            };
            some<Wait_Callback*> wait_callback = new Wait_Callback();
            (*wait_callback)();
            Virtual::Utility_t::Wait_Out_Of_Menu(1.0f, wait_callback());

            SKYLIB_LOG("NPC Party: Initialized.");
        }
    }

    void NPCP_t::On_Before_Save_Game(const std::string& file_name)
    {
        if (Is_Valid()) {
            SKYLIB_LOG("NPC Party: Saving...");

            std::ofstream save(Game_t::Save_File_Path(file_name.c_str(), "npcp"), std::ios::out);
            if (save.is_open() && save.good()) {
                State().save.Write(save);

                Party().On_Before_Save_Game(save);
                Hotkeys().On_Before_Save_Game(save);

                SKYLIB_LOG("NPC Party: Saved.");
            } else {
                // notify the player
                SKYLIB_LOG("NPC Party: Failed to create a save file.");
            }
        }
    }

    void NPCP_t::On_After_Save_Game(const std::string& file_name)
    {
        if (Is_Valid()) {
            Party().On_After_Save_Game();
            Hotkeys().On_After_Save_Game();
        }
    }

    void NPCP_t::On_Before_Load_Game(const std::string& file_name)
    {
        if (Is_Valid()) {
            Party().On_Before_Load_Game();
            Hotkeys().On_Before_Load_Game();
        }
    }

    void NPCP_t::On_After_Load_Game(const std::string& file_name, Bool_t did_load_successfully)
    {
        if (did_load_successfully && Is_Active()) {
            std::ifstream save(Game_t::Save_File_Path(file_name.c_str(), "npcp"), std::ios::in);
            if (save.is_open() && save.good()) {
                SKYLIB_LOG("NPC Party: Loading...");

                Create_State();

                State().save.Read(save);

                const Version_t<u16> save_version = Version();
                const Version_t<u16> const_version = Consts_t::NPCP::Version::Current();
                if (save_version <= const_version) {
                    if (save_version < const_version) {
                        Party().On_After_Load_Game(save, save_version);
                        Hotkeys().On_After_Load_Game(save, save_version);

                        Version(const_version);
                        UI_t::Create_Notification("NPC Party: Updated to version " +
                                                  std::to_string(const_version.major) + "." +
                                                  std::to_string(const_version.minor) + "." +
                                                  std::to_string(const_version.patch),
                                                  none<Virtual::Callback_i*>());

                        SKYLIB_LOG("NPC Party: Updated and loaded.");
                    } else {
                        Party().On_After_Load_Game(save);
                        Hotkeys().On_After_Load_Game(save);

                        SKYLIB_LOG("NPC Party: Loaded.");
                    }
                } else {
                    Delete_State();

                    // notify the player
                    SKYLIB_LOG("NPC Party: This version cannot load a newer version's save file.");
                }
            } else {
                On_After_New_Game();
            }
        }
    }

    void NPCP_t::On_Before_Delete_Game(const std::string& file_name)
    {
        OS_t::Delete_File(Game_t::Save_File_Path(file_name.c_str(), "npcp"));
    }

    void NPCP_t::On_Update(u32 time_stamp)
    {
        if (Is_Valid()) {
            Party().Enforce();
        }
    }

    Bool_t NPCP_t::Is_Active()
    {
        return !!Consts_t::NPCP::Mod();
    }

    void NPCP_t::Create_State()
    {
        Delete_State();
        this->state = new State_t();
    }

    void NPCP_t::Delete_State()
    {
        if (this->state) {
            delete this->state();
            this->state = none<State_t*>();
        }
    }

    Bool_t NPCP_t::Is_Valid()
    {
        return Is_Active() && this->state != none<State_t*>();
    }

    NPCP_t::State_t& NPCP_t::State()
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        return *this->state;
    }

    const Version_t<u16> NPCP_t::Version()
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        return Version_t<u16>(this->state->save.version_major,
                              this->state->save.version_minor,
                              this->state->save.version_patch,
                              this->state->save.version_build);
    }

    void NPCP_t::Version(const Version_t<u16> value)
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        this->state->save.version_major = value.major;
        this->state->save.version_minor = value.minor;
        this->state->save.version_patch = value.patch;
        this->state->save.version_build = value.build;
    }

    Party::Main_t& NPCP_t::Party()
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        return *this->state->party;
    }

    Hotkeys_t& NPCP_t::Hotkeys()
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        return *this->state->hotkeys;
    }

    NPCP_t NPCP;

}}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_skylib::doticu_npcp::NPCP);
