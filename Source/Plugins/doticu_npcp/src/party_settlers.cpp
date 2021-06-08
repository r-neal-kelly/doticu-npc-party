/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"

#include "npcp.inl"
#include "party.h"
#include "party_settlers.h"

namespace doticu_skylib { namespace doticu_npcp {

    Settlers_t::Save_t::Save_t()
    {
    }

    Settlers_t::Save_t::~Save_t()
    {
    }

    void Settlers_t::Save_t::Write(std::ofstream& file)
    {
    }

    void Settlers_t::Save_t::Read(std::ifstream& file)
    {
    }

    Settlers_t::State_t::State_t() :
        save(),

        settlers()
    {
    }

    Settlers_t::State_t::~State_t()
    {
    }

    Party_t& Settlers_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Settlers_t::Members()
    {
        return Party().Members();
    }

    Settlers_t::Settlers_t() :
        state()
    {
    }

    Settlers_t::~Settlers_t()
    {
    }

    void Settlers_t::On_After_New_Game()
    {
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            State().settlers[idx].On_After_New_Game();
        }
    }

    void Settlers_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            State().settlers[idx].On_Before_Save_Game(file);
        }
    }

    void Settlers_t::On_After_Save_Game()
    {
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            State().settlers[idx].On_After_Save_Game();
        }
    }

    void Settlers_t::On_Before_Load_Game()
    {
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            State().settlers[idx].On_Before_Load_Game();
        }
    }

    void Settlers_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            State().settlers[idx].On_After_Load_Game(file);
        }
    }

    void Settlers_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            State().settlers[idx].On_After_Load_Game(file, version_to_update);
        }
    }

    void Settlers_t::On_Update()
    {
    }

    Settlers_t::State_t& Settlers_t::State()
    {
        return this->state;
    }

    Settlers_t::Save_t& Settlers_t::Save()
    {
        return State().save;
    }

    Settler_t& Settlers_t::Settler(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return State().settlers[settler_id()];
    }

    maybe<Settler_t*> Settlers_t::Settler(Member_t& member)
    {
        return member.Settler();
    }

    maybe<Settler_t*> Settlers_t::Settler(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            Settler_t& settler = Settler(idx);
            if (settler.Is_Active() && settler.Actor() == actor) {
                return &settler;
            }
        }
        return none<Settler_t*>();
    }

    maybe<Settler_ID_t> Settlers_t::Inactive_ID()
    {
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            Settler_t& settler = Settler(idx);
            if (!settler.Is_Active()) {
                return idx;
            }
        }
        return none<Settler_ID_t>();
    }

    size_t Settlers_t::Active_Count()
    {
        size_t count = 0;
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            if (Settler(idx).Is_Active()) {
                count += 1;
            }
        }
        return count;
    }

    size_t Settlers_t::Inactive_Count()
    {
        return MAX_SETTLERS - Active_Count();
    }

    Bool_t Settlers_t::Has(Member_t& member)
    {
        return member.Is_Settler();
    }

    Bool_t Settlers_t::Has(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Settler(actor) != none<Settler_t*>();
    }

    maybe<Settler_t*> Settlers_t::Add(Member_t& member)
    {
        if (member.Is_Active() && !Has(member)) {
            maybe<Settler_ID_t> settler_id = Inactive_ID();
            if (settler_id) {
                Settler_t& settler = Settler(settler_id());
                settler.~Settler_t();
                new (&settler) Settler_t(member.Member_ID(), settler_id());
                if (settler.Is_Active()) {
                    return &settler;
                } else {
                    return none<Settler_t*>();
                }
            } else {
                return none<Settler_t*>();
            }
        } else {
            return none<Settler_t*>();
        }
    }

    maybe<Settler_t*> Settlers_t::Add(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Member_t*> member = Members().Member(actor);
        if (member) {
            return Add(*member);
        } else {
            member = Members().Add(actor, false);
            if (member) {
                return Add(*member);
            } else {
                return none<Settler_t*>();
            }
        }
    }

    Bool_t Settlers_t::Remove(Settler_t& settler)
    {
        if (settler.Is_Active()) {
            settler.Reset();

            return true;
        } else {
            return false;
        }
    }

    Bool_t Settlers_t::Remove(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Settler_t*> settler = Settler(actor);
        if (settler) {
            return Remove(*settler);
        } else {
            return false;
        }
    }

    void Settlers_t::Reset_Options()
    {
        State().save.~Save_t();
        new (&State().save) Save_t();
    }

}}




