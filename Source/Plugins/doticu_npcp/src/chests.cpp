/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/armor.h"
#include "doticu_skylib/book.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/potion.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/weapon.h"

#include "chests.inl"
#include "consts.h"

namespace doticu_skylib { namespace doticu_npcp {

    maybe<Reference_t*> Chests_t::Chest(Chest_e chest)
    {
        if (chest == Chest_e::INPUT)                return Consts_t::NPCP::Reference::Chest::Input()();

        else if (chest == Chest_e::SWORDS)          return Consts_t::NPCP::Reference::Chest::Swords()();
        else if (chest == Chest_e::GREATSWORDS)     return Consts_t::NPCP::Reference::Chest::Greatswords()();
        else if (chest == Chest_e::WARAXES)         return Consts_t::NPCP::Reference::Chest::Waraxes()();
        else if (chest == Chest_e::BATTLEAXES)      return Consts_t::NPCP::Reference::Chest::Battleaxes()();
        else if (chest == Chest_e::MACES)           return Consts_t::NPCP::Reference::Chest::Maces()();
        else if (chest == Chest_e::WARHAMMERS)      return Consts_t::NPCP::Reference::Chest::Warhammers()();
        else if (chest == Chest_e::DAGGERS)         return Consts_t::NPCP::Reference::Chest::Daggers()();
        else if (chest == Chest_e::STAVES)          return Consts_t::NPCP::Reference::Chest::Staves()();
        else if (chest == Chest_e::BOWS)            return Consts_t::NPCP::Reference::Chest::Bows()();
        else if (chest == Chest_e::AMMO)            return Consts_t::NPCP::Reference::Chest::Ammo()();
        else if (chest == Chest_e::OTHER_WEAPONS)   return Consts_t::NPCP::Reference::Chest::Other_Weapons()();

        else if (chest == Chest_e::LIGHT_ARMOR)     return Consts_t::NPCP::Reference::Chest::Light_Armor()();
        else if (chest == Chest_e::HEAVY_ARMOR)     return Consts_t::NPCP::Reference::Chest::Heavy_Armor()();
        else if (chest == Chest_e::SHIELDS)         return Consts_t::NPCP::Reference::Chest::Shields()();
        else if (chest == Chest_e::JEWELRY)         return Consts_t::NPCP::Reference::Chest::Jewelry()();
        else if (chest == Chest_e::CLOTHES)         return Consts_t::NPCP::Reference::Chest::Clothes()();

        else if (chest == Chest_e::POTIONS)         return Consts_t::NPCP::Reference::Chest::Potions()();
        else if (chest == Chest_e::POISONS)         return Consts_t::NPCP::Reference::Chest::Poisons()();
        else if (chest == Chest_e::INGREDIENTS)     return Consts_t::NPCP::Reference::Chest::Ingredients()();
        else if (chest == Chest_e::FOOD)            return Consts_t::NPCP::Reference::Chest::Food()();

        else if (chest == Chest_e::SOUL_GEMS)       return Consts_t::NPCP::Reference::Chest::Soul_Gems()();
        else if (chest == Chest_e::SCROLLS)         return Consts_t::NPCP::Reference::Chest::Scrolls()();
        else if (chest == Chest_e::METALS)          return Consts_t::NPCP::Reference::Chest::Metals()();
        else if (chest == Chest_e::LEATHER)         return Consts_t::NPCP::Reference::Chest::Leather()();
        else if (chest == Chest_e::GEMS)            return Consts_t::NPCP::Reference::Chest::Gems()();
        else if (chest == Chest_e::CLUTTER)         return Consts_t::NPCP::Reference::Chest::Clutter()();
        else if (chest == Chest_e::KEYS)            return Consts_t::NPCP::Reference::Chest::Keys()();
        else if (chest == Chest_e::OTHER_MISC)      return Consts_t::NPCP::Reference::Chest::Other_Misc()();

        else if (chest == Chest_e::SPELL_TOMES)     return Consts_t::NPCP::Reference::Chest::Spell_Tomes()();
        else if (chest == Chest_e::RECIPES)         return Consts_t::NPCP::Reference::Chest::Recipes()();
        else if (chest == Chest_e::A_BOOKS)         return Consts_t::NPCP::Reference::Chest::A_Books()();
        else if (chest == Chest_e::B_BOOKS)         return Consts_t::NPCP::Reference::Chest::B_Books()();
        else if (chest == Chest_e::C_BOOKS)         return Consts_t::NPCP::Reference::Chest::C_Books()();
        else if (chest == Chest_e::D_BOOKS)         return Consts_t::NPCP::Reference::Chest::D_Books()();
        else if (chest == Chest_e::E_BOOKS)         return Consts_t::NPCP::Reference::Chest::E_Books()();
        else if (chest == Chest_e::F_BOOKS)         return Consts_t::NPCP::Reference::Chest::F_Books()();
        else if (chest == Chest_e::G_BOOKS)         return Consts_t::NPCP::Reference::Chest::G_Books()();
        else if (chest == Chest_e::H_BOOKS)         return Consts_t::NPCP::Reference::Chest::H_Books()();
        else if (chest == Chest_e::I_BOOKS)         return Consts_t::NPCP::Reference::Chest::I_Books()();
        else if (chest == Chest_e::J_BOOKS)         return Consts_t::NPCP::Reference::Chest::J_Books()();
        else if (chest == Chest_e::K_BOOKS)         return Consts_t::NPCP::Reference::Chest::K_Books()();
        else if (chest == Chest_e::L_BOOKS)         return Consts_t::NPCP::Reference::Chest::L_Books()();
        else if (chest == Chest_e::M_BOOKS)         return Consts_t::NPCP::Reference::Chest::M_Books()();
        else if (chest == Chest_e::N_BOOKS)         return Consts_t::NPCP::Reference::Chest::N_Books()();
        else if (chest == Chest_e::O_BOOKS)         return Consts_t::NPCP::Reference::Chest::O_Books()();
        else if (chest == Chest_e::P_BOOKS)         return Consts_t::NPCP::Reference::Chest::P_Books()();
        else if (chest == Chest_e::Q_BOOKS)         return Consts_t::NPCP::Reference::Chest::Q_Books()();
        else if (chest == Chest_e::R_BOOKS)         return Consts_t::NPCP::Reference::Chest::R_Books()();
        else if (chest == Chest_e::S_BOOKS)         return Consts_t::NPCP::Reference::Chest::S_Books()();
        else if (chest == Chest_e::T_BOOKS)         return Consts_t::NPCP::Reference::Chest::T_Books()();
        else if (chest == Chest_e::U_BOOKS)         return Consts_t::NPCP::Reference::Chest::U_Books()();
        else if (chest == Chest_e::V_BOOKS)         return Consts_t::NPCP::Reference::Chest::V_Books()();
        else if (chest == Chest_e::W_BOOKS)         return Consts_t::NPCP::Reference::Chest::W_Books()();
        else if (chest == Chest_e::X_BOOKS)         return Consts_t::NPCP::Reference::Chest::X_Books()();
        else if (chest == Chest_e::Y_BOOKS)         return Consts_t::NPCP::Reference::Chest::Y_Books()();
        else if (chest == Chest_e::Z_BOOKS)         return Consts_t::NPCP::Reference::Chest::Z_Books()();
        else if (chest == Chest_e::OTHER_BOOKS)     return Consts_t::NPCP::Reference::Chest::Other_Books()();

        else if (chest == Chest_e::CUSTOM_00)       return Consts_t::NPCP::Reference::Chest::Custom_00()();
        else if (chest == Chest_e::CUSTOM_01)       return Consts_t::NPCP::Reference::Chest::Custom_01()();
        else if (chest == Chest_e::CUSTOM_02)       return Consts_t::NPCP::Reference::Chest::Custom_02()();
        else if (chest == Chest_e::CUSTOM_03)       return Consts_t::NPCP::Reference::Chest::Custom_03()();
        else if (chest == Chest_e::CUSTOM_04)       return Consts_t::NPCP::Reference::Chest::Custom_04()();
        else if (chest == Chest_e::CUSTOM_05)       return Consts_t::NPCP::Reference::Chest::Custom_05()();
        else if (chest == Chest_e::CUSTOM_06)       return Consts_t::NPCP::Reference::Chest::Custom_06()();
        else if (chest == Chest_e::CUSTOM_07)       return Consts_t::NPCP::Reference::Chest::Custom_07()();
        else if (chest == Chest_e::CUSTOM_08)       return Consts_t::NPCP::Reference::Chest::Custom_08()();
        else if (chest == Chest_e::CUSTOM_09)       return Consts_t::NPCP::Reference::Chest::Custom_09()();
        else if (chest == Chest_e::CUSTOM_10)       return Consts_t::NPCP::Reference::Chest::Custom_10()();
        else if (chest == Chest_e::CUSTOM_11)       return Consts_t::NPCP::Reference::Chest::Custom_11()();
        else if (chest == Chest_e::CUSTOM_12)       return Consts_t::NPCP::Reference::Chest::Custom_12()();
        else if (chest == Chest_e::CUSTOM_13)       return Consts_t::NPCP::Reference::Chest::Custom_13()();
        else if (chest == Chest_e::CUSTOM_14)       return Consts_t::NPCP::Reference::Chest::Custom_14()();
        else if (chest == Chest_e::CUSTOM_15)       return Consts_t::NPCP::Reference::Chest::Custom_15()();

        else                                        return none<Reference_t*>();
    }

