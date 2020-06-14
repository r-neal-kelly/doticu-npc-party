/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "actor_base2.h"
#include "actor2.h"
#include "aliases.h"
#include "cell.h"
#include "follower.h"
#include "followers.h"
#include "form.h"
#include "forms.h"
#include "game.h"
#include "main.h"
#include "member.h"
#include "members.h"
#include "object_ref.h"
#include "outfit.h"
#include "package.h"
#include "papyrus.h"
#include "player.h"
#include "quest.h"
#include "string2.h"
#include "utils.h"

namespace doticu_npcp { namespace Main {

    bool Query_Plugin(const SKSEInterface *skse, PluginInfo *info);
    bool Load_Plugin(const SKSEInterface *skse);
    bool Register_Functions(VMClassRegistry *registry);

}}

namespace doticu_npcp { namespace Main {

    bool Query_Plugin(const SKSEInterface *skse, PluginInfo *info) {
        if (!skse || !info) {
            return false;
        }

        info->infoVersion = PluginInfo::kInfoVersion; // constant
        info->name = "doticu_npcp"; // exposed to plugin query API
        info->version = 1; // exposed to scripts

        if (PACKED_SKSE_VERSION < MAKE_EXE_VERSION(2, 0, 17)) {
            return false;
        }

        return true;
    }

    bool Load_Plugin(const SKSEInterface *skse) {
        g_skse = skse;
        g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);
        g_plugin_handle = skse->GetPluginHandle();

        if (!g_skse) {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not get skse interface.");
            return false;
        }

        if (!g_papyrus) {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not get papyrus interface.");
            return false;
        }

        if (!g_papyrus->Register(Register_Functions)) {
            _FATALERROR(DOTICU_NPCP_PRINT_PREFIX "Could not add Papyrus functions.");
            return false;
        }

        g_log.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcp.log");

        return true;
    }

    bool Register_Functions(VMClassRegistry *registry) {
        #define REGISTER_NAMESPACE(NAMESPACE_)                                                  \
        M                                                                                       \
            if (!doticu_npcp::NAMESPACE_::Exports::Register(registry)) {                        \
                _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Failed to add " #NAMESPACE_ " functions.");  \
                return false;                                                                   \
            } else {                                                                            \
                _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added " #NAMESPACE_ " functions.");          \
            }                                                                                   \
        W

        REGISTER_NAMESPACE(Actor_Base2);
        REGISTER_NAMESPACE(Actor2);
        REGISTER_NAMESPACE(Aliases);
        REGISTER_NAMESPACE(Cell);
        REGISTER_NAMESPACE(Follower);
        REGISTER_NAMESPACE(Followers);
        REGISTER_NAMESPACE(Form);
        REGISTER_NAMESPACE(Forms);
        REGISTER_NAMESPACE(Game);
        REGISTER_NAMESPACE(Member);
        REGISTER_NAMESPACE(Members);
        REGISTER_NAMESPACE(Object_Ref);
        REGISTER_NAMESPACE(Outfit);
        REGISTER_NAMESPACE(Package);
        REGISTER_NAMESPACE(Papyrus);
        REGISTER_NAMESPACE(Player);
        REGISTER_NAMESPACE(Quest);
        REGISTER_NAMESPACE(String2);
        REGISTER_NAMESPACE(Utils);

        _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added all functions.\n");

        return true;

        #undef REGISTER_NAMESPACE
    }

}}

extern "C" {

    bool SKSEPlugin_Query(const SKSEInterface *skse, PluginInfo *info) {
        return doticu_npcp::Main::Query_Plugin(skse, info);
    }

    bool SKSEPlugin_Load(const SKSEInterface *skse) {
        return doticu_npcp::Main::Load_Plugin(skse);
    }

}
