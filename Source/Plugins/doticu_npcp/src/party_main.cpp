/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/script.h"

#include "consts.h"
#include "party_displays.h"
#include "party_expoees.h"
#include "party_followers.h"
#include "party_main.h"
#include "party_members.h"
#include "party_settlers.h"

namespace doticu_npcp { namespace Party {

    void Main_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        Members_t::Register_Me(machine);
        Settlers_t::Register_Me(machine);
        Expoees_t::Register_Me(machine);
        Displays_t::Register_Me(machine);
        Followers_t::Register_Me(machine);
    }

    Main_t::Main_t(Bool_t is_new_game) :
        members(new Members_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        settlers(new Settlers_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        expoees(new Expoees_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        displays(new Displays_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        followers(new Followers_t(Consts_t::NPCP::Quest::Followers(), is_new_game)),
        scripts(Vector_t<maybe<Script_t*>>(Consts_t::NPCP::Int::MAX_MEMBERS)),
        update_ais(Vector_t<maybe<Member_Update_AI_e>>(Consts_t::NPCP::Int::MAX_MEMBERS, Member_Update_AI_e::RESET_AI))
    {
    }

    Main_t::Main_t(const Version_t<u16> version_to_update) :
        members(new Members_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        settlers(new Settlers_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        expoees(new Expoees_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        displays(new Displays_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        followers(new Followers_t(Consts_t::NPCP::Quest::Followers(), version_to_update)),
        scripts(Vector_t<maybe<Script_t*>>(Consts_t::NPCP::Int::MAX_MEMBERS)),
        update_ais(Vector_t<maybe<Member_Update_AI_e>>(Consts_t::NPCP::Int::MAX_MEMBERS, Member_Update_AI_e::RESET_AI))
    {
    }

    Main_t::~Main_t()
    {
        for (size_t idx = 0, end = Consts_t::NPCP::Int::MAX_MEMBERS; idx < end; idx += 1) {
            maybe<Script_t*> script = this->scripts[idx];
            if (script) {
                Script_t::Destroy(script());
            }
        }
    }

    void Main_t::Before_Save()
    {
        members->Before_Save();
        settlers->Before_Save();
        expoees->Before_Save();
        displays->Before_Save();
        followers->Before_Save();
    }

    void Main_t::After_Save()
    {
        members->After_Save();
        settlers->After_Save();
        expoees->After_Save();
        displays->After_Save();
        followers->After_Save();
    }

    Members_t& Main_t::Members()
    {
        return *this->members;
    }

    Settlers_t& Main_t::Settlers()
    {
        return *this->settlers;
    }

    Expoees_t& Main_t::Expoees()
    {
        return *this->expoees;
    }

    Displays_t& Main_t::Displays()
    {
        return *this->displays;
    }

    Followers_t& Main_t::Followers()
    {
        return *this->followers;
    }

    some<Script_t*> Main_t::Script(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));

        maybe<Script_t*>& script = this->scripts[valid_member_id()];
        if (!script) {
            script = Script_t::Create()();
            SKYLIB_ASSERT_SOME(script);
        }

        return script();
    }

    void Main_t::Update_AI(some<Member_ID_t> valid_member_id, some<Member_Update_AI_e> update_ai)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(update_ai);

        maybe<Member_Update_AI_e>& this_update_ai = this->update_ais[valid_member_id()];
        if (this_update_ai != Member_Update_AI_e::RESET_AI) {
            this_update_ai = update_ai;
        }
    }

    void Main_t::Tokenize(some<Member_ID_t> valid_member_id,
                          some<Bound_Object_t*> object,
                          Container_Entry_Count_t count)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(count > 0);

        some<Actor_t*> actor = Members().Actor(valid_member_id);
        Reference_Container_t container = actor->Container();
        some<Reference_Container_Entry_t*> entry = container.Some_Entry(object);
        if (entry->Non_Extra_Lists_Count() != count) {
            entry->Decrement_Count(container, Container_Entry_Count_t::_MAX_);
            entry->Increment_Count(container, count);
        }
    }

    void Main_t::Untokenize(some<Member_ID_t> valid_member_id,
                            some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(object);

        some<Actor_t*> actor = Members().Actor(valid_member_id);
        Reference_Container_t container = actor->Container();
        maybe<Reference_Container_Entry_t*> entry = container.Maybe_Entry(object);
        if (entry && entry->Non_Extra_Lists_Count() > 0) {
            entry->Decrement_Count(container, Container_Entry_Count_t::_MAX_);
        }
    }

    void Main_t::Enforce(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));

        Members_t& members = Members();
        Settlers_t& settlers = Settlers();
        Member_ID_t::value_type id = valid_member_id();

        members.Enforce(id);
        settlers.Enforce(id);

        maybe<Member_Update_AI_e>& update_ai = this->update_ais[id];
        if (update_ai == Member_Update_AI_e::RESET_AI) {
            members.Actor(id)->Reset_AI();
        } else if (update_ai == Member_Update_AI_e::EVALUATE_PACKAGE) {
            members.Actor(id)->Evaluate_Package(true, false);
        }
        update_ai = Member_Update_AI_e::_NONE_;
    }

    void Main_t::Enforce()
    {
        Members_t& members = Members();
        for (size_t idx = 0, end = Consts_t::NPCP::Int::MAX_MEMBERS; idx < end; idx += 1) {
            if (members.Has_Member(idx)) {
                Enforce(idx);
            }
        }
    }

}}
