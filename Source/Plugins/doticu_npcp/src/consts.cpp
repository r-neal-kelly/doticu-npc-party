/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "game.h"
#include "utils.h"

#include "papyrus.inl"

/*
    We us macros in this module, because we want the
    assert to show us which variable is actually nullptr,
    instead of it being ambiguous through a template.
*/

namespace doticu_npcp { namespace Consts {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_consts");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Consts_t* Self()
    {
        return static_cast<Consts_t*>(Static_Data_Quest());
    }

    Object_t* Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    #define FORM(MOD_, TYPE_, MOD_ID_)              \
    {                                               \
        static TYPE_* value = static_cast<TYPE_*>   \
            (Game::MOD_(MOD_ID_));                  \
        NPCP_ASSERT(value);                         \
        return value;                               \
    }

    enum Skyrim_Forms {
        ACTOR_PLAYER                        = 0x000014,

        FACTION_BARD_SINGER_NO_AUTOSTART    = 0x0163FA,
        FACTION_CURRENT_FOLLOWER            = 0x05C84E,
        FACTION_PLAYER_FOLLOWER             = 0x084D1B,
        FACTION_POTENTIAL_FOLLOWER          = 0x05C84D,
        FACTION_WI_NO_BODY_CLEANUP          = 0x09653A,

        GLOBAL_PLAYER_FOLLOWER_COUNT        = 0x0BCC98,

        KEYWORD_MAGIC_DAMAGE_FIRE           = 0x01CEAD,
        KEYWORD_MAGIC_DAMAGE_FROST          = 0x01CEAE,
        KEYWORD_MAGIC_DAMAGE_SHOCK          = 0x01CEAF,
        KEYWORD_MAGIC_VAMPIRE_DRAIN         = 0x101BDE,

        QUEST_DIALOGUE_FOLLOWER             = 0x0750BA,

        STATIC_MARKER_X                     = 0x00003B,
    };

    #define SKYRIM_FORM(TYPE_, MOD_ID_) FORM(Skyrim_Form, TYPE_, MOD_ID_);

    Actor_t* Player_Actor() SKYRIM_FORM(Actor_t, ACTOR_PLAYER);

    Faction_t* No_Bard_Singer_Autostart_Faction() SKYRIM_FORM(Faction_t, FACTION_BARD_SINGER_NO_AUTOSTART);
    Faction_t* Current_Follower_Faction() SKYRIM_FORM(Faction_t, FACTION_CURRENT_FOLLOWER);
    Faction_t* Player_Follower_Faction() SKYRIM_FORM(Faction_t, FACTION_PLAYER_FOLLOWER);
    Faction_t* Potential_Follower_Faction() SKYRIM_FORM(Faction_t, FACTION_POTENTIAL_FOLLOWER);
    Faction_t* WI_No_Body_Cleanup_Faction() SKYRIM_FORM(Faction_t, FACTION_WI_NO_BODY_CLEANUP);

    Global_t* Player_Follower_Count_Global() SKYRIM_FORM(Global_t, GLOBAL_PLAYER_FOLLOWER_COUNT);

