/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64/PluginAPI.h"

#include "actor_base2.h"
#include "actor2.h"
#include "aliases.h"
#include "cell.h"
#include "follower.h"
#include "followers.h"
#include "form.h"
#include "forms.h"
#include "game.h"
#include "member.h"
#include "object_ref.h"
#include "outfit.h"
#include "papyrus.h"
#include "player.h"
#include "quest.h"
#include "string2.h"
#include "utils.h"

bool Register_Functions(VMClassRegistry *registry) {
    doticu_npcp::Actor_Base2::Exports::Register(registry);
    doticu_npcp::Actor2::Exports::Register(registry);
    doticu_npcp::Aliases::Exports::Register(registry);
    doticu_npcp::Cell::Exports::Register(registry);
    doticu_npcp::Follower::Exports::Register(registry);
    doticu_npcp::Followers::Exports::Register(registry);
    doticu_npcp::Form::Exports::Register(registry);
    doticu_npcp::Forms::Exports::Register(registry);
    doticu_npcp::Game::Exports::Register(registry);
    doticu_npcp::Member::Exports::Register(registry);
    doticu_npcp::Object_Ref::Exports::Register(registry);
    doticu_npcp::Outfit::Exports::Register(registry);
    doticu_npcp::Papyrus::Exports::Register(registry);
    doticu_npcp::Player::Exports::Register(registry);
    doticu_npcp::Quest::Exports::Register(registry);
    doticu_npcp::String2::Exports::Register(registry);
    doticu_npcp::Utils::Exports::Register(registry);

    _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added all class functions.");

    return true;
}

extern "C" {

    bool SKSEPlugin_Query(const SKSEInterface *skse, PluginInfo *info) {
        if (!skse || !info) {
            return false;
        }

        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = "doticu_npcp";
        info->version = 1;

        PluginHandle g_handle_plugin = skse->GetPluginHandle();

        return true;
    }

    bool SKSEPlugin_Load(const SKSEInterface *skse) {
        gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcp.log");

        SKSEPapyrusInterface *g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

        if (!g_papyrus) {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not query papyrus interface.");
            return false;
        }

        if (!g_papyrus->Register(Register_Functions)) {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not add Papyrus functions.");
            return false;
        }
    }

}
