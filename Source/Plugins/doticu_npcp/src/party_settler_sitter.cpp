/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_list.h"
#include "doticu_skylib/reference.h"

#include "consts.h"
#include "npcp.inl"
#include "party_settler_sitter.h"

namespace doticu_skylib { namespace doticu_npcp {

    some<Form_List_t*> Settler_Sitter_t::Packages()
    {
        return Consts_t::NPCP::Form_List::Settler_Sitter_Packages();
    }

    some<Misc_t*> Settler_Sitter_t::Token()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sitter();
    }

    Settler_Sitter_t::Save_t::Save_t() :
        seat()
    {
    }

    Settler_Sitter_t::Save_t::~Save_t()
    {
    }

    void Settler_Sitter_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write_Form(file, this->seat);
    }

    void Settler_Sitter_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read_Form(file, this->seat);
    }

    Settler_Sitter_t::State_t::State_t() :
        save()
    {
    }

    Settler_Sitter_t::State_t::~State_t()
    {
    }

    Settler_Sitter_t::Settler_Sitter_t() :
        state()
    {
    }

    Settler_Sitter_t::~Settler_Sitter_t()
    {
    }

    void Settler_Sitter_t::On_After_New_Game()
    {
        Settler_Type_i::On_After_New_Game();
    }

    void Settler_Sitter_t::On_Before_Save_Game(std::ofstream& file)
    {
        Settler_Type_i::On_Before_Save_Game(file);

        Save().Write(file);
    }

    void Settler_Sitter_t::On_After_Save_Game()
    {
        Settler_Type_i::On_After_Save_Game();
    }

    void Settler_Sitter_t::On_Before_Load_Game()
    {
        Settler_Type_i::On_Before_Load_Game();
    }

    void Settler_Sitter_t::On_After_Load_Game(std::ifstream& file)
    {
        Settler_Type_i::On_After_Load_Game(file);

        Save().Read(file);
    }

    void Settler_Sitter_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Settler_Type_i::On_After_Load_Game(file, version_to_update);

        Save().Read(file);
    }

    Settler_Sitter_t::State_t& Settler_Sitter_t::State()
    {
        return this->state;
    }

    const Settler_Sitter_t::State_t& Settler_Sitter_t::State() const
    {
        return this->state;
    }

    Settler_Sitter_t::Save_t& Settler_Sitter_t::Save()
    {
        return State().save;
    }

    const Settler_Sitter_t::Save_t& Settler_Sitter_t::Save() const
    {
        return State().save;
    }

    Bool_t Settler_Sitter_t::Only_Preferred_Path()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ONLY_PREFERRED_PATH);
    }

    void Settler_Sitter_t::Only_Preferred_Path(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ONLY_PREFERRED_PATH, value);
    }

    Bool_t Settler_Sitter_t::Stop_Movement()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::STOP_MOVEMENT);
    }

    void Settler_Sitter_t::Stop_Movement(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::STOP_MOVEMENT, value);
    }

    some<Package_t*> Settler_Sitter_t::Package(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        maybe<Package_t*> package = Packages()->Static_At(settler_id())->As_Package();
        SKYLIB_ASSERT_SOME(package);

        return package();
    }

}}
