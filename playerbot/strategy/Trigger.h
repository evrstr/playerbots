#pragma once
#include "Event.h"
#include "Value.h"
#include "AiObject.h"

class Unit;

namespace ai
{
    class NextAction;
    template<class T> class Value;
}

namespace ai
{
    /// AI 触发器基类，支持周期性状态检测(IsActive)及外部聊天/数据包事件注入
    class Trigger : public AiNamedObject
    {
    public:
        Trigger(PlayerbotAI* ai, std::string name = "trigger", int checkInterval = 1) : AiNamedObject(ai, name) {
            this->triggered = false;
            this->checkInterval = checkInterval;
            this->lastCheckTime = time(0) - rand() % checkInterval;
        }
        virtual ~Trigger() {}

    public:
        virtual Event Check();
        virtual void ExternalEvent(std::string param, Player* owner = NULL) {}
        virtual void ExternalEvent(WorldPacket &packet, Player* owner = NULL) {}
        virtual void ExternalEventForce(std::string param, Player* owner = NULL)
        {
            this->param = param;
            this->owner = owner;
            this->triggered = true;
        }
        virtual bool IsActive() { return false; }
        virtual bool IsAlreadyTriggered() { return triggered; }
        // True for a trigger fed by an external packet (WorldPacketTrigger). Such an event is a | 外部数据包触发器返回 true，表示该一次性事件必须等待动作处理而不能在当帧丢弃
        // one-shot obligation the bot has to answer, so the engine must not drop it just because its
        // action did not get to run in the tick that delivered it.
        virtual bool IsExternalEvent() const { return false; }
        virtual NextAction** getHandlers() { return NULL; }
        void Update() {}  //Nonfunctional see AiObjectContext::Update() to enable. (未启用，见 AiObjectContext::Update())
        virtual void Reset() { triggered = false; }
        virtual Unit* GetTarget();
        virtual Value<ObjectGuid>* GetTargetValue();
        virtual std::string GetTargetName() { return "self target"; }

        bool needCheck() {
            if (checkInterval < 2) return true;

            time_t now = time(0);
            if (!lastCheckTime || now - lastCheckTime >= checkInterval) {
                lastCheckTime = now;
                return true;
            }
            return false;
        }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dummy"; } //Must equal iternal name
        virtual std::string GetHelpDescription() { return "This is a trigger."; }
        virtual std::vector<std::string> GetUsedTriggers() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif

    protected:
        int checkInterval;
        time_t lastCheckTime;
        std::string param;
        bool triggered;
        Player* owner = nullptr;
    };


    /// 触发器节点，绑定 Trigger 实例及其触发后生成的处理动作链表
    class TriggerNode
    {
    public:
        TriggerNode(std::string name, NextAction** handlers = NULL)
        {
            this->name = name;
            this->handlers = handlers;
            this->trigger = NULL;
        }
        virtual ~TriggerNode();

    public:
        Trigger* getTrigger() { return trigger; }
        void setTrigger(Trigger* trigger) { this->trigger = trigger; }
        std::string getName() { return name; }

    public:
        NextAction** getHandlers();
        float getFirstRelevance();
    private:
        std::string name;
        Trigger* trigger;
        NextAction** handlers;
    };
}
