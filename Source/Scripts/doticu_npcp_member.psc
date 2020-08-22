; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_member extends ReferenceAlias

; Private Variables
Actor                   p_ref_actor                         =  none
ObjectReference         p_container_pack                    =  none
ObjectReference         p_marker_mannequin                  =  none
ObjectReference         p_marker_display                    =  none
ObjectReference         p_marker_undisplay                  =  none
Outfit                  p_outfit_vanilla                    =  none
Outfit                  p_outfit_default                    =  none
doticu_npcp_outfit      p_outfit2_member                    =  none
doticu_npcp_outfit      p_outfit2_immobile                  =  none
doticu_npcp_outfit      p_outfit2_settler                   =  none
doticu_npcp_outfit      p_outfit2_thrall                    =  none
doticu_npcp_outfit      p_outfit2_follower                  =  none
doticu_npcp_outfit      p_outfit2_vanilla                   =  none
doticu_npcp_outfit      p_outfit2_default                   =  none
doticu_npcp_outfit      p_outfit2_current                   =  none
doticu_npcp_outfit      p_outfit2_auto_backup               =  none

bool                    p_is_clone                          = false
bool                    p_is_immobile                       = false
bool                    p_is_settler                        = false
bool                    p_is_thrall                         = false
bool                    p_is_paralyzed                      = false
bool                    p_is_mannequin                      = false
bool                    p_is_display                        = false
bool                    p_is_reanimated                     = false

int                     p_code_style                        =     0
int                     p_code_vitality                     =     0
int                     p_code_outfit2                      =     0
int                     p_int_rating                        =     0

string                  p_str_name                          =    ""

Faction                 p_prev_faction_crime                =  none
bool                    p_prev_faction_potential_follower   = false
bool                    p_prev_faction_no_body_cleanup      = false
float                   p_prev_aggression                   =   0.0
float                   p_prev_confidence                   =   0.0
float                   p_prev_assistance                   =   0.0
float                   p_prev_morality                     =   0.0

Faction[]               p_prev_factions                     =  none; to be deleted in a future update

; Native Methods
int function ID() native
Actor function Actor() native
Alias function Follower() native
int function Style() native
int function Vitality() native
int function Outfit2() native
int function Rating() native
string function Name() native
string function Rating_Stars() native

bool function Is_Filled() native
bool function Is_Unfilled() native
bool function Is_Ready() native
bool function Is_Unready() native
bool function Is_Loaded() native
bool function Is_Unloaded() native
bool function Is_Unique() native
bool function Is_Generic() native
bool function Is_Original() native
bool function Is_Clone() native
bool function Is_Alive() native
bool function Is_Dead() native
bool function Is_Mobile() native
bool function Is_Immobile() native
bool function Is_Settler() native
bool function Isnt_Settler() native
bool function Is_Thrall() native
bool function Isnt_Thrall() native
bool function Is_Paralyzed() native
bool function Isnt_Paralyzed() native
bool function Is_Mannequin() native
bool function Isnt_Mannequin() native
bool function Is_Display() native
bool function Isnt_Display() native
bool function Is_Reanimated() native
bool function Isnt_Reanimated() native
bool function Is_Follower() native
bool function Isnt_Follower() native
bool function Is_Sneak() native
bool function Isnt_Sneak() native
bool function Is_Saddler() native
bool function Isnt_Saddler() native
bool function Is_Retreater() native
bool function Isnt_Retreater() native

int function Unmember() native
int function Clone() native
int function Unclone() native
int function Mobilize() native
int function Immobilize() native
int function Settle() native
int function Resettle() native
int function Unsettle() native
int function Enthrall() native
int function Unthrall() native
int function Paralyze() native
int function Unparalyze() native
int function Mannequinize(ObjectReference marker) native
int function Unmannequinize() native
int function Reanimate() native
int function Deanimate() native

int function Stylize(int style) native
int function Stylize_Default() native
int function Stylize_Warrior() native
int function Stylize_Mage() native
int function Stylize_Archer() native
int function Stylize_Coward() native

int function Vitalize(int vitality) native
int function Vitalize_Mortal() native
int function Vitalize_Protected() native
int function Vitalize_Essential() native
int function Vitalize_Invulnerable() native

int function Change_Outfit2(int outfit2_code) native
int function Change_Member_Outfit2() native
int function Change_Immobile_Outfit2() native
int function Change_Settler_Outfit2() native
int function Change_Thrall_Outfit2() native
int function Change_Follower_Outfit2() native
int function Change_Vanilla_Outfit2() native
int function Change_Default_Outfit2() native
int function Change_Current_Outfit2() native

int function Rate(int rating) native

function Rename(string new_name) native

function Enforce() native

int function Summon(float radius = 140.0, float degree = 0.0) native
int function Open_Pack() native
int function Stash() native
int function Resurrect() native
int function Kill() native

int function Follow() native
int function Unfollow() native

event OnLoad() native
event OnDeath(Actor killer) native
event OnActivate(ObjectReference activator) native
event OnCombatStateChanged(Actor target, int combat_code) native
event OnHit(ObjectReference attacker, Form tool, Projectile projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native

; Public Methods
int function Goto(int distance = 140, int angle = 0)
    if !Is_Filled()
        return doticu_npcp_codes.MEMBER()
    endIf

    ; this is done so that we can exit expo gracefully
    doticu_npcp.Funcs().MANNEQUINS.f_Try_Set_Teleport(self)

    doticu_npcp.Funcs().ACTORS.Move_To(doticu_npcp_consts.Player_Actor(), p_ref_actor, distance, angle)

    ;Enforce()

    return doticu_npcp_codes.SUCCESS()
endFunction
