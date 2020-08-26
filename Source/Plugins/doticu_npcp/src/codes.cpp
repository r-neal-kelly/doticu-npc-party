/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "utils.h"

namespace doticu_npcp { namespace CODES {



}}

namespace doticu_npcp { namespace CODES { namespace Exports {

    Int_t SUCCESS(Selfless_t*)                      { return CODES::SUCCESS; }
    Int_t FAILURE(Selfless_t*)                      { return CODES::FAILURE; }
    Int_t IS(Selfless_t*)                           { return CODES::IS; }
    Int_t ISNT(Selfless_t*)                         { return CODES::ISNT; }
    Int_t HAS(Selfless_t*)                          { return CODES::HAS; }
    Int_t HASNT(Selfless_t*)                        { return CODES::HASNT; }
    Int_t ALIVE(Selfless_t*)                        { return CODES::ALIVE; }
    Int_t DEAD(Selfless_t*)                         { return CODES::DEAD; }

    Int_t ACTOR(Selfless_t*)                        { return CODES::ACTOR; }
    Int_t CHILD(Selfless_t*)                        { return CODES::CHILD; }
    Int_t CLONE(Selfless_t*)                        { return CODES::CLONE; }
    Int_t DISPLAY(Selfless_t*)                      { return CODES::DISPLAY; }
    Int_t FOLLOWER(Selfless_t*)                     { return CODES::FOLLOWER; }
    Int_t FOLLOWERS(Selfless_t*)                    { return CODES::FOLLOWERS; }
    Int_t INTERIOR(Selfless_t*)                     { return CODES::INTERIOR; }
    Int_t MANNEQUIN(Selfless_t*)                    { return CODES::MANNEQUIN; }
    Int_t MARKER(Selfless_t*)                       { return CODES::MARKER; }
    Int_t MEMBER(Selfless_t*)                       { return CODES::MEMBER; }
    Int_t MEMBERS(Selfless_t*)                      { return CODES::MEMBERS; }
    Int_t VAMPIRE(Selfless_t*)                      { return CODES::VAMPIRE; }

    Int_t ACTION_WEAPON_SWING(Selfless_t*)          { return CODES::ACTION::WEAPON_SWING; }
    Int_t ACTION_SPELL_CAST(Selfless_t*)            { return CODES::ACTION::SPELL_CAST; }
    Int_t ACTION_SPELL_FIRE(Selfless_t*)            { return CODES::ACTION::SPELL_FIRE; }
    Int_t ACTION_VOICE_CAST(Selfless_t*)            { return CODES::ACTION::VOICE_CAST; }
    Int_t ACTION_VOICE_FIRE(Selfless_t*)            { return CODES::ACTION::VOICE_FIRE; }
    Int_t ACTION_BOW_DRAW(Selfless_t*)              { return CODES::ACTION::BOW_DRAW; }
    Int_t ACTION_BOW_RELEASE(Selfless_t*)           { return CODES::ACTION::BOW_RELEASE; }
    Int_t ACTION_DRAW_BEGIN(Selfless_t*)            { return CODES::ACTION::DRAW_BEGIN; }
    Int_t ACTION_DRAW_END(Selfless_t*)              { return CODES::ACTION::DRAW_END; }
    Int_t ACTION_SHEATHE_BEGIN(Selfless_t*)         { return CODES::ACTION::SHEATHE_BEGIN; }
    Int_t ACTION_SHEATHE_END(Selfless_t*)           { return CODES::ACTION::SHEATHE_END; }

    Int_t COMBAT_NO(Selfless_t*)                    { return CODES::COMBAT::NO; }
    Int_t COMBAT_YES(Selfless_t*)                   { return CODES::COMBAT::YES; }
    Int_t COMBAT_SEARCHING(Selfless_t*)             { return CODES::COMBAT::SEARCHING; }

    Int_t CRITICAL_NONE(Selfless_t*)                { return CODES::CRITICAL::NONE; }
    Int_t CRITICAL_GOO_BEGIN(Selfless_t*)           { return CODES::CRITICAL::GOO_BEGIN; }
    Int_t CRITICAL_GOO_END(Selfless_t*)             { return CODES::CRITICAL::GOO_END; }
    Int_t CRITICAL_DISINTEGRATE_BEGIN(Selfless_t*)  { return CODES::CRITICAL::DISINTEGRATE_BEGIN; }
    Int_t CRITICAL_DISINTEGRATE_END(Selfless_t*)    { return CODES::CRITICAL::DISINTEGRATE_END; }

