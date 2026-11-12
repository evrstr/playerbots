#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "ChooseRpgTargetAction.h"
#include "UseItemAction.h"
#include "playerbot/strategy/values/LastMovementValue.h"
#include "SayAction.h"

namespace ai
{
    /// RPG 交互辅助类：提供检查与解析当前 RPG 目标、触发器与相关动作的工具方法
    class RpgHelper : public AiObject
    {
    public:
        /// 构造函数：初始化RPG 交互辅助类
        RpgHelper(PlayerbotAI* ai) : AiObject(ai) {}

        /// 动作执行前的准备钩子
        void BeforeExecute();
        /// 动作执行后的收尾钩子
        void AfterExecute(bool doDelay = true,  bool waitForGroup = false, std::string nextAction = "rpg");
        /// 动作或队列取消时的回调处理
        void OnCancel() { resetFacing(guidP()); if (bot->GetTradeData()) bot->TradeCancel(true); };

        virtual GuidPosition guidP() { return AI_VALUE(GuidPosition, "rpg target"); }
        virtual ObjectGuid guid() { return (ObjectGuid)guidP(); }        
        /// 判断目标是否处于指定的有效距离范围内
        virtual bool InRange() { return AI_VALUE2(float, "distance", "rpg target") <= INTERACTION_DISTANCE * 1.5; }
        /// 设置下一次随机发言或表情前的冷却延迟
        void setDelay(bool waitForGroup);
    private:
        /// 调整机器人朝向面对指定世界对象
        void setFacingTo(GuidPosition guidPosition);
        /// 调整机器人朝向指定角度
        void setFacing(GuidPosition guidPosition);
        /// 重置并清除强制朝向锁定
        void resetFacing(GuidPosition guidPosition);
    };

    /// RPG 启用条件校验类：判断当前目标与环境是否满足执行特定 RPG 子动作的条件
    class RpgEnabled
    {
    public:
        /// 构造函数：初始化RPG 启用条件校验类
        RpgEnabled(PlayerbotAI* ai) { rpg = std::make_unique<RpgHelper>(ai); }
    protected:
        std::unique_ptr<RpgHelper> rpg;
    };

    /// RPG 子动作基类：所有具体城镇/NPC 交互行为（买、卖、修、接任务等）的基类
    class RpgSubAction : public Action, public RpgEnabled
    {
    public:
        /// 构造函数：初始化RPG 子动作基类
        RpgSubAction(PlayerbotAI* ai, std::string name = "rpg sub") : Action(ai, name), RpgEnabled(ai) {}

        // Long range is possible? (检查远距离移动是否可行)
        virtual bool isPossible() override { return rpg->guidP() && rpg->guidP().GetWorldObject(bot->GetInstanceId());}
        // Short range can we do the action now? (短距离内检查当前是否已可执行动作)
        virtual bool isUseful() override { return rpg->InRange(); }

        /// 执行动作主逻辑（RPG 子动作基类）
        virtual bool Execute(Event& event) override { rpg->BeforeExecute();  bool doAction = ai->DoSpecificAction(ActionName(), ActionEvent(event), true); rpg->AfterExecute(doAction, true); DoDelay(); return doAction; }

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const { return "generic rpg action"; };
    protected:
        /// 执行指定的延迟等待时长
        void DoDelay(){ SetDuration(ai->GetAIInternalUpdateDelay()); }
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() { return "none"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) { return event; }
    };        

    /// RPG 原地停留动作：在目标 NPC 旁短暂停留以模拟真实玩家思考交互
    class RpgStayAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 原地停留动作
        RpgStayAction(PlayerbotAI* ai, std::string name = "rpg stay") : RpgSubAction(ai, name) {}