    some<Reference_t*> Chests_t::Chest(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Reference_t*> custom_chest = Custom_Chest(object);
        if (custom_chest) {
            return custom_chest();
        } else {
            maybe<Reference_t*> armor_chest = Armor_Chest(object);
            if (armor_chest) {
                return armor_chest();
            } else {
                maybe<Reference_t*> weapon_chest = Weapon_Chest(object);
                if (weapon_chest) {
                    return weapon_chest();
                } else {
                    maybe<Reference_t*> edible_chest = Edible_Chest(object);
                    if (edible_chest) {
                        return edible_chest();
                    } else {
                        maybe<Reference_t*> book_chest = Book_Chest(object);
                        if (book_chest) {
                            return book_chest();
                        } else {
                            maybe<Reference_t*> misc_chest = Misc_Chest(object);
                            if (misc_chest) {
                                return misc_chest();
                            } else {
                                return Consts_t::NPCP::Reference::Chest::Other_Misc();
                            }
                        }
                    }
                }
            }
        }
    }

    maybe<Reference_t*> Chests_t::Armor_Chest(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Armor_t*> armor = object->As_Armor();
        if (armor) {
            if (armor->Is_Light_Armor()) {
                return Consts_t::NPCP::Reference::Chest::Light_Armor()();
            } else if (armor->Is_Heavy_Armor()) {
                return Consts_t::NPCP::Reference::Chest::Heavy_Armor()();
            } else if (armor->Is_Shield()) {
                return Consts_t::NPCP::Reference::Chest::Shields()();
            } else if (armor->Is_Likely_Jewelry()) {
                return Consts_t::NPCP::Reference::Chest::Jewelry()();
            } else if (armor->Is_Likely_Clothing()) {
                return Consts_t::NPCP::Reference::Chest::Clothes()();
            } else if (armor->Is_Surely_Armor()) {
                return Consts_t::NPCP::Reference::Chest::Light_Armor()();
            } else if (armor->Is_Surely_Jewelry()) {
                return Consts_t::NPCP::Reference::Chest::Jewelry()();
            } else {
                return Consts_t::NPCP::Reference::Chest::Clothes()();
            }
        } else {
            return none<Reference_t*>();
        }
    }

