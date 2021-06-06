/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
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

    Settler_Slot_t::Settler_u::Settler_u() :
        sandboxer()
    {
    }

    Settler_Slot_t::Settler_u::~Settler_u()
    {
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

        Save().settler_type = settler_type;
    }

    Settler_Slot_t::~Settler_Slot_t()
    {
    }

    void Settler_Slot_t::On_After_New_Game()
    {
        if (Save().settler_type == Settler_Type_e::SANDBOXER)       State().settler.sandboxer.On_After_New_Game();
        else if (Save().settler_type == Settler_Type_e::SLEEPER)    State().settler.sleeper.On_After_New_Game();
        else if (Save().settler_type == Settler_Type_e::SITTER)     State().settler.sitter.On_After_New_Game();
        else if (Save().settler_type == Settler_Type_e::EATER)      State().settler.eater.On_After_New_Game();
        else if (Save().settler_type == Settler_Type_e::GUARD)      State().settler.guard.On_After_New_Game();
    }

    void Settler_Slot_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        if (Save().settler_type == Settler_Type_e::SANDBOXER)       State().settler.sandboxer.On_Before_Save_Game(file);
        else if (Save().settler_type == Settler_Type_e::SLEEPER)    State().settler.sleeper.On_Before_Save_Game(file);
        else if (Save().settler_type == Settler_Type_e::SITTER)     State().settler.sitter.On_Before_Save_Game(file);
        else if (Save().settler_type == Settler_Type_e::EATER)      State().settler.eater.On_Before_Save_Game(file);
        else if (Save().settler_type == Settler_Type_e::GUARD)      State().settler.guard.On_Before_Save_Game(file);
    }

    void Settler_Slot_t::On_After_Save_Game()
    {
        if (Save().settler_type == Settler_Type_e::SANDBOXER)       State().settler.sandboxer.On_After_Save_Game();
        else if (Save().settler_type == Settler_Type_e::SLEEPER)    State().settler.sleeper.On_After_Save_Game();
        else if (Save().settler_type == Settler_Type_e::SITTER)     State().settler.sitter.On_After_Save_Game();
        else if (Save().settler_type == Settler_Type_e::EATER)      State().settler.eater.On_After_Save_Game();
        else if (Save().settler_type == Settler_Type_e::GUARD)      State().settler.guard.On_After_Save_Game();
    }

    void Settler_Slot_t::On_Before_Load_Game()
    {
        if (Save().settler_type == Settler_Type_e::SANDBOXER)       State().settler.sandboxer.On_Before_Load_Game();
        else if (Save().settler_type == Settler_Type_e::SLEEPER)    State().settler.sleeper.On_Before_Load_Game();
        else if (Save().settler_type == Settler_Type_e::SITTER)     State().settler.sitter.On_Before_Load_Game();
        else if (Save().settler_type == Settler_Type_e::EATER)      State().settler.eater.On_Before_Load_Game();
        else if (Save().settler_type == Settler_Type_e::GUARD)      State().settler.guard.On_Before_Load_Game();
    }

    void Settler_Slot_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        if (Save().settler_type == Settler_Type_e::SANDBOXER)       State().settler.sandboxer.On_After_Load_Game(file);
        else if (Save().settler_type == Settler_Type_e::SLEEPER)    State().settler.sleeper.On_After_Load_Game(file);
        else if (Save().settler_type == Settler_Type_e::SITTER)     State().settler.sitter.On_After_Load_Game(file);
        else if (Save().settler_type == Settler_Type_e::EATER)      State().settler.eater.On_After_Load_Game(file);
        else if (Save().settler_type == Settler_Type_e::GUARD)      State().settler.guard.On_After_Load_Game(file);
    }

    void Settler_Slot_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        if (Save().settler_type == Settler_Type_e::SANDBOXER)       State().settler.sandboxer.On_After_Load_Game(file, version_to_update);
        else if (Save().settler_type == Settler_Type_e::SLEEPER)    State().settler.sleeper.On_After_Load_Game(file, version_to_update);
        else if (Save().settler_type == Settler_Type_e::SITTER)     State().settler.sitter.On_After_Load_Game(file, version_to_update);
        else if (Save().settler_type == Settler_Type_e::EATER)      State().settler.eater.On_After_Load_Game(file, version_to_update);
        else if (Save().settler_type == Settler_Type_e::GUARD)      State().settler.guard.On_After_Load_Game(file, version_to_update);
    }

    Settler_Slot_t::State_t& Settler_Slot_t::State()
    {
        return this->state;
    }

    Settler_Slot_t::Save_t& Settler_Slot_t::Save()
    {
        return State().save;
    }

    Bool_t Settler_Slot_t::Is_Active()
    {
        return Save().settler_type != none<Settler_Type_e>();
    }

}}
