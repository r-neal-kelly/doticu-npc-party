/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "commands.h"
#include "consts.h"
#include "form.h"
#include "funcs.h"
#include "game.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "topic_infos.h"
#include "utils.h"

#include "mcm/mcm_chests.h"

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos {

    static void Open_Category(Reference_t* category, String_t name)
    {
        Game::Update_NPCP_Categories();
        Object_Ref::Rename(category, name);
        Modules::Funcs_t::Self()->Open_Container(category);
    }

    void Execute_Topic_Info(Topic_Info_t* topic_info, Reference_t* ref)
    {
        if (topic_info) {
            Actor_t* actor = static_cast<Actor_t*>(ref);
            Topic_t* topic = topic_info->topic;
            Branch_t* branch = topic_info->Branch();
            if (branch) {
                if (branch == Consts::Main_Branch()) {
                    if (topic == Consts::Main_Clone_Topic()) {
                        Modules::Control::Commands_t::Self()->Clone(actor);
                    } else if (topic == Consts::Main_Enthrall_Topic()) {
                        Modules::Control::Commands_t::Self()->Enthrall(actor);
                    } else if (topic == Consts::Main_Follow_Topic()) {
                        Modules::Control::Commands_t::Self()->Follow(actor);
                    } else if (topic == Consts::Main_Immobilize_Topic()) {
                        Modules::Control::Commands_t::Self()->Immobilize(actor, true);
                    } else if (topic == Consts::Main_Member_Topic()) {
                        Modules::Control::Commands_t::Self()->Member(actor);
                    } else if (topic == Consts::Main_Mobilize_Topic()) {
                        Modules::Control::Commands_t::Self()->Mobilize(actor, true);
                    } else if (topic == Consts::Main_Pack_Topic()) {
                        Modules::Control::Commands_t::Self()->Open_Pack(actor);
                    } else if (topic == Consts::Main_Paralyze_Topic()) {
                        Modules::Control::Commands_t::Self()->Paralyze(actor, true);
                    } else if (topic == Consts::Main_Resettle_Topic()) {
                        Modules::Control::Commands_t::Self()->Resettle(actor, true);
                    } else if (topic == Consts::Main_Saddle_Topic()) {
                        Modules::Control::Commands_t::Self()->Saddle(actor);
                    } else if (topic == Consts::Main_Settle_Topic()) {
                        Modules::Control::Commands_t::Self()->Settle(actor, true);
                    } else if (topic == Consts::Main_Sneak_Topic()) {
                        Modules::Control::Commands_t::Self()->Sneak(actor, true);
                    } else if (topic == Consts::Main_Sojourn_Topic()) {
                        Modules::Control::Commands_t::Self()->Sojourn(actor, true);
                    } else if (topic == Consts::Main_Stash_Topic()) {
                        Modules::Control::Commands_t::Self()->Stash(actor);
                    } else if (topic == Consts::Main_Unclone_Topic()) {
                        Modules::Control::Commands_t::Self()->Unclone(actor);
                    } else if (topic == Consts::Main_Unfollow_Topic()) {
                        Modules::Control::Commands_t::Self()->Unfollow(actor);
                    } else if (topic == Consts::Main_Unmember_Topic()) {
                        Modules::Control::Commands_t::Self()->Unmember(actor);
                    } else if (topic == Consts::Main_Unsaddle_Topic()) {
                        Modules::Control::Commands_t::Self()->Unsaddle(actor);
                    } else if (topic == Consts::Main_Unsettle_Topic()) {
                        Modules::Control::Commands_t::Self()->Unsettle(actor, true);
                    } else if (topic == Consts::Main_Unsneak_Topic()) {
                        Modules::Control::Commands_t::Self()->Unsneak(actor, true);
                    } else if (topic == Consts::Main_Unsojourn_Topic()) {
                        Modules::Control::Commands_t::Self()->Unsojourn(actor, true);
                    } else if (topic == Consts::Main_Unthrall_Topic()) {
                        Modules::Control::Commands_t::Self()->Unthrall(actor);
                    }

                } else if (branch == Consts::Main_Direct_Branch()) {
                    if (topic == Consts::Main_Direct_Topic()) {
                        Actor2::Set_Doing_Favor(actor, true);
                    } else if (topic == Consts::Main_Direct_End_Topic()) {
                        Actor2::Set_Doing_Favor(actor, false);
                    }

                } else if (branch == Consts::Main_Outfit_Branch()) {
                    if (topic == Consts::Main_Outfit_Topic()) {
                        Modules::Control::Commands_t::Self()->Show_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Current_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Current_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Default_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Default_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Follower_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Follower_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Immobile_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Immobile_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Member_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Member_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Settler_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Settler_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Thrall_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Thrall_Outfit2(actor);
                    } else if (topic == Consts::Main_Outfit_Vanilla_Topic()) {
                        Modules::Control::Commands_t::Self()->Change_Vanilla_Outfit2(actor);
                    }

                } else if (branch == Consts::Main_Style_Branch()) {
                    if (topic == Consts::Main_Style_Topic()) {
                        Modules::Control::Commands_t::Self()->Show_Style(actor);
                    } else if (topic == Consts::Main_Style_Archer_Topic()) {
                        Modules::Control::Commands_t::Self()->Stylize_Archer(actor, true);
                    } else if (topic == Consts::Main_Style_Coward_Topic()) {
                        Modules::Control::Commands_t::Self()->Stylize_Coward(actor, true);
                    } else if (topic == Consts::Main_Style_Default_Topic()) {
                        Modules::Control::Commands_t::Self()->Stylize_Default(actor, true);
                    } else if (topic == Consts::Main_Style_Mage_Topic()) {
                        Modules::Control::Commands_t::Self()->Stylize_Mage(actor, true);
                    } else if (topic == Consts::Main_Style_Warrior_Topic()) {
                        Modules::Control::Commands_t::Self()->Stylize_Warrior(actor, true);
                    }

                } else if (branch == Consts::Main_Vitality_Branch()) {
                    if (topic == Consts::Main_Vitality_Topic()) {
                        Modules::Control::Commands_t::Self()->Show_Vitality(actor);
                    } else if (topic == Consts::Main_Vitality_Essential_Topic()) {
                        Modules::Control::Commands_t::Self()->Vitalize_Essential(actor, true);
                    } else if (topic == Consts::Main_Vitality_Invulnerable_Topic()) {
                        Modules::Control::Commands_t::Self()->Vitalize_Invulnerable(actor, true);
                    } else if (topic == Consts::Main_Vitality_Mortal_Topic()) {
                        Modules::Control::Commands_t::Self()->Vitalize_Mortal(actor, true);
                    } else if (topic == Consts::Main_Vitality_Protected_Topic()) {
                        Modules::Control::Commands_t::Self()->Vitalize_Protected(actor, true);
                    }

                } else if (branch == Consts::Menu_Followers_Branch()) {
                    if (topic == Consts::Menu_Followers_Immobilize_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Immobilize();
                    } else if (topic == Consts::Menu_Followers_Mobilize_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Mobilize();
                    } else if (topic == Consts::Menu_Followers_Saddle_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Saddle();
                    } else if (topic == Consts::Menu_Followers_Settle_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Settle();
                    } else if (topic == Consts::Menu_Followers_Sneak_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Sneak();
                    } else if (topic == Consts::Menu_Followers_Stash_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Stash();
                    } else if (topic == Consts::Menu_Followers_Summon_All_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Summon_All();
                    } else if (topic == Consts::Menu_Followers_Summon_Immobile_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Summon_Immobile();
                    } else if (topic == Consts::Menu_Followers_Summon_Mobile_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Summon_Mobile();
                    } else if (topic == Consts::Menu_Followers_Unfollow_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Unfollow();
                    } else if (topic == Consts::Menu_Followers_Unmember_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Unmember();
                    } else if (topic == Consts::Menu_Followers_Unsaddle_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Unsaddle();
                    } else if (topic == Consts::Menu_Followers_Unsettle_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Unsettle();
                    } else if (topic == Consts::Menu_Followers_Unsneak_Topic()) {
                        Modules::Control::Commands_t::Self()->Followers_Unsneak();
                    }

                } else if (branch == Consts::Menu_Chests_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Input_Topic_Info()) {
                        Open_Category(Consts::Input_Category(), " Input ");
                    }

                } else if (branch == Consts::Menu_Chests_Weapons_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Weapons_Swords_Topic_Info()) {
                        Open_Category(Consts::Swords_Category(), " Swords ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Greatswords_Topic_Info()) {
                        Open_Category(Consts::Greatswords_Category(), " Greatswords ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Waraxes_Topic_Info()) {
                        Open_Category(Consts::Waraxes_Category(), " Waraxes ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Battleaxes_Topic_Info()) {
                        Open_Category(Consts::Battleaxes_Category(), " Battleaxes ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Maces_Topic_Info()) {
                        Open_Category(Consts::Maces_Category(), " Maces ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Warhammers_Topic_Info()) {
                        Open_Category(Consts::Warhammers_Category(), " Warhammers ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Daggers_Topic_Info()) {
                        Open_Category(Consts::Daggers_Category(), " Daggers ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Staves_Topic_Info()) {
                        Open_Category(Consts::Staves_Category(), " Staves ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Bows_Topic_Info()) {
                        Open_Category(Consts::Bows_Category(), " Bows ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Ammo_Topic_Info()) {
                        Open_Category(Consts::Ammo_Category(), " Ammo ");
                    } else if (topic_info == Consts::Menu_Chests_Weapons_Others_Topic_Info()) {
                        Open_Category(Consts::Weapons_Category(), " Other Weapons ");
                    }

                } else if (branch == Consts::Menu_Chests_Apparel_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Apparel_Light_Armor_Topic_Info()) {
                        Open_Category(Consts::Light_Armor_Category(), " Light Armor ");
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Heavy_Armor_Topic_Info()) {
                        Open_Category(Consts::Heavy_Armor_Category(), " Heavy Armor ");
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Shields_Topic_Info()) {
                        Open_Category(Consts::Shields_Category(), " Shields ");
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Jewelry_Topic_Info()) {
                        Open_Category(Consts::Jewelry_Category(), " Jewelry ");
                    } else if (topic_info == Consts::Menu_Chests_Apparel_Clothes_Topic_Info()) {
                        Open_Category(Consts::Clothes_Category(), " Clothes ");
                    }

                } else if (branch == Consts::Menu_Chests_Edibles_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Edibles_Potions_Topic_Info()) {
                        Open_Category(Consts::Potions_Category(), " Potions ");
                    } else if (topic_info == Consts::Menu_Chests_Edibles_Poisons_Topic_Info()) {
                        Open_Category(Consts::Poisons_Category(), " Poisons ");
                    } else if (topic_info == Consts::Menu_Chests_Edibles_Ingredients_Topic_Info()) {
                        Open_Category(Consts::Ingredients_Category(), " Ingredients ");
                    } else if (topic_info == Consts::Menu_Chests_Edibles_Food_Topic_Info()) {
                        Open_Category(Consts::Food_Category(), " Food ");
                    }

                } else if (branch == Consts::Menu_Chests_Misc_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Misc_Soulgems_Topic_Info()) {
                        Open_Category(Consts::Soulgems_Category(), " Soulgems ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Scrolls_Topic_Info()) {
                        Open_Category(Consts::Scrolls_Category(), " Scrolls ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Metals_Topic_Info()) {
                        Open_Category(Consts::Metals_Category(), " Metals ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Leather_Topic_Info()) {
                        Open_Category(Consts::Leather_Category(), " Leather ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Gems_Topic_Info()) {
                        Open_Category(Consts::Gems_Category(), " Gems ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Clutter_Topic_Info()) {
                        Open_Category(Consts::Clutter_Category(), " Clutter ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Keys_Topic_Info()) {
                        Open_Category(Consts::Keys_Category(), " Keys ");
                    } else if (topic_info == Consts::Menu_Chests_Misc_Others_Topic_Info()) {
                        Open_Category(Consts::Misc_Category(), " Other Misc ");
                    }

                } else if (branch == Consts::Menu_Chests_Books_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Books_Spell_Tomes_Topic_Info()) {
                        Open_Category(Consts::Spell_Tomes_Category(), " Spell Tomes ");
                    } else if (topic_info == Consts::Menu_Chests_Books_Recipes_Topic_Info()) {
                        Open_Category(Consts::Recipes_Category(), " Recipes ");
                    } else if (topic_info == Consts::Menu_Chests_Books_A_Topic_Info()) {
                        Open_Category(Consts::A_Books_Category(), " Books A ");
                    } else if (topic_info == Consts::Menu_Chests_Books_B_Topic_Info()) {
                        Open_Category(Consts::B_Books_Category(), " Books B ");
                    } else if (topic_info == Consts::Menu_Chests_Books_C_Topic_Info()) {
                        Open_Category(Consts::C_Books_Category(), " Books C ");
                    } else if (topic_info == Consts::Menu_Chests_Books_D_Topic_Info()) {
                        Open_Category(Consts::D_Books_Category(), " Books D ");
                    } else if (topic_info == Consts::Menu_Chests_Books_E_Topic_Info()) {
                        Open_Category(Consts::E_Books_Category(), " Books E ");
                    } else if (topic_info == Consts::Menu_Chests_Books_F_Topic_Info()) {
                        Open_Category(Consts::F_Books_Category(), " Books F ");
                    } else if (topic_info == Consts::Menu_Chests_Books_G_Topic_Info()) {
                        Open_Category(Consts::G_Books_Category(), " Books G ");
                    } else if (topic_info == Consts::Menu_Chests_Books_H_Topic_Info()) {
                        Open_Category(Consts::H_Books_Category(), " Books H ");
                    } else if (topic_info == Consts::Menu_Chests_Books_I_Topic_Info()) {
                        Open_Category(Consts::I_Books_Category(), " Books I ");
                    } else if (topic_info == Consts::Menu_Chests_Books_J_Topic_Info()) {
                        Open_Category(Consts::J_Books_Category(), " Books J ");
                    } else if (topic_info == Consts::Menu_Chests_Books_K_Topic_Info()) {
                        Open_Category(Consts::K_Books_Category(), " Books K ");
                    } else if (topic_info == Consts::Menu_Chests_Books_L_Topic_Info()) {
                        Open_Category(Consts::L_Books_Category(), " Books L ");
                    } else if (topic_info == Consts::Menu_Chests_Books_M_Topic_Info()) {
                        Open_Category(Consts::M_Books_Category(), " Books M ");
                    } else if (topic_info == Consts::Menu_Chests_Books_N_Topic_Info()) {
                        Open_Category(Consts::N_Books_Category(), " Books N ");
                    } else if (topic_info == Consts::Menu_Chests_Books_O_Topic_Info()) {
                        Open_Category(Consts::O_Books_Category(), " Books O ");
                    } else if (topic_info == Consts::Menu_Chests_Books_P_Topic_Info()) {
                        Open_Category(Consts::P_Books_Category(), " Books P ");
                    } else if (topic_info == Consts::Menu_Chests_Books_Q_Topic_Info()) {
                        Open_Category(Consts::Q_Books_Category(), " Books Q ");
                    } else if (topic_info == Consts::Menu_Chests_Books_R_Topic_Info()) {
                        Open_Category(Consts::R_Books_Category(), " Books R ");
                    } else if (topic_info == Consts::Menu_Chests_Books_S_Topic_Info()) {
                        Open_Category(Consts::S_Books_Category(), " Books S ");
                    } else if (topic_info == Consts::Menu_Chests_Books_T_Topic_Info()) {
                        Open_Category(Consts::T_Books_Category(), " Books T ");
                    } else if (topic_info == Consts::Menu_Chests_Books_U_Topic_Info()) {
                        Open_Category(Consts::U_Books_Category(), " Books U ");
                    } else if (topic_info == Consts::Menu_Chests_Books_V_Topic_Info()) {
                        Open_Category(Consts::V_Books_Category(), " Books V ");
                    } else if (topic_info == Consts::Menu_Chests_Books_W_Topic_Info()) {
                        Open_Category(Consts::W_Books_Category(), " Books W ");
                    } else if (topic_info == Consts::Menu_Chests_Books_X_Topic_Info()) {
                        Open_Category(Consts::X_Books_Category(), " Books X ");
                    } else if (topic_info == Consts::Menu_Chests_Books_Y_Topic_Info()) {
                        Open_Category(Consts::Y_Books_Category(), " Books Y ");
                    } else if (topic_info == Consts::Menu_Chests_Books_Z_Topic_Info()) {
                        Open_Category(Consts::Z_Books_Category(), " Books Z ");
                    } else if (topic_info == Consts::Menu_Chests_Books_Others_Topic_Info()) {
                        Open_Category(Consts::Books_Category(), " Books # ");
                    }

                } else if (branch == Consts::Menu_Chests_Custom_Branch()) {
                    if (topic_info == Consts::Menu_Chests_Custom_Topic_Info()) {
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
                    } else if (topic_info == Consts::Menu_Chests_Custom_00_Topic_Info()) {
                        Open_Category(Consts::Custom_00_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(0)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_01_Topic_Info()) {
                        Open_Category(Consts::Custom_01_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(1)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_02_Topic_Info()) {
                        Open_Category(Consts::Custom_02_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(2)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_03_Topic_Info()) {
                        Open_Category(Consts::Custom_03_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(3)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_04_Topic_Info()) {
                        Open_Category(Consts::Custom_04_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(4)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_05_Topic_Info()) {
                        Open_Category(Consts::Custom_05_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(5)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_06_Topic_Info()) {
                        Open_Category(Consts::Custom_06_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(6)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_07_Topic_Info()) {
                        Open_Category(Consts::Custom_07_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(7)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_08_Topic_Info()) {
                        Open_Category(Consts::Custom_08_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(8)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_09_Topic_Info()) {
                        Open_Category(Consts::Custom_09_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(9)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_10_Topic_Info()) {
                        Open_Category(Consts::Custom_10_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(10)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_11_Topic_Info()) {
                        Open_Category(Consts::Custom_11_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(11)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_12_Topic_Info()) {
                        Open_Category(Consts::Custom_12_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(12)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_13_Topic_Info()) {
                        Open_Category(Consts::Custom_13_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(13)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_14_Topic_Info()) {
                        Open_Category(Consts::Custom_14_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(14)->String());
                    } else if (topic_info == Consts::Menu_Chests_Custom_15_Topic_Info()) {
                        Open_Category(Consts::Custom_15_Category(), MCM::Chests_t::Self()->Custom_Names_Array()->Point(15)->String());
                    }
                }
            }
        }
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
            ADD_CLASS_METHOD("doticu_npcp_main", Selfless_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("Execute_Topic_Info", 2, void, Execute_Topic_Info, Topic_Info_t*, Reference_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
