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

    static void Name_Custom_Categories()
    {
        Array_t* custom_names = MCM::Chests_t::Self()->Custom_Names_Array();
        Form::Name(Consts::Menu_Chests_Custom_00_Topic(), custom_names->Point(0)->String());
        Form::Name(Consts::Menu_Chests_Custom_01_Topic(), custom_names->Point(1)->String());
        Form::Name(Consts::Menu_Chests_Custom_02_Topic(), custom_names->Point(2)->String());
        Form::Name(Consts::Menu_Chests_Custom_03_Topic(), custom_names->Point(3)->String());
        Form::Name(Consts::Menu_Chests_Custom_04_Topic(), custom_names->Point(4)->String());
        Form::Name(Consts::Menu_Chests_Custom_05_Topic(), custom_names->Point(5)->String());
        Form::Name(Consts::Menu_Chests_Custom_06_Topic(), custom_names->Point(6)->String());
        Form::Name(Consts::Menu_Chests_Custom_07_Topic(), custom_names->Point(7)->String());
        Form::Name(Consts::Menu_Chests_Custom_08_Topic(), custom_names->Point(8)->String());
        Form::Name(Consts::Menu_Chests_Custom_09_Topic(), custom_names->Point(9)->String());
        Form::Name(Consts::Menu_Chests_Custom_10_Topic(), custom_names->Point(10)->String());
        Form::Name(Consts::Menu_Chests_Custom_11_Topic(), custom_names->Point(11)->String());
        Form::Name(Consts::Menu_Chests_Custom_12_Topic(), custom_names->Point(12)->String());
        Form::Name(Consts::Menu_Chests_Custom_13_Topic(), custom_names->Point(13)->String());
        Form::Name(Consts::Menu_Chests_Custom_14_Topic(), custom_names->Point(14)->String());
        Form::Name(Consts::Menu_Chests_Custom_15_Topic(), custom_names->Point(15)->String());
    }

    static void Open_Category(Reference_t* category, String_t name)
    {
        Game::Update_NPCP_Categories();
        Object_Ref::Rename(category, name);
        Modules::Funcs_t::Self()->Open_Container(category);
    }

    static void Open_Custom_Category(Reference_t* category, Int_t custom_id)
    {
        Open_Category(category, MCM::Chests_t::Self()->Custom_Names_Array()->Point(custom_id)->String());
    }

    static Bool_t Has_Form(Formlist_t* formlist, Form_t* form)
    {
        if (formlist) {
            for (size_t idx = 0, end = formlist->forms.count; idx < end; idx += 1) {
                if (formlist->forms.entries[idx] == form) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    void Execute_Topic_Info(Topic_Info_t* topic_info, Reference_t* ref)
    {
        using Commands_t = Modules::Control::Commands_t;

        if (topic_info) {
            Actor_t* actor = static_cast<Actor_t*>(ref);
            Branch_t* branch = topic_info->Branch();
            Topic_t* topic = topic_info->topic;
            const char* topic_eid = topic->Editor_ID();
            if (branch) {
                if (Has_Form(Consts::Main_Branches_Formlist(), branch)) {
                         if (String2::Ends_With(topic_eid, "_main"));
                    else if (String2::Ends_With(topic_eid, "_main2"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_clone"))           Commands_t::Self()->Clone(actor);
                    else if (String2::Ends_With(topic_eid, "_enthrall"))        Commands_t::Self()->Enthrall(actor);
                    else if (String2::Ends_With(topic_eid, "_follow"))          Commands_t::Self()->Follow(actor);
                    else if (String2::Ends_With(topic_eid, "_immobilize"))      Commands_t::Self()->Immobilize(actor, true);
                    else if (String2::Ends_With(topic_eid, "_member"))          Commands_t::Self()->Member(actor);
                    else if (String2::Ends_With(topic_eid, "_mobilize"))        Commands_t::Self()->Mobilize(actor, true);
                    else if (String2::Ends_With(topic_eid, "_pack"))            Commands_t::Self()->Open_Pack(actor);
                    else if (String2::Ends_With(topic_eid, "_paralyze"))        Commands_t::Self()->Paralyze(actor, true);
                    else if (String2::Ends_With(topic_eid, "_resettle"))        Commands_t::Self()->Resettle(actor, true);
                    else if (String2::Ends_With(topic_eid, "_saddle"))          Commands_t::Self()->Saddle(actor);
                    else if (String2::Ends_With(topic_eid, "_settle"))          Commands_t::Self()->Settle(actor, true);
                    else if (String2::Ends_With(topic_eid, "_sneak"))           Commands_t::Self()->Sneak(actor, true);
                    else if (String2::Ends_With(topic_eid, "_sojourn"))         Commands_t::Self()->Sojourn(actor, true);
                    else if (String2::Ends_With(topic_eid, "_stash"))           Commands_t::Self()->Stash(actor);
                    else if (String2::Ends_With(topic_eid, "_unclone"))         Commands_t::Self()->Unclone(actor);
                    else if (String2::Ends_With(topic_eid, "_unfollow"))        Commands_t::Self()->Unfollow(actor);
                    else if (String2::Ends_With(topic_eid, "_unmember"))        Commands_t::Self()->Unmember(actor);
                    else if (String2::Ends_With(topic_eid, "_unsaddle"))        Commands_t::Self()->Unsaddle(actor);
                    else if (String2::Ends_With(topic_eid, "_unsettle"))        Commands_t::Self()->Unsettle(actor, true);
                    else if (String2::Ends_With(topic_eid, "_unsneak"))         Commands_t::Self()->Unsneak(actor, true);
                    else if (String2::Ends_With(topic_eid, "_unsojourn"))       Commands_t::Self()->Unsojourn(actor, true);
                    else if (String2::Ends_With(topic_eid, "_unthrall"))        Commands_t::Self()->Unthrall(actor);
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (Has_Form(Consts::Main_Direct_Branches_Formlist(), branch)) {
                         if (String2::Ends_With(topic_eid, "_direct"))          Actor2::Set_Doing_Favor(actor, true);
                    else if (String2::Ends_With(topic_eid, "_begin"));
                    else if (String2::Ends_With(topic_eid, "_continue"));
                    else if (String2::Ends_With(topic_eid, "_end"))             Actor2::Set_Doing_Favor(actor, false);
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (Has_Form(Consts::Main_Outfit_Branches_Formlist(), branch)) {
                         if (String2::Ends_With(topic_eid, "_outfit"))          Commands_t::Self()->Show_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_outfit2"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_current"))         Commands_t::Self()->Change_Current_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_default"))         Commands_t::Self()->Change_Default_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_follower"))        Commands_t::Self()->Change_Follower_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_immobile"))        Commands_t::Self()->Change_Immobile_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_member"))          Commands_t::Self()->Change_Member_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_settler"))         Commands_t::Self()->Change_Settler_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_thrall"))          Commands_t::Self()->Change_Thrall_Outfit2(actor);
                    else if (String2::Ends_With(topic_eid, "_vanilla"))         Commands_t::Self()->Change_Vanilla_Outfit2(actor);
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (Has_Form(Consts::Main_Style_Branches_Formlist(), branch)) {
                         if (String2::Ends_With(topic_eid, "_style"))           Commands_t::Self()->Show_Style(actor);
                    else if (String2::Ends_With(topic_eid, "_style2"));
                    else if (String2::Ends_With(topic_eid, "_archer"))          Commands_t::Self()->Stylize_Archer(actor, true);
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_coward"))          Commands_t::Self()->Stylize_Coward(actor, true);
                    else if (String2::Ends_With(topic_eid, "_default"))         Commands_t::Self()->Stylize_Default(actor, true);
                    else if (String2::Ends_With(topic_eid, "_mage"))            Commands_t::Self()->Stylize_Mage(actor, true);
                    else if (String2::Ends_With(topic_eid, "_warrior"))         Commands_t::Self()->Stylize_Warrior(actor, true);
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (Has_Form(Consts::Main_Vitality_Branches_Formlist(), branch)) {
                         if (String2::Ends_With(topic_eid, "_vitality"))        Commands_t::Self()->Show_Vitality(actor);
                    else if (String2::Ends_With(topic_eid, "_vitality2"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_essential"))       Commands_t::Self()->Vitalize_Essential(actor, true);
                    else if (String2::Ends_With(topic_eid, "_invulnerable"))    Commands_t::Self()->Vitalize_Invulnerable(actor, true);
                    else if (String2::Ends_With(topic_eid, "_mortal"))          Commands_t::Self()->Vitalize_Mortal(actor, true);
                    else if (String2::Ends_With(topic_eid, "_protected"))       Commands_t::Self()->Vitalize_Protected(actor, true);
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Branch()) {
                         if (String2::Ends_With(topic_eid, "_menu"));
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Followers_Branch()) {
                         if (String2::Ends_With(topic_eid, "_followers"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_immobilize"))      Commands_t::Self()->Followers_Immobilize();
                    else if (String2::Ends_With(topic_eid, "_mobilize"))        Commands_t::Self()->Followers_Mobilize();
                    else if (String2::Ends_With(topic_eid, "_saddle"))          Commands_t::Self()->Followers_Saddle();
                    else if (String2::Ends_With(topic_eid, "_settle"))          Commands_t::Self()->Followers_Settle();
                    else if (String2::Ends_With(topic_eid, "_sneak"))           Commands_t::Self()->Followers_Sneak();
                    else if (String2::Ends_With(topic_eid, "_stash"))           Commands_t::Self()->Followers_Stash();
                    else if (String2::Ends_With(topic_eid, "_summon_all"))      Commands_t::Self()->Followers_Summon_All();
                    else if (String2::Ends_With(topic_eid, "_summon_immobile")) Commands_t::Self()->Followers_Summon_Immobile();
                    else if (String2::Ends_With(topic_eid, "_summon_mobile"))   Commands_t::Self()->Followers_Summon_Mobile();
                    else if (String2::Ends_With(topic_eid, "_unfollow"))        Commands_t::Self()->Followers_Unfollow();
                    else if (String2::Ends_With(topic_eid, "_unmember"))        Commands_t::Self()->Followers_Unmember();
                    else if (String2::Ends_With(topic_eid, "_unsaddle"))        Commands_t::Self()->Followers_Unsaddle();
                    else if (String2::Ends_With(topic_eid, "_unsettle"))        Commands_t::Self()->Followers_Unsettle();
                    else if (String2::Ends_With(topic_eid, "_unsneak"))         Commands_t::Self()->Followers_Unsneak();
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Branch()) {
                         if (String2::Ends_With(topic_eid, "_chests"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_input"))           Open_Category(Consts::Input_Category(), " Input ");
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Weapons_Branch()) {
                         if (String2::Ends_With(topic_eid, "_weapons"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_swords"))          Open_Category(Consts::Swords_Category(), " Swords ");
                    else if (String2::Ends_With(topic_eid, "_greatswords"))     Open_Category(Consts::Greatswords_Category(), " Greatswords ");
                    else if (String2::Ends_With(topic_eid, "_waraxes"))         Open_Category(Consts::Waraxes_Category(), " Waraxes ");
                    else if (String2::Ends_With(topic_eid, "_battleaxes"))      Open_Category(Consts::Battleaxes_Category(), " Battleaxes ");
                    else if (String2::Ends_With(topic_eid, "_maces"))           Open_Category(Consts::Maces_Category(), " Maces ");
                    else if (String2::Ends_With(topic_eid, "_warhammers"))      Open_Category(Consts::Warhammers_Category(), " Warhammers ");
                    else if (String2::Ends_With(topic_eid, "_daggers"))         Open_Category(Consts::Daggers_Category(), " Daggers ");
                    else if (String2::Ends_With(topic_eid, "_staves"))          Open_Category(Consts::Staves_Category(), " Staves ");
                    else if (String2::Ends_With(topic_eid, "_bows"))            Open_Category(Consts::Bows_Category(), " Bows ");
                    else if (String2::Ends_With(topic_eid, "_ammo"))            Open_Category(Consts::Ammo_Category(), " Ammo ");
                    else if (String2::Ends_With(topic_eid, "_others"))          Open_Category(Consts::Weapons_Category(), " Other Weapons ");
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Apparel_Branch()) {
                         if (String2::Ends_With(topic_eid, "_apparel"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_light_armor"))     Open_Category(Consts::Light_Armor_Category(), " Light Armor ");
                    else if (String2::Ends_With(topic_eid, "_heavy_armor"))     Open_Category(Consts::Heavy_Armor_Category(), " Heavy Armor ");
                    else if (String2::Ends_With(topic_eid, "_shields"))         Open_Category(Consts::Shields_Category(), " Shields ");
                    else if (String2::Ends_With(topic_eid, "_jewelry"))         Open_Category(Consts::Jewelry_Category(), " Jewelry ");
                    else if (String2::Ends_With(topic_eid, "_clothes"))         Open_Category(Consts::Clothes_Category(), " Clothes ");
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Edibles_Branch()) {
                         if (String2::Ends_With(topic_eid, "_edibles"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_potions"))         Open_Category(Consts::Potions_Category(), " Potions ");
                    else if (String2::Ends_With(topic_eid, "_poisons"))         Open_Category(Consts::Poisons_Category(), " Poisons ");
                    else if (String2::Ends_With(topic_eid, "_ingredients"))     Open_Category(Consts::Ingredients_Category(), " Ingredients ");
                    else if (String2::Ends_With(topic_eid, "_food"))            Open_Category(Consts::Food_Category(), " Food ");
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Misc_Branch()) {
                         if (String2::Ends_With(topic_eid, "_misc"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_soulgems"))        Open_Category(Consts::Soulgems_Category(), " Soulgems ");
                    else if (String2::Ends_With(topic_eid, "_scrolls"))         Open_Category(Consts::Scrolls_Category(), " Scrolls ");
                    else if (String2::Ends_With(topic_eid, "_metals"))          Open_Category(Consts::Metals_Category(), " Metals ");
                    else if (String2::Ends_With(topic_eid, "_leather"))         Open_Category(Consts::Leather_Category(), " Leather ");
                    else if (String2::Ends_With(topic_eid, "_gems"))            Open_Category(Consts::Gems_Category(), " Gems ");
                    else if (String2::Ends_With(topic_eid, "_clutter"))         Open_Category(Consts::Clutter_Category(), " Clutter ");
                    else if (String2::Ends_With(topic_eid, "_keys"))            Open_Category(Consts::Keys_Category(), " Keys ");
                    else if (String2::Ends_With(topic_eid, "_others"))          Open_Category(Consts::Misc_Category(), " Other Misc ");
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Books_Branch()) {
                         if (String2::Ends_With(topic_eid, "_books"));
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_spell_tomes"))     Open_Category(Consts::Spell_Tomes_Category(), " Spell Tomes ");
                    else if (String2::Ends_With(topic_eid, "_recipes"))         Open_Category(Consts::Recipes_Category(), " Recipes ");
                    else if (String2::Ends_With(topic_eid, "_a"))               Open_Category(Consts::A_Books_Category(), " Books A ");
                    else if (String2::Ends_With(topic_eid, "_b"))               Open_Category(Consts::B_Books_Category(), " Books B ");
                    else if (String2::Ends_With(topic_eid, "_c"))               Open_Category(Consts::C_Books_Category(), " Books C ");
                    else if (String2::Ends_With(topic_eid, "_d"))               Open_Category(Consts::D_Books_Category(), " Books D ");
                    else if (String2::Ends_With(topic_eid, "_e"))               Open_Category(Consts::E_Books_Category(), " Books E ");
                    else if (String2::Ends_With(topic_eid, "_f"))               Open_Category(Consts::F_Books_Category(), " Books F ");
                    else if (String2::Ends_With(topic_eid, "_g"))               Open_Category(Consts::G_Books_Category(), " Books G ");
                    else if (String2::Ends_With(topic_eid, "_h"))               Open_Category(Consts::H_Books_Category(), " Books H ");
                    else if (String2::Ends_With(topic_eid, "_i"))               Open_Category(Consts::I_Books_Category(), " Books I ");
                    else if (String2::Ends_With(topic_eid, "_j"))               Open_Category(Consts::J_Books_Category(), " Books J ");
                    else if (String2::Ends_With(topic_eid, "_k"))               Open_Category(Consts::K_Books_Category(), " Books K ");
                    else if (String2::Ends_With(topic_eid, "_l"))               Open_Category(Consts::L_Books_Category(), " Books L ");
                    else if (String2::Ends_With(topic_eid, "_m"))               Open_Category(Consts::M_Books_Category(), " Books M ");
                    else if (String2::Ends_With(topic_eid, "_n"))               Open_Category(Consts::N_Books_Category(), " Books N ");
                    else if (String2::Ends_With(topic_eid, "_o"))               Open_Category(Consts::O_Books_Category(), " Books O ");
                    else if (String2::Ends_With(topic_eid, "_p"))               Open_Category(Consts::P_Books_Category(), " Books P ");
                    else if (String2::Ends_With(topic_eid, "_q"))               Open_Category(Consts::Q_Books_Category(), " Books Q ");
                    else if (String2::Ends_With(topic_eid, "_r"))               Open_Category(Consts::R_Books_Category(), " Books R ");
                    else if (String2::Ends_With(topic_eid, "_s"))               Open_Category(Consts::S_Books_Category(), " Books S ");
                    else if (String2::Ends_With(topic_eid, "_t"))               Open_Category(Consts::T_Books_Category(), " Books T ");
                    else if (String2::Ends_With(topic_eid, "_u"))               Open_Category(Consts::U_Books_Category(), " Books U ");
                    else if (String2::Ends_With(topic_eid, "_v"))               Open_Category(Consts::V_Books_Category(), " Books V ");
                    else if (String2::Ends_With(topic_eid, "_w"))               Open_Category(Consts::W_Books_Category(), " Books W ");
                    else if (String2::Ends_With(topic_eid, "_x"))               Open_Category(Consts::X_Books_Category(), " Books X ");
                    else if (String2::Ends_With(topic_eid, "_y"))               Open_Category(Consts::Y_Books_Category(), " Books Y ");
                    else if (String2::Ends_With(topic_eid, "_z"))               Open_Category(Consts::Z_Books_Category(), " Books Z ");
                    else if (String2::Ends_With(topic_eid, "_others"))          Open_Category(Consts::Books_Category(), " Books # ");
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else if (branch == Consts::Menu_Chests_Custom_Branch()) {
                         if (String2::Ends_With(topic_eid, "_custom"))          Name_Custom_Categories();
                    else if (String2::Ends_With(topic_eid, "_back"));
                    else if (String2::Ends_With(topic_eid, "_00"))              Open_Custom_Category(Consts::Custom_00_Category(), 0);
                    else if (String2::Ends_With(topic_eid, "_01"))              Open_Custom_Category(Consts::Custom_01_Category(), 1);
                    else if (String2::Ends_With(topic_eid, "_02"))              Open_Custom_Category(Consts::Custom_02_Category(), 2);
                    else if (String2::Ends_With(topic_eid, "_03"))              Open_Custom_Category(Consts::Custom_03_Category(), 3);
                    else if (String2::Ends_With(topic_eid, "_04"))              Open_Custom_Category(Consts::Custom_04_Category(), 4);
                    else if (String2::Ends_With(topic_eid, "_05"))              Open_Custom_Category(Consts::Custom_05_Category(), 5);
                    else if (String2::Ends_With(topic_eid, "_06"))              Open_Custom_Category(Consts::Custom_06_Category(), 6);
                    else if (String2::Ends_With(topic_eid, "_07"))              Open_Custom_Category(Consts::Custom_07_Category(), 7);
                    else if (String2::Ends_With(topic_eid, "_08"))              Open_Custom_Category(Consts::Custom_08_Category(), 8);
                    else if (String2::Ends_With(topic_eid, "_09"))              Open_Custom_Category(Consts::Custom_09_Category(), 9);
                    else if (String2::Ends_With(topic_eid, "_10"))              Open_Custom_Category(Consts::Custom_10_Category(), 10);
                    else if (String2::Ends_With(topic_eid, "_11"))              Open_Custom_Category(Consts::Custom_11_Category(), 11);
                    else if (String2::Ends_With(topic_eid, "_12"))              Open_Custom_Category(Consts::Custom_12_Category(), 12);
                    else if (String2::Ends_With(topic_eid, "_13"))              Open_Custom_Category(Consts::Custom_13_Category(), 13);
                    else if (String2::Ends_With(topic_eid, "_14"))              Open_Custom_Category(Consts::Custom_14_Category(), 14);
                    else if (String2::Ends_With(topic_eid, "_15"))              Open_Custom_Category(Consts::Custom_15_Category(), 15);
                    else                                                        _MESSAGE("unhandled topic: %s", topic_eid);

                } else {
                    _MESSAGE("unhandled branch: %8.8X", branch);
                }
            } else {
                _MESSAGE("unhandled topic: %s", topic_eid);
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
