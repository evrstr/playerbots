#pragma once
#include "GenericActions.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/RandomItemMgr.h"

namespace ai
{
    // This class bypasses the requirement for a bot to have a key item in their inventory when opening a lock. (此类职业开锁时无需在背包中持有对应钥匙物品。)
    class BotUseItemSpell : public Spell
    {
    public:
        /// 构造函数：初始化机器人使用物品施法包装类
        BotUseItemSpell(WorldObject* caster, SpellEntry const* info, uint32 triggeredFlags, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr, bool itemCheats = false) : Spell(caster, info, triggeredFlags, originalCasterGUID, triggeredBy), itemCheats(itemCheats) {};

        /// 创建并初始化目标对象或实例
        static BotUseItemSpell* Create(WorldObject* caster, SpellEntry const* info, uint32 triggeredFlags, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr, bool itemCheats = false)
        {
            if (!caster || !info)
                return nullptr;

            if (info != sSpellTemplate.LookupEntry<SpellEntry>(info->Id))
                return nullptr;

            return new BotUseItemSpell(caster, info, triggeredFlags, originalCasterGUID, triggeredBy, itemCheats);
        }

        /// 强制立即触发指定法术的施法流程
        SpellCastResult ForceSpellStart(SpellCastTargets const* targets, Aura* triggeredByAura = nullptr);
        /// 检查机器人是否具备开启目标锁具的技能或钥匙条件
        bool OpenLockCheck();

    private:
        bool itemCheats;
    };

    /// 使用物品指令基类动作：解析物品名称或链接并使用背包内对应物品或交互对象
    class UseAction : public ChatCommandAction, public Qualified
    {
    public:
        /// 构造函数：初始化使用物品指令基类动作
        UseAction(PlayerbotAI* ai, std::string name = "use", uint32 duration = sPlayerbotAIConfig.reactDelay) : ChatCommandAction(ai, name, duration), Qualified() {}

    public:
        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        virtual bool ShouldReactionInterruptCast() const override { return true; }

    protected:
        /// 执行动作主逻辑（使用物品指令基类动作）
        virtual bool Execute(Event& event) override;
        /// 使用指定的背包物品或对其目标施放效果
        bool UseItem(Player* requester, uint32 itemId, Unit* target = nullptr);
        /// 使用指定的背包物品或对其目标施放效果
        bool UseItem(Player* requester, uint32 itemId, GameObject* target);
        /// 使用指定的背包物品或对其目标施放效果
        bool UseItem(Player* requester, uint32 itemId, Item* target);
        /// 与指定的游戏对象交互（如打开宝箱、点击矿点或机关）
        bool UseGameObject(Player* requester, Event& event, GameObject* gameObject);
        
        //void TellConsumableUse(Player* requester, Item* item, std::string action, float percent);

        /// 检查指定物品是否正处于冷却时间中
        bool HasItemCooldown(uint32 itemId) const;

    private:
        /// 执行使用物品的底层施法、目标校验与冷却处理
        bool UseItemInternal(Player* requester, uint32 itemId, Unit* target, GameObject* gameObjectTarget, Item* itemTarget);
        /// 使用可触发新任务的背包起始任务物品
        bool UseQuestGiverItem(Player* requester, Item* item);
        /// 打开或使用背包中的容器类物品
        bool OpenItem(Player* requester, Item* item);
#ifndef MANGOSBOT_ZERO
        /// 对带插槽的装备镶嵌指定的宝石物品
        bool UseGemItem(Player* requester, Item* item, Item* gem, bool replace = false);
#endif
    };

    /// 按物品 ID 列表使用动作：按预设的物品 ID 列表依次查找并使用背包内可用消耗品
    class UseItemIdAction : public UseAction
    {
    public:
        /// 构造函数：初始化按物品 ID 列表使用动作
        UseItemIdAction(PlayerbotAI* ai, std::string name = "use id", uint32 duration = sPlayerbotAIConfig.reactDelay) : UseAction(ai, name, duration) {}
        /// 判断执行该动作的前置条件是否满足（按物品 ID 列表使用动作）
        virtual bool isPossible() override;
        /// 判断当前状态下该动作是否可用/有效（按物品 ID 列表使用动作）
        virtual bool isUseful() override;

