/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "game.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "party/party_aliases.inl"
#include "party/party_player.h"
#include "party/party_member.h"
#include "party/party_followers.h"
#include "party/party_follower.h"
#include "party/party_horses.h"
#include "party/party_horse.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

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
            if (follower && follower->Is_In_Combat()) {
                return true;
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

    static Vector_t<Quest_t*> Follower_Like_Quests()
    {
        Quest_t* our_quest = Consts::Followers_Quest();

        Vector_t<Quest_t*> quests;
        quests.reserve(32);
        quests.push_back(Consts::Follower_Dialogue_Quest());

        DataHandler* data_handler = DataHandler::GetSingleton();
        if (data_handler) {
            for (size_t idx = 0, count = data_handler->quests.count; idx < count; idx += 1) {
                Quest_t* quest = *(data_handler->quests.entries + idx);
                if (quest->aliases.count > 0) {
                    if (quest != our_quest) {
                        const char* editor_id = quest->Editor_ID();
                        if (String2::Contains_Caseless(editor_id, "follow")) {
                            if (!Vector::Has(quests, quest)) {
                                quests.push_back(quest);
                            }
                        } else {
                            ModInfo* mod_info = quest->GetFinalSourceFile();
                            while (mod_info) {
                                if (String2::Contains_Caseless(mod_info->name, "follow") ||
                                    String2::Contains(mod_info->name, "EFF")) {
                                    if (!Vector::Has(quests, quest)) {
                                        quests.push_back(quest);
                                    }
                                    mod_info = nullptr;
                                } else {
                                    ModInfo* parent = *reinterpret_cast<ModInfo**>
                                        ((reinterpret_cast<UInt8*>(mod_info) + 0x008));
                                    if (parent != mod_info) {
                                        mod_info = parent;
                                    } else {
                                        mod_info = nullptr;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        /*for (size_t idx = 0, count = quests.size(); idx < count; idx += 1) {
            _MESSAGE(quests[idx]->Editor_ID());
        }*/

        return quests;
    }

    Bool_t Followers_t::Can_Actor_Follow(Actor_t* actor) // check if they have breadcrumbs?
    {
        static Vector_t<Quest_t*> follower_like_quests = Follower_Like_Quests();

        if (actor) {
            if (Actor2::Has_Faction(actor, Consts::Current_Follower_Faction())) {
                XAliases_t* xaliases = static_cast<XAliases_t*>(actor->extraData.GetByType(kExtraData_AliasInstanceArray));
                if (xaliases) {
                    for (size_t idx = 0, count = xaliases->aliases.count; idx < count; idx += 1) {
                        XAliases_t::AliasInfo* info = xaliases->aliases[idx];
                        if (info) {
                            Quest_t* quest = info->quest;
                            if (quest && quest != this) {
                                if (Vector::Has(follower_like_quests, quest)) {
                                    return false;
                                }
                            }
                        }
                    }
                    return true;
                } else {
                    return true;
                }
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    void Followers_t::Add_Follower(Member_t* member, Callback_t<Int_t, Follower_t*>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        if (member) {
            if (member->Isnt_Mannequin()) {
                Actor_t* actor = member->Actor();
                if (Hasnt_Actor(actor)) {
                    if (Can_Actor_Follow(actor)) {
                        if (Count_Filled() < Max()) {
                            Follower_t* follower = From_Unfilled();
                            NPCP_ASSERT(follower);
                            follower->Fill(member, user_callback);
                        } else {
                            user_callback->operator()(CODES::FOLLOWERS, nullptr);
                            delete user_callback;
                        }
                    } else {
                        user_callback->operator()(CODES::CANT, nullptr);
                        delete user_callback;
                    }
                } else {
                    user_callback->operator()(CODES::FOLLOWER, nullptr);
                    delete user_callback;
                }
            } else {
                user_callback->operator()(CODES::MANNEQUIN, nullptr);
                delete user_callback;
            }
        } else {
            user_callback->operator()(CODES::MEMBER, nullptr);
            delete user_callback;
        }
    }

    void Followers_t::Remove_Follower(Member_t* member, Callback_t<Int_t, Member_t*>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        if (member) {
            Follower_t* follower = From_Actor(member->Actor());
            if (follower) {
                follower->Unfill(user_callback);
            } else {
                user_callback->operator()(CODES::FOLLOWER, member);
                delete user_callback;
            }
        } else {
            user_callback->operator()(CODES::MEMBER, nullptr);
            delete user_callback;
        }
    }

    void Followers_t::Relinquish_Follower(Member_t* member, Callback_t<Int_t, Member_t*>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        if (member) {
            Follower_t* follower = From_Actor(member->Actor());
            if (follower) {
                follower->Relinquish(user_callback);
            } else {
                user_callback->operator()(CODES::FOLLOWER, member);
                delete user_callback;
            }
        } else {
            user_callback->operator()(CODES::MEMBER, nullptr);
            delete user_callback;
        }
    }

    Int_t Followers_t::Enforce()
    {
        Vector_t<Follower_t*> filled = Filled();
        size_t filled_count = filled.size();
        if (filled_count > 0) {
            for (size_t idx = 0; idx < filled_count; idx += 1) {
                filled[idx]->Member()->Enforce();
            }
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Resurrect()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> dead = Dead();
            size_t dead_count = dead.size();
            if (dead_count > 0) {
                for (size_t idx = 0; idx < dead_count; idx += 1) {
                    dead[idx]->Resurrect();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Mobilize()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> immobile = Immobile();
            size_t immobile_count = immobile.size();
            if (immobile_count > 0) {
                for (size_t idx = 0; idx < immobile_count; idx += 1) {
                    immobile[idx]->Mobilize();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Immobilize()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> mobile = Mobile();
            size_t mobile_count = mobile.size();
            if (mobile_count > 0) {
                for (size_t idx = 0; idx < mobile_count; idx += 1) {
                    mobile[idx]->Immobilize();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Settle()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> non_settlers = Non_Settlers();
            size_t non_settler_count = non_settlers.size();
            if (non_settler_count > 0) {
                for (size_t idx = 0; idx < non_settler_count; idx += 1) {
                    non_settlers[idx]->Settle();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Resettle()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> settlers = Settlers();
            size_t settler_count = settlers.size();
            if (settler_count > 0) {
                for (size_t idx = 0; idx < settler_count; idx += 1) {
                    settlers[idx]->Resettle();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unsettle()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> settlers = Settlers();
            size_t settler_count = settlers.size();
            if (settler_count > 0) {
                for (size_t idx = 0; idx < settler_count; idx += 1) {
                    settlers[idx]->Unsettle();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Enthrall()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> non_thralls = Non_Thralls();
            size_t non_thrall_count = non_thralls.size();
            if (non_thrall_count > 0) {
                for (size_t idx = 0; idx < non_thrall_count; idx += 1) {
                    non_thralls[idx]->Enthrall();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unthrall()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> thralls = Thralls();
            size_t thrall_count = thralls.size();
            if (thrall_count > 0) {
                for (size_t idx = 0; idx < thrall_count; idx += 1) {
                    thralls[idx]->Unthrall();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Paralyze()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> non_paralyzed = Non_Paralyzed();
            size_t non_paralyzed_count = non_paralyzed.size();
            if (non_paralyzed_count > 0) {
                for (size_t idx = 0; idx < non_paralyzed_count; idx += 1) {
                    non_paralyzed[idx]->Paralyze();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unparalyze()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> paralyzed = Paralyzed();
            size_t paralyzed_count = paralyzed.size();
            if (paralyzed_count > 0) {
                for (size_t idx = 0; idx < paralyzed_count; idx += 1) {
                    paralyzed[idx]->Unparalyze();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Sneak()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> non_sneaks = Non_Sneaks();
            size_t non_sneak_count = non_sneaks.size();
            if (non_sneak_count > 0) {
                for (size_t idx = 0; idx < non_sneak_count; idx += 1) {
                    non_sneaks[idx]->Sneak();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unsneak()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> sneaks = Sneaks();
            size_t sneak_count = sneaks.size();
            if (sneak_count > 0) {
                for (size_t idx = 0; idx < sneak_count; idx += 1) {
                    sneaks[idx]->Unsneak();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Saddle()
    {
        static volatile Int_t active_callback_count = 0;

        if (Player_t::Self()->Is_In_Exterior_Cell()) {
            if (Count_Filled() > 0) {
                if (active_callback_count < 1) {
                    Vector_t<Follower_t*> non_saddlers = Non_Saddlers();
                    size_t non_saddler_count = non_saddlers.size();
                    if (non_saddler_count > 0) {
                        active_callback_count = non_saddler_count;
                        for (size_t idx = 0; idx < non_saddler_count; idx += 1) {
                            struct Saddle_Callback : Callback_t<Int_t, Follower_t*> {
                                volatile Int_t* active_callback_count;
                                Saddle_Callback(volatile Int_t* active_callback_count) :
                                    active_callback_count(active_callback_count)
                                {
                                }
                                void operator()(Int_t code, Follower_t* follower)
                                {
                                    *active_callback_count -= 1; // I don't think we need to do this atomically.
                                }
                            };
                            Callback_t<Int_t, Follower_t*>* saddle_callback = new Saddle_Callback(&active_callback_count);
                            non_saddlers[idx]->Saddle(&saddle_callback);
                        }
                        return CODES::SUCCESS;
                    } else {
                        return CODES::HASNT;
                    }
                } else {
                    return CODES::HAS;
                }
            } else {
                return CODES::FOLLOWERS;
            }
        } else {
            return CODES::INTERIOR;
        }
    }

    Int_t Followers_t::Unsaddle()
    {
        static volatile Int_t active_callback_count = 0;

        if (Count_Filled() > 0) {
            if (active_callback_count < 1) {
                Vector_t<Follower_t*> saddlers = Saddlers();
                size_t saddler_count = saddlers.size();
                if (saddler_count > 0) {
                    active_callback_count = saddler_count;
                    for (size_t idx = 0; idx < saddler_count; idx += 1) {
                        struct Unsaddle_Callback : Callback_t<Int_t, Follower_t*> {
                            volatile Int_t* active_callback_count;
                            Unsaddle_Callback(volatile Int_t* active_callback_count) :
                                active_callback_count(active_callback_count)
                            {
                            }
                            void operator()(Int_t code, Follower_t* follower)
                            {
                                *active_callback_count -= 1; // I don't think we need to do this atomically.
                            }
                        };
                        Callback_t<Int_t, Follower_t*>* unsaddle_callback = new Unsaddle_Callback(&active_callback_count);
                        saddlers[idx]->Unsaddle(&unsaddle_callback);
                    }
                    return CODES::SUCCESS;
                } else {
                    return CODES::HASNT;
                }
            } else {
                return CODES::HAS;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Retreat()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> non_retreaters = Non_Retreaters();
            size_t non_retreater_count = non_retreaters.size();
            if (non_retreater_count > 0) {
                for (size_t idx = 0; idx < non_retreater_count; idx += 1) {
                    non_retreaters[idx]->Retreat();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unretreat()
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> retreaters = Retreaters();
            size_t retreater_count = retreaters.size();
            if (retreater_count > 0) {
                for (size_t idx = 0; idx < retreater_count; idx += 1) {
                    retreaters[idx]->Unretreat();
                }
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unfollow()
    {
        Vector_t<Follower_t*> filled = Filled();
        size_t filled_count = filled.size();
        if (filled_count > 0) {
            for (size_t idx = 0; idx < filled_count; idx += 1) {
                filled[idx]->Member()->Unfollow();
            }
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unmember()
    {
        static volatile Int_t active_callback_count = 0;
        if (active_callback_count < 1) {
            Vector_t<Follower_t*> filled = Filled();
            size_t filled_count = filled.size();
            if (filled_count > 0) {
                active_callback_count = filled_count;
                Members_t* members = Members_t::Self();
                for (size_t idx = 0; idx < filled_count; idx += 1) {
                    struct Unmember_Callback : Callback_t<Int_t, Actor_t*> {
                        volatile Int_t* active_callback_count;
                        Unmember_Callback(volatile Int_t* active_callback_count) :
                            active_callback_count(active_callback_count)
                        {
                        }
                        void operator()(Int_t code, Actor_t* actor)
                        {
                            *active_callback_count -= 1;
                        }
                    };
                    Callback_t<Int_t, Actor_t*>* unmember_callback = new Unmember_Callback(&active_callback_count);
                    members->Remove_Original(filled[idx]->Actor(), &unmember_callback);
                }
                return CODES::SUCCESS;
            } else {
                return CODES::FOLLOWERS;
            }
        } else {
            return CODES::HAS;
        }
    }

    Int_t Followers_t::Level()
    {
        Vector_t<Follower_t*> filled = Filled();
        size_t filled_count = filled.size();
        if (filled_count > 0) {
            for (size_t idx = 0; idx < filled_count; idx += 1) {
                filled[idx]->Level();
            }
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Unlevel()
    {
        Vector_t<Follower_t*> filled = Filled();
        size_t filled_count = filled.size();
        if (filled_count > 0) {
            for (size_t idx = 0; idx < filled_count; idx += 1) {
                filled[idx]->Unlevel();
            }
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
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

    Int_t Followers_t::Summon_Filled(float radius, float degree, float interval)
    {
        Vector_t<Follower_t*> filled = Filled();
        if (filled.size() > 0) {
            Summon(filled, radius, degree, interval);
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Summon_Mobile(float radius, float degree, float interval)
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> mobile = Mobile();
            if (mobile.size() > 0) {
                Summon(mobile, radius, degree, interval);
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Summon_Immobile(float radius, float degree, float interval)
    {
        if (Count_Filled() > 0) {
            Vector_t<Follower_t*> immobile = Immobile();
            if (immobile.size() > 0) {
                Summon(immobile, radius, degree, interval);
                return CODES::SUCCESS;
            } else {
                return CODES::HASNT;
            }
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Catch_Up(Cell_t* new_cell, Cell_t* old_cell)
    {
        Vector_t<Follower_t*> filled = Filled();
        size_t filled_count = filled.size();
        if (filled_count > 0) {
            for (size_t idx = 0; idx < filled_count; idx += 1) {
                filled[idx]->Catch_Up(new_cell, old_cell);
            }
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Int_t Followers_t::Stash()
    {
        Vector_t<Follower_t*> filled = Filled();
        size_t filled_count = filled.size();
        if (filled_count > 0) {
            for (size_t idx = 0; idx < filled_count; idx += 1) {
                filled[idx]->Stash();
            }
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWERS;
        }
    }

    Vector_t<Follower_t*> Followers_t::Filter(Vector_t<String_t>* strings, Vector_t<Int_t>* ints, Int_t flags_1, Int_t flags_2)
    {
        return Sort(Aliases_t::Filter(Aliases(), strings, ints, flags_1, flags_2));
    }

    void Followers_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Followers_t,           \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("From_Actor", 1, Follower_t*, From_Actor, Actor_t*);
        METHOD("Level", 0, Int_t, Level);
        METHOD("Unlevel", 0, Int_t, Unlevel);

        #undef METHOD
    }

}}}
