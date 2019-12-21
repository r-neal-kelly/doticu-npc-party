# STYLE
An overview of the several patterns, naming conventions, and symbols that are used to signify and encapsulate meaning across the program, creating a consistency that is to be desired for reading comprehension.

---

## Naming Conventions
- Vanilla intrinsic types and keywords are always in lower camelCase:

        string
        int
        bool
        autoReadOnly
        endIf

- Refined vanilla types are always in captial CamelCase:

        ReferenceAlias
        MiscObject
        Actor

- Custom types created by this program are all in lower snake_case:

        doticu_npcp_actors
        doticu_npcp_member
        doticu_npcp_follower

        ; each type's name has "doticu_npcp_"
        ; because all types are stored in the same folder
        ; on disc, and should never conflict with anything

- For all other custom values created by this program, including functions, constants, variables, and more, underscores are to be used in a variety of ways:

        bool IS_FOLLOWER
        function Create_Follower
        state STATE_FOLLOWER
        int idx_arr_followers

- Constant labels have all capitals and no lower case letters, with the exception of symbols at the front of the label, e.g. `p_` or `f_`.

        int property MAX_MEMBERS auto
        int p_MAX_ALIASES

- Variable labels are in lower case only, no capitals in any way.

        string str_info
        int p_id_alias
        
- Function and method labels have every letter capitalized, except for symbols and occasionally, acronyms:

        function Create_Member()
        function f_Create()
        function p_Create_Member_ID()

- State labels are like constant labels, in that they are in all caps, but they also have the important addition of the word "STATE" prefacing the rest of the label.

        state STATE_DEFAULT
        state p_STATE_EXCEPTION

- Generally, labels are to be named in such as a way as to designate a tree structure, like a file system, in the context of other labels around it. It is usually the case that the *type* of the value is listed before anything else, but not always so when there are space limitations. The following is a good example that encompasses the file structure like grammar:

        string str_style_member_prev
        string str_style_member_next
        string str_style_member_curr

        string str_style_follower_prev
        string str_style_follower_next
        string str_style_follower_curr

        ; "str" indicates a value of type string
        ; "style" is what really defines the value, the thing we are handling
        ; "member" is distinct from "follower", but they both refine "style"
        ; "prev" and "next" further refine "style"

- Some "*types*" are synonomous with others, but in a common-sensical way, e.g. `key` is almost, if not always an `int`.

        ; int key_member_clone
        ; int code_style_warrior
        ; int id_follower
        ; int idx_arr_members

- Booleans should always be named in such a way that the label implies the fact that they are booleans:

        ; bool is_clone
        ; bool isnt_clone
        ; bool has_clone
        ; bool hasnt_clone
        ; bool can_clone
        ; bool cant_clone
        ; bool do_clone
        ; bool dont_clone

---

## Symbols

### `p_`
Only ever means "private," as in a private variable or method (that is, function.) Although Papyrus doesn't support private functions, this sign is there to stop a programmer from making the mistake of using it outside of the file that it's defined within. By convention, this sign is used even on variables that aren't accessible from without the file, to remind the user as much. This symobl is always to be lower case.

### `f_`
Only ever means "friend," as in a friend method (that is, function.) Papyrus doesn't support friend functions in the traditional sense, but this sign is there to stop a programmer from using a function that they aren't sure they should be using. It's distinct from "p_" because this kind of function needs to be called from without the file that it's defined within. This symbol is always to be lower case.

### `id_`
Only ever means "id" or "identification," as in the id of a follower.

### `idx_`
Only ever means "index," as in the index of an array.

### `arr_`
Only ever refers to an "array," and nothing else.

### `str_`
Only ever refers to an "string," and nothing else.

---

## The Structure of a File
A single comment line is used to delimit sections of a file. The comment line is only required when the section has use in the file. They should generally appear in the following order:

        ; Private Constants
        ; Private Variables

        ; Public Constants
        ; Public Variables

        ; Friend Methods
        ; Private Methods
        ; Public Methods

        ; Private States
        ; Public States

        ; Events
