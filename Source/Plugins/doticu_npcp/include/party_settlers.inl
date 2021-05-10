/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/form_owner.h"
#include "doticu_skylib/furniture.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/package.h"
#include "doticu_skylib/package_data.h"
#include "doticu_skylib/package_location.h"
#include "doticu_skylib/package_value.h"
#include "doticu_skylib/package_value_bool.h"
#include "doticu_skylib/package_value_float.h"
#include "doticu_skylib/package_value_int.h"
#include "doticu_skylib/package_value_list.h"
#include "doticu_skylib/package_value_location.h"
#include "doticu_skylib/package_value_reference.h"
#include "doticu_skylib/package_value_target.h"
#include "doticu_skylib/package_value_topic.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/static.h"

#include "consts.h"
#include "intrinsic.h"
#include "party_settlers.h"

namespace doticu_npcp { namespace Party {

    template <typename T>
    inline some<Misc_t*> Settlers_t::Token()
    {
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Sandboxer_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sandboxer();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Sleeper_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sleeper();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Sitter_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sitter();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Eater_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Eater();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Guard_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Guard();
    }

    template <typename T>
    inline some<Form_List_t*> Settlers_t::Packages()
    {
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Sandboxer_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Sandboxer_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Sleeper_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Sleeper_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Sitter_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Sitter_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Eater_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Eater_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Guard_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Guard_Packages();
    }

    template <typename T>
    inline some<Package_t*> Settlers_t::Package(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Packages<T>()->At(valid_settler_id())->As_Package()();
    }

    template <typename T>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags()
    {
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Sandboxer_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.sandboxer_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Sleeper_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.sleeper_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Sitter_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.sitter_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Eater_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.eater_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Guard_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.guard_flags);
    }

    template <typename T>
    inline Settler_Flags_e& Settlers_t::Flags(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Flags<T>()[settler_id()];
    }

