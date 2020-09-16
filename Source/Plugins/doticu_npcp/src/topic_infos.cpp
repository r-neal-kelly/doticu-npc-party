/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "form.h"
#include "funcs.h"
#include "game.h"
#include "object_ref.h"
#include "topic_infos.h"
#include "utils.h"

#include "mcm/mcm_chests.h"

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos {

    void Execute_Topic_Info(Topic_Info_t* topic_info, Reference_t* ref)
    {
        if (topic_info) {
            Branch_t* branch = topic_info->Branch();
            if (branch) {
                if (branch == Consts::Menu_Chests_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Input_Topic_Info()) {
                        return Execute_Menu_Chests_Input();
                    }

                } else if (branch == Consts::Menu_Chests_Weapons_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Weapons_Swords_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Swords();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Greatswords_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Greatswords();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Waraxes_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Waraxes();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Battleaxes_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Battleaxes();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Maces_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Maces();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Warhammers_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Warhammers();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Daggers_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Daggers();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Staves_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Staves();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Bows_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Bows();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Ammo_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Ammo();
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Others_Topic_Info()) {
                        return Execute_Menu_Chests_Weapons_Others();
                    }

                } else if (branch == Consts::Menu_Chests_Apparel_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Apparel_Light_Armor_Topic_Info()) {
                        return Execute_Menu_Chests_Apparel_Light_Armor();
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Heavy_Armor_Topic_Info()) {
                        return Execute_Menu_Chests_Apparel_Heavy_Armor();
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Shields_Topic_Info()) {
                        return Execute_Menu_Chests_Apparel_Shields();
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Jewelry_Topic_Info()) {
                        return Execute_Menu_Chests_Apparel_Jewelry();
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Clothes_Topic_Info()) {
                        return Execute_Menu_Chests_Apparel_Clothes();
                    }

                } else if (branch == Consts::Menu_Chests_Edibles_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Edibles_Potions_Topic_Info()) {
                        return Execute_Menu_Chests_Edibles_Potions();
                    } else if (topic_info == Consts::Menu_Chests_Edibles_Poisons_Topic_Info()) {
                        return Execute_Menu_Chests_Edibles_Poisons();
                    } else if (topic_info == Consts::Menu_Chests_Edibles_Ingredients_Topic_Info()) {
                        return Execute_Menu_Chests_Edibles_Ingredients();
                    } else if (topic_info == Consts::Menu_Chests_Edibles_Food_Topic_Info()) {
                        return Execute_Menu_Chests_Edibles_Food();
                    }

                } else if (branch == Consts::Menu_Chests_Misc_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Misc_Soulgems_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Soulgems();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Scrolls_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Scrolls();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Metals_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Metals();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Leather_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Leather();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Gems_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Gems();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Clutter_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Clutter();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Keys_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Keys();
                    } else if (topic_info == Consts::Menu_Chests_Misc_Others_Topic_Info()) {
                        return Execute_Menu_Chests_Misc_Others();
                    }

                } else if (branch == Consts::Menu_Chests_Books_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Books_Spell_Tomes_Topic_Info()) {
                        return Execute_Menu_Chests_Books_Spell_Tomes();
                    } else if (topic_info == Consts::Menu_Chests_Books_Recipes_Topic_Info()) {
                        return Execute_Menu_Chests_Books_Recipes();
                    } else if (topic_info == Consts::Menu_Chests_Books_A_Topic_Info()) {
                        return Execute_Menu_Chests_Books_A();
                    } else if (topic_info == Consts::Menu_Chests_Books_B_Topic_Info()) {
                        return Execute_Menu_Chests_Books_B();
                    } else if (topic_info == Consts::Menu_Chests_Books_C_Topic_Info()) {
                        return Execute_Menu_Chests_Books_C();
                    } else if (topic_info == Consts::Menu_Chests_Books_D_Topic_Info()) {
                        return Execute_Menu_Chests_Books_D();
                    } else if (topic_info == Consts::Menu_Chests_Books_E_Topic_Info()) {
                        return Execute_Menu_Chests_Books_E();
                    } else if (topic_info == Consts::Menu_Chests_Books_F_Topic_Info()) {
                        return Execute_Menu_Chests_Books_F();
                    } else if (topic_info == Consts::Menu_Chests_Books_G_Topic_Info()) {
                        return Execute_Menu_Chests_Books_G();
                    } else if (topic_info == Consts::Menu_Chests_Books_H_Topic_Info()) {
                        return Execute_Menu_Chests_Books_H();
                    } else if (topic_info == Consts::Menu_Chests_Books_I_Topic_Info()) {
                        return Execute_Menu_Chests_Books_I();
                    } else if (topic_info == Consts::Menu_Chests_Books_J_Topic_Info()) {
                        return Execute_Menu_Chests_Books_J();
                    } else if (topic_info == Consts::Menu_Chests_Books_K_Topic_Info()) {
                        return Execute_Menu_Chests_Books_K();
                    } else if (topic_info == Consts::Menu_Chests_Books_L_Topic_Info()) {
                        return Execute_Menu_Chests_Books_L();
                    } else if (topic_info == Consts::Menu_Chests_Books_M_Topic_Info()) {
                        return Execute_Menu_Chests_Books_M();
                    } else if (topic_info == Consts::Menu_Chests_Books_N_Topic_Info()) {
                        return Execute_Menu_Chests_Books_N();
                    } else if (topic_info == Consts::Menu_Chests_Books_O_Topic_Info()) {
                        return Execute_Menu_Chests_Books_O();
                    } else if (topic_info == Consts::Menu_Chests_Books_P_Topic_Info()) {
                        return Execute_Menu_Chests_Books_P();
                    } else if (topic_info == Consts::Menu_Chests_Books_Q_Topic_Info()) {
                        return Execute_Menu_Chests_Books_Q();
                    } else if (topic_info == Consts::Menu_Chests_Books_R_Topic_Info()) {
                        return Execute_Menu_Chests_Books_R();
                    } else if (topic_info == Consts::Menu_Chests_Books_S_Topic_Info()) {
                        return Execute_Menu_Chests_Books_S();
                    } else if (topic_info == Consts::Menu_Chests_Books_T_Topic_Info()) {
                        return Execute_Menu_Chests_Books_T();
                    } else if (topic_info == Consts::Menu_Chests_Books_U_Topic_Info()) {
                        return Execute_Menu_Chests_Books_U();
                    } else if (topic_info == Consts::Menu_Chests_Books_V_Topic_Info()) {
                        return Execute_Menu_Chests_Books_V();
                    } else if (topic_info == Consts::Menu_Chests_Books_W_Topic_Info()) {
                        return Execute_Menu_Chests_Books_W();
                    } else if (topic_info == Consts::Menu_Chests_Books_X_Topic_Info()) {
                        return Execute_Menu_Chests_Books_X();
                    } else if (topic_info == Consts::Menu_Chests_Books_Y_Topic_Info()) {
                        return Execute_Menu_Chests_Books_Y();
                    } else if (topic_info == Consts::Menu_Chests_Books_Z_Topic_Info()) {
                        return Execute_Menu_Chests_Books_Z();
                    } else if (topic_info == Consts::Menu_Chests_Books_Others_Topic_Info()) {
                        return Execute_Menu_Chests_Books_Others();
                    }

                } else if (branch == Consts::Menu_Chests_Custom_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Custom_Topic_Info()) {
                        return Execute_Menu_Chests_Custom();
                    } else if (topic_info == Consts::Menu_Chests_Custom_00_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_00();
                    } else if (topic_info == Consts::Menu_Chests_Custom_01_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_01();
                    } else if (topic_info == Consts::Menu_Chests_Custom_02_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_02();
                    } else if (topic_info == Consts::Menu_Chests_Custom_03_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_03();
                    } else if (topic_info == Consts::Menu_Chests_Custom_04_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_04();
                    } else if (topic_info == Consts::Menu_Chests_Custom_05_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_05();
                    } else if (topic_info == Consts::Menu_Chests_Custom_06_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_06();
                    } else if (topic_info == Consts::Menu_Chests_Custom_07_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_07();
                    } else if (topic_info == Consts::Menu_Chests_Custom_08_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_08();
                    } else if (topic_info == Consts::Menu_Chests_Custom_09_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_09();
                    } else if (topic_info == Consts::Menu_Chests_Custom_10_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_10();
                    } else if (topic_info == Consts::Menu_Chests_Custom_11_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_11();
                    } else if (topic_info == Consts::Menu_Chests_Custom_12_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_12();
                    } else if (topic_info == Consts::Menu_Chests_Custom_13_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_13();
                    } else if (topic_info == Consts::Menu_Chests_Custom_14_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_14();
                    } else if (topic_info == Consts::Menu_Chests_Custom_15_Topic_Info()) {
                        return Execute_Menu_Chests_Custom_15();
                    }
                }
            }
        }
    }

    void Open_Category(Reference_t* category, String_t name)
    {
        Game::Update_NPCP_Categories();
        Object_Ref::Rename(category, name);
        Modules::Funcs_t::Self()->Open_Container(category);
    }

    void Execute_Menu_Chests_Input()
    {
        Open_Category(Consts::Input_Category(), " Input ");
    }

    void Execute_Menu_Chests_Weapons_Swords()
    {
        Open_Category(Consts::Swords_Category(), " Swords ");
    }

    void Execute_Menu_Chests_Weapons_Greatswords()
    {
        Open_Category(Consts::Greatswords_Category(), " Greatswords ");
    }

    void Execute_Menu_Chests_Weapons_Waraxes()
    {
        Open_Category(Consts::Waraxes_Category(), " Waraxes ");
    }

    void Execute_Menu_Chests_Weapons_Battleaxes()
    {
        Open_Category(Consts::Battleaxes_Category(), " Battleaxes ");
    }

    void Execute_Menu_Chests_Weapons_Maces()
    {
        Open_Category(Consts::Maces_Category(), " Maces ");
    }

    void Execute_Menu_Chests_Weapons_Warhammers()
    {
        Open_Category(Consts::Warhammers_Category(), " Warhammers ");
    }

    void Execute_Menu_Chests_Weapons_Daggers()
    {
        Open_Category(Consts::Daggers_Category(), " Daggers ");
    }

    void Execute_Menu_Chests_Weapons_Staves()
    {
        Open_Category(Consts::Staves_Category(), " Staves ");
    }

    void Execute_Menu_Chests_Weapons_Bows()
    {
        Open_Category(Consts::Bows_Category(), " Bows ");
    }

    void Execute_Menu_Chests_Weapons_Ammo()
    {
        Open_Category(Consts::Ammo_Category(), " Ammo ");
    }

    void Execute_Menu_Chests_Weapons_Others()
    {
        Open_Category(Consts::Weapons_Category(), " Other Weapons ");
    }

    void Execute_Menu_Chests_Apparel_Light_Armor()
    {
        Open_Category(Consts::Light_Armor_Category(), " Light Armor ");
    }

    void Execute_Menu_Chests_Apparel_Heavy_Armor()
    {
        Open_Category(Consts::Heavy_Armor_Category(), " Heavy Armor ");
    }

    void Execute_Menu_Chests_Apparel_Shields()
    {
        Open_Category(Consts::Shields_Category(), " Shields ");
    }

    void Execute_Menu_Chests_Apparel_Jewelry()
    {
        Open_Category(Consts::Jewelry_Category(), " Jewelry ");
    }

    void Execute_Menu_Chests_Apparel_Clothes()
    {
        Open_Category(Consts::Clothes_Category(), " Clothes ");
    }

    void Execute_Menu_Chests_Edibles_Potions()
    {
        Open_Category(Consts::Potions_Category(), " Potions ");
    }

    void Execute_Menu_Chests_Edibles_Poisons()
    {
        Open_Category(Consts::Poisons_Category(), " Poisons ");
    }

    void Execute_Menu_Chests_Edibles_Ingredients()
    {
        Open_Category(Consts::Ingredients_Category(), " Ingredients ");
    }

    void Execute_Menu_Chests_Edibles_Food()
    {
        Open_Category(Consts::Food_Category(), " Food ");
    }

    void Execute_Menu_Chests_Misc_Soulgems()
    {
        Open_Category(Consts::Soulgems_Category(), " Soulgems ");
    }

    void Execute_Menu_Chests_Misc_Scrolls()
    {
        Open_Category(Consts::Scrolls_Category(), " Scrolls ");
    }

    void Execute_Menu_Chests_Misc_Metals()
    {
        Open_Category(Consts::Metals_Category(), " Metals ");
    }

    void Execute_Menu_Chests_Misc_Leather()
    {
        Open_Category(Consts::Leather_Category(), " Leather ");
    }

    void Execute_Menu_Chests_Misc_Gems()
    {
        Open_Category(Consts::Gems_Category(), " Gems ");
    }

    void Execute_Menu_Chests_Misc_Clutter()
    {
        Open_Category(Consts::Clutter_Category(), " Clutter ");
    }

    void Execute_Menu_Chests_Misc_Keys()
    {
        Open_Category(Consts::Keys_Category(), " Keys ");
    }

    void Execute_Menu_Chests_Misc_Others()
    {
        Open_Category(Consts::Misc_Category(), " Other Misc ");
    }

    void Execute_Menu_Chests_Books_Spell_Tomes()
    {
        Open_Category(Consts::Spell_Tomes_Category(), " Spell Tomes ");
    }

    void Execute_Menu_Chests_Books_Recipes()
    {
        Open_Category(Consts::Recipes_Category(), " Recipes ");
    }

    void Execute_Menu_Chests_Books_A()
    {
        Open_Category(Consts::A_Books_Category(), " Books A ");
    }

    void Execute_Menu_Chests_Books_B()
    {
        Open_Category(Consts::B_Books_Category(), " Books B ");
    }

    void Execute_Menu_Chests_Books_C()
    {
        Open_Category(Consts::C_Books_Category(), " Books C ");
    }

    void Execute_Menu_Chests_Books_D()
    {
        Open_Category(Consts::D_Books_Category(), " Books D ");
    }

    void Execute_Menu_Chests_Books_E()
    {
        Open_Category(Consts::E_Books_Category(), " Books E ");
    }

    void Execute_Menu_Chests_Books_F()
    {
        Open_Category(Consts::F_Books_Category(), " Books F ");
    }

    void Execute_Menu_Chests_Books_G()
    {
        Open_Category(Consts::G_Books_Category(), " Books G ");
    }

    void Execute_Menu_Chests_Books_H()
    {
        Open_Category(Consts::H_Books_Category(), " Books H ");
    }

    void Execute_Menu_Chests_Books_I()
    {
        Open_Category(Consts::I_Books_Category(), " Books I ");
    }

    void Execute_Menu_Chests_Books_J()
    {
        Open_Category(Consts::J_Books_Category(), " Books J ");
    }

    void Execute_Menu_Chests_Books_K()
    {
        Open_Category(Consts::K_Books_Category(), " Books K ");
    }

    void Execute_Menu_Chests_Books_L()
    {
        Open_Category(Consts::L_Books_Category(), " Books L ");
    }

    void Execute_Menu_Chests_Books_M()
    {
        Open_Category(Consts::M_Books_Category(), " Books M ");
    }

    void Execute_Menu_Chests_Books_N()
    {
        Open_Category(Consts::N_Books_Category(), " Books N ");
    }

    void Execute_Menu_Chests_Books_O()
    {
        Open_Category(Consts::O_Books_Category(), " Books O ");
    }

    void Execute_Menu_Chests_Books_P()
    {
        Open_Category(Consts::P_Books_Category(), " Books P ");
    }

    void Execute_Menu_Chests_Books_Q()
    {
        Open_Category(Consts::Q_Books_Category(), " Books Q ");
    }

    void Execute_Menu_Chests_Books_R()
    {
        Open_Category(Consts::R_Books_Category(), " Books R ");
    }

    void Execute_Menu_Chests_Books_S()
    {
        Open_Category(Consts::S_Books_Category(), " Books S ");
    }

    void Execute_Menu_Chests_Books_T()
    {
        Open_Category(Consts::T_Books_Category(), " Books T ");
    }

    void Execute_Menu_Chests_Books_U()
    {
        Open_Category(Consts::U_Books_Category(), " Books U ");
    }

    void Execute_Menu_Chests_Books_V()
    {
        Open_Category(Consts::V_Books_Category(), " Books V ");
    }

    void Execute_Menu_Chests_Books_W()
    {
        Open_Category(Consts::W_Books_Category(), " Books W ");
    }

    void Execute_Menu_Chests_Books_X()
    {
        Open_Category(Consts::X_Books_Category(), " Books X ");
    }

    void Execute_Menu_Chests_Books_Y()
    {
        Open_Category(Consts::Y_Books_Category(), " Books Y ");
    }

    void Execute_Menu_Chests_Books_Z()
    {
        Open_Category(Consts::Z_Books_Category(), " Books Z ");
    }

    void Execute_Menu_Chests_Books_Others()
    {
        Open_Category(Consts::Books_Category(), " Books # ");
    }

    void Execute_Menu_Chests_Custom()
    {
        Array_t* custom_names = MCM::Chests_t::Self()->Custom_Names_Array();
        Form::Name(Consts::Menu_Chests_Custom_00_Topic_Info()->topic, custom_names->Point(0)->String());
        Form::Name(Consts::Menu_Chests_Custom_01_Topic_Info()->topic, custom_names->Point(1)->String());
        Form::Name(Consts::Menu_Chests_Custom_02_Topic_Info()->topic, custom_names->Point(2)->String());
        Form::Name(Consts::Menu_Chests_Custom_03_Topic_Info()->topic, custom_names->Point(3)->String());
        Form::Name(Consts::Menu_Chests_Custom_04_Topic_Info()->topic, custom_names->Point(4)->String());
        Form::Name(Consts::Menu_Chests_Custom_05_Topic_Info()->topic, custom_names->Point(5)->String());
        Form::Name(Consts::Menu_Chests_Custom_06_Topic_Info()->topic, custom_names->Point(6)->String());
        Form::Name(Consts::Menu_Chests_Custom_07_Topic_Info()->topic, custom_names->Point(7)->String());
        Form::Name(Consts::Menu_Chests_Custom_08_Topic_Info()->topic, custom_names->Point(8)->String());
        Form::Name(Consts::Menu_Chests_Custom_09_Topic_Info()->topic, custom_names->Point(9)->String());
        Form::Name(Consts::Menu_Chests_Custom_10_Topic_Info()->topic, custom_names->Point(10)->String());
        Form::Name(Consts::Menu_Chests_Custom_11_Topic_Info()->topic, custom_names->Point(11)->String());
        Form::Name(Consts::Menu_Chests_Custom_12_Topic_Info()->topic, custom_names->Point(12)->String());
        Form::Name(Consts::Menu_Chests_Custom_13_Topic_Info()->topic, custom_names->Point(13)->String());
        Form::Name(Consts::Menu_Chests_Custom_14_Topic_Info()->topic, custom_names->Point(14)->String());
        Form::Name(Consts::Menu_Chests_Custom_15_Topic_Info()->topic, custom_names->Point(15)->String());
    }

    void Execute_Menu_Chests_Custom_00()
    {
        Open_Category(Consts::Custom_00_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(0)->String());
    }

    void Execute_Menu_Chests_Custom_01()
    {
        Open_Category(Consts::Custom_01_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(1)->String());
    }

    void Execute_Menu_Chests_Custom_02()
    {
        Open_Category(Consts::Custom_02_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(2)->String());
    }

    void Execute_Menu_Chests_Custom_03()
    {
        Open_Category(Consts::Custom_03_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(3)->String());
    }

    void Execute_Menu_Chests_Custom_04()
    {
        Open_Category(Consts::Custom_04_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(4)->String());
    }

    void Execute_Menu_Chests_Custom_05()
    {
        Open_Category(Consts::Custom_05_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(5)->String());
    }

    void Execute_Menu_Chests_Custom_06()
    {
        Open_Category(Consts::Custom_06_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(6)->String());
    }

    void Execute_Menu_Chests_Custom_07()
    {
        Open_Category(Consts::Custom_07_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(7)->String());
    }

    void Execute_Menu_Chests_Custom_08()
    {
        Open_Category(Consts::Custom_08_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(8)->String());
    }

    void Execute_Menu_Chests_Custom_09()
    {
        Open_Category(Consts::Custom_09_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(9)->String());
    }

    void Execute_Menu_Chests_Custom_10()
    {
        Open_Category(Consts::Custom_10_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(10)->String());
    }

    void Execute_Menu_Chests_Custom_11()
    {
        Open_Category(Consts::Custom_11_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(11)->String());
    }

    void Execute_Menu_Chests_Custom_12()
    {
        Open_Category(Consts::Custom_12_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(12)->String());
    }

    void Execute_Menu_Chests_Custom_13()
    {
        Open_Category(Consts::Custom_13_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(13)->String());
    }

    void Execute_Menu_Chests_Custom_14()
    {
        Open_Category(Consts::Custom_14_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(14)->String());
    }

    void Execute_Menu_Chests_Custom_15()
    {
        Open_Category(Consts::Custom_15_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(15)->String());
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos { namespace Exports {

    void Execute_Topic_Info(Selfless_t*, Topic_Info_t* topic_info, Reference_t* ref)
    {
        return Topic_Infos::Execute_Topic_Info(topic_info, ref);
    }

    Bool_t Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("Execute_Topic_Info", 2, void, Execute_Topic_Info, Topic_Info_t*, Reference_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
