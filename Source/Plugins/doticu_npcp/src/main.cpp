/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "doticu_skylib/global.h"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_macros.h"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

#include "consts.h"
#include "main.h"
#include "mcm_main.h"
#include "party_members.h"
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
            return
                Version_t<u16>::From_MM_mm_ppp_b(skse->runtimeVersion) == Consts_t::Skyrim::Version::Required() &&
                Version_t<u16>::From_MM_mm_ppp_b(skse->skseVersion) >= Consts_t::SKSE::Version::Minimum();
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
                            if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
                                Before_Save();
                            } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
                                // interestingly, this callback will give us the savefile path as message->data
                                Before_Load();
                            } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
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
        Main_t::Register_Me(machine);
        Vars_t::Register_Me(machine);
        Party::Members_t::Register_Me(machine);
        MCM::Main_t::Register_Me(machine);

        SKYLIB_LOG("Added all functions.\n");

        return true;
    }

    some<Main_t*> Main_t::Self()
    {
        return Consts_t::NPCP::Quest::Main();
    }

    String_t Main_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_main");
    }

    some<V::Class_t*> Main_t::Class()
    {
        DEFINE_CLASS();
    }

    some<V::Object_t*> Main_t::Object()
    {
        DEFINE_OBJECT_STATIC();
    }

    void Main_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

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

    Party::Members_t& Main_t::Party_Members()
    {
        // this needs to be reinitialized for new game!
        static Party::Members_t party_members(Consts_t::NPCP::Quest::Members());
        return party_members;
    }

    Bool_t Main_t::Is_Active()
    {
        return !!Consts_t::NPCP::Mod();
    }

    Bool_t Main_t::Is_Initialized()
    {
        return Consts_t::NPCP::Global::Is_Initialized()->Bool();
    }

    Bool_t Main_t::Has_Requirements()
    {
        if (Is_Initialized()) {
            if (Vars_t::Version() < Version_t<u16>(0, 9, 15)) {
                UI_t::Create_Message_Box(
                    "Update failed. You must have version 0.9.15-beta installed first.",
                    none<V::Callback_i*>()
                );
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }

    void Main_t::Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = some<unique<Callback_i<Bool_t>>>;

        class Is_In_Menu_Mode_Callback :
            public V::Callback_t
        {
        public:
            Callback callback;

        public:
            Is_In_Menu_Mode_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(V::Variable_t* result) override
            {
                Bool_t is_in_menu_mode = result ? result->As<Bool_t>() : false;
                (*this->callback)(!is_in_menu_mode);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        if (UI_t::Is_Menu_Open("Dialogue Menu")) {
            (*callback)(false);
        } else {
            UI_t::Is_In_Menu_Mode(new Is_In_Menu_Mode_Callback(std::move(callback)));
        }
    }

    void Main_t::Initialize()
    {
        struct Wait_Callback_t :
            public V::Callback_t
        {
        public:
            virtual void operator ()(V::Variable_t*) override
            {
                if (Is_Active() && !Is_Initialized() && Has_Requirements()) {
                    Vars_t::Initialize();
                    Party_Members().Initialize(); // Party::Main_t::Initialize();
                    MCM::Main_t::Initialize();

                    Consts_t::NPCP::Global::Is_Initialized()->Bool(true);

                    // this needs to be saved to log.
                    UI_t::Create_Notification(
                        "Thank you for installing!",
                        none<V::Callback_i*>()
                    );

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
        V::Utility_t::Wait_Out_Of_Menu(1.0f, new Wait_Callback_t());
    }

    void Main_t::Before_Save()
    {
        if (Is_Active() && Is_Initialized() && Has_Requirements()) {
            Party_Members().Before_Save();
            MCM::Main_t::Before_Save();

            Main_t::After_Save();
        }
    }

    void Main_t::After_Save()
    {
        class Wait_Callback :
            public V::Callback_t
        {
        public:
            virtual void operator ()(V::Variable_t*) override
            {
                if (Is_Active() && Is_Initialized() && Has_Requirements()) {
                    Party_Members().After_Save();
                }
            }
        };
        V::Utility_t::Wait_Even_In_Menu(0.1f, new Wait_Callback());
    }

    void Main_t::Before_Load()
    {
        if (Is_Active() && Is_Initialized() && Has_Requirements()) {
            Party_Members().Before_Load();
        }
    }

    void Main_t::After_Load()
    {
        if (Is_Active() && Is_Initialized() && Has_Requirements()) {
            if (Try_Update()) {
                const Version_t<u16> version = Vars_t::Version();
                std::string note =
                    "Running version " +
                    std::to_string(version.major) + "." +
                    std::to_string(version.minor) + "." +
                    std::to_string(version.patch);
                UI_t::Create_Notification(note.c_str(), none<V::Callback_i*>()); // will want to save this message in logs.

                Party_Members().After_Load();
                MCM::Main_t::After_Load();
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

    Bool_t Main_t::Try_Update()
    {
        SKYLIB_ASSERT(Is_Initialized());

        const Version_t<u16> current_version = Consts_t::NPCP::Version::Current();
        const Version_t<u16> installed_version = Vars_t::Version();
        if (installed_version < current_version) {
            if (installed_version < Version_t<u16>(0, 10, 0)) {
                u_0_10_0();
            }
            Vars_t::Version(current_version);
            return true;
        } else {
            return false;
        }
    }

    void Main_t::u_0_10_0()
    {
        Party_Members().u_0_10_0();
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
