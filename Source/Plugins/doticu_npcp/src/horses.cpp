/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "aliases.h"
#include "horses.h"

namespace doticu_npcp { namespace Party { namespace Horses {

    Range_t<UInt64> Indices(Horses_t* self)
    {
        return { BEGIN, END };
    }

    Range_t<Alias_t**> Aliases(Horses_t* self)
    {
        return Aliases::Aliases(self, BEGIN, END);
    }

    Range_t<Horse_t**> Horses(Horses_t* self)
    {
        return Aliases(self);
    }

    Horse_t* From_Actor(Horses_t* self, Actor_t* actor)
    {
        if (self && actor) {
            Alias_t* alias = Aliases::From_Actor(self, actor);
            if (alias) {
                if (alias->id >= BEGIN && alias->id < END) {
                    return alias;
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

}}}
