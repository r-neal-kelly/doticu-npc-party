/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"

#include "form.h"
#include "game.h"
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

    struct NPCP_Categories {
        TESObjectREFR *swords; // kFormType_Weapon
        TESObjectREFR *greatswords;
        TESObjectREFR *waraxes;
        TESObjectREFR *battleaxes;
        TESObjectREFR *maces;
        TESObjectREFR *warhammers;
        TESObjectREFR *daggers;
        TESObjectREFR *bows;
        TESObjectREFR *staves;
        TESObjectREFR *weapons;

        TESObjectREFR *light_armor; // kFormType_Armor
        TESObjectREFR *heavy_armor;
        TESObjectREFR *shields;
        TESObjectREFR *jewelry;
        TESObjectREFR *clothes;

        TESObjectREFR *potions; // kFormType_Potion
        TESObjectREFR *poisons;
        TESObjectREFR *food;

        TESObjectREFR *spell_tomes; // kFormType_Book
        TESObjectREFR *recipes;
        TESObjectREFR *books[27];

        TESObjectREFR *metals; // kFormType_Misc
        TESObjectREFR *leather;
        TESObjectREFR *gems;
        TESObjectREFR *clutter;

        TESObjectREFR *ammo; // kFormType_Ammo

        TESObjectREFR *ingredients; // kFormType_Ingredient

        TESObjectREFR *scrolls; // kFormType_ScrollItem

        TESObjectREFR *soulgems; // kFormType_SoulGem

        TESObjectREFR *keys; // kFormType_Key

        TESObjectREFR *others;
    };

    static NPCP_Categories *Get_NPCP_Categories() {
        static NPCP_Categories categories;
        static bool is_created = false;

        if (is_created) {
            return &categories;
        }

        DataHandler *data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            _MESSAGE("Game::Get_NPCP_Categories: Unable to get data_handler.");
            return NULL;
        }

        const ModInfo *mod_info = data_handler->LookupModByName("doticu_npc_party.esp");
        if (!mod_info) {
            _MESSAGE("Game::Get_NPCP_Categories: Unable to get mod_info.");
            return NULL;
        }

        #define Set_NPCP_Category(FIELD, LOWER_FORM_ID)                                         \
        M                                                                                       \
            TESForm *form = LookupFormByID(mod_info->GetFormID(LOWER_FORM_ID));                 \
            if (form) {                                                                         \
                FIELD = DYNAMIC_CAST(form, TESForm, TESObjectREFR);                             \
            } else {                                                                            \
                _MESSAGE("Game::Get_NPCP_Categories: Unable to get category '%s'.", #FIELD);    \
                return NULL;                                                                    \
            }                                                                                   \
        W

        Set_NPCP_Category(categories.swords,        0x30D20A);
        Set_NPCP_Category(categories.greatswords,   0x30D20B);
        Set_NPCP_Category(categories.waraxes,       0x30D20C);
        Set_NPCP_Category(categories.battleaxes,    0x30D20D);
        Set_NPCP_Category(categories.maces,         0x30D20E);
        Set_NPCP_Category(categories.warhammers,    0x30D20F);
        Set_NPCP_Category(categories.daggers,       0x30D210);
        Set_NPCP_Category(categories.bows,          0x30D211);
        Set_NPCP_Category(categories.staves,        0x30D212);
        Set_NPCP_Category(categories.weapons,       0x30D213);

        Set_NPCP_Category(categories.light_armor,   0x30D214);
        Set_NPCP_Category(categories.heavy_armor,   0x30D215);
        Set_NPCP_Category(categories.shields,       0x30D216);
        Set_NPCP_Category(categories.jewelry,       0x30D217);
        Set_NPCP_Category(categories.clothes,       0x30D218);

        Set_NPCP_Category(categories.potions,       0x30D219);
        Set_NPCP_Category(categories.poisons,       0x30D21A);
        Set_NPCP_Category(categories.food,          0x30D21B);

        Set_NPCP_Category(categories.spell_tomes,   0x30D21C);
        Set_NPCP_Category(categories.recipes,       0x30D21D);
        Set_NPCP_Category(categories.books[0],      0x30D21E);
        Set_NPCP_Category(categories.books[1],      0x30D21F);
        Set_NPCP_Category(categories.books[2],      0x30D220);
        Set_NPCP_Category(categories.books[3],      0x30D221);
        Set_NPCP_Category(categories.books[4],      0x30D222);
        Set_NPCP_Category(categories.books[5],      0x30D223);
        Set_NPCP_Category(categories.books[6],      0x30D224);
        Set_NPCP_Category(categories.books[7],      0x30D225);
        Set_NPCP_Category(categories.books[8],      0x30D226);
        Set_NPCP_Category(categories.books[9],      0x30D227);
        Set_NPCP_Category(categories.books[10],     0x30D228);
        Set_NPCP_Category(categories.books[11],     0x30D229);
        Set_NPCP_Category(categories.books[12],     0x30D22A);
        Set_NPCP_Category(categories.books[13],     0x30D22B);
        Set_NPCP_Category(categories.books[14],     0x30D22C);
        Set_NPCP_Category(categories.books[15],     0x30D22D);
        Set_NPCP_Category(categories.books[16],     0x30D22E);
        Set_NPCP_Category(categories.books[17],     0x30D22F);
        Set_NPCP_Category(categories.books[18],     0x30D230);
        Set_NPCP_Category(categories.books[19],     0x30D231);
        Set_NPCP_Category(categories.books[20],     0x30D232);
        Set_NPCP_Category(categories.books[21],     0x30D233);
        Set_NPCP_Category(categories.books[22],     0x30D234);
        Set_NPCP_Category(categories.books[23],     0x30D235);
        Set_NPCP_Category(categories.books[24],     0x30D236);
        Set_NPCP_Category(categories.books[25],     0x30D237);
        Set_NPCP_Category(categories.books[26],     0x30D238);

        Set_NPCP_Category(categories.metals,        0x30D239);
        Set_NPCP_Category(categories.leather,       0x30D23A);
        Set_NPCP_Category(categories.gems,          0x30D23B);
        Set_NPCP_Category(categories.clutter,       0x30D23C);

        Set_NPCP_Category(categories.ammo,          0x30D23D);

        Set_NPCP_Category(categories.ingredients,   0x30D23E);

        Set_NPCP_Category(categories.scrolls,       0x30D23F);

        Set_NPCP_Category(categories.soulgems,      0x30D240);

        Set_NPCP_Category(categories.keys,          0x30D241);

        Set_NPCP_Category(categories.others,        0x30D242);

        is_created = true;

        return &categories;

        #undef Set_NPCP_Category
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

    TESObjectREFR *Get_NPCP_Category(TESForm *form) {
        if (!form) {
            return NULL;
        }

        NPCP_Categories *categories = Get_NPCP_Categories();
        if (!categories) {
            _MESSAGE("Game::Get_NPCP_Category: Missing categories.");
            return NULL;
        }

        NPCP_Category_Keywords *keywords = Get_NPCP_Category_Keywords();
        if (!keywords) {
            _MESSAGE("Game::Get_NPCP_Category: Missing keywords.");
            return NULL;
        }

        switch (form->formType) {
            case (kFormType_Weapon): {
                if (Form::Has_Keyword(form, keywords->WeapTypeBow)) {
                    return categories->bows;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeDagger)) {
                    return categories->daggers;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeGreatsword)) {
                    return categories->greatswords;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeSword)) {
                    return categories->swords;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeBattleaxe)) {
                    return categories->battleaxes;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeWarAxe)) {
                    return categories->waraxes;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeWarhammer)) {
                    return categories->warhammers;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeMace)) {
                    return categories->maces;
                } else if (Form::Has_Keyword(form, keywords->WeapTypeStaff) ||
                           Form::Has_Keyword(form, keywords->VendorItemStaff)) {
                    return categories->staves;
                } else {
                    return categories->weapons;
                }
            }
            case (kFormType_Armor): {
                if (Form::Has_Keyword(form, keywords->ArmorLight)) {
                    return categories->light_armor;
                } else if (Form::Has_Keyword(form, keywords->ArmorHeavy)) {
                    return categories->heavy_armor;
                } else if (Form::Has_Keyword(form, keywords->ArmorShield)) {
                    return categories->shields;
                } else if (Form::Has_Keyword(form, keywords->ArmorJewelry)) {
                    return categories->jewelry;
                } else if (Form::Has_Keyword(form, keywords->ArmorClothing)) {
                    return categories->clothes;
                } else if (Form::Has_Keyword(form, keywords->ArmorBoots) ||
                           Form::Has_Keyword(form, keywords->ArmorCuirass) ||
                           Form::Has_Keyword(form, keywords->ArmorGauntlets) ||
                           Form::Has_Keyword(form, keywords->ArmorHelmet)) {
                    return categories->light_armor;
                } else if (Form::Has_Keyword(form, keywords->VendorItemJewelry) ||
                           Form::Has_Keyword(form, keywords->ClothingCirclet) ||
                           Form::Has_Keyword(form, keywords->ClothingNecklace) ||
                           Form::Has_Keyword(form, keywords->ClothingRing)) {
                    return categories->jewelry;
                } else {
                    return categories->clothes;
                }
            }
            case (kFormType_Potion): {
                if (Form::Has_Keyword(form, keywords->VendorItemPotion)) {
                    return categories->potions;
                } else if (Form::Has_Keyword(form, keywords->VendorItemPoison)) {
                    return categories->poisons;
                } else {
                    return categories->food;
                }
            }
            case (kFormType_Book): {
                if (Form::Has_Keyword(form, keywords->VendorItemSpellTome)) {
                    return categories->spell_tomes;
                } else if (Form::Has_Keyword(form, keywords->VendorItemRecipe)) {
                    return categories->recipes;
                } else {
                    const char chr = tolower(Form::Get_Name(form)[0]);
                    s64 idx_chars = chr >= 'a' && chr <= 'z' ? chr - 'a' : -1;
                    if (idx_chars > -1 && idx_chars < 26) {
                        return categories->books[idx_chars];
                    } else {
                        return categories->books[26];
                    }
                }
            }
            case (kFormType_Misc): {
                if (Form::Has_Keyword(form, keywords->VendorItemOreIngot)) {
                    return categories->metals;
                } else if (Form::Has_Keyword(form, keywords->VendorItemAnimalHide)) {
                    return categories->leather;
                } else if (Form::Has_Keyword(form, keywords->VendorItemGem)) {
                    return categories->gems;
                } else {
                    return categories->clutter;
                }
            }
            case (kFormType_Ammo): {
                return categories->ammo;
            }
            case (kFormType_Ingredient): {
                return categories->ingredients;
            }
            case (kFormType_ScrollItem): {
                return categories->scrolls;
            }
            case (kFormType_SoulGem): {
                return categories->soulgems;
            }
            case (kFormType_Key): {
                return categories->keys;
            }
            default: {
                return categories->others;
            }
        }
    }

}}

namespace doticu_npcp { namespace Game { namespace Exports {

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names(StaticFunctionTag *) {
        return Game::Get_Male_Vanilla_Voice_Names();
    }

    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names(StaticFunctionTag *) {
        return Game::Get_Female_Vanilla_Voice_Names();
    }

    BGSVoiceType *Get_Voice_By_Name(StaticFunctionTag *, BSFixedString str_name) {
        return Game::Get_Voice_By_Name(str_name);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <StaticFunctionTag, VMResultArray<BSFixedString>>(
                "Game_Get_Male_Vanilla_Voice_Names",
                "doticu_npcp",
                Exports::Get_Male_Vanilla_Voice_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <StaticFunctionTag, VMResultArray<BSFixedString>>(
                "Game_Get_Female_Vanilla_Voice_Names",
                "doticu_npcp",
                Exports::Get_Female_Vanilla_Voice_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, BGSVoiceType *, BSFixedString>(
                "Game_Get_Voice_By_Name",
                "doticu_npcp",
                Exports::Get_Voice_By_Name,
                registry)
        );

        return true;
    }

}}}
