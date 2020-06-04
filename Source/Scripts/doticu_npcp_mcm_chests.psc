;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_chests extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Public Constants
bool property DO_UPDATE hidden
    bool function Get()
        return MCM.DO_UPDATE
    endFunction
endProperty
bool property DONT_UPDATE hidden
    bool function Get()
        return MCM.DONT_UPDATE
    endFunction
endProperty
int property FLAG_ENABLE hidden
    int function Get()
        return MCM.FLAG_ENABLE
    endFunction
endProperty
int property FLAG_DISABLE hidden
    int function Get()
        return MCM.FLAG_DISABLE
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                  =  none

; Private Variables
bool                p_is_created            = false

int                 p_option_swords         =    -1
int                 p_option_greatswords    =    -1
int                 p_option_waraxes        =    -1
int                 p_option_battleaxes     =    -1
int                 p_option_maces          =    -1
int                 p_option_warhammers     =    -1
int                 p_option_daggers        =    -1
int                 p_option_bows           =    -1
int                 p_option_staves         =    -1
int                 p_option_weapons        =    -1

int                 p_option_light_armor    =    -1
int                 p_option_heavy_armor    =    -1
int                 p_option_shields        =    -1
int                 p_option_jewelry        =    -1
int                 p_option_clothes        =    -1

int                 p_option_potions        =    -1
int                 p_option_poisons        =    -1
int                 p_option_food           =    -1

int                 p_option_ammo           =    -1
int                 p_option_ingredients    =    -1
int                 p_option_soulgems       =    -1
int                 p_option_scrolls        =    -1
int                 p_option_metals         =    -1
int                 p_option_leather        =    -1
int                 p_option_gems           =    -1
int                 p_option_clutter        =    -1
int                 p_option_keys           =    -1
int                 p_option_others         =    -1

int                 p_option_spell_tomes    =    -1
int                 p_option_recipes        =    -1
int                 p_option_books_a        =    -1
int                 p_option_books_b        =    -1
int                 p_option_books_c        =    -1
int                 p_option_books_d        =    -1
int                 p_option_books_e        =    -1
int                 p_option_books_f        =    -1
int                 p_option_books_g        =    -1
int                 p_option_books_h        =    -1
int                 p_option_books_i        =    -1
int                 p_option_books_j        =    -1
int                 p_option_books_k        =    -1
int                 p_option_books_l        =    -1
int                 p_option_books_m        =    -1
int                 p_option_books_n        =    -1
int                 p_option_books_o        =    -1
int                 p_option_books_p        =    -1
int                 p_option_books_q        =    -1
int                 p_option_books_r        =    -1
int                 p_option_books_s        =    -1
int                 p_option_books_t        =    -1
int                 p_option_books_u        =    -1
int                 p_option_books_v        =    -1
int                 p_option_books_w        =    -1
int                 p_option_books_x        =    -1
int                 p_option_books_y        =    -1
int                 p_option_books_z        =    -1
int                 p_option_books          =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Build_Page()
    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    MCM.SetTitleText(" Chests ")

    MCM.AddHeaderOption(" Weapons ")
    MCM.AddEmptyOption()
    p_option_swords = MCM.AddTextOption(" Swords ", "")
    p_option_greatswords = MCM.AddTextOption(" Greatswords ", "")
    p_option_waraxes = MCM.AddTextOption(" Waraxes ", "")
    p_option_battleaxes = MCM.AddTextOption(" Battleaxes ", "")
    p_option_maces = MCM.AddTextOption(" Maces ", "")
    p_option_warhammers = MCM.AddTextOption(" Warhammers ", "")
    p_option_daggers = MCM.AddTextOption(" Daggers ", "")
    p_option_bows = MCM.AddTextOption(" Bows ", "")
    p_option_staves = MCM.AddTextOption(" Staves ", "")
    p_option_weapons = MCM.AddTextOption(" Others ", "")

    MCM.AddHeaderOption(" Apparel ")
    MCM.AddEmptyOption()
    p_option_light_armor = MCM.AddTextOption(" Light Armor ", "")
    p_option_heavy_armor = MCM.AddTextOption(" Heavy Armor ", "")
    p_option_shields = MCM.AddTextOption(" Shields ", "")
    p_option_jewelry = MCM.AddTextOption(" Jewelry ", "")
    p_option_clothes = MCM.AddTextOption(" Clothes ", "")
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Edibles ")
    MCM.AddEmptyOption()
    p_option_potions = MCM.AddTextOption(" Potions ", "")
    p_option_poisons = MCM.AddTextOption(" Poisons ", "")
    p_option_food = MCM.AddTextOption(" Food ", "")
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Misc ")
    MCM.AddEmptyOption()
    p_option_ammo = MCM.AddTextOption(" Ammo ", "")
    p_option_ingredients = MCM.AddTextOption(" Ingredients ", "")
    p_option_soulgems = MCM.AddTextOption(" Soulgems ", "")
    p_option_scrolls = MCM.AddTextOption(" Scrolls ", "")
    p_option_metals = MCM.AddTextOption(" Metals ", "")
    p_option_leather = MCM.AddTextOption(" Leather ", "")
    p_option_gems = MCM.AddTextOption(" Gems ", "")
    p_option_clutter = MCM.AddTextOption(" Clutter ", "")
    p_option_keys = MCM.AddTextOption(" Keys ", "")
    p_option_others = MCM.AddTextOption(" Others ", "")

    MCM.AddHeaderOption(" Books ")
    MCM.AddEmptyOption()
    p_option_spell_tomes = MCM.AddTextOption(" Spell Tomes ", "")
    p_option_recipes = MCM.AddTextOption(" Recipes ", "")
    p_option_books_a = MCM.AddTextOption(" A ", "")
    p_option_books_b = MCM.AddTextOption(" B ", "")
    p_option_books_c = MCM.AddTextOption(" C ", "")
    p_option_books_d = MCM.AddTextOption(" D ", "")
    p_option_books_e = MCM.AddTextOption(" E ", "")
    p_option_books_f = MCM.AddTextOption(" F ", "")
    p_option_books_g = MCM.AddTextOption(" G ", "")
    p_option_books_h = MCM.AddTextOption(" H ", "")
    p_option_books_i = MCM.AddTextOption(" I ", "")
    p_option_books_j = MCM.AddTextOption(" J ", "")
    p_option_books_k = MCM.AddTextOption(" K ", "")
    p_option_books_l = MCM.AddTextOption(" L ", "")
    p_option_books_m = MCM.AddTextOption(" M ", "")
    p_option_books_n = MCM.AddTextOption(" N ", "")
    p_option_books_o = MCM.AddTextOption(" O ", "")
    p_option_books_p = MCM.AddTextOption(" P ", "")
    p_option_books_q = MCM.AddTextOption(" Q ", "")
    p_option_books_r = MCM.AddTextOption(" R ", "")
    p_option_books_s = MCM.AddTextOption(" S ", "")
    p_option_books_t = MCM.AddTextOption(" T ", "")
    p_option_books_u = MCM.AddTextOption(" U ", "")
    p_option_books_v = MCM.AddTextOption(" V ", "")
    p_option_books_w = MCM.AddTextOption(" W ", "")
    p_option_books_x = MCM.AddTextOption(" X ", "")
    p_option_books_y = MCM.AddTextOption(" Y ", "")
    p_option_books_z = MCM.AddTextOption(" Z ", "")
    p_option_books = MCM.AddTextOption(" # ", "")
    MCM.AddEmptyOption()
