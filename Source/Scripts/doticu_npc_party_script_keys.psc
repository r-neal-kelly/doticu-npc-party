Scriptname doticu_npc_party_script_keys extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS  = none
doticu_npc_party_script_codes   CODES   = none
doticu_npc_party_script_vars    VARS    = none
doticu_npc_party_script_mods    MODS    = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS

    Update_Keys()
endFunction

; Public Methods
function Update_Keys()
    UnregisterForAllKeys()
    RegisterForKey(VARS.key_member_create)
    RegisterForKey(VARS.key_member_destroy)
endFunction

; Events
event OnKeyDown(int code_key)
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor
    int code_return

    if code_key == VARS.key_member_create
        code_return = MODS.MEMBERS.Create_Member(ref_actor)
        if code_return == CODES.NO_ACTOR
            Debug.Notification("Not an npc. Cannot add to party.")
        elseIf code_return == CODES.IS_DUPLICATE
            Debug.Notification("Already has npc. Cannot add to party.")
        elseIf code_return == CODES.OUT_OF_SPACE
            Debug.Notification("Party is full. Cannot add npc.")
        elseIf code_return == CODES.NO_RESURRECT
            Debug.Notification("Failed to resurrect npc. Cannot add to party.")
        elseIf code_return == CODES.FATAL_ERROR
            Debug.Notification("Fatal error. Cannot add to party.")
        elseIf code_return < 0
            Debug.Notification("Unknown error. Cannot add to party.")
        else
            Debug.Notification("Added npc to party.")
        endIf
    elseIf code_key == VARS.key_member_destroy
        code_return = MODS.MEMBERS.Destroy_Member(ref_actor)
        if code_return == CODES.NO_ACTOR
            Debug.Notification("Not an npc. Cannot remove from party.")
        elseIf code_return == CODES.NO_MEMBER
            Debug.Notification("Not a member. Cannot remove from party.")
        elseIf code_return == CODES.FATAL_ERROR
            Debug.Notification("Fatal error. Cannot add to party.")
        elseIf code_return < 0
            Debug.Notification("Unknown error. Cannot remove npc.")
        else
            Debug.Notification("Removed npc from party.")
        endIf
    endIf
endEvent
