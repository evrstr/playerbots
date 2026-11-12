#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 添加指定拾取目标动作：将指定可拾取尸体或宝箱加入待拾取列表
    class AddLootAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化添加指定拾取目标动作
        AddLootAction(PlayerbotAI* ai) : ChatCommandAction(ai, "add loot") {}
        /// 判断当前状态下该动作是否可用/有效（添加指定拾取目标动作）
        virtual bool isUseful() override;

    private:
        /// 执行动作主逻辑（添加指定拾取目标动作）
        bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "add loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This action allows the bot to add a specific lootable object (like a corpse or chest) to its stored loot list.\n"
                   "The bot will move to and open this object later when it's safe and within range.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"available loot"}; }
#endif 
    };

    /// 添加全部拾取目标动作：扫描并将附近所有可拾取对象加入待拾取列表
    class AddAllLootAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化添加全部拾取目标动作
        AddAllLootAction(PlayerbotAI* ai, std::string name = "add all loot") : ChatCommandAction(ai, name) {}
        /// 判断当前状态下该动作是否可用/有效（添加全部拾取目标动作）
        virtual bool isUseful() override;

    protected:
        /// 将指定目标 GUID 加入战利品待拾取队列
        virtual bool AddLoot(Player* requester, ObjectGuid guid);
        /// 执行动作主逻辑（添加全部拾取目标动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "add all loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot add all nearby lootable objects (like corpses or chests) to its stored loot list.\n"
                   "The bot will move to and open these objects later, respecting group rules and bag space.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"nearest game objects no los", "nearest corpses", "bag space"}; }
#endif 
    };

    /// 添加采集拾取目标动作：将需要采集技能的矿点、草药等目标加入拾取列表
    class AddGatheringLootAction : public AddAllLootAction
    {
    public:
        /// 构造函数：初始化添加采集拾取目标动作
        AddGatheringLootAction(PlayerbotAI* ai) : AddAllLootAction(ai, "add gathering loot") {}

    private:
        /// 将指定目标 GUID 加入战利品待拾取队列
        bool AddLoot(Player* requester, ObjectGuid guid) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "add gathering loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This action directs the bot to add lootable objects that require specific gathering skills (like herbs or minerals) to its stored loot list.\n"
                   "The bot will move to and gather from these objects later if it's safe and within range.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"nearest game objects no los", "bag space"}; }
#endif 
    };
}
