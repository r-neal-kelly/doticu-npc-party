/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_chests.h"
#include "mcm_main.h"
#include "strings.h"

namespace doticu_npcp { namespace MCM {

    Latent_ID_t::Latent_ID_t(maybe<V::Stack_ID_t> stack_id) :
        stack_id(stack_id)
    {
    }

    Latent_ID_t::Latent_ID_t(Latent_ID_t&& other) noexcept :
        stack_id(std::exchange(other.stack_id, none<V::Stack_ID_t>()))
    {
    }

    Latent_ID_t::~Latent_ID_t()
    {
        if (this->stack_id) {
            V::Machine_t::Self()->Return_Latent_Function(stack_id(), V::Variable_t());
        }
    }

    std::mutex      Main_t::event_mutex = std::mutex();
    Main_t::Save    Main_t::save        = Main_t::Save();

    some<Main_t*>       Main_t::Self()          { return Consts_t::NPCP::Quest::Control(); }
    String_t            Main_t::Class_Name()    { DEFINE_CLASS_NAME("doticu_npcp_mcm_main"); }
    some<V::Class_t*>   Main_t::Class()         { DEFINE_CLASS(); }
    some<V::Object_t*>  Main_t::Object()        { DEFINE_OBJECT_STATIC(); }

    void Main_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        mcmlib::Config_Base_t::Register_Me(machine);

        String_t class_name = Class_Name();

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)      \
        SKYLIB_M                                                                        \
            BIND_METHOD(machine, class_name, Main_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        METHOD("OnConfigOpen", true, void, On_Config_Open);
        METHOD("OnConfigClose", true, void, On_Config_Close);
        METHOD("OnPageReset", true, void, On_Page_Open, String_t);
        METHOD("OnOptionSelect", true, void, On_Option_Select, Int_t);
        METHOD("OnOptionMenuOpen", true, void, On_Option_Menu_Open, Int_t);
        METHOD("OnOptionMenuAccept", true, void, On_Option_Menu_Accept, Int_t, Int_t);
        METHOD("OnOptionSliderOpen", true, void, On_Option_Slider_Open, Int_t);
        METHOD("OnOptionSliderAccept", true, void, On_Option_Slider_Accept, Int_t, Float_t);
        METHOD("OnOptionInputAccept", true, void, On_Option_Input_Accept, Int_t, String_t);
        METHOD("OnOptionKeymapChange", true, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        METHOD("OnOptionDefault", true, void, On_Option_Default, Int_t);
        METHOD("OnOptionHighlight", true, void, On_Option_Highlight, Int_t);

        #undef METHOD

        Chests_t::Register_Me(machine);
    }

    V::Variable_tt<String_t>& Main_t::Current_Page() { DEFINE_VARIABLE_REFERENCE(String_t, "p_current_page"); }

    void Main_t::Initialize()
    {
        std::lock_guard<std::mutex> guard(event_mutex);

        save = Save();
        save.current_page = Strings_t::SETTINGS;

        Chests_t::Initialize();
    }

    void Main_t::Before_Save()
    {
        std::lock_guard<std::mutex> guard(event_mutex);

        Current_Page() = save.current_page;

        Chests_t::Before_Save();
    }

    void Main_t::After_Load()
    {
        std::lock_guard<std::mutex> guard(event_mutex);

        save.current_page = Current_Page();

        Chests_t::After_Load();
    }

    Bool_t Main_t::On_Config_Open(V::Stack_ID_t stack_id)
    {
        std::lock_guard<std::mutex> guard(this->event_mutex);

        Latent_ID_t latent_id(stack_id);

        Vector_t<String_t> pages;
        pages.reserve(9);
        pages.push_back(Strings_t::FOLLOWERS);
        pages.push_back(Strings_t::MEMBERS);
        pages.push_back(Strings_t::SETTLERS);
        pages.push_back(Strings_t::MANNEQUINS);
        pages.push_back(Strings_t::FILTER);
        pages.push_back(Strings_t::CHESTS);
        pages.push_back(Strings_t::SETTINGS);
        pages.push_back(Strings_t::HOTKEYS);
        pages.push_back(Strings_t::LOGS);
        Pages() = pages;

        Chests_t::On_Config_Open();

        return true;
    }

    Bool_t Main_t::On_Config_Close(V::Stack_ID_t stack_id)
    {
        std::lock_guard<std::mutex> guard(this->event_mutex);

        Latent_ID_t latent_id(stack_id);

        Chests_t::On_Config_Close();

        return true;
    }

    Bool_t Main_t::On_Page_Open(V::Stack_ID_t stack_id, String_t page)
    {

    }

    Bool_t Main_t::On_Option_Select(V::Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Menu_Open(V::Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Menu_Accept(V::Stack_ID_t stack_id, Int_t option, Int_t index)
    {

    }

    Bool_t Main_t::On_Option_Slider_Open(V::Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Slider_Accept(V::Stack_ID_t stack_id, Int_t option, Float_t value)
    {

    }

    Bool_t Main_t::On_Option_Input_Accept(V::Stack_ID_t stack_id, Int_t option, String_t value)
    {

    }

    Bool_t Main_t::On_Option_Keymap_Change(V::Stack_ID_t stack_id, Int_t option, Int_t key, String_t conflict, String_t mod)
    {

    }

    Bool_t Main_t::On_Option_Default(V::Stack_ID_t stack_id, Int_t option)
    {

    }

    Bool_t Main_t::On_Option_Highlight(V::Stack_ID_t stack_id, Int_t option)
    {

    }

}}
