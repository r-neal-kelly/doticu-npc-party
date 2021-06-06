/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_list.h"

#include "consts.h"
#include "npcp.inl"
#include "party_settler_guard.h"

namespace doticu_skylib { namespace doticu_npcp {

    some<Form_List_t*> Settler_Guard_t::Packages()
    {
        return Consts_t::NPCP::Form_List::Settler_Guard_Packages();
    }

    some<Misc_t*> Settler_Guard_t::Token()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Guard();
    }

    Settler_Guard_t::Save_t::Save_t() :
        flags(),
        time(),
        duration(),
        marker(),
        radius(),
        speed()
    {
    }

    Settler_Guard_t::Save_t::~Save_t()
    {
    }

    void Settler_Guard_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->flags);
        NPCP.Write(file, this->time);
        NPCP.Write(file, this->duration);
        this->marker.Write(file);
        NPCP.Write(file, this->radius);
        NPCP.Write(file, this->speed);
    }

    void Settler_Guard_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->flags);
        NPCP.Read(file, this->time);
        NPCP.Read(file, this->duration);
        this->marker.Read(file);
        NPCP.Read(file, this->radius);
        NPCP.Read(file, this->speed);
    }

    Settler_Guard_t::State_t::State_t() :
        save()
    {
    }

    Settler_Guard_t::State_t::~State_t()
    {
    }

    Settler_Guard_t::Settler_Guard_t() :
        state()
    {
    }

    Settler_Guard_t::~Settler_Guard_t()
    {
    }

    void Settler_Guard_t::On_After_New_Game()
    {
    }

    void Settler_Guard_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
    }

    void Settler_Guard_t::On_After_Save_Game()
    {
    }

    void Settler_Guard_t::On_Before_Load_Game()
    {
    }

    void Settler_Guard_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
    }

    void Settler_Guard_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);
    }

    Settler_Guard_t::State_t& Settler_Guard_t::State()
    {
        return this->state;
    }

    Settler_Guard_t::Save_t& Settler_Guard_t::Save()
    {
        return State().save;
    }

    Bool_t Settler_Guard_t::Is_Enabled()
    {
        return Save().flags.Is_Flagged(Flags_e::IS_ENABLED);
    }

    void Settler_Guard_t::Is_Enabled(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::IS_ENABLED, value);
    }

    some<Package_t*> Settler_Guard_t::Package(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        maybe<Package_t*> package = Packages()->Static_At(settler_id())->As_Package();
        SKYLIB_ASSERT_SOME(package);

        return package();
    }

}}
