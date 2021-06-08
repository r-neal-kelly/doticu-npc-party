/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.inl"
#include "doticu_skylib/game.h"

#include "npcp.h"

namespace doticu_skylib { namespace doticu_npcp {

    template <typename T>
    inline maybe<T*> NPCP_t::Deserialized_Form(maybe<Form_ID_t> form_id)
    {
        maybe<Form_t*> form = none<Form_t*>();
        if (form_id) {
            if (form_id.Is_Dynamic()) {
                form = Game_t::Form(form_id());
            } else if (form_id.Is_Heavy()) {
                maybe<Heavy_Mod_Index_t> mod_index = form_id.Heavy_Mod_Index();
                maybe<Heavy_Form_Index_t> form_index = form_id.Heavy_Form_Index();
                const Vector_t<maybe<Mod_t*>>& mods = Deserialized_Heavy_Mods();
                if (mod_index && form_index && mod_index() < mods.size() && mods[mod_index()]) {
                    form = Game_t::Form(mods[mod_index()](), form_index());
                }
            } else {
                maybe<Light_Mod_Index_t> mod_index = form_id.Light_Mod_Index();
                maybe<Light_Form_Index_t> form_index = form_id.Light_Form_Index();
                const Vector_t<maybe<Mod_t*>>& mods = Deserialized_Light_Mods();
                if (mod_index && form_index && mod_index() < mods.size() && mods[mod_index()]) {
                    form = Game_t::Form(mods[mod_index()](), form_index());
                }
            }
        }

        if (form) {
            return form->As<T>();
        } else {
            return none<T*>();
        }
    }

    template <typename T>
    inline void NPCP_t::Write(std::ofstream& file, const T& data)
    {
        if (file.good()) {
            file.write(reinterpret_cast<const char*>(&data), sizeof(data));
        }
    }

    template <typename T>
    inline void NPCP_t::Read(std::ifstream& file, T& data)
    {
        if (file.good()) {
            file.read(reinterpret_cast<char*>(&data), sizeof(data));
        }
    }

    template <typename T>
    inline void NPCP_t::Write_Form(std::ofstream& file, const maybe<T*>& form)
    {
        if (file.good()) {
            maybe<Form_ID_t> form_id = form ? form->form_id : none<Form_ID_t>();
            file.write(reinterpret_cast<const char*>(&form_id), sizeof(form_id));
        }
    }

    template <typename T>
    inline void NPCP_t::Read_Form(std::ifstream& file, maybe<T*>& form)
    {
        if (file.good()) {
            maybe<Form_ID_t> form_id = none<Form_ID_t>();
            file.read(reinterpret_cast<char*>(&form_id), sizeof(form_id));
            form = Deserialized_Form<T>(form_id);
        }
    }

}}
