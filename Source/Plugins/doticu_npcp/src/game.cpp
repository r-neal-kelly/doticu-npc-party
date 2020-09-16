/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"

#include "consts.h"
#include "form.h"
#include "game.h"
#include "object_ref.h"
#include "string2.h"
#include "types.h"
#include "utils.h"

namespace doticu_npcp { namespace Game {

    inline static DataHandler* Data_Handler()
    {
        static DataHandler* data_handler = DataHandler::GetSingleton();
        NPCP_ASSERT(data_handler != nullptr);
        return data_handler;
    }

    tArray<Reference_t*>& References()
    {
        return *reinterpret_cast<tArray<Reference_t*>*>(&Data_Handler()->arrREFR);
    }

    Form_t* Form(UInt32 form_id)
    {
        return LookupFormByID(form_id);
    }

    Form_t* Mod_Form(const char* mod_name, UInt32 lower_form_id)
    {
        const ModInfo* mod_info = Data_Handler()->LookupModByName(mod_name);
        if (mod_info) {
            return LookupFormByID(mod_info->GetFormID(lower_form_id));
        } else {
            return nullptr;
        }
    }

    Form_t* Skyrim_Form(UInt32 lower_form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("Skyrim.esm");
        NPCP_ASSERT(mod_info != nullptr);
        return LookupFormByID(mod_info->GetFormID(lower_form_id));
    }

    Form_t* Skyrim_Update_Form(UInt32 lower_form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("Update.esm");
        NPCP_ASSERT(mod_info != nullptr);
        return LookupFormByID(mod_info->GetFormID(lower_form_id));
    }

    Form_t* Dawnguard_Form(UInt32 lower_form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("Dawnguard.esm");
        NPCP_ASSERT(mod_info != nullptr);
        return LookupFormByID(mod_info->GetFormID(lower_form_id));
    }

    Form_t* Hearthfires_Form(UInt32 lower_form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("HearthFires.esm");
        NPCP_ASSERT(mod_info != nullptr);
        return LookupFormByID(mod_info->GetFormID(lower_form_id));
    }

    Form_t* Dragonborn_Form(UInt32 lower_form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("Dragonborn.esm");
        NPCP_ASSERT(mod_info != nullptr);
        return LookupFormByID(mod_info->GetFormID(lower_form_id));
    }
    
    Form_t* NPCP_Form(UInt32 lower_form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("doticu_npc_party.esp");
        NPCP_ASSERT(mod_info != nullptr);
        return LookupFormByID(mod_info->GetFormID(lower_form_id));
    }

    Bool_t Is_Mod_Installed(const char* mod_name)
    {
        const ModInfo* mod_info = Data_Handler()->LookupModByName(mod_name);
        return mod_info && mod_info->IsActive();
    }

    Bool_t Is_Better_Vampires_Installed()
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("Better Vampires.esp");
        return mod_info && mod_info->IsActive();
    }

    Bool_t Is_Form_In_Mod(UInt32 form_id, const char* mod_name)
    {
        const ModInfo* mod_info = Data_Handler()->LookupModByName(mod_name);
        if (mod_info) {
            return mod_info->IsFormInMod(form_id);
        } else {
            return false;
        }
    }

    Bool_t Is_NPCP_Form(UInt32 form_id)
    {
        static const ModInfo* mod_info = Data_Handler()->LookupModByName("doticu_npc_party.esp");
        NPCP_ASSERT(mod_info != nullptr);
        return mod_info->IsFormInMod(form_id);
    }

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names()
    {
        VMResultArray<BSFixedString> results;

        DataHandler* data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            return results;
        }

        TESForm* form_voice = NULL;
        BGSVoiceType* voice = NULL;
        for (u64 idx = 0, size = data_handler->arrVTYP.count; idx < size; idx += 1) {
            data_handler->arrVTYP.GetNthItem(idx, form_voice);
            voice = (BGSVoiceType*)form_voice;

            if (voice->formID >= 0x05000000) {
                break;
            }

            const char* str_voice = voice->editorId.Get();
            if (String2::Contains(str_voice, "Male")) {
                results.push_back(BSFixedString(str_voice));
            }
        }

