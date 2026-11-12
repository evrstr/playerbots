#pragma once

#include "playerbot/playerbot.h"
#include "playerbot/Talentspec.h"
#include "GenericActions.h"

namespace ai
{
    /// 修改天赋指令动作：查看、分配或重置机器人当前的天赋加点方案
    class ChangeTalentsAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化修改天赋指令动作
        ChangeTalentsAction(PlayerbotAI* ai, std::string name = "talents") : ChatCommandAction(ai, name) {}

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（修改天赋指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    public:
        /// 执行动作主逻辑（修改天赋指令动作）
        virtual bool Execute(Event& event) override;
        /// 根据预设或自动算法为机器人分配剩余天赋点数
        static bool AutoSelectTalents(Player* bot, std::ostringstream* out, BotRoles role = BotRoles::BOT_ROLE_NONE);
    private:
        /// 获取当前战场所有可用的预设行进路径列表
        static std::vector<TalentPath*> getPremadePaths(uint8 cls, std::string findName, BotRoles role = BotRoles::BOT_ROLE_NONE);
        /// 获取当前战场所有可用的预设行进路径列表
        static std::vector<TalentPath*> getPremadePaths(Player* bot, TalentSpec* oldSpec);
        /// 根据起止据点编号获取预设的战场战术路径
        static TalentPath* getPremadePath(uint8 cls, int id);
        /// 向聊天频道列出当前战场的预设路径信息（调试用）
        static void listPremadePaths(uint8 cls, std::vector<TalentPath*> paths, std::ostringstream* out);
        /// 从多条可选战场预设路径中随机或按权重挑选一条
        static TalentPath* PickPremadePath(std::vector<TalentPath*> paths, bool useProbability);
        /// 根据机器人当前已点天赋匹配最接近的预设天赋方案
        static TalentSpec* GetBestPremadeSpec(Player* bot, int spec);
    };

    /// 自动分配天赋动作：根据机器人定位或预设方案自动学习天赋
    class AutoSetTalentsAction : public ChangeTalentsAction 
    {
    public:
        /// 构造函数：初始化自动分配天赋动作
        AutoSetTalentsAction(PlayerbotAI* ai) : ChangeTalentsAction(ai, "auto talents") {}
        /// 执行动作主逻辑（自动分配天赋动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动分配天赋动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