    maybe<Reference_t*> Chests_t::Book_Chest(some<Bound_Object_t*> object)
    {
        static some<Reference_t*> a_to_z_chests[26] = {
            Consts_t::NPCP::Reference::Chest::A_Books(),
            Consts_t::NPCP::Reference::Chest::B_Books(),
            Consts_t::NPCP::Reference::Chest::C_Books(),
            Consts_t::NPCP::Reference::Chest::D_Books(),
            Consts_t::NPCP::Reference::Chest::E_Books(),
            Consts_t::NPCP::Reference::Chest::F_Books(),
            Consts_t::NPCP::Reference::Chest::G_Books(),
            Consts_t::NPCP::Reference::Chest::H_Books(),
            Consts_t::NPCP::Reference::Chest::I_Books(),
            Consts_t::NPCP::Reference::Chest::J_Books(),
            Consts_t::NPCP::Reference::Chest::K_Books(),
            Consts_t::NPCP::Reference::Chest::L_Books(),
            Consts_t::NPCP::Reference::Chest::M_Books(),
            Consts_t::NPCP::Reference::Chest::N_Books(),
            Consts_t::NPCP::Reference::Chest::O_Books(),
            Consts_t::NPCP::Reference::Chest::P_Books(),
            Consts_t::NPCP::Reference::Chest::Q_Books(),
            Consts_t::NPCP::Reference::Chest::R_Books(),
            Consts_t::NPCP::Reference::Chest::S_Books(),
            Consts_t::NPCP::Reference::Chest::T_Books(),
            Consts_t::NPCP::Reference::Chest::U_Books(),
            Consts_t::NPCP::Reference::Chest::V_Books(),
            Consts_t::NPCP::Reference::Chest::W_Books(),
            Consts_t::NPCP::Reference::Chest::X_Books(),
            Consts_t::NPCP::Reference::Chest::Y_Books(),
            Consts_t::NPCP::Reference::Chest::Z_Books(),
        };

        SKYLIB_ASSERT_SOME(object);

        maybe<Book_t*> book = object->As_Book();
        if (book) {
            if (book->Is_Spell_Tome()) {
                return Consts_t::NPCP::Reference::Chest::Spell_Tomes()();
            } else if (book->Is_Recipe()) {
                return Consts_t::NPCP::Reference::Chest::Recipes()();
            } else {
                some<const char*> component_name = book->Component_Name();
                const char first_letter = tolower(component_name[0]);
                if (first_letter >= 'a' && first_letter <= 'z') {
                    return a_to_z_chests[first_letter - 'a']();
                } else {
                    return Consts_t::NPCP::Reference::Chest::Other_Books()();
                }
            }
        } else {
            return none<Reference_t*>();
        }
    }

