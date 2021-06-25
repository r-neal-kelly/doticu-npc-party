/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party_settler_eater.h"
#include "party_settler_guard.h"
#include "party_settler_sandboxer.h"
#include "party_settler_sitter.h"
#include "party_settler_sleeper.h"
#include "party_settler_slot.h"

namespace doticu_skylib { namespace doticu_npcp {

    Settler_Slot_t::Save_t::Save_t() :
        settler_type()
    {
    }

    Settler_Slot_t::Save_t::~Save_t()
    {
    }

    void Settler_Slot_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->settler_type);
    }

    void Settler_Slot_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->settler_type);
    }

    Settler_Slot_t::State_t::State_t() :
        save(),

        settler_interface()
    {
    }

    Settler_Slot_t::State_t::~State_t()
    {
    }

    Settler_Slot_t::Settler_Slot_t() :
        state()
    {
    }

    Settler_Slot_t::Settler_Slot_t(some<Settler_Type_e> settler_type) :
        state()
    {
        SKYLIB_ASSERT_SOME(settler_type);

        Save().settler_type = settler_type;
    }

    Settler_Slot_t::~Settler_Slot_t()
    {
    }

    void Settler_Slot_t::On_After_New_Game()
    {
        if (Is_Active()) {
            State().settler_interface.On_After_New_Game();
        }
    }

    void Settler_Slot_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        if (Is_Active()) {
            State().settler_interface.On_Before_Save_Game(file);
        }
    }

    void Settler_Slot_t::On_After_Save_Game()
    {
        if (Is_Active()) {
            State().settler_interface.On_After_Save_Game();
        }
    }

    void Settler_Slot_t::On_Before_Load_Game()
    {
        if (Is_Active()) {
            State().settler_interface.On_Before_Load_Game();
        }
    }

    void Settler_Slot_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        if (Is_Active()) {
            State().settler_interface.On_After_Load_Game(file);
        }
    }

    void Settler_Slot_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        if (Is_Active()) {
            State().settler_interface.On_After_Load_Game(file, version_to_update);
        }
    }

    Settler_Slot_t::State_t& Settler_Slot_t::State()
    {
        return this->state;
    }

    const Settler_Slot_t::State_t& Settler_Slot_t::State() const
    {
        return this->state;
    }

    Settler_Slot_t::Save_t& Settler_Slot_t::Save()
    {
        return State().save;
    }

    const Settler_Slot_t::Save_t& Settler_Slot_t::Save() const
    {
        return State().save;
    }

    Bool_t Settler_Slot_t::Is_Active()
    {
        return Save().settler_type != none<Settler_Type_e>();
    }

}}
