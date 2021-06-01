; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_party_settler_slots extends Quest

int[]               types               = none; determines how to interpret the data, and which data is used
int[]               flags               = none; keep the is_enabled flag, so we can simply turn it off without deleting?

ObjectReference[]   markers             = none
int[]               radii               = none

int[]               times               = none
int[]               durations           = none
int[]               speeds              = none

int[]               attentions          = none
int[]               wander_distances    = none

ObjectReference[]   interactables       = none; bed for sleeper, chair for sitter, etc.
