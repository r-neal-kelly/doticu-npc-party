/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/const_ammos.h"
#include "doticu_skylib/const_armors.h"
#include "doticu_skylib/const_weapons.h"

#include "intrinsic.h"
#include "party_member_suit_template.h"

namespace doticu_npcp { namespace Party {

    Member_Suit_Template_t Member_Suit_Template_t::Archer()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Civilized()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Combatant()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Coward()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Dangerous()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Eater()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Exterior()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Follower()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Guard()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Home()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Immobile()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Inn()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Interior()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Mage()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Mannequin()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Member()
    {
        Member_Suit_Template_t suit_template;

        suit_template.armor = skylib::Const::Armors::Random_Set_Unweighted();

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Sandboxer()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Settlement()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Sitter()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Sleeper()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Thrall()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Warrior()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t::Member_Suit_Template_t() :
        armor(), weapons(), ammo(none<Ammo_t*>())
    {
    }

    Member_Suit_Template_t::Member_Suit_Template_t(const Member_Suit_Template_t& other) :
        armor(other.armor), weapons(other.weapons), ammo(other.ammo)
    {
    }

    Member_Suit_Template_t::Member_Suit_Template_t(Member_Suit_Template_t&& other) noexcept :
        armor(std::move(other.armor)), weapons(std::move(other.weapons)), ammo(std::move(other.ammo))
    {
    }

    Member_Suit_Template_t& Member_Suit_Template_t::operator =(const Member_Suit_Template_t& other)
    {
        if (this != std::addressof(other)) {
            this->armor = other.armor;
            this->weapons = other.weapons;
            this->ammo = other.ammo;
        }
        return *this;
    }

    Member_Suit_Template_t& Member_Suit_Template_t::operator =(Member_Suit_Template_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->armor = std::move(other.armor);
            this->weapons = std::move(other.weapons);
            this->ammo = std::move(other.ammo);
        }
        return *this;
    }

    Member_Suit_Template_t::~Member_Suit_Template_t()
    {
    }

}}
