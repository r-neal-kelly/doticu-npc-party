/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "skse64_common/skse_version.h"

#include "skse64/GameData.h"

#include "active_magic_effects.h"
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
#include "logs.h"
#include "main.h"
#include "object_ref.h"
#include "outfit.h"
#include "outfit2.h"
#include "packages.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "perks.h"
#include "quest.h"
#include "references.h"
#include "spell.h"
#include "string2.h"
#include "topic_infos.h"
#include "ui.h"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "party/party_player.h"
#include "party/party_greeter.h"
#include "party/party_movee.h"
#include "party/party_npcs.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_settler.h"
#include "party/party_mannequins.h"
#include "party/party_followers.h"
#include "party/party_follower.h"
#include "party/party_horses.h"
#include "party/party_horse.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_followers.h"
#include "mcm/mcm_members.h"
#include "mcm/mcm_mannequins.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_settlers.h"
#include "mcm/mcm_filter.h"
#include "mcm/mcm_chests.h"
#include "mcm/mcm_settings.h"
#include "mcm/mcm_hotkeys.h"
#include "mcm/mcm_logs.h"

namespace doticu_npcp {

    const IDebugLog g_log;
    const SKSEInterface* g_skse;
    const SKSEPapyrusInterface* g_papyrus;
    const SKSEMessagingInterface* g_messaging;
    PluginHandle g_plugin_handle;

}

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
        Vars_t* vars = Vars_t::Self();
        return Is_Version_Less_Than(vars->NPCP_Major(),
                                    vars->NPCP_Minor(),
                                    vars->NPCP_Patch(),
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
                if (main->Has_Requirements()) {
                    main->Start_Voice_Quests();

                    Vector_t<Quest_t*> quests_to_start;
                    quests_to_start.reserve(5);
                    quests_to_start.push_back(Consts::Vars_Quest());
                    quests_to_start.push_back(Consts::Funcs_Quest());
                    quests_to_start.push_back(Consts::Members_Quest());
                    quests_to_start.push_back(Consts::Followers_Quest());
                    quests_to_start.push_back(Consts::Control_Quest());
                    struct Callback : public Callback_t<> {
                        Main_t* main;
                        Callback(Main_t* main) :
                            main(main)
                        {
                        }
                        void operator()()
                        {
                            Vars_t::Self()->Initialize();
                            Logs_t::Self()->Initialize();
                            Party::NPCS_t::Self()->Initialize();
                            Party::Player_t::Self()->On_Init_Mod();

                            Papyrus::Keys_t::Self()->Register();
                            Party::Movee_t::Self()->Register();
                            Party::Player_t::Self()->On_Register();

                            Consts::Is_Installed_Global()->value = 1.0f;
                            Modules::Control::Commands_t::Self()->Log_Note("Thank you for installing!", true);
                        }
                    };
                    Quest::Start_All(quests_to_start, new Callback(main));
                }
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this);
        Funcs_t::Self()->Wait_Out_Of_Menu(1.0f, &vcallback);
    }

    void Main_t::Load_Mod()
    {
        if (Consts::Is_Installed_Global()->value > 0.0f) {
            struct VCallback : public Virtual_Callback_t {
                Main_t* main;
                VCallback(Main_t* main) :
                    main(main)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (main->Has_Requirements()) {
                        if (main->Try_Update()) {
                            std::string note =
                                "Running version " +
                                std::to_string(Consts::NPCP_Major()) + "." +
                                std::to_string(Consts::NPCP_Minor()) + "." +
                                std::to_string(Consts::NPCP_Patch());
                            Modules::Control::Commands_t::Self()->Log_Note(note.c_str(), true);
                        }
                        main->Try_Cleanup();
                        Modules::Keys_t::Self()->On_Load_Mod();
                        Party::Members_t::Self()->On_Load_Mod();
                        Party::Player_t::Self()->On_Load_Mod();
                        Party::Movee_t::Self()->On_Load_Mod();
                        Party::Mannequins_t::Self()->On_Load_Mod();
                        Utils::Print("NPC Party has loaded.");
                    }
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this);
            Funcs_t::Self()->Wait_Out_Of_Menu(1.0f, &vcallback);
        }
    }

    Bool_t Main_t::Has_Requirements()
    {
        if (Consts::Is_Installed_Global()->value > 0.0f && Is_NPCP_Version_Less_Than(0, 9, 1)) {
            UI::Message_Box("NPC Party: This save has a version of NPC Party older than 0.9.1. "
                            "The new version you are running will not work on this save yet. "
                            "Exit without saving, and then update to version 0.9.1 before trying again.");
            return false;
        } else {
            return true;
        }
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
            if (Is_NPCP_Version_Less_Than(0, 9, 12)) {
                Party::Members_t::Self()->u_0_9_12();
            }
            if (Is_NPCP_Version_Less_Than(0, 9, 15)) {
                Party::Members_t::Self()->u_0_9_15();
            }
            if (Is_NPCP_Version_Less_Than(0, 9, 16)) {
                u_0_9_16();
            }

            Vars_t* vars = Vars_t::Self();
            vars->NPCP_Major(curr_major);
            vars->NPCP_Minor(curr_minor);
            vars->NPCP_Patch(curr_patch);

            return true;
        } else {
            return false;
        }
    }

    void Main_t::Try_Cleanup()
    {
        Int_t objects_deleted = 0;

        {
            Vector_t<Reference_t*> outfit2s = Cell::References(Consts::Storage_Cell(), Consts::Outfit2_Container());
            for (size_t idx = 0, count = outfit2s.size(); idx < count; idx += 1) {
                Outfit2_t* outfit2 = static_cast<Outfit2_t*>(outfit2s.at(idx));
                if (outfit2 && outfit2->Type() == CODES::OUTFIT2::DELETED) {
                    Object_Ref::Delete_Safe(outfit2);
                    objects_deleted += 1;
                }
            }
        }
        
        {
            Party::NPCS_t* npcs = Party::NPCS_t::Self();
            Form_Vector_t* bases = npcs->Bases();
            Form_Vector_t* default_outfits = npcs->Default_Outfits();
            Vector_t<Reference_t*> form_vectors = Cell::References(Consts::Storage_Cell(), Consts::Form_Vector());
            for (size_t idx = 0, count = form_vectors.size(); idx < count; idx += 1) {
                Form_Vector_t* form_vector = static_cast<Form_Vector_t*>(form_vectors.at(idx));
                if (form_vector && form_vector != bases && form_vector != default_outfits) {
                    Object_Ref::Delete_Safe(form_vector);
                    objects_deleted += 1;
                }
            }
        }

        if (objects_deleted == 1) {
            Utils::Print("NPC Party requested 1 object to be deleted.");
        } else {
            Utils::Print((std::string("NPC Party requested ") + std::to_string(objects_deleted) + " objects to be deleted.").c_str());
        }
    }

    Int_t Main_t::Force_Cleanup()
    {
        Int_t objects_deleted = 0;

        {
            Vector_t<Reference_t*> outfit2s = Cell::References(Consts::Storage_Cell(), Consts::Outfit2_Container());
            for (size_t idx = 0, count = outfit2s.size(); idx < count; idx += 1) {
                Outfit2_t* outfit2 = static_cast<Outfit2_t*>(outfit2s.at(idx));
                if (outfit2 && outfit2->Type() == CODES::OUTFIT2::DELETED) {
                    outfit2->flags = Utils::Bit_Off(outfit2->flags, 5);
                    Object_Ref::Delete_Unsafe(outfit2);
                    objects_deleted += 1;
                }
            }
        }

        {
            Party::NPCS_t* npcs = Party::NPCS_t::Self();
            Form_Vector_t* bases = npcs->Bases();
            Form_Vector_t* default_outfits = npcs->Default_Outfits();
            Vector_t<Reference_t*> form_vectors = Cell::References(Consts::Storage_Cell(), Consts::Form_Vector());
            for (size_t idx = 0, count = form_vectors.size(); idx < count; idx += 1) {
                Form_Vector_t* form_vector = static_cast<Form_Vector_t*>(form_vectors.at(idx));
                if (form_vector && form_vector != bases && form_vector != default_outfits) {
                    form_vector->flags = Utils::Bit_Off(form_vector->flags, 5);
                    Object_Ref::Delete_Unsafe(form_vector);
                    objects_deleted += 1;
                }
            }
        }

        if (objects_deleted == 1) {
            Utils::Print("NPC Party forced 1 object to be deleted.");
        } else {
            Utils::Print((std::string("NPC Party forced ") + std::to_string(objects_deleted) + " objects to be deleted.").c_str());
        }

        return objects_deleted;
    }

    Int_t Main_t::Count_Unused_Objects()
    {
        Int_t unused_objects = 0;

        {
            Vector_t<Reference_t*> outfit2s = Cell::References(Consts::Storage_Cell(), Consts::Outfit2_Container());
            for (size_t idx = 0, count = outfit2s.size(); idx < count; idx += 1) {
                Outfit2_t* outfit2 = static_cast<Outfit2_t*>(outfit2s.at(idx));
                if (outfit2 && outfit2->Type() == CODES::OUTFIT2::DELETED) {
                    unused_objects += 1;
                }
            }
        }

        {
            Party::NPCS_t* npcs = Party::NPCS_t::Self();
            Form_Vector_t* bases = npcs->Bases();
            Form_Vector_t* default_outfits = npcs->Default_Outfits();
            Vector_t<Reference_t*> form_vectors = Cell::References(Consts::Storage_Cell(), Consts::Form_Vector());
            for (size_t idx = 0, count = form_vectors.size(); idx < count; idx += 1) {
                Form_Vector_t* form_vector = static_cast<Form_Vector_t*>(form_vectors.at(idx));
                if (form_vector && form_vector != bases && form_vector != default_outfits) {
                    unused_objects += 1;
                }
            }
        }

        return unused_objects;
    }

    void Main_t::Start_Voice_Quests()
    {
        Quest::Start(Consts::Female_Argonian_Quest());
        Quest::Start(Consts::Female_Commander_Quest());
        Quest::Start(Consts::Female_Commoner_Quest());
        Quest::Start(Consts::Female_Condescending_Quest());
        Quest::Start(Consts::Female_Coward_Quest());
        Quest::Start(Consts::Female_Dark_Elf_Quest());
        Quest::Start(Consts::Female_Elf_Haughty_Quest());
        Quest::Start(Consts::Female_Even_Toned_Quest());
        Quest::Start(Consts::Female_Khajiit_Quest());
        Quest::Start(Consts::Female_Nord_Quest());
        Quest::Start(Consts::Female_Old_Grumpy_Quest());
        Quest::Start(Consts::Female_Old_Kindly_Quest());
        Quest::Start(Consts::Female_Orc_Quest());
        Quest::Start(Consts::Female_Other_Quest());
        Quest::Start(Consts::Female_Shrill_Quest());
        Quest::Start(Consts::Female_Soldier_Quest());
        Quest::Start(Consts::Female_Sultry_Quest());
        Quest::Start(Consts::Female_Young_Eager_Quest());
        Quest::Start(Consts::Male_Argonian_Quest());
        Quest::Start(Consts::Male_Bandit_Quest());
        Quest::Start(Consts::Male_Brute_Quest());
        Quest::Start(Consts::Male_Commander_Quest());
        Quest::Start(Consts::Male_Commoner_Quest());
        Quest::Start(Consts::Male_Commoner_Accented_Quest());
        Quest::Start(Consts::Male_Condescending_Quest());
        Quest::Start(Consts::Male_Coward_Quest());
        Quest::Start(Consts::Male_Dark_Elf_Quest());
        Quest::Start(Consts::Male_Drunk_Quest());
        Quest::Start(Consts::Male_Elf_Haughty_Quest());
        Quest::Start(Consts::Male_Even_Toned_Quest());
        Quest::Start(Consts::Male_Even_Toned_Accented_Quest());
        Quest::Start(Consts::Male_Forsworn_Quest());
        Quest::Start(Consts::Male_Guard_Quest());
        Quest::Start(Consts::Male_Khajiit_Quest());
        Quest::Start(Consts::Male_Nord_Quest());
        Quest::Start(Consts::Male_Nord_Commander_Quest());
        Quest::Start(Consts::Male_Old_Grumpy_Quest());
        Quest::Start(Consts::Male_Old_Kindly_Quest());
        Quest::Start(Consts::Male_Orc_Quest());
        Quest::Start(Consts::Male_Other_Quest());
        Quest::Start(Consts::Male_Sly_Cynical_Quest());
        Quest::Start(Consts::Male_Soldier_Quest());
        Quest::Start(Consts::Male_Warlock_Quest());
        Quest::Start(Consts::Male_Young_Eager_Quest());
    }

    void Main_t::u_0_9_16()
    {
        Start_Voice_Quests();
    }

    void Main_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Main_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("OnInit", 0, void, Init_Mod);

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
                        if (Game::Is_NPCP_Installed()) {
                            Modules::Main_t::Self()->Load_Mod();
                        }
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

        REGISTER_NAMESPACE(Actor2);
        REGISTER_NAMESPACE(Consts);
        REGISTER_NAMESPACE(Papyrus::Active_Magic_Effects);
        REGISTER_NAMESPACE(Papyrus::Packages);
        REGISTER_NAMESPACE(Papyrus::Perks);
        REGISTER_NAMESPACE(Papyrus::References);
        REGISTER_NAMESPACE(Papyrus::Topic_Infos);

        #undef REGISTER_NAMESPACE

        #define REGISTER_TYPE(TYPE_)                                            \
        M                                                                       \
            TYPE_::Register_Me(reinterpret_cast<Virtual_Machine_t*>(registry)); \
            _MESSAGE(DOTICU_NPCP_PRINT_PREFIX "Added " #TYPE_ " functions.");   \
        W

        REGISTER_TYPE(Modules::Main_t);
        REGISTER_TYPE(Modules::Funcs_t);
        REGISTER_TYPE(Modules::Vars_t);
        REGISTER_TYPE(Modules::Logs_t);

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
        REGISTER_TYPE(Papyrus::Outfit2_t);

        REGISTER_TYPE(Modules::Control::Commands_t);

        REGISTER_TYPE(Papyrus::Keys_t);

        REGISTER_TYPE(MCM::SKI_Config_Base_t);
        REGISTER_TYPE(MCM::Main_t);
        REGISTER_TYPE(MCM::Followers_t);
        REGISTER_TYPE(MCM::Members_t);
        REGISTER_TYPE(MCM::Mannequins_t);
        REGISTER_TYPE(MCM::Member_t);
        REGISTER_TYPE(MCM::Settlers_t);
        REGISTER_TYPE(MCM::Filter_t);
        REGISTER_TYPE(MCM::Chests_t);
        REGISTER_TYPE(MCM::Settings_t);
        REGISTER_TYPE(MCM::Hotkeys_t);
        REGISTER_TYPE(MCM::Logs_t);

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
