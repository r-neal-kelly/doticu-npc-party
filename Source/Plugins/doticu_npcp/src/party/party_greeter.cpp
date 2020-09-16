/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "funcs.h"
#include "object_ref.h"
#include "papyrus.inl"

#include "party/party_alias.inl"
#include "party/party_greeter.h"
#include "party/party_members.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Greeter_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_greeter");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Greeter_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Greeter_t* Greeter_t::Self()
    {
        return reinterpret_cast<Greeter_t*>(*(Consts::Funcs_Quest()->aliases.entries + 1));
    }

    Object_t* Greeter_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Greeter_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Greeter_t::Is_Locked_Variable() { DEFINE_VARIABLE("p_is_locked"); }
    Variable_t* Greeter_t::Actor_Variable() { DEFINE_VARIABLE("p_ref_actor"); }
    Variable_t* Greeter_t::Time_Waited_Variable() { DEFINE_VARIABLE("p_time_waited"); }

    void Greeter_t::Lock(Callback_t<Greeter_t*>* on_lock, Float_t interval, Float_t limit)
    {
        Alias_t::Lock(this, on_lock, interval, limit);
    }

    void Greeter_t::Unlock()
    {
        Alias_t::Unlock(this);
    }

    void Greeter_t::Start(Actor_t* actor, Callback_t<Int_t, Greeter_t*>* user_callback)
    {
        using UCallback_t = Callback_t<Int_t, Greeter_t*>;

        struct Lock_t : public Callback_t<Greeter_t*> {
            Actor_t* actor;
            UCallback_t* user_callback;
            Lock_t(Actor_t* actor, UCallback_t* user_callback) :
                actor(actor), user_callback(user_callback)
            {
            }
            void operator()(Greeter_t* self)
            {
                struct Unlock_t : public UCallback_t {
                    Greeter_t* self;
                    UCallback_t* user_callback;
                    Unlock_t(Greeter_t* self, UCallback_t* user_callback) :
                        self(self), user_callback(user_callback)
                    {
                    }
                    void operator()(Int_t code, Greeter_t* greeter)
                    {
                        if (user_callback) {
                            user_callback->operator()(code, greeter);
                            delete user_callback;
                        }
                        self->Unlock();
                    }
                };
                self->Start_Impl(actor, new Unlock_t(self, user_callback));
            }
        };
        Lock(new Lock_t(actor, user_callback));
    }

    void Greeter_t::Start_Impl(Actor_t* actor, Callback_t<Int_t, Greeter_t*>* user_callback)
    {
        using UCallback_t = Callback_t<Int_t, Greeter_t*>;
        NPCP_ASSERT(user_callback);

        if (actor) {
            if (Actor2::Is_Alive(actor)) {
                Member_t* member = Members_t::Self()->From_Actor(actor);
                if (member && member->Is_Mannequin()) {
                    user_callback->operator()(CODES::MANNEQUIN, nullptr);
                    delete user_callback;
                } else if (member && member->Is_Display()) {
                    user_callback->operator()(CODES::DISPLAY, nullptr);
                    delete user_callback;
                } else {
                    struct VCallback : public Virtual_Callback_t {
                        Greeter_t* self;
                        Actor_t* actor;
                        UCallback_t* user_callback;
                        VCallback(Greeter_t* self, Actor_t* actor, UCallback_t* user_callback) :
                            self(self), actor(actor), user_callback(user_callback)
                        {
                        }
                        void operator()(Variable_t* result)
                        {
                            self->Actor_Variable()->Pack(actor);
                            self->Time_Waited_Variable()->Float(0.0f);

                            Object_Ref::Token(actor, Consts::Greeter_Token());
                            Actor2::Pacify(actor);
                            Actor2::Evaluate_Package(actor);

                            self->Update();

                            user_callback->operator()(CODES::SUCCESS, self);
                            delete user_callback;
                        }
                    };
                    Virtual_Callback_i* vcallback = new VCallback(this, actor, user_callback);
                    Alias_t::Fill(actor, &vcallback);
                }
            } else {
                user_callback->operator()(CODES::DEAD, nullptr);
                delete user_callback;
            }
        } else {
            user_callback->operator()(CODES::ACTOR, nullptr);
            delete user_callback;
        }
    }

    void Greeter_t::Stop(Callback_t<Int_t, Actor_t*>* user_callback)
    {
        using UCallback_t = Callback_t<Int_t, Actor_t*>;

        struct Lock_t : public Callback_t<Greeter_t*> {
            UCallback_t* user_callback;
            Lock_t(UCallback_t* user_callback) :
                user_callback(user_callback)
            {
            }
            void operator()(Greeter_t* self)
            {
                struct Unlock_t : public UCallback_t {
                    Greeter_t* self;
                    UCallback_t* user_callback;
                    Unlock_t(Greeter_t* self, UCallback_t* user_callback) :
                        self(self), user_callback(user_callback)
                    {
                    }
                    void operator()(Int_t code, Actor_t* actor)
                    {
                        if (user_callback) {
                            user_callback->operator()(code, actor);
                            delete user_callback;
                        }
                        self->Unlock();
                    }
                };
                self->Stop_Impl(new Unlock_t(self, user_callback));
            }
        };
        Lock(new Lock_t(user_callback));
    }

    void Greeter_t::Stop_Impl(Callback_t<Int_t, Actor_t*>* user_callback)
    {
        using UCallback_t = Callback_t<Int_t, Actor_t*>;
        NPCP_ASSERT(user_callback);

        if (Is_Filled()) {
            struct VCallback : public Virtual_Callback_t {
                Greeter_t* self;
                UCallback_t* user_callback;
                VCallback(Greeter_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    Actor_t* actor = self->Actor_Variable()->Actor();
                    Object_Ref::Untoken(actor, Consts::Greeter_Token());
                    Actor2::Pacify(actor);
                    Actor2::Evaluate_Package(actor);

                    self->Time_Waited_Variable()->Float(0.0f);
                    self->Actor_Variable()->None(Class_Info_t::Fetch(Actor_t::kTypeID, true));

                    user_callback->operator()(CODES::SUCCESS, actor);
                    delete user_callback;
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this, user_callback);
            Alias_t::Unfill(&vcallback);
        } else {
            user_callback->operator()(CODES::GREETER, nullptr);
            delete user_callback;
        }
    }

    void Greeter_t::Update()
    {
        struct Lock_t : public Callback_t<Greeter_t*> {
            void operator()(Greeter_t* self)
            {
                struct Unlock_t : public Callback_t<Greeter_t*> {
                    void operator()(Greeter_t* self)
                    {
                        self->Unlock();
                    }
                };
                self->Update_Impl(new Unlock_t());
            }
        };
        Lock(new Lock_t());
    }

    void Greeter_t::Update_Impl(Callback_t<Greeter_t*>* user_callback)
    {
        using UCallback_t = Callback_t<Greeter_t*>;
        NPCP_ASSERT(user_callback);

        if (Is_Filled()) {
            struct VCallback : public Virtual_Callback_t {
                Greeter_t* self;
                UCallback_t* user_callback;
                VCallback(Greeter_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (result && result->Bool()) {
                        self->Stop();
                    } else {
                        Float_t time_waited = self->Time_Waited_Variable()->Float();
                        if (time_waited >= MAX_WAIT_TIME) {
                            self->Stop();
                        } else {
                            self->Time_Waited_Variable()->Float(time_waited + UPDATE_INTERVAL);
                            struct VCallback : public Virtual_Callback_t {
                                Greeter_t* self;
                                VCallback(Greeter_t* self) :
                                    self(self)
                                {
                                }
                                void operator()(Variable_t* result)
                                {
                                    self->Update();
                                }
                            };
                            Virtual_Callback_i* vcallback = new VCallback(self);
                            Modules::Funcs_t::Self()->Wait_Out_Of_Menu(UPDATE_INTERVAL, &vcallback);
                        }
                    }
                    user_callback->operator()(self);
                    delete user_callback;
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this, user_callback);
            Actor2::Is_Talking_To_Player(Actor_Variable()->Actor(), &vcallback);
        } else {
            user_callback->operator()(this);
            delete user_callback;
        }
    }

    void Greeter_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Greeter_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
