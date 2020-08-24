/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "cell.h"
#include "codes.h"
#include "consts.h"
#include "game.h"
#include "object_ref.h"
#include "party.h"
#include "party.inl"
#include "quest.h"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "mcm/mcm_filter.h"

namespace doticu_npcp { namespace Party {

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

    Int_t Members_t::Add_Original(Actor_t* original)
    {
        if (original) {
            if (!Should_Clone(original)) {
                if (Actor2::Isnt_Child(original)) {
                    if (Hasnt_Actor(original)) {
                        if (Count_Filled() < Limit()) {
                            if (Actor2::Is_Alive(original) || Actor2::Try_Resurrect(original)) {
                                NPCS_t::Self()->Add_Original(original);
                                Member_t* member = From_Unfilled();
                                NPCP_ASSERT(member);
                                member->Fill(original, false);
                                return CODES::SUCCESS;
                            } else {
                                return CODES::DEAD;
                            }
                        } else {
                            return CODES::MEMBERS;
                        }
                    } else {
                        return CODES::MEMBER;
                    }
                } else {
                    return CODES::CHILD;
                }
            } else {
                return Add_Clone(original);
            }
        } else {
            return CODES::ACTOR;
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

    Int_t Members_t::Add_Clone(Actor_t* original)
    {
        if (original) {
            if (Actor2::Isnt_Child(original)) {
                if (Count_Filled() < Limit()) {
                    Actor_t* clone = NPCS_t::Self()->Add_Clone(original);
                    Member_t* member = From_Unfilled();
                    NPCP_ASSERT(member);
                    member->Fill(clone, true);
                    return CODES::SUCCESS;
                } else {
                    return CODES::MEMBERS;
                }
            } else {
                return CODES::CHILD;
            }
        } else {
            return CODES::ACTOR;
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
    
}}

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    Int_t Add_Original(Members_t* self, Actor_t* original) FORWARD_INT(Members_t::Add_Original(original));
    Int_t Remove_Original(Members_t* self, Actor_t* original) FORWARD_INT(Members_t::Remove_Original(original));
    Int_t Add_Clone(Members_t* self, Actor_t* original) FORWARD_INT(Members_t::Add_Clone(original));
    Int_t Remove_Clone(Members_t* self, Actor_t* clone, Bool_t do_delete_clone) FORWARD_INT(Members_t::Remove_Clone(clone, do_delete_clone));

    Member_t* From_Actor(Members_t* self, Actor_t* actor) FORWARD_POINTER(From_Actor(actor));

    Bool_t Has_Space(Members_t* self) FORWARD_BOOL(Has_Space());
    Bool_t Hasnt_Space(Members_t* self) FORWARD_BOOL(Hasnt_Space());
    Bool_t Has_Actor(Members_t* self, Actor_t* actor) FORWARD_BOOL(Has_Actor(actor));
    Bool_t Hasnt_Actor(Members_t* self, Actor_t* actor) FORWARD_BOOL(Hasnt_Actor(actor));
    Bool_t Has_Base(Members_t* self, Actor_t* actor_with_base) FORWARD_BOOL(Has_Base(actor_with_base));
    Bool_t Hasnt_Base(Members_t* self, Actor_t* actor_with_base) FORWARD_BOOL(Hasnt_Base(actor_with_base));
    Bool_t Has_Head(Members_t* self, Actor_t* actor) FORWARD_BOOL(Has_Head(actor));
    Bool_t Hasnt_Head(Members_t* self, Actor_t* actor) FORWARD_BOOL(Hasnt_Head(actor));
    Bool_t Has_Display(Members_t* self) FORWARD_BOOL(Members_t::Has_Display());
    Bool_t Hasnt_Display(Members_t* self) FORWARD_BOOL(Members_t::Hasnt_Display());

    Int_t Max(Members_t* self) FORWARD_INT(Max());
    Int_t Limit(Members_t* self) FORWARD_INT(Limit());
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
    Int_t Count_Base(Members_t* self, Actor_t* actor_with_base) FORWARD_INT(Count_Base(actor_with_base));
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

    void Enforce_Loaded(Members_t* self, Bool_t do_resurrect) FORWARD_VOID(Members_t::Enforce_Loaded(do_resurrect));

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

    Int_t Display_Start(Members_t* self) FORWARD_INT(Members_t::Display_Start());
    Int_t Display_Stop(Members_t* self) FORWARD_INT(Members_t::Display_Stop());
    Int_t Display_Next(Members_t* self) FORWARD_INT(Members_t::Display_Next());
    Int_t Display_Previous(Members_t* self) FORWARD_INT(Members_t::Display_Previous());

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Members_t::Class_Name(), Members_t,        \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Add_Original", 1, Int_t, Add_Original, Actor_t*);
        ADD_METHOD("Remove_Original", 1, Int_t, Remove_Original, Actor_t*);
        ADD_METHOD("Add_Clone", 1, Int_t, Add_Clone, Actor_t*);
        ADD_METHOD("Remove_Clone", 2, Int_t, Remove_Clone, Actor_t*, Bool_t);

        ADD_METHOD("p_From_Actor", 1, Member_t*, From_Actor, Actor_t*);

        ADD_METHOD("Has_Space", 0, Bool_t, Has_Space);
        ADD_METHOD("Hasnt_Space", 0, Bool_t, Hasnt_Space);
        ADD_METHOD("Has_Actor", 1, Bool_t, Has_Actor, Actor_t*);
        ADD_METHOD("Hasnt_Actor", 1, Bool_t, Hasnt_Actor, Actor_t*);
        ADD_METHOD("Has_Base", 1, Bool_t, Has_Base, Actor_t*);
        ADD_METHOD("Hasnt_Base", 1, Bool_t, Hasnt_Base, Actor_t*);
        ADD_METHOD("Has_Head", 1, Bool_t, Has_Head, Actor_t*);
        ADD_METHOD("Hasnt_Head", 1, Bool_t, Hasnt_Head, Actor_t*);
        ADD_METHOD("Has_Display", 0, Bool_t, Has_Display);
        ADD_METHOD("Hasnt_Display", 0, Bool_t, Hasnt_Display);

        ADD_METHOD("Max", 0, Int_t, Max);
        ADD_METHOD("Limit", 0, Int_t, Limit);
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
        ADD_METHOD("Count_Base", 1, Int_t, Count_Base, Actor_t*);
        ADD_METHOD("Count_Heads", 1, Int_t, Count_Heads, Actor_t*);

        ADD_METHOD("All", 0, Vector_t<Member_t*>, All);
        ADD_METHOD("Filled", 0, Vector_t<Member_t*>, Filled);

        ADD_METHOD("Sort_Filled", 2, Vector_t<Member_t*>, Sort_Filled, Int_t, Int_t);

        ADD_METHOD("Slice", 3, Vector_t<Member_t*>, Slice, VMArray<Member_t*>, Int_t, Int_t);

        ADD_METHOD("Race_Names", 0, Vector_t<String_t>, Race_Names);

        ADD_METHOD("Enforce_Loaded", 1, void, Enforce_Loaded, Bool_t);

        ADD_METHOD("Filter_Strings", 3, Vector_t<String_t>, Filter_Strings, String_t, String_t, String_t);
        ADD_METHOD("Filter_Ints", 4, Vector_t<Int_t>, Filter_Ints, Int_t, Int_t, Int_t, Int_t);
        ADD_METHOD("Add_Filter_Flag_1", 2, Int_t, Add_Filter_Flag_1, Int_t, String_t);
        ADD_METHOD("Add_Filter_Flag_2", 2, Int_t, Add_Filter_Flag_2, Int_t, String_t);
        ADD_METHOD("Filter", 4, Vector_t<Member_t*>, Filter, VMArray<String_t>, VMArray<Int_t>, Int_t, Int_t);

        ADD_METHOD("Display_Start", 0, Int_t, Display_Start);
        ADD_METHOD("Display_Stop", 0, Int_t, Display_Stop);
        ADD_METHOD("Display_Next", 0, Int_t, Display_Next);
        ADD_METHOD("Display_Previous", 0, Int_t, Display_Previous);

        #undef ADD_METHOD

        return true;
    }

}}}}
