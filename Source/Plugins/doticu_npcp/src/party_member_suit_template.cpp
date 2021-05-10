/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/const_ammos.h"
#include "doticu_skylib/const_armors.h"
#include "doticu_skylib/const_weapons.h"
#include "doticu_skylib/weapon.h"

#include "intrinsic.h"
#include "party_member_suit_template.h"

namespace doticu_npcp { namespace Party {

    /*
    Armor_Set_t                 Set_Armor_Ancient_Falmer();
    Armor_Set_t                 Set_Armor_Ancient_Falmer_Auriel();
    Armor_Set_t                 Set_Armor_Ancient_Falmer_Pauldronless();
    Armor_Set_t                 Set_Armor_Ancient_Falmer_Reflecting();

    Armor_Set_t                 Set_Armor_Ancient_Nordic();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Ahzidal();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Bromjunaar();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Dukaan();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Hevnoraak();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Jagged_Crown();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Kolbjorn();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Konahrik();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Krosis();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Morokei();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Nahkriin();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Otar();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Rahgot();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Unburned();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Vokun();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Volsung();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Yngol();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Ysgramor();
    Armor_Set_t                 Set_Armor_Ancient_Nordic_Zahkriisos();

    Armor_Set_t                 Set_Armor_Blades();

    Armor_Set_t                 Set_Armor_Bonemold();
    Armor_Set_t                 Set_Armor_Bonemold_Enchanted();
    Armor_Set_t                 Set_Armor_Bonemold_Pauldron();
    Armor_Set_t                 Set_Armor_Bonemold_Pauldron_Enchanted();
    Armor_Set_t                 Set_Armor_Bonemold_Pauldron_Guard();
    Armor_Set_t                 Set_Armor_Bonemold_Pauldron_Guard_Enchanted();
    Armor_Set_t                 Set_Armor_Bonemold_Pauldron_Improved();

    Armor_Set_t                 Set_Armor_Chitin_Heavy();
    Armor_Set_t                 Set_Armor_Chitin_Heavy_Enchanted();
    Armor_Set_t                 Set_Armor_Chitin_Light();
    Armor_Set_t                 Set_Armor_Chitin_Light_Enchanted();

    Armor_Set_t                 Set_Armor_Daedric();
    Armor_Set_t                 Set_Armor_Daedric_Enchanted();

    Armor_Set_t                 Set_Armor_Dawnguard_Heavy_Brown();
    Armor_Set_t                 Set_Armor_Dawnguard_Heavy_Grey();
    Armor_Set_t                 Set_Armor_Dawnguard_Light_Brown();
    Armor_Set_t                 Set_Armor_Dawnguard_Light_Grey();
    Armor_Set_t                 Set_Armor_Dawnguard_Light_Red();

    Armor_Set_t                 Set_Armor_Dragonplate();
    Armor_Set_t                 Set_Armor_Dragonplate_Enchanted();

    Armor_Set_t                 Set_Armor_Dragonscale();
    Armor_Set_t                 Set_Armor_Dragonscale_Enchanted();

    Armor_Set_t                 Set_Armor_Dwarven();
    Armor_Set_t                 Set_Armor_Dwarven_Enchanted();
    Armor_Set_t                 Set_Armor_Dwarven_Aetherial();
    Armor_Set_t                 Set_Armor_Dwarven_Aetherial_Enchanted();
    Armor_Set_t                 Set_Armor_Dwarven_Spellbreaker();
    Armor_Set_t                 Set_Armor_Dwarven_Spellbreaker_Enchanted();
    Armor_Set_t                 Set_Armor_Dwarven_Visage_Of_Mzund();
    Armor_Set_t                 Set_Armor_Dwarven_Visage_Of_Mzund_Enchanted();

    Armor_Set_t                 Set_Armor_Ebony();
    Armor_Set_t                 Set_Armor_Ebony_Enchanted();
    Armor_Set_t                 Set_Armor_Ebony_Mail();
    Armor_Set_t                 Set_Armor_Ebony_Mail_Enchanted();
    Armor_Set_t                 Set_Armor_Ebony_Masque_Of_Clavicus_Vile();
    Armor_Set_t                 Set_Armor_Ebony_Masque_Of_Clavicus_Vile_Enchanted();

    Armor_Set_t                 Set_Armor_Elven();
    Armor_Set_t                 Set_Armor_Elven_Enchanted();
    Armor_Set_t                 Set_Armor_Elven_Gilded();
    Armor_Set_t                 Set_Armor_Elven_Gilded_Enchanted();
    Armor_Set_t                 Set_Armor_Elven_Pauldronless();
    Armor_Set_t                 Set_Armor_Elven_Pauldronless_Enchanted();

    Armor_Set_t                 Set_Armor_Falmer();
    Armor_Set_t                 Set_Armor_Falmer_Hardened();
    Armor_Set_t                 Set_Armor_Falmer_Heavy();
    Armor_Set_t                 Set_Armor_Falmer_Heavy_Shellbug();

    Armor_Set_t                 Set_Armor_Forsworn();
    Armor_Set_t                 Set_Armor_Forsworn_Old_Gods();

    Armor_Set_t                 Set_Armor_Fur();
    Armor_Set_t                 Set_Armor_Fur_Topless();
    Armor_Set_t                 Set_Armor_Fur_Topless_Pauldron();
    Armor_Set_t                 Set_Armor_Fur_Saviors_Hide();
    Armor_Set_t                 Set_Armor_Fur_Sleeveless();

    Armor_Set_t                 Set_Armor_Glass();
    Armor_Set_t                 Set_Armor_Glass_Enchanted();

    Armor_Set_t                 Set_Armor_Guard_Falkreath();
    Armor_Set_t                 Set_Armor_Guard_Hjaalmarch();
    Armor_Set_t                 Set_Armor_Guard_Markarth();
    Armor_Set_t                 Set_Armor_Guard_Pale();
    Armor_Set_t                 Set_Armor_Guard_Riften();
    Armor_Set_t                 Set_Armor_Guard_Riften_Pugilist();
    Armor_Set_t                 Set_Armor_Guard_Solitude();
    Armor_Set_t                 Set_Armor_Guard_Solitude_Reward();
    Armor_Set_t                 Set_Armor_Guard_Whiterun();
    Armor_Set_t                 Set_Armor_Guard_Windhelm();
    Armor_Set_t                 Set_Armor_Guard_Windhelm_Sleeved();
    Armor_Set_t                 Set_Armor_Guard_Winterhold();

    Armor_Set_t                 Set_Armor_Hide();
    Armor_Set_t                 Set_Armor_Hide_Enchanted();
    Armor_Set_t                 Set_Armor_Hide_Predators_Grace();
    Armor_Set_t                 Set_Armor_Hide_Predators_Grace_Enchanted();
    Armor_Set_t                 Set_Armor_Hide_Studded();
    Armor_Set_t                 Set_Armor_Hide_Studded_Enchanted();

    Armor_Set_t                 Set_Armor_Imperial_Heavy();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_Enchanted();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_General_Carius();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_General_Carius_Enchanted();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_General_Tullius();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_General_Tullius_Enchanted();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_Knight();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_Knight_Enchanted();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_Officer();
    Armor_Set_t                 Set_Armor_Imperial_Heavy_Officer_Enchanted();
    Armor_Set_t                 Set_Armor_Imperial_Light();
    Armor_Set_t                 Set_Armor_Imperial_Light_Enchanted();
    Armor_Set_t                 Set_Armor_Imperial_Light_Studded();
    Armor_Set_t                 Set_Armor_Imperial_Light_Studded_Enchanted();

    Armor_Set_t                 Set_Armor_Iron();
    Armor_Set_t                 Set_Armor_Iron_Enchanted();
    Armor_Set_t                 Set_Armor_Iron_Banded();
    Armor_Set_t                 Set_Armor_Iron_Banded_Enchanted();

    Armor_Set_t                 Set_Armor_Leather();
    Armor_Set_t                 Set_Armor_Leather_Enchanted();

    Armor_Set_t                 Set_Armor_Miraak_Reward();
    Armor_Set_t                 Set_Armor_Miraak_Reward_1();
    Armor_Set_t                 Set_Armor_Miraak_Reward_2();
    Armor_Set_t                 Set_Armor_Miraak_Reward_3();
    Armor_Set_t                 Set_Armor_Miraak_Heavy_Reward();
    Armor_Set_t                 Set_Armor_Miraak_Heavy_Reward_1();
    Armor_Set_t                 Set_Armor_Miraak_Heavy_Reward_2();
    Armor_Set_t                 Set_Armor_Miraak_Heavy_Reward_3();
    Armor_Set_t                 Set_Armor_Miraak_Light_Reward();
    Armor_Set_t                 Set_Armor_Miraak_Light_Reward_1();
    Armor_Set_t                 Set_Armor_Miraak_Light_Reward_2();
    Armor_Set_t                 Set_Armor_Miraak_Light_Reward_3();

    Armor_Set_t                 Set_Armor_Morag_Tong();

    Armor_Set_t                 Set_Armor_Nightingale_Reward();
    Armor_Set_t                 Set_Armor_Nightingale_Reward_1();
    Armor_Set_t                 Set_Armor_Nightingale_Reward_2();
    Armor_Set_t                 Set_Armor_Nightingale_Reward_3();

    Armor_Set_t                 Set_Armor_Nordic();
    Armor_Set_t                 Set_Armor_Nordic_Enchanted();

    Armor_Set_t                 Set_Armor_Orcish();
    Armor_Set_t                 Set_Armor_Orcish_Enchanted();

    Armor_Set_t                 Set_Armor_Penitus_Oculatus();

    Armor_Set_t                 Set_Armor_Plate();
    Armor_Set_t                 Set_Armor_Plate_Enchanted();

    Armor_Set_t                 Set_Armor_Scaled();
    Armor_Set_t                 Set_Armor_Scaled_Enchanted();
    Armor_Set_t                 Set_Armor_Scaled_Horned();
    Armor_Set_t                 Set_Armor_Scaled_Horned_Enchanted();

    Armor_Set_t                 Set_Armor_Shrouded();
    Armor_Set_t                 Set_Armor_Shrouded_Ancient();
    Armor_Set_t                 Set_Armor_Shrouded_Maskless();
    Armor_Set_t                 Set_Armor_Shrouded_Short_Sleeved();
    Armor_Set_t                 Set_Armor_Shrouded_Tumblerbane();
    Armor_Set_t                 Set_Armor_Shrouded_Worn();

    Armor_Set_t                 Set_Armor_Stalhrim_Heavy();
    Armor_Set_t                 Set_Armor_Stalhrim_Heavy_Enchanted();
    Armor_Set_t                 Set_Armor_Stalhrim_Light();
    Armor_Set_t                 Set_Armor_Stalhrim_Light_Enchanted();
    Armor_Set_t                 Set_Armor_Stalhrim_Light_Deathbrand();
    Armor_Set_t                 Set_Armor_Stalhrim_Light_Deathbrand_Enchanted();

    Armor_Set_t                 Set_Armor_Steel();
    Armor_Set_t                 Set_Armor_Steel_Enchanted();
    Armor_Set_t                 Set_Armor_Steel_Horned();
    Armor_Set_t                 Set_Armor_Steel_Horned_Enchanted();
    Armor_Set_t                 Set_Armor_Steel_Pauldron();
    Armor_Set_t                 Set_Armor_Steel_Pauldron_Enchanted();
    Armor_Set_t                 Set_Armor_Steel_Targe_Of_The_Blooded();
    Armor_Set_t                 Set_Armor_Steel_Targe_Of_The_Blooded_Enchanted();

    Armor_Set_t                 Set_Armor_Stormcloak_Officer();

    Armor_Set_t                 Set_Armor_Thieves_Guild();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Alternate();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Blackguard();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Improved();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Karliah();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Master();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Torturer();
    Armor_Set_t                 Set_Armor_Thieves_Guild_Variant();

    Armor_Set_t                 Set_Armor_Tsun();

    Armor_Set_t                 Set_Armor_Vampire_Black();
    Armor_Set_t                 Set_Armor_Vampire_Black_Enchanted();
    Armor_Set_t                 Set_Armor_Vampire_Grey();
    Armor_Set_t                 Set_Armor_Vampire_Grey_Enchanted();
    Armor_Set_t                 Set_Armor_Vampire_Red();
    Armor_Set_t                 Set_Armor_Vampire_Red_Enchanted();
    Armor_Set_t                 Set_Armor_Vampire_Royal();
    Armor_Set_t                 Set_Armor_Vampire_Royal_Serana();
    Armor_Set_t                 Set_Armor_Vampire_Royal_Valerica();

    Armor_Set_t                 Set_Armor_Wolf();

    Armor_Set_t                 Set_Clothes_Bandages();

    Armor_Set_t                 Set_Clothes_Bar_Keeper_Bright();
    Armor_Set_t                 Set_Clothes_Bar_Keeper_Dark();

    Armor_Set_t                 Set_Clothes_Beggar();

    Armor_Set_t                 Set_Clothes_Black_Smith_Grey();
    Armor_Set_t                 Set_Clothes_Black_Smith_Red();

    Armor_Set_t                 Set_Clothes_Blind_Priest();

    Armor_Set_t                 Set_Clothes_Chef();

    Armor_Set_t                 Set_Clothes_Child_Blue();
    Armor_Set_t                 Set_Clothes_Child_Bright();
    Armor_Set_t                 Set_Clothes_Child_Dark();
    Armor_Set_t                 Set_Clothes_Child_Green();
    Armor_Set_t                 Set_Clothes_Child_Red();
    Armor_Set_t                 Set_Clothes_Child_Skaal();

    Armor_Set_t                 Set_Clothes_Cultist();

    Armor_Set_t                 Set_Clothes_Dunmer_Blue();
    Armor_Set_t                 Set_Clothes_Dunmer_Blue_Hooded();
    Armor_Set_t                 Set_Clothes_Dunmer_Brown();
    Armor_Set_t                 Set_Clothes_Dunmer_Brown_Hooded();
    Armor_Set_t                 Set_Clothes_Dunmer_Red();
    Armor_Set_t                 Set_Clothes_Dunmer_Red_Hooded();

    Armor_Set_t                 Set_Clothes_Emperor();
    
    Armor_Set_t                 Set_Clothes_Executionee_Bright();
    Armor_Set_t                 Set_Clothes_Executionee_Dark();

    Armor_Set_t                 Set_Clothes_Executioner();

    Armor_Set_t                 Set_Clothes_Farm_A();
    Armor_Set_t                 Set_Clothes_Farm_B_Bright();
    Armor_Set_t                 Set_Clothes_Farm_B_Dark();
    Armor_Set_t                 Set_Clothes_Farm_C_Bright();
    Armor_Set_t                 Set_Clothes_Farm_C_Bright_Hooded();
    Armor_Set_t                 Set_Clothes_Farm_C_Dark();
    Armor_Set_t                 Set_Clothes_Farm_D_Bright();
    Armor_Set_t                 Set_Clothes_Farm_D_Dark();

    Armor_Set_t                 Set_Clothes_Fine_A_Blue();
    Armor_Set_t                 Set_Clothes_Fine_A_Green();
    Armor_Set_t                 Set_Clothes_Fine_B_Blue();
    Armor_Set_t                 Set_Clothes_Fine_B_Red();

    Armor_Set_t                 Set_Clothes_Greybeard();

    Armor_Set_t                 Set_Clothes_Jarl_A_Blue();
    Armor_Set_t                 Set_Clothes_Jarl_A_Green();
    Armor_Set_t                 Set_Clothes_Jarl_A_Yellow();
    Armor_Set_t                 Set_Clothes_Jarl_B();
    Armor_Set_t                 Set_Clothes_Jarl_C_Bright();
    Armor_Set_t                 Set_Clothes_Jarl_C_Dark();

    Armor_Set_t                 Set_Clothes_Jester();
    Armor_Set_t                 Set_Clothes_Jester_Cicero();

    Armor_Set_t                 Set_Clothes_Mage_Adept();
    Armor_Set_t                 Set_Clothes_Mage_Adept_Enchanted();
    Armor_Set_t                 Set_Clothes_Mage_Apprentice();
    Armor_Set_t                 Set_Clothes_Mage_Apprentice_Enchanted();
    Armor_Set_t                 Set_Clothes_Mage_Archmage();
    Armor_Set_t                 Set_Clothes_Mage_Archmage_Hooded();
    Armor_Set_t                 Set_Clothes_Mage_Expert();
    Armor_Set_t                 Set_Clothes_Mage_Expert_Enchanted();
    Armor_Set_t                 Set_Clothes_Mage_Master();
    Armor_Set_t                 Set_Clothes_Mage_Master_Enchanted();
    Armor_Set_t                 Set_Clothes_Mage_Novice();
    Armor_Set_t                 Set_Clothes_Mage_Novice_Enchanted();

    Armor_Set_t                 Set_Clothes_Merchant_Bright();
    Armor_Set_t                 Set_Clothes_Merchant_Dark();

    Armor_Set_t                 Set_Clothes_Miner_Bright();
    Armor_Set_t                 Set_Clothes_Miner_Dark();

    Armor_Set_t                 Set_Clothes_Monk();
    Armor_Set_t                 Set_Clothes_Monk_Hooded();

    Armor_Set_t                 Set_Clothes_Mourner();

    Armor_Set_t                 Set_Clothes_Mythic_Dawn();
    Armor_Set_t                 Set_Clothes_Mythic_Dawn_Hooded();

    Armor_Set_t                 Set_Clothes_Necromancer();
    Armor_Set_t                 Set_Clothes_Necromancer_Enchanted();
    Armor_Set_t                 Set_Clothes_Necromancer_Hooded();
    Armor_Set_t                 Set_Clothes_Necromancer_Hooded_Enchanted();

    Armor_Set_t                 Set_Clothes_Nocturnal();

    Armor_Set_t                 Set_Clothes_Prisoner();
    Armor_Set_t                 Set_Clothes_Prisoner_Bloody();
    Armor_Set_t                 Set_Clothes_Prisoner_Shirted();

    Armor_Set_t                 Set_Clothes_Psiijic();

    Armor_Set_t                 Set_Clothes_Redguard_Bright();
    Armor_Set_t                 Set_Clothes_Redguard_Dark();

    Armor_Set_t                 Set_Clothes_Robes_Black();
    Armor_Set_t                 Set_Clothes_Robes_Black_Hooded();
    Armor_Set_t                 Set_Clothes_Robes_Blue();
    Armor_Set_t                 Set_Clothes_Robes_Blue_Hooded();
    Armor_Set_t                 Set_Clothes_Robes_Blue_Hooded_Enchanted();
    Armor_Set_t                 Set_Clothes_Robes_Brown();
    Armor_Set_t                 Set_Clothes_Robes_Brown_Hooded();
    Armor_Set_t                 Set_Clothes_Robes_Green();
    Armor_Set_t                 Set_Clothes_Robes_Green_Hooded();
    Armor_Set_t                 Set_Clothes_Robes_Grey();
    Armor_Set_t                 Set_Clothes_Robes_Grey_Hooded();
    Armor_Set_t                 Set_Clothes_Robes_Red();
    Armor_Set_t                 Set_Clothes_Robes_Red_Hooded();

    Armor_Set_t                 Set_Clothes_Sheogorath();

    Armor_Set_t                 Set_Clothes_Shrouded();

    Armor_Set_t                 Set_Clothes_Skaal();

    Armor_Set_t                 Set_Clothes_Telvanni();
    Armor_Set_t                 Set_Clothes_Telvanni_Ildari();

    Armor_Set_t                 Set_Clothes_Temple_Priest();

    Armor_Set_t                 Set_Clothes_Thalmor();
    Armor_Set_t                 Set_Clothes_Thalmor_Hooded();

    Armor_Set_t                 Set_Clothes_Torturer();

    Armor_Set_t                 Set_Clothes_Ulfric();

    Armor_Set_t                 Set_Clothes_Vaermina_Priest();

    Armor_Set_t                 Set_Clothes_Vampire();

    Armor_Set_t                 Set_Clothes_Warlock();
    Armor_Set_t                 Set_Clothes_Warlock_Enchanted();
    Armor_Set_t                 Set_Clothes_Warlock_Hooded();
    Armor_Set_t                 Set_Clothes_Warlock_Hooded_Enchanted();

    Armor_Set_t                 Set_Clothes_Wedding_Dress();

    Armor_Set_t                 Set_Clothes_Wench();

    Armor_Set_t                 Set_Clothes_Wounded_Arivanya();
    Armor_Set_t                 Set_Clothes_Wounded_Susanna();
    */

