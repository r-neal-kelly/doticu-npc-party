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
    Int_t STARTED(Selfless_t*)                      { return CODES::STARTED; }
    Int_t STOPPED(Selfless_t*)                      { return CODES::STOPPED; }
    Int_t SYNC(Selfless_t*)                         { return CODES::SYNC; }
    Int_t ASYNC(Selfless_t*)                        { return CODES::ASYNC; }
    Int_t OUT_OF_BOUNDS(Selfless_t*)                { return CODES::OUT_OF_BOUNDS; }

    Int_t IS_ACTOR(Selfless_t*)                     { return CODES::IS_ACTOR; }
    Int_t ISNT_ACTOR(Selfless_t*)                   { return CODES::ISNT_ACTOR; }
    Int_t IS_LOADED(Selfless_t*)                    { return CODES::IS_LOADED; }
    Int_t ISNT_LOADED(Selfless_t*)                  { return CODES::ISNT_LOADED; }
    Int_t IS_UNLOADED(Selfless_t*)                  { return CODES::IS_UNLOADED; }
    Int_t ISNT_UNLOADED(Selfless_t*)                { return CODES::ISNT_UNLOADED; }
    Int_t IS_UNIQUE(Selfless_t*)                    { return CODES::IS_UNIQUE; }
    Int_t ISNT_UNIQUE(Selfless_t*)                  { return CODES::ISNT_UNIQUE; }
    Int_t IS_GENERIC(Selfless_t*)                   { return CODES::IS_GENERIC; }
    Int_t ISNT_GENERIC(Selfless_t*)                 { return CODES::ISNT_GENERIC; }
    Int_t IS_ORIGINAL(Selfless_t*)                  { return CODES::IS_ORIGINAL; }
    Int_t ISNT_ORIGINAL(Selfless_t*)                { return CODES::ISNT_ORIGINAL; }
    Int_t IS_CLONE(Selfless_t*)                     { return CODES::IS_CLONE; }
    Int_t ISNT_CLONE(Selfless_t*)                   { return CODES::ISNT_CLONE; }
    Int_t IS_ALIVE(Selfless_t*)                     { return CODES::IS_ALIVE; }
    Int_t ISNT_ALIVE(Selfless_t*)                   { return CODES::ISNT_ALIVE; }
    Int_t IS_DEAD(Selfless_t*)                      { return CODES::IS_DEAD; }
    Int_t ISNT_DEAD(Selfless_t*)                    { return CODES::ISNT_DEAD; }
    Int_t IS_MEMBER(Selfless_t*)                    { return CODES::IS_MEMBER; }
    Int_t ISNT_MEMBER(Selfless_t*)                  { return CODES::ISNT_MEMBER; }
    Int_t IS_NON_MEMBER(Selfless_t*)                { return CODES::IS_NON_MEMBER; }
    Int_t ISNT_NON_MEMBER(Selfless_t*)              { return CODES::ISNT_NON_MEMBER; }
    Int_t IS_MOBILE(Selfless_t*)                    { return CODES::IS_MOBILE; }
    Int_t ISNT_MOBILE(Selfless_t*)                  { return CODES::ISNT_MOBILE; }
    Int_t IS_IMMOBILE(Selfless_t*)                  { return CODES::IS_IMMOBILE; }
    Int_t ISNT_IMMOBILE(Selfless_t*)                { return CODES::ISNT_IMMOBILE; }
    Int_t IS_SETTLER(Selfless_t*)                   { return CODES::IS_SETTLER; }
    Int_t ISNT_SETTLER(Selfless_t*)                 { return CODES::ISNT_SETTLER; }
    Int_t IS_NON_SETTLER(Selfless_t*)               { return CODES::IS_NON_SETTLER; }
    Int_t ISNT_NON_SETTLER(Selfless_t*)             { return CODES::ISNT_NON_SETTLER; }
    Int_t IS_THRALL(Selfless_t*)                    { return CODES::IS_THRALL; }
    Int_t ISNT_THRALL(Selfless_t*)                  { return CODES::ISNT_THRALL; }
    Int_t IS_NON_THRALL(Selfless_t*)                { return CODES::IS_NON_THRALL; }
    Int_t ISNT_NON_THRALL(Selfless_t*)              { return CODES::ISNT_NON_THRALL; }
    Int_t IS_PARALYZED(Selfless_t*)                 { return CODES::IS_PARALYZED; }
    Int_t ISNT_PARALYZED(Selfless_t*)               { return CODES::ISNT_PARALYZED; }
    Int_t IS_NON_PARALYZED(Selfless_t*)             { return CODES::IS_NON_PARALYZED; }
    Int_t ISNT_NON_PARALYZED(Selfless_t*)           { return CODES::ISNT_NON_PARALYZED; }
    Int_t IS_MANNEQUIN(Selfless_t*)                 { return CODES::IS_MANNEQUIN; }
    Int_t ISNT_MANNEQUIN(Selfless_t*)               { return CODES::ISNT_MANNEQUIN; }
    Int_t IS_NON_MANNEQUIN(Selfless_t*)             { return CODES::IS_NON_MANNEQUIN; }
    Int_t ISNT_NON_MANNEQUIN(Selfless_t*)           { return CODES::ISNT_NON_MANNEQUIN; }
    Int_t IS_DISPLAY(Selfless_t*)                   { return CODES::IS_DISPLAY; }
    Int_t ISNT_DISPLAY(Selfless_t*)                 { return CODES::ISNT_DISPLAY; }
    Int_t IS_NON_DISPLAY(Selfless_t*)               { return CODES::IS_NON_DISPLAY; }
    Int_t ISNT_NON_DISPLAY(Selfless_t*)             { return CODES::ISNT_NON_DISPLAY; }
    Int_t IS_REANIMATED(Selfless_t*)                { return CODES::IS_REANIMATED; }
    Int_t ISNT_REANIMATED(Selfless_t*)              { return CODES::ISNT_REANIMATED; }
    Int_t IS_NON_REANIMATED(Selfless_t*)            { return CODES::IS_NON_REANIMATED; }
    Int_t ISNT_NON_REANIMATED(Selfless_t*)          { return CODES::ISNT_NON_REANIMATED; }
    Int_t IS_FOLLOWER(Selfless_t*)                  { return CODES::IS_FOLLOWER; }
    Int_t ISNT_FOLLOWER(Selfless_t*)                { return CODES::ISNT_FOLLOWER; }
    Int_t IS_NON_FOLLOWER(Selfless_t*)              { return CODES::IS_NON_FOLLOWER; }
    Int_t ISNT_NON_FOLLOWER(Selfless_t*)            { return CODES::ISNT_NON_FOLLOWER; }
    Int_t IS_SNEAK(Selfless_t*)                     { return CODES::IS_SNEAK; }
    Int_t ISNT_SNEAK(Selfless_t*)                   { return CODES::ISNT_SNEAK; }
    Int_t IS_NON_SNEAK(Selfless_t*)                 { return CODES::IS_NON_SNEAK; }
    Int_t ISNT_NON_SNEAK(Selfless_t*)               { return CODES::ISNT_NON_SNEAK; }
    Int_t IS_SADDLER(Selfless_t*)                   { return CODES::IS_SADDLER; }
    Int_t ISNT_SADDLER(Selfless_t*)                 { return CODES::ISNT_SADDLER; }
    Int_t IS_NON_SADDLER(Selfless_t*)               { return CODES::IS_NON_SADDLER; }
    Int_t ISNT_NON_SADDLER(Selfless_t*)             { return CODES::ISNT_NON_SADDLER; }
    Int_t IS_RETREATER(Selfless_t*)                 { return CODES::IS_RETREATER; }
    Int_t ISNT_RETREATER(Selfless_t*)               { return CODES::ISNT_RETREATER; }
    Int_t IS_NON_RETREATER(Selfless_t*)             { return CODES::IS_NON_RETREATER; }
    Int_t ISNT_NON_RETREATER(Selfless_t*)           { return CODES::ISNT_NON_RETREATER; }

    Int_t IS_STYLE(Selfless_t*)                     { return CODES::IS_STYLE; }
    Int_t ISNT_STYLE(Selfless_t*)                   { return CODES::ISNT_STYLE; }
    Int_t IS_DEFAULT(Selfless_t*)                   { return CODES::IS_DEFAULT; }
    Int_t IS_WARRIOR(Selfless_t*)                   { return CODES::IS_WARRIOR; }
    Int_t IS_MAGE(Selfless_t*)                      { return CODES::IS_MAGE; }
    Int_t IS_ARCHER(Selfless_t*)                    { return CODES::IS_ARCHER; }
    Int_t IS_COWARD(Selfless_t*)                    { return CODES::IS_COWARD; }

    Int_t IS_VITALITY(Selfless_t*)                  { return CODES::IS_VITALITY; }
    Int_t ISNT_VITALITY(Selfless_t*)                { return CODES::ISNT_VITALITY; }
    Int_t IS_MORTAL(Selfless_t*)                    { return CODES::IS_MORTAL; }
    Int_t IS_PROTECTED(Selfless_t*)                 { return CODES::IS_PROTECTED; }
    Int_t IS_ESSENTIAL(Selfless_t*)                 { return CODES::IS_ESSENTIAL; }
    Int_t IS_INVULNERABLE(Selfless_t*)              { return CODES::IS_INVULNERABLE; }

    Int_t HAS_ACTOR(Selfless_t*)                    { return CODES::HAS_ACTOR; }
    Int_t HASNT_ACTOR(Selfless_t*)                  { return CODES::HASNT_ACTOR; }
    Int_t HAS_LOADED(Selfless_t*)                   { return CODES::HAS_LOADED; }
    Int_t HASNT_LOADED(Selfless_t*)                 { return CODES::HASNT_LOADED; }
    Int_t HAS_UNLOADED(Selfless_t*)                 { return CODES::HAS_UNLOADED; }
    Int_t HASNT_UNLOADED(Selfless_t*)               { return CODES::HASNT_UNLOADED; }
    Int_t HAS_UNIQUE(Selfless_t*)                   { return CODES::HAS_UNIQUE; }
    Int_t HASNT_UNIQUE(Selfless_t*)                 { return CODES::HASNT_UNIQUE; }
    Int_t HAS_GENERIC(Selfless_t*)                  { return CODES::HAS_GENERIC; }
    Int_t HASNT_GENERIC(Selfless_t*)                { return CODES::HASNT_GENERIC; }
    Int_t HAS_ORIGINAL(Selfless_t*)                 { return CODES::HAS_ORIGINAL; }
    Int_t HASNT_ORIGINAL(Selfless_t*)               { return CODES::HASNT_ORIGINAL; }
    Int_t HAS_CLONE(Selfless_t*)                    { return CODES::HAS_CLONE; }
    Int_t HASNT_CLONE(Selfless_t*)                  { return CODES::HASNT_CLONE; }
    Int_t HAS_ALIVE(Selfless_t*)                    { return CODES::HAS_ALIVE; }
    Int_t HASNT_ALIVE(Selfless_t*)                  { return CODES::HASNT_ALIVE; }
    Int_t HAS_DEAD(Selfless_t*)                     { return CODES::HAS_DEAD; }
    Int_t HASNT_DEAD(Selfless_t*)                   { return CODES::HASNT_DEAD; }
    Int_t HAS_MEMBER(Selfless_t*)                   { return CODES::HAS_MEMBER; }
    Int_t HASNT_MEMBER(Selfless_t*)                 { return CODES::HASNT_MEMBER; }
    Int_t HAS_NON_MEMBER(Selfless_t*)               { return CODES::HAS_NON_MEMBER; }
    Int_t HASNT_NON_MEMBER(Selfless_t*)             { return CODES::HASNT_NON_MEMBER; }
    Int_t HAS_MOBILE(Selfless_t*)                   { return CODES::HAS_MOBILE; }
    Int_t HASNT_MOBILE(Selfless_t*)                 { return CODES::HASNT_MOBILE; }
    Int_t HAS_IMMOBILE(Selfless_t*)                 { return CODES::HAS_IMMOBILE; }
    Int_t HASNT_IMMOBILE(Selfless_t*)               { return CODES::HASNT_IMMOBILE; }
    Int_t HAS_SETTLER(Selfless_t*)                  { return CODES::HAS_SETTLER; }
    Int_t HASNT_SETTLER(Selfless_t*)                { return CODES::HASNT_SETTLER; }
    Int_t HAS_NON_SETTLER(Selfless_t*)              { return CODES::HAS_NON_SETTLER; }
    Int_t HASNT_NON_SETTLER(Selfless_t*)            { return CODES::HASNT_NON_SETTLER; }
    Int_t HAS_THRALL(Selfless_t*)                   { return CODES::HAS_THRALL; }
    Int_t HASNT_THRALL(Selfless_t*)                 { return CODES::HASNT_THRALL; }
    Int_t HAS_NON_THRALL(Selfless_t*)               { return CODES::HAS_NON_THRALL; }
    Int_t HASNT_NON_THRALL(Selfless_t*)             { return CODES::HASNT_NON_THRALL; }
    Int_t HAS_PARALYZED(Selfless_t*)                { return CODES::HAS_PARALYZED; }
    Int_t HASNT_PARALYZED(Selfless_t*)              { return CODES::HASNT_PARALYZED; }
    Int_t HAS_NON_PARALYZED(Selfless_t*)            { return CODES::HAS_NON_PARALYZED; }
    Int_t HASNT_NON_PARALYZED(Selfless_t*)          { return CODES::HASNT_NON_PARALYZED; }
    Int_t HAS_MANNEQUIN(Selfless_t*)                { return CODES::HAS_MANNEQUIN; }
    Int_t HASNT_MANNEQUIN(Selfless_t*)              { return CODES::HASNT_MANNEQUIN; }
    Int_t HAS_NON_MANNEQUIN(Selfless_t*)            { return CODES::HAS_NON_MANNEQUIN; }
    Int_t HASNT_NON_MANNEQUIN(Selfless_t*)          { return CODES::HASNT_NON_MANNEQUIN; }
    Int_t HAS_DISPLAY(Selfless_t*)                  { return CODES::HAS_DISPLAY; }
    Int_t HASNT_DISPLAY(Selfless_t*)                { return CODES::HASNT_DISPLAY; }
    Int_t HAS_NON_DISPLAY(Selfless_t*)              { return CODES::HAS_NON_DISPLAY; }
    Int_t HASNT_NON_DISPLAY(Selfless_t*)            { return CODES::HASNT_NON_DISPLAY; }
    Int_t HAS_REANIMATED(Selfless_t*)               { return CODES::HAS_REANIMATED; }
    Int_t HASNT_REANIMATED(Selfless_t*)             { return CODES::HASNT_REANIMATED; }
    Int_t HAS_NON_REANIMATED(Selfless_t*)           { return CODES::HAS_NON_REANIMATED; }
    Int_t HASNT_NON_REANIMATED(Selfless_t*)         { return CODES::HASNT_NON_REANIMATED; }
    Int_t HAS_FOLLOWER(Selfless_t*)                 { return CODES::HAS_FOLLOWER; }
    Int_t HASNT_FOLLOWER(Selfless_t*)               { return CODES::HASNT_FOLLOWER; }
    Int_t HAS_NON_FOLLOWER(Selfless_t*)             { return CODES::HAS_NON_FOLLOWER; }
    Int_t HASNT_NON_FOLLOWER(Selfless_t*)           { return CODES::HASNT_NON_FOLLOWER; }
    Int_t HAS_SNEAK(Selfless_t*)                    { return CODES::HAS_SNEAK; }
    Int_t HASNT_SNEAK(Selfless_t*)                  { return CODES::HASNT_SNEAK; }
    Int_t HAS_NON_SNEAK(Selfless_t*)                { return CODES::HAS_NON_SNEAK; }
    Int_t HASNT_NON_SNEAK(Selfless_t*)              { return CODES::HASNT_NON_SNEAK; }
    Int_t HAS_SADDLER(Selfless_t*)                  { return CODES::HAS_SADDLER; }
    Int_t HASNT_SADDLER(Selfless_t*)                { return CODES::HASNT_SADDLER; }
    Int_t HAS_NON_SADDLER(Selfless_t*)              { return CODES::HAS_NON_SADDLER; }
    Int_t HASNT_NON_SADDLER(Selfless_t*)            { return CODES::HASNT_NON_SADDLER; }
    Int_t HAS_RETREATER(Selfless_t*)                { return CODES::HAS_RETREATER; }
    Int_t HASNT_RETREATER(Selfless_t*)              { return CODES::HASNT_RETREATER; }
    Int_t HAS_NON_RETREATER(Selfless_t*)            { return CODES::HAS_NON_RETREATER; }
    Int_t HASNT_NON_RETREATER(Selfless_t*)          { return CODES::HASNT_NON_RETREATER; }
    Int_t HAS_MARKER(Selfless_t*)                   { return CODES::HAS_MARKER; }
    Int_t HASNT_MARKER(Selfless_t*)                 { return CODES::HASNT_MARKER; }

    Int_t CHILD(Selfless_t*)                        { return CODES::CHILD; }
    Int_t ADULT(Selfless_t*)                        { return CODES::ADULT; }
    Int_t INTERIOR(Selfless_t*)                     { return CODES::INTERIOR; }
    Int_t EXTERIOR(Selfless_t*)                     { return CODES::EXTERIOR; }
    Int_t RATING(Selfless_t*)                       { return CODES::RATING; }
    Int_t NON_RATING(Selfless_t*)                   { return CODES::NON_RATING; }
    Int_t VAMPIRE(Selfless_t*)                      { return CODES::VAMPIRE; }
    Int_t NON_VAMPIRE(Selfless_t*)                  { return CODES::NON_VAMPIRE; }

    Int_t CAN_RESURRECT(Selfless_t*)                { return CODES::CAN_RESURRECT; }
    Int_t CANT_RESURRECT(Selfless_t*)               { return CODES::CANT_RESURRECT; }
    Int_t CAN_CLONE(Selfless_t*)                    { return CODES::CAN_CLONE; }
    Int_t CANT_CLONE(Selfless_t*)                   { return CODES::CANT_CLONE; }

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
        ADD_GLOBAL("STARTED", 0, Int_t, STARTED);
        ADD_GLOBAL("STOPPED", 0, Int_t, STOPPED);
        ADD_GLOBAL("SYNC", 0, Int_t, SYNC);
        ADD_GLOBAL("ASYNC", 0, Int_t, ASYNC);
        ADD_GLOBAL("OUT_OF_BOUNDS", 0, Int_t, OUT_OF_BOUNDS);

        ADD_GLOBAL("IS_ACTOR", 0, Int_t, IS_ACTOR);
        ADD_GLOBAL("ISNT_ACTOR", 0, Int_t, ISNT_ACTOR);
        ADD_GLOBAL("IS_LOADED", 0, Int_t, IS_LOADED);
        ADD_GLOBAL("ISNT_LOADED", 0, Int_t, ISNT_LOADED);
        ADD_GLOBAL("IS_UNLOADED", 0, Int_t, IS_UNLOADED);
        ADD_GLOBAL("ISNT_UNLOADED", 0, Int_t, ISNT_UNLOADED);
        ADD_GLOBAL("IS_UNIQUE", 0, Int_t, IS_UNIQUE);
        ADD_GLOBAL("ISNT_UNIQUE", 0, Int_t, ISNT_UNIQUE);
        ADD_GLOBAL("IS_GENERIC", 0, Int_t, IS_GENERIC);
        ADD_GLOBAL("ISNT_GENERIC", 0, Int_t, ISNT_GENERIC);
        ADD_GLOBAL("IS_ORIGINAL", 0, Int_t, IS_ORIGINAL);
        ADD_GLOBAL("ISNT_ORIGINAL", 0, Int_t, ISNT_ORIGINAL);
        ADD_GLOBAL("IS_CLONE", 0, Int_t, IS_CLONE);
        ADD_GLOBAL("ISNT_CLONE", 0, Int_t, ISNT_CLONE);
        ADD_GLOBAL("IS_ALIVE", 0, Int_t, IS_ALIVE);
        ADD_GLOBAL("ISNT_ALIVE", 0, Int_t, ISNT_ALIVE);
        ADD_GLOBAL("IS_DEAD", 0, Int_t, IS_DEAD);
        ADD_GLOBAL("ISNT_DEAD", 0, Int_t, ISNT_DEAD);
        ADD_GLOBAL("IS_MEMBER", 0, Int_t, IS_MEMBER);
        ADD_GLOBAL("ISNT_MEMBER", 0, Int_t, ISNT_MEMBER);
        ADD_GLOBAL("IS_NON_MEMBER", 0, Int_t, IS_NON_MEMBER);
        ADD_GLOBAL("ISNT_NON_MEMBER", 0, Int_t, ISNT_NON_MEMBER);
        ADD_GLOBAL("IS_MOBILE", 0, Int_t, IS_MOBILE);
        ADD_GLOBAL("ISNT_MOBILE", 0, Int_t, ISNT_MOBILE);
        ADD_GLOBAL("IS_IMMOBILE", 0, Int_t, IS_IMMOBILE);
        ADD_GLOBAL("ISNT_IMMOBILE", 0, Int_t, ISNT_IMMOBILE);
        ADD_GLOBAL("IS_SETTLER", 0, Int_t, IS_SETTLER);
        ADD_GLOBAL("ISNT_SETTLER", 0, Int_t, ISNT_SETTLER);
        ADD_GLOBAL("IS_NON_SETTLER", 0, Int_t, IS_NON_SETTLER);
        ADD_GLOBAL("ISNT_NON_SETTLER", 0, Int_t, ISNT_NON_SETTLER);
        ADD_GLOBAL("IS_THRALL", 0, Int_t, IS_THRALL);
        ADD_GLOBAL("ISNT_THRALL", 0, Int_t, ISNT_THRALL);
        ADD_GLOBAL("IS_NON_THRALL", 0, Int_t, IS_NON_THRALL);
        ADD_GLOBAL("ISNT_NON_THRALL", 0, Int_t, ISNT_NON_THRALL);
        ADD_GLOBAL("IS_PARALYZED", 0, Int_t, IS_PARALYZED);
        ADD_GLOBAL("ISNT_PARALYZED", 0, Int_t, ISNT_PARALYZED);
        ADD_GLOBAL("IS_NON_PARALYZED", 0, Int_t, IS_NON_PARALYZED);
        ADD_GLOBAL("ISNT_NON_PARALYZED", 0, Int_t, ISNT_NON_PARALYZED);
        ADD_GLOBAL("IS_MANNEQUIN", 0, Int_t, IS_MANNEQUIN);
        ADD_GLOBAL("ISNT_MANNEQUIN", 0, Int_t, ISNT_MANNEQUIN);
        ADD_GLOBAL("IS_NON_MANNEQUIN", 0, Int_t, IS_NON_MANNEQUIN);
        ADD_GLOBAL("ISNT_NON_MANNEQUIN", 0, Int_t, ISNT_NON_MANNEQUIN);
        ADD_GLOBAL("IS_DISPLAY", 0, Int_t, IS_DISPLAY);
        ADD_GLOBAL("ISNT_DISPLAY", 0, Int_t, ISNT_DISPLAY);
        ADD_GLOBAL("IS_NON_DISPLAY", 0, Int_t, IS_NON_DISPLAY);
        ADD_GLOBAL("ISNT_NON_DISPLAY", 0, Int_t, ISNT_NON_DISPLAY);
        ADD_GLOBAL("IS_REANIMATED", 0, Int_t, IS_REANIMATED);
        ADD_GLOBAL("ISNT_REANIMATED", 0, Int_t, ISNT_REANIMATED);
        ADD_GLOBAL("IS_NON_REANIMATED", 0, Int_t, IS_NON_REANIMATED);
        ADD_GLOBAL("ISNT_NON_REANIMATED", 0, Int_t, ISNT_NON_REANIMATED);
        ADD_GLOBAL("IS_FOLLOWER", 0, Int_t, IS_FOLLOWER);
        ADD_GLOBAL("ISNT_FOLLOWER", 0, Int_t, ISNT_FOLLOWER);
        ADD_GLOBAL("IS_NON_FOLLOWER", 0, Int_t, IS_NON_FOLLOWER);
        ADD_GLOBAL("ISNT_NON_FOLLOWER", 0, Int_t, ISNT_NON_FOLLOWER);
        ADD_GLOBAL("IS_SNEAK", 0, Int_t, IS_SNEAK);
        ADD_GLOBAL("ISNT_SNEAK", 0, Int_t, ISNT_SNEAK);
        ADD_GLOBAL("IS_NON_SNEAK", 0, Int_t, IS_NON_SNEAK);
        ADD_GLOBAL("ISNT_NON_SNEAK", 0, Int_t, ISNT_NON_SNEAK);
        ADD_GLOBAL("IS_SADDLER", 0, Int_t, IS_SADDLER);
        ADD_GLOBAL("ISNT_SADDLER", 0, Int_t, ISNT_SADDLER);
        ADD_GLOBAL("IS_NON_SADDLER", 0, Int_t, IS_NON_SADDLER);
        ADD_GLOBAL("ISNT_NON_SADDLER", 0, Int_t, ISNT_NON_SADDLER);
        ADD_GLOBAL("IS_RETREATER", 0, Int_t, IS_RETREATER);
        ADD_GLOBAL("ISNT_RETREATER", 0, Int_t, ISNT_RETREATER);
        ADD_GLOBAL("IS_NON_RETREATER", 0, Int_t, IS_NON_RETREATER);
        ADD_GLOBAL("ISNT_NON_RETREATER", 0, Int_t, ISNT_NON_RETREATER);

        ADD_GLOBAL("IS_STYLE", 0, Int_t, IS_STYLE);
        ADD_GLOBAL("ISNT_STYLE", 0, Int_t, ISNT_STYLE);
        ADD_GLOBAL("IS_DEFAULT", 0, Int_t, IS_DEFAULT);
        ADD_GLOBAL("IS_WARRIOR", 0, Int_t, IS_WARRIOR);
        ADD_GLOBAL("IS_MAGE", 0, Int_t, IS_MAGE);
        ADD_GLOBAL("IS_ARCHER", 0, Int_t, IS_ARCHER);
        ADD_GLOBAL("IS_COWARD", 0, Int_t, IS_COWARD);

        ADD_GLOBAL("IS_VITALITY", 0, Int_t, IS_VITALITY);
        ADD_GLOBAL("ISNT_VITALITY", 0, Int_t, ISNT_VITALITY);
        ADD_GLOBAL("IS_MORTAL", 0, Int_t, IS_MORTAL);
        ADD_GLOBAL("IS_PROTECTED", 0, Int_t, IS_PROTECTED);
        ADD_GLOBAL("IS_ESSENTIAL", 0, Int_t, IS_ESSENTIAL);
        ADD_GLOBAL("IS_INVULNERABLE", 0, Int_t, IS_INVULNERABLE);
        
        ADD_GLOBAL("HAS_ACTOR", 0, Int_t, HAS_ACTOR);
        ADD_GLOBAL("HASNT_ACTOR", 0, Int_t, HASNT_ACTOR);
        ADD_GLOBAL("HAS_LOADED", 0, Int_t, HAS_LOADED);
        ADD_GLOBAL("HASNT_LOADED", 0, Int_t, HASNT_LOADED);
        ADD_GLOBAL("HAS_UNLOADED", 0, Int_t, HAS_UNLOADED);
        ADD_GLOBAL("HASNT_UNLOADED", 0, Int_t, HASNT_UNLOADED);
        ADD_GLOBAL("HAS_UNIQUE", 0, Int_t, HAS_UNIQUE);
        ADD_GLOBAL("HASNT_UNIQUE", 0, Int_t, HASNT_UNIQUE);
        ADD_GLOBAL("HAS_GENERIC", 0, Int_t, HAS_GENERIC);
        ADD_GLOBAL("HASNT_GENERIC", 0, Int_t, HASNT_GENERIC);
        ADD_GLOBAL("HAS_ORIGINAL", 0, Int_t, HAS_ORIGINAL);
        ADD_GLOBAL("HASNT_ORIGINAL", 0, Int_t, HASNT_ORIGINAL);
        ADD_GLOBAL("HAS_CLONE", 0, Int_t, HAS_CLONE);
        ADD_GLOBAL("HASNT_CLONE", 0, Int_t, HASNT_CLONE);
        ADD_GLOBAL("HAS_ALIVE", 0, Int_t, HAS_ALIVE);
        ADD_GLOBAL("HASNT_ALIVE", 0, Int_t, HASNT_ALIVE);
        ADD_GLOBAL("HAS_DEAD", 0, Int_t, HAS_DEAD);
        ADD_GLOBAL("HASNT_DEAD", 0, Int_t, HASNT_DEAD);
        ADD_GLOBAL("HAS_MEMBER", 0, Int_t, HAS_MEMBER);
        ADD_GLOBAL("HASNT_MEMBER", 0, Int_t, HASNT_MEMBER);
        ADD_GLOBAL("HAS_NON_MEMBER", 0, Int_t, HAS_NON_MEMBER);
        ADD_GLOBAL("HASNT_NON_MEMBER", 0, Int_t, HASNT_NON_MEMBER);
        ADD_GLOBAL("HAS_MOBILE", 0, Int_t, HAS_MOBILE);
        ADD_GLOBAL("HASNT_MOBILE", 0, Int_t, HASNT_MOBILE);
        ADD_GLOBAL("HAS_IMMOBILE", 0, Int_t, HAS_IMMOBILE);
        ADD_GLOBAL("HASNT_IMMOBILE", 0, Int_t, HASNT_IMMOBILE);
        ADD_GLOBAL("HAS_SETTLER", 0, Int_t, HAS_SETTLER);
        ADD_GLOBAL("HASNT_SETTLER", 0, Int_t, HASNT_SETTLER);
        ADD_GLOBAL("HAS_NON_SETTLER", 0, Int_t, HAS_NON_SETTLER);
        ADD_GLOBAL("HASNT_NON_SETTLER", 0, Int_t, HASNT_NON_SETTLER);
        ADD_GLOBAL("HAS_THRALL", 0, Int_t, HAS_THRALL);
        ADD_GLOBAL("HASNT_THRALL", 0, Int_t, HASNT_THRALL);
        ADD_GLOBAL("HAS_NON_THRALL", 0, Int_t, HAS_NON_THRALL);
        ADD_GLOBAL("HASNT_NON_THRALL", 0, Int_t, HASNT_NON_THRALL);
        ADD_GLOBAL("HAS_PARALYZED", 0, Int_t, HAS_PARALYZED);
        ADD_GLOBAL("HASNT_PARALYZED", 0, Int_t, HASNT_PARALYZED);
        ADD_GLOBAL("HAS_NON_PARALYZED", 0, Int_t, HAS_NON_PARALYZED);
        ADD_GLOBAL("HASNT_NON_PARALYZED", 0, Int_t, HASNT_NON_PARALYZED);
        ADD_GLOBAL("HAS_MANNEQUIN", 0, Int_t, HAS_MANNEQUIN);
        ADD_GLOBAL("HASNT_MANNEQUIN", 0, Int_t, HASNT_MANNEQUIN);
        ADD_GLOBAL("HAS_NON_MANNEQUIN", 0, Int_t, HAS_NON_MANNEQUIN);
        ADD_GLOBAL("HASNT_NON_MANNEQUIN", 0, Int_t, HASNT_NON_MANNEQUIN);
        ADD_GLOBAL("HAS_DISPLAY", 0, Int_t, HAS_DISPLAY);
        ADD_GLOBAL("HASNT_DISPLAY", 0, Int_t, HASNT_DISPLAY);
        ADD_GLOBAL("HAS_NON_DISPLAY", 0, Int_t, HAS_NON_DISPLAY);
        ADD_GLOBAL("HASNT_NON_DISPLAY", 0, Int_t, HASNT_NON_DISPLAY);
        ADD_GLOBAL("HAS_REANIMATED", 0, Int_t, HAS_REANIMATED);
        ADD_GLOBAL("HASNT_REANIMATED", 0, Int_t, HASNT_REANIMATED);
        ADD_GLOBAL("HAS_NON_REANIMATED", 0, Int_t, HAS_NON_REANIMATED);
        ADD_GLOBAL("HASNT_NON_REANIMATED", 0, Int_t, HASNT_NON_REANIMATED);
        ADD_GLOBAL("HAS_FOLLOWER", 0, Int_t, HAS_FOLLOWER);
        ADD_GLOBAL("HASNT_FOLLOWER", 0, Int_t, HASNT_FOLLOWER);
        ADD_GLOBAL("HAS_NON_FOLLOWER", 0, Int_t, HAS_NON_FOLLOWER);
        ADD_GLOBAL("HASNT_NON_FOLLOWER", 0, Int_t, HASNT_NON_FOLLOWER);
        ADD_GLOBAL("HAS_SNEAK", 0, Int_t, HAS_SNEAK);
        ADD_GLOBAL("HASNT_SNEAK", 0, Int_t, HASNT_SNEAK);
        ADD_GLOBAL("HAS_NON_SNEAK", 0, Int_t, HAS_NON_SNEAK);
        ADD_GLOBAL("HASNT_NON_SNEAK", 0, Int_t, HASNT_NON_SNEAK);
        ADD_GLOBAL("HAS_SADDLER", 0, Int_t, HAS_SADDLER);
        ADD_GLOBAL("HASNT_SADDLER", 0, Int_t, HASNT_SADDLER);
        ADD_GLOBAL("HAS_NON_SADDLER", 0, Int_t, HAS_NON_SADDLER);
        ADD_GLOBAL("HASNT_NON_SADDLER", 0, Int_t, HASNT_NON_SADDLER);
        ADD_GLOBAL("HAS_RETREATER", 0, Int_t, HAS_RETREATER);
        ADD_GLOBAL("HASNT_RETREATER", 0, Int_t, HASNT_RETREATER);
        ADD_GLOBAL("HAS_NON_RETREATER", 0, Int_t, HAS_NON_RETREATER);
        ADD_GLOBAL("HASNT_NON_RETREATER", 0, Int_t, HASNT_NON_RETREATER);
        ADD_GLOBAL("HAS_MARKER", 0, Int_t, HAS_MARKER);
        ADD_GLOBAL("HASNT_MARKER", 0, Int_t, HASNT_MARKER);

        ADD_GLOBAL("CHILD", 0, Int_t, CHILD);
        ADD_GLOBAL("ADULT", 0, Int_t, ADULT);
        ADD_GLOBAL("INTERIOR", 0, Int_t, INTERIOR);
        ADD_GLOBAL("EXTERIOR", 0, Int_t, EXTERIOR);
        ADD_GLOBAL("RATING", 0, Int_t, RATING);
        ADD_GLOBAL("NON_RATING", 0, Int_t, NON_RATING);
        ADD_GLOBAL("VAMPIRE", 0, Int_t, VAMPIRE);
        ADD_GLOBAL("NON_VAMPIRE", 0, Int_t, NON_VAMPIRE);

        ADD_GLOBAL("CAN_RESURRECT", 0, Int_t, CAN_RESURRECT);
        ADD_GLOBAL("CANT_RESURRECT", 0, Int_t, CANT_RESURRECT);
        ADD_GLOBAL("CAN_CLONE", 0, Int_t, CAN_CLONE);
        ADD_GLOBAL("CANT_CLONE", 0, Int_t, CANT_CLONE);

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
