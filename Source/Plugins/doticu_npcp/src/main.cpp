/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>
#include "common/IDebugLog.h"

#include "skse64/PluginAPI.h"
#include "doticu_npcp.h"

#define DOTICU_NPCP_PRINT_PREFIX "doticu_npcp: "

static PluginHandle g_handle_plugin = kPluginHandle_Invalid;
static SKSEPapyrusInterface *g_papyrus = NULL;

extern "C" {

    // Please see PluginAPI.h for more information
    bool SKSEPlugin_Query(const SKSEInterface *skse, PluginInfo *info) {
        if (!skse || !info) {
            return false;
        }

        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = "doticu_npcp";
        info->version = 1;

        g_handle_plugin = skse->GetPluginHandle();

        return true;
    }

    bool SKSEPlugin_Load(const SKSEInterface *skse) {
        // this is what allows use to use _MESSAGE and friends. declared in doticu_npcp.h
        gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcp.log");

        g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

        if (!g_papyrus) {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not query papyrus interface.");
            return false;
        }

        bool did_work = g_papyrus->Register(doticu_npcp::Register_Functions);
        if (did_work) {
            _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added functions.");
            return true;
        } else {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not add papyrus functions.");
            return false;
        }
    }

}
