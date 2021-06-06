/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party.h"
#include "party_expoees.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Expoees_t::Save_t::Save_t() :
        sort_type(DEFAULT_SORT_TYPE)
    {
    }

    Expoees_t::Save_t::~Save_t()
    {
    }

    void Expoees_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->sort_type);
    }

    void Expoees_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->sort_type);
    }

    Expoees_t::State_t::State_t() :
        save(),

        expoees()
    {
    }

    Expoees_t::State_t::~State_t()
    {
    }

    Party_t& Expoees_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Expoees_t::Members()
    {
        return Party().Members();
    }

    Expoees_t::Expoees_t() :
        state()
    {
    }

    Expoees_t::~Expoees_t()
    {
    }

    void Expoees_t::On_After_New_Game()
    {
        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            State().expoees[idx].On_After_New_Game();
        }
    }

    void Expoees_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            State().expoees[idx].On_Before_Save_Game(file);
        }
    }

    void Expoees_t::On_After_Save_Game()
    {
        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            State().expoees[idx].On_After_Save_Game();
        }
    }

    void Expoees_t::On_Before_Load_Game()
    {
        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            State().expoees[idx].On_Before_Load_Game();
        }
    }

    void Expoees_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            State().expoees[idx].On_After_Load_Game(file);
        }
    }

    void Expoees_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            State().expoees[idx].On_After_Load_Game(file, version_to_update);
        }
    }

    void Expoees_t::On_Update()
    {
    }

    Expoees_t::State_t& Expoees_t::State()
    {
        return this->state;
    }

    Expoees_t::Save_t& Expoees_t::Save()
    {
        return State().save;
    }

    Expoee_t& Expoees_t::Expoee(some<Expoee_ID_t> expoee_id)
    {
        SKYLIB_ASSERT_SOME(expoee_id);

        return State().expoees[expoee_id()];
    }

    maybe<Expoee_t*> Expoees_t::Active_Expoee(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        Member_t& member = Members().Member(member_id);
        if (member.Is_Active()) {
            return member.Expoee();
        } else {
            return none<Expoee_t*>();
        }
    }

}}
