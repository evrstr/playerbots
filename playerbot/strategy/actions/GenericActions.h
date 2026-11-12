#pragma once
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"
#include "RemoveAuraAction.h"

namespace ai
{
    /// 近战攻击动作：向当前目标靠近并启动自动近战攻击
    class MeleeAction : public AttackAction 
    {
    public:
        /// 构造函数：初始化近战攻击动作
        MeleeAction(PlayerbotAI* ai) : AttackAction(ai, "melee") {}
        /// 获取当前动作的目标名称标识（近战攻击动作）
        virtual std::string GetTargetName() override { return "current target"; }
        /// 判断当前状态下该动作是否可用/有效（近战攻击动作）
        virtual bool isUseful() override;
    };

    /// 使用圣光之泉动作：生命值下降时自动移动并点击牧师放置的圣光之泉回血
    class UseLightwellAction : public MovementAction
    {
    public:
        /// 构造函数：初始化使用圣光之泉动作
        UseLightwellAction(PlayerbotAI* ai) : MovementAction(ai, "lightwell") {}
        /// 获取动作产生的仇恨类型
        ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_NONE; }

        /// 判断当前状态下该动作是否可用/有效（使用圣光之泉动作）
        bool isUseful() override
        {
            if (MovementAction::isUseful())
            {
                return (bot->getClass() == CLASS_PRIEST || bot->GetGroup()) && bot->GetHealthPercent() < sPlayerbotAIConfig.mediumHealth && !ai->HasAura("lightwell renew", bot);
            }

            return false;
        }

        /// 判断执行该动作的前置条件是否满足（使用圣光之泉动作）
        bool isPossible() override
        {
            std::list<ObjectGuid> closeObjects = AI_VALUE(std::list<ObjectGuid>, "nearest game objects no los");
            if (closeObjects.empty())
                return false;

            for (std::list<ObjectGuid>::iterator i = closeObjects.begin(); i != closeObjects.end(); ++i)
            {
                GameObject* go = ai->GetGameObject(*i);
                if (!go)
                    continue;

                if (!(go->GetEntry() == 181106 || go->GetEntry() == 181165 || go->GetEntry() == 181102 || go->GetEntry() == 181105))
                    continue;

                if (!sServerFacade.isSpawned(go) || go->GetGoState() != GO_STATE_READY || !bot->CanInteract(go))
                    continue;

                if (Unit* owner = go->GetOwner())
                {
                    if (owner->GetTypeId() == TYPEID_PLAYER)
                    {
                        Player* ownerPlayer = (Player*)owner;
                        if (!ownerPlayer)
                            return false;

                        if (!ownerPlayer->IsInGroup(bot))
                            continue;
                    }
                }

                lightwellGameObject = *i;
                return MovementAction::isPossible();
            }

            return false;
        }
        
        /// 执行动作主逻辑（使用圣光之泉动作）
        virtual bool Execute(Event& event) override
        {
            GameObject* go = ai->GetGameObject(lightwellGameObject);
            if (go)
            {
                if (bot->IsWithinDistInMap(go, INTERACTION_DISTANCE, false))
                {
                    WorldPacket data(CMSG_GAMEOBJ_USE);
                    data << go->GetObjectGuid();
                    bot->GetSession()->HandleGameObjectUseOpcode(data);
                    return true;
                }
                else
                {
                    return MoveNear(go, 4.0f);
                }
            }

            return false;
        }

    private:
        ObjectGuid lightwellGameObject;
    };

    /// 聊天命令动作基类：所有由主人聊天消息触发的机器人动作的基类
    class ChatCommandAction : public Action
    {
    public:
        /// 构造函数：初始化聊天命令动作基类
        ChatCommandAction(PlayerbotAI* ai, std::string name, uint32 duration = sPlayerbotAIConfig.reactDelay) : Action(ai, name, duration) {}
    public:
        /// 执行动作主逻辑（聊天命令动作基类）
        virtual bool Execute(Event& event) override { return true; }
    };

    /// 更新策略依赖动作：根据策略变化同步启用或移除关联的策略集
    class UpdateStrategyDependenciesAction : public Action
    {
        /// 待更新策略结构体：保存策略更新目标状态及策略变更表达式
        struct StrategyToUpdate
        {
            /// 构造函数：初始化待更新策略结构体
            StrategyToUpdate(BotState inState, std::string inStrategy, std::vector<std::string> inStrategiesRequired = {})
            : state(inState)
            , name(inStrategy)
            , strategiesRequired(inStrategiesRequired) {}

            BotState state;
            std::string name;
            std::vector<std::string> strategiesRequired;
        };

     public:
         /// 构造函数：初始化更新策略依赖动作
         UpdateStrategyDependenciesAction(PlayerbotAI* ai, std::string name = "update strategy dependencies") : Action(ai, name) {}
         /// 执行动作主逻辑（更新策略依赖动作）
         bool Execute(Event& event) override;
         /// 判断当前状态下该动作是否可用/有效（更新策略依赖动作）
         bool isUseful() override;

    protected:
        std::vector<StrategyToUpdate> strategiesToUpdate;

    private:
        std::vector<const StrategyToUpdate*> strategiesToAdd;
        std::vector<const StrategyToUpdate*> strategiesToRemove;
    };

    /// 取消拯救祝福动作：坦克等不需要降低仇恨的角色自动点掉拯救祝福
    class RemoveBlessingOfSalvationAction : public RemoveAuraAction
    {
    public:
        /// 构造函数：初始化取消拯救祝福动作
        RemoveBlessingOfSalvationAction(PlayerbotAI* ai) : RemoveAuraAction(ai, "blessing of salvation") {}
    };

    /// 取消强效拯救祝福动作：自动点掉强效拯救祝福以免影响仇恨建立
    class RemoveGreaterBlessingOfSalvationAction : public RemoveAuraAction
    {
    public:
        /// 构造函数：初始化取消强效拯救祝福动作
        RemoveGreaterBlessingOfSalvationAction(PlayerbotAI* ai) : RemoveAuraAction(ai, "greater blessing of salvation") {}
    };

    /// 初始化宠物动作：在召唤或进入游戏后初始化宠物状态与默认技能自动施放
    class InitializePetAction : public Action
    {
    public:
        /// 构造函数：初始化初始化宠物动作
        InitializePetAction(PlayerbotAI* ai) : Action(ai, "initialize pet") {}
        /// 执行动作主逻辑（初始化宠物动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（初始化宠物动作）
        bool isUseful() override;
    };

    /// 设置宠物行为动作：调整宠物的攻击/防御/被动姿态或特定行为状态
    class SetPetAction : public Action
    {
    public:
        /// 构造函数：初始化设置宠物行为动作
        SetPetAction(PlayerbotAI* ai) : Action(ai, "pet") {}
        /// 执行动作主逻辑（设置宠物行为动作）
        bool Execute(Event& event) override;
    };
}
