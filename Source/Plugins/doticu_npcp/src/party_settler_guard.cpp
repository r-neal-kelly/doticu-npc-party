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

    Settler_Guard_t::Save_t::Save_t()
    {
    }

    Settler_Guard_t::Save_t::~Save_t()
    {
    }

    void Settler_Guard_t::Save_t::Write(std::ofstream& file)
    {
    }

    void Settler_Guard_t::Save_t::Read(std::ifstream& file)
    {
    }

    Settler_Guard_t::State_t::State_t() :
        save()
    {
    }

    Settler_Guard_t::State_t::~State_t()
    {
    }

    Settler_Guard_t::Settler_Guard_t() :
        Settler_Type_i(),
        state()
    {
    }

    Settler_Guard_t::~Settler_Guard_t()
    {
    }

    void Settler_Guard_t::On_After_New_Game()
    {
        Settler_Type_i::On_After_New_Game();
    }

    void Settler_Guard_t::On_Before_Save_Game(std::ofstream& file)
    {
        Settler_Type_i::On_Before_Save_Game(file);

        Save().Write(file);
    }

    void Settler_Guard_t::On_After_Save_Game()
    {
        Settler_Type_i::On_After_Save_Game();
    }

    void Settler_Guard_t::On_Before_Load_Game()
    {
        Settler_Type_i::On_Before_Load_Game();
    }

    void Settler_Guard_t::On_After_Load_Game(std::ifstream& file)
    {
        Settler_Type_i::On_After_Load_Game(file);

        Save().Read(file);
    }

    void Settler_Guard_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Settler_Type_i::On_After_Load_Game(file, version_to_update);

        Save().Read(file);
    }

    Settler_Guard_t::State_t& Settler_Guard_t::State()
    {
        return this->state;
    }

    const Settler_Guard_t::State_t& Settler_Guard_t::State() const
    {
        return this->state;
    }

    Settler_Guard_t::Save_t& Settler_Guard_t::Save()
    {
        return State().save;
    }

    const Settler_Guard_t::Save_t& Settler_Guard_t::Save() const
    {
        return State().save;
    }

    some<Package_t*> Settler_Guard_t::Package(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        maybe<Package_t*> package = Packages()->Static_At(settler_id())->As_Package();
        SKYLIB_ASSERT_SOME(package);

        return package();
    }

}}
