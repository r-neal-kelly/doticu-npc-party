/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/virtual_stack_id.h"

#include "doticu_mcmlib/config_base.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace MCM {

    class Latent_ID_t
    {
    public:
        const maybe<V::Stack_ID_t> stack_id;

    public:
        Latent_ID_t(maybe<V::Stack_ID_t> stack_id);
        Latent_ID_t(const Latent_ID_t& other) = delete;
        Latent_ID_t(Latent_ID_t&& other) noexcept;
        Latent_ID_t& operator=(const Latent_ID_t& other) = delete;
        Latent_ID_t& operator=(Latent_ID_t&& other) noexcept = delete;
        ~Latent_ID_t();
    };

    class Main_t :
        public mcmlib::Config_Base_t
    {
    protected:
        class Save_Data
        {
        public:
            String_t current_page = "";
        };

    protected:
        static std::mutex   event_mutex;
        static Save_Data    save_data;

    public:
        static some<Main_t*>        Self();
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static some<V::Object_t*>   Object();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static V::Variable_tt<String_t>& Current_Page();

    public:
        static void Initialize();
        static void Before_Save();
        static void After_Load();

    public:
        Bool_t On_Config_Open(V::Stack_ID_t stack_id);
        Bool_t On_Config_Close(V::Stack_ID_t stack_id);
        Bool_t On_Page_Open(V::Stack_ID_t stack_id, String_t page);
        Bool_t On_Option_Select(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Open(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Menu_Accept(V::Stack_ID_t stack_id, Int_t option, Int_t index);
        Bool_t On_Option_Slider_Open(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Slider_Accept(V::Stack_ID_t stack_id, Int_t option, Float_t value);
        Bool_t On_Option_Input_Accept(V::Stack_ID_t stack_id, Int_t option, String_t value);
        Bool_t On_Option_Keymap_Change(V::Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod);
        Bool_t On_Option_Default(V::Stack_ID_t stack_id, Int_t option);
        Bool_t On_Option_Highlight(V::Stack_ID_t stack_id, Int_t option);
    };

}}
