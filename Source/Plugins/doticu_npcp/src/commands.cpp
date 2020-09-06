/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "commands.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_movee.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_mannequins.h"
#include "party/party_followers.h"
#include "party/party_follower.h"

namespace doticu_npcp { namespace Modules { namespace Control {

    String_t Commands_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_commands");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Commands_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Commands_t* Commands_t::Self()
    {
        return static_cast<Commands_t*>(Consts::Control_Quest());
    }

    Object_t* Commands_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Commands_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    void Commands_t::Log_Note(const char* note, Bool_t do_log)
    {
        class Arguments : public Virtual_Arguments_t {
        public:
            String_t note;
            Bool_t do_log;
            Arguments(String_t note, Bool_t do_log) :
                note(note), do_log(do_log)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->String(note);
                arguments->At(1)->Bool(do_log);
                return true;
            }
        } arguments(note, do_log);

        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(), "doticu_npcp_logs", "Create_Note", &arguments);
    }

    void Commands_t::Log_Note(const char* part_1, const char* part_2, Bool_t do_log)
    {
        return Log_Note((std::string(part_1) + part_2).c_str(), do_log);
    }

    void Commands_t::Log_Note(const char* part_1, const char* part_2, const char* part_3, Bool_t do_log)
    {
        return Log_Note((std::string(part_1) + part_2 + part_3).c_str(), do_log);
    }

    void Commands_t::Log_Note(const char* part_1, const char* part_2, const char* part_3, const char* part_4, Bool_t do_log)
    {
        return Log_Note((std::string(part_1) + part_2 + part_3 + part_4).c_str(), do_log);
    }

