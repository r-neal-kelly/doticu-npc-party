Scriptname doticu_npcp_container extends ObjectReference

; Private Constants
doticu_npcp_consts      p_CONSTS    = none
doticu_npcp_codes       p_CODES     = none
doticu_npcp_containers  p_CONTAINERS = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_CONTAINERS = DATA.MODS.FUNCS.CONTAINERS
endFunction

function f_Initialize()
endFunction

function f_Register()
endFunction

function f_Create(string str_name)
    self.SetDisplayName(str_name, true)
    self.SetActorOwner(p_CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.Disable()
    self.Delete()
endFunction

; Public Methods
function Open()
    return p_CONTAINERS.Open(self)
endFunction

string function Get_Name()
    return p_CONTAINERS.Get_Name(self)
endFunction

function Set_Name(string str_name)
    return p_CONTAINERS.Set_Name(self, str_name)
endFunction

int function Count_Items()
    return p_CONTAINERS.Count_Items(self)
endFunction

int function Count_Item(Form form_item)
    return p_CONTAINERS.Count_Item(self, form_item)
endFunction

function Take_All(ObjectReference ref_container)
    return p_CONTAINERS.Take_All(self, ref_container)
endFunction

function Copy(ObjectReference ref_container)
    return p_CONTAINERS.Copy(self, ref_container)
endFunction

function Empty()
    return p_CONTAINERS.Empty(self)
endFunction
