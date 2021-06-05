/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Chest_e :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            INPUT,

            SWORDS,
            GREATSWORDS,
            WARAXES,
            BATTLEAXES,
            MACES,
            WARHAMMERS,
            DAGGERS,
            STAVES,
            BOWS,
            AMMO,
            OTHER_WEAPONS,

            LIGHT_ARMOR,
            HEAVY_ARMOR,
            SHIELDS,
            JEWELRY,
            CLOTHES,

            POTIONS,
            POISONS,
            INGREDIENTS,
            FOOD,

            SOUL_GEMS,
            SCROLLS,
            METALS,
            LEATHER,
            GEMS,
            CLUTTER,
            KEYS,
            OTHER_MISC,

            SPELL_TOMES,
            RECIPES,
            A_BOOKS,
            B_BOOKS,
            C_BOOKS,
            D_BOOKS,
            E_BOOKS,
            F_BOOKS,
            G_BOOKS,
            H_BOOKS,
            I_BOOKS,
            J_BOOKS,
            K_BOOKS,
            L_BOOKS,
            M_BOOKS,
            N_BOOKS,
            O_BOOKS,
            P_BOOKS,
            Q_BOOKS,
            R_BOOKS,
            S_BOOKS,
            T_BOOKS,
            U_BOOKS,
            V_BOOKS,
            W_BOOKS,
            X_BOOKS,
            Y_BOOKS,
            Z_BOOKS,
            OTHER_BOOKS,

            CUSTOM_00,
            CUSTOM_01,
            CUSTOM_02,
            CUSTOM_03,
            CUSTOM_04,
            CUSTOM_05,
            CUSTOM_06,
            CUSTOM_07,
            CUSTOM_08,
            CUSTOM_09,
            CUSTOM_10,
            CUSTOM_11,
            CUSTOM_12,
            CUSTOM_13,
            CUSTOM_14,
            CUSTOM_15,
        };

    public:
        using Enum_t::Enum_t;
    };

    class Chests_t
    {
    public:
        static constexpr size_t MAX_CUSTOM_CHESTS = 16;

    public:
        static maybe<Reference_t*>  Chest(Chest_e chest);

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
        static void Open_Chest(Chest_e chest, String_t name, maybe<unique<Callback_i<Bool_t>>> callback = nullptr);
    };

}}
