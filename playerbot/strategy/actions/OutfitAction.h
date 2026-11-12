#pragma once
#include "playerbot/LootObjectStack.h"
#include "EquipAction.h"

namespace ai
{
    /// 配装方案指令动作：查看、保存、切换或应用装备套装方案
    class OutfitAction : public EquipAction 
    {
    public:
        /// 构造函数：初始化配装方案指令动作
        OutfitAction(PlayerbotAI* ai, std::string name = "outfit") : EquipAction(ai, name) {}
        /// 执行动作主逻辑（配装方案指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（配装方案指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    protected:
        /// 按指定条件列出物品、节点或配置列表
        void List(Player* requester);
        /// 保存当前自定义策略或 AI 配置
        void Save(std::string name, ItemIds outfit);
        /// 刷新并应用配置或策略变更
        void Update(std::string name);
    };

    /// 抗性配装指令动作：切换为针对特定魔法抗性（如火抗、暗抗）的配装方案
    class ResistAction : public OutfitAction
    {
    public:
        /// 构造函数：初始化抗性配装指令动作
        ResistAction(PlayerbotAI* ai) : OutfitAction(ai, "resist") {}
        /// 执行动作主逻辑（抗性配装指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（抗性配装指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 查找或匹配针对特定元素抗性的配装方案
        std::string FindResistOutfit(const std::string& school);
        /// 检查机器人当前是否穿戴了抗性配装
        bool WearsResistOutfit();
        /// 根据抗性装备状态切换对应的战斗策略
        void ChangeResistStrategy(const std::string& previousSchool, const std::string& school);
    };
}