    Int_t MOTION_DYNAMIC(Selfless_t*)               { return CODES::MOTION::DYNAMIC; }
    Int_t MOTION_SPHERE_INERTIA(Selfless_t*)        { return CODES::MOTION::SPHERE_INERTIA; }
    Int_t MOTION_BOX_INERTIA(Selfless_t*)           { return CODES::MOTION::BOX_INERTIA; }
    Int_t MOTION_KEY_FRAMED(Selfless_t*)            { return CODES::MOTION::KEY_FRAMED; }
    Int_t MOTION_FIXED(Selfless_t*)                 { return CODES::MOTION::FIXED; }
    Int_t MOTION_THIN_BOX_INERTIA(Selfless_t*)      { return CODES::MOTION::THIN_BOX_INERTIA; }
    Int_t MOTION_CHARACTER(Selfless_t*)             { return CODES::MOTION::CHARACTER; }

    Int_t OUTFIT_BASE(Selfless_t*)                  { return CODES::OUTFIT::BASE; }
    Int_t OUTFIT_REFERENCE(Selfless_t*)             { return CODES::OUTFIT::REFERENCE; }

    Int_t OUTFIT2_CURRENT(Selfless_t*)              { return CODES::OUTFIT2::CURRENT; }
    Int_t OUTFIT2_MEMBER(Selfless_t*)               { return CODES::OUTFIT2::MEMBER; }
    Int_t OUTFIT2_SETTLER(Selfless_t*)              { return CODES::OUTFIT2::SETTLER; }
    Int_t OUTFIT2_THRALL(Selfless_t*)               { return CODES::OUTFIT2::THRALL; }
    Int_t OUTFIT2_FOLLOWER(Selfless_t*)             { return CODES::OUTFIT2::FOLLOWER; }
    Int_t OUTFIT2_IMMOBILE(Selfless_t*)             { return CODES::OUTFIT2::IMMOBILE; }
    Int_t OUTFIT2_VANILLA(Selfless_t*)              { return CODES::OUTFIT2::VANILLA; }
    Int_t OUTFIT2_DEFAULT(Selfless_t*)              { return CODES::OUTFIT2::DEFAULT; }

    Int_t SEX_MALE(Selfless_t*)                     { return CODES::SEX::MALE; }
    Int_t SEX_FEMALE(Selfless_t*)                   { return CODES::SEX::FEMALE; }
    Int_t SEX_NONE(Selfless_t*)                     { return CODES::SEX::NONE; }

    Int_t STYLE_DEFAULT(Selfless_t*)                { return CODES::STYLE::DEFAULT; }
    Int_t STYLE_WARRIOR(Selfless_t*)                { return CODES::STYLE::WARRIOR; }
    Int_t STYLE_MAGE(Selfless_t*)                   { return CODES::STYLE::MAGE; }
    Int_t STYLE_ARCHER(Selfless_t*)                 { return CODES::STYLE::ARCHER; }
    Int_t STYLE_COWARD(Selfless_t*)                 { return CODES::STYLE::COWARD; }

    Int_t VIEW_MEMBERS(Selfless_t*)                 { return CODES::VIEW::MEMBERS; }
    Int_t VIEW_FOLLOWERS(Selfless_t*)               { return CODES::VIEW::FOLLOWERS; }
    Int_t VIEW_MEMBERS_MEMBER(Selfless_t*)          { return CODES::VIEW::MEMBERS_MEMBER; }
    Int_t VIEW_FOLLOWERS_MEMBER(Selfless_t*)        { return CODES::VIEW::FOLLOWERS_MEMBER; }
    Int_t VIEW_FILTER(Selfless_t*)                  { return CODES::VIEW::FILTER; }
    Int_t VIEW_FILTER_MEMBERS(Selfless_t*)          { return CODES::VIEW::FILTER_MEMBERS; }
    Int_t VIEW_FILTER_MEMBERS_MEMBER(Selfless_t*)   { return CODES::VIEW::FILTER_MEMBERS_MEMBER; }
    Int_t VIEW_MANNEQUINS(Selfless_t*)              { return CODES::VIEW::MANNEQUINS; }
    Int_t VIEW_MANNEQUINS_CELL(Selfless_t*)         { return CODES::VIEW::MANNEQUINS_CELL; }
    Int_t VIEW_MANNEQUINS_MEMBER(Selfless_t*)       { return CODES::VIEW::MANNEQUINS_MEMBER; }

    Int_t VITALITY_MORTAL(Selfless_t*)              { return CODES::VITALITY::MORTAL; }
    Int_t VITALITY_PROTECTED(Selfless_t*)           { return CODES::VITALITY::PROTECTED; }
    Int_t VITALITY_ESSENTIAL(Selfless_t*)           { return CODES::VITALITY::ESSENTIAL; }
    Int_t VITALITY_INVULNERABLE(Selfless_t*)        { return CODES::VITALITY::INVULNERABLE; }

