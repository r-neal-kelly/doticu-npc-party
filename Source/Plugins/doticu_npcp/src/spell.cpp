/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "form.h"

namespace doticu_npcp { namespace Spell {

    Bool_t Can_Damage_Health(Spell_t* spell)
    {
        if (spell) {
            if (spell->hostile > 0) {
                Spell_t::EffectItem** effect_items = spell->effectItemList.entries;
                for (size_t idx = 0, count = spell->effectItemList.count; idx < count; idx += 1) {
                    Spell_t::EffectItem* effect_item = effect_items[idx];
                    if (effect_item && effect_item->mgef) {
                        using Props = Magic_Effect_t::Properties;
                        Props& props = effect_item->mgef->properties;
                        if ((props.flags & Props::kEffectType_Detrimental) &&
                            (props.archetype == Props::kArchetype_ValueMod) &&
                            (props.primaryValue == static_cast<UInt32>(Actor_Value_t::HEALTH))) {
                            return true;
                        }
                    }
                }
                return false;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

}}
