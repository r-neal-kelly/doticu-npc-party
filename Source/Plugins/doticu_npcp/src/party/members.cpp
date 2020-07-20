/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "game.h"
#include "party.h"
#include "party.inl"
#include "utils.h"
#include "vars.h"
#include "vector.h"

// ForceRefTo is found and callable on TESQuest
// Clear might be unlabeled on the virtual table of BGSBaseAlias
// maybe we could try a couple of addresses after ForceRefTo?

namespace doticu_npcp { namespace Party {

    String_t Members_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_members");
        return class_name;
    }

    Class_Info_t* Members_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Members_t* Members_t::Self()
    {
        static Members_t* members = static_cast<Members_t*>(Game::NPCP_Form(Consts::QUEST_MEMBERS));
        return members;
    }

    Object_t* Members_t::Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), Class_Name());
        return object;
    }

    Variable_t* Members_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Range_t<UInt64> Members_t::Indices()
    {
        return { BEGIN, END };
    }

    Range_t<Member_t**> Members_t::Aliases()
    {
        return Aliases_t::Aliases<Member_t>(BEGIN, END);
    }

    Member_t* Members_t::From_ID(Int_t unique_id)
    {
        if (unique_id >= BEGIN && unique_id < END) {
            return Aliases_t::From_ID<Member_t>(unique_id);
        } else {
            return nullptr;
        }
    }

    Member_t* Members_t::From_Actor(Actor_t* actor)
    {
        if (actor) {
            Member_t* member = Aliases_t::From_Actor<Member_t>(actor);
            if (member) {
                if (member->id >= BEGIN && member->id < END) {
                    return member;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Member_t* Members_t::From_Unfilled()
    {
        return Aliases_t::From_Unfilled(Aliases());
    }

    Bool_t Members_t::Has_Space()
    {
        return From_Unfilled() != nullptr;
    }

    Bool_t Members_t::Hasnt_Space()
    {
        return From_Unfilled() == nullptr;
    }

    Bool_t Members_t::Has_Actor(Actor_t* actor)
    {
        return actor && From_Actor(actor) != nullptr;
    }

    Bool_t Members_t::Hasnt_Actor(Actor_t* actor)
    {
        return actor && From_Actor(actor) == nullptr;
    }

    Bool_t Members_t::Has_Head(Actor_t* actor)
    {
        return actor && Aliases_t::Has_Head<Member_t>(Aliases(), actor);
    }

    Bool_t Members_t::Hasnt_Head(Actor_t* actor)
    {
        return actor && !Aliases_t::Has_Head<Member_t>(Aliases(), actor);
    }

    Int_t Members_t::Max()
    {
        return MAX;
    }

    Int_t Members_t::Count_Filled()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled);
    }

    Int_t Members_t::Count_Unfilled()
    {
        return Count_If(Aliases(), &Member_t::Is_Unfilled);
    }

    Int_t Members_t::Count_Loaded()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Loaded);
    }

    Int_t Members_t::Count_Unloaded()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Unloaded);
    }

    Int_t Members_t::Count_Unique()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Unique);
    }

    Int_t Members_t::Count_Generic()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Generic);
    }

    Int_t Members_t::Count_Alive()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Alive);
    }

    Int_t Members_t::Count_Dead()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Dead);
    }

    Int_t Members_t::Count_Originals()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Original);
    }

    Int_t Members_t::Count_Clones()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Clone);
    }

    Int_t Members_t::Count_Mobile()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Mobile);
    }

    Int_t Members_t::Count_Immobile()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Immobile);
    }

    Int_t Members_t::Count_Settlers()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Settler);
    }

    Int_t Members_t::Count_Non_Settlers()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Settler);
    }

    Int_t Members_t::Count_Thralls()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Thrall);
    }

    Int_t Members_t::Count_Non_Thralls()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Thrall);
    }

    Int_t Members_t::Count_Paralyzed()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Paralyzed);
    }

    Int_t Members_t::Count_Non_Paralyzed()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Paralyzed);
    }

    Int_t Members_t::Count_Mannequins()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Mannequin);
    }

    Int_t Members_t::Count_Non_Mannequins()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Mannequin);
    }

    Int_t Members_t::Count_Reanimated()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Reanimated);
    }

    Int_t Members_t::Count_Non_Reanimated()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Reanimated);
    }

    Int_t Members_t::Count_Followers()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Follower);
    }

    Int_t Members_t::Count_Non_Followers()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Follower);
    }

    Int_t Members_t::Count_Sneaks()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Sneak);
    }

    Int_t Members_t::Count_Non_Sneaks()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Sneak);
    }

    Int_t Members_t::Count_Saddlers()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Saddler);
    }

    Int_t Members_t::Count_Non_Saddlers()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Saddler);
    }

    Int_t Members_t::Count_Retreaters()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Retreater);
    }

    Int_t Members_t::Count_Non_Retreaters()
    {
        return Count_If(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Retreater);
    }

    Int_t Members_t::Count_Heads(Actor_t* actor)
    {
        return Aliases_t::Count_Heads(Aliases(), actor);
    }

    Vector_t<Member_t*> Members_t::All()
    {
        Vector_t<Member_t*> all;
        all.reserve(MAX);

        Range_t<Member_t**> aliases = Aliases();
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            all.push_back(*aliases.begin);
        }

        return all;
    }

    Vector_t<Member_t*> Members_t::Filled()
    {
        return Copy_If(Aliases(), &Member_t::Is_Filled, MAX);
    }

    Vector_t<Member_t*> Members_t::Unfilled()
    {
        return Copy_If(Aliases(), &Member_t::Is_Unfilled, HALF);
    }

    Vector_t<Member_t*> Members_t::Loaded()
    {
        return Copy_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Loaded, HALF);
    }

    Vector_t<Member_t*> Members_t::Unloaded()
    {
        return Copy_If(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Unloaded, HALF);
    }

    Vector_t<Member_t*> Members_t::Sort(Vector_t<Member_t*> members)
    {
        static const String_t sort_algorithm_name = String_t("p_str_sort_members");
        return Aliases_t::Sort<Member_t>(members, Vars::String_Variable(sort_algorithm_name));
    }

    Vector_t<Member_t*> Members_t::Sort_Filled(Int_t begin, Int_t end)
    {
        return Slice(Sort(Filled()), begin, end);
    }

    Vector_t<String_t> Members_t::Race_Names()
    {
        Vector_t<String_t> race_names;
        race_names.reserve(16);

        Range_t<Member_t**> members = Aliases();
        for (; members.begin < members.end; members.begin += 1) {
            Member_t* member = (*members.begin);
            if (member->Is_Filled()) {
                String_t race_name = member->Race();
                if (!String2::Is_Same_Caseless(race_name, "") && !Vector::Has(race_names, race_name)) {
                    race_names.push_back(race_name);
                }
            }
        }

        auto sort = [](const void* item_a, const void* item_b) -> int
        {
            String_t race_a = item_a ? *(String_t*)item_a : "";
            String_t race_b = item_b ? *(String_t*)item_b : "";
            return _stricmp(race_a, race_b);
        };
        qsort(race_names.data(), race_names.size(), sizeof(String_t), sort);

        return race_names;
    }

    void Members_t::Enforce_Loaded()
    {
        static const String_t event_name("Enforce");

        struct Args : public IFunctionArguments {
            bool Copy(Output* output) { return true; }
        } args;

        Vector_t<Member_t*> vec_members = Loaded();
        for (u64 idx = 0, size = vec_members.size(); idx < size; idx += 1) {
            Member_t* member = vec_members[idx];
            Handle_t handle(member);
            handle.Registry()->QueueEvent(handle, &event_name, &args);
        }
    }

    Vector_t<Member_t*> Members_t::Filter(Vector_t<String_t>* strings, Vector_t<Int_t>* ints, Int_t flags_1, Int_t flags_2)
    {
        return Sort(Aliases_t::Filter(Aliases(), strings, ints, flags_1, flags_2));
    }

}}

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    Member_t* From_ID(Members_t* self, Int_t unique_id) FORWARD_POINTER(From_ID(unique_id));
    Member_t* From_Actor(Members_t* self, Actor_t* actor) FORWARD_POINTER(From_Actor(actor));
    Member_t* From_Unfilled(Members_t* self) FORWARD_POINTER(From_Unfilled());

    Bool_t Has_Space(Members_t* self) FORWARD_BOOL(Has_Space());
    Bool_t Hasnt_Space(Members_t* self) FORWARD_BOOL(Hasnt_Space());
    Bool_t Has_Actor(Members_t* self, Actor_t* actor) FORWARD_BOOL(Has_Actor(actor));
    Bool_t Hasnt_Actor(Members_t* self, Actor_t* actor) FORWARD_BOOL(Hasnt_Actor(actor));
    Bool_t Has_Head(Members_t* self, Actor_t* actor) FORWARD_BOOL(Has_Head(actor));
    Bool_t Hasnt_Head(Members_t* self, Actor_t* actor) FORWARD_BOOL(Hasnt_Head(actor));

    Int_t Max(Members_t* self) FORWARD_INT(Max());
    Int_t Count_Filled(Members_t* self) FORWARD_INT(Count_Filled());
    Int_t Count_Unfilled(Members_t* self) FORWARD_INT(Count_Unfilled());
    Int_t Count_Loaded(Members_t* self) FORWARD_INT(Count_Loaded());
    Int_t Count_Unloaded(Members_t* self) FORWARD_INT(Count_Unloaded());
    Int_t Count_Unique(Members_t* self) FORWARD_INT(Count_Unique());
    Int_t Count_Generic(Members_t* self) FORWARD_INT(Count_Generic());
    Int_t Count_Alive(Members_t* self) FORWARD_INT(Count_Alive());
    Int_t Count_Dead(Members_t* self) FORWARD_INT(Count_Dead());
    Int_t Count_Originals(Members_t* self) FORWARD_INT(Count_Originals());
    Int_t Count_Clones(Members_t* self) FORWARD_INT(Count_Clones());
    Int_t Count_Mobile(Members_t* self) FORWARD_INT(Count_Mobile());
    Int_t Count_Immobile(Members_t* self) FORWARD_INT(Count_Immobile());
    Int_t Count_Settlers(Members_t* self) FORWARD_INT(Count_Settlers());
    Int_t Count_Non_Settlers(Members_t* self) FORWARD_INT(Count_Non_Settlers());
    Int_t Count_Thralls(Members_t* self) FORWARD_INT(Count_Thralls());
    Int_t Count_Non_Thralls(Members_t* self) FORWARD_INT(Count_Non_Thralls());
    Int_t Count_Paralyzed(Members_t* self) FORWARD_INT(Count_Paralyzed());
    Int_t Count_Non_Paralyzed(Members_t* self) FORWARD_INT(Count_Non_Paralyzed());
    Int_t Count_Mannequins(Members_t* self) FORWARD_INT(Count_Mannequins());
    Int_t Count_Non_Mannequins(Members_t* self) FORWARD_INT(Count_Non_Mannequins());
    Int_t Count_Reanimated(Members_t* self) FORWARD_INT(Count_Reanimated());
    Int_t Count_Non_Reanimated(Members_t* self) FORWARD_INT(Count_Non_Reanimated());
    Int_t Count_Followers(Members_t* self) FORWARD_INT(Count_Followers());
    Int_t Count_Non_Followers(Members_t* self) FORWARD_INT(Count_Non_Followers());
    Int_t Count_Sneaks(Members_t* self) FORWARD_INT(Count_Sneaks());
    Int_t Count_Non_Sneaks(Members_t* self) FORWARD_INT(Count_Non_Sneaks());
    Int_t Count_Saddlers(Members_t* self) FORWARD_INT(Count_Saddlers());
    Int_t Count_Non_Saddlers(Members_t* self) FORWARD_INT(Count_Non_Saddlers());
    Int_t Count_Retreaters(Members_t* self) FORWARD_INT(Count_Retreaters());
    Int_t Count_Non_Retreaters(Members_t* self) FORWARD_INT(Count_Non_Retreaters());
    Int_t Count_Heads(Members_t* self, Actor_t* actor) FORWARD_INT(Count_Heads(actor));

    Vector_t<Member_t*> All(Members_t* self) FORWARD_VECTOR(All(), Member_t*);
    Vector_t<Member_t*> Filled(Members_t* self) FORWARD_VECTOR(Filled(), Member_t*);

    Vector_t<Member_t*> Sort_Filled(Members_t* self, Int_t begin, Int_t end) FORWARD_VECTOR(Sort_Filled(begin, end), Member_t*);

    Vector_t<Member_t*> Slice(Members_t* self, VMArray<Member_t*>members_array, Int_t begin, Int_t end)
    {
        Vector_t<Member_t*> members_vector = Slice_Array(members_array);
        return self->Slice(members_vector, begin, end);
    }

    Vector_t<String_t> Race_Names(Members_t* self) FORWARD_VECTOR(Race_Names(), String_t);

    void Enforce_Loaded(Members_t* self) FORWARD_VOID(Enforce_Loaded());

    Vector_t<String_t> Filter_Strings(Members_t* self, String_t sex, String_t race, String_t search)
        FORWARD_VECTOR(Members_t::Filter_Strings(sex, race, search), String_t);
    Vector_t<Int_t> Filter_Ints(Members_t* self, Int_t style, Int_t vitality, Int_t outfit2, Int_t rating)
        FORWARD_VECTOR(Members_t::Filter_Ints(style, vitality, outfit2, rating), Int_t);
    Int_t Add_Filter_Flag_1(Members_t* self, Int_t flags_1, String_t flag_1)
        FORWARD_INT(Members_t::Add_Filter_Flag_1(flags_1, flag_1));
    Int_t Add_Filter_Flag_2(Members_t* self, Int_t flags_2, String_t flag_2)
        FORWARD_INT(Members_t::Add_Filter_Flag_2(flags_2, flag_2));
    Vector_t<Member_t*> Filter(Members_t* self, VMArray<String_t> strings, VMArray<Int_t> ints, Int_t flags_1, Int_t flags_2)
    {
        Vector_t<String_t> strings_vector = Slice_Array(strings);
        Vector_t<Int_t> ints_vector = Slice_Array(ints);
        return self->Filter(strings_vector.size() > 0 ? &strings_vector : nullptr,
                            ints_vector.size() > 0 ? &ints_vector : nullptr,
                            flags_1, flags_2);
    }

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Members_t::Class_Name(), Members_t,        \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("p_From_ID", 1, Member_t*, From_ID, Int_t);
        ADD_METHOD("p_From_Actor", 1, Member_t*, From_Actor, Actor_t*);
        ADD_METHOD("p_From_Unfilled", 0, Member_t*, From_Unfilled);

        ADD_METHOD("Has_Space", 0, Bool_t, Has_Space);
        ADD_METHOD("Hasnt_Space", 0, Bool_t, Hasnt_Space);
        ADD_METHOD("Has_Actor", 1, Bool_t, Has_Actor, Actor_t*);
        ADD_METHOD("Hasnt_Actor", 1, Bool_t, Hasnt_Actor, Actor_t*);
        ADD_METHOD("Has_Head", 1, Bool_t, Has_Head, Actor_t*);
        ADD_METHOD("Hasnt_Head", 1, Bool_t, Hasnt_Head, Actor_t*);

        ADD_METHOD("Max", 0, Int_t, Max);
        ADD_METHOD("Count_Filled", 0, Int_t, Count_Filled);
        ADD_METHOD("Count_Unfilled", 0, Int_t, Count_Unfilled);
        ADD_METHOD("Count_Loaded", 0, Int_t, Count_Loaded);
        ADD_METHOD("Count_Unloaded", 0, Int_t, Count_Unloaded);
        ADD_METHOD("Count_Unique", 0, Int_t, Count_Unique);
        ADD_METHOD("Count_Generic", 0, Int_t, Count_Generic);
        ADD_METHOD("Count_Alive", 0, Int_t, Count_Alive);
        ADD_METHOD("Count_Dead", 0, Int_t, Count_Dead);
        ADD_METHOD("Count_Originals", 0, Int_t, Count_Originals);
        ADD_METHOD("Count_Clones", 0, Int_t, Count_Clones);
        ADD_METHOD("Count_Mobile", 0, Int_t, Count_Mobile);
        ADD_METHOD("Count_Immobile", 0, Int_t, Count_Immobile);
        ADD_METHOD("Count_Settlers", 0, Int_t, Count_Settlers);
        ADD_METHOD("Count_Non_Settlers", 0, Int_t, Count_Non_Settlers);
        ADD_METHOD("Count_Thralls", 0, Int_t, Count_Thralls);
        ADD_METHOD("Count_Non_Thralls", 0, Int_t, Count_Non_Thralls);
        ADD_METHOD("Count_Paralyzed", 0, Int_t, Count_Paralyzed);
        ADD_METHOD("Count_Non_Paralyzed", 0, Int_t, Count_Non_Paralyzed);
        ADD_METHOD("Count_Mannequins", 0, Int_t, Count_Mannequins);
        ADD_METHOD("Count_Non_Mannequins", 0, Int_t, Count_Non_Mannequins);
        ADD_METHOD("Count_Reanimated", 0, Int_t, Count_Reanimated);
        ADD_METHOD("Count_Non_Reanimated", 0, Int_t, Count_Non_Reanimated);
        ADD_METHOD("Count_Followers", 0, Int_t, Count_Followers);
        ADD_METHOD("Count_Non_Followers", 0, Int_t, Count_Non_Followers);
        ADD_METHOD("Count_Sneaks", 0, Int_t, Count_Sneaks);
        ADD_METHOD("Count_Non_Sneaks", 0, Int_t, Count_Non_Sneaks);
        ADD_METHOD("Count_Saddlers", 0, Int_t, Count_Saddlers);
        ADD_METHOD("Count_Non_Saddlers", 0, Int_t, Count_Non_Saddlers);
        ADD_METHOD("Count_Retreaters", 0, Int_t, Count_Retreaters);
        ADD_METHOD("Count_Non_Retreaters", 0, Int_t, Count_Non_Retreaters);
        ADD_METHOD("Count_Heads", 1, Int_t, Count_Heads, Actor_t*);

        ADD_METHOD("All", 0, Vector_t<Member_t*>, All);
        ADD_METHOD("Filled", 0, Vector_t<Member_t*>, Filled);

        ADD_METHOD("Sort_Filled", 2, Vector_t<Member_t*>, Sort_Filled, Int_t, Int_t);

        ADD_METHOD("Slice", 3, Vector_t<Member_t*>, Slice, VMArray<Member_t*>, Int_t, Int_t);

        ADD_METHOD("Race_Names", 0, Vector_t<String_t>, Race_Names);

        ADD_METHOD("Enforce_Loaded", 0, void, Enforce_Loaded);

        ADD_METHOD("Filter_Strings", 3, Vector_t<String_t>, Filter_Strings, String_t, String_t, String_t);
        ADD_METHOD("Filter_Ints", 4, Vector_t<Int_t>, Filter_Ints, Int_t, Int_t, Int_t, Int_t);
        ADD_METHOD("Add_Filter_Flag_1", 2, Int_t, Add_Filter_Flag_1, Int_t, String_t);
        ADD_METHOD("Add_Filter_Flag_2", 2, Int_t, Add_Filter_Flag_2, Int_t, String_t);
        ADD_METHOD("Filter", 4, Vector_t<Member_t*>, Filter, VMArray<String_t>, VMArray<Int_t>, Int_t, Int_t);

        #undef ADD_METHOD

        return true;
    }

}}}}
