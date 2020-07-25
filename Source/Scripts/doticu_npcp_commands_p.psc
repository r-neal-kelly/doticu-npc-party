;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_commands_p extends Quest

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty
doticu_npcp_commands_p_notes property NOTES hidden
    doticu_npcp_commands_p_notes function Get()
        return (self as Quest) as doticu_npcp_commands_p_notes
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA              =  none

; Private Variables
bool                p_is_created        = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    NOTES.f_Create(DATA)

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false

    NOTES.f_Destroy()
endFunction

function f_Register()
    NOTES.f_Register()
endFunction

; Public Methods
function Member(Actor ref_actor)
    if MEMBERS.Should_Clone_Actor(ref_actor)
        Clone(ref_actor)
        return
    endIf

    string str_name = ACTORS.Name(ref_actor)

    NOTES.Member(MEMBERS.Create_Member(ref_actor), str_name)
endFunction

function Unmember(Actor ref_actor)
    if MEMBERS.Should_Unclone_Member(MEMBERS.Get_Member(ref_actor))
        Unclone(ref_actor)
        return
    endIf

    string str_name = ACTORS.Name(ref_actor)

    NOTES.Unmember(MEMBERS.Destroy_Member(ref_actor), str_name)
endFunction

function Clone(Actor ref_actor)
    string str_name = ACTORS.Name(ref_actor)

    NOTES.Clone(MEMBERS.Create_Member(ref_actor, true), str_name)
endFunction