        //virtual bool isUseful() override { return rpg->InRange() && !ai->HasRealPlayerMaster(); }

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "idling near"; };

        /// 执行动作主逻辑（RPG 原地停留动作）
        virtual bool Execute(Event& event) override { rpg->BeforeExecute(); if (bot->GetPlayerMenu()) bot->GetPlayerMenu()->CloseGossip(); rpg->AfterExecute(); DoDelay(); return true; };
    };   

    /// RPG 忙碌动作：在目标点执行模拟工作或闲逛状态
    class RpgWorkAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 忙碌动作
        RpgWorkAction(PlayerbotAI* ai, std::string name = "rpg work") : RpgSubAction(ai, name ) {}

        //virtual bool isUseful() override { return rpg->InRange() && !ai->HasRealPlayerMaster(); }

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "working next to"; };

        /// 执行动作主逻辑（RPG 忙碌动作）
        virtual bool Execute(Event& event) override { rpg->BeforeExecute(); bot->HandleEmoteCommand(EMOTE_STATE_USESTANDING); rpg->AfterExecute(); DoDelay(); return true; };
    };

    /// RPG 表情动作：对目标 NPC 或玩家做出礼貌或应景的表情
    class RpgEmoteAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 表情动作
        RpgEmoteAction(PlayerbotAI* ai, std::string name = "rpg emote") : RpgSubAction(ai, name) {}

       /// 获取当前 RPG 交互目标关联的动作名称
       virtual std::string GetRpgActionName() const override { return "chatting with"; };

        //virtual bool isUseful() override { return rpg->InRange() && !ai->HasRealPlayerMaster(); }

        /// 执行动作主逻辑（RPG 表情动作）
        virtual bool Execute(Event& event) override;
    };

    /// 取消当前 RPG 交互动作：结束当前 RPG 目标交互并清理目标状态
    class RpgCancelAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化取消当前 RPG 交互动作
        RpgCancelAction(PlayerbotAI* ai, std::string name = "rpg cancel") : RpgSubAction(ai, name) {}

        /// 判断当前状态下该动作是否可用/有效（取消当前 RPG 交互动作）
        virtual bool isUseful() override {return rpg->InRange();}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "leaving"; };

        /// 执行动作主逻辑（取消当前 RPG 交互动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 乘坐飞行点动作：与当前飞行管理员交互解锁航线或乘骑飞行点前往目的地
    class RpgTaxiAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 乘坐飞行点动作
        RpgTaxiAction(PlayerbotAI* ai, std::string name = "rpg taxi") : RpgSubAction(ai, name) {}

        /// 判断当前状态下该动作是否可用/有效（RPG 乘坐飞行点动作）
        virtual bool isUseful() override { return rpg->InRange() && !ai->HasRealPlayerMaster() && bot->GetGroup(); }

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "grabbing a taxi from"; };

        /// 执行动作主逻辑（RPG 乘坐飞行点动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 探索飞行点动作：仅与飞行管理员对话以解锁当前地区的飞行点
    class RpgDiscoverAction : public RpgTaxiAction
    {
    public:
        /// 构造函数：初始化RPG 探索飞行点动作
        RpgDiscoverAction(PlayerbotAI* ai, std::string name = "rpg discover") : RpgTaxiAction(ai,name) {}

        /// 判断当前状态下该动作是否可用/有效（RPG 探索飞行点动作）
        virtual bool isUseful() override { return rpg->InRange(); }

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "discovering taxi paths from"; };

        /// 执行动作主逻辑（RPG 探索飞行点动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 接取任务动作：与当前选定的任务发布者交互并接取可用任务
    class RpgStartQuestAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 接取任务动作
        RpgStartQuestAction(PlayerbotAI* ai, std::string name = "rpg start quest") : RpgSubAction(ai, name) {}
        /// 执行动作主逻辑（RPG 接取任务动作）
        virtual bool Execute(Event& event) override { rpg->BeforeExecute();  bool doAction = ai->DoSpecificAction(ActionName(), ActionEvent(event), true); rpg->AfterExecute(doAction, true, ""); DoDelay(); return doAction; }

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "starting a quest at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "accept all quests"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override {WorldPacket p(CMSG_QUESTGIVER_ACCEPT_QUEST); p << rpg->guid(); p.rpos(0);  return  Event("rpg action", p); }
    };

    /// RPG 交付任务动作：向当前选定的任务发布者交付已完成任务并领取奖励
    class RpgEndQuestAction : public RpgStartQuestAction
    {
    public:
        /// 构造函数：初始化RPG 交付任务动作
        RpgEndQuestAction(PlayerbotAI* ai, std::string name = "rpg end quest") : RpgStartQuestAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "handing in a quest at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "talk to quest giver"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { WorldPacket p(CMSG_QUESTGIVER_COMPLETE_QUEST); p << rpg->guid(); p.rpos(0);  return  Event("rpg action", p); }
    };

    /// RPG 购买物品动作：在当前商人 NPC 处购买必需消耗品、弹药或装备
    class RpgBuyAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 购买物品动作
        RpgBuyAction(PlayerbotAI* ai, std::string name = "rpg buy") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "buying items from"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "buy"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", "vendor"); }
    };
   
    /// RPG 出售物品动作：将背包内多余或灰色垃圾物品出售给当前商人 NPC
    class RpgSellAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 出售物品动作
        RpgSellAction(PlayerbotAI* ai, std::string name = "rpg sell") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "selling items to"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "sell"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", "vendor"); }
    };

    /// RPG 拍卖行寄售动作：在拍卖师处将适合拍卖的物品上架寄售
    class RpgAHSellAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 拍卖行寄售动作
        RpgAHSellAction(PlayerbotAI* ai, std::string name = "rpg ah sell") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "posting items on ah at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "ah"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", "vendor"); }
    };

    /// RPG 拍卖行竞购动作：在拍卖师处浏览并购入所需装备或材料
    class RpgAHBuyAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 拍卖行竞购动作
        RpgAHBuyAction(PlayerbotAI* ai, std::string name = "rpg ah buy") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "bidding on items on ah at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "ah bid"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", "vendor"); }
    };

    /// RPG 收取邮件动作：在邮箱处查看并提取邮件附件与金币
    class RpgGetMailAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 收取邮件动作
        RpgGetMailAction(PlayerbotAI* ai, std::string name = "rpg get mail") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "getting mail from"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "mail"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", "take"); }
       
        /// 执行动作主逻辑（RPG 收取邮件动作）
        virtual bool Execute(Event& event) override { bool doAction = RpgSubAction::Execute(event); if (doAction) ai->DoSpecificAction("equip upgrades", event, true); return doAction; }
    };

    /// RPG 修理装备动作：在可修理 NPC 处修复当前受损的装备耐久度
    class RpgRepairAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 修理装备动作
        RpgRepairAction(PlayerbotAI* ai, std::string name = "rpg repair") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "repairing at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "repair"; }
    };

    /// RPG 学习技能动作：在职业或专业训练师处学习当前等级可学的新法术与配方
    class RpgTrainAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 学习技能动作
        RpgTrainAction(PlayerbotAI* ai, std::string name = "rpg train") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "training a new skill at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "trainer"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action",rpg->guidP()); }
    };

    /// RPG 治疗恢复动作：对附近受伤友军进行治疗或自身休整恢复
    class RpgHealAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 治疗恢复动作
        RpgHealAction(PlayerbotAI* ai, std::string name = "rpg heal") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "healing"; };

        /// 执行动作主逻辑（RPG 治疗恢复动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 绑定炉石动作：在旅店老板处将炉石绑定到当前旅店
    class RpgHomeBindAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 绑定炉石动作
        RpgHomeBindAction(PlayerbotAI* ai, std::string name = "rpg home bind") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "making this inn my home at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "home"; }
    };

    /// RPG 战场排队动作：与战场军官对话排队进入战场
    class RpgQueueBgAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 战场排队动作
        RpgQueueBgAction(PlayerbotAI* ai, std::string name = "rpg queue bg") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "queing for a battleground at"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { SET_AI_VALUE(uint32, "bg type", (uint32)AI_VALUE(BattleGroundTypeId, "rpg bg type")); return "free bg join"; }
    };

    /// RPG 购买公会登记表动作：与公会注册员交互购买公会创建登记表
    class RpgBuyPetitionAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 购买公会登记表动作
        RpgBuyPetitionAction(PlayerbotAI* ai, std::string name = "rpg buy petition") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "buying a guild pettition from"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "buy petition"; }
    };

    /// RPG 交互游戏对象动作：点击或使用作为 RPG 目标的游戏对象（如篝火、邮箱、锻炉等）
    class RpgUseAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 交互游戏对象动作
        RpgUseAction(PlayerbotAI* ai, std::string name = "rpg use") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "using"; };

        /// 执行动作主逻辑（RPG 交互游戏对象动作）
        virtual bool Execute(Event& event) override {
            rpg->BeforeExecute();
            bool doAction = ai->DoSpecificAction(ActionName(), ActionEvent(event), true);
            rpg->AfterExecute(true);
            DoDelay();
            return doAction;
        }

    private:
        /// 判断当前状态下该动作是否可用/有效（RPG 交互游戏对象动作）
        virtual bool isUseful() override;

        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override
        {
            if (rpg->guidP().IsGameObject())
            {
                if (rpg->guidP().GetGameObject(bot->GetInstanceId()) && rpg->guidP().GetGameObject(bot->GetInstanceId())->GetGoType() == GAMEOBJECT_TYPE_CHEST)
                    return "add all loot";

                return "use";
            }

            return "rpg item";
        }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", chat->formatWorldobject(rpg->guidP().GetWorldObject(bot->GetInstanceId()))); }
    };

    /// RPG AI 对话动作：向周边玩家发送由对话系统或 LLM 生成的自然角色扮演发言
    class RpgAIChatAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG AI 对话动作
        RpgAIChatAction(PlayerbotAI* ai, std::string name = "rpg ai chat") : RpgSubAction(ai, name) {}

        /// 处理通过命令手动触发的机器人发言
        void ManualChat(GuidPosition target, const std::string& line);

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "ai talking with"; };
    private:
        /// 判断当前状态下该动作是否可用/有效（RPG AI 对话动作）
        virtual bool isUseful() override;

        /// 按预设概率与延迟让机器人说出指定文本台词
        bool SpeakLine();
        /// 等待异步对话生成结果返回
        bool WaitForLines();
        /// 向文本生成器或 LLM 请求新的对话回复内容
        bool RequestNewLines();
        /// 执行动作主逻辑（RPG AI 对话动作）
        virtual bool Execute(Event& event) override;

        std::queue<delayedPacket> packets;
        futurePackets futPackets;
    };

    /// RPG 施法动作：在城镇交互过程中对目标或自身施放休闲/辅助法术
    class RpgSpellAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 施法动作
        RpgSpellAction(PlayerbotAI* ai, std::string name = "rpg spell") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "casting a spell on"; };
    private:
        /// 判断当前状态下该动作是否可用/有效（RPG 施法动作）
        virtual bool isUseful() override { return true; }
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "cast random spell"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", chat->formatWorldobject(rpg->guidP().GetWorldObject(bot->GetInstanceId()))); }
    };

    /// RPG 制作物品动作：在锻炉、炼金台等处利用专业技能合成或制造物品
    class RpgCraftAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 制作物品动作
        RpgCraftAction(PlayerbotAI* ai, std::string name = "rpg craft") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return rpg->guidP().IsGameObject() ? "crafting an item at" : "crafting an item near"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "craft random item"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { return Event("rpg action", chat->formatWorldobject(rpg->guidP().GetWorldObject(bot->GetInstanceId()))); }
    };

    /// RPG 赠送实用物品动作：发现附近玩家缺少可用消耗品或装备时主动发起交易赠予
    class RpgTradeUsefulAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 赠送实用物品动作
        RpgTradeUsefulAction(PlayerbotAI* ai, std::string name = "rpg trade useful") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "trading an item to"; };

        /// 判断指定物品是否正处于交易窗口待交易状态
        bool IsTradingItem(uint32 entry);

        /// 执行动作主逻辑（RPG 赠送实用物品动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 附魔交互动作：主动为自己或附近友军的装备施加专业附魔
    class RpgEnchantAction : public RpgTradeUsefulAction
    {
    public:
        /// 构造函数：初始化RPG 附魔交互动作
        RpgEnchantAction(PlayerbotAI* ai, std::string name = "rpg enchant") : RpgTradeUsefulAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "enchanting an item for"; };

        /// 执行动作主逻辑（RPG 附魔交互动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 发起决斗动作：在城外安全区域向附近玩家发起切磋决斗请求
    class RpgDuelAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 发起决斗动作
        RpgDuelAction(PlayerbotAI* ai, std::string name = "rpg duel") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "starting a duel with"; };

        /// 判断当前状态下该动作是否可用/有效（RPG 发起决斗动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（RPG 发起决斗动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 使用物品动作：在 RPG 状态中使用背包内指定的交互物品
    class RpgItemAction : public UseAction, public RpgEnabled
    {
    public:
        /// 构造函数：初始化RPG 使用物品动作
        RpgItemAction(PlayerbotAI* ai, std::string name = "rpg item") : UseAction(ai, name), RpgEnabled(ai) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const { return "using an item on"; };

        // Long range is possible? (检查远距离移动是否可行)
        virtual bool isPossible() override { return rpg->guidP() && rpg->guidP().GetWorldObject(bot->GetInstanceId()); }
        // Short range can we do the action now? (短距离内检查当前是否已可执行动作)
        virtual bool isUseful() override { return !urand(0,3) || rpg->InRange(); }

        /// 执行动作主逻辑（RPG 使用物品动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 法术点击交互动作：对支持 SpellClick 机制的 NPC 或载具触发法术交互
    class RpgSpellClickAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 法术点击交互动作
        RpgSpellClickAction(PlayerbotAI* ai, std::string name = "rpg spell click") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "spellclicking"; };

        /// 执行动作主逻辑（RPG 法术点击交互动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 闲聊对话动作：与选定 NPC 进行普通对话选项交互
    class RpgGossipTalkAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 闲聊对话动作
        RpgGossipTalkAction(PlayerbotAI* ai, std::string name = "rpg gossip talk") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "gossiping with"; };
    private:
        /// 获取对应的 RPG 子动作名称
        virtual std::string ActionName() override { return "gossip hello"; }
        /// 构造并发送触发指定动作的内部事件
        virtual Event ActionEvent(Event event) override { WorldPacket p(CMSG_GOSSIP_SELECT_OPTION); p << rpg->guid(); p.rpos(0); return Event("rpg action", p); }
    };

    /// RPG 银行存物动作：在银行管理员处将多余材料或贵重物品存入个人银行
    class RpgBankDepositAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 银行存物动作
        RpgBankDepositAction(PlayerbotAI* ai, std::string name = "rpg bank deposit") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "depositing items at"; };

        /// 执行动作主逻辑（RPG 银行存物动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 银行取物动作：从个人银行中取出当前任务或制作所需的物品
    class RpgBankWithdrawAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 银行取物动作
        RpgBankWithdrawAction(PlayerbotAI* ai, std::string name = "rpg bank withdraw") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "withdrawing items from"; };

        /// 执行动作主逻辑（RPG 银行取物动作）
        virtual bool Execute(Event& event) override;
    };

#ifndef MANGOSBOT_ZERO
    /// RPG 公会银行存物动作：将可共享物资存入公会银行
    class RpgGuildBankDepositAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 公会银行存物动作
        RpgGuildBankDepositAction(PlayerbotAI* ai, std::string name = "rpg guild bank deposit") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "depositing items in guild bank at"; };

        /// 执行动作主逻辑（RPG 公会银行存物动作）
        virtual bool Execute(Event& event) override;
    };

    /// RPG 公会银行取物动作：从公会银行提取所需的消耗品或制造材料
    class RpgGuildBankWithdrawAction : public RpgSubAction
    {
    public:
        /// 构造函数：初始化RPG 公会银行取物动作
        RpgGuildBankWithdrawAction(PlayerbotAI* ai, std::string name = "rpg guild bank withdraw") : RpgSubAction(ai, name) {}

        /// 获取当前 RPG 交互目标关联的动作名称
        virtual std::string GetRpgActionName() const override { return "withdrawing items from guild bank at"; };

        /// 执行动作主逻辑（RPG 公会银行取物动作）
        virtual bool Execute(Event& event) override;
    };
#endif
}
