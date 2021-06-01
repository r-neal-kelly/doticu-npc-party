/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <fstream>

#include "doticu_skylib/skse_plugin.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    namespace Party {

        class Main_t;

    }

    class Hotkeys_t;

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

        public:
            void    Read(std::ifstream& save);
            void    Write(std::ofstream& save);
        };

        class State_t
        {
        public:
            Save_t                              save;

            const some<unique<Party::Main_t>>   party;
            const some<unique<Hotkeys_t>>       hotkeys;

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        maybe<State_t*> state;

    public:
        NPCP_t();
        NPCP_t(const NPCP_t& other) = delete;
        NPCP_t(NPCP_t&& other) noexcept = delete;
        NPCP_t& operator =(const NPCP_t& other) = delete;
        NPCP_t& operator =(NPCP_t&& other) noexcept = delete;

    public:
        virtual         ~NPCP_t();

        virtual Bool_t  On_Register(some<Virtual::Machine_t*> v_machine) override;

        virtual void    On_After_Load_Data() override;
        virtual void    On_After_New_Game() override;
        virtual void    On_Before_Save_Game(const std::string& file_name) override;
        virtual void    On_After_Save_Game(const std::string& file_name) override;
        virtual void    On_Before_Load_Game(const std::string& file_name) override;
        virtual void    On_After_Load_Game(const std::string& file_name, Bool_t did_load_successfully) override;
        virtual void    On_Before_Delete_Game(const std::string& file_name) override;
        virtual void    On_Update(u32 time_stamp) override;

    public:
        Bool_t  Is_Active();

        void    Create_State();
        void    Delete_State();

    public:
        Bool_t                  Is_Valid();

        State_t&                State();

        const Version_t<u16>    Version();
        void                    Version(const Version_t<u16> value);

        Party::Main_t&          Party();
        Hotkeys_t&              Hotkeys();
    };

    extern NPCP_t NPCP;

}}
