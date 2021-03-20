/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "cell.h"
#include "codes.h"
#include "game.h"
#include "object_ref.h"
#include "outfit2.h"
#include "papyrus.inl"
#include "quest.h"
#include "string2.h"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "party/party_aliases.inl"
#include "party/party_npcs.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_settler.h"

#include "mcm/mcm_filter.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Members_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_members");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Members_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Members_t* Members_t::Self()
    {
        return static_cast<Members_t*>(Consts::Members_Quest());
    }

    Object_t* Members_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Members_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Members_t::Has_Display_Variable()
    {
        static const String_t variable_name = String_t("p_has_display");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* Members_t::Display_Idx_Variable()
    {
        static const String_t variable_name = String_t("p_idx_display");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* Members_t::Display_Marker_Variable()
    {
        static const String_t variable_name = String_t("p_marker_display");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Range_t<UInt64> Members_t::Indices()
    {
        return { BEGIN, END };
    }

    Range_t<Member_t**> Members_t::Aliases()
    {
        return Aliases_t::Aliases<Member_t>(BEGIN, END);
    }

    Reference_t* Members_t::Display_Marker()
    {
        return Display_Marker_Variable()->Reference();
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

    Bool_t Members_t::Has_Base(Actor_t* actor_with_base)
    {
        return actor_with_base && Aliases_t::Has_Base<Member_t>(Aliases(), actor_with_base);
    }

    Bool_t Members_t::Hasnt_Base(Actor_t* actor_with_base)
    {
        return actor_with_base && !Aliases_t::Has_Base<Member_t>(Aliases(), actor_with_base);
    }

    Bool_t Members_t::Has_Head(Actor_t* actor)
    {
        return actor && Aliases_t::Has_Head<Member_t>(Aliases(), actor);
    }

    Bool_t Members_t::Hasnt_Head(Actor_t* actor)
    {
        return actor && !Aliases_t::Has_Head<Member_t>(Aliases(), actor);
    }

    Bool_t Members_t::Has_Display()
    {
        return Has_Display_Variable()->Bool();
    }

    Bool_t Members_t::Hasnt_Display()
    {
        return !Has_Display_Variable()->Bool();
    }

    Bool_t Members_t::Is_Clone(Actor_t* actor)
    {
        Member_t* member = From_Actor(actor);
        return member && member->Is_Clone();
    }

    Bool_t Members_t::Should_Clone(Actor_t* actor)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        return
            (Actor2::Is_Unique(actor) && vars->Force_Clone_Uniques()) ||
            (Actor2::Is_Generic(actor) && vars->Force_Clone_Generics());
    }

    Bool_t Members_t::Should_Unclone(Actor_t* actor)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        return
            (Actor2::Is_Unique(actor) && vars->Force_Unclone_Uniques()) ||
            (Actor2::Is_Generic(actor) && vars->Force_Unclone_Generics());
    }

    Int_t Members_t::Max()
    {
        return MAX;
    }

    Int_t Members_t::Limit()
    {
        return Modules::Vars_t::Self()->Member_Limit();
    }

    Int_t Members_t::Count_Filled()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Filled);
    }

    Int_t Members_t::Count_Unfilled()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Unfilled);
    }

    Int_t Members_t::Count_Loaded()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Loaded);
    }

    Int_t Members_t::Count_Unloaded()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Unloaded);
    }

    Int_t Members_t::Count_Unique()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Unique);
    }

    Int_t Members_t::Count_Generic()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Generic);
    }

    Int_t Members_t::Count_Alive()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Alive);
    }

    Int_t Members_t::Count_Dead()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Dead);
    }

    Int_t Members_t::Count_Originals()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Original);
    }

    Int_t Members_t::Count_Clones()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Clone);
    }

    Int_t Members_t::Count_Mobile()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Mobile);
    }

    Int_t Members_t::Count_Immobile()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Immobile);
    }

    Int_t Members_t::Count_Settlers()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Settler);
    }

    Int_t Members_t::Count_Non_Settlers()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Settler);
    }

    Int_t Members_t::Count_Thralls()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Thrall);
    }

    Int_t Members_t::Count_Non_Thralls()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Thrall);
    }

    Int_t Members_t::Count_Paralyzed()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Paralyzed);
    }

    Int_t Members_t::Count_Non_Paralyzed()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Paralyzed);
    }

    Int_t Members_t::Count_Mannequins()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Mannequin);
    }

    Int_t Members_t::Count_Non_Mannequins()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Mannequin);
    }

    Int_t Members_t::Count_Reanimated()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Reanimated);
    }

    Int_t Members_t::Count_Non_Reanimated()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Reanimated);
    }

    Int_t Members_t::Count_Followers()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Follower);
    }

    Int_t Members_t::Count_Non_Followers()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Follower);
    }

    Int_t Members_t::Count_Sneaks()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Sneak);
    }

    Int_t Members_t::Count_Non_Sneaks()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Sneak);
    }

    Int_t Members_t::Count_Saddlers()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Saddler);
    }

    Int_t Members_t::Count_Non_Saddlers()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Saddler);
    }

    Int_t Members_t::Count_Retreaters()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Is_Retreater);
    }

    Int_t Members_t::Count_Non_Retreaters()
    {
        return Count_If<Member_t>(Aliases(), &Member_t::Isnt_Retreater);
    }

    Int_t Members_t::Count_Base(Actor_t* actor_with_base)
    {
        return Aliases_t::Count_Base(Aliases(), actor_with_base);
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
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Filled, MAX);
    }

    Vector_t<Member_t*> Members_t::Unfilled()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Unfilled, HALF);
    }

    Vector_t<Member_t*> Members_t::Loaded()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Loaded, HALF);
    }

    Vector_t<Member_t*> Members_t::Unloaded()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Unloaded, HALF);
    }

    Vector_t<Member_t*> Members_t::Settlers()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Filled, &Member_t::Is_Settler, HALF);
    }

    Vector_t<Member_t*> Members_t::Non_Settlers()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Filled, &Member_t::Isnt_Settler, HALF);
    }

    Vector_t<Member_t*> Members_t::Displayed()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Display, Modules::Vars_t::Self()->Member_Display_Limit());
    }

    Vector_t<Member_t*> Members_t::Undisplayed()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Isnt_Display, HALF);
    }

    Vector_t<Member_t*> Members_t::Sort(Vector_t<Member_t*> members)
    {
        return Aliases_t::Sort<Member_t>(members, Modules::Vars_t::Self()->Member_Sort_Algorithm());
    }

    Vector_t<Member_t*> Members_t::Sort_Filled(Int_t begin, Int_t end)
    {
        return Slice(Sort(Filled()), begin, end);
    }

    Vector_t<Member_t*> Members_t::Sort_Settlers(Int_t begin, Int_t end)
    {
        return Slice(Sort(Settlers()), begin, end);
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

    void Members_t::Enforce_Loaded(Bool_t do_resurrect)
    {
        Vector_t<Member_t*> loaded = Loaded();
        if (do_resurrect) {
            for (size_t idx = 0, count = loaded.size(); idx < count; idx += 1) {
                Member_t* member = loaded.at(idx);
                if (member->Is_Dead() && member->Is_Follower()) {
                    member->Resurrect();
                } else {
                    member->Enforce();
                }
            }
        } else {
            for (size_t idx = 0, count = loaded.size(); idx < count; idx += 1) {
                Member_t* member = loaded.at(idx);
                if (member->Is_Alive()) {
                    member->Enforce();
                }
            }
        }
    }

    Vector_t<Member_t*> Members_t::Filter(Vector_t<String_t>* strings, Vector_t<Int_t>* ints, Int_t flags_1, Int_t flags_2)
    {
        return Sort(Aliases_t::Filter(Aliases(), strings, ints, flags_1, flags_2));
    }

    Vector_t<Member_t*> Members_t::Current_Filter()
    {
        MCM::Filter_t* filter = MCM::Filter_t::Self();
        Vector_t<String_t> strings = filter->Strings();
        Vector_t<Int_t> ints = filter->Ints();
        Int_t flags_1 = filter->Flags_1();
        Int_t flags_2 = filter->Flags_2();
        return Filter(&strings, &ints, flags_1, flags_2);
    }

    Int_t Members_t::Display_Start()
    {
        if (Hasnt_Display()) {
            Vector_t<Member_t*> filter = Current_Filter();
            Int_t filter_count = filter.size();
            if (filter_count > 0) {
                Has_Display_Variable()->Bool(true);
                Display_Idx_Variable()->Int(0);

                Reference_t* marker = Object_Ref::Create_Marker_At(*g_thePlayer);
                NPCP_ASSERT(marker);
                Display_Marker_Variable()->Pack(marker);

                Int_t display_count = Modules::Vars_t::Self()->Member_Display_Limit();
                Int_t slice_count = filter_count < display_count ? filter_count : display_count;
                Display(filter, 0, slice_count, marker);

                return CODES::SUCCESS;
            } else {
                return CODES::MEMBERS;
            }
        } else {
            return CODES::DISPLAY;
        }
    }

    Int_t Members_t::Display_Stop()
    {
        if (Has_Display()) {
            Has_Display_Variable()->Bool(false);
            Display_Idx_Variable()->Int(0);

            Reference_t* display_marker = Display_Marker_Variable()->Reference();
            Display_Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(display_marker);

            Undisplay();

            return CODES::SUCCESS;
        } else {
            return CODES::DISPLAY;
        }
    }
    
    Int_t Members_t::Display_Next()
    {
        if (Has_Display()) {
            Vector_t<Member_t*> filter = Current_Filter();
            Int_t filter_count = filter.size();
            if (filter_count > 0) {
                Int_t display_count = Modules::Vars_t::Self()->Member_Display_Limit();
                Int_t slice_count = filter_count < display_count ? filter_count : display_count;
                Int_t idx = Display_Idx_Variable()->Int();
                if (idx < 0 || idx >= filter_count) {
                    idx = 0;
                } else {
                    idx += slice_count;
                }
                if (idx >= filter_count) {
                    idx -= filter_count;
                }
                Display_Idx_Variable()->Int(idx);

                Display(filter, idx, slice_count, Display_Marker());

                return CODES::SUCCESS;
            } else {
                Display_Stop();
                return CODES::MEMBERS;
            }
        } else {
            return CODES::DISPLAY;
        }
    }

    Int_t Members_t::Display_Previous()
    {
        if (Has_Display()) {
            Vector_t<Member_t*> filter = Current_Filter();
            Int_t filter_count = filter.size();
            if (filter_count > 0) {
                Int_t display_count = Modules::Vars_t::Self()->Member_Display_Limit();
                Int_t slice_count = filter_count < display_count ? filter_count : display_count;
                Int_t idx = Display_Idx_Variable()->Int();
                if (idx < 0 || idx >= filter_count) {
                    idx = filter_count - 1; // we could make this zero also
                } else {
                    idx -= slice_count;
                }
                if (idx < 0) {
                    idx += filter_count;
                }
                Display_Idx_Variable()->Int(idx);

                Display(filter, idx, slice_count, Display_Marker());

                return CODES::SUCCESS;
            } else {
                Display_Stop();
                return CODES::MEMBERS;
            }
        } else {
            return CODES::DISPLAY;
        }
    }

    void Members_t::Display(Vector_t<Member_t*> filter,
                            Int_t begin,
                            Int_t count,
                            Reference_t* origin,
                            float radius,
                            float degree,
                            float interval)
    {
        if (Has_Display()) {
            Undisplay();

            Int_t filter_count = filter.size();
            NPCP_ASSERT(filter_count > 0);
            NPCP_ASSERT(begin > -1 && begin < filter_count);
            NPCP_ASSERT(count > 0 && count <= filter_count);
            NPCP_ASSERT(origin != nullptr);

            Vector_t<Member_t*> displays;
            displays.reserve(count);
            size_t iterations = 0;
            for (size_t idx = begin; iterations < count && idx < filter_count; iterations += 1, idx += 1) {
                displays.push_back(filter[idx]);
            }
            for (size_t idx = 0; iterations < count; iterations += 1, idx += 1) {
                displays.push_back(filter[idx]);
            }

            float first_degree = degree;
            if (count % 2 == 0) {
                first_degree += interval / 2;
                first_degree += interval * ((count / 2) - 1);
            } else {
                first_degree += interval * (count / 2);
            }

            for (size_t idx = 0, size = displays.size(); idx < size; idx += 1, first_degree -= interval) {
                displays[idx]->Display(origin, radius, first_degree);
            }
        }
    }

    void Members_t::Undisplay()
    {
        Vector_t<Member_t*> displayed = Displayed();
        for (size_t idx = 0, count = displayed.size(); idx < count; idx += 1) {
            displayed[idx]->Undisplay();
        }
    }

    void Members_t::Add_Original(Actor_t* original, Callback_t<Int_t, Member_t*>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        if (original) {
            if (!Should_Clone(original)) {
                if (Actor2::Isnt_Child(original)) {
                    if (Hasnt_Actor(original)) {
                        if (Count_Filled() < Limit()) {
                            if (Actor2::Is_Alive(original) || Actor2::Try_Resurrect(original)) {
                                NPCS_t::Self()->Add_Original(original);
                                Member_t* member = From_Unfilled();
                                NPCP_ASSERT(member);
                                member->Fill(original, false, *user_callback);
                            } else {
                                (*user_callback)->operator()(CODES::DEAD, nullptr);
                                delete (*user_callback);
                            }
                        } else {
                            (*user_callback)->operator()(CODES::MEMBERS, nullptr);
                            delete (*user_callback);
                        }
                    } else {
                        (*user_callback)->operator()(CODES::MEMBER, nullptr);
                        delete (*user_callback);
                    }
                } else {
                    (*user_callback)->operator()(CODES::CHILD, nullptr);
                    delete (*user_callback);
                }
            } else {
                return Add_Clone(original, user_callback);
            }
        } else {
            (*user_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*user_callback);
        }
    }

    void Members_t::Remove_Original(Actor_t* original, Callback_t<Int_t, Actor_t*>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<Int_t, Actor_t*>;

        if (original) {
            Member_t* member = From_Actor(original);
            if (member) {
                if (member->Is_Original()) {
                    struct Unfill_Callback : public Callback_t<Int_t, Actor_t*> {
                        Members_t* members;
                        UCallback_t* user_callback;
                        Unfill_Callback(Members_t* members, UCallback_t* user_callback) :
                            members(members), user_callback(user_callback)
                        {
                        }
                        void operator()(Int_t code, Actor_t* original)
                        {
                            NPCS_t::Self()->Remove_Original(original);
                            user_callback->operator()(code, original);
                            delete user_callback;
                        }
                    };
                    Callback_t<Int_t, Actor_t*>* unfill_callback =
                        new Unfill_Callback(this, *user_callback);
                    member->Unfill(unfill_callback);
                } else {
                    return Remove_Clone(original, false, user_callback);
                }
            } else {
                (*user_callback)->operator()(CODES::MEMBER, original);
                delete (*user_callback);
            }
        } else {
            (*user_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*user_callback);
        }
    }

    void Members_t::Add_Clone(Actor_t* original, Callback_t<Int_t, Member_t*>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        if (original) {
            if (Actor2::Isnt_Child(original)) {
                if (Count_Filled() < Limit()) {
                    Actor_t* clone = NPCS_t::Self()->Add_Clone(original);
                    Member_t* member = From_Unfilled();
                    NPCP_ASSERT(member);
                    member->Fill(clone, true, *user_callback);
                } else {
                    (*user_callback)->operator()(CODES::MEMBERS, nullptr);
                    delete (*user_callback);
                }
            } else {
                (*user_callback)->operator()(CODES::CHILD, nullptr);
                delete (*user_callback);
            }
        } else {
            (*user_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*user_callback);
        }
    }

    void Members_t::Remove_Clone(Actor_t* clone, Bool_t do_delete_clone, Callback_t<Int_t, Actor_t*>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<Int_t, Actor_t*>;

        if (clone) {
            Member_t* member = From_Actor(clone);
            if (member) {
                if (member->Is_Clone()) {
                    struct Unfill_Callback : public Callback_t<Int_t, Actor_t*> {
                        Members_t* members;
                        Bool_t do_delete_clone;
                        UCallback_t* user_callback;
                        Unfill_Callback(Members_t* members, Bool_t do_delete_clone, UCallback_t* user_callback) :
                            members(members), do_delete_clone(do_delete_clone), user_callback(user_callback)
                        {
                        }
                        void operator()(Int_t code, Actor_t* clone)
                        {
                            if (do_delete_clone || members->Should_Unclone(clone)) {
                                NPCS_t::Self()->Remove_Clone(clone, true);
                                user_callback->operator()(code, nullptr);
                                delete user_callback;
                            } else {
                                NPCS_t::Self()->Remove_Clone(clone, false);
                                user_callback->operator()(code, clone);
                                delete user_callback;
                            }
                        }
                    };
                    Callback_t<Int_t, Actor_t*>* unfill_callback =
                        new Unfill_Callback(this, do_delete_clone, *user_callback);
                    member->Unfill(unfill_callback);
                } else {
                    (*user_callback)->operator()(CODES::CLONE, clone);
                    delete (*user_callback);
                }
            } else {
                (*user_callback)->operator()(CODES::MEMBER, clone);
                delete (*user_callback);
            }
        } else {
            (*user_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*user_callback);
        }
    }

    void Members_t::On_Load_Mod()
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        Vector_t<Member_t*> filled = Filled();
        Int_t filled_count = filled.size();
        if (vars->Member_Limit() < filled_count) {
            vars->Member_Limit(filled_count);
        }

        for (size_t idx = 0, end = filled.size(); idx < end; idx += 1) {
            Member_t* member = filled[idx];
            if (member && member->Is_Settler()) {
                Settler_t* settler = static_cast<Settler_t*>(member);
                settler->Enforce(settler->Actor(), true);
            }
        }
    }

    void Members_t::u_0_9_3()
    {
        NPCS_t* npcs = NPCS_t::Self();

        Vector_t<Member_t*> filled = Filled();
        for (size_t idx = 0, count = filled.size(); idx < count; idx += 1) {
            Member_t* member = filled.at(idx);
            Actor_t* actor = member->Actor();

            { // recache factions
                Variable_t* previous_factions_variable = member->Variable("p_prev_factions");
                NPCP_ASSERT(previous_factions_variable);
                Array_t* previous_factions = previous_factions_variable->Array();
                if (previous_factions) {
                    Faction_t* potentional_follower_faction = Consts::Potential_Follower_Faction();
                    Faction_t* wi_no_body_cleanup_faction = Consts::WI_No_Body_Cleanup_Faction();
                    for (size_t idx = 0, count = previous_factions->count; idx < count; idx += 1) {
                        Faction_t* faction = previous_factions->Point(idx)->Faction();
                        if (faction == potentional_follower_faction) {
                            member->Previous_Potential_Follower_Faction_Variable()->Bool(true);
                        }
                        if (faction == wi_no_body_cleanup_faction) {
                            member->Previous_No_Body_Cleanup_Faction_Variable()->Bool(true);
                        }
                    }
                }
            }

            { // make sure outfit2 have their correct type.
                Outfit2_t* member_outfit2 = static_cast<Outfit2_t*>(member->Member_Outfit2_Variable()->Reference());
                if (member_outfit2) {
                    member_outfit2->Type_Variable()->Int(CODES::OUTFIT2::MEMBER);
                }
                Outfit2_t* immobile_outfit2 = static_cast<Outfit2_t*>(member->Immobile_Outfit2_Variable()->Reference());
                if (immobile_outfit2) {
                    immobile_outfit2->Type_Variable()->Int(CODES::OUTFIT2::IMMOBILE);
                }
                Outfit2_t* settler_outfit2 = static_cast<Outfit2_t*>(member->Settler_Outfit2_Variable()->Reference());
                if (settler_outfit2) {
                    settler_outfit2->Type_Variable()->Int(CODES::OUTFIT2::SETTLER);
                }
                Outfit2_t* thrall_outfit2 = static_cast<Outfit2_t*>(member->Thrall_Outfit2_Variable()->Reference());
                if (thrall_outfit2) {
                    thrall_outfit2->Type_Variable()->Int(CODES::OUTFIT2::THRALL);
                }
                Outfit2_t* follower_outfit2 = static_cast<Outfit2_t*>(member->Follower_Outfit2_Variable()->Reference());
                if (follower_outfit2) {
                    follower_outfit2->Type_Variable()->Int(CODES::OUTFIT2::FOLLOWER);
                }
                Outfit2_t* vanilla_outfit2 = static_cast<Outfit2_t*>(member->Vanilla_Outfit2_Variable()->Reference());
                if (vanilla_outfit2) {
                    vanilla_outfit2->Type_Variable()->Int(CODES::OUTFIT2::VANILLA);
                }
                Outfit2_t* default_outfit2 = static_cast<Outfit2_t*>(member->Default_Outfit2_Variable()->Reference());
                if (default_outfit2) {
                    default_outfit2->Type_Variable()->Int(CODES::OUTFIT2::DEFAULT);
                }
            }

            // make sure the default outfit is there.
            npcs->Add_Base_If_Needed(actor, actor);
            member->Default_Outfit_Variable()->Pack(npcs->Default_Outfit(actor));

            // new name cache
            member->Name_Variable()->String(Actor2::Get_Name(actor));
        }
    }

    void Members_t::u_0_9_6()
    {
        Vector_t<Member_t*> filled = Filled();
        for (size_t idx = 0, count = filled.size(); idx < count; idx += 1) {
            Member_t* member = filled[idx];
            if (member) {
                Reference_t* pack = member->Pack();
                if (pack) {
                    Object_Ref::Validate_XContainer(pack);
                }

                Outfit2_t* member_outfit2 = static_cast<Outfit2_t*>(member->Member_Outfit2_Variable()->Reference());
                if (member_outfit2) {
                    Object_Ref::Validate_XContainer(member_outfit2);
                }
                Outfit2_t* immobile_outfit2 = static_cast<Outfit2_t*>(member->Immobile_Outfit2_Variable()->Reference());
                if (immobile_outfit2) {
                    Object_Ref::Validate_XContainer(immobile_outfit2);
                }
                Outfit2_t* settler_outfit2 = static_cast<Outfit2_t*>(member->Settler_Outfit2_Variable()->Reference());
                if (settler_outfit2) {
                    Object_Ref::Validate_XContainer(settler_outfit2);
                }
                Outfit2_t* thrall_outfit2 = static_cast<Outfit2_t*>(member->Thrall_Outfit2_Variable()->Reference());
                if (thrall_outfit2) {
                    Object_Ref::Validate_XContainer(thrall_outfit2);
                }
                Outfit2_t* follower_outfit2 = static_cast<Outfit2_t*>(member->Follower_Outfit2_Variable()->Reference());
                if (follower_outfit2) {
                    Object_Ref::Validate_XContainer(follower_outfit2);
                }
                Outfit2_t* vanilla_outfit2 = static_cast<Outfit2_t*>(member->Vanilla_Outfit2_Variable()->Reference());
                if (vanilla_outfit2) {
                    Object_Ref::Validate_XContainer(vanilla_outfit2);
                }
                Outfit2_t* default_outfit2 = static_cast<Outfit2_t*>(member->Default_Outfit2_Variable()->Reference());
                if (default_outfit2) {
                    Object_Ref::Validate_XContainer(default_outfit2);
                }
            }
        }

        Object_Ref::Validate_XContainer(Consts::Input_Category());
        Object_Ref::Validate_XContainer(Consts::Swords_Category());
        Object_Ref::Validate_XContainer(Consts::Greatswords_Category());
        Object_Ref::Validate_XContainer(Consts::Waraxes_Category());
        Object_Ref::Validate_XContainer(Consts::Battleaxes_Category());
        Object_Ref::Validate_XContainer(Consts::Maces_Category());
        Object_Ref::Validate_XContainer(Consts::Warhammers_Category());
        Object_Ref::Validate_XContainer(Consts::Daggers_Category());
        Object_Ref::Validate_XContainer(Consts::Staves_Category());
        Object_Ref::Validate_XContainer(Consts::Bows_Category());
        Object_Ref::Validate_XContainer(Consts::Ammo_Category());
        Object_Ref::Validate_XContainer(Consts::Weapons_Category());
        Object_Ref::Validate_XContainer(Consts::Light_Armor_Category());
        Object_Ref::Validate_XContainer(Consts::Heavy_Armor_Category());
        Object_Ref::Validate_XContainer(Consts::Shields_Category());
        Object_Ref::Validate_XContainer(Consts::Jewelry_Category());
        Object_Ref::Validate_XContainer(Consts::Clothes_Category());
        Object_Ref::Validate_XContainer(Consts::Potions_Category());
        Object_Ref::Validate_XContainer(Consts::Poisons_Category());
        Object_Ref::Validate_XContainer(Consts::Ingredients_Category());
        Object_Ref::Validate_XContainer(Consts::Food_Category());
        Object_Ref::Validate_XContainer(Consts::Soulgems_Category());
        Object_Ref::Validate_XContainer(Consts::Scrolls_Category());
        Object_Ref::Validate_XContainer(Consts::Metals_Category());
        Object_Ref::Validate_XContainer(Consts::Leather_Category());
        Object_Ref::Validate_XContainer(Consts::Gems_Category());
        Object_Ref::Validate_XContainer(Consts::Clutter_Category());
        Object_Ref::Validate_XContainer(Consts::Keys_Category());
        Object_Ref::Validate_XContainer(Consts::Misc_Category());
        Object_Ref::Validate_XContainer(Consts::Spell_Tomes_Category());
        Object_Ref::Validate_XContainer(Consts::Recipes_Category());
        Object_Ref::Validate_XContainer(Consts::A_Books_Category());
        Object_Ref::Validate_XContainer(Consts::B_Books_Category());
        Object_Ref::Validate_XContainer(Consts::C_Books_Category());
        Object_Ref::Validate_XContainer(Consts::D_Books_Category());
        Object_Ref::Validate_XContainer(Consts::E_Books_Category());
        Object_Ref::Validate_XContainer(Consts::F_Books_Category());
        Object_Ref::Validate_XContainer(Consts::G_Books_Category());
        Object_Ref::Validate_XContainer(Consts::H_Books_Category());
        Object_Ref::Validate_XContainer(Consts::I_Books_Category());
        Object_Ref::Validate_XContainer(Consts::J_Books_Category());
        Object_Ref::Validate_XContainer(Consts::K_Books_Category());
        Object_Ref::Validate_XContainer(Consts::L_Books_Category());
        Object_Ref::Validate_XContainer(Consts::M_Books_Category());
        Object_Ref::Validate_XContainer(Consts::N_Books_Category());
        Object_Ref::Validate_XContainer(Consts::O_Books_Category());
        Object_Ref::Validate_XContainer(Consts::P_Books_Category());
        Object_Ref::Validate_XContainer(Consts::Q_Books_Category());
        Object_Ref::Validate_XContainer(Consts::R_Books_Category());
        Object_Ref::Validate_XContainer(Consts::S_Books_Category());
        Object_Ref::Validate_XContainer(Consts::T_Books_Category());
        Object_Ref::Validate_XContainer(Consts::U_Books_Category());
        Object_Ref::Validate_XContainer(Consts::V_Books_Category());
        Object_Ref::Validate_XContainer(Consts::W_Books_Category());
        Object_Ref::Validate_XContainer(Consts::X_Books_Category());
        Object_Ref::Validate_XContainer(Consts::Y_Books_Category());
        Object_Ref::Validate_XContainer(Consts::Z_Books_Category());
        Object_Ref::Validate_XContainer(Consts::Books_Category());
    }

    void Members_t::u_0_9_8()
    {
        Vector_t<Form_t*> unplayables;
        unplayables.reserve(16);
        unplayables.push_back(Game::Skyrim_Form(0x10E2DC));
        unplayables.push_back(Game::Skyrim_Form(0x10E2CE));
        unplayables.push_back(Game::Skyrim_Form(0x0CF8B3));
        unplayables.push_back(Game::Skyrim_Form(0x0CF8B0));
        unplayables.push_back(Game::Skyrim_Form(0x0CF8B1));
        unplayables.push_back(Game::Skyrim_Form(0x0CF8B2));
        unplayables.push_back(Game::Skyrim_Form(0x088952));
        unplayables.push_back(Game::Skyrim_Form(0x088954));
        unplayables.push_back(Game::Skyrim_Form(0x036A44));
        unplayables.push_back(Game::Skyrim_Form(0x036A46));
        unplayables.push_back(Game::Skyrim_Form(0x036A45));

        auto Remove_Bad_Unplayables = [&unplayables](Outfit2_t* outfit2)
        {
            for (size_t idx = 0, count = unplayables.size(); idx < count; idx += 1) {
                XEntry_t* xentry = Object_Ref::Get_XEntry(outfit2, unplayables[idx], false);
                if (xentry) {
                    Object_Ref::Remove_XEntry(outfit2, xentry);
                    XEntry_t::Destroy(xentry);
                }
            }
        };

        Vector_t<Member_t*> filled = Filled();
        for (size_t idx = 0, count = filled.size(); idx < count; idx += 1) {
            Member_t* member = filled[idx];
            if (member) {
                Outfit2_t* immobile_outfit2 = static_cast<Outfit2_t*>(member->Immobile_Outfit2_Variable()->Reference());
                if (immobile_outfit2) {
                    Remove_Bad_Unplayables(immobile_outfit2);
                }
                Outfit2_t* settler_outfit2 = static_cast<Outfit2_t*>(member->Settler_Outfit2_Variable()->Reference());
                if (settler_outfit2) {
                    Remove_Bad_Unplayables(settler_outfit2);
                }
                Outfit2_t* thrall_outfit2 = static_cast<Outfit2_t*>(member->Thrall_Outfit2_Variable()->Reference());
                if (thrall_outfit2) {
                    Remove_Bad_Unplayables(thrall_outfit2);
                }
                Outfit2_t* follower_outfit2 = static_cast<Outfit2_t*>(member->Follower_Outfit2_Variable()->Reference());
                if (follower_outfit2) {
                    Remove_Bad_Unplayables(follower_outfit2);
                }
            }
        }
    }

    void Members_t::u_0_9_9()
    {
        Vector_t<Member_t*> filled = Filled();
        for (size_t idx = 0, count = filled.size(); idx < count; idx += 1) {
            Member_t* member = filled[idx];
            if (member) {
                Actor_t* actor = member->Actor();
                if (member->Previous_Potential_Follower_Faction_Variable()->Bool()) {
                    Actor2::Add_Faction(actor, Consts::Potential_Follower_Faction(), 0);
                }

                Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
                if (member->Is_Immobile()) {
                    value_owner->Set_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER, 1.0f);
                } else {
                    value_owner->Set_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER, 0.0f);
                }

                Outfit2_t* member_outfit2 = static_cast<Outfit2_t*>(member->Member_Outfit2_Variable()->Reference());
                if (member_outfit2) {
                    member_outfit2->Member_Variable()->Pack(member);
                }
                Outfit2_t* immobile_outfit2 = static_cast<Outfit2_t*>(member->Immobile_Outfit2_Variable()->Reference());
                if (immobile_outfit2) {
                    immobile_outfit2->Member_Variable()->Pack(member);
                }
                Outfit2_t* settler_outfit2 = static_cast<Outfit2_t*>(member->Settler_Outfit2_Variable()->Reference());
                if (settler_outfit2) {
                    settler_outfit2->Member_Variable()->Pack(member);
                }
                Outfit2_t* thrall_outfit2 = static_cast<Outfit2_t*>(member->Thrall_Outfit2_Variable()->Reference());
                if (thrall_outfit2) {
                    thrall_outfit2->Member_Variable()->Pack(member);
                }
                Outfit2_t* follower_outfit2 = static_cast<Outfit2_t*>(member->Follower_Outfit2_Variable()->Reference());
                if (follower_outfit2) {
                    follower_outfit2->Member_Variable()->Pack(member);
                }
                Outfit2_t* vanilla_outfit2 = static_cast<Outfit2_t*>(member->Vanilla_Outfit2_Variable()->Reference());
                if (vanilla_outfit2) {
                    vanilla_outfit2->Member_Variable()->Pack(member);
                }
                Outfit2_t* default_outfit2 = static_cast<Outfit2_t*>(member->Default_Outfit2_Variable()->Reference());
                if (default_outfit2) {
                    default_outfit2->Member_Variable()->Pack(member);
                }
            }
        }
    }

    void Members_t::u_0_9_12()
    {
        Actor_Base_t* player_actor_base = static_cast<Actor_Base_t*>
            (Consts::Player_Actor()->baseForm);

        Vector_t<Member_t*> filled = Filled();
        for (size_t idx = 0, count = filled.size(); idx < count; idx += 1) {
            Member_t* member = filled[idx];
            if (member) {
                Actor_t* actor = member->Actor();
                Actor_Base_t* actor_base = Actor2::Dynamic_Base(actor);
                Object_Ref::Inventory_t actor_inventory(actor);
                for (size_t idx = 0, end = actor_inventory.entries.size(); idx < end; idx += 1) {
                    Object_Ref::Entry_t& entry = actor_inventory.entries[idx];
                    if (Actor2::Outfit_Inventory_t::Can_Evaluate_Form(entry.form)) {
                        if (entry.xentry && entry.xentry->xlists) {
                            for (XLists_t::Iterator it = entry.xentry->xlists->Begin(); !it.End(); ++it) {
                                XList_t* xlist = it.Get();
                                if (xlist) {
                                    ExtraOwnership* xownership = static_cast<ExtraOwnership*>
                                        (xlist->GetByType(kExtraData_Ownership));
                                    if (xownership && xownership->owner == player_actor_base) {
                                        xownership->owner = actor_base;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void Members_t::u_0_9_15()
    {
        Vector_t<Member_t*> filled = Filled();
        for (size_t idx = 0, count = filled.size(); idx < count; idx += 1) {
            Member_t* member = filled[idx];
            Settler_t* settler = static_cast<Settler_t*>(member);
            if (settler) {
                Variable_t* is_settler_variable = member->Variable("p_is_settler");
                NPCP_ASSERT(is_settler_variable);
                if (is_settler_variable->Bool()) {
                    Sandboxer_t* sandboxer = static_cast<Sandboxer_t*>(settler);
                    sandboxer->Flag(Sandboxer_t::Flag_e::IS_ENABLED);
                    sandboxer->Default();
                    sandboxer->Enforce(sandboxer->Actor(), true);
                }
            }
        }
    }

    void Members_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Members_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }
    
}}}