    protected:
        /// 执行动作主逻辑（按物品 ID 列表使用动作）
        virtual bool Execute(Event& event) override;
        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() { return getQualifier().empty() ? 0 : getMultiQualifierInt(getQualifier(),0, ","); }
        /// 获取当前动作的目标单位（按物品 ID 列表使用动作）
        virtual Unit* GetTarget() override { return nullptr; }
    };

    /// 对目标使用物品动作：按物品 ID 列表查找物品并对指定友好或敌对目标使用
    class UseTargetedItemIdAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化对目标使用物品动作
        UseTargetedItemIdAction(PlayerbotAI* ai, std::string name, uint32 duration = sPlayerbotAIConfig.reactDelay) : UseItemIdAction(ai, name, duration) {}
        /// 获取当前动作的目标单位（对目标使用物品动作）
        virtual Unit* GetTarget() override { return Action::GetTarget(); }
        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override { return  0; }
    };

    /// 使用法术类物品动作：使用触发特定法术效果（如任务道具、饰品）的物品
    class UseSpellItemAction : public UseAction 
    {
    public:
        /// 构造函数：初始化使用法术类物品动作
        UseSpellItemAction(PlayerbotAI* ai, std::string name) : UseAction(ai, name) {}
        /// 判断当前状态下该动作是否可用/有效（使用法术类物品动作）
        virtual bool isUseful() override;
    };

    /// 使用药水基类动作：按生命/法力需求及冷却时间控制各类药水的使用
    class UsePotionAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用药水基类动作
        UsePotionAction(PlayerbotAI* ai, std::string name, SpellEffects effect) : UseItemIdAction(ai, name), effect(effect) {}

        /// 判断当前状态下该动作是否可用/有效（使用药水基类动作）
        bool isUseful() override { return UseItemIdAction::isUseful() && AI_VALUE2(bool, "combat", "self target"); }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override
        {
            std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", getName());
            if (items.empty())
            {
                return sRandomItemMgr.GetRandomPotion(bot->GetLevel(), effect);
            }

            return items.front()->GetProto()->ItemId;
        }

        /// 执行动作主逻辑（使用药水基类动作）
        bool Execute(Event& event) override
        {
            // Check the chance of using a potion (only in pvp) (检查使用药水的触发概率（仅限 PvP）)
#ifdef MANGOSBOT_ZERO
            const bool shouldUsePotion = !ai->IsInPvp() || frand(0.0f, 1.0f) < sPlayerbotAIConfig.usePotionChance;
#else
            const bool shouldUsePotion = !bot->InArena() && (!ai->IsInPvp() || frand(0.0f, 1.0f) < sPlayerbotAIConfig.usePotionChance);
#endif
            if (shouldUsePotion)
            {
                return UseItemIdAction::Execute(event);
            }
            else
            {
                // Force potion cooldown to prevent spamming this action (强制触发药水冷却以防止频繁重复执行)
                const ItemPrototype* proto = sObjectMgr.GetItemPrototype(GetItemId());
                if (proto)
                {
                    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
                    {
                        _Spell const& spellData = proto->Spells[i];
                        if (spellData.SpellId)
                        {
                            // wrong triggering type (触发器类型不匹配)
#ifdef MANGOSBOT_ZERO
                            if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE && spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
                            if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE)
#endif
                            {
                                continue;
                            }

                            const SpellEntry* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellData.SpellId);
                            if (spellInfo)
                            {
                                bot->RemoveSpellCooldown(*spellInfo, false);
                                bot->AddCooldown(*spellInfo, proto, false);
                                break;
                            }
                        }
                    }
                }
            }

            return true;
        }

    private:
        SpellEffects effect;
    };

    /// 使用治疗药水动作：生命值危险时从背包查找并使用最高等级治疗药水
    class UseHealingPotionAction : public UsePotionAction
    {
    public:
        /// 构造函数：初始化使用治疗药水动作
        UseHealingPotionAction(PlayerbotAI* ai) : UsePotionAction(ai, "healing potion", SPELL_EFFECT_HEAL) {}
    };

    /// 使用法力药水动作：法力值不足时从背包查找并使用最高等级法力药水
    class UseManaPotionAction : public UsePotionAction
    {
    public:
        /// 构造函数：初始化使用法力药水动作
        UseManaPotionAction(PlayerbotAI* ai) : UsePotionAction(ai, "mana potion", SPELL_EFFECT_ENERGIZE) {}
    };

    /// 使用炉石动作：使用炉石将机器人传送回绑定的旅店位置
    class UseHearthStoneAction : public UseAction
    {
    public:
        /// 构造函数：初始化使用炉石动作
        UseHearthStoneAction(PlayerbotAI* ai) : UseAction(ai, "hearthstone", 10000U) {}

        /// 执行动作主逻辑（使用炉石动作）
        virtual bool Execute(Event& event) override;

        /// 判断当前状态下该动作是否可用/有效（使用炉石动作）
        bool isUseful() override;
    
        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptMovement() const override { return true; }
    };

    /// 使用治疗石动作：危机时刻优先使用术士制造的各类治疗石
    class UseHealthstoneAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用治疗石动作
        UseHealthstoneAction(PlayerbotAI* ai) : UseItemIdAction(ai, "healthstone") {}

        /// 判断当前状态下该动作是否可用/有效（使用治疗石动作）
        bool isUseful() override { return UseItemIdAction::isUseful() && AI_VALUE2(bool, "combat", "self target"); }

        /// 获取关联的物品模板 ID
        uint32 GetItemId() override
        {
            std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", getName());
            if (items.empty())
            {
                const uint32 level = bot->GetLevel();
                if(level < 12)
                {
                    return 5512;
                }
                else if(level >= 12 && level < 24)
                {
                    return 5511;
                }
                else if(level >= 24 && level < 36)
                {
                    return 5509;
                }
                else if(level >= 36 && level < 48)
                {
                    return 5510;
                }
                else if(level >= 48 && level < 61)
                {
                    return 9421;
                }
                else if(level >= 61 && level < 63)
                {
                    return 22103;
                }
                else if(level >= 63 && level < 71)
                {
                    return 36889;
                }
                else
                {
                    return 36892;
                }
            }

            return items.front()->GetProto()->ItemId;
        }

        /// 执行动作主逻辑（使用治疗石动作）
        bool Execute(Event& event) override
        {
            // Check the chance of using a healthstone (only in pvp) (检查使用治疗石的触发概率（仅限 PvP）)
            const bool shouldUsePotion = !ai->IsInPvp() || frand(0.0f, 1.0f) < sPlayerbotAIConfig.usePotionChance;
            if (shouldUsePotion)
            {
                return UseItemIdAction::Execute(event);
            }
            else
            {
                // Force potion cooldown to prevent spamming this action (强制触发药水冷却以防止频繁重复执行)
                const ItemPrototype* proto = sObjectMgr.GetItemPrototype(GetItemId());
                if (proto)
                {
                    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
                    {
                        _Spell const& spellData = proto->Spells[i];
                        if (spellData.SpellId)
                        {
                            // wrong triggering type (触发器类型不匹配)
#ifdef MANGOSBOT_ZERO
                            if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE && spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
                            if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE)
#endif
                            {
                                continue;
                            }

                            const SpellEntry* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellData.SpellId);
                            if (spellInfo)
                            {
                                bot->RemoveSpellCooldown(*spellInfo, false);
                                bot->AddCooldown(*spellInfo, proto, false);
                                break;
                            }
                        }
                    }
                }
            }

            return true;
        }
    };

    /// 使用鞭根块茎动作：在战斗中使用费伍德森林采集的鞭根块茎恢复生命
    class UseWhipperRootTuberAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用鞭根块茎动作
        UseWhipperRootTuberAction(PlayerbotAI* ai) : UseItemIdAction(ai, "whipper root tuber") {}

        /// 判断当前状态下该动作是否可用/有效（使用鞭根块茎动作）
        bool isUseful() override { return bot->GetLevel() >= 45 && UseItemIdAction::isUseful() && AI_VALUE2(bool, "combat", "self target"); }

        /// 获取关联的物品模板 ID
        uint32 GetItemId() override { return 11951; }
    };

    /// 使用抗毒药剂动作：自身中毒时使用抗毒药剂或强力抗毒药剂解毒
    class UseAntiVenomAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用抗毒药剂动作
        UseAntiVenomAction(PlayerbotAI* ai) : UseItemIdAction(ai, "anti-venom") {}

        /// 判断当前状态下该动作是否可用/有效（使用抗毒药剂动作）
        bool isUseful() override
        {
            if (!UseItemIdAction::isUseful())
                return false;

            return ai->HasAuraToDispel(bot, DISPEL_POISON);
        }

        /// 获取关联的物品模板 ID
        uint32 GetItemId() override
        {
            int firstAidSkillValue = bot->GetSkillValue(129);
            if (firstAidSkillValue >= 300 && bot->HasItemCount(19440, 1))
                return 19440;
            if (firstAidSkillValue >= 130 && bot->HasItemCount(6453, 1))
                return 6453;
            if (firstAidSkillValue >= 80 && bot->HasItemCount(6452, 1))
                return 6452;
            return 0;
        }
    };

    /// 学习随机配方动作：自动使用背包中已拾取且可学习的专业图纸或配方
    class UseRandomRecipeAction : public UseAction
    {
    public:
        /// 构造函数：初始化学习随机配方动作
        UseRandomRecipeAction(PlayerbotAI* ai) : UseAction(ai, "random recipe", 6000U) {}

        /// 判断当前状态下该动作是否可用/有效（学习随机配方动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（学习随机配方动作）
        virtual bool isPossible() override {return AI_VALUE2(uint32,"item count", "recipe") > 0; }
      
        /// 执行动作主逻辑（学习随机配方动作）
        virtual bool Execute(Event& event) override;

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptMovement() const override { return true; }
    };

    /// 打开随机容器物品动作：打开背包中的箱子、包裹或任务容器物品
    class OpenRandomItemAction : public UseAction
    {
    public:
        /// 构造函数：初始化打开随机容器物品动作
        OpenRandomItemAction(PlayerbotAI* ai) : UseAction(ai, "open random item") {}

        /// 判断当前状态下该动作是否可用/有效（打开随机容器物品动作）
        virtual bool isUseful() override;

        /// 判断执行该动作的前置条件是否满足（打开随机容器物品动作）
        virtual bool isPossible() override { return AI_VALUE2(uint32, "item count", "open") > 0; }

        /// 执行动作主逻辑（打开随机容器物品动作）
        virtual bool Execute(Event& event) override;

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptMovement() const override { return true; }
    };

    /// 使用随机任务物品动作：尝试使用背包中可主动触发的任务道具
    class UseRandomQuestItemAction : public UseAction
    {
    public:
        /// 构造函数：初始化使用随机任务物品动作
        UseRandomQuestItemAction(PlayerbotAI* ai) : UseAction(ai, "use random quest item") {}

        /// 判断当前状态下该动作是否可用/有效（使用随机任务物品动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（使用随机任务物品动作）
        virtual bool isPossible() override { return AI_VALUE2(uint32, "item count", "quest") > 0;}

        /// 执行动作主逻辑（使用随机任务物品动作）
        virtual bool Execute(Event& event) override;

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptMovement() const override { return true; }
    };

    // goblin sappers (地精工兵)
    class UseGoblinSapperChargeAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用地精工兵炸药动作
        UseGoblinSapperChargeAction(PlayerbotAI* ai) : UseItemIdAction(ai, "goblin sapper") {}
        /// 判断当前状态下该动作是否可用/有效（使用地精工兵炸药动作）
        virtual bool isUseful() override { return UseItemIdAction::isUseful() && bot->GetSkillValue(202) >= 205 && bot->GetHealth() > 1000; }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override
        { 
#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
                return false;
#endif
            return (bot->GetLevel() >= 68) ? 23827 : 10646; 
        }
    };

    // oil of immolation (献祭之油)
    class UseOilOfImmolationAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用献祭之油动作
        UseOilOfImmolationAction(PlayerbotAI* ai) : UseItemIdAction(ai, "oil of immolation") {}
        /// 判断当前状态下该动作是否可用/有效（使用献祭之油动作）
        virtual bool isUseful() override
        {
#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
                return false;
#endif
            return UseItemIdAction::isUseful() && bot->GetLevel() >= 31 && !ai->HasAura(11350, bot);
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override { return 8956; }
    };

    // stoneshield potion (石盾药水)
    class UseStoneshieldPotionAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用石盾药水动作
        UseStoneshieldPotionAction(PlayerbotAI* ai) : UseItemIdAction(ai, "stoneshield potion") {}
        /// 判断当前状态下该动作是否可用/有效（使用石盾药水动作）
        virtual bool isUseful() override
        {
#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
                return false;
#endif
            return UseItemIdAction::isUseful() && bot->GetLevel() >= 46 && !ai->HasAura(17540, bot);
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override { return 13455; }
    };

    /// 使用战场战旗动作：在战场内插下联盟或部落军旗为附近友军提供增益
    class UseBgBannerAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用战场战旗动作
        UseBgBannerAction(PlayerbotAI* ai) : UseItemIdAction(ai, "bg banner") {}

        /// 判断当前状态下该动作是否可用/有效（使用战场战旗动作）
        virtual bool isUseful() override
        {
            if (!UseItemIdAction::isUseful())
                return false;

            if (!bot->InBattleGround() || bot->GetLevel() < 60 || !bot->IsInCombat())
                return false;

            std::list<ObjectGuid> units = *context->GetValue<std::list<ObjectGuid> >("nearest npcs no los");
            for (std::list<ObjectGuid>::iterator i = units.begin(); i != units.end(); i++)
            {
                Unit* unit = ai->GetUnit(*i);
                if (!unit)
                    continue;

                if (bot->GetTeam() == HORDE && unit->GetEntry() == 14466)
                    return false;

                if (bot->GetTeam() == ALLIANCE && unit->GetEntry() == 14465)
                    return false;
            }

            return true;
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override
        {
            return bot->GetTeam() == ALLIANCE ? 18606 : 18607;
        }

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptMovement() const override { return true; }
    };

    /// 使用火箭靴动作：在撤退、追击或扛旗时激活工程学火箭靴加速
    class UseRocketBootsAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用火箭靴动作
        UseRocketBootsAction(PlayerbotAI* ai) : UseItemIdAction(ai, "rocket boots") {}

        /// 判断当前状态下该动作是否可用/有效（使用火箭靴动作）
        virtual bool isUseful() override
        {
            if(!UseItemIdAction::isUseful())
                return false;

            if (ai->HasAnyAuraOf(bot, "sprint", "speed", "goblin rocket boots", "dash", NULL))
                return false;

            return true;
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override
        {
            return 7189;
        }
    };

    /// 使用绷带动作：脱离受击状态且安全时对自己或队友使用急救绷带回血
    class UseBandageAction : public UseTargetedItemIdAction
    {
    public:
        /// 构造函数：初始化使用绷带动作
        UseBandageAction(PlayerbotAI* ai) : UseTargetedItemIdAction(ai, "use bandage", 8000U) {}

        /// 判断当前状态下该动作是否可用/有效（使用绷带动作）
        virtual bool isUseful() override
        {
            if (!UseTargetedItemIdAction::isUseful())
                return false;

            if (bot->HasAura(11196))
                return false;

            if (AI_VALUE(uint8, "my attacker count") > 0 || bot->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                return false;

            if (bot->GetSkillValue(129) < 1)
                return false;
              
            // Prevent tanks from bandaging in dungeons and raids (防止坦克在地下城和团队副本中使用绷带)
            if (ai->IsTank(bot) && ai->IsStateActive(BotState::BOT_STATE_COMBAT))
            {
                const Map* map = bot->GetMap();
                if (map->IsDungeon() || map->IsRaid())
                {
                    return false;
                }
            }

            // Do not use consumable if bot can heal self or has preheal strategy (若机器人可自我治疗或启用了预治疗策略，则不使用消耗品)
            if (ai->IsHeal(bot) && (ai->GetManaPercent() > 10 || ai->HasStrategy("preheal", BotState::BOT_STATE_COMBAT)))
                return false;

            return true;
        }

        /// 获取当前动作的目标名称标识（使用绷带动作）
        virtual std::string GetTargetName() override { return "self target"; }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override
        {
            int firstAidSkillValue = bot->GetSkillValue(129);
#ifdef MANGOSBOT_TWO
            if (firstAidSkillValue >= 400)
                return 34722;
            if (firstAidSkillValue >= 350)
                return 34721;
#endif
#ifndef MANGOSBOT_ZERO
            if (firstAidSkillValue >= 325)
                return 21991;
            if (firstAidSkillValue >= 300)
                return 21990;
#endif
            if (firstAidSkillValue >= 225)
                return 14530;
            if (firstAidSkillValue >= 200)
                return 14529;
            if (firstAidSkillValue >= 175)
                return 8545;
            if (firstAidSkillValue >= 150)
                return 8544;
            if (firstAidSkillValue >= 125)
                return 6451;
            if (firstAidSkillValue >= 100)
                return 6450;
            if (firstAidSkillValue >= 75)
                return 3531;
            if (firstAidSkillValue >= 50)
                return 3530;
            if (firstAidSkillValue >= 20)
                return 2581;
            return 1251;
        }

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptMovement() const override { return true; }
    };

    /// 投掷手雷动作：对目标区域投掷工程学铁皮/瑟银手雷造成晕眩与范围伤害
    class ThrowGrenadeAction : public UseTargetedItemIdAction
    {
    public:
        /// 构造函数：初始化投掷手雷动作
        ThrowGrenadeAction(PlayerbotAI* ai) : UseTargetedItemIdAction(ai, "throw grenade") {}

        /// 获取当前动作的目标名称标识（投掷手雷动作）
        virtual std::string GetTargetName() override { return "current target"; }

        /// 判断当前状态下该动作是否可用/有效（投掷手雷动作）
        virtual bool isUseful() override
        {
#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
                return false;
#endif

            Unit* target = GetTarget();
            if (!target)
                return false;

            if (!UseTargetedItemIdAction::isUseful())
                return false;

            if (!target->IsNonMeleeSpellCasted(false) && target->IsStopped())
                return false;

            if (bot->GetSkillValue(202) < 175)
                return false;

            return bot->GetLevel() >= 52;
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override
        { 
            if (bot->GetSkillValue(202) >= 325)
                return 23737;
            if (bot->GetSkillValue(202) >= 260)
                return 15993;
            return 4390; 
        }
    };

    /// 使用黑暗符文/恶魔符文动作：法力紧缺且生命充裕时消耗生命值换取法力恢复
    class UseDarkRuneAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用黑暗符文/恶魔符文动作
        UseDarkRuneAction(PlayerbotAI* ai) : UseItemIdAction(ai, "dark rune") {}

        /// 判断当前状态下该动作是否可用/有效（使用黑暗符文/恶魔符文动作）
        virtual bool isUseful() override
        {
            if(!UseItemIdAction::isUseful())
                return false;

#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
                return false;
#endif

            if (bot->getClass() == CLASS_MAGE) // mage should use mana gem, shares cd with dark rune (法师优先使用法力宝石（与黑暗符文共享冷却）)
                return false;

            return bot->GetHealth() > 1000;
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override { return 20520; }
    };

    /// 使用火焰防护药水动作：对抗高额火焰伤害首领前喝下强效火焰防护药水
    class UseFireProtectionPotionAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用火焰防护药水动作
        UseFireProtectionPotionAction(PlayerbotAI* ai) : UseItemIdAction(ai, "fire protection potion") {}

        /// 判断当前状态下该动作是否可用/有效（使用火焰防护药水动作）
        virtual bool isUseful() override
        {
            return UseItemIdAction::isUseful() && !bot->HasAura(17543) && (bot->GetLevel() >= 48);
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override { return 13457; }
    };

    /// 使用自由行动药水动作：在 PvP 或控制较多的战斗中使用自由行动药水免疫昏迷与减速
    class UseFreeActionPotionAction : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用自由行动药水动作
        UseFreeActionPotionAction(PlayerbotAI* ai) : UseItemIdAction(ai, "free action potion") {}

        /// 判断当前状态下该动作是否可用/有效（使用自由行动药水动作）
        virtual bool isUseful() override
        {
            if (!UseItemIdAction::isUseful())
                return false;

            if (bot->GetLevel() < 20 || bot->HasAura(6615))
                return false;

            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (!target || !target->IsPlayer())
                return false;

            if (!bot->InBattleGround() && urand(0, 1))
                return false;

            return true;
        }

        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() override { return 5634; }
    };

    /// 饮水回蓝动作：非战斗状态下法力不足时坐下饮水恢复法力
    class DrinkAction : public UseAction
    {
    public:
        /// 构造函数：初始化饮水回蓝动作
        DrinkAction(PlayerbotAI* ai) : UseAction(ai, "drink") {}

        /// 执行动作主逻辑（饮水回蓝动作）
        bool Execute(Event& event) override
        {
            if (sServerFacade.IsInCombat(bot))
                return false;

            if (!bot->HasMana())
                return false;

            if (ai->HasCheat(BotCheatMask::item))
            {
                if (bot->IsNonMeleeSpellCasted(true))
                    return false;

                bot->clearUnitState(UNIT_STAT_CHASE);
                bot->clearUnitState(UNIT_STAT_FOLLOW);

                if (ai->GetBot()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
                {
                    ai->StopMoving();
                }

                if (sServerFacade.isMoving(bot))
                {
                    ai->StopMoving();
                    SetDuration(sPlayerbotAIConfig.globalCoolDown);
                    return false;
                }

                bot->addUnitState(UNIT_STAND_STATE_SIT);
                ai->InterruptSpell();

                float drinkDuration = AI_VALUE(float, "drink duration");

                const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(24355);
                if (!pSpellInfo)
                    return false;

                ai->Unmount();

                ai->CastSpell(24355, bot);
                SetDuration(drinkDuration);
                bot->RemoveSpellCooldown(*pSpellInfo);

                // Eat and drink at the same time (同时进食与饮水恢复生命和法力)

                if (AI_VALUE(bool, "should eat"))
                {
                    const SpellEntry* pSpellInfo2 = sServerFacade.LookupSpellInfo(24005);
                    if (pSpellInfo2)
                    {
                        ai->AddAura(bot, 24005);
                        bot->RemoveSpellCooldown(*pSpellInfo2);
                    }
                }

                return true;
            }

            if (AI_VALUE2(std::list<Item*>, "inventory items", name).empty())
                return false;

            return UseAction::Execute(event);
        }

        /// 判断当前状态下该动作是否可用/有效（饮水回蓝动作）
        bool isUseful() override
        {
            return UseAction::isUseful() && AI_VALUE(bool, "should drink");
        }

        /// 判断执行该动作的前置条件是否满足（饮水回蓝动作）
        bool isPossible() override
        {
            return !sServerFacade.IsInCombat(bot) && UseAction::isPossible();
        }
    };

    /// 进食回血动作：非战斗状态下生命值不足时坐下进食恢复生命
    class EatAction : public UseAction
    {
    public:
        /// 构造函数：初始化进食回血动作
        EatAction(PlayerbotAI* ai) : UseAction(ai, "food") {}

        /// 执行动作主逻辑（进食回血动作）
        bool Execute(Event& event) override
        {
            if (sServerFacade.IsInCombat(bot))
                return false;

            if (ai->HasCheat(BotCheatMask::item))
            {
                if (bot->IsNonMeleeSpellCasted(true))
                    return false;

                bot->clearUnitState(UNIT_STAT_CHASE);
                bot->clearUnitState(UNIT_STAT_FOLLOW);

                if (ai->GetBot()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
                {
                    ai->StopMoving();
                }

                if (sServerFacade.isMoving(bot))
                {
                    ai->StopMoving();
                    SetDuration(sPlayerbotAIConfig.globalCoolDown);
                    return false;
                }

                bot->addUnitState(UNIT_STAND_STATE_SIT);
                ai->InterruptSpell();

                float eatDuration = AI_VALUE(float, "eat duration");

                const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(24005);
                if (!pSpellInfo)
                    return false;

                ai->Unmount();

                ai->CastSpell(24005, bot);
                SetDuration(eatDuration);
                bot->RemoveSpellCooldown(*pSpellInfo);

                // Eat and drink at the same time (同时进食与饮水恢复生命和法力)
                if (AI_VALUE(bool, "should drink"))
                {
                    const SpellEntry* pSpellInfo2 = sServerFacade.LookupSpellInfo(24355);
                    if (pSpellInfo2)
                    {
                        ai->AddAura(bot, 24355);
                        bot->RemoveSpellCooldown(*pSpellInfo2);
                    }
                }

                return true;
            }

            if (AI_VALUE2(std::list<Item*>, "inventory items", name).empty())
                return false;

            return UseAction::Execute(event);
        }

        /// 判断当前状态下该动作是否可用/有效（进食回血动作）
        bool isUseful() override
        {
            return UseAction::isUseful() && AI_VALUE(bool, "should eat");
        }

        /// 判断执行该动作的前置条件是否满足（进食回血动作）
        bool isPossible() override
        {
            return !sServerFacade.IsInCombat(bot) && UseAction::isPossible();
        }
    };
}