    Keyword_t* Fire_Damage_Magic_Keyword() SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_FIRE);
    Keyword_t* Frost_Damage_Magic_Keyword() SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_FROST);
    Keyword_t* Shock_Damage_Magic_Keyword() SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_SHOCK);
    Keyword_t* Vampire_Drain_Magic_Keyword() SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_VAMPIRE_DRAIN);

    Quest_t* Follower_Dialogue_Quest() SKYRIM_FORM(Quest_t, QUEST_DIALOGUE_FOLLOWER);

    Static_t* X_Marker_Static() SKYRIM_FORM(Static_t, STATIC_MARKER_X);

    #undef SKYRIM_FORM

    enum Dawnguard_Forms {
        FACTION_DLC1_THRALL                 = 0x0162F7,
        FACTION_DLC1_VAMPIRE_FEED_NO_CRIME  = 0x014CBD,
    };

    #define DAWNGUARD_FORM(TYPE_, MOD_ID_) FORM(Dawnguard_Form, TYPE_, MOD_ID_);

    Faction_t* DLC1_Thrall_Faction() DAWNGUARD_FORM(Faction_t, FACTION_DLC1_THRALL);
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction() DAWNGUARD_FORM(Faction_t, FACTION_DLC1_VAMPIRE_FEED_NO_CRIME);

    #undef DAWNGUARD_FORM

    enum NPCP_Forms {
        ARMOR_BLANK                         = 0x1EF2A5,

        FACTION_HORSE                       = 0x354111,
        FACTION_MEMBER                      = 0x091154,

        FORMLIST_MARKERS_SETTLER            = 0x00B46E,

        MISC_TOKEN_BANISHED                 = 0x003DFD,
        MISC_TOKEN_CLONE                    = 0x003DFC,
        MISC_TOKEN_DISPLAY                  = 0x13D7AC,
        MISC_TOKEN_FOLLOWER                 = 0x000D84,
        MISC_TOKEN_FOLLOWER_SNEAK           = 0x000D85,
        MISC_TOKEN_GENERIC                  = 0x003DFE,
        MISC_TOKEN_GREETER                  = 0x057384,
        MISC_TOKEN_IMMOBILE                 = 0x000D77,
        MISC_TOKEN_MANNEQUIN                = 0x264F42,
        MISC_TOKEN_MEMBER                   = 0x000D75,
        MISC_TOKEN_MOVEE                    = 0x1612B3,
        MISC_TOKEN_PARALYZED                = 0x12E4A7,
        MISC_TOKEN_REANIMATED               = 0x1E4E9D,
        MISC_TOKEN_RETREATER                = 0x2F3D00,
        MISC_TOKEN_SADDLER                  = 0x34F000,
        MISC_TOKEN_SETTLER                  = 0x000D73,
        MISC_TOKEN_STYLE_ARCHER             = 0x0A045E,
        MISC_TOKEN_STYLE_COWARD             = 0x2D56F3,
        MISC_TOKEN_STYLE_DEFAULT            = 0x0A045D,
        MISC_TOKEN_STYLE_MAGE               = 0x0A045F,
        MISC_TOKEN_STYLE_WARRIOR            = 0x0A0460,
        MISC_TOKEN_THRALL                   = 0x011E90,
        MISC_TOKEN_VITALITY_ESSENTIAL       = 0x0A0459,
        MISC_TOKEN_VITALITY_INVULNERABLE    = 0x0A045C,
        MISC_TOKEN_VITALITY_MORTAL          = 0x0A045B,
        MISC_TOKEN_VITALITY_PROTECTED       = 0x0A045A,
        MISC_VECTOR_FORM                    = 0x15C1B2,

        OUTFIT_EMPTY                        = 0x0C3C64,

        QUEST_DATA_STATIC                   = 0x0FBA9A,
        QUEST_DATA_DYNAMIC                  = 0x003DFF,
        QUEST_FUNCS                         = 0x005384,
        QUEST_MEMBERS                       = 0x00184C,
        QUEST_FOLLOWERS                     = 0x000D83,
        QUEST_CONTROL                       = 0x000D7F,

        REFERENCE_CATEGORY_INPUT            = 0x395E55,
        REFERENCE_CATEGORY_SWORDS           = 0x30D20A,
        REFERENCE_CATEGORY_GREATSWORDS      = 0x30D20B,
        REFERENCE_CATEGORY_WARAXES          = 0x30D20C,
        REFERENCE_CATEGORY_BATTLEAXES       = 0x30D20D,
        REFERENCE_CATEGORY_MACES            = 0x30D20E,
        REFERENCE_CATEGORY_WARHAMMERS       = 0x30D20F,
        REFERENCE_CATEGORY_DAGGERS          = 0x30D210,
        REFERENCE_CATEGORY_STAVES           = 0x30D212,
        REFERENCE_CATEGORY_BOWS             = 0x30D211,
        REFERENCE_CATEGORY_AMMO             = 0x30D23D,
        REFERENCE_CATEGORY_WEAPONS          = 0x30D213,
        REFERENCE_CATEGORY_LIGHT_ARMOR      = 0x30D214,
        REFERENCE_CATEGORY_HEAVY_ARMOR      = 0x30D215,
        REFERENCE_CATEGORY_SHIELDS          = 0x30D216,
        REFERENCE_CATEGORY_JEWELRY          = 0x30D217,
        REFERENCE_CATEGORY_CLOTHES          = 0x30D218,
        REFERENCE_CATEGORY_POTIONS          = 0x30D219,
        REFERENCE_CATEGORY_POISONS          = 0x30D21A,
        REFERENCE_CATEGORY_INGREDIENTS      = 0x30D23E,
        REFERENCE_CATEGORY_FOOD             = 0x30D21B,
        REFERENCE_CATEGORY_SOULGEMS         = 0x30D240,
        REFERENCE_CATEGORY_SCROLLS          = 0x30D23F,
        REFERENCE_CATEGORY_METALS           = 0x30D239,
        REFERENCE_CATEGORY_LEATHER          = 0x30D23A,
        REFERENCE_CATEGORY_GEMS             = 0x30D23B,
        REFERENCE_CATEGORY_CLUTTER          = 0x30D23C,
        REFERENCE_CATEGORY_KEYS             = 0x30D241,
        REFERENCE_CATEGORY_MISC             = 0x30D242,
        REFERENCE_CATEGORY_SPELL_TOMES      = 0x30D21C,
        REFERENCE_CATEGORY_RECIPES          = 0x30D21D,
        REFERENCE_CATEGORY_BOOKS_A          = 0x30D21E,
        REFERENCE_CATEGORY_BOOKS_B          = 0x30D21F,
        REFERENCE_CATEGORY_BOOKS_C          = 0x30D220,
        REFERENCE_CATEGORY_BOOKS_D          = 0x30D221,
        REFERENCE_CATEGORY_BOOKS_E          = 0x30D222,
        REFERENCE_CATEGORY_BOOKS_F          = 0x30D223,
        REFERENCE_CATEGORY_BOOKS_G          = 0x30D224,
        REFERENCE_CATEGORY_BOOKS_H          = 0x30D225,
        REFERENCE_CATEGORY_BOOKS_I          = 0x30D226,
        REFERENCE_CATEGORY_BOOKS_J          = 0x30D227,
        REFERENCE_CATEGORY_BOOKS_K          = 0x30D228,
        REFERENCE_CATEGORY_BOOKS_L          = 0x30D229,
        REFERENCE_CATEGORY_BOOKS_M          = 0x30D22A,
        REFERENCE_CATEGORY_BOOKS_N          = 0x30D22B,
        REFERENCE_CATEGORY_BOOKS_O          = 0x30D22C,
        REFERENCE_CATEGORY_BOOKS_P          = 0x30D22D,
        REFERENCE_CATEGORY_BOOKS_Q          = 0x30D22E,
        REFERENCE_CATEGORY_BOOKS_R          = 0x30D22F,
        REFERENCE_CATEGORY_BOOKS_S          = 0x30D230,
        REFERENCE_CATEGORY_BOOKS_T          = 0x30D231,
        REFERENCE_CATEGORY_BOOKS_U          = 0x30D232,
        REFERENCE_CATEGORY_BOOKS_V          = 0x30D233,
        REFERENCE_CATEGORY_BOOKS_W          = 0x30D234,
        REFERENCE_CATEGORY_BOOKS_X          = 0x30D235,
        REFERENCE_CATEGORY_BOOKS_Y          = 0x30D236,
        REFERENCE_CATEGORY_BOOKS_Z          = 0x30D237,
        REFERENCE_CATEGORY_BOOKS            = 0x30D238,
        REFERENCE_MARKER_STORAGE            = 0x114F9D,

        WEAPON_BLANK                        = 0x0C8D65,
    };

    #define NPCP_FORM(TYPE_, MOD_ID_) FORM(NPCP_Form, TYPE_, MOD_ID_);

    Armor_t* Blank_Armor() NPCP_FORM(Armor_t, ARMOR_BLANK);

    Faction_t* Member_Faction() NPCP_FORM(Faction_t, FACTION_MEMBER);
    Faction_t* Horse_Faction() NPCP_FORM(Faction_t, FACTION_HORSE);

    Formlist_t* Settler_Markers_Formlist() NPCP_FORM(Formlist_t, FORMLIST_MARKERS_SETTLER);

    Misc_t* Member_Token() NPCP_FORM(Misc_t, MISC_TOKEN_MEMBER);
    Misc_t* Generic_Token() NPCP_FORM(Misc_t, MISC_TOKEN_GENERIC);
    Misc_t* Clone_Token() NPCP_FORM(Misc_t, MISC_TOKEN_CLONE);
    Misc_t* Greeter_Token() NPCP_FORM(Misc_t, MISC_TOKEN_GREETER);
    Misc_t* Movee_Token() NPCP_FORM(Misc_t, MISC_TOKEN_MOVEE);
    Misc_t* Immobile_Token() NPCP_FORM(Misc_t, MISC_TOKEN_IMMOBILE);
    Misc_t* Settler_Token() NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER);
    Misc_t* Thrall_Token() NPCP_FORM(Misc_t, MISC_TOKEN_THRALL);
    Misc_t* Paralyzed_Token() NPCP_FORM(Misc_t, MISC_TOKEN_PARALYZED);
    Misc_t* Mannequin_Token() NPCP_FORM(Misc_t, MISC_TOKEN_MANNEQUIN);
    Misc_t* Display_Token() NPCP_FORM(Misc_t, MISC_TOKEN_DISPLAY);
    Misc_t* Reanimated_Token() NPCP_FORM(Misc_t, MISC_TOKEN_REANIMATED);
    Misc_t* Banished_Token() NPCP_FORM(Misc_t, MISC_TOKEN_BANISHED);
    Misc_t* Default_Style_Token() NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_DEFAULT);
    Misc_t* Warrior_Style_Token() NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_WARRIOR);
    Misc_t* Mage_Style_Token() NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_MAGE);
    Misc_t* Archer_Style_Token() NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_ARCHER);
    Misc_t* Coward_Style_Token() NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_COWARD);
    Misc_t* Mortal_Vitality_Token() NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_MORTAL);
    Misc_t* Protected_Vitality_Token() NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_PROTECTED);
    Misc_t* Essential_Vitality_Token() NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_ESSENTIAL);
    Misc_t* Invulnerable_Vitality_Token() NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_INVULNERABLE);
    Misc_t* Follower_Token() NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER);
    Misc_t* Sneak_Follower_Token() NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER_SNEAK);
    Misc_t* Saddler_Token() NPCP_FORM(Misc_t, MISC_TOKEN_SADDLER);
    Misc_t* Retreater_Token() NPCP_FORM(Misc_t, MISC_TOKEN_RETREATER);
    Misc_t* Form_Vector() NPCP_FORM(Misc_t, MISC_VECTOR_FORM);

    Outfit_t* Empty_Outfit() NPCP_FORM(Outfit_t, OUTFIT_EMPTY);

    Quest_t* Static_Data_Quest() NPCP_FORM(Quest_t, QUEST_DATA_STATIC);
    Quest_t* Dynamic_Data_Quest() NPCP_FORM(Quest_t, QUEST_DATA_DYNAMIC);
    Quest_t* Funcs_Quest() NPCP_FORM(Quest_t, QUEST_FUNCS);
    Quest_t* Members_Quest() NPCP_FORM(Quest_t, QUEST_MEMBERS);
    Quest_t* Followers_Quest() NPCP_FORM(Quest_t, QUEST_FOLLOWERS);
    Quest_t* Control_Quest() NPCP_FORM(Quest_t, QUEST_CONTROL);

    Reference_t* Input_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_INPUT);
    Reference_t* Swords_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SWORDS);
    Reference_t* Greatswords_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_GREATSWORDS);
    Reference_t* Waraxes_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WARAXES);
    Reference_t* Battleaxes_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BATTLEAXES);
    Reference_t* Maces_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_MACES);
    Reference_t* Warhammers_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WARHAMMERS);
    Reference_t* Daggers_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_DAGGERS);
    Reference_t* Staves_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_STAVES);
    Reference_t* Bows_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOWS);
    Reference_t* Ammo_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_AMMO);
    Reference_t* Weapons_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WEAPONS);
    Reference_t* Light_Armor_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_LIGHT_ARMOR);
    Reference_t* Heavy_Armor_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_HEAVY_ARMOR);
    Reference_t* Shields_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SHIELDS);
    Reference_t* Jewelry_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_JEWELRY);
    Reference_t* Clothes_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CLOTHES);
    Reference_t* Potions_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_POTIONS);
    Reference_t* Poisons_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_POISONS);
    Reference_t* Ingredients_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_INGREDIENTS);
    Reference_t* Food_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_FOOD);
    Reference_t* Soulgems_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SOULGEMS);
    Reference_t* Scrolls_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SCROLLS);
    Reference_t* Metals_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_METALS);
    Reference_t* Leather_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_LEATHER);
    Reference_t* Gems_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_GEMS);
    Reference_t* Clutter_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CLUTTER);
    Reference_t* Keys_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_KEYS);
    Reference_t* Misc_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_MISC);
    Reference_t* Spell_Tomes_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SPELL_TOMES);
    Reference_t* Recipes_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_RECIPES);
    Reference_t* A_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_A);
    Reference_t* B_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_B);
    Reference_t* C_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_C);
    Reference_t* D_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_D);
    Reference_t* E_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_E);
    Reference_t* F_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_F);
    Reference_t* G_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_G);
    Reference_t* H_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_H);
    Reference_t* I_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_I);
    Reference_t* J_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_J);
    Reference_t* K_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_K);
    Reference_t* L_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_L);
    Reference_t* M_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_M);
    Reference_t* N_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_N);
    Reference_t* O_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_O);
    Reference_t* P_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_P);
    Reference_t* Q_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Q);
    Reference_t* R_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_R);
    Reference_t* S_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_S);
    Reference_t* T_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_T);
    Reference_t* U_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_U);
    Reference_t* V_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_V);
    Reference_t* W_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_W);
    Reference_t* X_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_X);
    Reference_t* Y_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Y);
    Reference_t* Z_Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Z);
    Reference_t* Books_Category() NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS);
    Reference_t* Storage_Marker() NPCP_FORM(Reference_t, REFERENCE_MARKER_STORAGE);

    Weapon_t* Blank_Weapon() NPCP_FORM(Weapon_t, WEAPON_BLANK);

    #undef NPCP_FORM

    #undef FORM

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    #define FORWARD_CONST(METHOD_) { return Consts::METHOD_(); }

    // Skryim
    Quest_t* Follower_Dialogue_Quest(Selfless_t*) FORWARD_CONST(Follower_Dialogue_Quest);

    // Dawnguard

    // NPCP
    Reference_t* Input_Category(Selfless_t*) FORWARD_CONST(Input_Category);
    Reference_t* Swords_Category(Selfless_t*) FORWARD_CONST(Swords_Category);
    Reference_t* Greatswords_Category(Selfless_t*) FORWARD_CONST(Greatswords_Category);
    Reference_t* Waraxes_Category(Selfless_t*) FORWARD_CONST(Waraxes_Category);
    Reference_t* Battleaxes_Category(Selfless_t*) FORWARD_CONST(Battleaxes_Category);
    Reference_t* Maces_Category(Selfless_t*) FORWARD_CONST(Maces_Category);
    Reference_t* Warhammers_Category(Selfless_t*) FORWARD_CONST(Warhammers_Category);
    Reference_t* Daggers_Category(Selfless_t*) FORWARD_CONST(Daggers_Category);
    Reference_t* Staves_Category(Selfless_t*) FORWARD_CONST(Staves_Category);
    Reference_t* Bows_Category(Selfless_t*) FORWARD_CONST(Bows_Category);
    Reference_t* Ammo_Category(Selfless_t*) FORWARD_CONST(Ammo_Category);
    Reference_t* Weapons_Category(Selfless_t*) FORWARD_CONST(Weapons_Category);
    Reference_t* Light_Armor_Category(Selfless_t*) FORWARD_CONST(Light_Armor_Category);
    Reference_t* Heavy_Armor_Category(Selfless_t*) FORWARD_CONST(Heavy_Armor_Category);
    Reference_t* Shields_Category(Selfless_t*) FORWARD_CONST(Shields_Category);
    Reference_t* Jewelry_Category(Selfless_t*) FORWARD_CONST(Jewelry_Category);
    Reference_t* Clothes_Category(Selfless_t*) FORWARD_CONST(Clothes_Category);
    Reference_t* Potions_Category(Selfless_t*) FORWARD_CONST(Potions_Category);
    Reference_t* Poisons_Category(Selfless_t*) FORWARD_CONST(Poisons_Category);
    Reference_t* Ingredients_Category(Selfless_t*) FORWARD_CONST(Ingredients_Category);
    Reference_t* Food_Category(Selfless_t*) FORWARD_CONST(Food_Category);
    Reference_t* Soulgems_Category(Selfless_t*) FORWARD_CONST(Soulgems_Category);
    Reference_t* Scrolls_Category(Selfless_t*) FORWARD_CONST(Scrolls_Category);
    Reference_t* Metals_Category(Selfless_t*) FORWARD_CONST(Metals_Category);
    Reference_t* Leather_Category(Selfless_t*) FORWARD_CONST(Leather_Category);
    Reference_t* Gems_Category(Selfless_t*) FORWARD_CONST(Gems_Category);
    Reference_t* Clutter_Category(Selfless_t*) FORWARD_CONST(Clutter_Category);
    Reference_t* Keys_Category(Selfless_t*) FORWARD_CONST(Keys_Category);
    Reference_t* Misc_Category(Selfless_t*) FORWARD_CONST(Misc_Category);
    Reference_t* Spell_Tomes_Category(Selfless_t*) FORWARD_CONST(Spell_Tomes_Category);
    Reference_t* Recipes_Category(Selfless_t*) FORWARD_CONST(Recipes_Category);
    Reference_t* A_Books_Category(Selfless_t*) FORWARD_CONST(A_Books_Category);
    Reference_t* B_Books_Category(Selfless_t*) FORWARD_CONST(B_Books_Category);
    Reference_t* C_Books_Category(Selfless_t*) FORWARD_CONST(C_Books_Category);
    Reference_t* D_Books_Category(Selfless_t*) FORWARD_CONST(D_Books_Category);
    Reference_t* E_Books_Category(Selfless_t*) FORWARD_CONST(E_Books_Category);
    Reference_t* F_Books_Category(Selfless_t*) FORWARD_CONST(F_Books_Category);
    Reference_t* G_Books_Category(Selfless_t*) FORWARD_CONST(G_Books_Category);
    Reference_t* H_Books_Category(Selfless_t*) FORWARD_CONST(H_Books_Category);
    Reference_t* I_Books_Category(Selfless_t*) FORWARD_CONST(I_Books_Category);
    Reference_t* J_Books_Category(Selfless_t*) FORWARD_CONST(J_Books_Category);
    Reference_t* K_Books_Category(Selfless_t*) FORWARD_CONST(K_Books_Category);
    Reference_t* L_Books_Category(Selfless_t*) FORWARD_CONST(L_Books_Category);
    Reference_t* M_Books_Category(Selfless_t*) FORWARD_CONST(M_Books_Category);
    Reference_t* N_Books_Category(Selfless_t*) FORWARD_CONST(N_Books_Category);
    Reference_t* O_Books_Category(Selfless_t*) FORWARD_CONST(O_Books_Category);
    Reference_t* P_Books_Category(Selfless_t*) FORWARD_CONST(P_Books_Category);
    Reference_t* Q_Books_Category(Selfless_t*) FORWARD_CONST(Q_Books_Category);
    Reference_t* R_Books_Category(Selfless_t*) FORWARD_CONST(R_Books_Category);
    Reference_t* S_Books_Category(Selfless_t*) FORWARD_CONST(S_Books_Category);
    Reference_t* T_Books_Category(Selfless_t*) FORWARD_CONST(T_Books_Category);
    Reference_t* U_Books_Category(Selfless_t*) FORWARD_CONST(U_Books_Category);
    Reference_t* V_Books_Category(Selfless_t*) FORWARD_CONST(V_Books_Category);
    Reference_t* W_Books_Category(Selfless_t*) FORWARD_CONST(W_Books_Category);
    Reference_t* X_Books_Category(Selfless_t*) FORWARD_CONST(X_Books_Category);
    Reference_t* Y_Books_Category(Selfless_t*) FORWARD_CONST(Y_Books_Category);
    Reference_t* Z_Books_Category(Selfless_t*) FORWARD_CONST(Z_Books_Category);
    Reference_t* Books_Category(Selfless_t*) FORWARD_CONST(Books_Category);

    #undef FORWARD_CONST

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_consts", Selfless_t,          \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        // Skyrim
        ADD_GLOBAL("Follower_Dialogue_Quest", 0, Quest_t*, Follower_Dialogue_Quest);

        // NPCP
        ADD_GLOBAL("Input_Category", 0, Reference_t*, Input_Category);
        ADD_GLOBAL("Swords_Category", 0, Reference_t*, Swords_Category);
        ADD_GLOBAL("Greatswords_Category", 0, Reference_t*, Greatswords_Category);
        ADD_GLOBAL("Waraxes_Category", 0, Reference_t*, Waraxes_Category);
        ADD_GLOBAL("Battleaxes_Category", 0, Reference_t*, Battleaxes_Category);
        ADD_GLOBAL("Maces_Category", 0, Reference_t*, Maces_Category);
        ADD_GLOBAL("Warhammers_Category", 0, Reference_t*, Warhammers_Category);
        ADD_GLOBAL("Daggers_Category", 0, Reference_t*, Daggers_Category);
        ADD_GLOBAL("Staves_Category", 0, Reference_t*, Staves_Category);
        ADD_GLOBAL("Bows_Category", 0, Reference_t*, Bows_Category);
        ADD_GLOBAL("Ammo_Category", 0, Reference_t*, Ammo_Category);
        ADD_GLOBAL("Weapons_Category", 0, Reference_t*, Weapons_Category);
        ADD_GLOBAL("Light_Armor_Category", 0, Reference_t*, Light_Armor_Category);
        ADD_GLOBAL("Heavy_Armor_Category", 0, Reference_t*, Heavy_Armor_Category);
        ADD_GLOBAL("Shields_Category", 0, Reference_t*, Shields_Category);
        ADD_GLOBAL("Jewelry_Category", 0, Reference_t*, Jewelry_Category);
        ADD_GLOBAL("Clothes_Category", 0, Reference_t*, Clothes_Category);
        ADD_GLOBAL("Potions_Category", 0, Reference_t*, Potions_Category);
        ADD_GLOBAL("Poisons_Category", 0, Reference_t*, Poisons_Category);
        ADD_GLOBAL("Ingredients_Category", 0, Reference_t*, Ingredients_Category);
        ADD_GLOBAL("Food_Category", 0, Reference_t*, Food_Category);
        ADD_GLOBAL("Soulgems_Category", 0, Reference_t*, Soulgems_Category);
        ADD_GLOBAL("Scrolls_Category", 0, Reference_t*, Scrolls_Category);
        ADD_GLOBAL("Metals_Category", 0, Reference_t*, Metals_Category);
        ADD_GLOBAL("Leather_Category", 0, Reference_t*, Leather_Category);
        ADD_GLOBAL("Gems_Category", 0, Reference_t*, Gems_Category);
        ADD_GLOBAL("Clutter_Category", 0, Reference_t*, Clutter_Category);
        ADD_GLOBAL("Keys_Category", 0, Reference_t*, Keys_Category);
        ADD_GLOBAL("Misc_Category", 0, Reference_t*, Misc_Category);
        ADD_GLOBAL("Spell_Tomes_Category", 0, Reference_t*, Spell_Tomes_Category);
        ADD_GLOBAL("Recipes_Category", 0, Reference_t*, Recipes_Category);
        ADD_GLOBAL("A_Books_Category", 0, Reference_t*, A_Books_Category);
        ADD_GLOBAL("B_Books_Category", 0, Reference_t*, B_Books_Category);
        ADD_GLOBAL("C_Books_Category", 0, Reference_t*, C_Books_Category);
        ADD_GLOBAL("D_Books_Category", 0, Reference_t*, D_Books_Category);
        ADD_GLOBAL("E_Books_Category", 0, Reference_t*, E_Books_Category);
        ADD_GLOBAL("F_Books_Category", 0, Reference_t*, F_Books_Category);
        ADD_GLOBAL("G_Books_Category", 0, Reference_t*, G_Books_Category);
        ADD_GLOBAL("H_Books_Category", 0, Reference_t*, H_Books_Category);
        ADD_GLOBAL("I_Books_Category", 0, Reference_t*, I_Books_Category);
        ADD_GLOBAL("J_Books_Category", 0, Reference_t*, J_Books_Category);
        ADD_GLOBAL("K_Books_Category", 0, Reference_t*, K_Books_Category);
        ADD_GLOBAL("L_Books_Category", 0, Reference_t*, L_Books_Category);
        ADD_GLOBAL("M_Books_Category", 0, Reference_t*, M_Books_Category);
        ADD_GLOBAL("N_Books_Category", 0, Reference_t*, N_Books_Category);
        ADD_GLOBAL("O_Books_Category", 0, Reference_t*, O_Books_Category);
        ADD_GLOBAL("P_Books_Category", 0, Reference_t*, P_Books_Category);
        ADD_GLOBAL("Q_Books_Category", 0, Reference_t*, Q_Books_Category);
        ADD_GLOBAL("R_Books_Category", 0, Reference_t*, R_Books_Category);
        ADD_GLOBAL("S_Books_Category", 0, Reference_t*, S_Books_Category);
        ADD_GLOBAL("T_Books_Category", 0, Reference_t*, T_Books_Category);
        ADD_GLOBAL("U_Books_Category", 0, Reference_t*, U_Books_Category);
        ADD_GLOBAL("V_Books_Category", 0, Reference_t*, V_Books_Category);
        ADD_GLOBAL("W_Books_Category", 0, Reference_t*, W_Books_Category);
        ADD_GLOBAL("X_Books_Category", 0, Reference_t*, X_Books_Category);
        ADD_GLOBAL("Y_Books_Category", 0, Reference_t*, Y_Books_Category);
        ADD_GLOBAL("Z_Books_Category", 0, Reference_t*, Z_Books_Category);
        ADD_GLOBAL("Books_Category", 0, Reference_t*, Books_Category);

        #undef ADD_GLOBAL

        return true;
    }

}}}
