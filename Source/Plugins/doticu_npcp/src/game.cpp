/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameRTTI.h"

#include "consts.h"
#include "form.h"
#include "game.h"
#include "object_ref.h"
#include "string2.h"
#include "types.h"
#include "utils.h"

namespace doticu_npcp { namespace Game {

    Bool_t Is_Outsourced_Follower(Actor_t* actor)
    {
        if (actor) {
            ExtraAliasInstanceArray* xaliases = static_cast<ExtraAliasInstanceArray*>
                (actor->extraData.GetByType(kExtraData_AliasInstanceArray));
            using Alias_Info_t = ExtraAliasInstanceArray::AliasInfo;
            if (xaliases) {
                BSReadLocker locker(&xaliases->lock);
                Quest_t* vanilla_followers_quest = Consts::Follower_Dialogue_Quest();
                Quest_t* npcp_followers_quest = Consts::Followers_Quest();
                Package_t* follower_template_package = Consts::Follower_Template_Package();
                Package_t* follow_player_template_package = Consts::Follow_Player_Template_Package();
                Package_t* follow_template_package = Consts::Follow_Template_Package();
                Actor_t* player_actor = Consts::Player_Actor();
                Reference_Handle_t player_reference_handle = player_actor->CreateRefHandle();
                for (size_t idx = 0, end = xaliases->aliases.count; idx < end; idx += 1) {
                    Alias_Info_t* alias_info = xaliases->aliases.entries[idx];
                    if (alias_info && alias_info->quest) {
                        if (alias_info->quest == vanilla_followers_quest) {
                            return true;
                        } else if (alias_info->quest != npcp_followers_quest && alias_info->packages) {
                            for (size_t idx = 0, end = alias_info->packages->count; idx < end; idx += 1) {
                                Package_t* package = reinterpret_cast<Package_t*>(alias_info->packages->entries[idx]);
                                if (package) {
                                    if (package->data) {
                                        Package_t* package_template = package->data->package_template;
                                        if (package_template == follower_template_package ||
                                            package_template == follow_player_template_package ||
                                            package_template == follow_template_package) {
                                            for (size_t idx = 0, end = package->data->value_count; idx < end; idx += 1) {
                                                Package_Value_t* value = package->data->values[idx];
                                                if (value && value->Type() == Package_Value_t::Type_e::SINGLE_REFERENCE) {
                                                    Package_Target_t* target =
                                                        static_cast<Package_Single_Reference_Value_t*>(value)->target;
                                                    if (target) {
                                                        if (target->type == Package_Target_t::Type_e::SPECIFIC) {
                                                            if (target->target.specific == player_reference_handle) {
                                                                return true;
                                                            }
                                                        } else if (target->type == Package_Target_t::Type_e::LINKED) {
                                                            if (target->target.linked == player_actor ||
                                                                target->target.linked == player_actor->baseForm) {
                                                                return true;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    struct NPCP_Category_Keywords {
        BGSKeyword *WeapTypeSword; // kFormType_Weapon
        BGSKeyword *WeapTypeGreatsword;
        BGSKeyword *WeapTypeWarAxe;
        BGSKeyword *WeapTypeBattleaxe;
        BGSKeyword *WeapTypeMace;
        BGSKeyword *WeapTypeWarhammer;
        BGSKeyword *WeapTypeDagger;
        BGSKeyword *WeapTypeBow;
        BGSKeyword *WeapTypeStaff;
        BGSKeyword *VendorItemStaff;
        
        BGSKeyword *ArmorLight; // kFormType_Armor
        BGSKeyword *ArmorHeavy;
        BGSKeyword *ArmorShield;
        BGSKeyword *ArmorJewelry;
        BGSKeyword *ArmorClothing;
        BGSKeyword *ArmorBoots;
        BGSKeyword *ArmorCuirass;
        BGSKeyword *ArmorGauntlets;
        BGSKeyword *ArmorHelmet;
        BGSKeyword *VendorItemJewelry;
        BGSKeyword *ClothingCirclet;
        BGSKeyword *ClothingNecklace;
        BGSKeyword *ClothingRing;

        BGSKeyword *VendorItemPotion; // kFormType_Potion
        BGSKeyword *VendorItemPoison;
        
        BGSKeyword *VendorItemSpellTome; // kFormType_Book
        BGSKeyword *VendorItemRecipe;

        BGSKeyword *VendorItemOreIngot; // kFormType_Misc
        BGSKeyword *VendorItemAnimalHide;
        BGSKeyword *VendorItemGem;
    };

    Reference_t* Get_NPCP_Category(Form_t* form)
    {
        static Reference_t* book_categories[26] = {
            Consts::A_Books_Category(),
            Consts::B_Books_Category(),
            Consts::C_Books_Category(),
            Consts::D_Books_Category(),
            Consts::E_Books_Category(),
            Consts::F_Books_Category(),
            Consts::G_Books_Category(),
            Consts::H_Books_Category(),
            Consts::I_Books_Category(),
            Consts::J_Books_Category(),
            Consts::K_Books_Category(),
            Consts::L_Books_Category(),
            Consts::M_Books_Category(),
            Consts::N_Books_Category(),
            Consts::O_Books_Category(),
            Consts::P_Books_Category(),
            Consts::Q_Books_Category(),
            Consts::R_Books_Category(),
            Consts::S_Books_Category(),
            Consts::T_Books_Category(),
            Consts::U_Books_Category(),
            Consts::V_Books_Category(),
            Consts::W_Books_Category(),
            Consts::X_Books_Category(),
            Consts::Y_Books_Category(),
            Consts::Z_Books_Category()
        };

        NPCP_ASSERT(form);

        Reference_t* custom_category = Get_NPCP_Custom_Category(form);
        if (custom_category) {
            return custom_category;
        }

        NPCP_Category_Keywords* keywords = Get_NPCP_Category_Keywords();
        NPCP_ASSERT(keywords);

        switch (form->formType) {
            case (kFormType_Weapon):
            {
                if (Form::Has_Keyword(form, keywords->WeapTypeBow)) {
                    return Consts::Bows_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeDagger)) {
                    return Consts::Daggers_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeGreatsword)) {
                    return Consts::Greatswords_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeSword)) {
                    return Consts::Swords_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeBattleaxe)) {
                    return Consts::Battleaxes_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeWarAxe)) {
                    return Consts::Waraxes_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeWarhammer)) {
                    return Consts::Warhammers_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeMace)) {
                    return Consts::Maces_Category();
                } else if (Form::Has_Keyword(form, keywords->WeapTypeStaff) ||
                           Form::Has_Keyword(form, keywords->VendorItemStaff)) {
                    return Consts::Staves_Category();
                } else {
                    return Consts::Weapons_Category();
                }
            }
            case (kFormType_Armor):
            {
                if (Form::Has_Keyword(form, keywords->ArmorLight)) {
                    return Consts::Light_Armor_Category();
                } else if (Form::Has_Keyword(form, keywords->ArmorHeavy)) {
                    return Consts::Heavy_Armor_Category();
                } else if (Form::Has_Keyword(form, keywords->ArmorShield)) {
                    return Consts::Shields_Category();
                } else if (Form::Has_Keyword(form, keywords->ArmorJewelry)) {
                    return Consts::Jewelry_Category();
                } else if (Form::Has_Keyword(form, keywords->ArmorClothing)) {
                    return Consts::Clothes_Category();
                } else if (Form::Has_Keyword(form, keywords->ArmorBoots) ||
                           Form::Has_Keyword(form, keywords->ArmorCuirass) ||
                           Form::Has_Keyword(form, keywords->ArmorGauntlets) ||
                           Form::Has_Keyword(form, keywords->ArmorHelmet)) {
                    return Consts::Light_Armor_Category();
                } else if (Form::Has_Keyword(form, keywords->VendorItemJewelry) ||
                           Form::Has_Keyword(form, keywords->ClothingCirclet) ||
                           Form::Has_Keyword(form, keywords->ClothingNecklace) ||
                           Form::Has_Keyword(form, keywords->ClothingRing)) {
                    return Consts::Jewelry_Category();
                } else {
                    return Consts::Clothes_Category();
                }
            }
            case (kFormType_Potion):
            {
                if (Form::Has_Keyword(form, keywords->VendorItemPotion)) {
                    return Consts::Potions_Category();
                } else if (Form::Has_Keyword(form, keywords->VendorItemPoison)) {
                    return Consts::Poisons_Category();
                } else {
                    return Consts::Food_Category();
                }
            }
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
    }

    Reference_t* Get_NPCP_Custom_Category(Form_t* form)
    {
        static constexpr size_t MAX_CUSTOM_CATEGORIES = 16;
        static Reference_t* custom_categories[MAX_CUSTOM_CATEGORIES] = {
            Consts::Custom_00_Category(),
            Consts::Custom_01_Category(),
            Consts::Custom_02_Category(),
            Consts::Custom_03_Category(),
            Consts::Custom_04_Category(),
            Consts::Custom_05_Category(),
            Consts::Custom_06_Category(),
            Consts::Custom_07_Category(),
            Consts::Custom_08_Category(),
            Consts::Custom_09_Category(),
            Consts::Custom_10_Category(),
            Consts::Custom_11_Category(),
            Consts::Custom_12_Category(),
            Consts::Custom_13_Category(),
            Consts::Custom_14_Category(),
            Consts::Custom_15_Category(),
        };

        NPCP_ASSERT(form);

        for (size_t idx = 0; idx < MAX_CUSTOM_CATEGORIES; idx += 1) {
            Reference_t* custom_category = custom_categories[idx];
            if (custom_category && Object_Ref::Contains_Form(custom_category, form)) {
                return custom_category;
            }
        }

        return nullptr;
    }

    void Update_NPCP_Categories()
    {
        Object_Ref::Categorize(Consts::Input_Category());

        Object_Ref::Categorize(Consts::Swords_Category(), true);
        Object_Ref::Categorize(Consts::Greatswords_Category(), true);
        Object_Ref::Categorize(Consts::Waraxes_Category(), true);
        Object_Ref::Categorize(Consts::Battleaxes_Category(), true);
        Object_Ref::Categorize(Consts::Maces_Category(), true);
        Object_Ref::Categorize(Consts::Warhammers_Category(), true);
        Object_Ref::Categorize(Consts::Daggers_Category(), true);
        Object_Ref::Categorize(Consts::Staves_Category(), true);
        Object_Ref::Categorize(Consts::Bows_Category(), true);
        Object_Ref::Categorize(Consts::Ammo_Category(), true);
        Object_Ref::Categorize(Consts::Weapons_Category(), true);

        Object_Ref::Categorize(Consts::Light_Armor_Category(), true);
        Object_Ref::Categorize(Consts::Heavy_Armor_Category(), true);
        Object_Ref::Categorize(Consts::Shields_Category(), true);
        Object_Ref::Categorize(Consts::Jewelry_Category(), true);
        Object_Ref::Categorize(Consts::Clothes_Category(), true);

        Object_Ref::Categorize(Consts::Potions_Category(), true);
        Object_Ref::Categorize(Consts::Poisons_Category(), true);
        Object_Ref::Categorize(Consts::Ingredients_Category(), true);
        Object_Ref::Categorize(Consts::Food_Category(), true);

        Object_Ref::Categorize(Consts::Soulgems_Category(), true);
        Object_Ref::Categorize(Consts::Scrolls_Category(), true);
        Object_Ref::Categorize(Consts::Metals_Category(), true);
        Object_Ref::Categorize(Consts::Leather_Category(), true);
        Object_Ref::Categorize(Consts::Gems_Category(), true);
        Object_Ref::Categorize(Consts::Clutter_Category(), true);
        Object_Ref::Categorize(Consts::Keys_Category(), true);
        Object_Ref::Categorize(Consts::Misc_Category(), true);

        Object_Ref::Categorize(Consts::Spell_Tomes_Category(), true);
        Object_Ref::Categorize(Consts::Recipes_Category(), true);
        Object_Ref::Categorize(Consts::A_Books_Category(), true);
        Object_Ref::Categorize(Consts::B_Books_Category(), true);
        Object_Ref::Categorize(Consts::C_Books_Category(), true);
        Object_Ref::Categorize(Consts::D_Books_Category(), true);
        Object_Ref::Categorize(Consts::E_Books_Category(), true);
        Object_Ref::Categorize(Consts::F_Books_Category(), true);
        Object_Ref::Categorize(Consts::G_Books_Category(), true);
        Object_Ref::Categorize(Consts::H_Books_Category(), true);
        Object_Ref::Categorize(Consts::I_Books_Category(), true);
        Object_Ref::Categorize(Consts::J_Books_Category(), true);
        Object_Ref::Categorize(Consts::K_Books_Category(), true);
        Object_Ref::Categorize(Consts::L_Books_Category(), true);
        Object_Ref::Categorize(Consts::M_Books_Category(), true);
        Object_Ref::Categorize(Consts::N_Books_Category(), true);
        Object_Ref::Categorize(Consts::O_Books_Category(), true);
        Object_Ref::Categorize(Consts::P_Books_Category(), true);
        Object_Ref::Categorize(Consts::Q_Books_Category(), true);
        Object_Ref::Categorize(Consts::R_Books_Category(), true);
        Object_Ref::Categorize(Consts::S_Books_Category(), true);
        Object_Ref::Categorize(Consts::T_Books_Category(), true);
        Object_Ref::Categorize(Consts::U_Books_Category(), true);
        Object_Ref::Categorize(Consts::V_Books_Category(), true);
        Object_Ref::Categorize(Consts::W_Books_Category(), true);
        Object_Ref::Categorize(Consts::X_Books_Category(), true);
        Object_Ref::Categorize(Consts::Y_Books_Category(), true);
        Object_Ref::Categorize(Consts::Z_Books_Category(), true);
        Object_Ref::Categorize(Consts::Books_Category(), true);
    }

}}
