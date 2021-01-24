/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "doticu_skylib/global.h"
#include "doticu_skylib/ui.h"

#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_macros.h"
#include "doticu_skylib/virtual_utils.h"

#include "consts.h"
#include "main.h"
#include "vars.h"

namespace doticu_npcp {

    const SKSEInterface*            Main_t::SKSE                = nullptr;
    const SKSEPapyrusInterface*     Main_t::SKSE_PAPYRUS        = nullptr;
    const SKSEMessagingInterface*   Main_t::SKSE_MESSAGING      = nullptr;
    PluginHandle                    Main_t::SKSE_PLUGIN_HANDLE  = 0;

    Bool_t Main_t::SKSE_Query_Plugin(const SKSEInterface* skse, PluginInfo* info)
    {
        if (skse && info) {
            info->infoVersion = PluginInfo::kInfoVersion;
            info->name = "doticu_npcp";
            info->version = 1;

            if (Version_t<u16>::From_MM_mm_ppp_b(skse->runtimeVersion) == Consts_t::Skyrim::Version::Required()) {
                if (Version_t<u16>::From_MM_mm_ppp_b(skse->skseVersion) >= Consts_t::SKSE::Version::Minimum()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Main_t::SKSE_Load_Plugin(const SKSEInterface* skse)
    {
        SKSE_LOG.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\doticu_npcp.log");
        if (skse) {
            SKSE = skse;
            SKSE_PAPYRUS = static_cast<const SKSEPapyrusInterface*>(SKSE->QueryInterface(kInterface_Papyrus));
            SKSE_MESSAGING = static_cast<const SKSEMessagingInterface*>(SKSE->QueryInterface(kInterface_Messaging));
            SKSE_PLUGIN_HANDLE = SKSE->GetPluginHandle();
            if (SKSE_PAPYRUS && SKSE_MESSAGING) {
                if (SKSE_PAPYRUS->Register(reinterpret_cast<SKSEPapyrusInterface::RegisterFunctions>(SKSE_Register_Functions))) {
                    auto Callback = [](SKSEMessagingInterface::Message* message)->void
                    {
                        if (message) {
                            if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                                After_Load();
                            }
                        }
                    };
                    SKSE_MESSAGING->RegisterListener(SKSE_PLUGIN_HANDLE, "SKSE", Callback);
                    //Papyrus::Keys_t::On_Load_Plugin();
                    return true;
                } else {
                    _FATALERROR("Unable to register functions.");
                    return false;
                }
            } else {
                _FATALERROR("Unable to get papyrus and/or messaging interface.");
                return false;
            }
        } else {
            _FATALERROR("Unable to get skse interface.");
            return false;
        }
    }

    Bool_t Main_t::SKSE_Register_Functions(V::Machine_t* machine)
    {
        #define REGISTER(TYPE_)                         \
        SKYLIB_M                                        \
            TYPE_::Register_Me(machine);                \
            SKYLIB_LOG("Added " #TYPE_ " functions.");  \
        SKYLIB_W

        REGISTER(doticu_npcp::Main_t);
        REGISTER(doticu_npcp::Vars_t);

        #undef REGISTER

        SKYLIB_LOG("Added all functions.\n");

        return true;
    }

    some<Main_t*>       Main_t::Self()          { return Consts_t::NPCP::Quest::Main(); }
    String_t            Main_t::Class_Name()    { DEFINE_CLASS_NAME("doticu_npcp_main"); }
    some<V::Class_t*>   Main_t::Class()         { DEFINE_CLASS(); }
    some<V::Object_t*>  Main_t::Object()        { DEFINE_OBJECT_STATIC(); }

    void Main_t::Register_Me(V::Machine_t* machine)
    {
        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)      \
        SKYLIB_M                                                                        \
            BIND_METHOD(machine, class_name, Main_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        METHOD("OnInit", true, void, On_Init);

        #undef METHOD
    }

    Bool_t Main_t::Is_Active()
    {
        return Consts_t::NPCP::Mod() != nullptr;
    }

    Bool_t Main_t::Is_Initialized()
    {
        return Consts_t::NPCP::Global::Is_Initialized()->Bool();
    }

    Bool_t Main_t::Has_Requirements()
    {
        if (Is_Initialized()) {
            if (Vars_t::Version() < Version_t<u16>(0, 9, 15)) {
                UI_t::Message_Box("Update failed. You must have version 0.9.15-beta installed first.");
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }

    void Main_t::Initialize()
    {
        struct Wait_Callback_t : public V::Callback_t
        {
        public:
            void operator ()(V::Variable_t*)
            {
                if (!Is_Initialized() && Has_Requirements()) {
                    Vars_t::Initialize();

                    Consts_t::NPCP::Global::Is_Initialized()->Bool(true);

                    /*
                        Logs_t::Self()->Initialize();
                        Party::NPCS_t::Self()->Initialize();
                        Party::Player_t::Self()->On_Init_Mod();

                        Papyrus::Keys_t::Self()->Register();
                        Party::Movee_t::Self()->Register();
                        Party::Player_t::Self()->On_Register();

                        Modules::Control::Commands_t::Self()->Log_Note("Thank you for installing!", true);
                    */
                }
            }
        };
        V::Utils_t::Wait_Out_Of_Menu(1.0f, new Wait_Callback_t());
    }

    void Main_t::After_Load()
    {
        struct Wait_Callback_t : public V::Callback_t
        {
        public:
            void operator ()(V::Variable_t*)
            {
                if (Is_Initialized() && Has_Requirements()) {
                    if (Try_Update()) {
                        const Version_t<u16> version = Vars_t::Version();
                        std::string note =
                            "Running version " +
                            std::to_string(version.major) + "." +
                            std::to_string(version.minor) + "." +
                            std::to_string(version.patch);
                        UI_t::Notification(note.c_str()); // will want to save this message in logs.
                    }
                    /*
                        Modules::Keys_t::Self()->On_Load_Mod();
                        Party::Members_t::Self()->On_Load_Mod();
                        Party::Player_t::Self()->On_Load_Mod();
                        Party::Movee_t::Self()->On_Load_Mod();
                        Party::Mannequins_t::Self()->On_Load_Mod();
                        Utils::Print("NPC Party has loaded.");
                    */
                }
            }
        };
        V::Utils_t::Wait_Out_Of_Menu(1.0f, new Wait_Callback_t());
    }

    Bool_t Main_t::Try_Update()
    {
        SKYLIB_ASSERT(Is_Initialized());

        const Version_t<u16> current_version = Consts_t::NPCP::Version::Current();
        const Version_t<u16> installed_version = Vars_t::Version();
        if (installed_version < current_version) {
            Vars_t::Version(current_version);
            return true;
        } else {
            return false;
        }
    }

    void Main_t::On_Init()
    {
        Initialize();
    }

}

extern "C" {

    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Query(const SKSEInterface*, PluginInfo*);
    _declspec(dllexport) skylib::Bool_t SKSEPlugin_Load(const SKSEInterface*);

    skylib::Bool_t SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
    {
        return doticu_npcp::Main_t::SKSE_Query_Plugin(skse, info);
    }

    skylib::Bool_t SKSEPlugin_Load(const SKSEInterface* skse)
    {
        return doticu_npcp::Main_t::SKSE_Load_Plugin(skse);
    }

}