endFunction

function f_On_Option_Select(int id_option)
    if false

    ; Weapons
    elseIf id_option == p_option_swords
        p_Open(CONSTS.CATEGORY_SWORDS, " Swords ")
    elseIf id_option == p_option_greatswords
        p_Open(CONSTS.CATEGORY_GREATSWORDS, " Greatswords ")
    elseIf id_option == p_option_waraxes
        p_Open(CONSTS.CATEGORY_WARAXES, " Waraxes ")
    elseIf id_option == p_option_battleaxes
        p_Open(CONSTS.CATEGORY_BATTLEAXES, " Battleaxes ")
    elseIf id_option == p_option_maces
        p_Open(CONSTS.CATEGORY_MACES, " Maces ")
    elseIf id_option == p_option_warhammers
        p_Open(CONSTS.CATEGORY_WARHAMMERS, " Warhammers ")
    elseIf id_option == p_option_daggers
        p_Open(CONSTS.CATEGORY_DAGGERS, " Daggers ")
    elseIf id_option == p_option_bows
        p_Open(CONSTS.CATEGORY_BOWS, " Bows ")
    elseIf id_option == p_option_staves
        p_Open(CONSTS.CATEGORY_STAVES, " Staves ")
    elseIf id_option == p_option_weapons
        p_Open(CONSTS.CATEGORY_WEAPONS, " Other Weapons ")

    ; Armor
    elseIf id_option == p_option_light_armor
        p_Open(CONSTS.CATEGORY_LIGHT_ARMOR, " Light Armor ")
    elseIf id_option == p_option_heavy_armor
        p_Open(CONSTS.CATEGORY_HEAVY_ARMOR, " Heavy Armor ")
    elseIf id_option == p_option_shields
        p_Open(CONSTS.CATEGORY_SHIELDS, " Shields ")
    elseIf id_option == p_option_jewelry
        p_Open(CONSTS.CATEGORY_JEWELRY, " Jewelry ")
    elseIf id_option == p_option_clothes
        p_Open(CONSTS.CATEGORY_CLOTHES, " Clothes ")

    ; Edibles
    elseIf id_option == p_option_potions
        p_Open(CONSTS.CATEGORY_POTIONS, " Potions ")
    elseIf id_option == p_option_poisons
        p_Open(CONSTS.CATEGORY_POISONS, " Poisons ")
    elseIf id_option == p_option_food
        p_Open(CONSTS.CATEGORY_FOOD, " Food ")

    ; Misc
    elseIf id_option == p_option_ammo
        p_Open(CONSTS.CATEGORY_AMMO, " Ammo ")
    elseIf id_option == p_option_ingredients
        p_Open(CONSTS.CATEGORY_INGREDIENTS, " Ingredients ")
    elseIf id_option == p_option_soulgems
        p_Open(CONSTS.CATEGORY_SOULGEMS, " Soulgems ")
    elseIf id_option == p_option_scrolls
        p_Open(CONSTS.CATEGORY_SCROLLS, " Scrolls ")
    elseIf id_option == p_option_metals
        p_Open(CONSTS.CATEGORY_METALS, " Metals ")
    elseIf id_option == p_option_leather
        p_Open(CONSTS.CATEGORY_LEATHER, " Leather ")
    elseIf id_option == p_option_gems
        p_Open(CONSTS.CATEGORY_GEMS, " Gems ")
    elseIf id_option == p_option_clutter
        p_Open(CONSTS.CATEGORY_CLUTTER, " Clutter ")
    elseIf id_option == p_option_keys
        p_Open(CONSTS.CATEGORY_KEYS, " Keys ")
    elseIf id_option == p_option_others
        p_Open(CONSTS.CATEGORY_OTHERS, " Other Misc ")

    ; Books
    elseIf id_option == p_option_spell_tomes
        p_Open(CONSTS.CATEGORY_SPELL_TOMES, " Spell Tomes ")
    elseIf id_option == p_option_recipes
        p_Open(CONSTS.CATEGORY_RECIPES, " Recipes ")
    elseIf id_option == p_option_books_a
        p_Open(CONSTS.CATEGORY_BOOKS_A, " Books A ")
    elseIf id_option == p_option_books_b
        p_Open(CONSTS.CATEGORY_BOOKS_B, " Books B ")
    elseIf id_option == p_option_books_c
        p_Open(CONSTS.CATEGORY_BOOKS_C, " Books C ")
    elseIf id_option == p_option_books_d
        p_Open(CONSTS.CATEGORY_BOOKS_D, " Books D ")
    elseIf id_option == p_option_books_e
        p_Open(CONSTS.CATEGORY_BOOKS_E, " Books E ")
    elseIf id_option == p_option_books_f
        p_Open(CONSTS.CATEGORY_BOOKS_F, " Books F ")
    elseIf id_option == p_option_books_g
        p_Open(CONSTS.CATEGORY_BOOKS_G, " Books G ")
    elseIf id_option == p_option_books_h
        p_Open(CONSTS.CATEGORY_BOOKS_H, " Books H ")
    elseIf id_option == p_option_books_i
        p_Open(CONSTS.CATEGORY_BOOKS_I, " Books I ")
    elseIf id_option == p_option_books_j
        p_Open(CONSTS.CATEGORY_BOOKS_J, " Books J ")
    elseIf id_option == p_option_books_k
        p_Open(CONSTS.CATEGORY_BOOKS_K, " Books K ")
    elseIf id_option == p_option_books_l
        p_Open(CONSTS.CATEGORY_BOOKS_L, " Books L ")
    elseIf id_option == p_option_books_m
        p_Open(CONSTS.CATEGORY_BOOKS_M, " Books M ")
    elseIf id_option == p_option_books_n
        p_Open(CONSTS.CATEGORY_BOOKS_N, " Books N ")
    elseIf id_option == p_option_books_o
        p_Open(CONSTS.CATEGORY_BOOKS_O, " Books O ")
    elseIf id_option == p_option_books_p
        p_Open(CONSTS.CATEGORY_BOOKS_P, " Books P ")
    elseIf id_option == p_option_books_q
        p_Open(CONSTS.CATEGORY_BOOKS_Q, " Books Q ")
    elseIf id_option == p_option_books_r
        p_Open(CONSTS.CATEGORY_BOOKS_R, " Books R ")
    elseIf id_option == p_option_books_s
        p_Open(CONSTS.CATEGORY_BOOKS_S, " Books S ")
    elseIf id_option == p_option_books_t
        p_Open(CONSTS.CATEGORY_BOOKS_T, " Books T ")
    elseIf id_option == p_option_books_u
        p_Open(CONSTS.CATEGORY_BOOKS_U, " Books U ")
    elseIf id_option == p_option_books_v
        p_Open(CONSTS.CATEGORY_BOOKS_V, " Books V ")
    elseIf id_option == p_option_books_w
        p_Open(CONSTS.CATEGORY_BOOKS_W, " Books W ")
    elseIf id_option == p_option_books_x
        p_Open(CONSTS.CATEGORY_BOOKS_X, " Books X ")
    elseIf id_option == p_option_books_y
        p_Open(CONSTS.CATEGORY_BOOKS_Y, " Books Y ")
    elseIf id_option == p_option_books_z
        p_Open(CONSTS.CATEGORY_BOOKS_Z, " Books Z ")
    elseIf id_option == p_option_books
        p_Open(CONSTS.CATEGORY_BOOKS, " Books # ")

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
endFunction

function f_On_Option_Slider_Open(int id_option)
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Default(int id_option)
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

; Private Methods
function p_Open(ObjectReference ref_container, string str_name)
    FUNCS.Close_Menus()
    CONTAINERS.Set_Name(ref_container, str_name)
    CONTAINERS.Open(ref_container)
endFunction
