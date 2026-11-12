#pragma once

#include <map>

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"
#include "Multiplier.h"
#include "AiObjectContext.h"
#include "Strategy.h"
#include "playerbot/BotState.h"

namespace ai
{
    /// 动作执行监听器接口，用于在动作执行前后进行拦截、放行判断或结果覆写
    class ActionExecutionListener
    {
    public:
        virtual bool Before(Action* action, const Event& event) = 0;
        virtual bool AllowExecution(Action* action, const Event& event) = 0;
        virtual void After(Action* action, bool executed, const Event& event) = 0;
        virtual bool OverrideResult(Action* action, bool executed, const Event& event) = 0;
        virtual ~ActionExecutionListener() {};
    };

    // -----------------------------------------------------------------------------------------------------------------------

    /// 动作执行监听器组合管理类
    class ActionExecutionListeners : public ActionExecutionListener
    {
    public:
        virtual ~ActionExecutionListeners() override;

    // ActionExecutionListener
    public:
        virtual bool Before(Action* action, const Event& event) override;
        virtual bool AllowExecution(Action* action, const Event& event) override;
        virtual void After(Action* action, bool executed, const Event& event) override;
        virtual bool OverrideResult(Action* action, bool executed, const Event& event) override;

    public:
        void Add(ActionExecutionListener* listener)
        {
            listeners.push_back(listener);
        }
        void Remove(ActionExecutionListener* listener)
        {
            listeners.remove(listener);
        }

    private:
        std::list<ActionExecutionListener*> listeners;
    };

    // -----------------------------------------------------------------------------------------------------------------------

    /// 单个动作直接执行的结果枚举
    enum ActionResult
    {
        ACTION_RESULT_UNKNOWN,
        ACTION_RESULT_OK,
        ACTION_RESULT_IMPOSSIBLE,
        ACTION_RESULT_USELESS,
        ACTION_RESULT_FAILED
    };

    /// 机器人 AI 决策引擎核心类，管理策略集合、触发器轮询、乘数权重计算与动作队列调度
    class Engine : public PlayerbotAIAware
    {
    public:
        Engine(PlayerbotAI* ai, AiObjectContext *factory, BotState state);

        void Init();
        void addStrategy(const std::string& name);
        void addStrategies(std::string first, ...);
        bool removeStrategy(const std::string& name, bool init = true);
        bool HasStrategy(const std::string& name);
        Strategy* GetStrategy(const std::string& name) const;
        void removeAllStrategies();
        void toggleStrategy(const std::string& name);
        std::string ListStrategies();
        std::list<std::string_view> GetStrategies();
        bool ContainsStrategy(StrategyType type);
        void ChangeStrategy(const std::string& names);
        void PrintStrategies(Player* requester, const std::string& engineType);
        std::string GetLastAction() { return lastAction; }
        const Action* GetLastExecutedAction() const { return lastExecutedAction; }

    public:
        virtual bool DoNextAction(Unit*, int depth, bool minimal, bool isStunned);
        ActionResult ExecuteAction(const std::string& name, Event& event);
        bool CanExecuteAction(const std::string& name, bool isUseful = true, bool isPossible = true);

    public:
        void AddActionExecutionListener(ActionExecutionListener* listener)
        {
            actionExecutionListeners.Add(listener);
        }
        void removeActionExecutionListener(ActionExecutionListener* listener)
        {
            actionExecutionListeners.Remove(listener);
        }

    public:
        virtual ~Engine(void);

    protected:
        bool MultiplyAndPush(NextAction** actions, float forceRelevance, bool skipPrerequisites, const Event& event, const char* pushType);
        void Reset();
        void ProcessTriggers(bool minimal);
        void PushDefaultActions();
        void PushAgain(ActionNode* actionNode, float relevance, const Event& event);
        ActionNode* CreateActionNode(const std::string& name);
        virtual Action* InitializeAction(ActionNode* actionNode);
        virtual bool ListenAndExecute(Action* action, Event& event);
        // Hands an external (packet) trigger back once its action has had its turn. | 动作执行完一轮后归还外部数据包触发器
        void ReleaseExternalEvent(const std::string& source);
        // Drops armed entries whose TriggerNode is gone, so they cannot suppress later packets of the | 清理已失效的外部事件挂载项，防止永久屏蔽后续同类数据包
        // same opcode forever. Called from Init() once the trigger list has been rebuilt.
        void PruneUnhandledExternalEvents();

    private:
        void LogAction(const char* format, ...);
        void LogValues();
        void TrackLoop(Action* action);

    protected:
        Queue queue;
        std::list<TriggerNode*> triggers;
        std::list<Multiplier*> multipliers;
        AiObjectContext* aiObjectContext;
        std::map<std::string, Strategy*> strategies;
        float lastRelevance;
        std::string lastAction;
        std::string lastLoopAction;
        time_t lastLoopStart = 0;
        uint32 lastLoopMap = 0;
        float lastLoopX = 0.0f;
        float lastLoopY = 0.0f;
        uint32 lastLoopHealth = 0;
        ObjectGuid lastLoopTarget;
        ActionExecutionListeners actionExecutionListeners;
        BotState state;
        Action* lastExecutedAction;

        // External (packet) triggers whose event has been queued but not yet handed to its action, | 已入队但尚未交付动作处理的外部数据包触发器集合
        // keyed by trigger name (= the event source). They are exempt from the end-of-tick trigger | 在本帧结束时不重置，确保因权重竞争失利而未被执行的事件不会丢失
        // reset, so a request that loses the tick (the engine runs one action per tick) or whose
        // basket is dropped from the queue is re-pushed instead of silently lost. Entries are removed
        // by ReleaseExternalEvent() as soon as the action has had its turn.
        std::map<std::string, Trigger*> unhandledExternalEvents;

    public:
        bool testMode;
        bool initMode = true;
    };
}