    template <typename T>
    inline Bool_t Settlers_t::Is_Flagged(some<Settler_ID_t> settler_id, Settler_Flags_e flag)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Flags<T>(settler_id).Is_Flagged(flag);
    }

    template <typename T>
    inline void Settlers_t::Is_Flagged(some<Settler_ID_t> settler_id, Settler_Flags_e flag, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Flags<T>(settler_id).Is_Flagged(flag, value);
    }

    template <typename T>
    inline Bool_t Settlers_t::Is_Enabled(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Is_Flagged<T>(settler_id, T::Flags_e::IS_ENABLED);
    }

    template <typename T>
    inline void Settlers_t::Is_Enabled(some<Settler_ID_t> settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Is_Flagged<T>(settler_id, T::Flags_e::IS_ENABLED, value);
    }

    template <typename T>
    inline Bool_t Settlers_t::Is_Currently_Enabled(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        if (Is_Enabled<T>(settler_id)) {
            return true; // we need to check the time on Calendar_t, but it's missing minutes. where is that stored? in ini?
        } else {
            return false;
        }
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Swimming(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SWIMMING);
    }

    template <typename T>
    void Settlers_t::Allow_Swimming(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SWIMMING, value);
    }

    template <typename T>
    Bool_t Settlers_t::Always_Sneak(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALWAYS_SNEAK);
    }

    template <typename T>
    void Settlers_t::Always_Sneak(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALWAYS_SNEAK, value);
    }

    template <typename T>
    Bool_t Settlers_t::Ignore_Combat(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::IGNORE_COMBAT);
    }

    template <typename T>
    void Settlers_t::Ignore_Combat(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::IGNORE_COMBAT, value);
    }

    template <typename T>
    Bool_t Settlers_t::Keep_Weapons_Drawn(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::KEEP_WEAPONS_DRAWN);
    }

    template <typename T>
    void Settlers_t::Keep_Weapons_Drawn(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::KEEP_WEAPONS_DRAWN, value);
    }

    template <typename T>
    Bool_t Settlers_t::Hide_Weapons(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::HIDE_WEAPONS);
    }

    template <typename T>
    void Settlers_t::Hide_Weapons(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::HIDE_WEAPONS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Skip_Combat_Alert(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::SKIP_COMBAT_ALERT);
    }

    template <typename T>
    void Settlers_t::Skip_Combat_Alert(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::SKIP_COMBAT_ALERT, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Hellos_To_Player(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_HELLOS_TO_PLAYER);
    }

    template <typename T>
    void Settlers_t::Allow_Hellos_To_Player(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_HELLOS_TO_PLAYER, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Hellos_To_NPCs(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_HELLOS_TO_NPCS);
    }

    template <typename T>
    void Settlers_t::Allow_Hellos_To_NPCs(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_HELLOS_TO_NPCS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Idle_Chatter(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_IDLE_CHATTER);
    }

    template <typename T>
    void Settlers_t::Allow_Idle_Chatter(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_IDLE_CHATTER, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Aggro_Radius(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_AGGRO_RADIUS);
    }

    template <typename T>
    void Settlers_t::Allow_Aggro_Radius(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_AGGRO_RADIUS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_World_Interactions(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_WORLD_INTERACTIONS);
    }

    template <typename T>
    void Settlers_t::Allow_World_Interactions(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_WORLD_INTERACTIONS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Comment_On_Friendly_Fire(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::COMMENT_ON_FRIENDLY_FIRE);
    }

    template <typename T>
    void Settlers_t::Comment_On_Friendly_Fire(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::COMMENT_ON_FRIENDLY_FIRE, value);
    }

    template <typename T>
    Bool_t Settlers_t::Inspect_Corpses(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::INSPECT_CORPSES);
    }

    template <typename T>
    void Settlers_t::Inspect_Corpses(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::INSPECT_CORPSES, value);
    }

    template <typename T>
    Bool_t Settlers_t::Observe_Combat(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::OBSERVE_COMBAT);
    }

    template <typename T>
    void Settlers_t::Observe_Combat(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::OBSERVE_COMBAT, value);
    }

    template <typename T>
    Bool_t Settlers_t::React_To_Player_Actions(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::REACT_TO_PLAYER_ACTIONS);
    }

    template <typename T>
    void Settlers_t::React_To_Player_Actions(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::REACT_TO_PLAYER_ACTIONS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Already_Held_Food(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_ALREADY_HELD_FOOD);
    }

    template <typename T>
    void Settlers_t::Allow_Already_Held_Food(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_ALREADY_HELD_FOOD, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Conversation(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_CONVERSATION);
    }

    template <typename T>
    void Settlers_t::Allow_Conversation(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_CONVERSATION, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Eating(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_EATING);
    }

    template <typename T>
    void Settlers_t::Allow_Eating(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_EATING, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Fake_Food(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_FAKE_FOOD);
    }

    template <typename T>
    void Settlers_t::Allow_Fake_Food(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_FAKE_FOOD, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Horse_Riding(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_HORSE_RIDING);
    }

    template <typename T>
    void Settlers_t::Allow_Horse_Riding(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_HORSE_RIDING, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Idle_Markers(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_IDLE_MARKERS);
    }

    template <typename T>
    void Settlers_t::Allow_Idle_Markers(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_IDLE_MARKERS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Sitting(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SITTING);
    }

    template <typename T>
    void Settlers_t::Allow_Sitting(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SITTING, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Sleeping(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SLEEPING);
    }

    template <typename T>
    void Settlers_t::Allow_Sleeping(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SLEEPING, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Special_Furniture(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SPECIAL_FURNITURE);
    }

    template <typename T>
    void Settlers_t::Allow_Special_Furniture(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_SPECIAL_FURNITURE, value);
    }

    template <typename T>
    Bool_t Settlers_t::Allow_Wandering(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_WANDERING);
    }

    template <typename T>
    void Settlers_t::Allow_Wandering(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ALLOW_WANDERING, value);
    }

    template <typename T>
    Bool_t Settlers_t::Lock_Doors(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::LOCK_DOORS);
    }

    template <typename T>
    void Settlers_t::Lock_Doors(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::LOCK_DOORS, value);
    }

    template <typename T>
    Bool_t Settlers_t::Only_Preferred_Path(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::ONLY_PREFERRED_PATH);
    }

    template <typename T>
    void Settlers_t::Only_Preferred_Path(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::ONLY_PREFERRED_PATH, value);
    }

    template <typename T>
    Bool_t Settlers_t::Stop_Movement(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::STOP_MOVEMENT);
    }

    template <typename T>
    void Settlers_t::Stop_Movement(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::STOP_MOVEMENT, value);
    }

    template <typename T>
    Bool_t Settlers_t::Unlock_On_Arrival(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::UNLOCK_ON_ARRIVAL);
    }

    template <typename T>
    void Settlers_t::Unlock_On_Arrival(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::UNLOCK_ON_ARRIVAL, value);
    }

    template <typename T>
    Bool_t Settlers_t::Warn_Before_Locking(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Is_Flagged<T>(valid_settler_id, T::Flags_e::WARN_BEFORE_LOCKING);
    }

    template <typename T>
    void Settlers_t::Warn_Before_Locking(some<Settler_ID_t> valid_settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Is_Flagged<T>(valid_settler_id, T::Flags_e::WARN_BEFORE_LOCKING, value);
    }

    template <typename T>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers()
    {
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Sandboxer_t>()
    {
        return this->save_state.sandboxer_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Sleeper_t>()
    {
        return this->save_state.sleeper_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Sitter_t>()
    {
        return this->save_state.sitter_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Eater_t>()
    {
        return this->save_state.eater_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Guard_t>()
    {
        return this->save_state.guard_markers;
    }

    template <typename T>
    inline some<Reference_t*> Settlers_t::Marker(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Reference_t*>& marker = Markers<T>()[valid_settler_id()];
        if (!marker || !marker->Is_Valid() || marker->Is_Deleted()) {
            marker = Static_t::Create_X_Marker(Member_t(valid_settler_id).Actor()())();
            SKYLIB_ASSERT_SOME(marker);
        }

        return marker();
    }

    template <typename T>
    inline void Settlers_t::Move_Marker(some<Settler_ID_t> valid_settler_id, some<Reference_t*> to)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(to);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Marker<T>(valid_settler_id)->Move_To_Orbit(skylib::Const::Actor::Player(), 0.0f, 180.0f);
    }

    template <>
    inline void Settlers_t::Move_Marker<Sleeper_t>(some<Settler_ID_t> valid_settler_id, some<Reference_t*> to)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(to);
        SKYLIB_ASSERT(Is_Enabled<Sleeper_t>(valid_settler_id));

        Marker<Sleeper_t>(valid_settler_id)->Move_To_Orbit(skylib::Const::Actor::Player(), 0.0f, 180.0f);

        maybe<Reference_t*> bed = Bed<Sleeper_t>(valid_settler_id);
        if (bed) {
            bed->Move_To_Orbit(skylib::Const::Actor::Player(), 0.0f, 180.0f);
        }
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Sandboxer_t>()
    {
        return this->save_state.sandboxer_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Sleeper_t>()
    {
        return this->save_state.sleeper_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Sitter_t>()
    {
        return this->save_state.sitter_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Eater_t>()
    {
        return this->save_state.eater_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Guard_t>()
    {
        return this->save_state.guard_radii;
    }

    template <typename T>
    inline some<Settler_Radius_t> Settlers_t::Radius(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Radius_t>& radius = Radii<T>()[valid_settler_id()];
        if (!radius) {
            radius = DEFAULT_RADIUS;
            SKYLIB_ASSERT_SOME(radius);
        }

        return radius();
    }

    template <typename T>
    inline void Settlers_t::Radius(some<Settler_ID_t> valid_settler_id, some<Settler_Radius_t> radius)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(radius);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Radii<T>()[valid_settler_id()] = radius;
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Sandboxer_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Sleeper_t>()
    {
        return this->save_state.sleeper_times;
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Sitter_t>()
    {
        return this->save_state.sitter_times;
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Eater_t>()
    {
        return this->save_state.eater_times;
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Guard_t>()
    {
        return this->save_state.guard_times;
    }

    template <typename T>
    inline some<Settler_Time_t> Settlers_t::Time(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Time_t>& time = Times<T>()[valid_settler_id()];
        if (!time) {
            time = DEFAULT_TIME;
            SKYLIB_ASSERT_SOME(time);
        }

        return time();
    }

    template <>
    inline some<Settler_Time_t> Settlers_t::Time<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time(some<Settler_ID_t> valid_settler_id, some<Settler_Time_t> time)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(time);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Times<T>()[valid_settler_id()] = time;
    }

    template <>
    inline void Settlers_t::Time<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_t> time) = delete;

    template <typename T>
    inline some<Settler_Time_AM_PM_e> Settlers_t::Time_AM_PM(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Time<T>(valid_settler_id)().AM_PM();
    }

    template <>
    inline some<Settler_Time_AM_PM_e> Settlers_t::Time_AM_PM<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time_AM_PM(some<Settler_ID_t> valid_settler_id, some<Settler_Time_AM_PM_e> am_pm)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(am_pm);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Time_t> time = Time<T>(valid_settler_id);
        time().AM_PM(am_pm);
        Time<T>(valid_settler_id, time);
    }

    template <>
    inline void Settlers_t::Time_AM_PM<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_AM_PM_e> am_pm) = delete;

    template <typename T>
    inline some<Settler_Time_Hour_t> Settlers_t::Time_Hour(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Time<T>(valid_settler_id)().Hour();
    }

    template <>
    inline some<Settler_Time_Hour_t> Settlers_t::Time_Hour<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time_Hour(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Hour_t> hour)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(hour);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Time_t> time = Time<T>(valid_settler_id);
        time().Hour(hour);
        Time<T>(valid_settler_id, time);
    }

    template <>
    inline void Settlers_t::Time_Hour<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Hour_t> hour) = delete;

    template <typename T>
    inline some<Settler_Time_Minute_t> Settlers_t::Time_Minute(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Time<T>(valid_settler_id)().Minute();
    }

    template <>
    inline some<Settler_Time_Minute_t> Settlers_t::Time_Minute<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time_Minute(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Minute_t> minute)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(minute);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Time_t> time = Time<T>(valid_settler_id);
        time().Minute(minute);
        Time<T>(valid_settler_id, time);
    }

    template <>
    inline void Settlers_t::Time_Minute<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Minute_t> minute) = delete;

    template <typename T>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Sandboxer_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Sleeper_t>()
    {
        return this->save_state.sleeper_durations;
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Sitter_t>()
    {
        return this->save_state.sitter_durations;
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Eater_t>()
    {
        return this->save_state.eater_durations;
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Guard_t>()
    {
        return this->save_state.guard_durations;
    }

    template <typename T>
    inline some<Settler_Duration_t> Settlers_t::Duration(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Duration_t>& duration = Durations<T>()[valid_settler_id()];
        if (!duration) {
            duration = DEFAULT_DURATION;
            SKYLIB_ASSERT_SOME(duration);
        }

        return duration();
    }

    template <>
    inline some<Settler_Duration_t> Settlers_t::Duration<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Duration(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_t> duration)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(duration);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Durations<T>()[valid_settler_id()] = duration;
    }

    template <>
    inline void Settlers_t::Duration<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_t> duration) = delete;

    template <typename T>
    inline some<Settler_Duration_Hours_t> Settlers_t::Duration_Hours(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Duration<T>(valid_settler_id)().Hours();
    }

    template <>
    inline some<Settler_Duration_Hours_t> Settlers_t::Duration_Hours<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Duration_Hours(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_Hours_t> hours)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(hours);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Duration_t> duration = Duration<T>(valid_settler_id);
        duration().Hours(hours);
        Duration<T>(valid_settler_id, duration);
    }

    template <>
    inline void Settlers_t::Duration_Hours<Sandboxer_t>(some<Settler_ID_t> valid_settler_id,
                                                        some<Settler_Duration_Hours_t> hours) = delete;

    template <typename T>
    inline some<Settler_Duration_Minutes_t> Settlers_t::Duration_Minutes(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Duration<T>(valid_settler_id)().Minutes();
    }

    template <>
    inline some<Settler_Duration_Minutes_t> Settlers_t::Duration_Minutes<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Duration_Minutes(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_Minutes_t> minutes)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(minutes);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Duration_t> duration = Duration<T>(valid_settler_id);
        duration().Minutes(minutes);
        Duration<T>(valid_settler_id, duration);
    }

    template <>
    inline void Settlers_t::Duration_Minutes<Sandboxer_t>(some<Settler_ID_t> valid_settler_id,
                                                          some<Settler_Duration_Minutes_t> minutes) = delete;

    template <typename T>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Sandboxer_t>()
    {
        return this->save_state.sandboxer_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Sleeper_t>()
    {
        return this->save_state.sleeper_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Sitter_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Eater_t>()
    {
        return this->save_state.eater_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Guard_t>() = delete;

    template <typename T>
    inline some<Settler_Attention_t> Settlers_t::Attention(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Attention_t>& attention = Attentions<T>()[valid_settler_id()];
        if (!attention) {
            attention = DEFAULT_ATTENTION;
            SKYLIB_ASSERT_SOME(attention);
        }

        return attention();
    }

    template <>
    inline some<Settler_Attention_t> Settlers_t::Attention<Sitter_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline some<Settler_Attention_t> Settlers_t::Attention<Guard_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Attention(some<Settler_ID_t> valid_settler_id,
                                      some<Settler_Attention_t> attention)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(attention);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Attentions<T>()[valid_settler_id()] = attention;
    }

    template <>
    inline void Settlers_t::Attention<Sitter_t>(some<Settler_ID_t> valid_settler_id,
                                                some<Settler_Attention_t> attention) = delete;

    template <>
    inline void Settlers_t::Attention<Guard_t>(some<Settler_ID_t> valid_settler_id,
                                               some<Settler_Attention_t> attention) = delete;

    template <typename T>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Sandboxer_t>()
    {
        return this->save_state.sandboxer_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Sleeper_t>()
    {
        return this->save_state.sleeper_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Sitter_t>()
    {
        return this->save_state.sitter_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Eater_t>()
    {
        return this->save_state.eater_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Guard_t>()
    {
        return this->save_state.guard_speeds;
    }

    template <typename T>
    inline some<Settler_Speed_e> Settlers_t::Speed(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Speed_e>& speed = Speeds<T>()[valid_settler_id()];
        if (!speed) {
            speed = DEFAULT_SPEED;
            SKYLIB_ASSERT_SOME(speed);
        }

        return speed();
    }

    template <typename T>
    inline void Settlers_t::Speed(some<Settler_ID_t> valid_settler_id, some<Settler_Speed_e> speed)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(speed);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Speeds<T>()[valid_settler_id()] = speed;
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Sandboxer_t>()
    {
        return this->save_state.sandboxer_wander_distances;
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Sleeper_t>()
    {
        return this->save_state.sleeper_wander_distances;
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Sitter_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Eater_t>()
    {
        return this->save_state.eater_wander_distances;
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Guard_t>() = delete;

    template <typename T>
    inline some<Settler_Wander_Distance_t> Settlers_t::Wander_Distance(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Wander_Distance_t>& wander_distance = Wander_Distances<T>()[valid_settler_id()];
        if (!wander_distance) {
            wander_distance = DEFAULT_WANDER_DISTANCE;
            SKYLIB_ASSERT_SOME(wander_distance);
        }

        return wander_distance();
    }

    template <>
    inline some<Settler_Wander_Distance_t> Settlers_t::Wander_Distance<Sitter_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline some<Settler_Wander_Distance_t> Settlers_t::Wander_Distance<Guard_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Wander_Distance(some<Settler_ID_t> valid_settler_id,
                                            some<Settler_Wander_Distance_t> wander_distance)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(wander_distance);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Wander_Distances<T>()[valid_settler_id()] = wander_distance;
    }

    template <>
    inline void Settlers_t::Wander_Distance<Sitter_t>(some<Settler_ID_t> valid_settler_id,
                                                      some<Settler_Wander_Distance_t> wander_distance) = delete;

    template <>
    inline void Settlers_t::Wander_Distance<Guard_t>(some<Settler_ID_t> valid_settler_id,
                                                     some<Settler_Wander_Distance_t> wander_distance) = delete;

    template <typename T>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds()
    {
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Sandboxer_t>() = delete;

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Sleeper_t>()
    {
        return this->save_state.sleeper_beds;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Sitter_t>() = delete;

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Eater_t>() = delete;

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Guard_t>() = delete;

    template <typename T>
    inline maybe<Reference_t*> Settlers_t::Bed(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Beds<T>()[valid_settler_id()];
    }

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Sitter_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Eater_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Guard_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Bed(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        if (bed) {
            maybe<Reference_t*> old_bed = Bed<T>(valid_settler_id);
            if (old_bed) {
                old_bed->Move_To_Orbit(Consts_t::NPCP::Reference::Storage_Marker(), 0.0f, 0.0f);
                old_bed->Mark_For_Delete(true);
            }
            bed->Move_To_Orbit(Marker<T>(valid_settler_id), 0.0f, 180.0f);
        }
        Beds<T>()[valid_settler_id()] = bed;
    }

    template <>
    inline void Settlers_t::Bed<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Sitter_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Eater_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Guard_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <typename T>
    inline void Settlers_t::Bed(some<Settler_ID_t> valid_settler_id, some<Furniture_t*> bed)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(bed);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Bed<T>(valid_settler_id, Reference_t::Create(bed, 1, Marker<T>(valid_settler_id), true, false, true));
    }

    template <>
    inline void Settlers_t::Bed<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Furniture_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Sitter_t>(some<Settler_ID_t> valid_settler_id, some<Furniture_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Eater_t>(some<Settler_ID_t> valid_settler_id, some<Furniture_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Guard_t>(some<Settler_ID_t> valid_settler_id, some<Furniture_t*> bed) = delete;

    template <typename T>
    inline void Settlers_t::Default(some<Settler_ID_t> valid_settler_id)
    {
    }

    template <>
    inline void Settlers_t::Default<Sandboxer_t>(some<Settler_ID_t> valid_settler_id)
    {
        using T = Sandboxer_t;
        using F = T::Flags_e;

        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Settler_Flags_e& flags = Flags<T>(valid_settler_id);
        flags.Is_Flagged(F::ALLOW_SWIMMING, true);
        flags.Is_Flagged(F::ALWAYS_SNEAK, false);
        flags.Is_Flagged(F::IGNORE_COMBAT, false);
        flags.Is_Flagged(F::KEEP_WEAPONS_DRAWN, false);
        flags.Is_Flagged(F::HIDE_WEAPONS, false);
        flags.Is_Flagged(F::SKIP_COMBAT_ALERT, false);

        flags.Is_Flagged(F::ALLOW_HELLOS_TO_PLAYER, true);
        flags.Is_Flagged(F::ALLOW_HELLOS_TO_NPCS, true);
        flags.Is_Flagged(F::ALLOW_IDLE_CHATTER, true);
        flags.Is_Flagged(F::ALLOW_AGGRO_RADIUS, true);
        flags.Is_Flagged(F::ALLOW_WORLD_INTERACTIONS, true);
        flags.Is_Flagged(F::COMMENT_ON_FRIENDLY_FIRE, true);
        flags.Is_Flagged(F::INSPECT_CORPSES, true);
        flags.Is_Flagged(F::OBSERVE_COMBAT, true);
        flags.Is_Flagged(F::REACT_TO_PLAYER_ACTIONS, true);

        flags.Is_Flagged(F::ALLOW_CONVERSATION, true);
        flags.Is_Flagged(F::ALLOW_EATING, true);
        flags.Is_Flagged(F::ALLOW_HORSE_RIDING, false);
        flags.Is_Flagged(F::ALLOW_IDLE_MARKERS, true);
        flags.Is_Flagged(F::ALLOW_SITTING, true);
        flags.Is_Flagged(F::ALLOW_SLEEPING, true);
        flags.Is_Flagged(F::ALLOW_SPECIAL_FURNITURE, true);
        flags.Is_Flagged(F::ALLOW_WANDERING, true);
        flags.Is_Flagged(F::ONLY_PREFERRED_PATH, false);
        flags.Is_Flagged(F::UNLOCK_ON_ARRIVAL, true);

        Attention<T>(valid_settler_id, 40);
        Radius<T>(valid_settler_id, DEFAULT_RADIUS);
        Speed<T>(valid_settler_id, Settler_Speed_e::WALK);
        Wander_Distance<T>(valid_settler_id, DEFAULT_WANDER_DISTANCE);
    }

    template <>
    inline void Settlers_t::Default<Sleeper_t>(some<Settler_ID_t> valid_settler_id)
    {
        using T = Sleeper_t;
        using F = T::Flags_e;

        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Settler_Flags_e& flags = Flags<T>(valid_settler_id);
        flags.Is_Flagged(F::ALLOW_SWIMMING, true);
        flags.Is_Flagged(F::ALWAYS_SNEAK, false);
        flags.Is_Flagged(F::IGNORE_COMBAT, false);
        flags.Is_Flagged(F::KEEP_WEAPONS_DRAWN, false);
        flags.Is_Flagged(F::HIDE_WEAPONS, true);
        flags.Is_Flagged(F::SKIP_COMBAT_ALERT, false);

        flags.Is_Flagged(F::ALLOW_HELLOS_TO_PLAYER, false);
        flags.Is_Flagged(F::ALLOW_HELLOS_TO_NPCS, false);
        flags.Is_Flagged(F::ALLOW_IDLE_CHATTER, false);
        flags.Is_Flagged(F::ALLOW_AGGRO_RADIUS, true);
        flags.Is_Flagged(F::ALLOW_WORLD_INTERACTIONS, false);
        flags.Is_Flagged(F::COMMENT_ON_FRIENDLY_FIRE, true);
        flags.Is_Flagged(F::INSPECT_CORPSES, true);
        flags.Is_Flagged(F::OBSERVE_COMBAT, true);
        flags.Is_Flagged(F::REACT_TO_PLAYER_ACTIONS, true);

        flags.Is_Flagged(F::ALLOW_CONVERSATION, false);
        flags.Is_Flagged(F::ALLOW_EATING, false);
        flags.Is_Flagged(F::ALLOW_HORSE_RIDING, false);
        flags.Is_Flagged(F::ALLOW_IDLE_MARKERS, true);
        flags.Is_Flagged(F::ALLOW_SITTING, true);
        flags.Is_Flagged(F::ALLOW_SLEEPING, true);
        flags.Is_Flagged(F::ALLOW_SPECIAL_FURNITURE, false);
        flags.Is_Flagged(F::ALLOW_WANDERING, false);
        flags.Is_Flagged(F::LOCK_DOORS, false);
        flags.Is_Flagged(F::ONLY_PREFERRED_PATH, false);
        flags.Is_Flagged(F::WARN_BEFORE_LOCKING, true);

        Attention<T>(valid_settler_id, 100);
        Bed<T>(valid_settler_id, none<Reference_t*>());
        Duration_Hours<T>(valid_settler_id, 8);
        Duration_Minutes<T>(valid_settler_id, 0);
        Radius<T>(valid_settler_id, DEFAULT_RADIUS);
        Speed<T>(valid_settler_id, Settler_Speed_e::JOG);
        Time_AM_PM<T>(valid_settler_id, Settler_Time_AM_PM_e::PM);
        Time_Hour<T>(valid_settler_id, 10);
        Time_Minute<T>(valid_settler_id, 30);
        Wander_Distance<T>(valid_settler_id, DEFAULT_WANDER_DISTANCE);
    }

    template <>
    inline void Settlers_t::Default<Sitter_t>(some<Settler_ID_t> valid_settler_id)
    {
        using T = Sitter_t;
        using F = T::Flags_e;

        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Settler_Flags_e& flags = Flags<T>(valid_settler_id);
        flags.Is_Flagged(F::ALLOW_SWIMMING, true);
        flags.Is_Flagged(F::ALWAYS_SNEAK, false);
        flags.Is_Flagged(F::IGNORE_COMBAT, false);
        flags.Is_Flagged(F::KEEP_WEAPONS_DRAWN, false);
        flags.Is_Flagged(F::HIDE_WEAPONS, false);
        flags.Is_Flagged(F::SKIP_COMBAT_ALERT, false);

        flags.Is_Flagged(F::ALLOW_HELLOS_TO_PLAYER, true);
        flags.Is_Flagged(F::ALLOW_HELLOS_TO_NPCS, true);
        flags.Is_Flagged(F::ALLOW_IDLE_CHATTER, true);
        flags.Is_Flagged(F::ALLOW_AGGRO_RADIUS, true);
        flags.Is_Flagged(F::ALLOW_WORLD_INTERACTIONS, true);
        flags.Is_Flagged(F::COMMENT_ON_FRIENDLY_FIRE, true);
        flags.Is_Flagged(F::INSPECT_CORPSES, true);
        flags.Is_Flagged(F::OBSERVE_COMBAT, true);
        flags.Is_Flagged(F::REACT_TO_PLAYER_ACTIONS, true);

        flags.Is_Flagged(F::ONLY_PREFERRED_PATH, false);
        flags.Is_Flagged(F::STOP_MOVEMENT, false);

        Duration_Hours<T>(valid_settler_id, 0);
        Duration_Minutes<T>(valid_settler_id, 30);
        Radius<T>(valid_settler_id, DEFAULT_RADIUS);
        Speed<T>(valid_settler_id, Settler_Speed_e::WALK);
        Time_AM_PM<T>(valid_settler_id, Settler_Time_AM_PM_e::AM);
        Time_Hour<T>(valid_settler_id, 8);
        Time_Minute<T>(valid_settler_id, 0);
    }

    template <>
    inline void Settlers_t::Default<Eater_t>(some<Settler_ID_t> valid_settler_id)
    {
        using T = Eater_t;
        using F = T::Flags_e;

        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Settler_Flags_e& flags = Flags<T>(valid_settler_id);
        flags.Is_Flagged(F::ALLOW_SWIMMING, true);
        flags.Is_Flagged(F::ALWAYS_SNEAK, false);
        flags.Is_Flagged(F::IGNORE_COMBAT, false);
        flags.Is_Flagged(F::KEEP_WEAPONS_DRAWN, false);
        flags.Is_Flagged(F::HIDE_WEAPONS, false);
        flags.Is_Flagged(F::SKIP_COMBAT_ALERT, false);

        flags.Is_Flagged(F::ALLOW_HELLOS_TO_PLAYER, false);
        flags.Is_Flagged(F::ALLOW_HELLOS_TO_NPCS, false);
        flags.Is_Flagged(F::ALLOW_IDLE_CHATTER, false);
        flags.Is_Flagged(F::ALLOW_AGGRO_RADIUS, true);
        flags.Is_Flagged(F::ALLOW_WORLD_INTERACTIONS, false);
        flags.Is_Flagged(F::COMMENT_ON_FRIENDLY_FIRE, true);
        flags.Is_Flagged(F::INSPECT_CORPSES, true);
        flags.Is_Flagged(F::OBSERVE_COMBAT, true);
        flags.Is_Flagged(F::REACT_TO_PLAYER_ACTIONS, true);

        flags.Is_Flagged(F::ALLOW_ALREADY_HELD_FOOD, true);
        flags.Is_Flagged(F::ALLOW_CONVERSATION, false);
        flags.Is_Flagged(F::ALLOW_EATING, true);
        flags.Is_Flagged(F::ALLOW_FAKE_FOOD, true);
        flags.Is_Flagged(F::ALLOW_HORSE_RIDING, false);
        flags.Is_Flagged(F::ALLOW_IDLE_MARKERS, false);
        flags.Is_Flagged(F::ALLOW_SITTING, false);
        flags.Is_Flagged(F::ALLOW_SLEEPING, false);
        flags.Is_Flagged(F::ALLOW_SPECIAL_FURNITURE, false);
        flags.Is_Flagged(F::ALLOW_WANDERING, false);
        flags.Is_Flagged(F::ONLY_PREFERRED_PATH, false);
        flags.Is_Flagged(F::UNLOCK_ON_ARRIVAL, true);

        Attention<T>(valid_settler_id, 0);
        Duration_Hours<T>(valid_settler_id, 2);
        Duration_Minutes<T>(valid_settler_id, 0);
        Radius<T>(valid_settler_id, DEFAULT_RADIUS);
        Speed<T>(valid_settler_id, Settler_Speed_e::FAST_WALK);
        Time_AM_PM<T>(valid_settler_id, Settler_Time_AM_PM_e::PM);
        Time_Hour<T>(valid_settler_id, 12);
        Time_Minute<T>(valid_settler_id, 0);
        Wander_Distance<T>(valid_settler_id, DEFAULT_WANDER_DISTANCE);
    }

    template <>
    inline void Settlers_t::Default<Guard_t>(some<Settler_ID_t> valid_settler_id)
    {
        using T = Guard_t;
        using F = T::Flags_e;

        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Settler_Flags_e& flags = Flags<T>(valid_settler_id);
        flags.Is_Flagged(F::ALLOW_SWIMMING, false);
        flags.Is_Flagged(F::ALWAYS_SNEAK, false);
        flags.Is_Flagged(F::IGNORE_COMBAT, false);
        flags.Is_Flagged(F::KEEP_WEAPONS_DRAWN, true);
        flags.Is_Flagged(F::HIDE_WEAPONS, false);
        flags.Is_Flagged(F::SKIP_COMBAT_ALERT, true);

        flags.Is_Flagged(F::ALLOW_HELLOS_TO_PLAYER, false);
        flags.Is_Flagged(F::ALLOW_HELLOS_TO_NPCS, false);
        flags.Is_Flagged(F::ALLOW_IDLE_CHATTER, false);
        flags.Is_Flagged(F::ALLOW_AGGRO_RADIUS, true);
        flags.Is_Flagged(F::ALLOW_WORLD_INTERACTIONS, false);
        flags.Is_Flagged(F::COMMENT_ON_FRIENDLY_FIRE, true);
        flags.Is_Flagged(F::INSPECT_CORPSES, true);
        flags.Is_Flagged(F::OBSERVE_COMBAT, true);
        flags.Is_Flagged(F::REACT_TO_PLAYER_ACTIONS, false);

        Duration_Hours<T>(valid_settler_id, 5);
        Duration_Minutes<T>(valid_settler_id, 45);
        Radius<T>(valid_settler_id, 0);
        Speed<T>(valid_settler_id, Settler_Speed_e::RUN);
        Time_AM_PM<T>(valid_settler_id, Settler_Time_AM_PM_e::PM);
        Time_Hour<T>(valid_settler_id, 2);
        Time_Minute<T>(valid_settler_id, 0);
    }

    template <typename T>
    inline some<Settler_ID_t> Settlers_t::Add(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));

        some<Settler_ID_t> settler_id = valid_member_id;
        if (!Is_Enabled<T>(settler_id)) {
            Is_Enabled<T>(settler_id, true);
            Marker<T>(settler_id)->Move_To_Orbit(Member_t(settler_id).Actor(), 0.0f, 180.0f);
            Default<T>(settler_id);
            Main().Update_AI(settler_id, Member_Update_AI_e::EVALUATE_PACKAGE);
            return settler_id;
        }
        return settler_id;
    }

    template <typename T>
    inline Bool_t Settlers_t::Remove(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        if (Is_Enabled<T>(settler_id)) {
            // incomplete
            return true;
        } else {
            return false;
        }
    }

    template <typename F>
    inline void Settlers_t::Enforce_Package_General_Flags(some<Package_t*> package,
                                                          Settler_Flags_e flags,
                                                          Bool_t& do_reset_ai)
    {
        using G = Package_Flags_e;

        SKYLIB_ASSERT(package);

        General_Flag(package, G::ALLOW_SWIMMING, flags.Is_Flagged(F::ALLOW_SWIMMING), do_reset_ai);
        General_Flag(package, G::ALWAYS_SNEAK, flags.Is_Flagged(F::ALWAYS_SNEAK), do_reset_ai);
        General_Flag(package, G::IGNORE_COMBAT, flags.Is_Flagged(F::IGNORE_COMBAT), do_reset_ai);
        General_Flag(package, G::KEEP_WEAPONS_DRAWN, flags.Is_Flagged(F::KEEP_WEAPONS_DRAWN), do_reset_ai);
        General_Flag(package, G::HIDE_WEAPONS, flags.Is_Flagged(F::HIDE_WEAPONS), do_reset_ai);
        General_Flag(package, G::SKIP_COMBAT_ALERT, flags.Is_Flagged(F::SKIP_COMBAT_ALERT), do_reset_ai);
    }

    template <typename F>
    inline void Settlers_t::Enforce_Package_Interrupt_Flags(some<Package_t*> package,
                                                            Settler_Flags_e flags,
                                                            Bool_t& do_reset_ai)
    {
        using I = Package_Interrupt_Flags_e;

        SKYLIB_ASSERT(package);

        Interrupt_Flag(package, I::ALLOW_HELLOS_TO_PLAYER, flags.Is_Flagged(F::ALLOW_HELLOS_TO_PLAYER), do_reset_ai);
        Interrupt_Flag(package, I::ALLOW_HELLOS_TO_NPCS, flags.Is_Flagged(F::ALLOW_HELLOS_TO_NPCS), do_reset_ai);
        Interrupt_Flag(package, I::ALLOW_IDLE_CHATTER, flags.Is_Flagged(F::ALLOW_IDLE_CHATTER), do_reset_ai);
        Interrupt_Flag(package, I::ALLOW_AGGRO_RADIUS, flags.Is_Flagged(F::ALLOW_AGGRO_RADIUS), do_reset_ai);
        Interrupt_Flag(package, I::ALLOW_WORLD_INTERACTIONS, flags.Is_Flagged(F::ALLOW_WORLD_INTERACTIONS), do_reset_ai);
        Interrupt_Flag(package, I::COMMENT_ON_FRIENDLY_FIRE, flags.Is_Flagged(F::COMMENT_ON_FRIENDLY_FIRE), do_reset_ai);
        Interrupt_Flag(package, I::INSPECT_CORPSES, flags.Is_Flagged(F::INSPECT_CORPSES), do_reset_ai);
        Interrupt_Flag(package, I::OBSERVE_COMBAT, flags.Is_Flagged(F::OBSERVE_COMBAT), do_reset_ai);
        Interrupt_Flag(package, I::REACT_TO_PLAYER_ACTIONS, flags.Is_Flagged(F::REACT_TO_PLAYER_ACTIONS), do_reset_ai);
    }

    template <typename T>
    inline void Settlers_t::Enforce_Package(some<Settler_ID_t> valid_settler_id,
                                            Bool_t& do_reset_ai)
    {
    }

    template <>
    inline void Settlers_t::Enforce_Package<Sandboxer_t>(some<Settler_ID_t> id,
                                                         Bool_t& do_reset_ai)
    {
        using T = Sandboxer_t;
        using F = T::Flags_e;
        using V = T::Value_e;

        some<Package_t*> package = Package<T>(id);
        Settler_Flags_e flags = Flags<T>(id);

        Enforce_Package_General_Flags<F>(package, flags, do_reset_ai);
        Enforce_Package_Interrupt_Flags<F>(package, flags, do_reset_ai);

        Bool(package, V::ALLOW_CONVERSATION, flags.Is_Flagged(F::ALLOW_CONVERSATION), do_reset_ai);
        Bool(package, V::ALLOW_EATING, flags.Is_Flagged(F::ALLOW_EATING), do_reset_ai);
        Bool(package, V::ALLOW_HORSE_RIDING, flags.Is_Flagged(F::ALLOW_HORSE_RIDING), do_reset_ai);
        Bool(package, V::ALLOW_IDLE_MARKERS, flags.Is_Flagged(F::ALLOW_IDLE_MARKERS), do_reset_ai);
        Bool(package, V::ALLOW_SITTING, flags.Is_Flagged(F::ALLOW_SITTING), do_reset_ai);
        Bool(package, V::ALLOW_SLEEPING, flags.Is_Flagged(F::ALLOW_SLEEPING), do_reset_ai);
        Bool(package, V::ALLOW_SPECIAL_FURNITURE, flags.Is_Flagged(F::ALLOW_SPECIAL_FURNITURE), do_reset_ai);
        Bool(package, V::ALLOW_WANDERING, flags.Is_Flagged(F::ALLOW_WANDERING), do_reset_ai);
        Bool(package, V::ONLY_PREFERRED_PATH, flags.Is_Flagged(F::ONLY_PREFERRED_PATH), do_reset_ai);
        Bool(package, V::UNLOCK_ON_ARRIVAL, flags.Is_Flagged(F::UNLOCK_ON_ARRIVAL), do_reset_ai);

        Float(package, V::ATTENTION, Attention<T>(id)(), do_reset_ai);
        Float(package, V::WANDER_DISTANCE, Wander_Distance<T>(id)(), do_reset_ai);

        Location(package, V::LOCATION, Marker<T>(id), Radius<T>(id), do_reset_ai);

        Schedule(package, none<Settler_Time_t>(), none<Settler_Duration_t>(), do_reset_ai);

        Speed(package, Speed<T>(id), do_reset_ai);
    }

    template <>
    inline void Settlers_t::Enforce_Package<Sleeper_t>(some<Settler_ID_t> id,
                                                       Bool_t& do_reset_ai)
    {
        using T = Sleeper_t;
        using F = T::Flags_e;
        using V = T::Value_e;

        some<Package_t*> package = Package<T>(id);
        Settler_Flags_e flags = Flags<T>(id);

        Enforce_Package_General_Flags<F>(package, flags, do_reset_ai);
        Enforce_Package_Interrupt_Flags<F>(package, flags, do_reset_ai);

        Bool(package, V::ALLOW_CONVERSATION, flags.Is_Flagged(F::ALLOW_CONVERSATION), do_reset_ai);
        Bool(package, V::ALLOW_EATING, flags.Is_Flagged(F::ALLOW_EATING), do_reset_ai);
        Bool(package, V::ALLOW_HORSE_RIDING, flags.Is_Flagged(F::ALLOW_HORSE_RIDING), do_reset_ai);
        Bool(package, V::ALLOW_IDLE_MARKERS, flags.Is_Flagged(F::ALLOW_IDLE_MARKERS), do_reset_ai);
        Bool(package, V::ALLOW_SITTING, flags.Is_Flagged(F::ALLOW_SITTING), do_reset_ai);
        Bool(package, V::ALLOW_SLEEPING, flags.Is_Flagged(F::ALLOW_SLEEPING), do_reset_ai);
        Bool(package, V::ALLOW_SPECIAL_FURNITURE, flags.Is_Flagged(F::ALLOW_SPECIAL_FURNITURE), do_reset_ai);
        Bool(package, V::ALLOW_WANDERING, flags.Is_Flagged(F::ALLOW_WANDERING), do_reset_ai);
        Bool(package, V::LOCK_DOORS, flags.Is_Flagged(F::LOCK_DOORS), do_reset_ai);
        Bool(package, V::ONLY_PREFERRED_PATH, flags.Is_Flagged(F::ONLY_PREFERRED_PATH), do_reset_ai);
        Bool(package, V::WARN_BEFORE_LOCKING, flags.Is_Flagged(F::WARN_BEFORE_LOCKING), do_reset_ai);

        Float(package, V::ATTENTION, Attention<T>(id)(), do_reset_ai);
        Float(package, V::WANDER_DISTANCE, Wander_Distance<T>(id)(), do_reset_ai);

        Location(package, V::LOCATION, Marker<T>(id), Radius<T>(id), do_reset_ai);

        Schedule(package, Time<T>(id), Duration<T>(id), do_reset_ai);

        Speed(package, Speed<T>(id), do_reset_ai);
    }

    template <>
    inline void Settlers_t::Enforce_Package<Sitter_t>(some<Settler_ID_t> id,
                                                      Bool_t& do_reset_ai)
    {
        using T = Sitter_t;
        using F = T::Flags_e;
        using V = T::Value_e;

        some<Package_t*> package = Package<T>(id);
        Settler_Flags_e flags = Flags<T>(id);

        Enforce_Package_General_Flags<F>(package, flags, do_reset_ai);
        Enforce_Package_Interrupt_Flags<F>(package, flags, do_reset_ai);

        Bool(package, V::ONLY_PREFERRED_PATH, flags.Is_Flagged(F::ONLY_PREFERRED_PATH), do_reset_ai);
        Bool(package, V::STOP_MOVEMENT, flags.Is_Flagged(F::STOP_MOVEMENT), do_reset_ai);

        Location(package, V::LOCATION, Marker<T>(id), Radius<T>(id), do_reset_ai);

        Schedule(package, Time<T>(id), Duration<T>(id), do_reset_ai);

        Speed(package, Speed<T>(id), do_reset_ai);
    }

    template <>
    inline void Settlers_t::Enforce_Package<Eater_t>(some<Settler_ID_t> id,
                                                     Bool_t& do_reset_ai)
    {
        using T = Eater_t;
        using F = T::Flags_e;
        using V = T::Value_e;

        some<Package_t*> package = Package<T>(id);
        Settler_Flags_e flags = Flags<T>(id);

        Enforce_Package_General_Flags<F>(package, flags, do_reset_ai);
        Enforce_Package_Interrupt_Flags<F>(package, flags, do_reset_ai);

        Bool(package, V::ALLOW_ALREADY_HELD_FOOD, flags.Is_Flagged(F::ALLOW_ALREADY_HELD_FOOD), do_reset_ai);
        Bool(package, V::ALLOW_CONVERSATION, flags.Is_Flagged(F::ALLOW_CONVERSATION), do_reset_ai);
        Bool(package, V::ALLOW_EATING, flags.Is_Flagged(F::ALLOW_EATING), do_reset_ai);
        Bool(package, V::ALLOW_FAKE_FOOD, flags.Is_Flagged(F::ALLOW_FAKE_FOOD), do_reset_ai);
        Bool(package, V::ALLOW_HORSE_RIDING, flags.Is_Flagged(F::ALLOW_HORSE_RIDING), do_reset_ai);
        Bool(package, V::ALLOW_IDLE_MARKERS, flags.Is_Flagged(F::ALLOW_IDLE_MARKERS), do_reset_ai);
        Bool(package, V::ALLOW_SITTING, flags.Is_Flagged(F::ALLOW_SITTING), do_reset_ai);
        Bool(package, V::ALLOW_SLEEPING, flags.Is_Flagged(F::ALLOW_SLEEPING), do_reset_ai);
        Bool(package, V::ALLOW_SPECIAL_FURNITURE, flags.Is_Flagged(F::ALLOW_SPECIAL_FURNITURE), do_reset_ai);
        Bool(package, V::ALLOW_WANDERING, flags.Is_Flagged(F::ALLOW_WANDERING), do_reset_ai);
        Bool(package, V::ONLY_PREFERRED_PATH, flags.Is_Flagged(F::ONLY_PREFERRED_PATH), do_reset_ai);
        Bool(package, V::UNLOCK_ON_ARRIVAL, flags.Is_Flagged(F::UNLOCK_ON_ARRIVAL), do_reset_ai);

        Float(package, V::ATTENTION, Attention<T>(id)(), do_reset_ai);
        Float(package, V::WANDER_DISTANCE, Wander_Distance<T>(id)(), do_reset_ai);

        Location(package, V::LOCATION, Marker<T>(id), Radius<T>(id), do_reset_ai);

        Schedule(package, Time<T>(id), Duration<T>(id), do_reset_ai);

        Speed(package, Speed<T>(id), do_reset_ai);
    }

    template <>
    inline void Settlers_t::Enforce_Package<Guard_t>(some<Settler_ID_t> id,
                                                     Bool_t& do_reset_ai)
    {
        using T = Guard_t;
        using F = T::Flags_e;
        using V = T::Value_e;

        some<Package_t*> package = Package<T>(id);
        Settler_Flags_e flags = Flags<T>(id);
        some<Reference_t*> marker = Marker<T>(id);

        Enforce_Package_General_Flags<F>(package, flags, do_reset_ai);
        Enforce_Package_Interrupt_Flags<F>(package, flags, do_reset_ai);

        Location(package, V::WAIT_LOCATION, marker, 0, do_reset_ai);
        Location(package, V::RESTRICTED_LOCATION, marker, Radius<T>(id), do_reset_ai);

        Schedule(package, Time<T>(id), Duration<T>(id), do_reset_ai);

        Speed(package, Speed<T>(id), do_reset_ai);
    }

}}
