/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_list.h"
#include "doticu_skylib/reference.h"

#include "consts.h"
#include "npcp.inl"
#include "party_settler_sleeper.h"

namespace doticu_skylib { namespace doticu_npcp {

    some<Form_List_t*> Settler_Sleeper_t::Packages()
    {
        return Consts_t::NPCP::Form_List::Settler_Sleeper_Packages();
    }

    some<Misc_t*> Settler_Sleeper_t::Token()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sleeper();
    }

    Settler_Sleeper_t::Save_t::Save_t() :
        attention(),
        wander_distance(),
        bed()
    {
    }

    Settler_Sleeper_t::Save_t::~Save_t()
    {
    }

    void Settler_Sleeper_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->attention);
        NPCP.Write(file, this->wander_distance);
        NPCP.Write_Form(file, this->bed);
    }

    void Settler_Sleeper_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->attention);
        NPCP.Read(file, this->wander_distance);
        NPCP.Read_Form(file, this->bed);
    }

    Settler_Sleeper_t::State_t::State_t() :
        save()
    {
    }

    Settler_Sleeper_t::State_t::~State_t()
    {
    }

    Settler_Sleeper_t::Settler_Sleeper_t() :
        state()
    {
    }

    Settler_Sleeper_t::~Settler_Sleeper_t()
    {
    }

    void Settler_Sleeper_t::On_After_New_Game()
    {
        Settler_Type_i::On_After_New_Game();
    }

    void Settler_Sleeper_t::On_Before_Save_Game(std::ofstream& file)
    {
        Settler_Type_i::On_Before_Save_Game(file);

        Save().Write(file);
    }

    void Settler_Sleeper_t::On_After_Save_Game()
    {
        Settler_Type_i::On_After_Save_Game();
    }

    void Settler_Sleeper_t::On_Before_Load_Game()
    {
        Settler_Type_i::On_Before_Load_Game();
    }

    void Settler_Sleeper_t::On_After_Load_Game(std::ifstream& file)
    {
        Settler_Type_i::On_After_Load_Game(file);

        Save().Read(file);
    }

    void Settler_Sleeper_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Settler_Type_i::On_After_Load_Game(file, version_to_update);

        Save().Read(file);
    }

    Settler_Sleeper_t::State_t& Settler_Sleeper_t::State()
    {
        return this->state;
    }

    const Settler_Sleeper_t::State_t& Settler_Sleeper_t::State() const
    {
        return this->state;
    }

    Settler_Sleeper_t::Save_t& Settler_Sleeper_t::Save()
    {
        return State().save;
    }

    const Settler_Sleeper_t::Save_t& Settler_Sleeper_t::Save() const
    {
        return State().save;
    }

    Bool_t Settler_Sleeper_t::Allow_Conversation()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_CONVERSATION);
    }

    void Settler_Sleeper_t::Allow_Conversation(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_CONVERSATION, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Eating()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_EATING);
    }

    void Settler_Sleeper_t::Allow_Eating(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_EATING, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Horse_Riding()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_HORSE_RIDING);
    }

    void Settler_Sleeper_t::Allow_Horse_Riding(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_HORSE_RIDING, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Idle_Markers()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_IDLE_MARKERS);
    }

    void Settler_Sleeper_t::Allow_Idle_Markers(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_IDLE_MARKERS, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Sitting()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_SITTING);
    }

    void Settler_Sleeper_t::Allow_Sitting(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_SITTING, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Sleeping()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_SLEEPING);
    }

    void Settler_Sleeper_t::Allow_Sleeping(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_SLEEPING, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Special_Furniture()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_SPECIAL_FURNITURE);
    }

    void Settler_Sleeper_t::Allow_Special_Furniture(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_SPECIAL_FURNITURE, value);
    }

    Bool_t Settler_Sleeper_t::Allow_Wandering()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_WANDERING);
    }

    void Settler_Sleeper_t::Allow_Wandering(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ALLOW_WANDERING, value);
    }

    Bool_t Settler_Sleeper_t::Lock_Doors()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::LOCK_DOORS);
    }

    void Settler_Sleeper_t::Lock_Doors(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::LOCK_DOORS, value);
    }

    Bool_t Settler_Sleeper_t::Only_Preferred_Path()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ONLY_PREFERRED_PATH);
    }

    void Settler_Sleeper_t::Only_Preferred_Path(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::ONLY_PREFERRED_PATH, value);
    }

    Bool_t Settler_Sleeper_t::Warn_Before_Locking()
    {
        return Settler_Type_i::Save().flags.Is_Flagged(Flags_e::WARN_BEFORE_LOCKING);
    }

    void Settler_Sleeper_t::Warn_Before_Locking(Bool_t value)
    {
        Settler_Type_i::Save().flags.Is_Flagged(Flags_e::WARN_BEFORE_LOCKING, value);
    }

    some<Package_t*> Settler_Sleeper_t::Package(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        maybe<Package_t*> package = Packages()->Static_At(settler_id())->As_Package();
        SKYLIB_ASSERT_SOME(package);

        return package();
    }

}}
