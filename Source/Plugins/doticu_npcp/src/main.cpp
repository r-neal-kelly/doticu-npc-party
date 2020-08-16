/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "actor_base2.h"
#include "actor2.h"
#include "cell.h"
#include "codes.h"
#include "consts.h"
#include "form.h"
#include "forms.h"
#include "form_vector.h"
#include "game.h"
#include "keys.h"
#include "main.h"
#include "object_ref.h"
#include "outfit.h"
#include "outfit2.h"
#include "package.h"
#include "papyrus.h"
#include "party.h"
#include "player.h"
#include "quest.h"
#include "spell.h"
#include "string2.h"
#include "tests.h"
#include "utils.h"
#include "vars.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_member.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Main {

    bool Query_Plugin(const SKSEInterface* skse, PluginInfo* info);
    bool Load_Plugin(const SKSEInterface* skse);
    bool Register_Functions(Papyrus::Registry_t* registry);

}}

namespace doticu_npcp { namespace Modules {

    String_t Main_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_main");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Main_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Main_t* Main_t::Self()
    {
        return static_cast<Main_t*>(Consts::Main_Quest());
    }

    Object_t* Main_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Main_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Bool_t Main_t::Is_Version_Less_Than(Int_t major,
                                        Int_t minor,
                                        Int_t patch,
                                        Int_t min_major,
                                        Int_t min_minor,
                                        Int_t min_patch)
    {
        if (major != min_major) {
            return major < min_major;
        } else if (minor != min_minor) {
            return minor < min_minor;
        } else if (patch != min_patch) {
            return patch < min_patch;
        } else {
            return false;
        }
    }

    Bool_t Main_t::Is_NPCP_Version_Less_Than(Int_t min_major,
                                             Int_t min_minor,
                                             Int_t min_patch)
    {
        return Is_Version_Less_Than(Vars::NPCP_Major(),
                                    Vars::NPCP_Minor(),
                                    Vars::NPCP_Patch(),
                                    min_major,
                                    min_minor,
                                    min_patch);
    }

    void Main_t::Load_Mod()
    {
        struct Callback : public Virtual_Callback_t {
        public:
            void operator()(Variable_t* result)
            {
                Utils::Print("NPC Party has loaded.");
            }
        };
        Virtual_Callback_i* callback = new Callback();

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "f_Load_Mod", nullptr, &callback);
    }

    Bool_t Main_t::Try_Update()
    {
        Int_t curr_major = Consts::NPCP_Major();
        Int_t curr_minor = Consts::NPCP_Minor();
        Int_t curr_patch = Consts::NPCP_Patch();

        if (Is_NPCP_Version_Less_Than(curr_major, curr_minor, curr_patch)) {

            if (Is_NPCP_Version_Less_Than(0, 9, 3)) {
                Party::Members_t::Self()->u_0_9_3();
            }

            Vars::NPCP_Major(curr_major);
            Vars::NPCP_Minor(curr_minor);
            Vars::NPCP_Patch(curr_patch);

            return true;
        } else {
            return false;
        }
    }

    void Main_t::Register_Me(Registry_t* registry)
    {
        auto Try_Update = [](Main_t* self)->Bool_t FORWARD_BOOL(Main_t::Try_Update());

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), Main_t,                      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("p_Try_Update", 0, Bool_t, Try_Update);

        #undef ADD_METHOD
    }

}}

namespace doticu_npcp { namespace Main {

    bool Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
    {
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

    bool Load_Plugin(const SKSEInterface* skse)
    {
        g_skse = skse;
        g_papyrus = static_cast<SKSEPapyrusInterface*>(skse->QueryInterface(kInterface_Papyrus));
        g_messaging = static_cast<SKSEMessagingInterface*>(skse->QueryInterface(kInterface_Messaging));
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

        if (g_messaging) {
            auto Callback = [](SKSEMessagingInterface::Message* message)->void
            {
                if (message) {
                    if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                        Modules::Main_t::Self()->Load_Mod();
                    }
                }
            };
            g_messaging->RegisterListener(g_plugin_handle, "SKSE", Callback);
        }

        return true;
    }

    bool Register_Functions(Papyrus::Registry_t* registry)
    {
        using namespace Papyrus;

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
        REGISTER_NAMESPACE(Cell);
        REGISTER_NAMESPACE(CODES);
        REGISTER_NAMESPACE(Consts);
        REGISTER_NAMESPACE(Form);
        REGISTER_NAMESPACE(Forms);
        REGISTER_NAMESPACE(Form_Vector);
        REGISTER_NAMESPACE(Game);
        REGISTER_NAMESPACE(Keys);
        REGISTER_NAMESPACE(Object_Ref);
        REGISTER_NAMESPACE(Outfit);
        REGISTER_NAMESPACE(Papyrus::Outfit2);
        REGISTER_NAMESPACE(Package);
        REGISTER_NAMESPACE(Papyrus);
        REGISTER_NAMESPACE(Player);
        REGISTER_NAMESPACE(Quest);
        REGISTER_NAMESPACE(Spell);
        REGISTER_NAMESPACE(String2);
        REGISTER_NAMESPACE(Tests);
        REGISTER_NAMESPACE(Utils);
        REGISTER_NAMESPACE(Vars);

        REGISTER_NAMESPACE(Party::Members);
        REGISTER_NAMESPACE(Party::Followers);
        REGISTER_NAMESPACE(Party::Horses);
        REGISTER_NAMESPACE(Party::Member);
        REGISTER_NAMESPACE(Party::Follower);
        REGISTER_NAMESPACE(Party::Horse);

        #undef REGISTER_NAMESPACE

        #define REGISTER_TYPE(TYPE_)                                            \
        M                                                                       \
            TYPE_::Register_Me(registry);                                       \
            _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added " #TYPE_ " functions.");   \
        W
        REGISTER_TYPE(Modules::Main_t);
        REGISTER_TYPE(Party::NPCS_t);
        REGISTER_TYPE(MCM::SKI_Config_Base_t);
        REGISTER_TYPE(MCM::Main_t);
        REGISTER_TYPE(MCM::Member_t);

        #undef REGISTER_TYPE

        _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added all functions.\n");

        return true;
    }

}}

extern "C" {

    bool SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_npcp::Main::Query_Plugin(skse, info);
    }

    bool SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_npcp::Main::Load_Plugin(skse);
    }

}
