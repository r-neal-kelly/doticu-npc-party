/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusEvents.h"

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "funcs.h"
#include "keys.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "string2.h"
#include "vars.h"

#include "party/party_alias.h"
#include "party/party_alias.inl"
#include "party/party_movee.h"
#include "party/party_members.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Movee_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_movee");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Movee_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Movee_t* Movee_t::Self()
    {
        return reinterpret_cast<Movee_t*>(*(Consts::Funcs_Quest()->aliases.entries + 2));
    }

    Object_t* Movee_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Movee_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Movee_t::Actor_Variable() { DEFINE_VARIABLE("p_ref_actor"); }

    Variable_t* Movee_t::Is_Created_Variable() { DEFINE_VARIABLE("p_is_created"); }
    Variable_t* Movee_t::Is_Locked_Variable() { DEFINE_VARIABLE("p_is_locked"); }
    Variable_t* Movee_t::Is_Airborne_Variable() { DEFINE_VARIABLE("p_is_airborne"); }
    Variable_t* Movee_t::Do_Distance_Farther_Variable() { DEFINE_VARIABLE("p_do_distance_farther"); }
    Variable_t* Movee_t::Do_Distance_Nearer_Variable() { DEFINE_VARIABLE("p_do_distance_nearer"); }
    Variable_t* Movee_t::Do_Rotate_Right_Variable() { DEFINE_VARIABLE("p_do_rotate_right"); }
    Variable_t* Movee_t::Do_Rotate_Left_Variable() { DEFINE_VARIABLE("p_do_rotate_left"); }

    Variable_t* Movee_t::Distance_Variable() { DEFINE_VARIABLE("p_distance"); }
    Variable_t* Movee_t::Rotation_Variable() { DEFINE_VARIABLE("p_rotation"); }

    Actor_t* Movee_t::Actor()
    {
        return Actor_Variable()->Actor();
    }

    Bool_t Movee_t::Is_Created()
    {
        return Is_Created_Variable()->Bool();
    }

    Bool_t Movee_t::Is_Locked()
    {
        return Is_Locked_Variable()->Bool();
    }

    Bool_t Movee_t::Is_Airborne()
    {
        return Is_Airborne_Variable()->Bool();
    }

    Bool_t Movee_t::Do_Distance_Farther()
    {
        return Do_Distance_Farther_Variable()->Bool();
    }
    
    Bool_t Movee_t::Do_Distance_Nearer()
    {
        return Do_Distance_Nearer_Variable()->Bool();
    }

    Bool_t Movee_t::Do_Rotate_Right()
    {
        return Do_Rotate_Right_Variable()->Bool();
    }
    
    Bool_t Movee_t::Do_Rotate_Left()
    {
        return Do_Rotate_Left_Variable()->Bool();
    }

    Float_t Movee_t::Distance()
    {
        return Distance_Variable()->Float();
    }

    Float_t Movee_t::Rotation()
    {
        return Rotation_Variable()->Float();
    }

    void Movee_t::Actor(Actor_t* actor)
    {
        if (actor) {
            Actor_Variable()->Pack(actor);
        } else {
            Actor_Variable()->None(Class_Info_t::Fetch(Actor_t::kTypeID, true));
        }
    }

    void Movee_t::Is_Created(Bool_t value)
    {
        Is_Created_Variable()->Bool(value);
    }

    void Movee_t::Is_Locked(Bool_t value)
    {
        Is_Locked_Variable()->Bool(value);
    }

    void Movee_t::Is_Airborne(Bool_t value)
    {
        Is_Airborne_Variable()->Bool(value);
    }

    void Movee_t::Do_Distance_Farther(Bool_t value)
    {
        Do_Distance_Farther_Variable()->Bool(value);
    }

    void Movee_t::Do_Distance_Nearer(Bool_t value)
    {
        Do_Distance_Nearer_Variable()->Bool(value);
    }

    void Movee_t::Do_Rotate_Right(Bool_t value)
    {
        Do_Rotate_Right_Variable()->Bool(value);
    }

    void Movee_t::Do_Rotate_Left(Bool_t value)
    {
        Do_Rotate_Left_Variable()->Bool(value);
    }

    void Movee_t::Distance(Float_t distance)
    {
        Distance_Variable()->Float(distance);
    }

    void Movee_t::Rotation(Float_t rotation)
    {
        Rotation_Variable()->Float(rotation);
    }

    void Movee_t::Lock(Callback_t<Movee_t*>* on_lock, Float_t interval, Float_t limit)
    {
        Alias_t::Lock(this, on_lock, interval, limit);
    }

    void Movee_t::Unlock()
    {
        Alias_t::Unlock(this);
    }

    Int_t Movee_t::Start(Actor_t* actor)
    {
        if (Is_Unfilled()) {
            if (actor) {
                Member_t* member = Members_t::Self()->From_Actor(actor);
                if (member) {
                    if (member->Is_Mannequin()) {
                        return CODES::MANNEQUIN;
                    } else if (member->Is_Display()) {
                        return CODES::DISPLAY;
                    }
                }

                struct Lock_t : public Callback_t<Movee_t*> {
                    Actor_t* actor;
                    Lock_t(Actor_t* actor) :
                        actor(actor)
                    {
                    }
                    void operator()(Movee_t* self)
                    {
                        struct Unlock_t : public Callback_t<> {
                            Movee_t* self;
                            Unlock_t(Movee_t* self) :
                                self(self)
                            {
                            }
                            void operator()()
                            {
                                self->Unlock();
                            }
                        };
                        self->Start_Impl(actor, new Unlock_t(self));
                    }
                };
                Lock(new Lock_t(actor));

                return CODES::SUCCESS;
            } else {
                return CODES::ACTOR;
            }
        } else {
            return CODES::MOVEE;
        }
    }

    void Movee_t::Start_Impl(Actor_t* actor, Callback_t<>* user_callback)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<>;

        Actor(actor);

        Is_Created(true);
        Is_Locked(false);
        Is_Airborne(false);
        Do_Distance_Farther(false);
        Do_Distance_Nearer(false);
        Do_Rotate_Left(false);
        Do_Rotate_Right(false);

        Distance(DEF_DISTANCE);
        Rotation(Utils::To_Degrees(actor->rot.z));

        Register();

        struct VCallback : public Virtual_Callback_t {
            Movee_t* self;
            UCallback_t* user_callback;
            VCallback(Movee_t* self, UCallback_t* user_callback) :
                self(self), user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                Actor_t* actor = self->Actor();
                if (actor) {
                    Object_Ref::Token(actor, Consts::Movee_Token());
                    Actor2::Evaluate_Package(actor);
                    Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
                    value_owner->Set_Actor_Value(Actor_Value_t::PARALYSIS, 1.0f);
                    self->Update();
                }
                user_callback->operator()();
                delete user_callback;
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this, user_callback);
        Alias_t::Fill(actor, &vcallback);
    }

    Int_t Movee_t::Stop()
    {
        if (Is_Filled()) {
            Is_Created(false);

            struct Lock_t : public Callback_t<Movee_t*> {
                void operator()(Movee_t* self)
                {
                    struct Unlock_t : public Callback_t<> {
                        Movee_t* self;
                        Unlock_t(Movee_t* self) :
                            self(self)
                        {
                        }
                        void operator()()
                        {
                            self->Unlock();
                        }
                    };
                    self->Stop_Impl(new Unlock_t(self));
                }
            };
            Lock(new Lock_t());

            return CODES::SUCCESS;
        } else {
            return CODES::MOVEE;
        }
    }

    void Movee_t::Stop_Impl(Callback_t<>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<>;

        Actor_t* actor = Actor();
        if (actor) {
            if (!Actor2::Is_Loaded(actor)) {
                Reload();
            }

            Object_Ref::Stop_Translation(actor);
            if (Is_Airborne()) {
                Object_Ref::Push_Actor_Away(actor, actor, 0.0f);
            } else {
                Object_Ref::Apply_Havok_Impulse(actor, 0.0f, 0.0f, 0.001f, 0.001f);
            }

            Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
            value_owner->Set_Actor_Value(Actor_Value_t::PARALYSIS, 0.0f);

            Object_Ref::Untoken(actor, Consts::Movee_Token());
        }

        Unregister();
        
        struct VCallback : public Virtual_Callback_t {
            Movee_t* self;
            UCallback_t* user_callback;
            VCallback(Movee_t* self, UCallback_t* user_callback) :
                self(self), user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                Actor_t* actor = self->Actor();
                if (actor) {
                    Actor2::Evaluate_Package(actor);

                    self->Rotation(0.0f);
                    self->Distance(0.0f);

                    self->Do_Rotate_Right(false);
                    self->Do_Rotate_Left(false);
                    self->Do_Distance_Nearer(false);
                    self->Do_Distance_Farther(false);
                    self->Is_Airborne(false);
                    self->Is_Locked(false);
                    self->Is_Created(false);

                    self->Actor(nullptr);
                }
                user_callback->operator()();
                delete user_callback;
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this, user_callback);
        Alias_t::Unfill(&vcallback);
    }

    void Movee_t::Register()
    {
        Unregister();

        auto Try_To_Register = [&](UInt32 hotkey_value)->void
        {
            if (hotkey_value > Keys_t::KEY_INVALID) {
                g_inputKeyEventRegs.Register(hotkey_value, Alias_t::kTypeID, this);
            }
        };

        if (Is_Created()) {
            Try_To_Register(Vars::N_Move_Farther_Value());
            Try_To_Register(Vars::N_Move_Nearer_Value());
            Try_To_Register(Vars::N_Move_Rotate_Left_Value());
            Try_To_Register(Vars::N_Move_Rotate_Right_Value());
        }
    }

    void Movee_t::Unregister()
    {
        g_inputKeyEventRegs.UnregisterAll(Alias_t::kTypeID, this);
    }

    void Movee_t::Update()
    {
        struct Lock_t : public Callback_t<Movee_t*> {
            void operator()(Movee_t* self)
            {
                struct Unlock_t : public Callback_t<> {
                    Movee_t* self;
                    Unlock_t(Movee_t* self) :
                        self(self)
                    {
                    }
                    void operator()()
                    {
                        self->Unlock();
                    }
                };
                self->Update_Impl(new Unlock_t(self));
            }
        };
        Lock(new Lock_t());
    }

    void Movee_t::Update_Impl(Callback_t<>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<>;

        Actor_t* actor = Actor();
        if (Is_Created() && actor) {
            if (Actor2::Is_Loaded(actor)) {
                Move();
            } else {
                Reload();
            }
            struct VCallback : public Virtual_Callback_t {
                Movee_t* self;
                UCallback_t* user_callback;
                VCallback(Movee_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    self->Update_Impl(user_callback);
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this, user_callback);
            Modules::Funcs_t::Self()->Wait_Out_Of_Menu(UPDATE_INTERVAL, &vcallback);
        } else {
            user_callback->operator()();
            delete user_callback;
        }
    }

    void Movee_t::Move()
    {
        Actor_t* actor = Actor();
        if (actor) {
            Float_t distance = Distance();
            if (Do_Distance_Farther() && !Do_Distance_Nearer()) {
                distance += DISTANCE_INTERVAL;
                if (distance > MAX_DISTANCE) {
                    distance = MAX_DISTANCE;
                }
            } else if (Do_Distance_Nearer() && !Do_Distance_Farther()) {
                distance -= DISTANCE_INTERVAL;
                if (distance < MIN_DISTANCE) {
                    distance = MIN_DISTANCE;
                }
            }
            Distance(distance);

            Float_t rotation = Rotation();
            if (Do_Rotate_Left() && !Do_Rotate_Right()) {
                rotation += ROTATION_INTERVAL;
                if (rotation > MAX_ROTATION) {
                    rotation = MIN_ROTATION;
                }
            } else if (Do_Rotate_Right() && !Do_Rotate_Left()) {
                rotation -= ROTATION_INTERVAL;
                if (rotation < MIN_ROTATION) {
                    rotation = MAX_ROTATION;
                }
            }
            Rotation(rotation);

            Actor_t* player = Consts::Player_Actor();
            Float_t pos_x;
            Float_t pos_y;
            Float_t pos_z;
            if (player->rot.x < Utils::To_Radians(0.0f) && player->rot.x > Utils::To_Radians(-91.0f)) {
                Is_Airborne(true);

                Float_t cos_x = cos(player->rot.x);
                pos_x = player->pos.x + distance * sin(player->rot.z) * cos_x;
                pos_y = player->pos.y + distance * cos(player->rot.z) * cos_x;
                pos_z = player->pos.z + distance * abs(sin(player->rot.x));
            } else {
                Is_Airborne(false);

                pos_x = player->pos.x + distance * sin(player->rot.z);
                pos_y = player->pos.y + distance * cos(player->rot.z);
                pos_z = player->pos.z;
            }

            if (Actor2::Is_Loaded(actor)) {
                Object_Ref::Translate_To(actor, pos_x, pos_y, pos_z, 0.0f, 0.0f, rotation, SPEED + distance, SPEED);
            }
        }
    }

    void Movee_t::Reload()
    {
        Actor_t* actor = Actor();
        if (actor) {
            Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
            value_owner->Set_Actor_Value(Actor_Value_t::PARALYSIS, 0.0f);
            Actor2::Move_To_Orbit(actor, Consts::Player_Actor(), DEF_DISTANCE, 0.0f);
        }
    }

    void Movee_t::On_Load_Mod()
    {
        if (Is_Created()) {
            Actor_t* actor = Actor();
            if (actor) {
                Reload();
                Update();
            }
        }
    }

    void Movee_t::On_Cell_Change(Cell_t* new_cell, Cell_t* old_cell)
    {
        if (Actor()) {
            Reload();
        }
    }

    void Movee_t::On_Key_Down(Int_t key_code)
    {
        struct Callback : public Virtual_Callback_t {
            Movee_t* self;
            Int_t key_code;
            Callback(Movee_t* self, Int_t key_code) :
                self(self), key_code(key_code)
            {
            }
            void operator()(Variable_t* result)
            {
                if (result && result->Bool()) {
                    if (key_code == Vars::N_Move_Farther_Value()) {
                        self->Do_Distance_Farther(true);
                    } else if (key_code == Vars::N_Move_Nearer_Value()) {
                        self->Do_Distance_Nearer(true);
                    } else if (key_code == Vars::N_Move_Rotate_Left_Value()) {
                        self->Do_Rotate_Left(true);
                    } else if (key_code == Vars::N_Move_Rotate_Right_Value()) {
                        self->Do_Rotate_Right(true);
                    }
                }
            }
        };
        Virtual_Callback_i* callback = new Callback(this, key_code);
        Object_Ref::Can_Use_Keys(&callback);
    }

    void Movee_t::On_Key_Up(Int_t key_code, Float_t time_held)
    {
        struct Callback : public Virtual_Callback_t {
            Movee_t* self;
            Int_t key_code;
            Callback(Movee_t* self, Int_t key_code) :
                self(self), key_code(key_code)
            {
            }
            void operator()(Variable_t* result)
            {
                if (result && result->Bool()) {
                    String_t pressed_hotkey = Keys_t::Self()->Pressed_Hotkey(key_code);
                    if (String2::Is_Same_Caseless(pressed_hotkey, Keys_t::N_Move_Farther())) {
                        self->Do_Distance_Farther(false);
                    } else if (String2::Is_Same_Caseless(pressed_hotkey, Keys_t::N_Move_Nearer())) {
                        self->Do_Distance_Nearer(false);
                    } else if (String2::Is_Same_Caseless(pressed_hotkey, Keys_t::N_Move_Rotate_Left())) {
                        self->Do_Rotate_Left(false);
                    } else if (String2::Is_Same_Caseless(pressed_hotkey, Keys_t::N_Move_Rotate_Right())) {
                        self->Do_Rotate_Right(false);
                    }
                }
            }
        };
        Virtual_Callback_i* callback = new Callback(this, key_code);
        Object_Ref::Can_Use_Keys(&callback);
    }

    void Movee_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Movee_t,               \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("Register", 0, void, Register);
        METHOD("Unregister", 0, void, Unregister);
        METHOD("OnKeyDown", 1, void, On_Key_Down, Int_t);
        METHOD("OnKeyUp", 2, void, On_Key_Up, Int_t, Float_t);

        #undef METHOD
    }

}}}
