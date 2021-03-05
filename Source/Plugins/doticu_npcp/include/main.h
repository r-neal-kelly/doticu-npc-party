/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

#include "doticu_skylib/quest.h"

#include "intrinsic.h"

namespace doticu_npcp {

    class Main_t : public Quest_t
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
        static Bool_t   Is_Active();
        static Bool_t   Is_Initialized();
        static Bool_t   Has_Requirements();
        static void     Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback);

    public:
        static void Initialize();
        static void Before_Save();
        static void After_Load();

    public:
        static Bool_t Try_Update();

    public:
        void On_Init();
    };

    /*
        Just some quick notes:
            We should use the owner faction on x_lists to with a custom faction indicating that the item is an outfit item.
            We should try to mark x_lists as outfit items and point to the default outfit that is on the base actor. Maybe then we won't need any blank armor.
    */

}
