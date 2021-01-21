/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

namespace doticu_npcp {

    Process_Lists_t* Process_Lists_t::Self()
    {
        static auto self = reinterpret_cast
            <Process_Lists_t**>
            (RelocationManager::s_baseAddr + Offsets::Process_Lists::SELF);
        NPCP_ASSERT(self);
        return *self;
    }

    void Process_Lists_t::Stop_Combat_Alarm(Actor_t* actor, Bool_t dont_end_alarm)
    {
        static auto stop_combat_alarm = reinterpret_cast
            <void (*)(Process_Lists_t*, Actor_t*, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Process_Lists::STOP_COMBAT_ALARM);
        if (actor) {
            stop_combat_alarm(this, actor, dont_end_alarm);
        }
    }

    Int_t Relationship_t::To_Papyrus_Rank(Rank_e rank)
    {
        switch (rank) {
            case (Rank_e::LOVER):           return  4;
            case (Rank_e::ALLY):            return  3;
            case (Rank_e::CONFIDANT):       return  2;
            case (Rank_e::FRIEND):          return  1;
            case (Rank_e::ACQUAINTANCE):    return  0;
            case (Rank_e::RIVAL):           return -1;
            case (Rank_e::FOE):             return -2;
            case (Rank_e::ENEMY):           return -3;
            case (Rank_e::ARCHNEMESIS):     return -4;
            default:                        return  0;
        };
    }

    Relationship_t::Rank_e Relationship_t::From_Papyrus_Rank(Int_t rank)
    {
        switch (rank) {
            case ( 4):  return Rank_e::LOVER;
            case ( 3):  return Rank_e::ALLY;
            case ( 2):  return Rank_e::CONFIDANT;
            case ( 1):  return Rank_e::FRIEND;
            case ( 0):  return Rank_e::ACQUAINTANCE;
            case (-1):  return Rank_e::RIVAL;
            case (-2):  return Rank_e::FOE;
            case (-3):  return Rank_e::ENEMY;
            case (-4):  return Rank_e::ARCHNEMESIS;
            default:    return Rank_e::ACQUAINTANCE;
        };
    }

    Dialogue_Info_t::Dialogue_Info_t(Quest_t* quest, Topic_t* topic, Topic_Info_t* topic_info, Actor_t* speaker)
    {
        static auto ctor = reinterpret_cast
            <Dialogue_Info_t * (*)(Dialogue_Info_t*, Quest_t*, Topic_t*, Topic_Info_t*, Actor_t*)>
            (RelocationManager::s_baseAddr + Offsets::Dialogue_Info::CTOR);
        ctor(this, quest, topic, topic_info, speaker);
    }

}