function Unclone(Actor ref_actor)
    string str_name = ACTORS.Name(ref_actor)

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unclone(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    if !ref_member.Is_Clone()
        NOTES.Unclone(doticu_npcp_codes.ISNT_CLONE(), str_name)
        return
    endIf

    NOTES.Unclone(MEMBERS.Destroy_Member(ref_actor, true), str_name)
endFunction

function Pack(int code_exec, Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Pack(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Pack(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Pack(ref_member.Pack(code_exec), str_name)
endFunction

function Stash(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Stash(doticu_npcp_codes.HASNT_MEMBER(), ref_member.Name())
    endIf

    NOTES.Stash(ref_member.Stash(), ref_member.Name())
endFunction

function Outfit(int code_exec, Actor ref_actor, int code_outfit2, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if code_outfit2 != doticu_npcp_codes.OUTFIT2_MEMBER() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_SETTLER() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_THRALL() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_FOLLOWER() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_IMMOBILE() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_CURRENT() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_VANILLA() &&\
        code_outfit2 != doticu_npcp_codes.OUTFIT2_DEFAULT()
        code_outfit2 = doticu_npcp_codes.OUTFIT2_MEMBER(); eventually VARS.default_outfit
    endIf
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Outfit(code_return, str_name, code_outfit2)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Outfit(doticu_npcp_codes.HASNT_MEMBER(), str_name, code_outfit2)
        return
    endIf

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_CURRENT()
        code_outfit2 = ref_member.Get_Outfit2()
    endIf

    NOTES.Outfit(ref_member.Outfit(code_exec, code_outfit2), str_name, code_outfit2)
endFunction

function Outfit_Member(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_MEMBER(), auto_create)
endFunction

function Outfit_Settler(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_SETTLER(), auto_create)
endFunction

function Outfit_Thrall(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_THRALL(), auto_create)
endFunction

function Outfit_Follower(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_FOLLOWER(), auto_create)
endFunction

function Outfit_Immobile(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_IMMOBILE(), auto_create)
endFunction

function Outfit_Current(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_CURRENT(), auto_create)
endFunction

function Outfit_Vanilla(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_VANILLA(), auto_create)
endFunction

function Outfit_Default(int code_exec, Actor ref_actor, bool auto_create)
    Outfit(code_exec, ref_actor, doticu_npcp_codes.OUTFIT2_DEFAULT(), auto_create)
endFunction

function Resurrect(int code_exec, Actor ref_actor, bool auto_create)
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        ; creating a member automatically resurrects them
        NOTES.Resurrect(MEMBERS.Create_Member(ref_actor), str_name)
        return
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Resurrect(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf
    
    NOTES.Resurrect(ref_member.Resurrect(code_exec), str_name)
endFunction

function Reanimate(int code_exec, Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Reanimate(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Reanimate(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Reanimate(ref_member.Reanimate(code_exec), str_name)
endFunction

function Mannequinize(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        int code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            return NOTES.Mannequinize(code_return, ACTORS.Name(ref_actor))
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Mannequinize(doticu_npcp_codes.HASNT_MEMBER(), ACTORS.Name(ref_actor))
    endIf

    NOTES.Mannequinize(ref_member.Mannequinize(ref_marker), ACTORS.Name(ref_actor))
endFunction

function Unmannequinize(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Unmannequinize(doticu_npcp_codes.HASNT_MEMBER(), ACTORS.Name(ref_actor))
    endIf

    NOTES.Unmannequinize(ref_member.Unmannequinize(), ACTORS.Name(ref_actor))
endFunction

function Settle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Settle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Settle(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Settle(ref_member.Settle(), str_name)
endFunction

function Unsettle( Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Unsettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unsettle(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Unsettle(ref_member.Unsettle(), str_name)
endFunction

function Resettle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Resettle(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Settler()
        code_return = ref_member.Settle()
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Resettle(code_return, str_name)
            return
        endIf
    endIf

    NOTES.Resettle(ref_member.Resettle(), str_name)
endFunction

function Enthrall(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Enthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Enthrall(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Enthrall(ref_member.Enthrall(), str_name)
endFunction

function Unthrall(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Unthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unthrall(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Unthrall(ref_member.Unthrall(), str_name)
endFunction

function Immobilize(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Immobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Immobilize(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Immobilize(ref_member.Immobilize(), str_name)
endFunction

function Mobilize(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Mobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Mobilize(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Mobilize(ref_member.Mobilize(), str_name)
endFunction

function Paralyze(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Paralyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Paralyze(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf
    
    NOTES.Paralyze(ref_member.Paralyze(), str_name)
endFunction

function Unparalyze(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Unparalyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unparalyze(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Unparalyze(ref_member.Unparalyze(), str_name)
endFunction

function Stylize(Actor ref_actor, int code_style, bool auto_create)
    if code_style != doticu_npcp_codes.STYLE_DEFAULT() &&\
        code_style != doticu_npcp_codes.STYLE_WARRIOR() &&\
        code_style != doticu_npcp_codes.STYLE_MAGE() &&\
        code_style != doticu_npcp_codes.STYLE_ARCHER() &&\
        code_style != doticu_npcp_codes.STYLE_COWARD()
        code_style = VARS.auto_style; eventually VARS.default_style
    endIf

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        int code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            return NOTES.Stylize(code_return, ACTORS.Name(ref_actor), code_style)
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Stylize(doticu_npcp_codes.HASNT_MEMBER(), ACTORS.Name(ref_actor), code_style)
    endIf

    if code_style == doticu_npcp_codes.STYLE_DEFAULT()
        NOTES.Stylize(ref_member.Stylize_Default(), ACTORS.Name(ref_actor), code_style)
    elseIf code_style == doticu_npcp_codes.STYLE_WARRIOR()
        NOTES.Stylize(ref_member.Stylize_Warrior(), ACTORS.Name(ref_actor), code_style)
    elseIf code_style == doticu_npcp_codes.STYLE_MAGE()
        NOTES.Stylize(ref_member.Stylize_Mage(), ACTORS.Name(ref_actor), code_style)
    elseIf code_style == doticu_npcp_codes.STYLE_ARCHER()
        NOTES.Stylize(ref_member.Stylize_Archer(), ACTORS.Name(ref_actor), code_style)
    elseIf code_style == doticu_npcp_codes.STYLE_COWARD()
        NOTES.Stylize(ref_member.Stylize_Coward(), ACTORS.Name(ref_actor), code_style)
    endIf
endFunction

function Stylize_Default(Actor ref_actor, bool auto_create)
    Stylize(ref_actor, doticu_npcp_codes.STYLE_DEFAULT(), auto_create)
endFunction

function Stylize_Warrior(Actor ref_actor, bool auto_create)
    Stylize(ref_actor, doticu_npcp_codes.STYLE_WARRIOR(), auto_create)
endFunction

function Stylize_Mage(Actor ref_actor, bool auto_create)
    Stylize(ref_actor, doticu_npcp_codes.STYLE_MAGE(), auto_create)
endFunction

function Stylize_Archer(Actor ref_actor, bool auto_create)
    Stylize(ref_actor, doticu_npcp_codes.STYLE_ARCHER(), auto_create)
endFunction

function Stylize_Coward(Actor ref_actor, bool auto_create)
    Stylize(ref_actor, doticu_npcp_codes.STYLE_COWARD(), auto_create)
endFunction

function Vitalize(Actor ref_actor, int code_vitality, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)
    
    if code_vitality != doticu_npcp_codes.VITALITY_MORTAL() &&\
        code_vitality != doticu_npcp_codes.VITALITY_PROTECTED() &&\
        code_vitality != doticu_npcp_codes.VITALITY_ESSENTIAL() &&\
        code_vitality != doticu_npcp_codes.VITALITY_INVULNERABLE()
        code_vitality = VARS.auto_vitality; eventually VARS.default_vitality
    endIf
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Vitalize(code_return, str_name, code_vitality)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Vitalize(doticu_npcp_codes.HASNT_MEMBER(), str_name, code_vitality)
        return
    endIf

    if code_vitality == doticu_npcp_codes.VITALITY_MORTAL()
        NOTES.Vitalize(ref_member.Vitalize_Mortal(), str_name, code_vitality)
    elseIf code_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
        NOTES.Vitalize(ref_member.Vitalize_Protected(), str_name, code_vitality)
    elseIf code_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
        NOTES.Vitalize(ref_member.Vitalize_Essential(), str_name, code_vitality)
    elseIf code_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
        NOTES.Vitalize(ref_member.Vitalize_Invulnerable(), str_name, code_vitality)
    endIf
endFunction

function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, doticu_npcp_codes.VITALITY_MORTAL(), auto_create)
endFunction

function Vitalize_Protected(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, doticu_npcp_codes.VITALITY_PROTECTED(), auto_create)
endFunction

function Vitalize_Essential(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, doticu_npcp_codes.VITALITY_ESSENTIAL(), auto_create)
endFunction

function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, doticu_npcp_codes.VITALITY_INVULNERABLE(), auto_create)
endFunction

function Follow(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Follow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Follow(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Follow(ref_member.Follow(), str_name)
endFunction

function Unfollow(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Unfollow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unfollow(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Unfollow(ref_member.Unfollow(), str_name)
endFunction

function Sneak(int code_exec, Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Sneak(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        NOTES.Sneak(doticu_npcp_codes.HASNT_FOLLOWER(), str_name)
        return
    endIf

    NOTES.Sneak(ref_follower.Sneak(code_exec), str_name)
endFunction

function Unsneak(int code_exec, Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unsneak(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return != doticu_npcp_codes.SUCCESS()
            NOTES.Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        NOTES.Unsneak(doticu_npcp_codes.HASNT_FOLLOWER(), str_name)
        return
    endIf

    NOTES.Unsneak(ref_follower.Unsneak(code_exec), str_name)
endFunction

function Saddle(int code_exec, Actor ref_actor, bool auto_create)
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        int code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            return NOTES.Saddle(code_return, str_name)
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Saddle(doticu_npcp_codes.HASNT_MEMBER(), str_name)
    endIf

    if auto_create && !ref_member.Is_Follower()
        int code_return = ref_member.Follow()
        if code_return != doticu_npcp_codes.SUCCESS()
            return NOTES.Saddle(code_return, str_name)
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        return NOTES.Saddle(doticu_npcp_codes.HASNT_FOLLOWER(), str_name)
    endIf

    NOTES.Saddle(ref_follower.Saddle(code_exec), str_name)
endFunction

function Unsaddle(int code_exec, Actor ref_actor, bool auto_create)
    string str_name = ACTORS.Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        int code_return = MEMBERS.Create_Member(ref_actor)
        if code_return != doticu_npcp_codes.SUCCESS()
            return NOTES.Unsaddle(code_return, str_name)
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Unsaddle(doticu_npcp_codes.HASNT_MEMBER(), str_name)
    endIf

    if auto_create && !ref_member.Is_Follower()
        int code_return = ref_member.Follow()
        if code_return != doticu_npcp_codes.SUCCESS()
            return NOTES.Unsaddle(code_return, str_name)
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        return NOTES.Unsaddle(doticu_npcp_codes.HASNT_FOLLOWER(), str_name)
    endIf

    NOTES.Unsaddle(ref_follower.Unsaddle(code_exec), str_name)
endFunction

function Move(Actor ref_actor)
    string str_name = ACTORS.Name(ref_actor)

    NOTES.Move(ACTORS.Toggle_Move(ref_actor), str_name)
endFunction

function Summon(Actor ref_actor)
    string str_name = ACTORS.Name(ref_actor)

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Summon(doticu_npcp_codes.HASNT_MEMBER(), str_name)
        return
    endIf

    NOTES.Summon(ref_member.Summon(), str_name)
endFunction

function Goto(Actor ref_actor)
    if !ref_actor
        return NOTES.Goto(doticu_npcp_codes.ISNT_ACTOR(), "")
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return NOTES.Goto(doticu_npcp_codes.HASNT_MEMBER(), ACTORS.Name(ref_actor))
    endIf

    NOTES.Goto(ref_member.Goto(), ref_member.Name())
endFunction

function Toggle_Member(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member
        Unmember(ref_actor)
    else
        Member(ref_actor)
    endIf
endFunction

function Toggle_Clone(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Clone()
        Unclone(ref_actor)
    else
        Clone(ref_actor)
    endIf
endFunction

function Toggle_Settler(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Settler()
        Unsettle(ref_actor, true)
    else
        Settle(ref_actor, true)
    endIf
endFunction

function Toggle_Thrall(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Thrall()
        Unthrall(ref_actor, true)
    else
        Enthrall(ref_actor, true)
    endIf
endFunction

function Toggle_Immobile(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Immobile()
        Mobilize(ref_actor, true)
    else
        Immobilize(ref_actor, true)
    endIf
endFunction

function Toggle_Paralyzed(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Paralyzed()
        Unparalyze(ref_actor, true)
    else
        Paralyze(ref_actor, true)
    endIf
endFunction

function Toggle_Follower(Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower
        Unfollow(ref_actor, true)
    else
        Follow(ref_actor, true)
    endIf
endFunction

function Toggle_Sneak(int code_exec, Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower && ref_follower.Is_Sneak()
        Unsneak(code_exec, ref_actor, true)
    else
        Sneak(code_exec, ref_actor, true)
    endIf
endFunction

function Toggle_Saddle(int code_exec, Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower && ref_follower.Is_Saddler()
        Unsaddle(code_exec, ref_actor, true)
    else
        Saddle(code_exec, ref_actor, true)
    endIf
endFunction

function Toggle_Mannequin(Actor ref_actor, ObjectReference ref_marker)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Mannequin()
        Mannequinize(ref_actor, ref_marker, true)
    else
        Unmannequinize(ref_actor)
    endIf
endFunction

function Cycle_Style(Actor ref_actor, bool auto_create)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Stylize(ref_actor, VARS.auto_style, auto_create)
    else
        int style = ref_member.Style()
        if style == doticu_npcp_codes.STYLE_DEFAULT()
            Stylize(ref_actor, doticu_npcp_codes.STYLE_WARRIOR(), auto_create)
        elseIf style == doticu_npcp_codes.STYLE_WARRIOR()
            Stylize(ref_actor, doticu_npcp_codes.STYLE_MAGE(), auto_create)
        elseIf style == doticu_npcp_codes.STYLE_MAGE()
            Stylize(ref_actor, doticu_npcp_codes.STYLE_ARCHER(), auto_create)
        elseIf style == doticu_npcp_codes.STYLE_ARCHER()
            Stylize(ref_actor, doticu_npcp_codes.STYLE_COWARD(), auto_create)
        elseIf style == doticu_npcp_codes.STYLE_COWARD()
            Stylize(ref_actor, doticu_npcp_codes.STYLE_DEFAULT(), auto_create)
        endIf
    endIf
endFunction

function Cycle_Vitality(Actor ref_actor, bool auto_create)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Vitalize(ref_actor, VARS.auto_vitality, auto_create)
    else
        int vitality = ref_member.Vitality()
        if vitality == doticu_npcp_codes.VITALITY_MORTAL()
            Vitalize(ref_actor, doticu_npcp_codes.VITALITY_PROTECTED(), auto_create)
        elseIf vitality == doticu_npcp_codes.VITALITY_PROTECTED()
            Vitalize(ref_actor, doticu_npcp_codes.VITALITY_ESSENTIAL(), auto_create)
        elseIf vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
            Vitalize(ref_actor, doticu_npcp_codes.VITALITY_INVULNERABLE(), auto_create)
        elseIf vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
            Vitalize(ref_actor, doticu_npcp_codes.VITALITY_MORTAL(), auto_create)
        endIf
    endIf
endFunction

function Members_Display_Start()
    NOTES.Members_Display_Start(MEMBERS.Display_Start())
endFunction

function Members_Display_Stop()
    NOTES.Members_Display_Stop(MEMBERS.Display_Stop())
endFunction

function Members_Display_Next()
    NOTES.Members_Display_Next(MEMBERS.Display_Next())
endFunction

function Members_Display_Previous()
    NOTES.Members_Display_Previous(MEMBERS.Display_Previous())
endFunction

function Toggle_Members_Display()
    if MEMBERS.Has_Display()
        Members_Display_Stop()
    else
        Members_Display_Start()
    endIf
endFunction

function Followers_Summon_All()
    NOTES.Followers_Summon_All(FOLLOWERS.Summon())
endFunction

function Followers_Summon_Mobile()
    NOTES.Followers_Summon_Mobile(FOLLOWERS.Summon_Mobile())
endFunction

function Followers_Summon_Immobile()
    NOTES.Followers_Summon_Immobile(FOLLOWERS.Summon_Immobile())
endFunction

function Followers_Settle()
    NOTES.Followers_Settle(FOLLOWERS.Settle())
endFunction

function Followers_Unsettle()
    NOTES.Followers_Unsettle(FOLLOWERS.Unsettle())
endFunction

function Followers_Immobilize()
    NOTES.Followers_Immobilize(FOLLOWERS.Immobilize())
endFunction

function Followers_Mobilize()
    NOTES.Followers_Mobilize(FOLLOWERS.Mobilize())
endFunction

function Followers_Sneak()
    NOTES.Followers_Sneak(FOLLOWERS.Sneak())
endFunction

function Followers_Unsneak()
    NOTES.Followers_Unsneak(FOLLOWERS.Unsneak())
endFunction

function Followers_Saddle()
    NOTES.Followers_Saddle(FOLLOWERS.Saddle())
endFunction

function Followers_Unsaddle()
    NOTES.Followers_Unsaddle(FOLLOWERS.Unsaddle())
endFunction

function Followers_Stash()
    NOTES.Followers_Stash(FOLLOWERS.Stash())
endFunction

function Followers_Resurrect()
    NOTES.Followers_Resurrect(FOLLOWERS.Resurrect())
endFunction

function Followers_Unfollow()
    NOTES.Followers_Unfollow(FOLLOWERS.Unfollow())
endFunction

function Followers_Unmember()
    NOTES.Followers_Unmember(FOLLOWERS.Unmember())
endFunction

function Toggle_Followers_Settle()
    if FOLLOWERS.Count_Settlers() > 0
        Followers_Unsettle()
    else
        Followers_Settle()
    endIf
endFunction

function Toggle_Followers_Immobilize()
    if FOLLOWERS.Count_Immobile() > 0
        Followers_Mobilize()
    else
        Followers_Immobilize()
    endIf
endFunction

function Toggle_Followers_Sneak()
    if FOLLOWERS.Count_Sneaks() > 0
        Followers_Unsneak()
    else
        Followers_Sneak()
    endIf
endFunction

function Toggle_Followers_Saddle()
    if FOLLOWERS.Count_Saddlers() > 0
        Followers_Unsaddle()
    else
        Followers_Saddle()
    endIf
endFunction

function Outfit_Show(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)

    if !ref_member
        return
    endIf

    int code_outfit2 = ref_member.Get_Outfit2()
    if code_outfit2 == doticu_npcp_codes.OUTFIT2_MEMBER()
        LOGS.Create_Note("Wearing Member ", false)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_SETTLER()
        LOGS.Create_Note("Wearing Settler ", false)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_THRALL()
        LOGS.Create_Note("Wearing Thrall ", false)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_FOLLOWER()
        LOGS.Create_Note("Wearing Follower ", false)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_IMMOBILE()
        LOGS.Create_Note("Wearing Immobile ", false)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_VANILLA()
        LOGS.Create_Note("Wearing Vanilla ", false)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_DEFAULT()
        LOGS.Create_Note("Wearing Default ", false)
    endIf
endFunction

function Style_Show(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)

    if !ref_member
        return
    endIf

    int code_style = ref_member.Style()
    if code_style == doticu_npcp_codes.STYLE_DEFAULT()
        LOGS.Create_Note("Is Default ", false)
    elseIf code_style == doticu_npcp_codes.STYLE_WARRIOR()
        LOGS.Create_Note("Is Warrior ", false)
    elseIf code_style == doticu_npcp_codes.STYLE_MAGE()
        LOGS.Create_Note("Is Mage ", false)
    elseIf code_style == doticu_npcp_codes.STYLE_ARCHER()
        LOGS.Create_Note("Is Archer ", false)
    elseIf code_style == doticu_npcp_codes.STYLE_COWARD()
        LOGS.Create_Note("Is Coward ", false)
    endIf
endFunction

function Vitality_Show(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)

    if !ref_member
        return
    endIf

    int code_vitality = ref_member.Vitality()
    if code_vitality == doticu_npcp_codes.VITALITY_MORTAL()
        LOGS.Create_Note("Is Mortal ", false)
    elseIf code_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
        LOGS.Create_Note("Is Protected ", false)
    elseIf code_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
        LOGS.Create_Note("Is Essential ", false)
    elseIf code_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
        LOGS.Create_Note("Is Invulnerable ", false)
    endIf
endFunction
