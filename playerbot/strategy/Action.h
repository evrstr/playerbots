#pragma once
#include "Event.h"
#include "Value.h"
#include "AiObject.h"
#include "AiObject.h"
#include "playerbot/PlayerbotAIConfig.h"

class Unit;

namespace ai
{
    class NextAction;
    template<class T> class Value;
}

namespace ai
{
    /// 描述后续待执行动作的名称与相关性权重
    class NextAction
    {
    public:
        NextAction(std::string name, float relevance = 0.0f)
        {
            this->name = name;
            this->relevance = relevance;
        }
        NextAction(const NextAction& o)
        {
            this->name = o.name;
            this->relevance = o.relevance;
        }

    public:
        std::string getName() const { return name; }
        float getRelevance() const { return relevance; }

    public:
        static int size(NextAction** actions);
        static NextAction** clone(NextAction** actions);
        static NextAction** merge(NextAction** what, NextAction** with);
        static NextAction** array(uint32 n,...);
        static void destroy(NextAction** actions);

    private:
        float relevance;
        std::string name;
    };

    //---------------------------------------------------------------------------------------------------------------------

    class ActionBasket;

    /// 动作产生仇恨的类型枚举（无仇恨/单体/群体/低仇恨）
    enum class ActionThreatType : uint8
    {
        ACTION_THREAT_NONE = 0,
        ACTION_THREAT_SINGLE= 1,
        ACTION_THREAT_AOE = 2,
        ACTION_THREAT_LOW = 3
    };

    /// AI 行为动作基类，封装可执行性检查、有效性判断、前置/替代/后续动作及执行逻辑
    class Action : public AiNamedObject
    {
    public:
        Action(PlayerbotAI* ai, std::string name = "action", uint32 duration = sPlayerbotAIConfig.reactDelay) : AiNamedObject(ai, name), verbose(false), duration(duration) {}
        virtual ~Action(void) {}

    public:
        virtual bool Execute(Event& event) { return true; }
        virtual bool isPossible() { return true; }
        virtual bool isUseful() { return true; }
        virtual bool isUsefulWhenStunned() { return false; }
        virtual bool IsMovement() { return false; }
        virtual NextAction** getPrerequisites() { return NULL; }
        virtual NextAction** getAlternatives() { return NULL; }
        virtual NextAction** getContinuers() { return NULL; }
        virtual ActionThreatType getThreatType() { return ActionThreatType::ACTION_THREAT_NONE; }
        void Update() {}  //Nonfunctional see AiObjectContext::Update() to enable. (未启用，见 AiObjectContext::Update())
        virtual void Reset() {}
        virtual Unit* GetTarget();
        virtual Value<ObjectGuid>* GetTargetValue();
        virtual std::string GetTargetName() { return "self target"; }
        void MakeVerbose(bool enabled) { verbose = enabled; }

        void setRelevance(float relevance1) { relevance = relevance1; };
        virtual float getRelevance() { return relevance; }

        bool IsReaction() const { return reaction; }
        void SetReaction(bool inReaction) { reaction = inReaction; }

        // Used when this action is executed as a reaction (作为反应动作执行时控制是否打断施法或移动)
        virtual bool ShouldReactionInterruptCast() const { return false; }
        virtual bool ShouldReactionInterruptMovement() const { return false; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dummy"; } //Must equal internal name (必须与内部注册名一致)
        virtual std::string GetHelpDescription() { return "This is an action."; }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif

        uint32 GetDuration() const { return duration; }

    protected:
        void SetDuration(uint32 inDuration) { duration = inDuration; }

    protected:
        bool verbose;
        float relevance = 0;
        bool reaction = false;

    private:
        uint32 duration;
    };

    //---------------------------------------------------------------------------------------------------------------------

    /// 动作节点包装器，关联具体 Action 实例与其前置(P)/替代(A)/后续(C)动作链表
    class ActionNode
    {
    public:
        ActionNode(std::string name, NextAction** prerequisites = NULL, NextAction** alternatives = NULL, NextAction** continuers = NULL)
        {
            this->action = NULL;
            this->name = name;
            this->prerequisites = prerequisites;
            this->alternatives = alternatives;
            this->continuers = continuers;
        }

        virtual ~ActionNode()
        {
            NextAction::destroy(prerequisites);
            NextAction::destroy(alternatives);
            NextAction::destroy(continuers);
        }

    public:
        Action* getAction() { return action; }
        void setAction(Action* action) { this->action = action; }
        std::string getName() { return name; }

    public:
        NextAction** getContinuers() { return NextAction::merge(NextAction::clone(continuers), action->getContinuers()); }
        NextAction** getAlternatives() { return NextAction::merge(NextAction::clone(alternatives), action->getAlternatives()); }
        NextAction** getPrerequisites() { return NextAction::merge(NextAction::clone(prerequisites), action->getPrerequisites()); }

    private:
        std::string name;
        Action* action;
        NextAction** continuers;
        NextAction** alternatives;
        NextAction** prerequisites;
    };

    //---------------------------------------------------------------------------------------------------------------------

    /// 动作队列条目，记录动作节点、当前权重、触发事件、是否跳过前置以及过期时间
        class ActionBasket
    {
    public:
        ActionBasket(ActionNode* action, float relevance, bool skipPrerequisites, const Event& event) :
          action(action), relevance(relevance), skipPrerequisites(skipPrerequisites), event(event) {
            created = time(0);
        }
        virtual ~ActionBasket(void) {}
    public:
        float getRelevance() {return relevance;}
        ActionNode* getAction() {return action;}
        Event getEvent() { return event; }
        bool isSkipPrerequisites() { return skipPrerequisites; }
        void AmendRelevance(float k) {relevance *= k; }
        void setRelevance(float relevance) { this->relevance = relevance; }
        void setEvent(Event event) { this->event = event; }
        bool isExpired(time_t secs) { return time(0) - created >= secs; }
    private:
        ActionNode* action;
        float relevance;
        bool skipPrerequisites;
        Event event;
        time_t created;
    };
}
