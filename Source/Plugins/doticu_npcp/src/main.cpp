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
                            // SaveGame and PreLoadGame will give us the savefile path as message->data, and it's char length too
                            if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
                                Before_Save();
                            } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
                                Before_Load();
                            } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data != nullptr) {
                                After_Load();
                            } else if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
                                Before_New_Game();
                            }
                        }
                    };
                    SKSE_MESSAGING->RegisterListener(SKSE_PLUGIN_HANDLE, "SKSE", Callback);
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
        Hotkeys_t::Register_Me(machine);
        MCM::Main_t::Register_Me(machine);

        SKYLIB_LOG("Added all functions.\n");

        return true;
    }

    Main_t::NPCP_State_t::NPCP_State_t(Bool_t is_new_game) :
        party_members(Consts_t::NPCP::Quest::Members()),
        hotkeys(Consts_t::NPCP::Quest::Control())
    {
    }

    Main_t::NPCP_State_t::NPCP_State_t(const Version_t<u16> version_to_update) :
        party_members(Consts_t::NPCP::Quest::Members(), version_to_update),
        hotkeys(Consts_t::NPCP::Quest::Control(), version_to_update)
    {
    }

    Main_t::NPCP_State_t::~NPCP_State_t()
    {
    }

    void Main_t::NPCP_State_t::Before_Save()
    {
        this->party_members.Before_Save();
        this->hotkeys.Before_Save();
    }

    void Main_t::NPCP_State_t::After_Save()
    {
        this->party_members.After_Save();
        this->hotkeys.After_Save();
    }

    Main_t::Protected_Locker_t::Protected_Locker_t(std::unique_lock<std::mutex>& lock) :
        lock(&lock)
    {
    }

    Main_t::Protected_Locker_t::Protected_Locker_t(const Protected_Locker_t& other) :
        lock(other.lock)
    {
    }

    Main_t::Protected_Locker_t::Protected_Locker_t(Protected_Locker_t&& other) noexcept :
        lock(std::move(other.lock))
    {
    }

    Main_t::Protected_Locker_t& Main_t::Protected_Locker_t::operator =(const Protected_Locker_t& other)
    {
        if (this != std::addressof(other)) {
            this->lock = other.lock;
        }
        return *this;
    }

    Main_t::Protected_Locker_t& Main_t::Protected_Locker_t::operator =(Protected_Locker_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->lock = std::move(other.lock);
        }
        return *this;
    }

    Main_t::Protected_Locker_t::~Protected_Locker_t()
    {
    }

    maybe<Main_t::NPCP_State_t*>    Main_t::npcp_state = none<Main_t::NPCP_State_t*>();
    std::mutex                      Main_t::npcp_state_lock;

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

    some<V::Object_t*> Main_t::Object()
    {
        DEFINE_OBJECT_STATIC();
    }

    Bool_t Main_t::Is_Active(const Protected_Locker_t locker)
    {
        return !!Consts_t::NPCP::Mod();
    }

    Bool_t Main_t::Is_Initialized(const Protected_Locker_t locker)
    {
        return Consts_t::NPCP::Global::Is_Initialized()->Bool();
    }

    Bool_t Main_t::Has_Requirements(const Protected_Locker_t locker)
    {
        if (Is_Initialized(locker) && Vars_t::Version() < Version_t<u16>(0, 9, 15)) {
            UI_t::Create_Message_Box("Update failed. You must have version 0.9.15-beta installed first.",
                                     none<V::Callback_i*>());
            return false;
        } else {
            return true;
        }
    }

    void Main_t::Before_New_Game()
    {
        std::unique_lock<std::mutex> locker(npcp_state_lock);

        if (npcp_state) {
            // if this causes a crash for any reason, we'll just need to let the memory leak.
            delete npcp_state();
        }
    }

    void Main_t::After_New_Game()
    {
        std::unique_lock<std::mutex> locker(npcp_state_lock);

        if (Is_Active(locker) && Has_Requirements(locker) && !Is_Initialized(locker)) {
            Vector_t<some<Quest_t*>> quests;
            quests.push_back(Consts_t::NPCP::Quest::Main());
            quests.push_back(Consts_t::NPCP::Quest::Vars());
            quests.push_back(Consts_t::NPCP::Quest::Funcs());
            quests.push_back(Consts_t::NPCP::Quest::Members());
            quests.push_back(Consts_t::NPCP::Quest::Followers());
            quests.push_back(Consts_t::NPCP::Quest::Control());

            struct Wait_Callback :
                public V::Callback_t
            {
            public:
                const Vector_t<some<Quest_t*>> quests;

            public:
                Wait_Callback(const Vector_t<some<Quest_t*>> quests) :
                    quests(std::move(quests))
                {
                }

            public:
                virtual void operator ()(V::Variable_t*) override
                {
                    class Quests_Are_Running_Callback :
                        public skylib::Callback_i<Bool_t>
                    {
                    public:
                        const Vector_t<some<Quest_t*>> quests;

                    public:
                        Quests_Are_Running_Callback(const Vector_t<some<Quest_t*>> quests) :
                            quests(std::move(quests))
                        {
                        }

                    public:
                        virtual void operator ()(Bool_t quests_are_running) override
                        {
                            std::unique_lock<std::mutex> locker(npcp_state_lock);

                            if (quests_are_running) {
                                if (!Is_Initialized(locker)) {
                                    SKYLIB_ASSERT(!npcp_state);
                                    npcp_state = new NPCP_State_t(true);

                                    Consts_t::NPCP::Global::Is_Initialized()->Bool(true);

                                    UI_t::Create_Notification(NPCP_PRINT_HEAD + "Thank you for installing!",
                                                              none<V::Callback_i*>()); // Log_t it
                                }
                            } else {
                                V::Utility_t::Wait_Out_Of_Menu(1.0f, new Wait_Callback(std::move(this->quests)));
                            }
                        }
                    };
                    Quest_t::Are_Running(this->quests, new Quests_Are_Running_Callback(std::move(this->quests)));
                }
            };
            V::Utility_t::Wait_Out_Of_Menu(1.0f, new Wait_Callback(std::move(quests)));
        }
    }

    void Main_t::Before_Save()
    {
        std::unique_lock<std::mutex> locker(npcp_state_lock);

        if (Is_Active(locker) && Has_Requirements(locker) && Is_Initialized(locker)) {
            SKYLIB_ASSERT(npcp_state);
            npcp_state->Before_Save();
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
                std::unique_lock<std::mutex> locker(npcp_state_lock);

                if (Is_Active(locker) && Has_Requirements(locker) && Is_Initialized(locker)) {
                    SKYLIB_ASSERT(npcp_state);
                    npcp_state->After_Save();
                }
            }
        };
        V::Utility_t::Wait_Even_In_Menu(0.1f, new Wait_Callback());
    }

    void Main_t::Before_Load()
    {
        std::unique_lock<std::mutex> locker(npcp_state_lock);

        if (Is_Active(locker) && Has_Requirements(locker) && Is_Initialized(locker)) {
            SKYLIB_ASSERT(npcp_state);
            delete npcp_state();
        }
    }

    void Main_t::After_Load()
    {
        std::unique_lock<std::mutex> locker(npcp_state_lock);

        if (Is_Active(locker) && Has_Requirements(locker)) {
            if (Is_Initialized(locker)) {
                SKYLIB_ASSERT(!npcp_state);
                const Version_t<u16> current_version = Consts_t::NPCP::Version::Current();
                const Version_t<u16> installed_version = Vars_t::Version();
                if (installed_version < current_version) {
                    npcp_state = new NPCP_State_t(installed_version);


                    Vars_t::Version(current_version); // Vars_t itself should handle this.

                    UI_t::Create_Notification(NPCP_PRINT_HEAD + "Running version " +
                                              std::to_string(current_version.major) + "." +
                                              std::to_string(current_version.minor) + "." +
                                              std::to_string(current_version.patch),
                                              none<V::Callback_i*>()); // Log_t it
                } else {
                    npcp_state = new NPCP_State_t(false);
                }
            } else {
                locker.~unique_lock();
                After_New_Game();
            }
        }
    }

    void Main_t::On_Init()
    {
        After_New_Game();
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
