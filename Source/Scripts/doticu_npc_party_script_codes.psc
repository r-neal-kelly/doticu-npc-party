Scriptname doticu_npc_party_script_codes extends Quest

; Codes
int property SUCCESS        =    0 autoReadOnly
int property FAILURE        =   -1 autoReadOnly
int property EXISTS         =   -5 autoReadOnly
int property STARTED        =  -10 autoReadOnly
int property STOPPED        =  -20 autoReadOnly
int property CREATED        =  -30 autoReadOnly
int property DESTROYED      =  -40 autoReadOnly
int property BAD_PARAM      =  -50 autoReadOnly
int property IS_DUPLICATE   =  -60 autoReadOnly; pretty much the same as EXISTS.
int property OUT_OF_BOUNDS  =  -70 autoReadOnly
int property OUT_OF_SPACE   =  -80 autoReadOnly
int property FATAL_ERROR    = -600 autoReadOnly

int property NO_ACTOR       = -100 autoReadOnly
int property NO_ALIAS       = -110 autoReadOnly
int property NO_MEMBER      = -120 autoReadOnly
int property NO_SETTLER     = -130 autoReadOnly
int property NO_IMMOBILE    = -140 autoReadOnly
int property NO_FOLLOWER    = -150 autoReadOnly
int property NO_SNEAK       = -160 autoReadOnly
int property NO_RESURRECT   = -170 autoReadOnly
