/// 机器人状态反应（Reaction）策略头文件
#pragma once

namespace ai
{
    // TO DO: Delete this when no more dependencies | 待办：解除全部依赖后删除此类
    /// 策略：监听并响应战斗开始/结束与死亡/复活的状态切换
    class ReactionStrategy : public Strategy
    {
    public:
        ReactionStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_REACTION; }

    protected:
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
