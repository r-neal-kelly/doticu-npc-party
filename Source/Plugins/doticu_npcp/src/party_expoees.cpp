/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"

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

    maybe<Expoee_t*> Expoees_t::Expoee(Member_t& member)
    {
        return member.Expoee();
    }

    maybe<Expoee_t*> Expoees_t::Expoee(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            Expoee_t& expoee = Expoee(idx);
            if (expoee.Is_Active() && expoee.Actor() == actor) {
                return &expoee;
            }
        }
        return none<Expoee_t*>();
    }

    maybe<Expoee_ID_t> Expoees_t::Inactive_ID()
    {
        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            Expoee_t& expoee = Expoee(idx);
            if (!expoee.Is_Active()) {
                return idx;
            }
        }
        return none<Expoee_ID_t>();
    }

    size_t Expoees_t::Active_Count()
    {
        size_t count = 0;
        for (size_t idx = 0, end = MAX_EXPOEES; idx < end; idx += 1) {
            if (Expoee(idx).Is_Active()) {
                count += 1;
            }
        }
        return count;
    }

    size_t Expoees_t::Inactive_Count()
    {
        return MAX_EXPOEES - Active_Count();
    }

    Bool_t Expoees_t::Has(Member_t& member)
    {
        return member.Is_Expoee();
    }

    Bool_t Expoees_t::Has(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Expoee(actor) != none<Expoee_t*>();
    }

    maybe<Expoee_t*> Expoees_t::Add(Member_t& member)
    {
        if (member.Is_Active() && !Has(member)) {
            maybe<Expoee_ID_t> expoee_id = Inactive_ID();
            if (expoee_id) {
                Expoee_t& expoee = Expoee(expoee_id());
                expoee.~Expoee_t();
                new (&expoee) Expoee_t(member.Member_ID(), expoee_id());
                if (expoee.Is_Active()) {
                    return &expoee;
                } else {
                    return none<Expoee_t*>();
                }
            } else {
                return none<Expoee_t*>();
            }
        } else {
            return none<Expoee_t*>();
        }
    }

    maybe<Expoee_t*> Expoees_t::Add(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Member_t*> member = Members().Member(actor);
        if (member) {
            return Add(*member);
        } else {
            member = Members().Add(actor);
            if (member) {
                return Add(*member);
            } else {
                return none<Expoee_t*>();
            }
        }
    }

    Bool_t Expoees_t::Remove(Expoee_t& expoee)
    {
        if (expoee.Is_Active()) {
            expoee.Reset();

            return true;
        } else {
            return false;
        }
    }

    Bool_t Expoees_t::Remove(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Expoee_t*> expoee = Expoee(actor);
        if (expoee) {
            return Remove(*expoee);
        } else {
            return false;
        }
    }

    void Expoees_t::Reset_Options()
    {
        State().save.~Save_t();
        new (&State().save) Save_t();
    }

}}
