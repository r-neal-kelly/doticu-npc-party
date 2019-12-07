Scriptname doticu_npc_party_script_codes extends Quest

; Public Constants
int property SUCCESS                =    0 autoReadOnly
int property FAILURE                =   -1 autoReadOnly
int property STARTED                =  -10 autoReadOnly
int property STOPPED                =  -20 autoReadOnly
int property CREATED                =  -30 autoReadOnly
int property DESTROYED              =  -40 autoReadOnly

int property HAS_SPACE              = -100 autoReadOnly
int property HAS_ACTOR              = -110 autoReadOnly
int property HAS_ALIAS              = -120 autoReadOnly
int property HAS_MEMBER             = -130 autoReadOnly
int property HAS_SETTLER            = -140 autoReadOnly
int property HAS_IMMOBILE           = -150 autoReadOnly
int property HAS_FOLLOWER           = -160 autoReadOnly
int property HAS_SNEAK              = -170 autoReadOnly

int property HASNT_SPACE            = -200 autoReadOnly
int property HASNT_SPACE_MEMBER     = -201 autoReadOnly
int property HASNT_SPACE_FOLLOWER   = -202 autoReadOnly
int property HASNT_ACTOR            = -210 autoReadOnly
int property HASNT_ALIAS            = -220 autoReadOnly
int property HASNT_MEMBER           = -230 autoReadOnly
int property HASNT_SETTLER          = -240 autoReadOnly
int property HASNT_IMMOBILE         = -250 autoReadOnly
int property HASNT_FOLLOWER         = -260 autoReadOnly
int property HASNT_SNEAK            = -270 autoReadOnly

int property IS_ACTOR               = -300 autoReadOnly
int property IS_ALIAS               = -310 autoReadOnly
int property IS_MEMBER              = -320 autoReadOnly
int property IS_SETTLER             = -330 autoReadOnly
int property IS_IMMOBILE            = -340 autoReadOnly
int property IS_FOLLOWER            = -350 autoReadOnly
int property IS_SNEAK               = -360 autoReadOnly
int property IS_THRALL              = -370 autoReadOnly

int property ISNT_ACTOR             = -400 autoReadOnly
int property ISNT_ALIAS             = -410 autoReadOnly
int property ISNT_MEMBER            = -420 autoReadOnly
int property ISNT_SETTLER           = -430 autoReadOnly
int property ISNT_IMMOBILE          = -440 autoReadOnly
int property ISNT_FOLLOWER          = -450 autoReadOnly
int property ISNT_SNEAK             = -460 autoReadOnly
int property ISNT_THRALL            = -470 autoReadOnly

int property CAN_RESURRECT          = -500 autoReadOnly

int property CANT_RESURRECT         = -600 autoReadOnly