    void Commands_t::Log_Error(const char* error, Int_t code, Bool_t do_log)
    {
        class Arguments : public Virtual_Arguments_t {
        public:
            String_t error;
            Bool_t do_log;
            Arguments(String_t error, Bool_t do_log) :
                error(error), do_log(do_log)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->String(error);
                arguments->At(1)->Bool(do_log);
                return true;
            }
        } arguments((std::string(error) + ": " + std::to_string(code)).c_str(), do_log);

        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(), "doticu_npcp_logs", "Create_Error", &arguments);
    }

    void Commands_t::Log_Error(const char* part_1, const char* part_2, Int_t code, Bool_t do_log)
    {
        return Log_Error((std::string(part_1) + part_2).c_str(), code, do_log);
    }

    // NPC

    void Commands_t::Log_Member(Int_t code, const char* name)
    {
        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is now a member.");
            case (CODES::ACTOR):
                return Log_Note("That can't become a member.");
            case (CODES::MEMBER):
                return Log_Note(name, " is already a member.");
            case (CODES::MEMBERS):
                return Log_Note("No room for ", name, " to become a member.");
            case (CODES::CHILD):
                return Log_Note("A child cannot become a member.");
            case (CODES::DEAD):
                return Log_Note(name, " can't be revived, and so can't become a member.");
            case (CODES::CLONE):
                return Log_Note(name, " could not be cloned. Try to manually member them.");
            default:
                return Log_Error(name, " could not become a member", code);
        };
    }

    void Commands_t::Log_Follow(Int_t code, const char* name)
    {
        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will start following.");
            case (CODES::FOLLOWERS):
                return Log_Note("No room for ", name, " to become a follower.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't start following.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " is already following.");
            case (CODES::MANNEQUIN):
                return Log_Note(name, " is a mannequin and cannot follow.");
            case (CODES::ACTOR):
                return Log_Note("That can't become a follower.");
            default:
                return Log_Error(name, " can't start following", code);
        };
    }

    void Commands_t::Log_Unfollow(Int_t code, const char* name)
    {
        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will stop following.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't stop following.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " wasn't following.");
            case (CODES::ACTOR):
                return Log_Note("That is not a follower.");
            default:
                return Log_Error(name, " can't stop following", code);
        };
    }

    void Commands_t::Log_Saddle(Int_t code, const char* name)
    {
        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has saddled up.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " isn't a follower, and so can't saddle up.");
            case (CODES::IS):
                return Log_Note(name, " is already saddled up.");
            case (CODES::INTERIOR):
                return Log_Note(name, " cannot saddle up in an interior space.");
            default:
                return Log_Error(name, " can't saddle up", code);
        };
    }

    void Commands_t::Log_Unsaddle(Int_t code, const char* name)
    {
        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has unsaddled.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " isn't a follower, and so can't unsaddle.");
            case (CODES::IS):
                return Log_Note(name, " is not saddled.");
            default:
                return Log_Error(name, " can't unsaddle", code);
        };
    }

    void Commands_t::Member(Actor_t* actor)
    {
        using namespace Party;

        class Add_Callback : public Members_t::Add_Callback_i {
        public:
            Commands_t* commands;
            const char* name;
            Add_Callback(Commands_t* commands, const char* name) :
                commands(commands), name(name)
            {
            }
            virtual void operator()(Int_t code, Member_t* member) override
            {
                commands->Log_Member(code, name);
            }
        };
        Members_t::Add_Callback_i* add_callback = new Add_Callback(this, Actor2::Get_Name(actor));
        Members_t::Self()->Add_Original(actor, &add_callback);
    }

    void Commands_t::Unmember(Actor_t* actor)
    {
        const char* name = Actor2::Get_Name(actor);
        Int_t code = Party::Members_t::Self()->Remove_Original(actor);

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is no longer a member.");
            case (CODES::ACTOR):
                return Log_Note("That is not a member.");
            case (CODES::MEMBER):
                return Log_Note(name, " isnt a member.");
            case (CODES::CLONE):
                return Log_Note(name, " isnt a clone.");
            default:
                return Log_Error(name, " could not be unmembered", code);
        };
    }

    void Commands_t::Clone(Actor_t* actor)
    {
        using namespace Party;

        struct Add_Callback : public Members_t::Add_Callback_i {
            Commands_t* commands;
            const char* name;
            Add_Callback(Commands_t* commands, const char* name) :
                commands(commands), name(name)
            {
            }
            void operator()(Int_t code, Member_t* member)
            {
                switch (code) {
                    case (CODES::SUCCESS):
                        return commands->Log_Note("A clone of ", name, " is now a member.");
                    case (CODES::ACTOR):
                        return commands->Log_Note("A clone of this can't be made a member.");
                    case (CODES::MEMBERS):
                        return commands->Log_Note("No room for a clone of ", name, " to be a member.");
                    case (CODES::CHILD):
                        return commands->Log_Note("A child cannot be cloned.");
                    case (CODES::CLONE):
                        return commands->Log_Note(name, " could not be cloned.");
                    default:
                        return commands->Log_Error(name, " could not be cloned", code);
                };
            }
        };
        Members_t::Add_Callback_i* add_callback = new Add_Callback(this, Actor2::Get_Name(actor));
        Members_t::Self()->Add_Clone(actor, &add_callback);
    }

    void Commands_t::Unclone(Actor_t* actor)
    {
        const char* name = Actor2::Get_Name(actor);
        Int_t code = Party::Members_t::Self()->Remove_Clone(actor, true);

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is no longer a member and was uncloned.");
            case (CODES::ACTOR):
                return Log_Note("That can't be unmembered or uncloned.");
            case (CODES::MEMBER):
                return Log_Note(name, " was already not a member and can't be uncloned.");
            case (CODES::CLONE):
                return Log_Note(name, " isnt a clone.");
            default:
                return Log_Error(name, " can't be unmembered and uncloned", code);
        };
    }

    void Commands_t::Start_Move(Actor_t* actor)
    {
        const char* name = Actor2::Get_Name(actor);
        Int_t code = Party::Movee_t::Self()->Start(actor);

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Moving ", name, ".");
            case (CODES::ACTOR):
                return Log_Note("Can only move actors.");
            case (CODES::MANNEQUIN):
                return Log_Note("Can't move mannequins.");
            case (CODES::DISPLAY):
                return Log_Note("Can't move displays.");
            case (CODES::MOVEE):
                return Log_Note("Someone is already being moved.");
            default:
                return Log_Error(name, " can't be moved", code);
        };
    }

    void Commands_t::Stop_Move(Actor_t* actor)
    {
        const char* name = Actor2::Get_Name(actor);
        Int_t code = Party::Movee_t::Self()->Stop();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Stopped moving ", name, ".");
            case (CODES::MOVEE):
                return Log_Note("No one is being moved.");
            default:
                return Log_Error(name, " can't be moved", code);
        };
    }

    void Commands_t::Toggle_Member(Actor_t* actor)
    {
        if (Party::Members_t::Self()->Has_Actor(actor)) {
            return Unmember(actor);
        } else {
            return Member(actor);
        }
    }

    void Commands_t::Toggle_Clone(Actor_t* actor)
    {
        if (Party::Members_t::Self()->Is_Clone(actor)) {
            return Unclone(actor);
        } else {
            return Clone(actor);
        }
    }

    void Commands_t::Toggle_Move(Actor_t* actor)
    {
        if (Party::Movee_t::Self()->Is_Filled()) {
            return Stop_Move(actor);
        } else {
            return Start_Move(actor);
        }
    }

    void Commands_t::Has_Base(Actor_t* actor)
    {
        if (actor) {
            Party::Members_t* members = Party::Members_t::Self();
            Party::Member_t* member = members->From_Actor(actor);
            const char* name = member ? member->Name().data : Actor2::Get_Name(actor);

            if (members->Has_Base(actor)) {
                return Log_Note("A member has the base of ", name, ".", false);
            } else {
                return Log_Note("No member has the base of ", name, ".", false);
            }
        } else {
            return Log_Note("That is not an NPC.", false);
        }
    }

    void Commands_t::Has_Head(Actor_t* actor)
    {
        if (actor) {
            Party::Members_t* members = Party::Members_t::Self();
            Party::Member_t* member = members->From_Actor(actor);
            const char* name = member ? member->Name().data : Actor2::Get_Name(actor);

            if (members->Has_Head(actor)) {
                return Log_Note("A member looks like ", name, ".", false);
            } else {
                return Log_Note("No member looks like ", name, ".", false);
            }
        } else {
            return Log_Note("That is not an NPC.", false);
        }
    }

    void Commands_t::Count_Base(Actor_t* actor)
    {
        if (actor) {
            Party::Members_t* members = Party::Members_t::Self();
            Party::Member_t* member = members->From_Actor(actor);
            const char* name = member ? member->Name().data : Actor2::Get_Name(actor);
            Int_t count = members->Count_Base(actor);

            if (count == 1) {
                return Log_Note("1 member has the base of ", name, ".", false);
            } else {
                return Log_Note(std::to_string(count).c_str(), " members have the base of ", name, ".", false);
            }
        } else {
            return Log_Note("That is not an NPC.", false);
        }
    }

    void Commands_t::Count_Heads(Actor_t* actor)
    {
        if (actor) {
            Party::Members_t* members = Party::Members_t::Self();
            Party::Member_t* member = members->From_Actor(actor);
            const char* name = member ? member->Name().data : Actor2::Get_Name(actor);
            Int_t count = members->Count_Heads(actor);

            if (count == 1) {
                return Log_Note("1 member looks like ", name, ".", false);
            } else {
                return Log_Note(std::to_string(count).c_str(), " members look like ", name, ".", false);
            }
        } else {
            return Log_Note("That is not an NPC.", false);
        }
    }

    // Member

    void Commands_t::Summon(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Summon();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has been summoned.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be summoned.");
            case (CODES::MANNEQUIN):
                return Log_Note(name, " is a mannequin, and so wasn't summoned.");
            default:
                return Log_Error(name, " can't be summoned", code);
        };
    }

    void Commands_t::Goto(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Goto();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("You have gone to ", name);
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be gone to.");
            default:
                return Log_Error(name, " can not be gone to", code);
        };
    }

    void Commands_t::Open_Pack(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Open_Pack();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will carry the pack.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't carry a pack.");
            default:
                return Log_Error(name, " can't carry the pack", code);
        };
    }

    void Commands_t::Stash(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Stash();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has stashed away the contents of their pack.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so cannot stash their pack.");
            default:
                return Log_Error(name, " can't stash their pack", code);
        };
    }

    void Commands_t::Resurrect(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Resurrect();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has been resurrected.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be resurrected.");
            case (CODES::IS):
                return Log_Note(name, " is already alive.");
            default:
                return Log_Error(name, " can't be resurrected", code);
        };
    }

    void Commands_t::Kill(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Kill();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has been killed.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be killed.");
            case (CODES::IS):
                return Log_Note(name, " is already dead.");
            default:
                return Log_Error(name, " can't be killed", code);
        };
    }

    void Commands_t::Mobilize(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Mobilize();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will start moving.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be mobilized.");
            case (CODES::IS):
                return Log_Note(name, " is already mobile.");
            default:
                return Log_Error(name, " can't be mobilized", code);
        };
    }

    void Commands_t::Immobilize(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Immobilize();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will stop moving.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be immobilized.");
            case (CODES::IS):
                return Log_Note(name, " is already immobile.");
            default:
                return Log_Error(name, " can't be immobilized", code);
        };
    }

    void Commands_t::Settle(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Settle();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will settle here.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't settle here.");
            case (CODES::IS):
                return Log_Note(name, " is already settled.");
            default:
                return Log_Error(name, " can't settle here", code);
        };
    }

    void Commands_t::Resettle(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Resettle();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will resettle here.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't resettle.");
            case (CODES::ISNT):
                return Log_Note(name, " isn't a settler, and so can't resettle.");
            default:
                return Log_Error(name, " can't resettle", code);
        };
    }

    void Commands_t::Unsettle(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Unsettle();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will not be a settler.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't unsettle.");
            case (CODES::IS):
                return Log_Note(name, " is already unsettled.");
            default:
                return Log_Error(name, " can't unsettle", code);
        };
    }

    void Commands_t::Enthrall(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Enthrall();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is now enthralled.");
            case (CODES::VAMPIRE):
                return Log_Note("Only a vampire can enthrall ", name, ".");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be enthralled.");
            case (CODES::IS):
                return Log_Note(name, " is already enthralled.");
            default:
                return Log_Error(name, " can't be enthralled", code);
        };
    }

    void Commands_t::Unthrall(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Unthrall();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will be unthralled.");
            case (CODES::VAMPIRE):
                return Log_Note("Only a vampire can unthrall ", name, ".");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be unthralled.");
            case (CODES::IS):
                return Log_Note(name, " is already unthralled.");
            default:
                return Log_Error(name, " can't be unthralled", code);
        };
    }

    void Commands_t::Paralyze(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Paralyze();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will be paralyzed.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be paralyzed.");
            case (CODES::IS):
                return Log_Note(name, " is already paralyzed.");
            default:
                return Log_Error(name, " can't be paralyzed", code);
        };
    }

    void Commands_t::Unparalyze(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Unparalyze();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will no longer be paralyzed.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be unparalyzed.");
            case (CODES::IS):
                return Log_Note(name, " is already unparalyzed.");
            default:
                return Log_Error(name, " can't be unparalyzed", code);
        };
    }

    void Commands_t::Mannequinize(Actor_t* actor, Reference_t* marker)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Mannequinize(marker);
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has become a mannequin.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be a mannequin.");
            case (CODES::IS):
                return Log_Note(name, " is already a mannequin.");
            case (CODES::MARKER):
                return Log_Note(name, " doesn't have a valid mannequin marker.");
            default:
                return Log_Error(name, " can't be mannequinized", code);
        };
    }

    void Commands_t::Unmannequinize(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Unmannequinize();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is no longer a mannequin.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be unmannequinized.");
            case (CODES::IS):
                return Log_Note(name, " is not a mannequin.");
            case (CODES::MARKER):
                return Log_Note(name, " doesn't have a valid mannequin marker.");
            default:
                return Log_Error(name, " can't be unmannequinized", code);
        };
    }

    void Commands_t::Expo(Int_t expoee_id, Reference_t* marker)
    {
        auto callback = [](Int_t code, const char* name)->void
        {
            Commands_t* commands = Commands_t::Self();
            switch (code) {
                case (CODES::SUCCESS):
                    return commands->Log_Note(name, " will now be a mannequin.");
                case (CODES::MEMBER):
                    return commands->Log_Note(name, " isn't a member, and so can't be a mannequin.");
                case (CODES::ACTOR):
                    return commands->Log_Note("Use the Move hotkey to bring an NPC closer to the pedestal.");
                case (CODES::HAS):
                    return commands->Log_Note("There is already a mannequin here.");
                case (CODES::MARKER):
                    return commands->Log_Error("Invalid marker", code);
                case (CODES::HASNT):
                    return commands->Log_Error("Invalid Expo ID", code);
                default:
                    return commands->Log_Error(name, " can't be mannequinized", code);
            };
        };
        Party::Mannequins_t::Self()->Expo(expoee_id, marker, callback);
    }

    void Commands_t::Unexpo(Int_t expoee_id)
    {
        auto callback = [](Int_t code, const char* name)->void
        {
            Commands_t* commands = Commands_t::Self();
            switch (code) {
                case (CODES::SUCCESS):
                    return commands->Log_Note(name, " will no longer be a mannequin.");
                case (CODES::MEMBER):
                    return commands->Log_Note("No mannequin on pedestal.");
                case (CODES::HASNT):
                    return commands->Log_Error("Invalid Expo ID", code);
                default:
                    return commands->Log_Error(name, " can't be mannequinized", code);
            };
        };
        Party::Mannequins_t::Self()->Unexpo(expoee_id, callback);
    }

    void Commands_t::Reanimate(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Reanimate();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has been reanimated.");
            case (CODES::ALIVE):
                return Log_Note(name, " is alive, and so can't be reanimated.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be reanimated.");
            case (CODES::IS):
                return Log_Note(name, " is already reanimated.");
            default:
                return Log_Error(name, " can't be reanimated", code);
        };
    }

    void Commands_t::Deanimate(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Deanimate();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will no longer be reanimated.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be deanimated.");
            case (CODES::IS):
                return Log_Note(name, " is already not reanimated.");
            default:
                return Log_Error(name, " can't be deanimated", code);
        };
    }

    void Commands_t::Follow(Actor_t* actor)
    {
        using namespace Party;

        if (actor) {
            Member_t* member = Members_t::Self()->From_Actor(actor);
            if (member) {
                class Add_Callback : public Followers_t::Add_Callback_i {
                public:
                    Commands_t* commands;
                    Member_t* member;
                    Add_Callback(Commands_t* commands, Member_t* member) :
                        commands(commands), member(member)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        commands->Log_Follow(code, member->Name());
                    }
                };
                Followers_t::Add_Callback_i* add_callback = new Add_Callback(this, member);
                Followers_t::Self()->Add_Follower(member, &add_callback);
            } else {
                Log_Follow(CODES::MEMBER, Actor2::Get_Name(actor));
            }
        } else {
            Log_Follow(CODES::ACTOR, "");
        }
    }

    void Commands_t::Follow(Actor_t* actor, Callback_t<Int_t, Party::Follower_t*>** user_callback)
    {
        using namespace Party;

        if (actor) {
            Member_t* member = Members_t::Self()->From_Actor(actor);
            if (member) {
                class Add_Callback : public Followers_t::Add_Callback_i {
                public:
                    Commands_t* commands;
                    Member_t* member;
                    Callback_t<Int_t, Follower_t*>* user_callback;
                    Add_Callback(Commands_t* commands, Member_t* member, Callback_t<Int_t, Follower_t*>* user_callback) :
                        commands(commands), member(member), user_callback(user_callback)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        commands->Log_Follow(code, member->Name());
                        user_callback->operator()(code, follower);
                        delete user_callback;
                    }
                };
                Followers_t::Add_Callback_i* add_callback = new Add_Callback(this, member, *user_callback);
                Followers_t::Self()->Add_Follower(member, &add_callback);
            } else {
                Log_Follow(CODES::MEMBER, Actor2::Get_Name(actor));
                (*user_callback)->operator()(CODES::MEMBER, nullptr);
                delete (*user_callback);
            }
        } else {
            Log_Follow(CODES::ACTOR, "");
            (*user_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*user_callback);
        }
    }

    void Commands_t::Unfollow(Actor_t* actor)
    {
        using namespace Party;

        if (actor) {
            Member_t* member = Members_t::Self()->From_Actor(actor);
            if (member) {
                struct Callback : public Callback_t<Int_t, Member_t*> {
                    Commands_t* commands;
                    Member_t* member;
                    Callback(Commands_t* commands, Member_t* member) :
                        commands(commands), member(member)
                    {
                    }
                    virtual void operator()(Int_t code, Member_t* member) override
                    {
                        commands->Log_Unfollow(code, member->Name());
                    }
                };
                Callback_t<Int_t, Member_t*>* callback = new Callback(this, member);
                Followers_t::Self()->Remove_Follower(member, &callback);
            } else {
                Log_Unfollow(CODES::MEMBER, Actor2::Get_Name(actor));
            }
        } else {
            Log_Unfollow(CODES::ACTOR, "");
        }
    }

    void Commands_t::Unfollow(Actor_t* actor, Callback_t<Int_t, Party::Member_t*>** user_callback)
    {
        using namespace Party;

        if (actor) {
            Member_t* member = Members_t::Self()->From_Actor(actor);
            if (member) {
                struct Callback : public Callback_t<Int_t, Member_t*> {
                    Commands_t* commands;
                    Member_t* member;
                    Callback_t<Int_t, Member_t*>* user_callback;
                    Callback(Commands_t* commands, Member_t* member, Callback_t<Int_t, Member_t*>* user_callback) :
                        commands(commands), member(member), user_callback(user_callback)
                    {
                    }
                    virtual void operator()(Int_t code, Member_t* member) override
                    {
                        commands->Log_Unfollow(code, member->Name());
                        user_callback->operator()(code, member);
                        delete user_callback;
                    }
                };
                Callback_t<Int_t, Member_t*>* callback = new Callback(this, member, *user_callback);
                Followers_t::Self()->Remove_Follower(member, &callback);
            } else {
                Log_Unfollow(CODES::MEMBER, Actor2::Get_Name(actor));
                (*user_callback)->operator()(CODES::MEMBER, nullptr);
                delete (*user_callback);
            }
        } else {
            Log_Unfollow(CODES::ACTOR, "");
            (*user_callback)->operator()(CODES::ACTOR, nullptr);
            delete (*user_callback);
        }
    }

    void Commands_t::Stylize_Default(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Stylize_Default();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " now fights with their default style.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be stylized.");
            case (CODES::IS):
                return Log_Note(name, " already fights with their default style.");
            default:
                return Log_Error(name, " can't use their deafult style", code);
        };
    }

    void Commands_t::Stylize_Warrior(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Stylize_Warrior();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " now fights as a warrior.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be a warrior.");
            case (CODES::IS):
                return Log_Note(name, " already fights as a warrior.");
            default:
                return Log_Error(name, " can't be a warrior", code);
        };
    }

    void Commands_t::Stylize_Mage(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Stylize_Mage();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " now fights as a mage.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be a mage.");
            case (CODES::IS):
                return Log_Note(name, " already fights as a mage.");
            default:
                return Log_Error(name, " can't be a mage", code);
        };
    }

    void Commands_t::Stylize_Archer(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Stylize_Archer();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " now fights as an archer.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be an archer.");
            case (CODES::IS):
                return Log_Note(name, " already fights as an archer.");
            default:
                return Log_Error(name, " can't be an archer", code);
        };
    }

    void Commands_t::Stylize_Coward(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Stylize_Coward();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " now flees as a coward.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be a coward.");
            case (CODES::IS):
                return Log_Note(name, " already flees as a coward.");
            default:
                return Log_Error(name, " can't be a coward", code);
        };
    }

    void Commands_t::Vitalize_Mortal(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Vitalize_Mortal();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is now mortal.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be made mortal.");
            case (CODES::IS):
                return Log_Note(name, " is already mortal.");
            default:
                return Log_Error(name, " can't be mortal", code);
        };
    }

    void Commands_t::Vitalize_Protected(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Vitalize_Protected();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is now protected.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be protected.");
            case (CODES::IS):
                return Log_Note(name, " is already protected.");
            default:
                return Log_Error(name, " can't be protected", code);
        };
    }

    void Commands_t::Vitalize_Essential(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Vitalize_Essential();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is now essential.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be essential.");
            case (CODES::IS):
                return Log_Note(name, " is already essential.");
            default:
                return Log_Error(name, " can't be essential", code);
        };
    }

    void Commands_t::Vitalize_Invulnerable(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Vitalize_Invulnerable();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " is now invulnerable.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be invulnerable.");
            case (CODES::IS):
                return Log_Note(name, " is already invulnerable.");
            default:
                return Log_Error(name, " can't be invulnerable", code);
        };
    }

    void Commands_t::Change_Member_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Member_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their member outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their member outfit", code);
        };
    }

    void Commands_t::Change_Immobile_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Immobile_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their immobile outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their immobile outfit", code);
        };
    }

    void Commands_t::Change_Settler_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Settler_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their settler outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their settler outfit", code);
        };
    }

    void Commands_t::Change_Thrall_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Thrall_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their thrall outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their thrall outfit", code);
        };
    }

    void Commands_t::Change_Follower_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Follower_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their follower outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their follower outfit", code);
        };
    }

    void Commands_t::Change_Vanilla_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Vanilla_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their vanilla outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their vanilla outfit", code);
        };
    }

    void Commands_t::Change_Default_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Default_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their default outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their default outfit", code);
        };
    }

    void Commands_t::Change_Current_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Change_Current_Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will change their current outfit.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be outfitted.");
            default:
                return Log_Error(name, " can't change their current outfit", code);
        };
    }

    void Commands_t::Rate(Actor_t* actor, Int_t rating)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Rate(rating);
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " has been rated.");
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and so can't be rated.");
            case (CODES::ISNT):
                return Log_Note(name, " isn't a valid rating.");
            default:
                return Log_Error(name, " can't change their current outfit", code);
        };
    }

    void Commands_t::Toggle_Immobile(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Immobile()) {
                Mobilize(actor);
            } else {
                Immobilize(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Immobilize(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Settler(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Settler()) {
                Unsettle(actor);
            } else {
                Settle(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Settle(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Thrall(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Thrall()) {
                Unthrall(actor);
            } else {
                Enthrall(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Enthrall(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Paralyzed(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Paralyzed()) {
                Unparalyze(actor);
            } else {
                Paralyze(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Paralyze(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Mannequin(Actor_t* actor, Reference_t* marker)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Mannequin()) {
                Unmannequinize(actor);
            } else {
                Mannequinize(actor, marker);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Reference_t* marker;
                Add_Callback(Commands_t* commands, Actor_t* actor, Reference_t* marker) :
                    commands(commands), actor(actor), marker(marker)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Mannequinize(actor, marker);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor, marker);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Expoee(Int_t expoee_id, Reference_t* marker)
    {
        if (Party::Mannequins_t::Self()->Has_Expoee(expoee_id)) {
            Unexpo(expoee_id);
        } else {
            Expo(expoee_id, marker);
        }
    }

    void Commands_t::Toggle_Reanimated(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Reanimated()) {
                Deanimate(actor);
            } else {
                Reanimate(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Reanimate(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Follower(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            if (member->Is_Follower()) {
                Unfollow(actor);
            } else {
                Follow(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Follow(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Show_Style(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Style();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::STYLE::DEFAULT):
                return Log_Note("Is Default ", false);
            case (CODES::STYLE::WARRIOR):
                return Log_Note("Is Warrior ", false);
            case (CODES::STYLE::MAGE):
                return Log_Note("Is Mage ", false);
            case (CODES::STYLE::ARCHER):
                return Log_Note("Is Archer ", false);
            case (CODES::STYLE::COWARD):
                return Log_Note("Is Coward ", false);
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and doesn't have a style.");
            default:
                return Log_Error(name, " doesn't have a style", code);
        };
    }

    void Commands_t::Show_Vitality(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Vitality();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::VITALITY::MORTAL):
                return Log_Note("Is Mortal ", false);
            case (CODES::VITALITY::PROTECTED):
                return Log_Note("Is Protected ", false);
            case (CODES::VITALITY::ESSENTIAL):
                return Log_Note("Is Essential ", false);
            case (CODES::VITALITY::INVULNERABLE):
                return Log_Note("Is Invulnerable ", false);
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and doesn't have a vitality.");
            default:
                return Log_Error(name, " doesn't have a vitality", code);
        };
    }

    void Commands_t::Show_Outfit2(Actor_t* actor)
    {
        Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (member) {
            name = member->Name().data;
            code = member->Outfit2();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::MEMBER;
        }

        switch (code) {
            case (CODES::OUTFIT2::MEMBER):
                return Log_Note("Wearing Member ", false);
            case (CODES::OUTFIT2::IMMOBILE):
                return Log_Note("Wearing Immobile ", false);
            case (CODES::OUTFIT2::SETTLER):
                return Log_Note("Wearing Settler ", false);
            case (CODES::OUTFIT2::THRALL):
                return Log_Note("Wearing Thrall ", false);
            case (CODES::OUTFIT2::FOLLOWER):
                return Log_Note("Wearing Follower ", false);
            case (CODES::OUTFIT2::VANILLA):
                return Log_Note("Wearing Vanilla ", false);
            case (CODES::OUTFIT2::DEFAULT):
                return Log_Note("Wearing Default ", false);
            case (CODES::MEMBER):
                return Log_Note(name, " isn't a member, and doesn't have an outfit.");
            default:
                return Log_Error(name, " doesn't have an outfit", code);
        };
    }

    void Commands_t::Cycle_Style(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            Int_t style = member->Style();
            switch (style) {
                case (CODES::STYLE::DEFAULT):
                    return Stylize_Warrior(actor);
                case (CODES::STYLE::WARRIOR):
                    return Stylize_Mage(actor);
                case (CODES::STYLE::MAGE):
                    return Stylize_Archer(actor);
                case (CODES::STYLE::ARCHER):
                    return Stylize_Coward(actor);
                case (CODES::STYLE::COWARD):
                    return Stylize_Default(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Stylize_Default(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Cycle_Vitality(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            Int_t vitality = member->Vitality();
            switch (vitality) {
                case (CODES::VITALITY::MORTAL):
                    return Vitalize_Protected(actor);
                case (CODES::VITALITY::PROTECTED):
                    return Vitalize_Essential(actor);
                case (CODES::VITALITY::ESSENTIAL):
                    return Vitalize_Invulnerable(actor);
                case (CODES::VITALITY::INVULNERABLE):
                    return Vitalize_Mortal(actor);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Vitalize_Mortal(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Cycle_Rating(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            Int_t rating = member->Rating();
            switch (rating) {
                case (0):
                    return Rate(actor, 1);
                case (1):
                    return Rate(actor, 2);
                case (2):
                    return Rate(actor, 3);
                case (3):
                    return Rate(actor, 4);
                case (4):
                    return Rate(actor, 5);
                case (5):
                    return Rate(actor, 0);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Rate(actor, 1);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    // Follower

    void Commands_t::Sneak(Actor_t* actor)
    {
        Party::Follower_t* follower = Party::Followers_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (follower) {
            name = follower->Name().data;
            code = follower->Sneak();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::FOLLOWER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will start sneaking.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " isn't a follower, and so can't start sneaking.");
            case (CODES::IS):
                return Log_Note(name, " is already sneaking.");
            default:
                return Log_Error(name, " can't start sneaking", code);
        };
    }

    void Commands_t::Unsneak(Actor_t* actor)
    {
        Party::Follower_t* follower = Party::Followers_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (follower) {
            name = follower->Name().data;
            code = follower->Unsneak();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::FOLLOWER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will stop sneaking.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " isn't a follower, and so can't stop sneaking.");
            case (CODES::IS):
                return Log_Note(name, " is not sneaking.");
            default:
                return Log_Error(name, " can't stop sneaking", code);
        };
    }

    void Commands_t::Saddle(Actor_t* actor)
    {
        using namespace Party;

        if (actor) {
            Follower_t* follower = Followers_t::Self()->From_Actor(actor);
            if (follower) {
                class Saddle_Callback : public Callback_t<Int_t, Follower_t*> {
                public:
                    Commands_t* commands;
                    Follower_t* follower;
                    Saddle_Callback(Commands_t* commands, Follower_t* follower) :
                        commands(commands), follower(follower)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        commands->Log_Saddle(code, follower->Name());
                    }
                };
                Callback_t<Int_t, Follower_t*>* saddle_callback = new Saddle_Callback(this, follower);
                follower->Saddle(&saddle_callback);
            } else {
                Log_Saddle(CODES::FOLLOWER, Actor2::Get_Name(actor));
            }
        } else {
            Log_Saddle(CODES::ACTOR, "");
        }
    }

    void Commands_t::Unsaddle(Actor_t* actor)
    {
        using namespace Party;

        if (actor) {
            Follower_t* follower = Followers_t::Self()->From_Actor(actor);
            if (follower) {
                class Unsaddle_Callback : public Callback_t<Int_t, Follower_t*> {
                public:
                    Commands_t* commands;
                    Follower_t* follower;
                    Unsaddle_Callback(Commands_t* commands, Follower_t* follower) :
                        commands(commands), follower(follower)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        commands->Log_Unsaddle(code, follower->Name());
                    }
                };
                Callback_t<Int_t, Follower_t*>* unsaddle_callback = new Unsaddle_Callback(this, follower);
                follower->Unsaddle(&unsaddle_callback);
            } else {
                Log_Unsaddle(CODES::FOLLOWER, Actor2::Get_Name(actor));
            }
        } else {
            Log_Unsaddle(CODES::ACTOR, "");
        }
    }

    void Commands_t::Retreat(Actor_t* actor)
    {
        Party::Follower_t* follower = Party::Followers_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (follower) {
            name = follower->Name().data;
            code = follower->Retreat();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::FOLLOWER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will start retreating.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " isn't a follower, and so can't retreat.");
            case (CODES::IS):
                return Log_Note(name, " is already retreating.");
            default:
                return Log_Error(name, " can't start retreating", code);
        };
    }

    void Commands_t::Unretreat(Actor_t* actor)
    {
        Party::Follower_t* follower = Party::Followers_t::Self()->From_Actor(actor);

        const char* name;
        Int_t code;
        if (follower) {
            name = follower->Name().data;
            code = follower->Unretreat();
        } else {
            name = Actor2::Get_Name(actor);
            code = CODES::FOLLOWER;
        }

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note(name, " will stop retreating.");
            case (CODES::FOLLOWER):
                return Log_Note(name, " isn't a follower, and so can't stop retreating.");
            case (CODES::IS):
                return Log_Note(name, " is not retreating.");
            default:
                return Log_Error(name, " can't stop retreating", code);
        };
    }

    void Commands_t::Toggle_Sneak(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            Party::Follower_t* follower = member->Follower();
            if (follower) {
                if (follower->Is_Sneak()) {
                    Unsneak(actor);
                } else {
                    Sneak(actor);
                }
            } else {
                class Add_Callback : public Followers_t::Add_Callback_i {
                public:
                    Commands_t* commands;
                    Actor_t* actor;
                    Member_t* member;
                    Add_Callback(Commands_t* commands, Actor_t* actor, Member_t* member) :
                        commands(commands), actor(actor), member(member)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        if (code == CODES::SUCCESS) {
                            commands->Sneak(actor);
                        } else {
                            commands->Log_Follow(code, member->Name());
                        }
                    }
                };
                Followers_t::Add_Callback_i* add_callback = new Add_Callback(this, actor, member);
                Followers_t::Self()->Add_Follower(member, &add_callback);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Toggle_Sneak(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Saddler(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            Party::Follower_t* follower = member->Follower();
            if (follower) {
                if (follower->Is_Saddler()) {
                    Unsaddle(actor);
                } else {
                    Saddle(actor);
                }
            } else {
                class Add_Callback : public Followers_t::Add_Callback_i {
                public:
                    Commands_t* commands;
                    Actor_t* actor;
                    Member_t* member;
                    Add_Callback(Commands_t* commands, Actor_t* actor, Member_t* member) :
                        commands(commands), actor(actor), member(member)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        if (code == CODES::SUCCESS) {
                            commands->Saddle(actor);
                        } else {
                            commands->Log_Follow(code, member->Name());
                        }
                    }
                };
                Followers_t::Add_Callback_i* add_callback = new Add_Callback(this, actor, member);
                Followers_t::Self()->Add_Follower(member, &add_callback);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Toggle_Saddler(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    void Commands_t::Toggle_Retreater(Actor_t* actor)
    {
        using namespace Party;

        Member_t* member = Party::Members_t::Self()->From_Actor(actor);
        if (member) {
            Party::Follower_t* follower = member->Follower();
            if (follower) {
                if (follower->Is_Retreater()) {
                    Unretreat(actor);
                } else {
                    Retreat(actor);
                }
            } else {
                class Add_Callback : public Followers_t::Add_Callback_i {
                public:
                    Commands_t* commands;
                    Actor_t* actor;
                    Member_t* member;
                    Add_Callback(Commands_t* commands, Actor_t* actor, Member_t* member) :
                        commands(commands), actor(actor), member(member)
                    {
                    }
                    virtual void operator()(Int_t code, Follower_t* follower) override
                    {
                        if (code == CODES::SUCCESS) {
                            commands->Retreat(actor);
                        } else {
                            commands->Log_Follow(code, member->Name());
                        }
                    }
                };
                Followers_t::Add_Callback_i* add_callback = new Add_Callback(this, actor, member);
                Followers_t::Self()->Add_Follower(member, &add_callback);
            }
        } else {
            class Add_Callback : public Members_t::Add_Callback_i {
            public:
                Commands_t* commands;
                Actor_t* actor;
                Add_Callback(Commands_t* commands, Actor_t* actor) :
                    commands(commands), actor(actor)
                {
                }
                virtual void operator()(Int_t code, Member_t* member) override
                {
                    if (code == CODES::SUCCESS) {
                        commands->Toggle_Retreater(actor);
                    } else {
                        commands->Log_Member(code, Actor2::Get_Name(actor));
                    }
                }
            };
            Members_t::Add_Callback_i* add_callback = new Add_Callback(this, actor);
            Members_t::Self()->Add_Original(actor, &add_callback);
        }
    }

    // Members

    void Commands_t::Members_Start_Display()
    {
        Int_t code = Party::Members_t::Self()->Display_Start();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Display mode has been started.");
            case (CODES::DISPLAY):
                return Log_Note("Display has already been started.");
            case (CODES::MEMBERS):
                return Log_Note("No members to display. Check your filter.");
            default:
                return Log_Error("Could not start a display", code);
        };
    }

    void Commands_t::Members_Stop_Display()
    {
        Int_t code = Party::Members_t::Self()->Display_Stop();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Display has now been stopped.");
            case (CODES::DISPLAY):
                return Log_Note("Display has already been stopped.");
            default:
                return Log_Error("Could not stop display", code);
        };
    }

    void Commands_t::Members_Display_Previous()
    {
        Int_t code = Party::Members_t::Self()->Display_Previous();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Displaying previous members.");
            case (CODES::DISPLAY):
                return Log_Note("You need to start up a display first.");
            case (CODES::MEMBERS):
                return Log_Note("No remaining members to display. Stopping.");
            default:
                return Log_Error("Could not display previous members", code);
        };
    }

    void Commands_t::Members_Display_Next()
    {
        Int_t code = Party::Members_t::Self()->Display_Next();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Displaying next members.");
            case (CODES::DISPLAY):
                return Log_Note("You need to start up a display first.");
            case (CODES::MEMBERS):
                return Log_Note("No remaining members to display. Stopping.");
            default:
                return Log_Error("Could not display next members", code);
        };
    }

    void Commands_t::Members_Toggle_Display()
    {
        if (Party::Members_t::Self()->Has_Display()) {
            return Members_Stop_Display();
        } else {
            return Members_Start_Display();
        }
    }

    // Followers

    void Commands_t::Followers_Summon_All()
    {
        Int_t code = Party::Followers_t::Self()->Summon_Filled();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Summoned all followers.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to summon.");
            default:
                return Log_Error("Could not summon all followers", code);
        };
    }

    void Commands_t::Followers_Summon_Mobile()
    {
        Int_t code = Party::Followers_t::Self()->Summon_Mobile();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Summoned all mobile followers.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to summon.");
            case (CODES::HASNT):
                return Log_Note("No mobile followers to summon.");
            default:
                return Log_Error("Could not summon mobile followers", code);
        };
    }

    void Commands_t::Followers_Summon_Immobile()
    {
        Int_t code = Party::Followers_t::Self()->Summon_Immobile();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("Summoned all immobile followers.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to summon.");
            case (CODES::HASNT):
                return Log_Note("No immobile followers to summon.");
            default:
                return Log_Error("Could not summon immobile followers", code);
        };
    }

    void Commands_t::Followers_Stash()
    {
        Int_t code = Party::Followers_t::Self()->Stash();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have stashed their packs away.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to stash packs.");
            default:
                return Log_Error("Followers could not stash their packs", code);
        };
    }

    void Commands_t::Followers_Resurrect()
    {
        Int_t code = Party::Followers_t::Self()->Resurrect();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All dead followers will resurrect.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to resurrect.");
            case (CODES::HASNT):
                return Log_Note("All followers are already alive.");
            default:
                return Log_Error("Could not make followers resurrect", code);
        };
    }

    void Commands_t::Followers_Mobilize()
    {
        Int_t code = Party::Followers_t::Self()->Mobilize();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have been mobilized.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to mobilize.");
            case (CODES::HASNT):
                return Log_Note("All followers are already mobilized.");
            default:
                return Log_Error("Could not mobilize followers", code);
        };
    }

    void Commands_t::Followers_Immobilize()
    {
        Int_t code = Party::Followers_t::Self()->Immobilize();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have been immobilized.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to immobilize.");
            case (CODES::HASNT):
                return Log_Note("All followers are already immobilized.");
            default:
                return Log_Error("Could not immobilize followers", code);
        };
    }

    void Commands_t::Followers_Settle()
    {
        Int_t code = Party::Followers_t::Self()->Settle();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers settle where they stand.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to settle.");
            case (CODES::HASNT):
                return Log_Note("All followers are already settled.");
            default:
                return Log_Error("Could not settle followers", code);
        };
    }

    void Commands_t::Followers_Resettle()
    {
        Int_t code = Party::Followers_t::Self()->Resettle();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All follownig settlers will resettle here.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to resettle.");
            case (CODES::HASNT):
                return Log_Note("There are no settlers among your followers.");
            default:
                return Log_Error("Could not resettle followers", code);
        };
    }

    void Commands_t::Followers_Unsettle()
    {
        Int_t code = Party::Followers_t::Self()->Unsettle();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have unsettled.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to unsettle.");
            case (CODES::HASNT):
                return Log_Note("All followers are already unsettled.");
            default:
                return Log_Error("Could not unsettle followers", code);
        };
    }

    void Commands_t::Followers_Enthrall()
    {
        Int_t code = Party::Followers_t::Self()->Enthrall();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have been enthralled.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to enthrall.");
            case (CODES::HASNT):
                return Log_Note("All followers are already enthralled.");
            default:
                return Log_Error("Could not enthrall followers", code);
        };
    }

    void Commands_t::Followers_Unthrall()
    {
        Int_t code = Party::Followers_t::Self()->Unthrall();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have been unthralled.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to unthrall.");
            case (CODES::HASNT):
                return Log_Note("All followers are already unthralled.");
            default:
                return Log_Error("Could not unthrall followers", code);
        };
    }

    void Commands_t::Followers_Paralyze()
    {
        Int_t code = Party::Followers_t::Self()->Paralyze();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have been paralyzed.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to paralyze.");
            case (CODES::HASNT):
                return Log_Note("All followers are already paralyzed.");
            default:
                return Log_Error("Could not paralyze followers", code);
        };
    }

    void Commands_t::Followers_Unparalyze()
    {
        Int_t code = Party::Followers_t::Self()->Unparalyze();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers have been unparalyzed.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to unparalyze.");
            case (CODES::HASNT):
                return Log_Note("All followers are already unparalyzed.");
            default:
                return Log_Error("Could not unparalyze followers", code);
        };
    }

    void Commands_t::Followers_Sneak()
    {
        Int_t code = Party::Followers_t::Self()->Sneak();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will sneak.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to sneak.");
            case (CODES::HASNT):
                return Log_Note("All followers are already sneaking.");
            default:
                return Log_Error("Could not make followers sneak", code);
        };
    }

    void Commands_t::Followers_Unsneak()
    {
        Int_t code = Party::Followers_t::Self()->Unsneak();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will stop sneaking.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to stop sneaking.");
            case (CODES::HASNT):
                return Log_Note("All followers are already not sneaking.");
            default:
                return Log_Error("Could not make followers stop sneaking", code);
        };
    }

    void Commands_t::Followers_Saddle()
    {
        Int_t code = Party::Followers_t::Self()->Saddle();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will saddle up.");
            case (CODES::INTERIOR):
                return Log_Note("Followers cannot saddle up in an interior space.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to saddle up.");
            case (CODES::HASNT):
                return Log_Note("All followers are already saddled up.");
            case (CODES::HAS):
                return Log_Note("Still saddling up followers, please wait.");
            default:
                return Log_Error("Could not make followers saddle up", code);
        };
    }

    void Commands_t::Followers_Unsaddle()
    {
        Int_t code = Party::Followers_t::Self()->Unsaddle();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will unsaddle.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to unsaddle.");
            case (CODES::HASNT):
                return Log_Note("All followers are already unsaddled.");
            case (CODES::HAS):
                return Log_Note("Still unsaddling followers, please wait.");
            default:
                return Log_Error("Could not make followers unsaddle", code);
        };
    }

    void Commands_t::Followers_Retreat()
    {
        Int_t code = Party::Followers_t::Self()->Retreat();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will retreat.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to retreat.");
            case (CODES::HASNT):
                return Log_Note("All followers are already retreating.");
            default:
                return Log_Error("Could not make followers retreat", code);
        };
    }

    void Commands_t::Followers_Unretreat()
    {
        Int_t code = Party::Followers_t::Self()->Unretreat();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will stop retreating.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to stop retreating.");
            case (CODES::HASNT):
                return Log_Note("All followers have already stopped retreating.");
            default:
                return Log_Error("Could not make followers stop retreating", code);
        };
    }

    void Commands_t::Followers_Unfollow()
    {
        Int_t code = Party::Followers_t::Self()->Unfollow();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers will no longer follow.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to unfollow.");
            default:
                return Log_Error("Could not make followers stop following", code);
        };
    }

    void Commands_t::Followers_Unmember()
    {
        Int_t code = Party::Followers_t::Self()->Unmember();

        switch (code) {
            case (CODES::SUCCESS):
                return Log_Note("All followers are no longer members.");
            case (CODES::FOLLOWERS):
                return Log_Note("No followers to unmember.");
            default:
                return Log_Error("Could not unmember followers", code);
        };
    }

    void Commands_t::Followers_Toggle_Immobile()
    {
        if (Party::Followers_t::Self()->Count_Immobile() > 0) {
            return Followers_Mobilize();
        } else {
            return Followers_Immobilize();
        }
    }

    void Commands_t::Followers_Toggle_Settler()
    {
        if (Party::Followers_t::Self()->Count_Settlers() > 0) {
            return Followers_Unsettle();
        } else {
            return Followers_Settle();
        }
    }

    void Commands_t::Followers_Toggle_Thrall()
    {
        if (Party::Followers_t::Self()->Count_Thralls() > 0) {
            return Followers_Unthrall();
        } else {
            return Followers_Enthrall();
        }
    }

    void Commands_t::Followers_Toggle_Paralyzed()
    {
        if (Party::Followers_t::Self()->Count_Paralyzed() > 0) {
            return Followers_Unparalyze();
        } else {
            return Followers_Paralyze();
        }
    }

    void Commands_t::Followers_Toggle_Sneak()
    {
        if (Party::Followers_t::Self()->Count_Sneaks() > 0) {
            return Followers_Unsneak();
        } else {
            return Followers_Sneak();
        }
    }

    void Commands_t::Followers_Toggle_Saddler()
    {
        if (Party::Followers_t::Self()->Count_Saddlers() > 0) {
            return Followers_Unsaddle();
        } else {
            return Followers_Saddle();
        }
    }

    void Commands_t::Followers_Toggle_Retreater()
    {
        if (Party::Followers_t::Self()->Count_Retreaters() > 0) {
            return Followers_Unretreat();
        } else {
            return Followers_Retreat();
        }
    }

    void Commands_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Commands_t,            \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        // NPC
        METHOD("Member", 1, void, Member, Actor_t*);
        METHOD("Unmember", 1, void, Unmember, Actor_t*);
        METHOD("Clone", 1, void, Clone, Actor_t*);
        METHOD("Unclone", 1, void, Unclone, Actor_t*);
        METHOD("Toggle_Move", 1, void, Toggle_Move, Actor_t*);

        // Member
        METHOD("Summon", 1, void, Summon, Actor_t*);
        METHOD("Goto", 1, void, Goto, Actor_t*);
        METHOD("Open_Pack", 1, void, Open_Pack, Actor_t*);
        METHOD("Stash", 1, void, Stash, Actor_t*);
        METHOD("Resurrect", 1, void, Resurrect, Actor_t*);
        METHOD("Mobilize", 1, void, Mobilize, Actor_t*);
        METHOD("Immobilize", 1, void, Immobilize, Actor_t*);
        METHOD("Settle", 1, void, Settle, Actor_t*);
        METHOD("Resettle", 1, void, Resettle, Actor_t*);
        METHOD("Unsettle", 1, void, Unsettle, Actor_t*);
        METHOD("Enthrall", 1, void, Enthrall, Actor_t*);
        METHOD("Unthrall", 1, void, Unthrall, Actor_t*);
        METHOD("Paralyze", 1, void, Paralyze, Actor_t*);
        METHOD("Unparalyze", 1, void, Unparalyze, Actor_t*);
        METHOD("Deanimate", 1, void, Deanimate, Actor_t*);
        METHOD("Follow", 1, void, Follow, Actor_t*);
        METHOD("Unfollow", 1, void, Unfollow, Actor_t*);
        METHOD("Stylize_Default", 1, void, Stylize_Default, Actor_t*);
        METHOD("Stylize_Warrior", 1, void, Stylize_Warrior, Actor_t*);
        METHOD("Stylize_Mage", 1, void, Stylize_Mage, Actor_t*);
        METHOD("Stylize_Archer", 1, void, Stylize_Archer, Actor_t*);
        METHOD("Stylize_Coward", 1, void, Stylize_Coward, Actor_t*);
        METHOD("Vitalize_Mortal", 1, void, Vitalize_Mortal, Actor_t*);
        METHOD("Vitalize_Protected", 1, void, Vitalize_Protected, Actor_t*);
        METHOD("Vitalize_Essential", 1, void, Vitalize_Essential, Actor_t*);
        METHOD("Vitalize_Invulnerable", 1, void, Vitalize_Invulnerable, Actor_t*);
        METHOD("Change_Member_Outfit2", 1, void, Change_Member_Outfit2, Actor_t*);
        METHOD("Change_Immobile_Outfit2", 1, void, Change_Immobile_Outfit2, Actor_t*);
        METHOD("Change_Settler_Outfit2", 1, void, Change_Settler_Outfit2, Actor_t*);
        METHOD("Change_Thrall_Outfit2", 1, void, Change_Thrall_Outfit2, Actor_t*);
        METHOD("Change_Follower_Outfit2", 1, void, Change_Follower_Outfit2, Actor_t*);
        METHOD("Change_Vanilla_Outfit2", 1, void, Change_Vanilla_Outfit2, Actor_t*);
        METHOD("Change_Default_Outfit2", 1, void, Change_Default_Outfit2, Actor_t*);
        METHOD("Change_Current_Outfit2", 1, void, Change_Current_Outfit2, Actor_t*);
        METHOD("Toggle_Expoee", 2, void, Toggle_Expoee, Int_t, Reference_t*);
        METHOD("Toggle_Reanimated", 1, void, Toggle_Reanimated, Actor_t*);
        METHOD("Show_Style", 1, void, Show_Style, Actor_t*);
        METHOD("Show_Vitality", 1, void, Show_Vitality, Actor_t*);
        METHOD("Show_Outfit2", 1, void, Show_Outfit2, Actor_t*);

        // Follower
        METHOD("Sneak", 1, void, Sneak, Actor_t*);
        METHOD("Unsneak", 1, void, Unsneak, Actor_t*);
        METHOD("Saddle", 1, void, Saddle, Actor_t*);
        METHOD("Unsaddle", 1, void, Unsaddle, Actor_t*);
        METHOD("Retreat", 1, void, Retreat, Actor_t*);
        METHOD("Unretreat", 1, void, Unretreat, Actor_t*);

        // Followers
        METHOD("Followers_Summon_All", 0, void, Followers_Summon_All);
        METHOD("Followers_Summon_Mobile", 0, void, Followers_Summon_Mobile);
        METHOD("Followers_Summon_Immobile", 0, void, Followers_Summon_Immobile);
        METHOD("Followers_Stash", 0, void, Followers_Stash);
        METHOD("Followers_Mobilize", 0, void, Followers_Mobilize);
        METHOD("Followers_Immobilize", 0, void, Followers_Immobilize);
        METHOD("Followers_Settle", 0, void, Followers_Settle);
        METHOD("Followers_Unsettle", 0, void, Followers_Unsettle);
        METHOD("Followers_Sneak", 0, void, Followers_Sneak);
        METHOD("Followers_Unsneak", 0, void, Followers_Unsneak);
        METHOD("Followers_Saddle", 0, void, Followers_Saddle);
        METHOD("Followers_Unsaddle", 0, void, Followers_Unsaddle);
        METHOD("Followers_Unfollow", 0, void, Followers_Unfollow);
        METHOD("Followers_Unmember", 0, void, Followers_Unmember);

        #undef METHOD
    }

}}}
