/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/quest.h"

#include "chests.h"
#include "mcm_main.h"

namespace doticu_npcp { namespace MCM {

    class Chests_t :
        public Quest_t
    {
    public:
        static constexpr size_t MAX_CUSTOM_CHESTS = doticu_npcp::Chests_t::MAX_CUSTOM_CHESTS;

    protected:
        class Options
        {
        public:
            Int_t input         = -1;

            Int_t swords        = -1;
            Int_t greatswords   = -1;
            Int_t waraxes       = -1;
            Int_t battleaxes    = -1;
            Int_t maces         = -1;
            Int_t warhammers    = -1;
            Int_t daggers       = -1;
            Int_t staves        = -1;
            Int_t bows          = -1;
            Int_t ammo          = -1;
            Int_t other_weapons = -1;

            Int_t light_armor   = -1;
            Int_t heavy_armor   = -1;
            Int_t shields       = -1;
            Int_t jewelry       = -1;
            Int_t clothes       = -1;

            Int_t potions       = -1;
            Int_t poisons       = -1;
            Int_t ingredients   = -1;
            Int_t food          = -1;

            Int_t soul_gems     = -1;
            Int_t scrolls       = -1;
            Int_t metals        = -1;
            Int_t leather       = -1;
            Int_t gems          = -1;
            Int_t clutter       = -1;
            Int_t keys          = -1;
            Int_t other_misc    = -1;

            Int_t spell_tomes   = -1;
            Int_t recipes       = -1;
            Int_t a_books       = -1;
            Int_t b_books       = -1;
            Int_t c_books       = -1;
            Int_t d_books       = -1;
            Int_t e_books       = -1;
            Int_t f_books       = -1;
            Int_t g_books       = -1;
            Int_t h_books       = -1;
            Int_t i_books       = -1;
            Int_t j_books       = -1;
            Int_t k_books       = -1;
            Int_t l_books       = -1;
            Int_t m_books       = -1;
            Int_t n_books       = -1;
            Int_t o_books       = -1;
            Int_t p_books       = -1;
            Int_t q_books       = -1;
            Int_t r_books       = -1;
            Int_t s_books       = -1;
            Int_t t_books       = -1;
            Int_t u_books       = -1;
            Int_t v_books       = -1;
            Int_t w_books       = -1;
            Int_t x_books       = -1;
            Int_t y_books       = -1;
            Int_t z_books       = -1;
            Int_t other_books   = -1;

            Int_t custom_chests[MAX_CUSTOM_CHESTS];
            Int_t custom_renames[MAX_CUSTOM_CHESTS];

        public:
            Options();
        };

        class Save
        {
        public:
            Vector_t<String_t> custom_names;
        };

    protected:
        static Options  options;
        static Save     save;

    public:
        static some<Chests_t*>      Self();
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static some<V::Object_t*>   Object();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static V::Variable_tt<Vector_t<String_t>>& Custom_Names();

    public:
        static void Initialize();
        static void Before_Save();
        static void After_Load();

    public:
        static void On_Config_Open();
        static void On_Config_Close();
        static void On_Page_Open(Bool_t is_refresh, const Latent_ID_t latent_id);
        static void On_Option_Select(Int_t option, const Latent_ID_t latent_id);
        static void On_Option_Menu_Open(Int_t option, const Latent_ID_t latent_id);
        static void On_Option_Menu_Accept(Int_t option, Int_t index, const Latent_ID_t latent_id);
        static void On_Option_Slider_Open(Int_t option, const Latent_ID_t latent_id);
        static void On_Option_Slider_Accept(Int_t option, Float_t value, const Latent_ID_t latent_id);
        static void On_Option_Input_Accept(Int_t option, String_t value, const Latent_ID_t latent_id);
        static void On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, const Latent_ID_t latent_id);
        static void On_Option_Default(Int_t option, const Latent_ID_t latent_id);
        static void On_Option_Highlight(Int_t option, const Latent_ID_t latent_id);
    };

}}
