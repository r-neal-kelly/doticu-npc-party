/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party.h"

namespace doticu_npcp { namespace Party { namespace Members {

    constexpr size_t MAX = 1024;
    constexpr size_t HALF = MAX / 2;
    constexpr size_t BEGIN = 0;
    constexpr size_t END = BEGIN + MAX;

    /*class Members_t : public Quest_t {
    public:
        static const String_t Class_Name()
        {
            static const String_t class_name = String_t("doticu_npcp_members");
            return class_name;
        }
    };*/

    String_t Class_Name();
    Class_Info_t* Class_Info();
    Members_t* Self();
    Object_t* Object();

    Range_t<UInt64> Indices(Members_t* self);
    Range_t<Alias_t**> Aliases(Members_t* self);
    Range_t<Member_t**> Members(Members_t* self);

    Member_t* From_ID(Members_t* self, Int_t unique_id);
    Member_t* From_Actor(Members_t* self, Actor_t* actor);

    Bool_t Has_Actor(Members_t* self, Actor_t* actor);
    Bool_t Hasnt_Actor(Members_t* self, Actor_t* actor);
    Bool_t Has_Head(Members_t* self, Actor_t* actor);
    Bool_t Hasnt_Head(Members_t* self, Actor_t* actor);

    Int_t Max(Members_t* self);
    Int_t Count_Filled(Members_t* self);
    Int_t Count_Unfilled(Members_t* self);
    Int_t Count_Loaded(Members_t* self);
    Int_t Count_Unloaded(Members_t* self);
    Int_t Count_Heads(Members_t* self, Actor_t* actor);

    Vector_t<Member_t*> Filled(Members_t* self);
    Vector_t<Member_t*> Loaded(Members_t* self);
    Vector_t<Member_t*> Unloaded(Members_t* self);

    Vector_t<Member_t*> Sort(Vector_t<Member_t*> members);
    Vector_t<Member_t*> Sort_Filled(Members_t* self, Int_t begin = 0, Int_t end = -1);

    Vector_t<String_t> Race_Names(Members_t* self);

    void Enforce_Loaded(Members_t* self);

}}}

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}
