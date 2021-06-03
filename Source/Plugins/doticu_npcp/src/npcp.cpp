/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
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

        deserialized_heavy_mods(),
        deserialized_light_mods(),

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

        serialized_heavy_mods(),
        serialized_light_mods(),

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
            Create_Serialized_Mods();
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
                if (On_Before_Save_Game(file), file.good()) {
                    On_Log("Saved.");
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
                    if (file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t)).good()) {
                        const Version_t<u16> save_version = Version();
                        const Version_t<u16> const_version = Consts_t::NPCP::Version::Current();
                        if (save_version == const_version) {
                            if (On_After_Load_Game(file), file.good()) {
                                On_Log("Loaded.");
                            } else {
                                On_Error("Failed to load.", Strings_t::ERROR_LOAD);
                                On_After_New_Game();
                            }
                        } else if (save_version < const_version) {
                            if (On_After_Load_Game(file, save_version), file.good()) {
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
        } else {
            Delete_State();
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

    void NPCP_t::On_Before_Save_Game(std::ofstream& file)
    {
        Byte_t last_byte = 0;
        (file.write(reinterpret_cast<char*>(&State().save), sizeof(Save_t)).good()) &&
            (Write_Serialized_Mods(file), file.good()) &&
            (Party().On_Before_Save_Game(file), file.good()) &&
            (Hotkeys().On_Before_Save_Game(file), file.good()) &&
            (file.write(reinterpret_cast<char*>(&last_byte), sizeof(last_byte)).good());
    }

    void NPCP_t::On_After_Load_Game(std::ifstream& file)
    {
        (Read_Deserialized_Mods(file), file.good()) &&
            (Party().On_After_Load_Game(file), file.good()) &&
            (Hotkeys().On_After_Load_Game(file), file.good());
    }

    void NPCP_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        (Read_Deserialized_Mods(file), file.good()) &&
            (Party().On_After_Load_Game(file, version_to_update), file.good()) &&
            (Hotkeys().On_After_Load_Game(file, version_to_update), file.good());
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

    void NPCP_t::Create_Serialized_Mods()
    {
        SKYLIB_ASSERT(Is_Active());

        this->serialized_heavy_mods.clear();
        this->serialized_light_mods.clear();

        const Array_t<maybe<Mod_t*>>& heavy_mods = Mod_t::Active_Heavy_Mods_2();
        for (size_t idx = 0, end = heavy_mods.Count(); idx < end; idx += 1) {
            maybe<Mod_t*> mod = heavy_mods[idx];
            if (mod) {
                const char* name = mod->Name();
                while (*name) {
                    this->serialized_heavy_mods.push_back(*name);
                    name += 1;
                }
                this->serialized_heavy_mods.push_back(0);
            }
        }

        const Array_t<maybe<Mod_t*>>& light_mods = Mod_t::Active_Light_Mods_2();
        for (size_t idx = 0, end = light_mods.Count(); idx < end; idx += 1) {
            maybe<Mod_t*> mod = light_mods[idx];
            if (mod) {
                const char* name = mod->Name();
                while (*name) {
                    this->serialized_light_mods.push_back(*name);
                    name += 1;
                }
                this->serialized_light_mods.push_back(0);
            }
        }
    }

    void NPCP_t::Write_Serialized_Mods(std::ofstream& file)
    {
        SKYLIB_ASSERT(Is_Valid());

        size_t heavy_byte_count = this->serialized_heavy_mods.size();
        size_t light_byte_count = this->serialized_light_mods.size();

        (file.write(reinterpret_cast<char*>(&heavy_byte_count), sizeof(heavy_byte_count)), file.good()) &&
            (file.write(reinterpret_cast<char*>(&light_byte_count), sizeof(light_byte_count)), file.good()) &&
            (file.write(this->serialized_heavy_mods.data(), heavy_byte_count), file.good()) &&
            (file.write(this->serialized_light_mods.data(), light_byte_count), file.good());
    }

    void NPCP_t::Read_Deserialized_Mods(std::ifstream& file)
    {
        SKYLIB_ASSERT(Is_Valid());

        size_t heavy_byte_count = 0;
        size_t light_byte_count = 0;
        if (file.read(reinterpret_cast<char*>(&heavy_byte_count), sizeof(heavy_byte_count)).good() &&
            file.read(reinterpret_cast<char*>(&light_byte_count), sizeof(light_byte_count)).good()) {
            char c = 0;
            Vector_t<const char> mod_name;
            mod_name.reserve(MAX_PATH);

            State().deserialized_heavy_mods.clear();
            State().deserialized_light_mods.clear();

            mod_name.clear();
            for (size_t idx = 0, end = heavy_byte_count; idx < end; idx += 1) {
                if (file.read(&c, sizeof(c)).good()) {
                    mod_name.push_back(c);
                    if (c == 0) {
                        State().deserialized_heavy_mods.push_back(Mod_t::Active_Heavy_Mod(mod_name.data()));
                        mod_name.clear();
                    }
                } else {
                    return;
                }
            }

            mod_name.clear();
            for (size_t idx = 0, end = light_byte_count; idx < end; idx += 1) {
                if (file.read(&c, sizeof(c)).good()) {
                    mod_name.push_back(c);
                    if (c == 0) {
                        State().deserialized_light_mods.push_back(Mod_t::Active_Light_Mod(mod_name.data()));
                        mod_name.clear();
                    }
                } else {
                    return;
                }
            }
        }
    }

    Bool_t NPCP_t::Is_Valid()
    {
        return Is_Active() && this->state != none<State_t*>();
    }

    NPCP_t::State_t& NPCP_t::State()
    {
        SKYLIB_ASSERT(Is_Valid());

        return *this->state;
    }

    const Version_t<u16> NPCP_t::Version()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Version_t<u16>(this->state->save.version_major,
                              this->state->save.version_minor,
                              this->state->save.version_patch,
                              this->state->save.version_build);
    }

    void NPCP_t::Version(const Version_t<u16> value)
    {
        SKYLIB_ASSERT(Is_Valid());

        this->state->save.version_major = value.major;
        this->state->save.version_minor = value.minor;
        this->state->save.version_patch = value.patch;
        this->state->save.version_build = value.build;
    }

    const Vector_t<maybe<Mod_t*>>& NPCP_t::Deserialized_Heavy_Mods()
    {
        SKYLIB_ASSERT(Is_Valid());

        return State().deserialized_heavy_mods;
    }

    const Vector_t<maybe<Mod_t*>>& NPCP_t::Deserialized_Light_Mods()
    {
        SKYLIB_ASSERT(Is_Valid());

        return State().deserialized_light_mods;
    }

    void NPCP_t::Write_String(std::ofstream& file, const String_t& string)
    {
        if (file.good()) {
            file.write(string, CString_t::Length(string, true));
        }
    }

    void NPCP_t::Read_String(std::ifstream& file, String_t& string)
    {
        static Vector_t<const char> buffer;
        buffer.clear();

        char c;
        while (file.good()) {
            file.read(&c, sizeof(c));
            buffer.push_back(c);
            if (c == 0) {
                string = buffer.data();
                return;
            }
        }
        string = "";
    }

    Party_t& NPCP_t::Party()
    {
        SKYLIB_ASSERT(Is_Valid());

        return *State().party;
    }

    Hotkeys_t& NPCP_t::Hotkeys()
    {
        SKYLIB_ASSERT(Is_Valid());

        return *State().hotkeys;
    }

    NPCP_t NPCP;

}}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_skylib::doticu_npcp::NPCP);
