/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos {

    void Execute_Topic_Info(Topic_Info_t* topic_info, Reference_t* ref);

    void Execute_Menu_Chests_Input();

    void Execute_Menu_Chests_Weapons_Swords();
    void Execute_Menu_Chests_Weapons_Greatswords();
    void Execute_Menu_Chests_Weapons_Waraxes();
    void Execute_Menu_Chests_Weapons_Battleaxes();
    void Execute_Menu_Chests_Weapons_Maces();
    void Execute_Menu_Chests_Weapons_Warhammers();
    void Execute_Menu_Chests_Weapons_Daggers();
    void Execute_Menu_Chests_Weapons_Staves();
    void Execute_Menu_Chests_Weapons_Bows();
    void Execute_Menu_Chests_Weapons_Ammo();
    void Execute_Menu_Chests_Weapons_Others();

    void Execute_Menu_Chests_Apparel_Light_Armor();
    void Execute_Menu_Chests_Apparel_Heavy_Armor();
    void Execute_Menu_Chests_Apparel_Shields();
    void Execute_Menu_Chests_Apparel_Jewelry();
    void Execute_Menu_Chests_Apparel_Clothes();

    void Execute_Menu_Chests_Edibles_Potions();
    void Execute_Menu_Chests_Edibles_Poisons();
    void Execute_Menu_Chests_Edibles_Ingredients();
    void Execute_Menu_Chests_Edibles_Food();

    void Execute_Menu_Chests_Misc_Soulgems();
    void Execute_Menu_Chests_Misc_Scrolls();
    void Execute_Menu_Chests_Misc_Metals();
    void Execute_Menu_Chests_Misc_Leather();
    void Execute_Menu_Chests_Misc_Gems();
    void Execute_Menu_Chests_Misc_Clutter();
    void Execute_Menu_Chests_Misc_Keys();
    void Execute_Menu_Chests_Misc_Others();

    void Execute_Menu_Chests_Books_Spell_Tomes();
    void Execute_Menu_Chests_Books_Recipes();
    void Execute_Menu_Chests_Books_A();
    void Execute_Menu_Chests_Books_B();
    void Execute_Menu_Chests_Books_C();
    void Execute_Menu_Chests_Books_D();
    void Execute_Menu_Chests_Books_E();
    void Execute_Menu_Chests_Books_F();
    void Execute_Menu_Chests_Books_G();
    void Execute_Menu_Chests_Books_H();
    void Execute_Menu_Chests_Books_I();
    void Execute_Menu_Chests_Books_J();
    void Execute_Menu_Chests_Books_K();
    void Execute_Menu_Chests_Books_L();
    void Execute_Menu_Chests_Books_M();
    void Execute_Menu_Chests_Books_N();
    void Execute_Menu_Chests_Books_O();
    void Execute_Menu_Chests_Books_P();
    void Execute_Menu_Chests_Books_Q();
    void Execute_Menu_Chests_Books_R();
    void Execute_Menu_Chests_Books_S();
    void Execute_Menu_Chests_Books_T();
    void Execute_Menu_Chests_Books_U();
    void Execute_Menu_Chests_Books_V();
    void Execute_Menu_Chests_Books_W();
    void Execute_Menu_Chests_Books_X();
    void Execute_Menu_Chests_Books_Y();
    void Execute_Menu_Chests_Books_Z();
    void Execute_Menu_Chests_Books_Others();

    void Execute_Menu_Chests_Custom();
    void Execute_Menu_Chests_Custom_00();
    void Execute_Menu_Chests_Custom_01();
    void Execute_Menu_Chests_Custom_02();
    void Execute_Menu_Chests_Custom_03();
    void Execute_Menu_Chests_Custom_04();
    void Execute_Menu_Chests_Custom_05();
    void Execute_Menu_Chests_Custom_06();
    void Execute_Menu_Chests_Custom_07();
    void Execute_Menu_Chests_Custom_08();
    void Execute_Menu_Chests_Custom_09();
    void Execute_Menu_Chests_Custom_10();
    void Execute_Menu_Chests_Custom_11();
    void Execute_Menu_Chests_Custom_12();
    void Execute_Menu_Chests_Custom_13();
    void Execute_Menu_Chests_Custom_14();
    void Execute_Menu_Chests_Custom_15();

}}}

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos { namespace Exports {

    Bool_t Register(VMClassRegistry *registry);

}}}}
