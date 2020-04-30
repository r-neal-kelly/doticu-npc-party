;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

; should probably destroy this script, it's hardly useful at all

Scriptname doticu_npcp_container extends ObjectReference

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false
string              p_str_name      =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA, string str_name)
    p_DATA = DATA

    p_is_created = true
    p_str_name = ""

    self.SetDisplayName(str_name, true)
    self.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.Disable()
    self.Delete()

    p_str_name = ""
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
function Open()
    CONTAINERS.Set_Name(self, p_str_name)
    return CONTAINERS.Open(self)
endFunction

string function Get_Name()
    return p_str_name
endFunction

function Set_Name(string str_name)
    p_str_name = str_name
    self.SetDisplayName(p_str_name, true)
endFunction

int function Count_Items()
    return CONTAINERS.Count_Items(self)
endFunction

int function Count_Item(Form form_item)
    return CONTAINERS.Count_Item(self, form_item)
endFunction

function Take_All(ObjectReference ref_container)
    return CONTAINERS.Take_All(self, ref_container)
endFunction

function Take_All_Playable(ObjectReference ref_container)
    return CONTAINERS.Take_All_Playable(self, ref_container)
endFunction

function Copy(ObjectReference ref_container)
    return CONTAINERS.Copy(self, ref_container)
endFunction

function Empty()
    return CONTAINERS.Empty(self)
endFunction
