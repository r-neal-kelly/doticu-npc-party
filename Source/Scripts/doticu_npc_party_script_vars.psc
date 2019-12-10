Scriptname doticu_npc_party_script_vars extends Quest

; Private Constants
doticu_npc_party_script_consts p_CONSTS = none

; Private Variables
bool p_auto_clone           = false
bool p_auto_clone_generic   = false
bool p_auto_delete_clone    = false
int  p_code_combat_default  =    -1

; Public Variables
int property key_resurrect                  = -1 auto hidden;
int property key_member                     = -1 auto hidden;
int property key_unmember                   = -1 auto hidden;
int property key_clone                      = -1 auto hidden;
int property key_unclone                    = -1 auto hidden;
int property key_access                     = -1 auto hidden;
int property key_settle                     = -1 auto hidden;
int property key_unsettle                   = -1 auto hidden;
int property key_immobilize                 = -1 auto hidden;
int property key_mobilize                   = -1 auto hidden;
int property key_enthrall                   = -1 auto hidden;
int property key_unthrall                   = -1 auto hidden;
int property key_style_default              = -1 auto hidden;
int property key_style_warrior              = -1 auto hidden;
int property key_style_mage                 = -1 auto hidden;
int property key_style_archer               = -1 auto hidden;
int property key_follow                     = -1 auto hidden;
int property key_unfollow                   = -1 auto hidden;
int property key_sneak                      = -1 auto hidden;
int property key_unsneak                    = -1 auto hidden;
int property key_summon_followers           = -1 auto hidden;
int property key_summon_followers_mobile    = -1 auto hidden;
int property key_summon_followers_immobile  = -1 auto hidden;
int property key_toggle_member              = 78 auto hidden; NUM+
int property key_toggle_clone               = -1 auto hidden;
int property key_toggle_settler             = 82 auto hidden; NUM0
int property key_toggle_immobile            = 83 auto hidden; NUM.
int property key_toggle_enthrall            = 73 auto hidden; NUM9
int property key_toggle_follower            = 55 auto hidden; NUM*
int property key_toggle_sneak               = 74 auto hidden; NUM-
int property key_cycle_style                = 43 auto hidden; Back Slash

bool property auto_clone hidden
    bool function Get()
        return p_auto_clone
    endFunction
    function Set(bool val)
        p_auto_clone = val
        if p_auto_clone
            p_CONSTS.GLOBAL_AUTO_CLONE.SetValue(1)
        else
            p_CONSTS.GLOBAL_AUTO_CLONE.SetValue(0)
        endIf
    endFunction
endProperty

bool property auto_clone_generic hidden
    bool function Get()
        return p_auto_clone_generic
    endFunction
    function Set(bool val)
        p_auto_clone_generic = val
        if p_auto_clone_generic
            p_CONSTS.GLOBAL_AUTO_CLONE_GENERIC.SetValue(1)
        else
            p_CONSTS.GLOBAL_AUTO_CLONE_GENERIC.SetValue(0)
        endIf
    endFunction
endProperty

bool property auto_delete_clone hidden
    bool function Get()
        return p_auto_delete_clone
    endFunction
    function Set(bool val)
        p_auto_delete_clone = val
        if p_auto_delete_clone
            p_CONSTS.GLOBAL_AUTO_DELETE_CLONE.SetValue(1)
        else
            p_CONSTS.GLOBAL_AUTO_DELETE_CLONE.SetValue(0)
        endIf
    endFunction
endProperty

int property code_combat_default hidden
    int function Get()
        return p_code_combat_default
    endFunction
    function Set(int val)
        p_code_combat_default = val
    endFunction
endProperty

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS

    auto_clone = false
    auto_clone_generic = true
    auto_delete_clone = true
    ; auto_delete_clone_generic = true
    code_combat_default = DATA.CODES.IS_DEFAULT
endFunction
