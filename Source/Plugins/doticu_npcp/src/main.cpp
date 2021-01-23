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
                                /*if (Game::Is_NPCP_Installed()) {
                                    Modules::Main_t::Self()->Load_Mod();
                                }*/
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

        METHOD("OnInit", true, void, Initialize);

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

    void Main_t::Initialize()
    {
        struct Wait_Callback_t : public V::Callback_t
        {
        public:
            void operator ()(V::Variable_t*)
            {
                if (!Consts_t::NPCP::Global::Is_Initialized()->Bool()) {
                    Consts_t::NPCP::Global::Is_Initialized()->Bool(true);
                    /*
                        Vars_t::Self()->Initialize();
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
            some<Main_t*> self;
            Wait_Callback_t(some<Main_t*> self) :
                self(self)
            {
            }
            void operator ()(V::Variable_t*)
            {
                if (Consts_t::NPCP::Global::Is_Initialized()->Bool()) {
                    /*
                        if (main->Try_Update()) {
                            std::string note =
                                "Running version " +
                                std::to_string(Consts::NPCP_Major()) + "." +
                                std::to_string(Consts::NPCP_Minor()) + "." +
                                std::to_string(Consts::NPCP_Patch());
                            Modules::Control::Commands_t::Self()->Log_Note(note.c_str(), true);
                        }
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
        V::Utils_t::Wait_Out_Of_Menu(1.0f, new Wait_Callback_t(this));
    }

    /*
    Bool_t Main_t::Has_Requirements()
    {
        // this will be check in the update routine now.
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
    }*/

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