    maybe<Reference_t*> Chests_t::Custom_Chest(some<Bound_Object_t*> object)
    {
        static some<Reference_t*> custom_chests[MAX_CUSTOM_CHESTS] = {
            Consts_t::NPCP::Reference::Chest::Custom_00(),
            Consts_t::NPCP::Reference::Chest::Custom_01(),
            Consts_t::NPCP::Reference::Chest::Custom_02(),
            Consts_t::NPCP::Reference::Chest::Custom_03(),
            Consts_t::NPCP::Reference::Chest::Custom_04(),
            Consts_t::NPCP::Reference::Chest::Custom_05(),
            Consts_t::NPCP::Reference::Chest::Custom_06(),
            Consts_t::NPCP::Reference::Chest::Custom_07(),
            Consts_t::NPCP::Reference::Chest::Custom_08(),
            Consts_t::NPCP::Reference::Chest::Custom_09(),
            Consts_t::NPCP::Reference::Chest::Custom_10(),
            Consts_t::NPCP::Reference::Chest::Custom_11(),
            Consts_t::NPCP::Reference::Chest::Custom_12(),
            Consts_t::NPCP::Reference::Chest::Custom_13(),
            Consts_t::NPCP::Reference::Chest::Custom_14(),
            Consts_t::NPCP::Reference::Chest::Custom_15(),
        };

        SKYLIB_ASSERT_SOME(object);

        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            some<Reference_t*> custom_chest = custom_chests[idx];
            if (custom_chest->Container_Entry_Count(object) > 0) {
                return custom_chest();
            }
        }

        return none<Reference_t*>();
    }

    maybe<Reference_t*> Chests_t::Edible_Chest(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Ingredient_t*> ingredient = object->As_Ingredient();
        if (ingredient) {
            return Consts_t::NPCP::Reference::Chest::Ingredients()();
        } else {
            maybe<Potion_t*> potion = object->As_Potion();
            if (potion) {
                if (potion->Is_Potion()) {
                    return Consts_t::NPCP::Reference::Chest::Potions()();
                } else if (potion->Is_Poison()) {
                    return Consts_t::NPCP::Reference::Chest::Poisons()();
                } else {
                    return Consts_t::NPCP::Reference::Chest::Food()();
                }
            } else {
                return none<Reference_t*>();
            }
        }
    }

