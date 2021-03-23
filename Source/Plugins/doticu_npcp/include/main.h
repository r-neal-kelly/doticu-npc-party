/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "skse64/PluginAPI.h"

#include "doticu_skylib/quest.h"

#include "hotkeys.h"
#include "intrinsic.h"
#include "mcm_main.h"
#include "party_members.h"
#include "vars.h"

namespace doticu_npcp {

    class Main_t :
        public Quest_t
    {
    protected:
        static const    SKSEInterface*          SKSE;
        static const    SKSEPapyrusInterface*   SKSE_PAPYRUS;
        static const    SKSEMessagingInterface* SKSE_MESSAGING;
        static          PluginHandle            SKSE_PLUGIN_HANDLE;
        static          IDebugLog               SKSE_LOG;

    public:
        static Bool_t   SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
        static Bool_t   SKSE_Load_Plugin(const SKSEInterface* skse);
        static Bool_t   SKSE_Register_Functions(V::Machine_t* machine);

    protected:
        class NPCP_State_t
        {
        public:
            //Vars_t              vars;
            Party::Members_t    party_members;
            Hotkeys_t           hotkeys;
            //MCM::Main_t         mcm_main;

        public:
            NPCP_State_t();
            NPCP_State_t(const NPCP_State_t& other)                 = delete;
            NPCP_State_t(NPCP_State_t&& other) noexcept             = delete;
            NPCP_State_t& operator =(const NPCP_State_t& other)     = delete;
            NPCP_State_t& operator =(NPCP_State_t&& other) noexcept = delete;
            ~NPCP_State_t();
        };

    protected:
        static maybe<NPCP_State_t*> npcp_state;
        static std::mutex           npcp_state_lock;

    protected:
        static some<Main_t*>        Self();
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

        static some<V::Object_t*>   Object();

    protected:
        static Bool_t   Is_Active(std::lock_guard<std::mutex>& locker);
        static Bool_t   Is_Initialized(std::lock_guard<std::mutex>& locker);
        static Bool_t   Has_Requirements(std::lock_guard<std::mutex>& locker);

    public:
        static void Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback); // this should be moved to Hotkeys_t

    protected:
        static void     Initialize();
        static void     Before_Save();
        static void     After_Save();
        static void     Before_Load();
        static void     After_Load();

        static Bool_t   Try_Update(); // I think these two will be deleted in favor of constructors with version param
        static void     u_0_10_0();

    protected:
        void On_Init();
    };

}
