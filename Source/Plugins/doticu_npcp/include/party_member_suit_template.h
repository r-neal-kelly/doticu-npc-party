/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/armor_set.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Suit_Template_t
    {
    public:
        static Member_Suit_Template_t   Archer();
        static Member_Suit_Template_t   Civilized();
        static Member_Suit_Template_t   Combatant();
        static Member_Suit_Template_t   Coward();
        static Member_Suit_Template_t   Dangerous();
        static Member_Suit_Template_t   Eater();
        static Member_Suit_Template_t   Exterior();
        static Member_Suit_Template_t   Follower();
        static Member_Suit_Template_t   Guard();
        static Member_Suit_Template_t   Home();
        static Member_Suit_Template_t   Immobile();
        static Member_Suit_Template_t   Inn();
        static Member_Suit_Template_t   Interior();
        static Member_Suit_Template_t   Mage();
        static Member_Suit_Template_t   Mannequin();
        static Member_Suit_Template_t   Member();
        static Member_Suit_Template_t   Sandboxer();
        static Member_Suit_Template_t   Settlement();
        static Member_Suit_Template_t   Sitter();
        static Member_Suit_Template_t   Sleeper();
        static Member_Suit_Template_t   Thrall();
        static Member_Suit_Template_t   Warrior();

    public:
        Armor_Set_t                 armor;
        Vector_t<some<Weapon_t*>>   weapons;
        maybe<Ammo_t*>              ammo;

    public:
        Member_Suit_Template_t();
        Member_Suit_Template_t(const Member_Suit_Template_t& other);
        Member_Suit_Template_t(Member_Suit_Template_t&& other) noexcept;
        Member_Suit_Template_t& operator =(const Member_Suit_Template_t& other);
        Member_Suit_Template_t& operator =(Member_Suit_Template_t&& other) noexcept;
        ~Member_Suit_Template_t();
    };

}}
