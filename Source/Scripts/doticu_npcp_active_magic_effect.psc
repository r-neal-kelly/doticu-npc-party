; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_active_magic_effect extends ActiveMagicEffect

function On_Effect_Start(ActiveMagicEffect active_magic_effect, Actor target, Actor caster) native global
event OnEffectStart(Actor target, Actor caster)
    On_Effect_Start(self as ActiveMagicEffect, target, caster)
endEvent
