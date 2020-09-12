; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_player extends ReferenceAlias

bool    p_is_locked     = false
bool    p_is_in_combat  = false

event   On_Register() native
event   OnCrosshairRefChange(ObjectReference ref) native
event   OnControlDown(string control) native
event   OnActorAction(int action_code, Actor ref_actor, Form tool, int tool_slot) native
