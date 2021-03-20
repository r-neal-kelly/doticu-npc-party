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
        static maybe<Reference_t*>  Armor_Chest(some<Bound_Object_t*> object);
        static maybe<Reference_t*>  Book_Chest(some<Bound_Object_t*> object);
        static maybe<Reference_t*>  Custom_Chest(some<Bound_Object_t*> object);
        static maybe<Reference_t*>  Edible_Chest(some<Bound_Object_t*> object);
        static maybe<Reference_t*>  Misc_Chest(some<Bound_Object_t*> object);
        static maybe<Reference_t*>  Weapon_Chest(some<Bound_Object_t*> object);

    public:
        template <typename T,
            std::enable_if_t<
                std::is_same<T, Functor_i<maybe<Reference_t*>, some<Bound_Object_t*>>&>::value ||
                std::is_same<T, maybe<Reference_t*>(*)(some<Bound_Object_t*>)>::value ||
                std::is_same<T, some<Reference_t*>(*)(some<Bound_Object_t*>)>::value,
                Bool_t
            > = true
        > static void   Categorize_Into_Chests(some<Reference_t*> reference, T Chest);
        static void     Categorize_Into_All_Chests(some<Reference_t*> reference);
        static void     Categorize_Into_Armor_Chests(some<Reference_t*> reference);
        static void     Categorize_Into_Book_Chests(some<Reference_t*> reference);
        static void     Categorize_Into_Custom_Chests(some<Reference_t*> reference);
        static void     Categorize_Into_Edible_Chests(some<Reference_t*> reference);
        static void     Categorize_Into_Misc_Chests(some<Reference_t*> reference);
        static void     Categorize_Into_Weapon_Chests(some<Reference_t*> reference);

        static void     Categorize_Chests();

    public:
        static void Open_Chest(some<Reference_t*> chest, String_t name, maybe<unique<Callback_i<Bool_t>>> callback);
    };

}
