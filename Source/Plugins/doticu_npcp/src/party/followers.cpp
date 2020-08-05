/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "game.h"
#include "object_ref.h"
#include "party.h"
#include "party.inl"
#include "utils.h"
#include "vars.h"

namespace doticu_npcp { namespace Party {

    String_t Followers_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_followers");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Followers_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Followers_t* Followers_t::Self()
    {
        return static_cast<Followers_t*>(Consts::Followers_Quest());
    }

    Object_t* Followers_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Followers_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
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
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled);
    }

    Int_t Followers_t::Count_Unfilled()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Unfilled);
    }

    Int_t Followers_t::Count_Loaded()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Loaded);
    }

    Int_t Followers_t::Count_Unloaded()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unloaded);
    }

    Int_t Followers_t::Count_Unique()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unique);
    }

    Int_t Followers_t::Count_Generic()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Generic);
    }

    Int_t Followers_t::Count_Alive()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Alive);
    }

    Int_t Followers_t::Count_Dead()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Dead);
    }

    Int_t Followers_t::Count_Originals()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Original);
    }

    Int_t Followers_t::Count_Clones()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Clone);
    }

    Int_t Followers_t::Count_Mobile()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mobile);
    }

    Int_t Followers_t::Count_Immobile()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Immobile);
    }

    Int_t Followers_t::Count_Settlers()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Settler);
    }

    Int_t Followers_t::Count_Non_Settlers()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Settler);
    }

    Int_t Followers_t::Count_Thralls()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Thrall);
    }

    Int_t Followers_t::Count_Non_Thralls()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Thrall);
    }

    Int_t Followers_t::Count_Paralyzed()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Paralyzed);
    }

    Int_t Followers_t::Count_Non_Paralyzed()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Paralyzed);
    }

    Int_t Followers_t::Count_Mannequins()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mannequin);
    }

    Int_t Followers_t::Count_Non_Mannequins()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Mannequin);
    }

    Int_t Followers_t::Count_Reanimated()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Reanimated);
    }

    Int_t Followers_t::Count_Non_Reanimated()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Reanimated);
    }

    Int_t Followers_t::Count_Followers()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Follower);
    }

    Int_t Followers_t::Count_Non_Followers()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Follower);
    }

    Int_t Followers_t::Count_Sneaks()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Sneak);
    }

    Int_t Followers_t::Count_Non_Sneaks()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Sneak);
    }

    Int_t Followers_t::Count_Saddlers()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Saddler);
    }

    Int_t Followers_t::Count_Non_Saddlers()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Saddler);
    }

    Int_t Followers_t::Count_Retreaters()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Retreater);
    }

    Int_t Followers_t::Count_Non_Retreaters()
    {
        return Count_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Retreater);
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
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Unfilled()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Unfilled, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Loaded()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Loaded, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Unloaded()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unloaded, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Unique()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Unique, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Generic()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Generic, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Alive()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Alive, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Dead()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Dead, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Originals()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Original, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Clones()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Clone, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Mobile()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mobile, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Immobile()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Immobile, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Settlers()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Settler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Settlers()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Settler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Thralls()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Thrall, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Thralls()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Thrall, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Paralyzed()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Paralyzed, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Paralyzed()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Paralyzed, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Mannequins()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Mannequin, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Mannequins()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Mannequin, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Reanimated()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Reanimated, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Reanimated()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Reanimated, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Followers()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Follower, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Followers()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Follower, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Sneaks()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Sneak, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Sneaks()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Sneak, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Saddlers()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Saddler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Saddlers()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Saddler, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Retreaters()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Is_Retreater, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Non_Retreaters()
    {
        return Copy_If<Follower_t>(Aliases(), &Follower_t::Is_Filled, &Follower_t::Isnt_Retreater, MAX);
    }

    Vector_t<Follower_t*> Followers_t::Sort(Vector_t<Follower_t*> followers)
    {
        return Aliases_t::Sort<Follower_t>(followers, Vars::Followers_Sort_Algorithm());
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

    // some of these can be made way faster now, by calling c++ innate funcs
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
        Vector_t<Follower_t*> immobile = Immobile();
        for (size_t idx = 0, size = immobile.size(); idx < size; idx += 1) {
            immobile[idx]->Mobilize();
        }
    }

    void Followers_t::Immobilize()
    {
        Vector_t<Follower_t*> mobile = Mobile();
        for (size_t idx = 0, size = mobile.size(); idx < size; idx += 1) {
            mobile[idx]->Immobilize();
        }
    }

    void Followers_t::Settle()
    {
        Vector_t<Follower_t*> non_settlers = Non_Settlers();
        for (size_t idx = 0, size = non_settlers.size(); idx < size; idx += 1) {
            non_settlers[idx]->Settle();
        }
    }

    void Followers_t::Unsettle()
    {
        Vector_t<Follower_t*> settlers = Settlers();
        for (size_t idx = 0, size = settlers.size(); idx < size; idx += 1) {
            settlers[idx]->Unsettle();
        }
    }

    void Followers_t::Enthrall()
    {
        Vector_t<Follower_t*> non_thralls = Non_Thralls();
        for (size_t idx = 0, size = non_thralls.size(); idx < size; idx += 1) {
            non_thralls[idx]->Enthrall();
        }
    }

    void Followers_t::Unthrall()
    {
        Vector_t<Follower_t*> thralls = Thralls();
        for (size_t idx = 0, size = thralls.size(); idx < size; idx += 1) {
            thralls[idx]->Unthrall();
        }
    }

    void Followers_t::Paralyze()
    {
        Vector_t<Follower_t*> non_paralyzed = Non_Paralyzed();
        for (size_t idx = 0, size = non_paralyzed.size(); idx < size; idx += 1) {
            non_paralyzed[idx]->Paralyze();
        }
    }

    void Followers_t::Unparalyze()
    {
        Vector_t<Follower_t*> paralyzed = Paralyzed();
        for (size_t idx = 0, size = paralyzed.size(); idx < size; idx += 1) {
            paralyzed[idx]->Unparalyze();
        }
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

}}

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
    void Enforce(Followers_t* self) FORWARD_VOID(Followers_t::Enforce());
    void Resurrect(Followers_t* self) FORWARD_VOID(Followers_t::Resurrect());
    void Mobilize(Followers_t* self) FORWARD_VOID(Followers_t::Mobilize());
    void Immobilize(Followers_t* self) FORWARD_VOID(Followers_t::Immobilize());
    void Settle(Followers_t* self) FORWARD_VOID(Followers_t::Settle());
    void Unsettle(Followers_t* self) FORWARD_VOID(Followers_t::Unsettle());
    void Enthrall(Followers_t* self) FORWARD_VOID(Followers_t::Enthrall());
    void Unthrall(Followers_t* self) FORWARD_VOID(Followers_t::Unthrall());
    void Paralyze(Followers_t* self) FORWARD_VOID(Followers_t::Paralyze());
    void Unparalyze(Followers_t* self) FORWARD_VOID(Followers_t::Unparalyze());
    void Sneak(Followers_t* self) FORWARD_VOID(Followers_t::Sneak());
    void Unsneak(Followers_t* self) FORWARD_VOID(Followers_t::Unsneak());
    void Saddle(Followers_t* self) FORWARD_VOID(Followers_t::Saddle());
    void Unsaddle(Followers_t* self) FORWARD_VOID(Followers_t::Unsaddle());
    void Retreat(Followers_t* self) FORWARD_VOID(Followers_t::Retreat());
    void Unretreat(Followers_t* self) FORWARD_VOID(Followers_t::Unretreat());
    void Unfollow(Followers_t* self) FORWARD_VOID(Followers_t::Unfollow());
    void Unmember(Followers_t* self) FORWARD_VOID(Followers_t::Unmember());

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
        ADD_METHOD("p_Enthrall", 0, void, Enthrall);
        ADD_METHOD("p_Unthrall", 0, void, Unthrall);
        ADD_METHOD("p_Paralyze", 0, void, Paralyze);
        ADD_METHOD("p_Unparalyze", 0, void, Unparalyze);
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
