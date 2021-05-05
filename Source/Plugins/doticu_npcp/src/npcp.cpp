/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "main.h"
#include "npcp.h"

namespace doticu_npcp {

    NPCP_t::NPCP_t(const some<const char*> plugin_name) :
        SKSE_Plugin_t(plugin_name,
                      Consts_t::Skyrim::Version::Required(),
                      Operator_e::EQUAL_TO,
                      Consts_t::SKSE::Version::Minimum(),
                      Operator_e::GREATER_THAN_OR_EQUAL_TO),
        main(none<Main_t*>())
    {
    }

    NPCP_t::~NPCP_t()
    {
        if (this->main) {
            delete this->main();
            this->main = none<Main_t*>();
        }
    }

    Bool_t NPCP_t::On_Register(some<V::Machine_t*> machine)
    {
        Main_t::Register_Me(machine);
        return true;
    }

    void NPCP_t::On_Message(some<SKSE_Message_t*> message)
    {
        // SaveGame and PreLoadGame will give us the savefile path as message->data, and it's char length too
        if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
            if (this->main) {
                this->main->Before_Save();
            }
        } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
            if (this->main) {
                this->main->Before_Load();
            }
        } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data) {
            if (this->main) {
                this->main->After_Load();
            }
        } else if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
            if (this->main) {
                this->main->New_Game();
            }
        } else if (message->type == SKSEMessagingInterface::kMessage_DataLoaded) {
            if (Is_Active()) {
                this->main = new Main_t(Consts_t::NPCP::Quest::Main());
            }
        }
    }

    Bool_t NPCP_t::Is_Active()
    {
        return !!Consts_t::NPCP::Mod();
    }

    Main_t& NPCP_t::Main()
    {
        SKYLIB_ASSERT(this->main);
        return *this->main;
    }

    extern NPCP_t NPCP("doticu_npcp");

}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_npcp::NPCP);
