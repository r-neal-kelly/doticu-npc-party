/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>
#include "common/IDebugLog.h"

#include "skse64/PluginAPI.h"
#include "doticu_npcp.h"

// Variables
static IDebugLog gLog;
static PluginHandle g_handle_plugin = kPluginHandle_Invalid;
static SKSEPapyrusInterface *g_papyrus = NULL;

extern "C" {

    // Please see PluginAPI.h for more information
    bool SKSEPlugin_Query(const SKSEInterface *skse, PluginInfo *info) {
        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = "Doticu_NPC_Party";
        info->version = 1;

        g_handle_plugin = skse->GetPluginHandle();

        return true;
    }

    bool SKSEPlugin_Load(const SKSEInterface *skse) {
        // this is what allows use to use _MESSAGE and friends.
        gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcp.log");

        g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

        bool did_work = g_papyrus->Register(doticu_npcp::Register_Functions);
        if (did_work) {
            _MESSAGE("Did work.");
        } else {
            _MESSAGE("Didn't work.");
        }
        
        return true;
    }

}
