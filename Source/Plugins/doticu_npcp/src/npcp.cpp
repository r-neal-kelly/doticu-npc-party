/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <fstream>

#include "doticu_skylib/game.h"
#include "doticu_skylib/os.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_utility.h"

#include "consts.h"
#include "hotkeys.h"
#include "npcp.h"
#include "party.h"
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

    NPCP_t::State_t::State_t() :
        save(),

        party(new Party_t()),
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

    Bool_t NPCP_t::On_Register(some<Virtual::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        Party_t::Register_Me(machine);
        Hotkeys_t::Register_Me(machine);

        On_Log("Registered all functions.");

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
            On_Log("Initializing...");

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
                    UI_t::Create_Notification(Strings_t::THANK_YOU_FOR_PLAYING, none<Virtual::Callback_i*>());
                }
            };
            some<Wait_Callback*> wait_callback = new Wait_Callback();
            (*wait_callback)();
            Virtual::Utility_t::Wait_Out_Of_Menu(1.0f, wait_callback());

            On_Log("Initialized.");
        }
    }

    void NPCP_t::On_Before_Save_Game(const std::string& file_name)
    {
        if (Is_Valid()) {
            On_Log("Saving...");
            std::ofstream file(Game_t::Save_File_Path(file_name.c_str(), "npcp"), std::ios::out);
            if (file.is_open() && file.good()) {
                if (file.write(reinterpret_cast<char*>(&State().save), sizeof(Save_t))) {
                    if ((Party().On_Before_Save_Game(file), file.good()) &&
                        (Hotkeys().On_Before_Save_Game(file), file.good())) {
                        Byte_t last_byte = 0;
                        file.write(reinterpret_cast<char*>(&last_byte), sizeof(last_byte));
                        On_Log("Saved.");
                    } else {
                        On_Error("Failed to save.", Strings_t::ERROR_SAVE);
                    }
                } else {
                    On_Error("Failed to save.", Strings_t::ERROR_SAVE);
                }
            } else {
                On_Error("Failed to save.", Strings_t::ERROR_SAVE);
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
        if (Is_Active() && did_load_successfully) {
            std::ifstream file(Game_t::Save_File_Path(file_name.c_str(), "npcp"), std::ios::in);
            if (file.is_open()) {
                On_Log("Loading...");
                if (file.good()) {
                    Create_State();
                    if (file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t))) {
                        const Version_t<u16> save_version = Version();
                        const Version_t<u16> const_version = Consts_t::NPCP::Version::Current();
                        if (save_version == const_version) {
                            if ((Party().On_After_Load_Game(file), file.good()) &&
                                (Hotkeys().On_After_Load_Game(file), file.good())) {
                                On_Log("Loaded.");
                            } else {
                                On_Error("Failed to load.", Strings_t::ERROR_LOAD);
                                On_After_New_Game();
                            }
                        } else if (save_version < const_version) {
                            if ((Party().On_After_Load_Game(file, save_version), file.good()) &&
                                (Hotkeys().On_After_Load_Game(file, save_version), file.good())) {
                                Version(const_version);
                                UI_t::Create_Notification("NPC Party: Updated to version " +
                                                          std::to_string(const_version.major) + "." +
                                                          std::to_string(const_version.minor) + "." +
                                                          std::to_string(const_version.patch),
                                                          none<Virtual::Callback_i*>());
                                On_Log("Updated and loaded.");
                            } else {
                                On_Error("Failed to load.", Strings_t::ERROR_LOAD);
                                On_After_New_Game();
                            }
                        } else {
                            On_Error("Failed to load. File is from a newer version.", Strings_t::ERROR_LOAD_VERSION);
                            On_After_New_Game();
                        }
                    } else {
                        On_Error("Failed to load.", Strings_t::ERROR_LOAD);
                        On_After_New_Game();
                    }
                } else {
                    On_Error("Failed to load.", Strings_t::ERROR_LOAD);
                    On_After_New_Game();
                }
            } else {
                On_After_New_Game();
            }
        }
    }

    void NPCP_t::On_Before_Delete_Game(const std::string& file_name)
    {
        On_Log((std::string("Deleting save file: ") + file_name + ".npcp").c_str());
        OS_t::Delete_File(Game_t::Save_File_Path(file_name.c_str(), "npcp"));
    }

    void NPCP_t::On_Update(u32 time_stamp)
    {
        if (Is_Valid()) {
            Party().On_Update();
            Hotkeys().On_Update();
        }
    }

    void NPCP_t::On_Log(some<const char*> log)
    {
        SKYLIB_ASSERT_SOME(log);

        SKYLIB_LOG("- %s", log);
    }

    void NPCP_t::On_Error(some<const char*> error, String_t user_message)
    {
        SKYLIB_ASSERT_SOME(error);

        SKYLIB_LOG("- Error: %s", error);

        UI_t::Create_Message_Box(user_message, none<Virtual::Callback_i*>());
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

    Party_t& NPCP_t::Party()
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        return *State().party;
    }

    Hotkeys_t& NPCP_t::Hotkeys()
    {
        SKYLIB_ASSERT_SOME(Is_Valid());

        return *State().hotkeys;
    }

    NPCP_t NPCP;

}}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_skylib::doticu_npcp::NPCP);