    maybe<Reference_t*> Chests_t::Misc_Chest(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Misc_t*> misc = object->As_Misc();
        if (misc) {
            if (misc->Is_Soul_Gem()) {
                return Consts_t::NPCP::Reference::Chest::Soul_Gems()();
            } else if (misc->Is_Key()) {
                return Consts_t::NPCP::Reference::Chest::Keys()();
            } else if (misc->Is_Ore_Or_Ingot()) {
                return Consts_t::NPCP::Reference::Chest::Metals()();
            } else if (misc->Is_Animal_Hide()) {
                return Consts_t::NPCP::Reference::Chest::Leather()();
            } else if (misc->Is_Gem()) {
                return Consts_t::NPCP::Reference::Chest::Gems()();
            } else {
                return Consts_t::NPCP::Reference::Chest::Clutter()();
            }
        } else {
            maybe<Scroll_t*> scroll = object->As_Scroll();
            if (scroll) {
                return Consts_t::NPCP::Reference::Chest::Scrolls()();
            } else {
                return none<Reference_t*>();
            }
        }
    }

    maybe<Reference_t*> Chests_t::Weapon_Chest(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Weapon_t*> weapon = object->As_Weapon();
        if (weapon) {
            if (weapon->Is_Bow_Or_Crossbow()) {
                return Consts_t::NPCP::Reference::Chest::Bows()();
            } else if (weapon->Is_Dagger()) {
                return Consts_t::NPCP::Reference::Chest::Daggers()();
            } else if (weapon->Is_Greatsword()) {
                return Consts_t::NPCP::Reference::Chest::Greatswords()();
            } else if (weapon->Is_Sword()) {
                return Consts_t::NPCP::Reference::Chest::Swords()();
            } else if (weapon->Is_Battleaxe()) {
                return Consts_t::NPCP::Reference::Chest::Battleaxes()();
            } else if (weapon->Is_Waraxe()) {
                return Consts_t::NPCP::Reference::Chest::Waraxes()();
            } else if (weapon->Is_Warhammer()) {
                return Consts_t::NPCP::Reference::Chest::Warhammers()();
            } else if (weapon->Is_Mace()) {
                return Consts_t::NPCP::Reference::Chest::Maces()();
            } else if (weapon->Is_Staff()) {
                return Consts_t::NPCP::Reference::Chest::Staves()();
            } else {
                return Consts_t::NPCP::Reference::Chest::Other_Weapons()();
            }
        } else {
            maybe<Ammo_t*> ammo = object->As_Ammo();
            if (ammo) {
                return Consts_t::NPCP::Reference::Chest::Ammo()();
            } else {
                return none<Reference_t*>();
            }
        }
    }

    void Chests_t::Categorize_Into_All_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests<some<Reference_t*>(*)(some<Bound_Object_t*>)>(reference, &Chest);
    }

    void Chests_t::Categorize_Into_Armor_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests(reference, &Armor_Chest);
    }

    void Chests_t::Categorize_Into_Book_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests(reference, &Book_Chest);
    }

    void Chests_t::Categorize_Into_Custom_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests(reference, &Custom_Chest);
    }

    void Chests_t::Categorize_Into_Edible_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests(reference, &Edible_Chest);
    }

    void Chests_t::Categorize_Into_Misc_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests(reference, &Misc_Chest);
    }

    void Chests_t::Categorize_Into_Weapon_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        Categorize_Into_Chests(reference, &Weapon_Chest);
    }

    void Chests_t::Categorize_Chests()
    {
        Categorize_Into_All_Chests(Consts_t::NPCP::Reference::Chest::Input());

        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Swords());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Greatswords());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Waraxes());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Battleaxes());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Maces());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Warhammers());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Daggers());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Staves());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Bows());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Ammo());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Other_Weapons());

        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Light_Armor());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Heavy_Armor());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Shields());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Jewelry());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Clothes());

        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Potions());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Poisons());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Ingredients());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Food());

        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Soul_Gems());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Scrolls());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Metals());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Leather());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Gems());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Clutter());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Keys());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Other_Misc());

        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Spell_Tomes());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Recipes());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::A_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::B_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::C_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::D_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::E_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::F_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::G_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::H_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::I_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::J_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::K_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::L_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::M_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::N_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::O_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::P_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Q_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::R_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::S_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::T_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::U_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::V_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::W_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::X_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Y_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Z_Books());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Other_Books());
    }

    void Chests_t::Open_Chest(Chest_e chest, String_t name, maybe<unique<Callback_i<Bool_t>>> callback)
    {
        maybe<Reference_t*> reference = Chest(chest);
        if (reference) {
            Categorize_Chests();
            reference->Name(name);
            reference->Open_Inventory(std::move(callback));
        }
    }

}}
