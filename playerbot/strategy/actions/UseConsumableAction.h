#pragma once
#include "UseItemAction.h"
#include "playerbot/strategy/ItemVisitors.h"

namespace ai
{
    /// 消耗品类型枚举：区分生命药水、法力药水、治疗石、食物、饮水、增益药剂等类别
    enum class ConsumableType : uint8
    {
        Flask = 0,
        Elixir,
        FoodBuff,
        Alcohol,
        Scroll,
        Count
    };

    /// 机器人消耗品角色定位枚举：区分坦克、治疗、近战输出与法系输出以匹配对应消耗品
    enum class BotConsumableRole : uint8
    {
        MeleeDps,
        RangedPhysDps,
        CasterDps,
        Healer,
        Tank,
    };

    /// 消耗品候选项结构体：保存背包内可用消耗品实例及其恢复效率与优先级评分
    struct ConsumableCandidate
    {
        Item* item = nullptr;
        uint32 spellId = 0;
        ConsumableType type = ConsumableType::Count;
        float score = 0.0f;
    };

    /// 智能使用消耗品动作：按角色定位与战斗场景从可用消耗品候选中挑选最佳药水或食物使用
    class UseConsumableAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化智能使用消耗品动作
        UseConsumableAction(PlayerbotAI* ai) : UseItemIdAction(ai, "use consumable") {}

        /// 执行动作主逻辑（智能使用消耗品动作）
        bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（智能使用消耗品动作）
        bool isPossible() override;
        /// 判断当前状态下该动作是否可用/有效（智能使用消耗品动作）
        bool isUseful() override;

    protected:
        /// 获取关联的物品模板 ID
        uint32 GetItemId() override { return selectedItemId; }

    private:

        /// 扫描背包收集所有符合条件的可用消耗品候选列表
        std::vector<ConsumableCandidate> CollectCandidates();

        /// 将背包物品分类为生命药水、法力药水、食物、绷带等消耗品类型
        bool ClassifyConsumable(const ItemPrototype* proto, ConsumableType& outType, uint32& outSpellId) const;

        /// 判断物品是否为元素防护药水类消耗品
        bool IsProtectionConsumable(const ItemPrototype* proto) const;

        /// 判断物品是否属于共享药水冷却的药水类消耗品
        bool IsPotionLike(const ItemPrototype* proto) const;

        /// 判断物品原型是否为恢复生命或法力的食物/饮水
        bool IsFoodOrDrink(const ItemPrototype* proto) const;

        /// 判断法术是否为提供基础属性加成的增益法术
        bool IsStatBuffSpell(uint32 spellId) const;

        /// 将增益法术 ID 解析为其实际生效的光环 Spell ID
        uint32 ResolveBuffAuraSpellId(uint32 spellId) const;

        /// 收集给定技能或消耗品可能施加的所有光环 Spell ID
        void CollectPossibleAuraIds(uint32 spellId, std::vector<uint32>& outIds) const;

        /// 检查机器人当前是否已拥有合剂类持续增益效果
        bool HasActiveFlask() const;

        /// 检查机器人当前是否已拥有进食增益（如充分进食）
        bool HasActiveFoodBuff() const;

        /// 检查目标是否已存在任一候选增益光环
        bool HasAnyCandidateAura(const ConsumableCandidate& candidate) const;

        /// 按角色定位、恢复量与冷却效率为消耗品候选项评分
        float ScoreCandidate(const ConsumableCandidate& candidate) const;

        /// 根据职业属性权重为技能或装备附带属性评分
        float ScoreSpellStats(uint32 spellId) const;

        /// 根据天赋与策略确定机器人的战斗角色定位（坦克/治疗/近战/法系）
        BotConsumableRole GetBotRole() const;

        /// 根据机器人职业定位计算各属性（力量/敏捷/耐力/智力/精神等）权重
        float GetStatWeight(uint32 statType) const;

        uint32 selectedItemId = 0;

        static const std::vector<uint32> knownFlaskAuras;
        static const std::vector<uint32> knownFoodBuffAuras;
        static const std::vector<uint32> alcoholItemIds;
        static const std::vector<uint32> excludedItemIds;
    };
}
