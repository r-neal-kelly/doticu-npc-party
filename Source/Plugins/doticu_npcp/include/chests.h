/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcp {

    class Chests_t
    {
    public:
        static constexpr size_t MAX_CUSTOM_CHESTS = 16;

    public:
        static some<Reference_t*>   Chest(some<Bound_Object_t*> object);
        static maybe<Reference_t*>  Custom_Chest(some<Bound_Object_t*> object);
        static void                 Open_Chest(some<Reference_t*> chest, String_t name, maybe<unique<Callback_i<Bool_t>>> callback);

        static void                 Categorize_Chests();
        static void                 Categorize_Into_All_Chests(some<Reference_t*> reference);
        static void                 Categorize_Into_Custom_Chests(some<Reference_t*> reference);
    };

}