        return results;
    }

    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names()
    {
        VMResultArray<BSFixedString> results;

        DataHandler* data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            return results;
        }

        TESForm* form_voice = NULL;
        BGSVoiceType* voice = NULL;
        for (u64 idx = 0, size = data_handler->arrVTYP.count; idx < size; idx += 1) {
            data_handler->arrVTYP.GetNthItem(idx, form_voice);
            voice = (BGSVoiceType*)form_voice;

            if (voice->formID >= 0x05000000) {
                break;
            }

            const char* str_voice = voice->editorId.Get();
            if (String2::Contains(str_voice, "Female")) {
                results.push_back(BSFixedString(str_voice));
            }
        }

        return results;
    }

    BGSVoiceType* Get_Voice_By_Name(BSFixedString str_name)
    {
        DataHandler* data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            return NULL;
        }

        TESForm* form_voice = NULL;
        BGSVoiceType* voice = NULL;
        for (u64 idx = 0, size = data_handler->arrVTYP.count; idx < size; idx += 1) {
            data_handler->arrVTYP.GetNthItem(idx, form_voice);
            voice = (BGSVoiceType*)form_voice;

            if (String2::Is_Same(voice->editorId.Get(), str_name.data)) {
                return voice;
            }
        }

        return NULL;
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

    static NPCP_Category_Keywords *Get_NPCP_Category_Keywords() {
        static NPCP_Category_Keywords keywords;
        static bool is_created = false;

        if (is_created) {
            return &keywords;
        }

        DataHandler *data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            _MESSAGE("Game::Get_NPCP_Category_Keywords: Unable to get data_handler.");
            return NULL;
        }

        #define Set_NPCP_Category_Keyword(FIELD, FORM_ID)                                           \
        M                                                                                           \
            TESForm *form = LookupFormByID(FORM_ID);                                                \
            if (form) {                                                                             \
                FIELD = DYNAMIC_CAST(form, TESForm, BGSKeyword);                                    \
            } else {                                                                                \
                _MESSAGE("Game::Get_NPCP_Category_Keywords: Unable to get category '%s'.", #FIELD); \
                return NULL;                                                                        \
            }                                                                                       \
        W

        Set_NPCP_Category_Keyword(keywords.WeapTypeSword,           0x0001E711);
        Set_NPCP_Category_Keyword(keywords.WeapTypeGreatsword,      0x0006D931);
        Set_NPCP_Category_Keyword(keywords.WeapTypeWarAxe,          0x0001E712);
        Set_NPCP_Category_Keyword(keywords.WeapTypeBattleaxe,       0x0006D932);
        Set_NPCP_Category_Keyword(keywords.WeapTypeMace,            0x0001E714);
        Set_NPCP_Category_Keyword(keywords.WeapTypeWarhammer,       0x0006D930);
        Set_NPCP_Category_Keyword(keywords.WeapTypeDagger,          0x0001E713);
        Set_NPCP_Category_Keyword(keywords.WeapTypeBow,             0x0001E715);
        Set_NPCP_Category_Keyword(keywords.WeapTypeStaff,           0x0001E716);
        Set_NPCP_Category_Keyword(keywords.VendorItemStaff,         0x000937A4);

        Set_NPCP_Category_Keyword(keywords.ArmorLight,              0x0006BBD3);
        Set_NPCP_Category_Keyword(keywords.ArmorHeavy,              0x0006BBD2);
        Set_NPCP_Category_Keyword(keywords.ArmorShield,             0x000965B2);
        Set_NPCP_Category_Keyword(keywords.ArmorJewelry,            0x0006BBE9);
        Set_NPCP_Category_Keyword(keywords.ArmorClothing,           0x0006BBE8);
        Set_NPCP_Category_Keyword(keywords.ArmorBoots,              0x0006C0ED);
        Set_NPCP_Category_Keyword(keywords.ArmorCuirass,            0x0006C0EC);
        Set_NPCP_Category_Keyword(keywords.ArmorGauntlets,          0x0006C0EF);
        Set_NPCP_Category_Keyword(keywords.ArmorHelmet,             0x0006C0EE);
        Set_NPCP_Category_Keyword(keywords.VendorItemJewelry,       0x0008F95A);
        Set_NPCP_Category_Keyword(keywords.ClothingCirclet,         0x0010CD08);
        Set_NPCP_Category_Keyword(keywords.ClothingNecklace,        0x0010CD0A);
        Set_NPCP_Category_Keyword(keywords.ClothingRing,            0x0010CD09);

        Set_NPCP_Category_Keyword(keywords.VendorItemPotion,        0x0008CDEC);
        Set_NPCP_Category_Keyword(keywords.VendorItemPoison,        0x0008CDED);

        Set_NPCP_Category_Keyword(keywords.VendorItemSpellTome,     0x000937A5);
        Set_NPCP_Category_Keyword(keywords.VendorItemRecipe,        0x000F5CB0);

        Set_NPCP_Category_Keyword(keywords.VendorItemOreIngot,      0x000914EC);
        Set_NPCP_Category_Keyword(keywords.VendorItemAnimalHide,    0x000914EA);
        Set_NPCP_Category_Keyword(keywords.VendorItemGem,           0x000914ED);

        is_created = true;

        return &keywords;

        #undef Set_NPCP_Category_Keyword
    }

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

namespace doticu_npcp { namespace Game { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
