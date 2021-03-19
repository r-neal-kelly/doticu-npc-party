/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/armor.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/potion.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/weapon.h"

#include "chests.h"
#include "consts.h"

namespace doticu_npcp {

    some<Reference_t*> Chests_t::Chest(some<Bound_Object_t*> object)
    {
        static some<Reference_t*> a_to_z_book_chests[26] = {
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

        maybe<Reference_t*> custom_chest = Custom_Chest(object);
        if (custom_chest) {
            return custom_chest();
        } else {
            maybe<Weapon_t*> weapon = object->As_Weapon();
            if (weapon) {
                if (weapon->Is_Bow_Or_Crossbow())   return Consts_t::NPCP::Reference::Chest::Bows();
                else if (weapon->Is_Dagger())       return Consts_t::NPCP::Reference::Chest::Daggers();
                else if (weapon->Is_Greatsword())   return Consts_t::NPCP::Reference::Chest::Greatswords();
                else if (weapon->Is_Sword())        return Consts_t::NPCP::Reference::Chest::Swords();
                else if (weapon->Is_Battleaxe())    return Consts_t::NPCP::Reference::Chest::Battleaxes();
                else if (weapon->Is_Waraxe())       return Consts_t::NPCP::Reference::Chest::Waraxes();
                else if (weapon->Is_Warhammer())    return Consts_t::NPCP::Reference::Chest::Warhammers();
                else if (weapon->Is_Mace())         return Consts_t::NPCP::Reference::Chest::Maces();
                else if (weapon->Is_Staff())        return Consts_t::NPCP::Reference::Chest::Staves();
                else                                return Consts_t::NPCP::Reference::Chest::Other_Weapons();
            }
            maybe<Armor_t*> armor = object->As_Armor();
            if (armor) {
                if (armor->Is_Light_Armor())            return Consts_t::NPCP::Reference::Chest::Light_Armor();
                else if (armor->Is_Heavy_Armor())       return Consts_t::NPCP::Reference::Chest::Heavy_Armor();
                else if (armor->Is_Shield())            return Consts_t::NPCP::Reference::Chest::Shields();
                else if (armor->Is_Likely_Jewelry())    return Consts_t::NPCP::Reference::Chest::Jewelry();
                else if (armor->Is_Likely_Clothing())   return Consts_t::NPCP::Reference::Chest::Clothes();
                else if (armor->Is_Surely_Armor())      return Consts_t::NPCP::Reference::Chest::Light_Armor();
                else if (armor->Is_Surely_Jewelry())    return Consts_t::NPCP::Reference::Chest::Jewelry();
                else                                    return Consts_t::NPCP::Reference::Chest::Clothes();
            }
            maybe<Potion_t*> potion = object->As_Potion();
            if (potion) {
                if (potion->Is_Medicine())      return Consts_t::NPCP::Reference::Chest::Potions();
                else if (potion->Is_Poison())   return Consts_t::NPCP::Reference::Chest::Poisons();
                else                            return Consts_t::NPCP::Reference::Chest::Food();
            }
            /*
        switch (form->formType) {
            case (kFormType_Book):
            {
                if (Form::Has_Keyword(form, keywords->VendorItemSpellTome)) {
                    return Consts::Spell_Tomes_Category();
                } else if (Form::Has_Keyword(form, keywords->VendorItemRecipe)) {
                    return Consts::Recipes_Category();
                } else {
                    const char chr = tolower(Form::Get_Name(form)[0]);
                    s64 idx_chars = chr >= 'a' && chr <= 'z' ? chr - 'a' : -1;
                    if (idx_chars > -1 && idx_chars < 26) {
                        return book_categories[idx_chars];
                    } else {
                        return Consts::Books_Category();
                    }
                }
            }
            case (kFormType_Misc):
            {
                if (Form::Has_Keyword(form, keywords->VendorItemOreIngot)) {
                    return Consts::Metals_Category();
                } else if (Form::Has_Keyword(form, keywords->VendorItemAnimalHide)) {
                    return Consts::Leather_Category();
                } else if (Form::Has_Keyword(form, keywords->VendorItemGem)) {
                    return Consts::Gems_Category();
                } else {
                    return Consts::Clutter_Category();
                }
            }
            case (kFormType_Ammo):
            {
                return Consts::Ammo_Category();
            }
            case (kFormType_Ingredient):
            {
                return Consts::Ingredients_Category();
            }
            case (kFormType_ScrollItem):
            {
                return Consts::Scrolls_Category();
            }
            case (kFormType_SoulGem):
            {
                return Consts::Soulgems_Category();
            }
            case (kFormType_Key):
            {
                return Consts::Keys_Category();
            }
            default:
            {
                return Consts::Misc_Category();
            }
        }
            */
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

    void Chests_t::Open_Chest(some<Reference_t*> chest, String_t name, maybe<unique<Callback_i<Bool_t>>> callback)
    {
        SKYLIB_ASSERT_SOME(chest);

        chest->Name(name);
        chest->Open_Inventory(std::move(callback));
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

        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Soulgems());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Scrolls());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Metals());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Leather());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Gems());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Clutter());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Keys());
        Categorize_Into_Custom_Chests(Consts_t::NPCP::Reference::Chest::Misc());

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

    void Chests_t::Categorize_Into_All_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);


    }

    /*
    void Categorize(Reference_t *ref, Bool_t only_custom_categories) {
        if (ref) {
            Vector_t<XEntry_t*> xentries_to_destroy;
            xentries_to_destroy.reserve(2);

            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                    XEntry_t* xentry = it.Get();
                    if (xentry && xentry->form && xentry->form->IsPlayable()) {
                        Reference_t* category = only_custom_categories ?
                            Game::Get_NPCP_Custom_Category(xentry->form) :
                            Game::Get_NPCP_Category(xentry->form);
                        Init_Container_If_Needed(category);
                        if (category && category != ref) {
                            Int_t bentry_count = Get_BEntry_Count(ref, xentry->form);
                            xentry->Validate(bentry_count);

                            XEntry_t* category_xentry = nullptr;

                            Vector_t<XList_t*> xlists_to_move;
                            xlists_to_move.reserve(2);
                            for (XLists_t::Iterator it = xentry->xlists->Begin(); !it.End(); ++it) {
                                XList_t* xlist = it.Get();
                                if (xlist) {
                                    xlists_to_move.push_back(xlist);
                                }
                            }

                            size_t xlists_to_move_count = xlists_to_move.size();
                            if (xlists_to_move_count > 0) {
                                category_xentry = Get_XEntry(category, xentry->form, true);
                                NPCP_ASSERT(category_xentry);
                                for (size_t idx = 0; idx < xlists_to_move_count; idx += 1) {
                                    XList_t* xlist = xlists_to_move[idx];
                                    xentry->Move_XList(category_xentry, category, xlist);
                                }
                            }
                            
                            Int_t bentry_negation = 0 - bentry_count;
                            if (xentry->Delta_Count() < bentry_negation) {
                                xentry->Delta_Count(bentry_negation);
                            }

                            if (xentry->Delta_Count() > bentry_negation) {
                                if (!category_xentry) {
                                    category_xentry = Get_XEntry(category, xentry->form, true);
                                    NPCP_ASSERT(category_xentry);
                                }
                                category_xentry->Increment(xentry->Delta_Count() - bentry_negation);
                                xentry->Delta_Count(bentry_negation);
                            }

                            if (xentry->Delta_Count() == 0) {
                                xentries_to_destroy.push_back(xentry);
                            }
                        }
                    }
                }
            }

            for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                XEntry_t* xentry = xentries_to_destroy[idx];
                Remove_XEntry(ref, xentry);
                XEntry_t::Destroy(xentry);
            }

            BContainer_t* bcontainer = Object_Ref::Get_BContainer(ref);
            if (bcontainer) {
                for (size_t idx = 0; idx < bcontainer->numEntries; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form && bentry->count > 0) {
                        if (bentry->form->IsPlayable() && bentry->form->formType != kFormType_LeveledItem) {
                            if (Get_XEntry(ref, bentry->form, false) == nullptr) {
                                Reference_t* category = only_custom_categories ?
                                    Game::Get_NPCP_Custom_Category(bentry->form) :
                                    Game::Get_NPCP_Category(bentry->form);
                                Init_Container_If_Needed(category);
                                if (category && category != ref) {
                                    XEntry_t* category_xentry = Get_XEntry(category, bentry->form, true);
                                    NPCP_ASSERT(category_xentry);
                                    category_xentry->Increment(bentry->count);
                                    XEntry_t* xentry = Get_XEntry(ref, bentry->form, true);
                                    NPCP_ASSERT(xentry);
                                    xentry->Delta_Count(0 - bentry->count);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    */

    void Chests_t::Categorize_Into_Custom_Chests(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);
    }

}
