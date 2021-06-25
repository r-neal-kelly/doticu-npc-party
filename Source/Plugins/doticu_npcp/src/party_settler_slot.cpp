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
        type()
    {
    }

    Settler_Slot_t::Save_t::~Save_t()
    {
    }

    void Settler_Slot_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->type);
    }

    void Settler_Slot_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->type);
    }

    Settler_Slot_t::State_t::State_t() :
        save(),

        settler()
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

        Save().type = settler_type;
    }

    Settler_Slot_t::~Settler_Slot_t()
    {
    }

    void Settler_Slot_t::On_After_New_Game()
    {
        if (Is_Active()) {
            State().settler.On_After_New_Game();
        }
    }

    void Settler_Slot_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        if (Is_Active()) {
            State().settler.On_Before_Save_Game(file);
        }
    }

    void Settler_Slot_t::On_After_Save_Game()
    {
        if (Is_Active()) {
            State().settler.On_After_Save_Game();
        }
    }

    void Settler_Slot_t::On_Before_Load_Game()
    {
        if (Is_Active()) {
            State().settler.On_Before_Load_Game();
        }
    }

    void Settler_Slot_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        if (Is_Active()) {
            State().settler.On_After_Load_Game(file);
        }
    }

    void Settler_Slot_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        if (Is_Active()) {
            State().settler.On_After_Load_Game(file, version_to_update);
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

    Bool_t Settler_Slot_t::Is_Active() const
    {
        return Save().type != none<Settler_Type_e>();
    }

    some<Settler_Type_e> Settler_Slot_t::Type() const
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().type();
    }

    some<Settler_Type_i*> Settler_Slot_t::Settler()
    {
        SKYLIB_ASSERT(Is_Active());

        return &State().settler;
    }

    some<const Settler_Type_i*> Settler_Slot_t::Settler() const
    {
        SKYLIB_ASSERT(Is_Active());

        return &State().settler;
    }

    void Settler_Slot_t::Activate(some<Settler_Type_e> type, some<Settler_Time_t> time, some<Settler_Marker_t> marker)
    {
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT_SOME(time);
        SKYLIB_ASSERT_SOME(marker);

        Deactivate();

        Save().type = type();
        State().settler.Activate(time, marker);
    }

    void Settler_Slot_t::Deactivate()
    {
        State().settler.Deactivate();

        this->~Settler_Slot_t();
        new (this) Settler_Slot_t();
    }

}}
