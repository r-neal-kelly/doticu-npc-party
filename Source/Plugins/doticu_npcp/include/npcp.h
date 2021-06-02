/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <fstream>

#include "doticu_skylib/skse_plugin.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Hotkeys_t;
    class Party_t;

    class NPCP_t :
        public SKSE_Plugin_t
    {
    public:
        class Save_t
        {
        public:
            u16 version_major;
            u16 version_minor;
            u16 version_patch;
            u16 version_build;

        public:
            Save_t();
            Save_t(const Save_t& other) = delete;
            Save_t(Save_t&& other) noexcept = delete;
            Save_t& operator =(const Save_t& other) = delete;
            Save_t& operator =(Save_t&& other) noexcept = delete;
            ~Save_t();
        };

        class State_t
        {
        public:
            Save_t                          save;

            Vector_t<maybe<Mod_t*>>         deserialized_heavy_mods;
            Vector_t<maybe<Mod_t*>>         deserialized_light_mods;

            const some<unique<Party_t>>     party;
            const some<unique<Hotkeys_t>>   hotkeys;

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        Vector_t<const char>    serialized_heavy_mods;
        Vector_t<const char>    serialized_light_mods;

        maybe<State_t*>         state;

    public:
        NPCP_t();
        NPCP_t(const NPCP_t& other) = delete;
        NPCP_t(NPCP_t&& other) noexcept = delete;
        NPCP_t& operator =(const NPCP_t& other) = delete;
        NPCP_t& operator =(NPCP_t&& other) noexcept = delete;

    public:
        virtual         ~NPCP_t();

        virtual Bool_t  On_Register(some<Virtual::Machine_t*> machine) override;

        virtual void    On_After_Load_Data() override;
        virtual void    On_After_New_Game() override;
        virtual void    On_Before_Save_Game(const std::string& file_name) override;
        virtual void    On_After_Save_Game(const std::string& file_name) override;
        virtual void    On_Before_Load_Game(const std::string& file_name) override;
        virtual void    On_After_Load_Game(const std::string& file_name, Bool_t did_load_successfully) override;
        virtual void    On_Before_Delete_Game(const std::string& file_name) override;
        virtual void    On_Update(u32 time_stamp) override;

        virtual void    On_Before_Save_Game(std::ofstream& file);
        virtual void    On_After_Load_Game(std::ifstream& file);
        virtual void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);

        virtual void    On_Log(some<const char*> log);
        virtual void    On_Error(some<const char*> error, String_t user_message);

    public:
        Bool_t  Is_Active();

        void    Create_State();
        void    Delete_State();

        void    Create_Serialized_Mods();
        void    Write_Serialized_Mods(std::ofstream& file);
        void    Read_Deserialized_Mods(std::ifstream& file);

    public:
        Bool_t                          Is_Valid();

        State_t&                        State();

        const Version_t<u16>            Version();
        void                            Version(const Version_t<u16> value);

        const Vector_t<maybe<Mod_t*>>   Deserialized_Heavy_Mods();
        const Vector_t<maybe<Mod_t*>>   Deserialized_Light_Mods();

        Party_t&                        Party();
        Hotkeys_t&                      Hotkeys();
    };

    extern NPCP_t NPCP;

}}
