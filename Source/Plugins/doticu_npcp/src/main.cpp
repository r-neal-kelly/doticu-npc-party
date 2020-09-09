/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "skse64/GameData.h"

#include "actor_base2.h"
#include "actor2.h"
#include "cell.h"
#include "codes.h"
#include "commands.h"
#include "consts.h"
#include "form.h"
#include "form_vector.h"
#include "funcs.h"
#include "game.h"
#include "keys.h"
#include "main.h"
#include "object_ref.h"
#include "outfit.h"
#include "outfit2.h"
#include "package.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "quest.h"
#include "spell.h"
#include "string2.h"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "party/party_player.h"
#include "party/party_greeter.h"
#include "party/party_movee.h"
#include "party/party_npcs.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_mannequins.h"
#include "party/party_followers.h"
#include "party/party_follower.h"
#include "party/party_horses.h"
#include "party/party_horse.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_members.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_filter.h"
#include "mcm/mcm_chests.h"
#include "mcm/mcm_hotkeys.h"

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

    void Main_t::Init_Mod()
    {
        struct VCallback : public Virtual_Callback_t {
            Main_t* main;
            VCallback(Main_t* main) :
                main(main)
            {
            }
            void operator()(Variable_t* result)
            {
                struct Callback : public Callback_t<Bool_t> {
                    Main_t* main;
                    Callback(Main_t* main) :
                        main(main)
                    {
                    }
                    void operator()(Bool_t has_requirements)
                    {
                        if (has_requirements) {
                            Quest::Start(Consts::Vars_Quest());
                            Quest::Start(Consts::Funcs_Quest());
                            Quest::Start(Consts::Members_Quest());
                            Quest::Start(Consts::Followers_Quest());
                            Quest::Start(Consts::Control_Quest());

                            Quest::Start(Consts::Reanimated_Dialogue_Quest());
                            Quest::Start(Consts::Thrall_Dialogue_Quest());

                            struct VCallback : public Virtual_Callback_t {
                                Main_t* main;
                                VCallback(Main_t* main) :
                                    main(main)
                                {
                                }
                                void operator()(Variable_t* result)
                                {
                                    Consts::Is_Installed_Global()->value = 1.0f;
                                    Modules::Control::Commands_t::Self()->Log_Note("Thank you for installing!", true);
                                    Party::Player_t::Self()->On_Init_Mod();
                                }
                            };
                            Virtual_Callback_i* vcallback = new VCallback(main);
                            Virtual_Machine_t::Self()->Call_Method(main, main->Class_Name(), "p_Create", nullptr, &vcallback);
                        }
                    }
                };
                main->Has_Requirements(new Callback(main));
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this);
        Funcs_t::Self()->Wait_Out_Of_Menu(1.0f, &vcallback);
    }

    void Main_t::Load_Mod()
    {
        struct VCallback : public Virtual_Callback_t {
            Main_t* main;
            VCallback(Main_t* main) :
                main(main)
            {
            }
            void operator()(Variable_t* result)
            {
                struct Callback : public Callback_t<Bool_t> {
                    Main_t* main;
                    Callback(Main_t* main) :
                        main(main)
                    {
                    }
                    void operator()(Bool_t has_requirements)
                    {
                        if (has_requirements) {
                            struct VCallback : public Virtual_Callback_t {
                                Main_t* main;
                                VCallback(Main_t* main) :
                                    main(main)
                                {
                                }
                                void operator()(Variable_t* result)
                                {
                                    if (main->Try_Update()) {
                                        std::string note =
                                            "Running version " +
                                            std::to_string(Consts::NPCP_Major()) + "." +
                                            std::to_string(Consts::NPCP_Minor()) + "." +
                                            std::to_string(Consts::NPCP_Patch());
                                        Modules::Control::Commands_t::Self()->Log_Note(note.c_str(), true);
                                    }
                                    Party::Player_t::Self()->On_Load_Mod();
                                    Party::Members_t::Self()->On_Load_Mod();
                                    Utils::Print("NPC Party has loaded.");
                                }
                            };
                            Virtual_Callback_i* vcallback = new VCallback(main);
                            Virtual_Machine_t::Self()->Call_Method(main, main->Class_Name(), "p_Register", nullptr, &vcallback);
                        }
                    }
                };
                main->Has_Requirements(new Callback(main));
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this);
        Funcs_t::Self()->Wait_Out_Of_Menu(1.0f, &vcallback);
    }

    void Main_t::Has_Requirements(Callback_t<Bool_t>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<Bool_t>;

        struct VCallback : public Virtual_Callback_t {
            UCallback_t* user_callback;
            VCallback(UCallback_t* user_callback) :
                user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                user_callback->operator()(result ? result->Bool() : false);
                delete user_callback;
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(user_callback);
        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "p_Has_Requires", nullptr, &vcallback);
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
            if (Is_NPCP_Version_Less_Than(0, 9, 6)) {
                Party::Members_t::Self()->u_0_9_6();
            }
            if (Is_NPCP_Version_Less_Than(0, 9, 8)) {
                Party::Members_t::Self()->u_0_9_8();
            }
            if (Is_NPCP_Version_Less_Than(0, 9, 9)) {
                Party::Members_t::Self()->u_0_9_9();
            }

            Vars::NPCP_Major(curr_major);
            Vars::NPCP_Minor(curr_minor);
            Vars::NPCP_Patch(curr_patch);

            return true;
        } else {
            return false;
        }
    }

    void Main_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Main_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("p_Init_Mod", 0, void, Init_Mod);

        #undef METHOD
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

        if (skse->skseVersion < MAKE_EXE_VERSION(2, 0, 17)) {
            return false;
        } else {
            return true;
        }
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

        Papyrus::Keys_t::On_Load_Plugin();

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
        REGISTER_NAMESPACE(Form_Vector);
        REGISTER_NAMESPACE(Game);
        REGISTER_NAMESPACE(Object_Ref);
        REGISTER_NAMESPACE(Outfit);
        REGISTER_NAMESPACE(Papyrus::Outfit2);
        REGISTER_NAMESPACE(Package);
        REGISTER_NAMESPACE(Papyrus);
        REGISTER_NAMESPACE(Quest);
        REGISTER_NAMESPACE(Spell);
        REGISTER_NAMESPACE(String2);
        REGISTER_NAMESPACE(Utils);
        REGISTER_NAMESPACE(Vars);

        #undef REGISTER_NAMESPACE

        #define REGISTER_TYPE(TYPE_)                                            \
        M                                                                       \
            TYPE_::Register_Me(reinterpret_cast<Virtual_Machine_t*>(registry)); \
            _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added " #TYPE_ " functions.");   \
        W

        REGISTER_TYPE(Modules::Main_t);
        REGISTER_TYPE(Modules::Funcs_t);

        REGISTER_TYPE(Party::Player_t);
        REGISTER_TYPE(Party::Greeter_t);
        REGISTER_TYPE(Party::Movee_t);
        REGISTER_TYPE(Party::NPCS_t);
        REGISTER_TYPE(Party::Members_t);
        REGISTER_TYPE(Party::Member_t);
        REGISTER_TYPE(Party::Mannequins_t);
        REGISTER_TYPE(Party::Followers_t);
        REGISTER_TYPE(Party::Follower_t);
        REGISTER_TYPE(Party::Horses_t);
        REGISTER_TYPE(Party::Horse_t);

        REGISTER_TYPE(Modules::Control::Commands_t);

        REGISTER_TYPE(Papyrus::Keys_t);

        REGISTER_TYPE(MCM::SKI_Config_Base_t);
        REGISTER_TYPE(MCM::Main_t);
        REGISTER_TYPE(MCM::Members_t);
        REGISTER_TYPE(MCM::Member_t);
        REGISTER_TYPE(MCM::Filter_t);
        REGISTER_TYPE(MCM::Chests_t);
        REGISTER_TYPE(MCM::Hotkeys_t);

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