    bool Register(Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_codes", Selfless_t,           \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("SUCCESS", 0, Int_t, SUCCESS);
        ADD_GLOBAL("FAILURE", 0, Int_t, FAILURE);
        ADD_GLOBAL("IS", 0, Int_t, IS);
        ADD_GLOBAL("ISNT", 0, Int_t, ISNT);
        ADD_GLOBAL("HAS", 0, Int_t, HAS);
        ADD_GLOBAL("HASNT", 0, Int_t, HASNT);
        ADD_GLOBAL("ALIVE", 0, Int_t, ALIVE);
        ADD_GLOBAL("DEAD", 0, Int_t, DEAD);

        ADD_GLOBAL("ACTOR", 0, Int_t, ACTOR);
        ADD_GLOBAL("CHILD", 0, Int_t, CHILD);
        ADD_GLOBAL("CLONE", 0, Int_t, CLONE);
        ADD_GLOBAL("DISPLAY", 0, Int_t, DISPLAY);
        ADD_GLOBAL("FOLLOWER", 0, Int_t, FOLLOWER);
        ADD_GLOBAL("FOLLOWERS", 0, Int_t, FOLLOWERS);
        ADD_GLOBAL("INTERIOR", 0, Int_t, INTERIOR);
        ADD_GLOBAL("MANNEQUIN", 0, Int_t, MANNEQUIN);
        ADD_GLOBAL("MARKER", 0, Int_t, MARKER);
        ADD_GLOBAL("MEMBER", 0, Int_t, MEMBER);
        ADD_GLOBAL("MEMBERS", 0, Int_t, MEMBERS);
        ADD_GLOBAL("VAMPIRE", 0, Int_t, VAMPIRE);

        ADD_GLOBAL("ACTION_WEAPON_SWING", 0, Int_t, ACTION_WEAPON_SWING);
        ADD_GLOBAL("ACTION_SPELL_CAST", 0, Int_t, ACTION_SPELL_CAST);
        ADD_GLOBAL("ACTION_SPELL_FIRE", 0, Int_t, ACTION_SPELL_FIRE);
        ADD_GLOBAL("ACTION_VOICE_CAST", 0, Int_t, ACTION_VOICE_CAST);
        ADD_GLOBAL("ACTION_VOICE_FIRE", 0, Int_t, ACTION_VOICE_FIRE);
        ADD_GLOBAL("ACTION_BOW_DRAW", 0, Int_t, ACTION_BOW_DRAW);
        ADD_GLOBAL("ACTION_BOW_RELEASE", 0, Int_t, ACTION_BOW_RELEASE);
        ADD_GLOBAL("ACTION_DRAW_BEGIN", 0, Int_t, ACTION_DRAW_BEGIN);
        ADD_GLOBAL("ACTION_DRAW_END", 0, Int_t, ACTION_DRAW_END);
        ADD_GLOBAL("ACTION_SHEATHE_BEGIN", 0, Int_t, ACTION_SHEATHE_BEGIN);
        ADD_GLOBAL("ACTION_SHEATHE_END", 0, Int_t, ACTION_SHEATHE_END);

        ADD_GLOBAL("COMBAT_NO", 0, Int_t, COMBAT_NO);
        ADD_GLOBAL("COMBAT_YES", 0, Int_t, COMBAT_YES);
        ADD_GLOBAL("COMBAT_SEARCHING", 0, Int_t, COMBAT_SEARCHING);

        ADD_GLOBAL("CRITICAL_NONE", 0, Int_t, CRITICAL_NONE);
        ADD_GLOBAL("CRITICAL_GOO_BEGIN", 0, Int_t, CRITICAL_GOO_BEGIN);
        ADD_GLOBAL("CRITICAL_GOO_END", 0, Int_t, CRITICAL_GOO_END);
        ADD_GLOBAL("CRITICAL_DISINTEGRATE_BEGIN", 0, Int_t, CRITICAL_DISINTEGRATE_BEGIN);
        ADD_GLOBAL("CRITICAL_DISINTEGRATE_END", 0, Int_t, CRITICAL_DISINTEGRATE_END);

        ADD_GLOBAL("MOTION_DYNAMIC", 0, Int_t, MOTION_DYNAMIC);
        ADD_GLOBAL("MOTION_SPHERE_INERTIA", 0, Int_t, MOTION_SPHERE_INERTIA);
        ADD_GLOBAL("MOTION_BOX_INERTIA", 0, Int_t, MOTION_BOX_INERTIA);
        ADD_GLOBAL("MOTION_KEY_FRAMED", 0, Int_t, MOTION_KEY_FRAMED);
        ADD_GLOBAL("MOTION_FIXED", 0, Int_t, MOTION_FIXED);
        ADD_GLOBAL("MOTION_THIN_BOX_INERTIA", 0, Int_t, MOTION_THIN_BOX_INERTIA);
        ADD_GLOBAL("MOTION_CHARACTER", 0, Int_t, MOTION_CHARACTER);

        ADD_GLOBAL("OUTFIT_BASE", 0, Int_t, OUTFIT_BASE);
        ADD_GLOBAL("OUTFIT_REFERENCE", 0, Int_t, OUTFIT_REFERENCE);

        ADD_GLOBAL("OUTFIT2_CURRENT", 0, Int_t, OUTFIT2_CURRENT);
        ADD_GLOBAL("OUTFIT2_MEMBER", 0, Int_t, OUTFIT2_MEMBER);
        ADD_GLOBAL("OUTFIT2_SETTLER", 0, Int_t, OUTFIT2_SETTLER);
        ADD_GLOBAL("OUTFIT2_THRALL", 0, Int_t, OUTFIT2_THRALL);
        ADD_GLOBAL("OUTFIT2_FOLLOWER", 0, Int_t, OUTFIT2_FOLLOWER);
        ADD_GLOBAL("OUTFIT2_IMMOBILE", 0, Int_t, OUTFIT2_IMMOBILE);
        ADD_GLOBAL("OUTFIT2_VANILLA", 0, Int_t, OUTFIT2_VANILLA);
        ADD_GLOBAL("OUTFIT2_DEFAULT", 0, Int_t, OUTFIT2_DEFAULT);

        ADD_GLOBAL("SEX_MALE", 0, Int_t, SEX_MALE);
        ADD_GLOBAL("SEX_FEMALE", 0, Int_t, SEX_FEMALE);
        ADD_GLOBAL("SEX_NONE", 0, Int_t, SEX_NONE);

        ADD_GLOBAL("STYLE_DEFAULT", 0, Int_t, STYLE_DEFAULT);
        ADD_GLOBAL("STYLE_WARRIOR", 0, Int_t, STYLE_WARRIOR);
        ADD_GLOBAL("STYLE_MAGE", 0, Int_t, STYLE_MAGE);
        ADD_GLOBAL("STYLE_ARCHER", 0, Int_t, STYLE_ARCHER);
        ADD_GLOBAL("STYLE_COWARD", 0, Int_t, STYLE_COWARD);

        ADD_GLOBAL("VIEW_MEMBERS", 0, Int_t, VIEW_MEMBERS);
        ADD_GLOBAL("VIEW_FOLLOWERS", 0, Int_t, VIEW_FOLLOWERS);
        ADD_GLOBAL("VIEW_MEMBERS_MEMBER", 0, Int_t, VIEW_MEMBERS_MEMBER);
        ADD_GLOBAL("VIEW_FOLLOWERS_MEMBER", 0, Int_t, VIEW_FOLLOWERS_MEMBER);
        ADD_GLOBAL("VIEW_FILTER", 0, Int_t, VIEW_FILTER);
        ADD_GLOBAL("VIEW_FILTER_MEMBERS", 0, Int_t, VIEW_FILTER_MEMBERS);
        ADD_GLOBAL("VIEW_FILTER_MEMBERS_MEMBER", 0, Int_t, VIEW_FILTER_MEMBERS_MEMBER);
        ADD_GLOBAL("VIEW_MANNEQUINS", 0, Int_t, VIEW_MANNEQUINS);
        ADD_GLOBAL("VIEW_MANNEQUINS_CELL", 0, Int_t, VIEW_MANNEQUINS_CELL);
        ADD_GLOBAL("VIEW_MANNEQUINS_MEMBER", 0, Int_t, VIEW_MANNEQUINS_MEMBER);

        ADD_GLOBAL("VITALITY_MORTAL", 0, Int_t, VITALITY_MORTAL);
        ADD_GLOBAL("VITALITY_PROTECTED", 0, Int_t, VITALITY_PROTECTED);
        ADD_GLOBAL("VITALITY_ESSENTIAL", 0, Int_t, VITALITY_ESSENTIAL);
        ADD_GLOBAL("VITALITY_INVULNERABLE", 0, Int_t, VITALITY_INVULNERABLE);

        #undef ADD_GLOBAL

        return true;
    }

}}}
