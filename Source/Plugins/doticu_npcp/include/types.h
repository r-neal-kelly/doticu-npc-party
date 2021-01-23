/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcp {

    typedef Projectile      Projectile_t;
    typedef BGSProjectile   Projectile_Base_t;
    typedef BGSVoiceType    Voice_Type_t;

    class Process_Lists_t {
    public:
        static Process_Lists_t* Self();
    public:
        void Stop_Combat_Alarm(Actor_t* actor, Bool_t dont_end_alarm = false);
    };

}
