/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "npcp.inl"
#include "party_settler_type_i.h"

namespace doticu_skylib { namespace doticu_npcp {

    Settler_Type_i::Save_t::Save_t() :
        flags(),
        time(),
        marker(),
        radius(),
        speed()
    {
    }

    Settler_Type_i::Save_t::~Save_t()
    {
    }

    void Settler_Type_i::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->flags);
        this->time.Write(file);
        this->marker.Write(file);
        NPCP.Write(file, this->radius);
        NPCP.Write(file, this->speed);
    }

    void Settler_Type_i::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->flags);
        this->time.Read(file);
        this->marker.Read(file);
        NPCP.Read(file, this->radius);
        NPCP.Read(file, this->speed);
    }

    Settler_Type_i::State_t::State_t() :
        save()
    {
    }

    Settler_Type_i::State_t::~State_t()
    {
    }

    Settler_Type_i::Settler_Type_i() :
        state()
    {
    }

    Settler_Type_i::~Settler_Type_i()
    {
    }

    void Settler_Type_i::On_After_New_Game()
    {
    }

    void Settler_Type_i::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
    }

    void Settler_Type_i::On_After_Save_Game()
    {
    }

    void Settler_Type_i::On_Before_Load_Game()
    {
    }

    void Settler_Type_i::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
    }

    void Settler_Type_i::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);
    }

    Settler_Type_i::State_t& Settler_Type_i::State()
    {
        return this->state;
    }

    const Settler_Type_i::State_t& Settler_Type_i::State() const
    {
        return this->state;
    }

    Settler_Type_i::Save_t& Settler_Type_i::Save()
    {
        return State().save;
    }

    const Settler_Type_i::Save_t& Settler_Type_i::Save() const
    {
        return State().save;
    }

    Bool_t Settler_Type_i::Is_Enabled()
    {
        return Save().flags.Is_Flagged(Flags_e::IS_ENABLED);
    }

    void Settler_Type_i::Is_Enabled(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::IS_ENABLED, value);
    }

    Bool_t Settler_Type_i::Allow_Swimming()
    {
        return Save().flags.Is_Flagged(Flags_e::ALLOW_SWIMMING);
    }

    void Settler_Type_i::Allow_Swimming(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALLOW_SWIMMING, value);
    }

    Bool_t Settler_Type_i::Always_Sneak()
    {
        return Save().flags.Is_Flagged(Flags_e::ALWAYS_SNEAK);
    }

    void Settler_Type_i::Always_Sneak(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALWAYS_SNEAK, value);
    }

    Bool_t Settler_Type_i::Ignore_Combat()
    {
        return Save().flags.Is_Flagged(Flags_e::IGNORE_COMBAT);
    }

    void Settler_Type_i::Ignore_Combat(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::IGNORE_COMBAT, value);
    }

    Bool_t Settler_Type_i::Keep_Weapons_Drawn()
    {
        return Save().flags.Is_Flagged(Flags_e::KEEP_WEAPONS_DRAWN);
    }

    void Settler_Type_i::Keep_Weapons_Drawn(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::KEEP_WEAPONS_DRAWN, value);
    }

    Bool_t Settler_Type_i::Hide_Weapons()
    {
        return Save().flags.Is_Flagged(Flags_e::HIDE_WEAPONS);
    }

    void Settler_Type_i::Hide_Weapons(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::HIDE_WEAPONS, value);
    }

    Bool_t Settler_Type_i::Skip_Combat_Alert()
    {
        return Save().flags.Is_Flagged(Flags_e::SKIP_COMBAT_ALERT);
    }

    void Settler_Type_i::Skip_Combat_Alert(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::SKIP_COMBAT_ALERT, value);
    }

    Bool_t Settler_Type_i::Allow_Hellos_To_Player()
    {
        return Save().flags.Is_Flagged(Flags_e::ALLOW_HELLOS_TO_PLAYER);
    }

    void Settler_Type_i::Allow_Hellos_To_Player(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALLOW_HELLOS_TO_PLAYER, value);
    }

    Bool_t Settler_Type_i::Allow_Hellos_To_NPCs()
    {
        return Save().flags.Is_Flagged(Flags_e::ALLOW_HELLOS_TO_NPCS);
    }

    void Settler_Type_i::Allow_Hellos_To_NPCs(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALLOW_HELLOS_TO_NPCS, value);
    }

    Bool_t Settler_Type_i::Allow_Idle_Chatter()
    {
        return Save().flags.Is_Flagged(Flags_e::ALLOW_IDLE_CHATTER);
    }

    void Settler_Type_i::Allow_Idle_Chatter(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALLOW_IDLE_CHATTER, value);
    }

    Bool_t Settler_Type_i::Allow_Aggro_Radius()
    {
        return Save().flags.Is_Flagged(Flags_e::ALLOW_AGGRO_RADIUS);
    }

    void Settler_Type_i::Allow_Aggro_Radius(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALLOW_AGGRO_RADIUS, value);
    }

    Bool_t Settler_Type_i::Allow_World_Interactions()
    {
        return Save().flags.Is_Flagged(Flags_e::ALLOW_WORLD_INTERACTIONS);
    }

    void Settler_Type_i::Allow_World_Interactions(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::ALLOW_WORLD_INTERACTIONS, value);
    }

    Bool_t Settler_Type_i::Comment_On_Friendly_Fire()
    {
        return Save().flags.Is_Flagged(Flags_e::COMMENT_ON_FRIENDLY_FIRE);
    }

    void Settler_Type_i::Comment_On_Friendly_Fire(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::COMMENT_ON_FRIENDLY_FIRE, value);
    }

    Bool_t Settler_Type_i::Inspect_Corpses()
    {
        return Save().flags.Is_Flagged(Flags_e::INSPECT_CORPSES);
    }

    void Settler_Type_i::Inspect_Corpses(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::INSPECT_CORPSES, value);
    }

    Bool_t Settler_Type_i::Observe_Combat()
    {
        return Save().flags.Is_Flagged(Flags_e::OBSERVE_COMBAT);
    }

    void Settler_Type_i::Observe_Combat(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::OBSERVE_COMBAT, value);
    }

    Bool_t Settler_Type_i::React_To_Player_Actions()
    {
        return Save().flags.Is_Flagged(Flags_e::REACT_TO_PLAYER_ACTIONS);
    }

    void Settler_Type_i::React_To_Player_Actions(Bool_t value)
    {
        Save().flags.Is_Flagged(Flags_e::REACT_TO_PLAYER_ACTIONS, value);
    }

}}
