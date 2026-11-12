#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 表情动作基类：处理机器人的文本表情（Emote）与动画表演逻辑
    class EmoteActionBase : public Action
    {
    public:
        /// 构造函数：初始化表情动作基类
        EmoteActionBase(PlayerbotAI* ai, std::string name);
        /// 获取指定表情动作可用的随机变体数量
        static uint32 GetNumberOfEmoteVariants(TextEmotes emote, uint8 race, uint8 gender);

    protected:
        /// 执行指定的文本表情或动作动画
        bool Emote(Unit* target, uint32 type, bool textEmote = false);
        /// 接收周围玩家做出的表情并给予相应回应
        bool ReceiveEmote(Player* requester, Player* source, uint32 emote, bool verbal = false);
        /// 获取当前动作的目标单位（表情动作基类）
        Unit* GetTarget() override;
        /// 初始化表情名称与客户端表情枚举值的映射表
        void InitEmotes();
        static std::map<std::string, uint32> emotes;
        static std::map<std::string, uint32> textEmotes;

    };

    /// 表情表演动作：根据事件或周围玩家行为做出对应的表情动作
    class EmoteAction : public EmoteActionBase, public Qualified
    {
    public:
        /// 构造函数：初始化表情表演动作
        EmoteAction(PlayerbotAI* ai);
        /// 执行动作主逻辑（表情表演动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（表情表演动作）
        bool isUseful() override;
    };

    /// 闲聊动作：在非战斗或 RPG 交互时触发机器人随机对话
    class TalkAction : public EmoteActionBase
    {
    public:
        /// 构造函数：初始化闲聊动作
        TalkAction(PlayerbotAI* ai) : EmoteActionBase(ai, "talk") {}
        /// 执行动作主逻辑（闲聊动作）
        virtual bool Execute(Event& event) override;

        /// 随机挑选一个与当前语境匹配的表情 ID
        static uint32 GetRandomEmote(Unit* unit, bool textEmote = false);
    };

    /// 坐骑动作表演动作：在骑乘状态下触发坐骑特殊动作（/mountspecial）
    class MountAnimAction : public Action
    {
    public:
        /// 构造函数：初始化坐骑动作表演动作
        MountAnimAction(PlayerbotAI* ai, std::string name = "mount anim") : Action(ai, name) {}

        /// 判断当前状态下该动作是否可用/有效（坐骑动作表演动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（坐骑动作表演动作）
        virtual bool Execute(Event& event) override;
    };
}