/*
namespace doticu_npcp { namespace Party {

    const Settler_Duration_t    Settlers_t::DEFAULT_DURATION(DEFAULT_DURATION_HOURS, DEFAULT_DURATION_MINUTES);
    const Settler_Time_t        Settlers_t::DEFAULT_TIME(DEFAULT_TIME_AM_PM, DEFAULT_TIME_HOUR, DEFAULT_TIME_MINUTE);

    Bool_t Settlers_t::Has_Settler(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return
            Is_Enabled<Sandboxer_t>(settler_id) ||
            Is_Enabled<Sleeper_t>(settler_id) ||
            Is_Enabled<Sitter_t>(settler_id) ||
            Is_Enabled<Eater_t>(settler_id) ||
            Is_Enabled<Guard_t>(settler_id);
        return false;
    }

    Bool_t Settlers_t::Has_Settler(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        if (Members().Has_Member(member_id)) {
            return Has_Settler(some<Settler_ID_t>(member_id()));
        } else {
            return false;
        }
    }

    Bool_t Settlers_t::Has_Settler(some<Actor_t*> actor)
    {
        maybe<Member_ID_t> valid_member_id = Members().Used_Member_ID(actor);
        if (valid_member_id) {
            return Has_Settler(some<Settler_ID_t>(valid_member_id()));
        } else {
            return false;
        }
    }

    void Settlers_t::Bool(some<Package_t*> package,
                          Settler_Value_Index_e index,
                          Bool_t value,
                          Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(package->data);

        if (package->data->Bool(index) != value) {
            package->data->Bool(index, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::Float(some<Package_t*> package,
                           Settler_Value_Index_e index,
                           Float_t value,
                           Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(package->data);

        if (package->data->Float(index) != value) {
            package->data->Float(index, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::General_Flag(some<Package_t*> package,
                                  Package_Flags_e general_flag,
                                  Bool_t value,
                                  Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);

        if (package->package_flags.Is_Flagged(general_flag) != value) {
            package->package_flags.Is_Flagged(general_flag, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::Interrupt_Flag(some<Package_t*> package,
                                    Package_Interrupt_Flags_e interrupt_flag,
                                    Bool_t value,
                                    Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);

        if (package->interrupt_flags.Is_Flagged(interrupt_flag) != value) {
            package->interrupt_flags.Is_Flagged(interrupt_flag, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::Location(some<Package_t*> package,
                              Settler_Value_Index_e index,
                              some<Reference_t*> marker,
                              some<Settler_Radius_t> radius,
                              Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(package->data);

        maybe<Package_Location_t*> location = package->data->Location(index);
        SKYLIB_ASSERT_SOME(location);

        if (location->Reference() != marker) {
            location->Reference(marker());
            do_reset_ai = true;
        }

        if (location->Radius() != radius()) {
            location->Radius(radius());
            do_reset_ai = true;
        }
    }

    void Settlers_t::Schedule(some<Package_t*> package,
                              maybe<Settler_Time_t> time,
                              maybe<Settler_Duration_t> duration,
                              Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);

        if (time) {
            s32 hour = time.Military_Hour();
            if (package->schedule.hour != hour) {
                package->schedule.hour = hour;
                do_reset_ai = true;
            }
            s32 minute = time.Minute()();
            if (package->schedule.minute != minute) {
                package->schedule.minute = minute;
                do_reset_ai = true;
            }
        } else {
            if (package->schedule.hour != -1) {
                package->schedule.hour = -1;
                do_reset_ai = true;
            }
            if (package->schedule.minute != -1) {
                package->schedule.minute = -1;
                do_reset_ai = true;
            }
        }

        if (duration) {
            s32 duration_in_minutes = duration.Total_Minutes();
            if (package->schedule.duration_in_minutes != duration_in_minutes) {
                package->schedule.duration_in_minutes = duration_in_minutes;
                do_reset_ai = true;
            }
        } else {
            if (package->schedule.duration_in_minutes != 0) {
                package->schedule.duration_in_minutes = 0;
                do_reset_ai = true;
            }
        }
    }

    void Settlers_t::Speed(some<Package_t*> package,
                           some<Settler_Speed_e> speed,
                           Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(speed);

        General_Flag(package, Package_Flags_e::ALLOW_PREFERRED_SPEED, true, do_reset_ai);

        if (package->preferred_speed != speed) {
            package->preferred_speed = speed();
            do_reset_ai = true;
        }
    }

    void Settlers_t::Enforce(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Member_t member(settler_id);
        if (member) {
            Main_t& main = Main();
            Bool_t do_reset_ai = false;
            Bool_t is_sneak = member.Is_Sneak();

            if (Is_Enabled<Sandboxer_t>(settler_id)) {
                Always_Sneak<Sandboxer_t>(settler_id, is_sneak);
                Enforce_Package<Sandboxer_t>(settler_id, do_reset_ai);
                member.Tokenize(Token<Sandboxer_t>());
            } else {
                member.Untokenize(Token<Sandboxer_t>());
            }

            if (Is_Enabled<Sleeper_t>(settler_id)) {
                Always_Sneak<Sleeper_t>(settler_id, is_sneak);
                Enforce_Package<Sleeper_t>(settler_id, do_reset_ai);

                maybe<Reference_t*> bed = Bed<Sleeper_t>(settler_id);
                if (bed) {
                    if (bed->Is_Disabled()) {
                        bed->Enable();
                        do_reset_ai = true;
                    }
                    some<Actor_Base_t*> custom_base = member.Custom_Base();
                    maybe<Form_Owner_t> owner = bed->x_list.Owner();
                    if (!owner.Has_Value() || owner.Value().As_Actor_Base() != custom_base) {
                        bed->x_list.Owner(custom_base); // this may need to be cleared in dtor?
                        do_reset_ai = true;
                    }
                }

                member.Tokenize(Token<Sleeper_t>());
            } else {
                member.Untokenize(Token<Sleeper_t>());
            }

            if (Is_Enabled<Sitter_t>(settler_id)) {
                Always_Sneak<Sitter_t>(settler_id, is_sneak);
                Enforce_Package<Sitter_t>(settler_id, do_reset_ai);
                member.Tokenize(Token<Sitter_t>());
            } else {
                member.Untokenize(Token<Sitter_t>());
            }

            if (Is_Enabled<Eater_t>(settler_id)) {
                Always_Sneak<Eater_t>(settler_id, is_sneak);
                Enforce_Package<Eater_t>(settler_id, do_reset_ai);
                member.Tokenize(Token<Eater_t>());
            } else {
                member.Untokenize(Token<Eater_t>());
            }

            if (Is_Enabled<Guard_t>(settler_id)) {
                Always_Sneak<Guard_t>(settler_id, is_sneak);
                Enforce_Package<Guard_t>(settler_id, do_reset_ai);
                member.Tokenize(Token<Guard_t>());
            } else {
                member.Untokenize(Token<Guard_t>());
            }

            if (do_reset_ai) {
                Main().Update_AI(settler_id, Member_Update_AI_e::RESET_AI);
            }
        }
    }

}}
*/