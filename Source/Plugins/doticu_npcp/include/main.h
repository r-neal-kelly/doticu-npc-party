/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

#include "doticu_skylib/quest.h"

#include "intrinsic.h"
#include "party_members.h"

namespace doticu_npcp {

    class Main_t :
        public Quest_t
    {
    public:
        static const    SKSEInterface*          SKSE;
        static const    SKSEPapyrusInterface*   SKSE_PAPYRUS;
        static const    SKSEMessagingInterface* SKSE_MESSAGING;
        static          PluginHandle            SKSE_PLUGIN_HANDLE;
        static          IDebugLog               SKSE_LOG;

    public:
        static Bool_t   SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
        static Bool_t   SKSE_Load_Plugin(const SKSEInterface* skse);
        static Bool_t   SKSE_Register_Functions(V::Machine_t* machine);

    public:
        static some<Main_t*>        Self();
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static some<V::Object_t*>   Object();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static Party::Members_t&    Party_Members();

    public:
        static Bool_t   Is_Active();
        static Bool_t   Is_Initialized();
        static Bool_t   Has_Requirements();
        static void     Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback);

    public:
        static void     Initialize();
        static void     Before_Save();
        static void     After_Save();
        static void     Before_Load();
        static void     After_Load();

        static Bool_t   Try_Update();
        static void     u_0_10_0();

    public:
        void On_Init();
    };

}
