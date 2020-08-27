/*
    Copyright � 2020 r-neal-kelly, aka doticu
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
        return
            (Actor2::Is_Unique(actor) && Vars::Do_Force_Clone_Unique()) ||
            (Actor2::Is_Generic(actor) && Vars::Do_Force_Clone_Generic());
    }

    Bool_t Members_t::Should_Unclone(Actor_t* actor)
    {
        return
            (Actor2::Is_Unique(actor) && Vars::Do_Force_Unclone_Unique()) ||
            (Actor2::Is_Generic(actor) && Vars::Do_Force_Unclone_Generic());
    }

    Int_t Members_t::Max()
    {
        return MAX;
    }

    Int_t Members_t::Limit()
    {
        return Vars::Member_Limit();
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

    Vector_t<Member_t*> Members_t::Displayed()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Is_Display, Vars::Display_Count());
    }

    Vector_t<Member_t*> Members_t::Undisplayed()
    {
        return Copy_If<Member_t>(Aliases(), &Member_t::Isnt_Display, HALF);
    }

    Vector_t<Member_t*> Members_t::Sort(Vector_t<Member_t*> members)
    {
        return Aliases_t::Sort<Member_t>(members, Vars::Members_Sort_Algorithm());
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

                Int_t display_count = Vars::Display_Count();
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
                Int_t display_count = Vars::Display_Count();
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
                Int_t display_count = Vars::Display_Count();
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

    void Members_t::Add_Original(Actor_t* original, Add_Callback_i** add_callback)
    {
        NPCP_ASSERT(add_callback);
        if (original) {
            if (!Should_Clone(original)) {
                if (Actor2::Isnt_Child(original)) {
                    if (Hasnt_Actor(original)) {
                        if (Count_Filled() < Limit()) {
                            if (Actor2::Is_Alive(original) || Actor2::Try_Resurrect(original)) {
                                NPCS_t::Self()->Add_Original(original);
                                Member_t* member = From_Unfilled();
                                NPCP_ASSERT(member);
                                member->Fill(original, false, add_callback);
                            } else {
                                (*add_callback)->operator()(CODES::DEAD, nullptr);
                                delete (*add_callback);
                            }
                        } else {
                            (*add_callback)->operator()(CODES::MEMBERS, nullptr);
                            delete (*add_callback);
                        }
                    } else {
                        (*add_callback)->operator()(CODES::MEMBER, nullptr);
                        delete (*add_callback);
                    }
                } else {
                    (*add_callback)->operator()(CODES::CHILD, nullptr);
                    delete (*add_callback);
                }
            } else {
                return Add_Clone(original, add_callback);
            }
        } else {
            (*add_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*add_callback);
        }
    }

    Int_t Members_t::Remove_Original(Actor_t* original)
    {
        if (original) {
            Member_t* member = From_Actor(original);
            if (member) {
                if (member->Is_Original()) {
                    member->Unfill();
                    NPCS_t::Self()->Remove_Original(original);
                    return CODES::SUCCESS;
                } else {
                    return Remove_Clone(original, false);
                }
            } else {
                return CODES::MEMBER;
            }
        } else {
            return CODES::ACTOR;
        }
    }

    void Members_t::Add_Clone(Actor_t* original, Add_Callback_i** add_callback)
    {
        NPCP_ASSERT(add_callback);
        if (original) {
            if (Actor2::Isnt_Child(original)) {
                if (Count_Filled() < Limit()) {
                    Actor_t* clone = NPCS_t::Self()->Add_Clone(original);
                    Member_t* member = From_Unfilled();
                    NPCP_ASSERT(member);
                    member->Fill(clone, true, add_callback);
                } else {
                    (*add_callback)->operator()(CODES::MEMBERS, nullptr);
                    delete (*add_callback);
                }
            } else {
                (*add_callback)->operator()(CODES::CHILD, nullptr);
                delete (*add_callback);
            }
        } else {
            (*add_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*add_callback);
        }
    }

    Int_t Members_t::Remove_Clone(Actor_t* clone, Bool_t do_delete_clone)
    {
        if (clone) {
            Member_t* member = From_Actor(clone);
            if (member) {
                if (member->Is_Clone()) {
                    member->Unfill();
                    NPCS_t::Self()->Remove_Clone(clone, do_delete_clone || Should_Unclone(clone));
                    return CODES::SUCCESS;
                } else {
                    return CODES::CLONE;
                }
            } else {
                return CODES::MEMBER;
            }
        } else {
            return CODES::ACTOR;
        }
    }

    void Members_t::Delete_Unused_Outfit2s()
    {
        Vector_t<Reference_t*> outfit2s = Cell::References(Consts::Storage_Cell(), Consts::Outfit2_Container());
        for (size_t idx = 0, count = outfit2s.size(); idx < count; idx += 1) {
            Outfit2_t* outfit2 = static_cast<Outfit2_t*>(outfit2s.at(idx));
            if (outfit2 && outfit2->Type() == CODES::OUTFIT2::DELETED) {
                Object_Ref::Delete_Safe(outfit2);
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

    void Members_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Members_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("p_From_Actor", 1, Member_t*, From_Actor, Actor_t*);

        METHOD("Has_Actor", 1, Bool_t, Has_Actor, Actor_t*);
        METHOD("Has_Base", 1, Bool_t, Has_Base, Actor_t*);
        METHOD("Has_Head", 1, Bool_t, Has_Head, Actor_t*);

        METHOD("Max", 0, Int_t, Max);
        METHOD("Count_Filled", 0, Int_t, Count_Filled);
        METHOD("Count_Base", 1, Int_t, Count_Base, Actor_t*);
        METHOD("Count_Heads", 1, Int_t, Count_Heads, Actor_t*);

        METHOD("Sort_Filled", 2, Vector_t<Member_t*>, Sort_Filled, Int_t, Int_t);

        METHOD("Race_Names", 0, Vector_t<String_t>, Race_Names);

        METHOD("Enforce_Loaded", 1, void, Enforce_Loaded, Bool_t);

        #undef METHOD
    }
    
}}}
