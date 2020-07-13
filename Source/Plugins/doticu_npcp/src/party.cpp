/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameData.h"

#include "papyrus.h"
#include "party.h"
#include "actor2.h"
#include "actor_base2.h"
#include "utils.h"
#include "game.h"
#include "consts.h"
#include "vars.h"
#include "vector.h"
#include "object_ref.h"
#include "player.h"
#include "cell.h"
#include "string2.h"

// ForceRefTo is found and callable on TESQuest
// Clear might be unlabeled on the virtual table of BGSBaseAlias

namespace doticu_npcp { namespace Party {

    // Aliases_t //

    Vector_t<String_t> Aliases_t::Filter_Strings(String_t sex, String_t race, String_t search)
    {
        Vector_t<String_t> strings;
        strings.reserve(3);
        strings.push_back(sex);
        strings.push_back(race);
        strings.push_back(search);
        return strings;
    }

    Vector_t<Int_t> Aliases_t::Filter_Ints(Int_t style, Int_t vitality, Int_t outfit2, Int_t rating)
    {
        Vector_t<Int_t> ints;
        ints.reserve(4);
        ints.push_back(style);
        ints.push_back(vitality);
        ints.push_back(outfit2);
        ints.push_back(rating);
        return ints;
    }

    Int_t Aliases_t::Add_Filter_Flag_1(Int_t flags_1, String_t flag_1)
    {
        static const String_t IS_LOADED = String_t("IS_LOADED");
        static const String_t IS_UNLOADED = String_t("IS_UNLOADED");
        static const String_t IS_UNIQUE = String_t("IS_UNIQUE");
        static const String_t IS_GENERIC = String_t("IS_GENERIC");
        static const String_t IS_ORIGINAL = String_t("IS_ORIGINAL");
        static const String_t IS_CLONE = String_t("IS_CLONE");
        static const String_t IS_ALIVE = String_t("IS_ALIVE");
        static const String_t IS_DEAD = String_t("IS_DEAD");
        static const String_t IS_MOBILE = String_t("IS_MOBILE");
        static const String_t IS_IMMOBILE = String_t("IS_IMMOBILE");
        static const String_t IS_SETTLER = String_t("IS_SETTLER");
        static const String_t ISNT_SETTLER = String_t("ISNT_SETTLER");
        static const String_t IS_THRALL = String_t("IS_THRALL");
        static const String_t ISNT_THRALL = String_t("ISNT_THRALL");
        static const String_t IS_PARALYZED = String_t("IS_PARALYZED");
        static const String_t ISNT_PARALYZED = String_t("ISNT_PARALYZED");
        static const String_t IS_MANNEQUIN = String_t("IS_MANNEQUIN");
        static const String_t ISNT_MANNEQUIN = String_t("ISNT_MANNEQUIN");
        static const String_t IS_REANIMATED = String_t("IS_REANIMATED");
        static const String_t ISNT_REANIMATED = String_t("ISNT_REANIMATED");
        static const String_t IS_FOLLOWER = String_t("IS_FOLLOWER");
        static const String_t ISNT_FOLLOWER = String_t("ISNT_FOLLOWER");
        static const String_t IS_SNEAK = String_t("IS_SNEAK");
        static const String_t ISNT_SNEAK = String_t("ISNT_SNEAK");
        static const String_t IS_SADDLER = String_t("IS_SADDLER");
        static const String_t ISNT_SADDLER = String_t("ISNT_SADDLER");
        static const String_t IS_RETREATER = String_t("IS_RETREATER");
        static const String_t ISNT_RETREATER = String_t("ISNT_RETREATER");

        if (String2::Is_Same_Caseless(flag_1, IS_UNIQUE)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_UNIQUE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_GENERIC)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_GENERIC);
        } else if (String2::Is_Same_Caseless(flag_1, IS_LOADED)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_LOADED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_UNLOADED)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_UNLOADED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_ALIVE)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_ALIVE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_DEAD)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_DEAD);
        } else if (String2::Is_Same_Caseless(flag_1, IS_ORIGINAL)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_ORIGINAL);
        } else if (String2::Is_Same_Caseless(flag_1, IS_CLONE)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_CLONE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_MOBILE)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_MOBILE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_IMMOBILE)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_IMMOBILE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_SETTLER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_SETTLER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_SETTLER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_SETTLER);
        } else if (String2::Is_Same_Caseless(flag_1, IS_THRALL)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_THRALL);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_THRALL)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_THRALL);
        } else if (String2::Is_Same_Caseless(flag_1, IS_PARALYZED)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_PARALYZED);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_PARALYZED)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_PARALYZED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_MANNEQUIN)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_MANNEQUIN);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_MANNEQUIN)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_MANNEQUIN);
        } else if (String2::Is_Same_Caseless(flag_1, IS_REANIMATED)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_REANIMATED);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_REANIMATED)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_REANIMATED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_FOLLOWER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_FOLLOWER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_FOLLOWER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_FOLLOWER);
        } else if (String2::Is_Same_Caseless(flag_1, IS_SNEAK)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_SNEAK);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_SNEAK)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_SNEAK);
        } else if (String2::Is_Same_Caseless(flag_1, IS_SADDLER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_SADDLER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_SADDLER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_SADDLER);
        } else if (String2::Is_Same_Caseless(flag_1, IS_RETREATER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::IS_RETREATER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_RETREATER)) {
            return Utils::Bit_On(flags_1, Filter_Flags_1::ISNT_RETREATER);
        } else {
            return flags_1;
        }
    }

    Int_t Aliases_t::Add_Filter_Flag_2(Int_t flags_2, String_t flag_2)
    {
        return flags_2;
    }

    // Members_t //

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
        static Members_t* members = static_cast<Members_t*>(Game::Get_NPCP_Form(Consts::QUEST_MEMBERS));
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

    // Followers_t //

    String_t Followers_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_followers");
        return class_name;
    }

    Class_Info_t* Followers_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Followers_t* Followers_t::Self()
    {
        static Followers_t* followers = static_cast<Followers_t*>(Game::Get_NPCP_Form(Consts::QUEST_FOLLOWERS));
        return followers;
    }

    Object_t* Followers_t::Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), Class_Name());
        return object;
    }

    Variable_t* Followers_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Range_t<UInt64> Followers_t::Indices()
    {
        return { BEGIN, END };
    }

    Range_t<Follower_t**> Followers_t::Aliases()
    {
        return Aliases_t::Aliases<Follower_t>(BEGIN, END);
    }

    Follower_t* Followers_t::From_ID(Int_t unique_id)
    {
        if (unique_id >= BEGIN && unique_id < END) {
            return Aliases_t::From_ID<Follower_t>(unique_id);
        } else {
            return nullptr;
        }
    }

    Follower_t* Followers_t::From_Actor(Actor_t* actor)
    {
        if (actor) {
            Follower_t* follower = Aliases_t::From_Actor<Follower_t>(actor);
            if (follower) {
                if (follower->id >= BEGIN && follower->id < END) {
                    return follower;
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

    Follower_t* Followers_t::From_Unfilled()
    {
        return Aliases_t::From_Unfilled(Aliases());
    }

    Follower_t* Followers_t::From_Horse_Actor(Actor_t* actor)
    {
        Horses_t* horses = Horses_t::Self();
        if (horses) {
            Horse_t* horse = horses->From_Actor(actor);
            if (horse) {
                return horse->Follower();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Form_t* Followers_t::Tasklist()
    {
        static const String_t tasklist_name = String_t("p_tasklist");

        Variable_t* variable = Variable(tasklist_name);
        if (variable) {
            return static_cast<Form_t*>(variable->Reference());
        } else {
            return nullptr;
        }
    }

    Bool_t Followers_t::Has_Space()
    {
        return From_Unfilled() != nullptr;
    }

    Bool_t Followers_t::Hasnt_Space()
    {
        return From_Unfilled() == nullptr;
    }

    Bool_t Followers_t::Has_Actor(Actor_t* actor)
    {
        return actor && From_Actor(actor) != nullptr;
    }

    Bool_t Followers_t::Hasnt_Actor(Actor_t* actor)
    {
        return actor && From_Actor(actor) == nullptr;
    }

    Bool_t Followers_t::Are_In_Combat()
    {
        Range_t<Follower_t**> followers = Aliases();
        for (; followers.begin < followers.end; followers.begin += 1) {
            Follower_t* follower = *followers.begin;
            if (follower) {
                Actor_t* actor = follower->Actor();
                if (actor && actor->IsInCombat()) {
                    return true;
                }
            }
        }
        return false;
    }

    Int_t Followers_t::Max()
    {
        return MAX;
    }

    Int_t Followers_t::Count_Filled()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled);
    }

    Int_t Followers_t::Count_Unfilled()
    {
        return Count_If(Aliases(), &Follower_t::Is_Unfilled);
    }

    Int_t Followers_t::Count_Loaded()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Loaded);
    }

    Int_t Followers_t::Count_Unloaded()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unloaded);
    }

    Int_t Followers_t::Count_Unique()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unique);
    }

    Int_t Followers_t::Count_Generic()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Generic);
    }

    Int_t Followers_t::Count_Alive()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Alive);
    }

    Int_t Followers_t::Count_Dead()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Dead);
    }

    Int_t Followers_t::Count_Originals()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Original);
    }

    Int_t Followers_t::Count_Clones()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Clone);
    }

    Int_t Followers_t::Count_Mobile()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mobile);
    }

    Int_t Followers_t::Count_Immobile()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Immobile);
    }

    Int_t Followers_t::Count_Settlers()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Settler);
    }

    Int_t Followers_t::Count_Non_Settlers()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Settler);
    }

    Int_t Followers_t::Count_Thralls()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Thrall);
    }

    Int_t Followers_t::Count_Non_Thralls()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Thrall);
    }

    Int_t Followers_t::Count_Paralyzed()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Paralyzed);
    }

    Int_t Followers_t::Count_Non_Paralyzed()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Paralyzed);
    }

    Int_t Followers_t::Count_Mannequins()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mannequin);
    }

    Int_t Followers_t::Count_Non_Mannequins()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Mannequin);
    }

    Int_t Followers_t::Count_Reanimated()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Reanimated);
    }

    Int_t Followers_t::Count_Non_Reanimated()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Reanimated);
    }

    Int_t Followers_t::Count_Followers()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Follower);
    }

    Int_t Followers_t::Count_Non_Followers()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Follower);
    }

    Int_t Followers_t::Count_Sneaks()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Sneak);
    }

    Int_t Followers_t::Count_Non_Sneaks()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Sneak);
    }

    Int_t Followers_t::Count_Saddlers()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Saddler);
    }

    Int_t Followers_t::Count_Non_Saddlers()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Saddler);
    }

    Int_t Followers_t::Count_Retreaters()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Retreater);
    }

    Int_t Followers_t::Count_Non_Retreaters()
    {
        return Count_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Retreater);
    }

    Vector_t<Follower_t*> Followers_t::All()
    {
        Vector_t<Follower_t*> all;
        all.reserve(MAX);

        Range_t<Follower_t**> aliases = Aliases();
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            all.push_back(*aliases.begin);
        }

        return all;
    }

    Vector_t<Follower_t*> Followers_t::Filled()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Unfilled()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Unfilled, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Loaded()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Loaded, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Unloaded()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unloaded, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Unique()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unique, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Generic()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Generic, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Alive()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Alive, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Dead()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Dead, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Originals()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Original, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Clones()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Clone, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Mobile()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mobile, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Immobile()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Immobile, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Settlers()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Settler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Settlers()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Settler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Thralls()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Thrall, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Thralls()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Thrall, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Paralyzed()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Paralyzed, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Paralyzed()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Paralyzed, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Mannequins()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mannequin, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Mannequins()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Mannequin, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Reanimated()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Reanimated, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Reanimated()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Reanimated, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Followers()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Follower, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Followers()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Follower, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Sneaks()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Sneak, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Sneaks()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Sneak, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Saddlers()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Saddler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Saddlers()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Saddler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Retreaters()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Retreater, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Retreaters()
    {
        return Copy_If(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Retreater, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Sort(Vector_t<Follower_t*> followers)
    {
        static const String_t sort_algorithm_name = String_t("p_str_sort_followers");
        return Aliases_t::Sort<Follower_t>(followers, Vars::String_Variable(sort_algorithm_name));
    }

    Vector_t<Follower_t*> Followers_t::Sort_Filled(Int_t begin, Int_t end)
    {
        return Slice(Sort(Filled()), begin, end);
    }

    void Followers_t::Send(Vector_t<Follower_t*> followers, String_t event_name)
    {
        if (followers.size() > 0 && !String2::Is_Same_Caseless(event_name, "")) {
            struct Args : public IFunctionArguments {
                bool Copy(Output* output)
                {
                    return true;
                }
            } args;

            for (size_t idx = 0, size = followers.size(); idx < size; idx += 1) {
                Follower_t* follower = followers[idx];
                Handle_t handle(follower);
                handle.Registry()->QueueEvent(handle, &event_name, &args);
            }
        }
    }

    void Followers_t::Send(Vector_t<Follower_t*> followers, String_t event_name, Form_t* form_arg)
    {
        if (followers.size() > 0 && !String2::Is_Same_Caseless(event_name, "")) {
            struct Args : public IFunctionArguments {
                Form_t* form_arg;
                Args(Form_t* form_arg) :
                    form_arg(form_arg)
                {
                }
                bool Copy(Output* output)
                {
                    output->Resize(1);
                    if (form_arg) {
                        PackValue(output->Get(0), &form_arg, (*g_skyrimVM)->GetClassRegistry());
                    } else {
                        output->Get(0)->SetNone();
                    }
                    return true;
                }
            } args(form_arg);

            for (size_t idx = 0, size = followers.size(); idx < size; idx += 1) {
                Follower_t* follower = followers[idx];
                Handle_t handle(follower);
                handle.Registry()->QueueEvent(handle, &event_name, &args);
            }
        }
    }

    void Followers_t::Register()
    {
        static const String_t event_name = String_t("f_Register");
        Send(Followers(), event_name);
    }

    void Followers_t::Enforce()
    {
        static const String_t event_name = String_t("On_Followers_Enforce");
        Send(Followers(), event_name, nullptr);
    }

    void Followers_t::Resurrect()
    {
        static const String_t event_name = String_t("On_Followers_Resurrect");
        Send(Dead(), event_name, Tasklist());
    }

    void Followers_t::Mobilize()
    {
        static const String_t event_name = String_t("On_Followers_Mobilize");
        Send(Immobile(), event_name, Tasklist());
    }

    void Followers_t::Immobilize()
    {
        static const String_t event_name = String_t("On_Followers_Immobilize");
        Send(Mobile(), event_name, Tasklist());
    }

    void Followers_t::Settle()
    {
        static const String_t event_name = String_t("On_Followers_Settle");
        Send(Non_Settlers(), event_name, Tasklist());
    }

    void Followers_t::Unsettle()
    {
        static const String_t event_name = String_t("On_Followers_Unsettle");
        Send(Settlers(), event_name, Tasklist());
    }

    void Followers_t::Sneak()
    {
        static const String_t event_name = String_t("On_Followers_Sneak");
        Send(Non_Sneaks(), event_name, Tasklist());
    }

    void Followers_t::Unsneak()
    {
        static const String_t event_name = String_t("On_Followers_Unsneak");
        Send(Sneaks(), event_name, Tasklist());
    }

    void Followers_t::Saddle()
    {
        static const String_t event_name = String_t("On_Followers_Saddle");
        Send(Non_Saddlers(), event_name, Tasklist());
    }

    void Followers_t::Unsaddle()
    {
        static const String_t event_name = String_t("On_Followers_Unsaddle");
        Send(Saddlers(), event_name, Tasklist());
    }

    void Followers_t::Retreat()
    {
        static const String_t event_name = String_t("On_Followers_Retreat");
        Send(Non_Retreaters(), event_name, Tasklist());
    }

    void Followers_t::Unretreat()
    {
        static const String_t event_name = String_t("On_Followers_Unretreat");
        Send(Retreaters(), event_name, Tasklist());
    }

    void Followers_t::Unfollow()
    {
        static const String_t event_name = String_t("On_Followers_Unfollow");
        Send(Followers(), event_name, Tasklist());
    }

    void Followers_t::Unmember()
    {
        static const String_t event_name = String_t("On_Followers_Unmember");
        Send(Followers(), event_name, Tasklist());
    }

    void Followers_t::Summon(Vector_t<Follower_t*> followers, float radius, float degree, float interval)
    {
        u64 size = followers.size();
        if (size > 0) {
            u64 idx;
            float odd_degree;
            float even_degree;
            if (followers.size() % 2 != 0) {
                Follower_t* follower = followers[0];
                if (follower) {
                    follower->Summon(radius, degree);
                }
                idx = 1;
                odd_degree = degree - interval;
                even_degree = degree + interval;
            } else {
                float interval_half = interval / 2;
                idx = 0;
                odd_degree = degree - interval_half;
                even_degree = degree + interval_half;
            }
            for (; idx < size; idx += 1) {
                Follower_t* follower = followers[idx];
                if (follower) {
                    if (idx % 2 == 0) {
                        follower->Summon(radius, even_degree);
                        even_degree += interval;
                    } else {
                        follower->Summon(radius, odd_degree);
                        odd_degree -= interval;
                    }
                }
            }
        }
    }

    void Followers_t::Summon_Filled(float radius, float degree, float interval)
    {
        Summon(Filled(), radius, degree, interval);
    }

    void Followers_t::Summon_Mobile(float radius, float degree, float interval)
    {
        Summon(Mobile(), radius, degree, interval);
    }

    void Followers_t::Summon_Immobile(float radius, float degree, float interval)
    {
        Summon(Immobile(), radius, degree, interval);
    }

    void Followers_t::Catch_Up()
    {
        Range_t<Follower_t**> range = Aliases();
        for (; range.begin < range.end; range.begin += 1) {
            Follower_t* follower = *range.begin;
            if (follower && follower->Is_Filled()) {
                follower->Catch_Up();
            }
        }
    }

    void Followers_t::Stash()
    {
        Range_t<Follower_t**> range = Aliases();
        for (; range.begin < range.end; range.begin += 1) {
            Follower_t* follower = *range.begin;
            if (follower && follower->Is_Filled()) {
                Member_t* member = follower->Member();
                if (member) {
                    Reference_t* pack = member->Pack();
                    if (pack) {
                        Object_Ref::Categorize(pack);
                    }
                }
            }
        }
    }

    Vector_t<Follower_t*> Followers_t::Filter(Vector_t<String_t>* strings, Vector_t<Int_t>* ints, Int_t flags_1, Int_t flags_2)
    {
        return Sort(Aliases_t::Filter(Aliases(), strings, ints, flags_1, flags_2));
    }

    // Horses_t //

    String_t Horses_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_horses");
        return class_name;
    }

    Class_Info_t* Horses_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Horses_t* Horses_t::Self()
    {
        static Horses_t* horses = static_cast<Horses_t*>(Game::Get_NPCP_Form(Consts::QUEST_FOLLOWERS));
        return horses;
    }

    Object_t* Horses_t::Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), Class_Name());
        return object;
    }

    Variable_t* Horses_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Range_t<UInt64> Horses_t::Indices()
    {
        return { BEGIN, END };
    }

    Range_t<Horse_t**> Horses_t::Aliases()
    {
        return Aliases_t::Aliases<Horse_t>(BEGIN, END);
    }

    Horse_t* Horses_t::From_ID(Int_t unique_id)
    {
        if (unique_id >= BEGIN && unique_id < END) {
            return Aliases_t::From_ID<Horse_t>(unique_id);
        } else {
            return nullptr;
        }
    }

    Horse_t* Horses_t::From_Actor(Actor_t* actor)
    {
        if (actor) {
            Horse_t* horse = Aliases_t::From_Actor<Horse_t>(actor);
            if (horse) {
                if (horse->id >= BEGIN && horse->id < END) {
                    return horse;
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

    // Alias_t //

    Int_t Alias_t::ID()
    {
        return id;
    }

    // Member_t //

    String_t Member_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_member");
        return class_name;
    }

    Class_Info_t* Member_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Variable_t* Member_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Actor_t* Member_t::Actor()
    {
        static const String_t variable_name = String_t("p_ref_actor");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Actor();
        } else {
            return nullptr;
        }
    }

    Follower_t* Member_t::Follower()
    {
        Followers_t* followers = Followers_t::Self();
        if (followers) {
            return followers->From_Actor(Actor());
        } else {
            return nullptr;
        }
    }

    Reference_t* Member_t::Pack()
    {
        static const String_t variable_name = String_t("p_container_pack");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Reference();
        } else {
            return 0;
        }
    }

    Cell_t* Member_t::Cell()
    {
        Actor_t* actor = Actor();
        return actor ? actor->parentCell : nullptr;
    }

    Int_t Member_t::Style()
    {
        static const String_t variable_name = String_t("p_code_style");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    Int_t Member_t::Vitality()
    {
        static const String_t variable_name = String_t("p_code_vitality");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    Int_t Member_t::Outfit2()
    {
        static const String_t variable_name = String_t("p_code_outfit2");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    Int_t Member_t::Rating()
    {
        static const String_t variable_name = String_t("p_int_rating");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    String_t Member_t::Sex()
    {
        static const String_t male = String_t("male");
        static const String_t female = String_t("female");
        static const String_t none = String_t("none");
        static const String_t invalid = String_t("");

        Int_t sex = Actor2::Sex(Actor());
        if (sex == 0) {
            return male;
        } else if (sex == 1) {
            return female;
        } else if (sex == -1) {
            return none;
        } else {
            return invalid;
        }
    }

    String_t Member_t::Race()
    {
        Actor_t* actor = Actor();
        return actor ? Actor2::Race(actor) : "";
    }

    String_t Member_t::Base_Name()
    {
        return Actor2::Get_Base_Name(Actor());
    }

    String_t Member_t::Reference_Name()
    {
        return Actor2::Get_Ref_Name(Actor());
    }

    String_t Member_t::Name()
    {
        return Actor2::Get_Name(Actor());
    }

    Bool_t Member_t::Is_Filled()
    {
        return Is_Created() && Actor() != nullptr;
    }

    Bool_t Member_t::Is_Unfilled()
    {
        return Is_Destroyed() || Actor() == nullptr;
    }

    Bool_t Member_t::Is_Loaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Loaded(actor);
    }

    Bool_t Member_t::Is_Unloaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unloaded(actor);
    }

    Bool_t Member_t::Is_Created()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Destroyed()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Unique()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unique(actor);
    }

    Bool_t Member_t::Is_Generic()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Generic(actor);
    }

    Bool_t Member_t::Is_Original()
    {
        static const String_t variable_name = String_t("p_is_clone");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Clone()
    {
        static const String_t variable_name = String_t("p_is_clone");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Alive()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Alive(actor);
    }

    Bool_t Member_t::Is_Dead()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Dead(actor);
    }

    Bool_t Member_t::Is_Mobile()
    {
        static const String_t variable_name = String_t("p_is_immobile");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Immobile()
    {
        static const String_t variable_name = String_t("p_is_immobile");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Settler()
    {
        static const String_t variable_name = String_t("p_is_settler");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Settler()
    {
        static const String_t variable_name = String_t("p_is_settler");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Thrall()
    {
        static const String_t variable_name = String_t("p_is_thrall");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Thrall()
    {
        static const String_t variable_name = String_t("p_is_thrall");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Paralyzed()
    {
        static const String_t variable_name = String_t("p_is_paralyzed");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Paralyzed()
    {
        static const String_t variable_name = String_t("p_is_paralyzed");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Mannequin()
    {
        static const String_t variable_name = String_t("p_is_mannequin");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Mannequin()
    {
        static const String_t variable_name = String_t("p_is_mannequin");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Reanimated()
    {
        static const String_t variable_name = String_t("p_is_reanimated");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Reanimated()
    {
        static const String_t variable_name = String_t("p_is_reanimated");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Follower()
    {
        return Follower() != nullptr;
    }

    Bool_t Member_t::Isnt_Follower()
    {
        return Follower() == nullptr;
    }

    Bool_t Member_t::Is_Sneak()
    {
        Follower_t* follower = Follower();
        return follower && follower->Is_Sneak();
    }

    Bool_t Member_t::Isnt_Sneak()
    {
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Sneak();
    }

    Bool_t Member_t::Is_Saddler()
    {
        Follower_t* follower = Follower();
        return follower && follower->Is_Saddler();
    }

    Bool_t Member_t::Isnt_Saddler()
    {
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Saddler();
    }

    Bool_t Member_t::Is_Retreater()
    {
        Follower_t* follower = Follower();
        return follower && follower->Is_Retreater();
    }

    Bool_t Member_t::Isnt_Retreater()
    {
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Retreater();
    }

    Bool_t Member_t::Has_Same_Head(Actor_t* other_actor)
    {
        if (other_actor) {
            Actor_t* alias_actor = Actor();
            if (alias_actor && Is_Created()) {
                Actor_Base_t* other_actor_base = static_cast<Actor_Base_t*>(other_actor->baseForm);
                Actor_Base_t* alias_actor_base = static_cast<Actor_Base_t*>(alias_actor->baseForm);
                if (other_actor_base && alias_actor_base && Actor_Base2::Has_Same_Head(other_actor_base, alias_actor_base)) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Member_t::On_Hit(Reference_t* attacker,
                          Form_t* tool,
                          Projectile_Base_t* projectile,
                          Bool_t is_power,
                          Bool_t is_sneak,
                          Bool_t is_bash,
                          Bool_t is_blocked)
    {
        static const String_t kill_func = String_t("p_Kill");

        // I would like to change these numbers before going out of beta.
        enum {
            IS_MORTAL = -303,
            IS_PROTECTED = -304,
            IS_ESSENTIAL = -305,
            IS_INVULNERABLE = -306
        };

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(Actor());
        if (value_owner && Is_Alive()) {
            Int_t member_vitality = Vitality();
            if (value_owner->Get_Actor_Value(Actor_Value_t::HEALTH) <= 0.0) {
                if (member_vitality == IS_MORTAL || member_vitality == IS_PROTECTED && attacker == *g_thePlayer) {
                    struct Args : public IFunctionArguments {
                        bool Copy(Output* output)
                        {
                            return true;
                        }
                    } func_args;
                    Handle_t handle(this);
                    handle.Registry()->QueueEvent(handle, &kill_func, &func_args);
                }
            } else if (member_vitality == IS_INVULNERABLE) {
                value_owner->Restore_Actor_Value(Actor_Modifier_t::DAMAGE, Actor_Value_t::HEALTH, 1000000000.0f);
            }
        }
    }

    void Member_t::Log_Variable_Infos()
    {
        Object_t* script = Object_t::Fetch(this, "doticu_npcp_member");
        if (script) {
            Class_Info_t* info = script->info;
            while (info) {
                info->Log_Variable_Infos();
                info = info->parent != info ? info->parent : nullptr;
            }
        }
    }

    // Follower_t //

    String_t Follower_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_follower");
        return class_name;
    }

    Class_Info_t* Follower_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Variable_t* Follower_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Actor_t* Follower_t::Actor()
    {
        static const String_t variable_name = String_t("p_ref_actor");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Actor();
        } else {
            return nullptr;
        }
    }

    Member_t* Follower_t::Member()
    {
        Members_t* members = Members_t::Self();
        if (members) {
            return members->From_Actor(Actor());
        } else {
            return nullptr;
        }
    }

    Horse_t* Follower_t::Horse()
    {
        Horses_t* horses = Horses_t::Self();
        if (horses) {
            return horses->From_ID(ID() + Followers_t::MAX);
        } else {
            return nullptr;
        }
    }

    Reference_t* Follower_t::Pack()
    {
        Member_t* member = Member();
        return member ? member->Pack() : nullptr;
    }

    Cell_t* Follower_t::Cell()
    {
        Member_t* member = Member();
        return member ? member->Cell() : nullptr;
    }

    Int_t Follower_t::Style()
    {
        Member_t* member = Member();
        return member ? member->Style() : 0;
    }

    Int_t Follower_t::Vitality()
    {
        Member_t* member = Member();
        return member ? member->Vitality() : 0;
    }

    Int_t Follower_t::Outfit2()
    {
        Member_t* member = Member();
        return member ? member->Outfit2() : 0;
    }

    Int_t Follower_t::Rating()
    {
        Member_t* member = Member();
        return member ? member->Rating() : 0;
    }

    String_t Follower_t::Sex()
    {
        Member_t* member = Member();
        return member ? member->Sex() : "";
    }

    String_t Follower_t::Race()
    {
        Member_t* member = Member();
        return member ? member->Race() : "";
    }

    String_t Follower_t::Base_Name()
    {
        Member_t* member = Member();
        return member ? member->Base_Name() : "";
    }

    String_t Follower_t::Reference_Name()
    {
        Member_t* member = Member();
        return member ? member->Reference_Name() : "";
    }

    String_t Follower_t::Name()
    {
        Member_t* member = Member();
        return member ? member->Name() : "";
    }

    Bool_t Follower_t::Is_Filled()
    {
        return Is_Created() && Actor() != nullptr;
    }

    Bool_t Follower_t::Is_Unfilled()
    {
        return Is_Destroyed() || Actor() == nullptr;
    }

    Bool_t Follower_t::Is_Loaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Loaded(actor);
    }

    Bool_t Follower_t::Is_Unloaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unloaded(actor);
    }

    Bool_t Follower_t::Is_Created()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Destroyed()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Unique()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unique(actor);
    }

    Bool_t Follower_t::Is_Generic()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Generic(actor);
    }

    Bool_t Follower_t::Is_Original()
    {
        Member_t* member = Member();
        return member && member->Is_Original();
    }

    Bool_t Follower_t::Is_Clone()
    {
        Member_t* member = Member();
        return member && member->Is_Clone();
    }

    Bool_t Follower_t::Is_Alive()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Alive(actor);
    }

    Bool_t Follower_t::Is_Dead()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Dead(actor);
    }

    Bool_t Follower_t::Is_Mobile()
    {
        Member_t* member = Member();
        return member && member->Is_Mobile();
    }

    Bool_t Follower_t::Is_Immobile()
    {
        Member_t* member = Member();
        return member && member->Is_Immobile();
    }

    Bool_t Follower_t::Is_Settler()
    {
        Member_t* member = Member();
        return member && member->Is_Settler();
    }

    Bool_t Follower_t::Isnt_Settler()
    {
        Member_t* member = Member();
        return member && member->Isnt_Settler();
    }

    Bool_t Follower_t::Is_Thrall()
    {
        Member_t* member = Member();
        return member && member->Is_Thrall();
    }

    Bool_t Follower_t::Isnt_Thrall()
    {
        Member_t* member = Member();
        return member && member->Isnt_Thrall();
    }

    Bool_t Follower_t::Is_Paralyzed()
    {
        Member_t* member = Member();
        return member && member->Is_Paralyzed();
    }

    Bool_t Follower_t::Isnt_Paralyzed()
    {
        Member_t* member = Member();
        return member && member->Isnt_Paralyzed();
    }

    Bool_t Follower_t::Is_Mannequin()
    {
        Member_t* member = Member();
        return member && member->Is_Mannequin();
    }

    Bool_t Follower_t::Isnt_Mannequin()
    {
        Member_t* member = Member();
        return member && member->Isnt_Mannequin();
    }

    Bool_t Follower_t::Is_Reanimated()
    {
        Member_t* member = Member();
        return member && member->Is_Reanimated();
    }

    Bool_t Follower_t::Isnt_Reanimated()
    {
        Member_t* member = Member();
        return member && member->Isnt_Reanimated();
    }

    Bool_t Follower_t::Is_Follower()
    {
        return Is_Filled();
    }

    Bool_t Follower_t::Isnt_Follower()
    {
        return Is_Unfilled();
    }

    Bool_t Follower_t::Is_Sneak()
    {
        static const String_t variable_name = String_t("p_is_sneak");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Isnt_Sneak()
    {
        static const String_t variable_name = String_t("p_is_sneak");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Saddler()
    {
        static const String_t variable_name = String_t("p_is_saddler");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Isnt_Saddler()
    {
        static const String_t variable_name = String_t("p_is_saddler");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Retreater()
    {
        static const String_t variable_name = String_t("p_is_retreater");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Isnt_Retreater()
    {
        static const String_t variable_name = String_t("p_is_retreater");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Near_Player(float radius)
    {
        Actor_t* actor = Actor();
        return actor && Object_Ref::Is_Near_Player(actor, radius);
    }

    Bool_t Follower_t::Isnt_Near_Player(float radius)
    {
        Actor_t* actor = Actor();
        return actor && !Object_Ref::Is_Near_Player(actor, radius);
    }

    Bool_t Follower_t::Is_In_Interior_Cell()
    {
        Cell_t* cell = Cell();
        return cell && Cell::Is_Interior(cell);
    }

    Bool_t Follower_t::Is_In_Exterior_Cell()
    {
        Cell_t* cell = Cell();
        return cell && Cell::Is_Exterior(cell);
    }

    void Follower_t::Summon(float radius, float degree)
    {
        Actor_t* player_actor = *g_thePlayer;
        Actor_t* follower_actor = Actor();
        if (player_actor && follower_actor && Is_Created()) {
            if (Player::Is_In_Exterior_Cell() && Is_Saddler()) {
                Horse_t* follower_horse = Horse();
                Actor_t* follower_horse_actor = follower_horse ? follower_horse->Actor() : nullptr;
                if (follower_horse_actor) {
                    Actor2::Move_To_Orbit(follower_horse_actor, player_actor, radius * 4, degree + 12);
                    Actor2::Move_To_Orbit(follower_actor, player_actor, radius * 3.5, degree);
                    Saddle();
                } else {
                    Actor2::Move_To_Orbit(follower_actor, player_actor, radius, degree);
                }
            } else {
                Actor2::Move_To_Orbit(follower_actor, player_actor, radius, degree);
            }
        }
    }

    void Follower_t::Summon_Ahead(float radius)
    {
        Summon(radius, 0);
    }

    void Follower_t::Summon_Behind(float radius)
    {
        Summon(radius, 180);
    }

    void Follower_t::Catch_Up()
    {
        if (Is_Filled() && Is_Mobile() && Isnt_Paralyzed() && Isnt_Mannequin()) {
            if (Player::Is_In_Interior_Cell() || Isnt_Saddler()) {
                if (Isnt_Near_Player()) {
                    Summon_Behind();
                }
            } else {
                Horse_t* horse = Horse();
                if (horse) {
                    Actor_t* horse_actor = horse->Actor();
                    if (horse_actor && !Object_Ref::Is_Near_Player(horse_actor, 10240.0f)) {
                        if (Player::Is_On_Mount()) {
                            Summon_Behind(1024.0f);
                        } else {
                            Summon_Behind();
                        }
                        Saddle();
                    }
                }
            }
        }
    }

    void Follower_t::Saddle()
    {
        static const String_t func_name = String_t("p_Saddle");

        struct Args : public IFunctionArguments {
            bool Copy(Output* output)
            {
                return true;
            }
        } args;

        Handle_t handle(this);
        handle.Registry()->QueueEvent(handle, &func_name, &args);
    }

    void Follower_t::Level()
    {
        Actor_t* player_actor = *g_thePlayer;
        Actor_t* follower_actor = Actor();
        if (player_actor && follower_actor && Is_Created()) {
            Actor_Value_Owner_t* values =
                Actor2::Actor_Value_Owner(follower_actor);
            Actor_Value_Owner_t* base_values =
                Actor_Base2::Actor_Value_Owner(static_cast<Actor_Base_t*>(follower_actor->baseForm));
            if (values && base_values) {
                const UInt16 player_level = CALL_MEMBER_FN(player_actor, GetLevel)();
                const float player_modifier = 0.67f - (log((float)player_level) * 0.067f);

                float health;
                float magicka;
                float stamina;

                float one_handed;
                float two_handed;
                float block;
                float heavy_armor;
                float light_armor;
                float smithing;

                float destruction;
                float restoration;
                float conjuration;
                float alteration;
                float illusion;
                float enchanting;

                float marksman;
                float sneak;
                float alchemy;
                float lockpicking;
                float pickpocket;
                float speechcraft;

                auto Get_Values = [&]() -> void
                {
                    auto Get_Value = [&](Actor_Value_t value_type) -> float
                    {
                        return base_values->Get_Base_Actor_Value(value_type) * player_modifier;
                    };

                    health = Get_Value(Actor_Value_t::HEALTH);
                    magicka = Get_Value(Actor_Value_t::MAGICKA);
                    stamina = Get_Value(Actor_Value_t::STAMINA);

                    one_handed = Get_Value(Actor_Value_t::ONE_HANDED);
                    two_handed = Get_Value(Actor_Value_t::TWO_HANDED);
                    block = Get_Value(Actor_Value_t::BLOCK);
                    heavy_armor = Get_Value(Actor_Value_t::HEAVY_ARMOR);
                    light_armor = Get_Value(Actor_Value_t::LIGHT_ARMOR);
                    smithing = Get_Value(Actor_Value_t::SMITHING);

                    destruction = Get_Value(Actor_Value_t::DESTRUCTION);
                    restoration = Get_Value(Actor_Value_t::RESTORATION);
                    conjuration = Get_Value(Actor_Value_t::CONJURATION);
                    alteration = Get_Value(Actor_Value_t::ALTERATION);
                    illusion = Get_Value(Actor_Value_t::ILLUSION);
                    enchanting = Get_Value(Actor_Value_t::ENCHANTING);

                    marksman = Get_Value(Actor_Value_t::MARKSMAN);
                    sneak = Get_Value(Actor_Value_t::SNEAK);
                    alchemy = Get_Value(Actor_Value_t::ALCHEMY);
                    lockpicking = Get_Value(Actor_Value_t::LOCKPICKING);
                    pickpocket = Get_Value(Actor_Value_t::PICKPOCKET);
                    speechcraft = Get_Value(Actor_Value_t::SPEECHCRAFT);
                };

                auto Mod_Values = [&]() -> void
                {
                    auto Mod_Strength = [&](float modifier) -> void
                    {
                        one_handed += modifier;
                        two_handed += modifier;
                        block += modifier;
                        heavy_armor += modifier;
                        light_armor += modifier;
                        smithing += modifier;
                    };

                    auto Mod_Intelligence = [&](float modifier) -> void
                    {
                        destruction += modifier;
                        restoration += modifier;
                        conjuration += modifier;
                        alteration += modifier;
                        illusion += modifier;
                        enchanting += modifier;
                    };

                    auto Mod_Dexterity = [&](float modifier) -> void
                    {
                        marksman += modifier;
                        sneak += modifier;
                        alchemy += modifier;
                        lockpicking += modifier;
                        pickpocket += modifier;
                        speechcraft += modifier;
                    };

                    // I want to update these before going out of beta
                    enum {
                        IS_WARRIOR = -381,
                        IS_MAGE = -382,
                        IS_ARCHER = -383
                    };
                    const SInt32 follower_style = Style();
                    const float player_level_modded = player_level * player_modifier;
                    if (follower_style == IS_WARRIOR) {
                        health += player_level * 4; // find a better equation
                        Mod_Strength(+player_level_modded);
                        Mod_Intelligence(-player_level_modded);
                        Mod_Dexterity(-player_level_modded);
                    } else if (follower_style == IS_MAGE) {
                        magicka += player_level * 4; // find a better equation
                        Mod_Strength(-player_level_modded);
                        Mod_Intelligence(+player_level_modded);
                        Mod_Dexterity(-player_level_modded);
                    } else if (follower_style == IS_ARCHER) {
                        stamina += player_level * 4; // find a better equation
                        Mod_Strength(-player_level_modded);
                        Mod_Intelligence(-player_level_modded);
                        Mod_Dexterity(+player_level_modded);
                    }
                };

                auto Set_Values = [&]() -> void
                {
                    constexpr float max_attribute = 1000.0f;
                    constexpr float min_attribute = 100.0f;
                    constexpr float max_skill = 100.0f;
                    constexpr float min_skill = 0.0f;

                    auto Set_Attribute = [&](Actor_Value_t value_type, float value) -> void
                    {
                        values->Set_Base_Actor_Value(
                            value_type,
                            value > max_attribute ? max_attribute :
                            value < min_attribute ? min_attribute :
                            value
                        );
                    };

                    auto Set_Skill = [&](Actor_Value_t value_type, float value) -> void
                    {
                        values->Set_Base_Actor_Value(
                            value_type,
                            value > max_skill ? max_skill :
                            value < min_skill ? min_skill :
                            value
                        );
                    };

                    Set_Attribute(Actor_Value_t::HEALTH, health);
                    Set_Attribute(Actor_Value_t::MAGICKA, magicka);
                    Set_Attribute(Actor_Value_t::STAMINA, stamina);

                    Set_Skill(Actor_Value_t::ONE_HANDED, one_handed);
                    Set_Skill(Actor_Value_t::TWO_HANDED, two_handed);
                    Set_Skill(Actor_Value_t::BLOCK, block);
                    Set_Skill(Actor_Value_t::HEAVY_ARMOR, heavy_armor);
                    Set_Skill(Actor_Value_t::LIGHT_ARMOR, light_armor);
                    Set_Skill(Actor_Value_t::SMITHING, smithing);

                    Set_Skill(Actor_Value_t::DESTRUCTION, destruction);
                    Set_Skill(Actor_Value_t::RESTORATION, restoration);
                    Set_Skill(Actor_Value_t::CONJURATION, conjuration);
                    Set_Skill(Actor_Value_t::ALTERATION, alteration);
                    Set_Skill(Actor_Value_t::ILLUSION, illusion);
                    Set_Skill(Actor_Value_t::ENCHANTING, enchanting);

                    Set_Skill(Actor_Value_t::MARKSMAN, marksman);
                    Set_Skill(Actor_Value_t::SNEAK, sneak);
                    Set_Skill(Actor_Value_t::ALCHEMY, alchemy);
                    Set_Skill(Actor_Value_t::LOCKPICKING, lockpicking);
                    Set_Skill(Actor_Value_t::PICKPOCKET, pickpocket);
                    Set_Skill(Actor_Value_t::SPEECHCRAFT, speechcraft);
                };

                auto Check_Values = [&]() -> void
                {
                    auto Check_Value = [&](Actor_Value_t value_type, float desired_value) -> void
                    {
                        float permanent_value = values->Get_Permanent_Actor_Value(value_type);
                        if (permanent_value < 0.0f) {
                            values->Restore_Actor_Value(Actor_Modifier_t::PERMANENT,
                                                        value_type,
                                                        -permanent_value + desired_value);
                            permanent_value = values->Get_Permanent_Actor_Value(value_type);
                            if (permanent_value < 0.0f) {
                                values->Mod_Actor_Value(value_type,
                                                        -permanent_value + desired_value);
                            }
                        }
                    };

                    Check_Value(Actor_Value_t::HEALTH, health);
                    Check_Value(Actor_Value_t::MAGICKA, magicka);
                    Check_Value(Actor_Value_t::STAMINA, stamina);

                    Check_Value(Actor_Value_t::ONE_HANDED, one_handed);
                    Check_Value(Actor_Value_t::TWO_HANDED, two_handed);
                    Check_Value(Actor_Value_t::BLOCK, block);
                    Check_Value(Actor_Value_t::HEAVY_ARMOR, heavy_armor);
                    Check_Value(Actor_Value_t::LIGHT_ARMOR, light_armor);
                    Check_Value(Actor_Value_t::SMITHING, smithing);

                    Check_Value(Actor_Value_t::DESTRUCTION, destruction);
                    Check_Value(Actor_Value_t::RESTORATION, restoration);
                    Check_Value(Actor_Value_t::CONJURATION, conjuration);
                    Check_Value(Actor_Value_t::ALTERATION, alteration);
                    Check_Value(Actor_Value_t::ILLUSION, illusion);
                    Check_Value(Actor_Value_t::ENCHANTING, enchanting);

                    Check_Value(Actor_Value_t::MARKSMAN, marksman);
                    Check_Value(Actor_Value_t::SNEAK, sneak);
                    Check_Value(Actor_Value_t::ALCHEMY, alchemy);
                    Check_Value(Actor_Value_t::LOCKPICKING, lockpicking);
                    Check_Value(Actor_Value_t::PICKPOCKET, pickpocket);
                    Check_Value(Actor_Value_t::SPEECHCRAFT, speechcraft);
                };

                Get_Values();
                Mod_Values();
                Set_Values();
                Check_Values();
            }
        }
    }

    void Follower_t::Unlevel()
    {
        if (!Is_Created()) {
            return;
        }

        Actor_t* follower_actor = Actor();
        if (!follower_actor) {
            return;
        }

        TESNPC* follower_base = static_cast<TESNPC*>(follower_actor->baseForm);
        if (!follower_base) {
            return;
        }

        #define RESET_VALUE(NAME)                                       \
        (                                                               \
            Actor2::Set_Actor_Value(follower_actor, NAME,               \
                Actor_Base2::Get_Base_Actor_Value(follower_base, NAME)  \
            )                                                           \
        )

        RESET_VALUE("Health");
        RESET_VALUE("Magicka");
        RESET_VALUE("Stamina");

        RESET_VALUE("OneHanded");
        RESET_VALUE("TwoHanded");
        RESET_VALUE("Block");
        RESET_VALUE("HeavyArmor");
        RESET_VALUE("LightArmor");
        RESET_VALUE("Smithing");

        RESET_VALUE("Destruction");
        RESET_VALUE("Restoration");
        RESET_VALUE("Conjuration");
        RESET_VALUE("Alteration");
        RESET_VALUE("Illusion");
        RESET_VALUE("Enchanting");

        RESET_VALUE("Marksman");
        RESET_VALUE("Sneak");
        RESET_VALUE("Alchemy");
        RESET_VALUE("Lockpicking");
        RESET_VALUE("Pickpocket");
        RESET_VALUE("Speechcraft");

        #undef RESET_VALUE
    }

    // Horse_t //

    String_t Horse_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_horse");
        return class_name;
    }

    Class_Info_t* Horse_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Variable_t* Horse_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Actor_t* Horse_t::Actor()
    {
        static const String_t variable_name = String_t("p_ref_actor");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Actor();
        } else {
            return nullptr;
        }
    }

    Follower_t* Horse_t::Follower()
    {
        Followers_t* followers = Followers_t::Self();
        if (followers) {
            return followers->From_ID(ID() - Followers_t::MAX);
        } else {
            return nullptr;
        }
    }

}}

// Exports //

#define FORWARD_POINTER(METHOD_) { return self ? self->METHOD_ : nullptr; }
#define FORWARD_BOOL(METHOD_) { return self ? self->METHOD_ : false; }
#define FORWARD_INT(METHOD_) { return self ? self->METHOD_ : 0; }
#define FORWARD_VECTOR(METHOD_, TYPE_) { return self ? self->METHOD_ : Vector_t<TYPE_>(); }
#define FORWARD_VOID(METHOD_) { self ? self->METHOD_, 1 : 0; }

namespace doticu_npcp { namespace Party { namespace Aliases { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        return true;
    }

}}}}

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

namespace doticu_npcp { namespace Party { namespace Followers { namespace Exports {

    Follower_t* From_ID(Followers_t* self, Int_t unique_id) FORWARD_POINTER(From_ID(unique_id));
    Follower_t* From_Actor(Followers_t* self, Actor_t* actor) FORWARD_POINTER(From_Actor(actor));
    Follower_t* From_Unfilled(Followers_t* self) FORWARD_POINTER(From_Unfilled());
    Follower_t* From_Horse_Actor(Followers_t* self, Actor_t* actor) FORWARD_POINTER(From_Horse_Actor(actor));

    Bool_t Has_Space(Followers_t* self) FORWARD_BOOL(Has_Space());
    Bool_t Hasnt_Space(Followers_t* self) FORWARD_BOOL(Hasnt_Space());
    Bool_t Has_Actor(Followers_t* self, Actor_t* actor) FORWARD_BOOL(Has_Actor(actor));
    Bool_t Hasnt_Actor(Followers_t* self, Actor_t* actor) FORWARD_BOOL(Hasnt_Actor(actor));
    Bool_t Are_In_Combat(Followers_t* self) FORWARD_BOOL(Are_In_Combat());

    Int_t Max(Followers_t* self) FORWARD_INT(Max());
    Int_t Count_Filled(Followers_t* self) FORWARD_INT(Count_Filled());
    Int_t Count_Unfilled(Followers_t* self) FORWARD_INT(Count_Unfilled());
    Int_t Count_Loaded(Followers_t* self) FORWARD_INT(Count_Loaded());
    Int_t Count_Unloaded(Followers_t* self) FORWARD_INT(Count_Unloaded());
    Int_t Count_Unique(Followers_t* self) FORWARD_INT(Count_Unique());
    Int_t Count_Generic(Followers_t* self) FORWARD_INT(Count_Generic());
    Int_t Count_Alive(Followers_t* self) FORWARD_INT(Count_Alive());
    Int_t Count_Dead(Followers_t* self) FORWARD_INT(Count_Dead());
    Int_t Count_Originals(Followers_t* self) FORWARD_INT(Count_Originals());
    Int_t Count_Clones(Followers_t* self) FORWARD_INT(Count_Clones());
    Int_t Count_Mobile(Followers_t* self) FORWARD_INT(Count_Mobile());
    Int_t Count_Immobile(Followers_t* self) FORWARD_INT(Count_Immobile());
    Int_t Count_Settlers(Followers_t* self) FORWARD_INT(Count_Settlers());
    Int_t Count_Non_Settlers(Followers_t* self) FORWARD_INT(Count_Non_Settlers());
    Int_t Count_Thralls(Followers_t* self) FORWARD_INT(Count_Thralls());
    Int_t Count_Non_Thralls(Followers_t* self) FORWARD_INT(Count_Non_Thralls());
    Int_t Count_Paralyzed(Followers_t* self) FORWARD_INT(Count_Paralyzed());
    Int_t Count_Non_Paralyzed(Followers_t* self) FORWARD_INT(Count_Non_Paralyzed());
    Int_t Count_Mannequins(Followers_t* self) FORWARD_INT(Count_Mannequins());
    Int_t Count_Non_Mannequins(Followers_t* self) FORWARD_INT(Count_Non_Mannequins());
    Int_t Count_Reanimated(Followers_t* self) FORWARD_INT(Count_Reanimated());
    Int_t Count_Non_Reanimated(Followers_t* self) FORWARD_INT(Count_Non_Reanimated());
    Int_t Count_Followers(Followers_t* self) FORWARD_INT(Count_Followers());
    Int_t Count_Non_Followers(Followers_t* self) FORWARD_INT(Count_Non_Followers());
    Int_t Count_Sneaks(Followers_t* self) FORWARD_INT(Count_Sneaks());
    Int_t Count_Non_Sneaks(Followers_t* self) FORWARD_INT(Count_Non_Sneaks());
    Int_t Count_Saddlers(Followers_t* self) FORWARD_INT(Count_Saddlers());
    Int_t Count_Non_Saddlers(Followers_t* self) FORWARD_INT(Count_Non_Saddlers());
    Int_t Count_Retreaters(Followers_t* self) FORWARD_INT(Count_Retreaters());
    Int_t Count_Non_Retreaters(Followers_t* self) FORWARD_INT(Count_Non_Retreaters());

    Vector_t<Follower_t*> All(Followers_t* self) FORWARD_VECTOR(All(), Follower_t*);
    Vector_t<Follower_t*> Filled(Followers_t* self) FORWARD_VECTOR(Filled(), Follower_t*);
    Vector_t<Follower_t*> Unfilled(Followers_t* self) FORWARD_VECTOR(Unfilled(), Follower_t*);
    Vector_t<Follower_t*> Loaded(Followers_t* self) FORWARD_VECTOR(Loaded(), Follower_t*);
    Vector_t<Follower_t*> Unloaded(Followers_t* self) FORWARD_VECTOR(Unloaded(), Follower_t*);

    Vector_t<Follower_t*> Sort_Filled(Followers_t* self, Int_t begin, Int_t end) FORWARD_VECTOR(Sort_Filled(begin, end), Follower_t*);

    Vector_t<Follower_t*> Slice(Followers_t* self, VMArray<Follower_t*>followers_array, Int_t begin, Int_t end)
    {
        Vector_t<Follower_t*> followers_vector = Slice_Array(followers_array);
        return self->Slice(followers_vector, begin, end);
    }

    void Register_(Followers_t* self) FORWARD_VOID(Followers_t::Register());
    void Enforce(Followers_t* self) FORWARD_VOID(Enforce());
    void Resurrect(Followers_t* self) FORWARD_VOID(Resurrect());
    void Mobilize(Followers_t* self) FORWARD_VOID(Mobilize());
    void Immobilize(Followers_t* self) FORWARD_VOID(Immobilize());
    void Settle(Followers_t* self) FORWARD_VOID(Settle());
    void Unsettle(Followers_t* self) FORWARD_VOID(Unsettle());
    void Sneak(Followers_t* self) FORWARD_VOID(Sneak());
    void Unsneak(Followers_t* self) FORWARD_VOID(Unsneak());
    void Saddle(Followers_t* self) FORWARD_VOID(Saddle());
    void Unsaddle(Followers_t* self) FORWARD_VOID(Unsaddle());
    void Retreat(Followers_t* self) FORWARD_VOID(Retreat());
    void Unretreat(Followers_t* self) FORWARD_VOID(Unretreat());
    void Unfollow(Followers_t* self) FORWARD_VOID(Unfollow());
    void Unmember(Followers_t* self) FORWARD_VOID(Unmember());

    void Summon_Filled(Followers_t* self, float radius, float degree, float interval) FORWARD_VOID(Summon_Filled());
    void Summon_Mobile(Followers_t* self, float radius, float degree, float interval) FORWARD_VOID(Summon_Mobile());
    void Summon_Immobile(Followers_t* self, float radius, float degree, float interval) FORWARD_VOID(Summon_Immobile());

    void Catch_Up(Followers_t* self) FORWARD_VOID(Catch_Up());
    void Stash(Followers_t* self) FORWARD_VOID(Stash());

    Vector_t<String_t> Filter_Strings(Followers_t* self, String_t sex, String_t race, String_t search)
        FORWARD_VECTOR(Followers_t::Filter_Strings(sex, race, search), String_t);
    Vector_t<Int_t> Filter_Ints(Followers_t* self, Int_t style, Int_t vitality, Int_t outfit2, Int_t rating)
        FORWARD_VECTOR(Followers_t::Filter_Ints(style, vitality, outfit2, rating), Int_t);
    Int_t Add_Filter_Flag_1(Followers_t* self, Int_t flags_1, String_t flag_1)
        FORWARD_INT(Followers_t::Add_Filter_Flag_1(flags_1, flag_1));
    Int_t Add_Filter_Flag_2(Followers_t* self, Int_t flags_2, String_t flag_2)
        FORWARD_INT(Followers_t::Add_Filter_Flag_2(flags_2, flag_2));
    Vector_t<Follower_t*> Filter(Followers_t* self, VMArray<String_t> strings, VMArray<Int_t> ints, Int_t flags_1, Int_t flags_2)
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
            ADD_CLASS_METHOD(Followers_t::Class_Name(), Followers_t,    \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("p_From_ID", 1, Follower_t*, From_ID, Int_t);
        ADD_METHOD("p_From_Actor", 1, Follower_t*, From_Actor, Actor_t*);
        ADD_METHOD("p_From_Unfilled", 0, Follower_t*, From_Unfilled);
        ADD_METHOD("p_From_Horse_Actor", 1, Follower_t*, From_Horse_Actor, Actor_t*);

        ADD_METHOD("Has_Space", 0, Bool_t, Has_Space);
        ADD_METHOD("Hasnt_Space", 0, Bool_t, Hasnt_Space);
        ADD_METHOD("Has_Actor", 1, Bool_t, Has_Actor, Actor_t*);
        ADD_METHOD("Hasnt_Actor", 1, Bool_t, Hasnt_Actor, Actor_t*);
        ADD_METHOD("Are_In_Combat", 0, Bool_t, Are_In_Combat);

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

        ADD_METHOD("All", 0, Vector_t<Follower_t*>, All);
        ADD_METHOD("Filled", 0, Vector_t<Follower_t*>, Filled);
        ADD_METHOD("Unfilled", 0, Vector_t<Follower_t*>, Unfilled);
        ADD_METHOD("Loaded", 0, Vector_t<Follower_t*>, Loaded);
        ADD_METHOD("Unloaded", 0, Vector_t<Follower_t*>, Unloaded);

        ADD_METHOD("Sort_Filled", 2, Vector_t<Follower_t*>, Sort_Filled, Int_t, Int_t);

        ADD_METHOD("Slice", 3, Vector_t<Follower_t*>, Slice, VMArray<Follower_t*>, Int_t, Int_t);

        ADD_METHOD("p_Register", 0, void, Register_);
        ADD_METHOD("p_Enforce", 0, void, Enforce);
        ADD_METHOD("p_Resurrect", 0, void, Resurrect);
        ADD_METHOD("p_Mobilize", 0, void, Mobilize);
        ADD_METHOD("p_Immobilize", 0, void, Immobilize);
        ADD_METHOD("p_Settle", 0, void, Settle);
        ADD_METHOD("p_Unsettle", 0, void, Unsettle);
        ADD_METHOD("p_Sneak", 0, void, Sneak);
        ADD_METHOD("p_Unsneak", 0, void, Unsneak);
        ADD_METHOD("p_Saddle", 0, void, Saddle);
        ADD_METHOD("p_Unsaddle", 0, void, Unsaddle);
        ADD_METHOD("p_Retreat", 0, void, Retreat);
        ADD_METHOD("p_Unretreat", 0, void, Unretreat);
        ADD_METHOD("p_Unfollow", 0, void, Unfollow);
        ADD_METHOD("p_Unmember", 0, void, Unmember);

        ADD_METHOD("p_Summon_Filled", 3, void, Summon_Filled, float, float, float);
        ADD_METHOD("p_Summon_Mobile", 3, void, Summon_Mobile, float, float, float);
        ADD_METHOD("p_Summon_Immobile", 3, void, Summon_Immobile, float, float, float);

        ADD_METHOD("p_Catch_Up", 0, void, Catch_Up);
        ADD_METHOD("p_Stash", 0, void, Stash);

        ADD_METHOD("Filter_Strings", 3, Vector_t<String_t>, Filter_Strings, String_t, String_t, String_t);
        ADD_METHOD("Filter_Ints", 4, Vector_t<Int_t>, Filter_Ints, Int_t, Int_t, Int_t, Int_t);
        ADD_METHOD("Add_Filter_Flag_1", 2, Int_t, Add_Filter_Flag_1, Int_t, String_t);
        ADD_METHOD("Add_Filter_Flag_2", 2, Int_t, Add_Filter_Flag_2, Int_t, String_t);
        ADD_METHOD("Filter", 4, Vector_t<Follower_t*>, Filter, VMArray<String_t>, VMArray<Int_t>, Int_t, Int_t);

        #undef ADD_METHOD

        return true;
    }

}}}}

namespace doticu_npcp { namespace Party { namespace Horses { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        return true;
    }

}}}}

namespace doticu_npcp { namespace Party { namespace Alias { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        return true;
    }

}}}}

namespace doticu_npcp { namespace Party { namespace Member { namespace Exports {

    Actor_t* Actor(Member_t* self) FORWARD_POINTER(Actor());
    Int_t ID(Member_t* self) FORWARD_INT(ID());

    void On_Hit(Member_t* self,
                Reference_t* attacker,
                Form_t* tool,
                Projectile_Base_t* projectile,
                Bool_t is_power,
                Bool_t is_sneak,
                Bool_t is_bash,
                Bool_t is_blocked)
        FORWARD_VOID(On_Hit(attacker, tool, projectile, is_power, is_sneak, is_bash, is_blocked));

    void Log_Variable_Infos(Member_t* self) FORWARD_VOID(Log_Variable_Infos());

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Member_t::Class_Name(), Member_t,          \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Actor", 0, Actor_t*, Actor);
        ADD_METHOD("ID", 0, Int_t, ID);

        ADD_METHOD("OnHit", 7, void, On_Hit, Reference_t*, Form_t*, Projectile_Base_t*, Bool_t, Bool_t, Bool_t, Bool_t);

        ADD_METHOD("Log_Variable_Infos", 0, void, Log_Variable_Infos);

        #undef ADD_METHOD

        return true;
    }

}}}}

namespace doticu_npcp { namespace Party { namespace Follower { namespace Exports {

    Actor_t* Actor(Follower_t* self) FORWARD_POINTER(Actor());
    Int_t ID(Follower_t* self) FORWARD_INT(ID());

    void Level(Follower_t* self) FORWARD_VOID(Follower_t::Level());
    void Unlevel(Follower_t* self) FORWARD_VOID(Follower_t::Unlevel());

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Follower_t::Class_Name(), Follower_t,      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Actor", 0, Actor_t*, Actor);
        ADD_METHOD("ID", 0, Int_t, ID);

        ADD_METHOD("p_Level", 0, void, Level);
        ADD_METHOD("p_Unlevel", 0, void, Unlevel);

        return true;
    }

}}}}

namespace doticu_npcp { namespace Party { namespace Horse { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        return true;
    }

}}}}

#undef FORWARD_POINTER
#undef FORWARD_BOOL
#undef FORWARD_INT
#undef FORWARD_VECTOR
#undef FORWARD_VOID
