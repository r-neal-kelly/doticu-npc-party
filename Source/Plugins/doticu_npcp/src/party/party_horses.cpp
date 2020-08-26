/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "consts.h"
#include "game.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_aliases.inl"
#include "party/party_followers.h"
#include "party/party_follower.h"
#include "party/party_horses.h"
#include "party/party_horse.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Horses_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_horses");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Horses_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Horses_t* Horses_t::Self()
    {
        return static_cast<Horses_t*>(Consts::Followers_Quest());
    }

    Object_t* Horses_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Horses_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
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

    Int_t Horses_t::Add_Horse(Follower_t* follower)
    {
        if (follower) {
            Horse_t* horse = From_ID(Followers_t::MAX + follower->ID());
            NPCP_ASSERT(horse);
            if (horse->Is_Unfilled()) {
                Actor_t* actor = static_cast<Actor_t*>
                    (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Horse_Leveled_Actor(), 1, true, false));
                horse->Fill(actor, follower);
                return CODES::SUCCESS;
            } else {
                return CODES::HORSE;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    Int_t Horses_t::Remove_Horse(Follower_t* follower)
    {
        if (follower) {
            Horse_t* horse = From_ID(Followers_t::MAX + follower->ID());
            NPCP_ASSERT(horse);
            if (horse->Is_Filled()) {
                class Callback : public Virtual_Callback_t {
                public:
                    Actor_t* actor;
                    Callback(Actor_t* actor) :
                        actor(actor)
                    {
                    }
                    void operator()(Variable_t* result)
                    {
                        Object_Ref::Delete_Safe(actor);
                    }
                };
                Virtual_Callback_i* callback = new Callback(horse->Actor());
                horse->Unfill(&callback);
                return CODES::SUCCESS;
            } else {
                return CODES::HORSE;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Horses_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Horses_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