    Member_Suit_Template_t Member_Suit_Template_t::Archer()
    {
        Member_Suit_Template_t suit_template;

        suit_template.armor = Vector_t<Armor_Set_t(*)()>
        {
            &skylib::Const::Armors::Set_Armor_Ancient_Falmer,
            &skylib::Const::Armors::Set_Armor_Ancient_Falmer_Pauldronless,

            &skylib::Const::Armors::Set_Armor_Chitin_Light,
            &skylib::Const::Armors::Set_Armor_Chitin_Light_Enchanted,

            &skylib::Const::Armors::Set_Armor_Dawnguard_Light_Brown,
            &skylib::Const::Armors::Set_Armor_Dawnguard_Light_Grey,
            &skylib::Const::Armors::Set_Armor_Dawnguard_Light_Red,

            &skylib::Const::Armors::Set_Armor_Dragonscale,
            &skylib::Const::Armors::Set_Armor_Dragonscale_Enchanted,

            &skylib::Const::Armors::Set_Armor_Elven,
            &skylib::Const::Armors::Set_Armor_Elven_Enchanted,
            &skylib::Const::Armors::Set_Armor_Elven_Pauldronless,
            &skylib::Const::Armors::Set_Armor_Elven_Pauldronless_Enchanted,

            &skylib::Const::Armors::Set_Armor_Forsworn,
            &skylib::Const::Armors::Set_Armor_Forsworn_Old_Gods,

            &skylib::Const::Armors::Set_Armor_Fur,
            &skylib::Const::Armors::Set_Armor_Fur_Topless,
            &skylib::Const::Armors::Set_Armor_Fur_Topless_Pauldron,
            &skylib::Const::Armors::Set_Armor_Fur_Saviors_Hide,
            &skylib::Const::Armors::Set_Armor_Fur_Sleeveless,

            &skylib::Const::Armors::Set_Armor_Hide,
            &skylib::Const::Armors::Set_Armor_Hide_Enchanted,
            &skylib::Const::Armors::Set_Armor_Hide_Predators_Grace,
            &skylib::Const::Armors::Set_Armor_Hide_Predators_Grace_Enchanted,
            &skylib::Const::Armors::Set_Armor_Hide_Studded,
            &skylib::Const::Armors::Set_Armor_Hide_Studded_Enchanted,

            &skylib::Const::Armors::Set_Armor_Imperial_Light,
            &skylib::Const::Armors::Set_Armor_Imperial_Light_Enchanted,
            &skylib::Const::Armors::Set_Armor_Imperial_Light_Studded,
            &skylib::Const::Armors::Set_Armor_Imperial_Light_Studded_Enchanted,

            &skylib::Const::Armors::Set_Armor_Leather,
            &skylib::Const::Armors::Set_Armor_Leather_Enchanted,

            &skylib::Const::Armors::Set_Armor_Morag_Tong,

            &skylib::Const::Armors::Set_Armor_Nightingale_Reward,
            &skylib::Const::Armors::Set_Armor_Nightingale_Reward_1,
            &skylib::Const::Armors::Set_Armor_Nightingale_Reward_2,
            &skylib::Const::Armors::Set_Armor_Nightingale_Reward_3,

            &skylib::Const::Armors::Set_Armor_Penitus_Oculatus,

            &skylib::Const::Armors::Set_Armor_Scaled,
            &skylib::Const::Armors::Set_Armor_Scaled_Enchanted,
            &skylib::Const::Armors::Set_Armor_Scaled_Horned,
            &skylib::Const::Armors::Set_Armor_Scaled_Horned_Enchanted,

            &skylib::Const::Armors::Set_Armor_Shrouded,
            &skylib::Const::Armors::Set_Armor_Shrouded_Ancient,
            &skylib::Const::Armors::Set_Armor_Shrouded_Maskless,
            &skylib::Const::Armors::Set_Armor_Shrouded_Short_Sleeved,
            &skylib::Const::Armors::Set_Armor_Shrouded_Tumblerbane,
            &skylib::Const::Armors::Set_Armor_Shrouded_Worn,

            &skylib::Const::Armors::Set_Armor_Stalhrim_Light,
            &skylib::Const::Armors::Set_Armor_Stalhrim_Light_Enchanted,
            &skylib::Const::Armors::Set_Armor_Stalhrim_Light_Deathbrand,
            &skylib::Const::Armors::Set_Armor_Stalhrim_Light_Deathbrand_Enchanted,

            &skylib::Const::Armors::Set_Armor_Stormcloak_Officer,

            &skylib::Const::Armors::Set_Armor_Thieves_Guild,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Alternate,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Blackguard,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Improved,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Karliah,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Master,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Torturer,
            &skylib::Const::Armors::Set_Armor_Thieves_Guild_Variant,

            &skylib::Const::Armors::Set_Armor_Tsun,

            &skylib::Const::Armors::Set_Armor_Vampire_Black,
            &skylib::Const::Armors::Set_Armor_Vampire_Black_Enchanted,
            &skylib::Const::Armors::Set_Armor_Vampire_Grey,
            &skylib::Const::Armors::Set_Armor_Vampire_Grey_Enchanted,
            &skylib::Const::Armors::Set_Armor_Vampire_Red,
            &skylib::Const::Armors::Set_Armor_Vampire_Red_Enchanted,
            &skylib::Const::Armors::Set_Armor_Vampire_Royal,
            &skylib::Const::Armors::Set_Armor_Vampire_Royal_Serana,
            &skylib::Const::Armors::Set_Armor_Vampire_Royal_Valerica,
        }.Random()();

        if (skylib::Math_t::Random_Bool()) {
            suit_template.weapon_a = skylib::Const::Weapons::Bow().Random();
            suit_template.ammo = skylib::Const::Ammos::Arrow().Random();
        } else {
            suit_template.weapon_a = skylib::Const::Weapons::Crossbow().Random();
            suit_template.ammo = skylib::Const::Ammos::Bolt().Random();
        }

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Civilized()
    {
        Member_Suit_Template_t suit_template;

        suit_template.armor = Vector_t<Armor_Set_t(*)()>
        {
            &skylib::Const::Armors::Set_Clothes_Bar_Keeper_Bright,
            &skylib::Const::Armors::Set_Clothes_Bar_Keeper_Dark,

            &skylib::Const::Armors::Set_Clothes_Black_Smith_Grey,
            &skylib::Const::Armors::Set_Clothes_Black_Smith_Red,

            &skylib::Const::Armors::Set_Clothes_Blind_Priest,

            &skylib::Const::Armors::Set_Clothes_Dunmer_Blue,
            &skylib::Const::Armors::Set_Clothes_Dunmer_Blue_Hooded,
            &skylib::Const::Armors::Set_Clothes_Dunmer_Brown,
            &skylib::Const::Armors::Set_Clothes_Dunmer_Brown_Hooded,
            &skylib::Const::Armors::Set_Clothes_Dunmer_Red,
            &skylib::Const::Armors::Set_Clothes_Dunmer_Red_Hooded,

            &skylib::Const::Armors::Set_Clothes_Emperor,

            &skylib::Const::Armors::Set_Clothes_Farm_A,
            &skylib::Const::Armors::Set_Clothes_Farm_B_Bright,
            &skylib::Const::Armors::Set_Clothes_Farm_B_Dark,
            &skylib::Const::Armors::Set_Clothes_Farm_C_Bright,
            &skylib::Const::Armors::Set_Clothes_Farm_C_Bright_Hooded,
            &skylib::Const::Armors::Set_Clothes_Farm_C_Dark,
            &skylib::Const::Armors::Set_Clothes_Farm_D_Bright,
            &skylib::Const::Armors::Set_Clothes_Farm_D_Dark,

            &skylib::Const::Armors::Set_Clothes_Fine_A_Blue,
            &skylib::Const::Armors::Set_Clothes_Fine_A_Green,
            &skylib::Const::Armors::Set_Clothes_Fine_B_Blue,
            &skylib::Const::Armors::Set_Clothes_Fine_B_Red,

            &skylib::Const::Armors::Set_Clothes_Jarl_A_Blue,
            &skylib::Const::Armors::Set_Clothes_Jarl_A_Green,
            &skylib::Const::Armors::Set_Clothes_Jarl_A_Yellow,
            &skylib::Const::Armors::Set_Clothes_Jarl_B,
            &skylib::Const::Armors::Set_Clothes_Jarl_C_Bright,
            &skylib::Const::Armors::Set_Clothes_Jarl_C_Dark,

            &skylib::Const::Armors::Set_Clothes_Mage_Adept,
            &skylib::Const::Armors::Set_Clothes_Mage_Adept_Enchanted,
            &skylib::Const::Armors::Set_Clothes_Mage_Apprentice,
            &skylib::Const::Armors::Set_Clothes_Mage_Apprentice_Enchanted,
            &skylib::Const::Armors::Set_Clothes_Mage_Archmage,
            &skylib::Const::Armors::Set_Clothes_Mage_Archmage_Hooded,
            &skylib::Const::Armors::Set_Clothes_Mage_Expert,
            &skylib::Const::Armors::Set_Clothes_Mage_Expert_Enchanted,
            &skylib::Const::Armors::Set_Clothes_Mage_Master,
            &skylib::Const::Armors::Set_Clothes_Mage_Master_Enchanted,
            &skylib::Const::Armors::Set_Clothes_Mage_Novice,
            &skylib::Const::Armors::Set_Clothes_Mage_Novice_Enchanted,

            &skylib::Const::Armors::Set_Clothes_Merchant_Bright,
            &skylib::Const::Armors::Set_Clothes_Merchant_Dark,

            &skylib::Const::Armors::Set_Clothes_Miner_Bright,
            &skylib::Const::Armors::Set_Clothes_Miner_Dark,

            &skylib::Const::Armors::Set_Clothes_Monk,
            &skylib::Const::Armors::Set_Clothes_Monk_Hooded,

            &skylib::Const::Armors::Set_Clothes_Mourner,

            &skylib::Const::Armors::Set_Clothes_Redguard_Bright,
            &skylib::Const::Armors::Set_Clothes_Redguard_Dark,

            &skylib::Const::Armors::Set_Clothes_Robes_Black,
            &skylib::Const::Armors::Set_Clothes_Robes_Black_Hooded,
            &skylib::Const::Armors::Set_Clothes_Robes_Blue,
            &skylib::Const::Armors::Set_Clothes_Robes_Blue_Hooded,
            &skylib::Const::Armors::Set_Clothes_Robes_Blue_Hooded_Enchanted,
            &skylib::Const::Armors::Set_Clothes_Robes_Brown,
            &skylib::Const::Armors::Set_Clothes_Robes_Brown_Hooded,
            &skylib::Const::Armors::Set_Clothes_Robes_Green,
            &skylib::Const::Armors::Set_Clothes_Robes_Green_Hooded,
            &skylib::Const::Armors::Set_Clothes_Robes_Grey,
            &skylib::Const::Armors::Set_Clothes_Robes_Grey_Hooded,
            &skylib::Const::Armors::Set_Clothes_Robes_Red,
            &skylib::Const::Armors::Set_Clothes_Robes_Red_Hooded,

            &skylib::Const::Armors::Set_Clothes_Wench,
        }.Random()();

        if (skylib::Math_t::Random_Bool()) {
            suit_template.weapon_a = skylib::Const::Weapons::Dagger().Random();
        }

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Combatant()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Coward()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Dangerous()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Eater()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Exterior()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Follower()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Guard()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Home()
    {
        Member_Suit_Template_t suit_template;

        suit_template.armor = skylib::Const::Armors::Set_Clothes_Farm_C_Dark();

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Immobile()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Inn()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Interior()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Mage()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Mannequin()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Member()
    {
        Member_Suit_Template_t suit_template;

        suit_template.armor = skylib::Const::Armors::Random_Set_Unweighted();

        suit_template.weapon_a = skylib::Const::Weapons::All().Random();

        if (suit_template.weapon_a->Is_Bow()) {
            suit_template.ammo = skylib::Const::Ammos::Arrow().Random();
        } else if (suit_template.weapon_a->Is_Crossbow()) {
            suit_template.ammo = skylib::Const::Ammos::Bolt().Random();
        }

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Sandboxer()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Settlement()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Sitter()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Sleeper()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Thrall()
    {
        Member_Suit_Template_t suit_template;

        suit_template.armor = Vector_t<Armor_Set_t(*)()>
        {
            &skylib::Const::Armors::Set_Armor_Falmer,

            &skylib::Const::Armors::Set_Armor_Forsworn,
            &skylib::Const::Armors::Set_Armor_Forsworn_Old_Gods,

            &skylib::Const::Armors::Set_Armor_Fur_Topless,

            &skylib::Const::Armors::Set_Clothes_Bandages,

            &skylib::Const::Armors::Set_Clothes_Beggar,

            &skylib::Const::Armors::Set_Clothes_Executionee_Bright,
            &skylib::Const::Armors::Set_Clothes_Executionee_Dark,

            &skylib::Const::Armors::Set_Clothes_Nocturnal,

            &skylib::Const::Armors::Set_Clothes_Prisoner,
            &skylib::Const::Armors::Set_Clothes_Prisoner_Bloody,
            &skylib::Const::Armors::Set_Clothes_Prisoner_Shirted,

            &skylib::Const::Armors::Set_Clothes_Wedding_Dress,

            &skylib::Const::Armors::Set_Clothes_Wench,
        }.Random()();
        suit_template.armor.forearm = none<Armor_t*>();

        suit_template.weapon_a = Vector_t<some<Weapon_t*>(*)()>
        {
            &skylib::Const::Weapon::Dagger_Iron_Fork,
            &skylib::Const::Weapon::Dagger_Iron_Knife,
            &skylib::Const::Weapon::Dagger_Iron_Shiv,
        }.Random()();

        return suit_template;
    }

    Member_Suit_Template_t Member_Suit_Template_t::Warrior()
    {
        Member_Suit_Template_t suit_template;

        return suit_template;
    }

    Member_Suit_Template_t::Member_Suit_Template_t() :
        armor(),
        weapon_a(none<Weapon_t*>()),
        weapon_b(none<Weapon_t*>()),
        ammo(none<Ammo_t*>())
    {
    }

    Member_Suit_Template_t::Member_Suit_Template_t(const Member_Suit_Template_t& other) :
        armor(other.armor),
        weapon_a(other.weapon_a),
        weapon_b(other.weapon_b),
        ammo(other.ammo)
    {
    }

    Member_Suit_Template_t::Member_Suit_Template_t(Member_Suit_Template_t&& other) noexcept :
        armor(std::move(other.armor)),
        weapon_a(std::move(other.weapon_a)),
        weapon_b(std::move(other.weapon_b)),
        ammo(std::move(other.ammo))
    {
    }

    Member_Suit_Template_t& Member_Suit_Template_t::operator =(const Member_Suit_Template_t& other)
    {
        if (this != std::addressof(other)) {
            this->armor = other.armor;
            this->weapon_a = other.weapon_a;
            this->weapon_b = other.weapon_b;
            this->ammo = other.ammo;
        }
        return *this;
    }

    Member_Suit_Template_t& Member_Suit_Template_t::operator =(Member_Suit_Template_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->armor = std::move(other.armor);
            this->weapon_a = std::move(other.weapon_a);
            this->weapon_b = std::move(other.weapon_b);
            this->ammo = std::move(other.ammo);
        }
        return *this;
    }

    Member_Suit_Template_t::~Member_Suit_Template_t()
    {
    }

}}
