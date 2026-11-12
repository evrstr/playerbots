#pragma once
#include "playerbot/strategy/Action.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/PlayerbotAI.h"

namespace ai
{
    /// 施放法术基类动作：负责目标解析、施法前检查、距离判断与法术施放执行
    class CastSpellAction : public Action
    {
    public:
        /// 构造函数：初始化施放法术基类动作
        CastSpellAction(PlayerbotAI* ai, std::string spell);
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_SINGLE; }
        /// 执行动作主逻辑（施放法术基类动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（施放法术基类动作）
        virtual bool isPossible() override;
        /// 判断当前状态下该动作是否可用/有效（施放法术基类动作）
        virtual bool isUseful() override;

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptCast() const override { return true; }

        /// 判断当前施法动作是否配置了前置接近目标动作
        bool HasReachAction() { return !GetReachActionName().empty(); }
        /// 获取当前绑定的法术 ID
        const uint32& GetSpellID() const { return spellId; }
        
    protected:
        /// 获取当前绑定的法术名称
        const std::string& GetSpellName() const { return spellName; }
        /// 设置动作关联的法术名称并解析对应的法术 ID
        void SetSpellName(const std::string& name, std::string spellIDContextName = "spell id", bool force = false);

        /// 获取当前动作的目标单位（施放法术基类动作）
        Unit* GetTarget() override;
        /// 获取当前动作的目标名称标识（施放法术基类动作）
        virtual std::string GetTargetName() override { return "current target"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() { return ""; }
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() { return "reach spell"; }

        /// 获取执行本动作前需要优先执行的前置动作列表
        virtual NextAction** getPrerequisites() override;

    protected:
        float range;

    private:
        std::string spellName;
        uint32 spellId;
    };

    /// 施放宠物法术动作：命令机器人召唤出的宠物对目标施放指定宠物技能
    class CastPetSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放宠物法术动作
        CastPetSpellAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) {}

        /// 判断执行该动作的前置条件是否满足（施放宠物法术动作）
        virtual bool isPossible() override;

    protected:
        /// 获取当前动作的目标名称标识（施放宠物法术动作）
        virtual std::string GetTargetName() override { return "current target"; }
        /// 获取接近目标阶段所使用的移动动作名称
        std::string GetReachActionName() override { return ""; }
    };

    //---------------------------------------------------------------------------------------------------------------------
    /// 施放光环法术基类动作：在目标或自身缺少指定光环时才执行施法
    class CastAuraSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放光环法术基类动作
        CastAuraSpellAction(PlayerbotAI* ai, std::string spell, bool isOwner = false) : CastSpellAction(ai, spell), isOwner(isOwner) {}
        /// 判断当前状态下该动作是否可用/有效（施放光环法术基类动作）
        virtual bool isUseful() override;

    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }

    protected:
        bool isOwner;
    };

    //---------------------------------------------------------------------------------------------------------------------
    /// 施放近战技能动作：施放需要进入近战距离才能使用的职业打击技能
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放近战技能动作
        CastMeleeSpellAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) 
        {
            range = ATTACK_DISTANCE;
        }

    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach melee"; }
    };

    //---------------------------------------------------------------------------------------------------------------------
    /// 施放近战范围技能动作：在周围有多个近战目标时施放近战 AOE 技能
    class CastMeleeAoeSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放近战范围技能动作
        CastMeleeAoeSpellAction(PlayerbotAI* ai, std::string spell, float radius) : CastSpellAction(ai, spell), radius(radius)
        {
            range = ATTACK_DISTANCE;
        }

        /// 判断当前状态下该动作是否可用/有效（施放近战范围技能动作）
        virtual bool isUseful() override;

    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return ""; }

    protected:
        float radius;
    };

    //---------------------------------------------------------------------------------------------------------------------
    /// 施放近战减益技能动作：在近战范围内对目标施加减益效果
    class CastMeleeDebuffSpellAction : public CastAuraSpellAction
    {
    public:
        /// 构造函数：初始化施放近战减益技能动作
        CastMeleeDebuffSpellAction(PlayerbotAI* ai, std::string spell, bool isOwner = true) : CastAuraSpellAction(ai, spell, isOwner)
        {
            range = ATTACK_DISTANCE;
        }
    
    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach melee"; }
    };
    
    /// 施放远程减益技能动作：在远程射程内对目标施加持续伤害或控制类减益
    class CastRangedDebuffSpellAction : public CastAuraSpellAction
    {
    public:
        /// 构造函数：初始化施放远程减益技能动作
        CastRangedDebuffSpellAction(PlayerbotAI* ai, std::string spell, bool isOwner = true) : CastAuraSpellAction(ai, spell, isOwner) {}
    
    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }
    };

    /// 对近战攻击者施放减益动作：对正在攻击己方的近战敌人施加减益光环
    class CastMeleeDebuffSpellOnAttackerAction : public CastAuraSpellAction
    {
    public:
        /// 构造函数：初始化对近战攻击者施放减益动作
        CastMeleeDebuffSpellOnAttackerAction(PlayerbotAI* ai, std::string spell, bool isOwner = true) : CastAuraSpellAction(ai, spell, isOwner)
        {
            range = ATTACK_DISTANCE;
        }

    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        std::string GetReachActionName() override { return "reach melee"; }
        /// 获取当前动作的目标名称标识（对近战攻击者施放减益动作）
        std::string GetTargetName() override { return "attacker without aura"; }
        /// 获取目标限定符参数
        std::string GetTargetQualifier() override { return GetSpellName(); }
        /// 获取动作名称
        virtual std::string getName() override { return GetSpellName() + " on attacker"; }
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_AOE; }
    };

    /// 对攻击者施放远程减益动作：对正在攻击己方的敌人远程施加减益光环
    class CastRangedDebuffSpellOnAttackerAction : public CastAuraSpellAction
    {
    public:
        /// 构造函数：初始化对攻击者施放远程减益动作
        CastRangedDebuffSpellOnAttackerAction(PlayerbotAI* ai, std::string spell, bool isOwner = true) : CastAuraSpellAction(ai, spell, isOwner) {}
        
    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }
        /// 获取当前动作的目标名称标识（对攻击者施放远程减益动作）
        virtual std::string GetTargetName() override { return "attacker without aura"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
        /// 获取动作名称
        virtual std::string getName() override { return GetSpellName() + " on attacker"; }
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_AOE; }
    };

    /// 施放增益法术动作：为自身或目标施加缺少的增益状态光环
    class CastBuffSpellAction : public CastAuraSpellAction
    {
    public:
        /// 构造函数：初始化施放增益法术动作
        CastBuffSpellAction(PlayerbotAI* ai, std::string spell) : CastAuraSpellAction(ai, spell) { }
        /// 获取当前动作的目标名称标识（施放增益法术动作）
        virtual std::string GetTargetName() override { return "self target"; }
    };

    /// 对指定目标施法动作：从黑板或限定符解析特定目标并对其施放法术
    class CastSpellTargetAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化对指定目标施法动作
        CastSpellTargetAction(PlayerbotAI* ai, std::string spell, std::string targetsValue, bool aliveCheck = false, bool auraCheck = false) : CastSpellAction(ai, spell), targetsValue(targetsValue), aliveCheck(aliveCheck), auraCheck(auraCheck) {}
        /// 获取当前动作的目标名称标识（对指定目标施法动作）
        virtual std::string GetTargetName() override { return "self target"; }
        /// 检查目标单位是否存活、在视野内且满足攻击/施法合法性
        virtual bool IsTargetValid(Unit* target);
        /// 获取当前动作的目标单位（对指定目标施法动作）
        Unit* GetTarget() override;

    private:
        std::string targetsValue;
        bool aliveCheck;
        bool auraCheck;
    };

    /// 对物品目标施法动作：对背包内指定物品施放法术（如附魔或转化）
    class CastItemTargetAction : public CastSpellTargetAction
    {
    public:
        /// 构造函数：初始化对物品目标施法动作
        CastItemTargetAction(PlayerbotAI* ai, std::string targetsValue, bool aliveCheck = false, bool auraCheck = false) : CastSpellTargetAction(ai, "item target", targetsValue, aliveCheck, false), itemAuraCheck(auraCheck) {}
        /// 检查目标单位是否存活、在视野内且满足攻击/施法合法性
        virtual bool IsTargetValid(Unit* target) override;
        /// 获取关联的物品模板 ID
        virtual uint32 GetItemId() = 0;

    protected:
        /// 判断当前状态下该动作是否可用/有效（对物品目标施法动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（对物品目标施法动作）
        virtual bool isPossible() override;
        /// 执行动作主逻辑（对物品目标施法动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 检查指定法术是否正处于冷却时间中
        bool HasSpellCooldown(uint32 itemId);

    private:
        bool itemAuraCheck;
    };

    /// 施放物品附魔动作：查找需要强化的装备或物品并施放附魔技能
    class CastEnchantItemAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放物品附魔动作
        CastEnchantItemAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) { }
        /// 获取当前动作的目标名称标识（施放物品附魔动作）
        virtual std::string GetTargetName() override { return "self target"; }
        /// 判断执行该动作的前置条件是否满足（施放物品附魔动作）
        virtual bool isPossible() override;
    };

    //---------------------------------------------------------------------------------------------------------------------

    /// 施放治疗法术动作：在目标缺少对应持续治疗或需要治疗时施放治疗术
    class CastHealingSpellAction : public CastAuraSpellAction
    {
    public:
        /// 构造函数：初始化施放治疗法术动作
        CastHealingSpellAction(PlayerbotAI* ai, std::string spell, uint8 estAmount = 15.0f) : CastAuraSpellAction(ai, spell, true), estAmount(estAmount) {}
        
    protected:
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_AOE; }
        /// 获取当前动作的目标名称标识（施放治疗法术动作）
        virtual std::string GetTargetName() override { return "self target"; }
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach party member to heal"; }
        /// 判断当前状态下该动作是否可用/有效（施放治疗法术动作）
        virtual bool isUseful() override 
        {
            // do not heal if they will not receive healing due to debuff (若目标因减益导致无法受到治疗，则跳过治疗)
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
            if (target && target->GetMaxNegativeAuraModifier(SPELL_AURA_MOD_HEALING_PCT) <= -100)
                return false;
            return CastAuraSpellAction::isUseful();
        }

    protected:
        uint8 estAmount;
    };

    /// 施放群体治疗法术动作：在多名队友同时掉血时施放群体治疗法术
    class CastAoeHealSpellAction : public CastHealingSpellAction
    {
    public:
        /// 构造函数：初始化施放群体治疗法术动作
        CastAoeHealSpellAction(PlayerbotAI* ai, std::string spell, uint8 estAmount = 15.0f) : CastHealingSpellAction(ai, spell, estAmount) {}
        /// 获取当前动作的目标名称标识（施放群体治疗法术动作）
        virtual std::string GetTargetName() override { return "party member to heal"; }
        /// 判断当前状态下该动作是否可用/有效（施放群体治疗法术动作）
        virtual bool isUseful() override;
    };

    /// 施放驱散法术动作：对自身或目标施放解除诅咒、中毒、疾病或魔法的驱散技能
    class CastCureSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放驱散法术动作
        CastCureSpellAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) {}
        /// 获取当前动作的目标名称标识（施放驱散法术动作）
        virtual std::string GetTargetName() override { return "self target"; }
    };

    /// 队友目标动作名称支持基类：为针对队友施放的法术统一拼接动作名称后缀
    class PartyMemberActionNameSupport 
    {
    public:
        /// 构造函数：初始化队友目标动作名称支持基类
        PartyMemberActionNameSupport(std::string spell) : name(spell + " on party") {}
        /// 获取动作名称
        std::string getName() { return name; }

    private:
        std::string name;
    };

    /// 治疗队友动作：寻找血量较低的队友并对其施放治疗法术
    class HealPartyMemberAction : public CastHealingSpellAction, public PartyMemberActionNameSupport
    {
    public:
        /// 构造函数：初始化治疗队友动作
        HealPartyMemberAction(PlayerbotAI* ai, std::string spell, uint8 estAmount = 15.0f) : CastHealingSpellAction(ai, spell, estAmount), PartyMemberActionNameSupport(spell) {}
        /// 获取动作名称
        virtual std::string getName() override { return PartyMemberActionNameSupport::getName(); }
        /// 获取当前动作的目标名称标识（治疗队友动作）
        virtual std::string GetTargetName() override { return "party member to heal"; }
    };

    /// 对队友施放持续治疗动作：对需要持续恢复的队友施放 HOT 治疗法术
    class HealHotPartyMemberAction : public HealPartyMemberAction
    {
    public:
        /// 构造函数：初始化对队友施放持续治疗动作
        HealHotPartyMemberAction(PlayerbotAI* ai, std::string spell) : HealPartyMemberAction(ai, spell) {}
        /// 判断当前状态下该动作是否可用/有效（对队友施放持续治疗动作）
        virtual bool isUseful() override;
    };

    /// 复活队友动作：寻找已死亡的队友并施放复活法术
    class ResurrectPartyMemberAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化复活队友动作
        ResurrectPartyMemberAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) {}
        
    protected:
        /// 获取当前动作的目标名称标识（复活队友动作）
        virtual std::string GetTargetName() override { return "party member to resurrect"; }
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach party member to heal"; }
    };
    //---------------------------------------------------------------------------------------------------------------------

    /// 驱散队友负面状态动作：检查并驱散队友身上的可解除减益效果
    class CurePartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        /// 构造函数：初始化驱散队友负面状态动作
        CurePartyMemberAction(PlayerbotAI* ai, std::string spell, uint32 dispelType) : CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell), dispelType(dispelType) {}
    
    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach party member to heal"; }
        /// 获取动作名称
        virtual std::string getName() override { return PartyMemberActionNameSupport::getName(); }
        /// 获取当前动作的目标名称标识（驱散队友负面状态动作）
        virtual std::string GetTargetName() override { return "party member to dispel"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return std::to_string(dispelType); }

    protected:
        uint32 dispelType;
    };

    //---------------------------------------------------------------------------------------------------------------------

    /// 为队友施放单体增益动作：为缺少对应增益的队友补加单体 Buff
    class BuffOnPartyAction : public CastBuffSpellAction, public PartyMemberActionNameSupport
    {
    public:
        /// 构造函数：初始化为队友施放单体增益动作
        BuffOnPartyAction(PlayerbotAI* ai, std::string spell, bool ignoreTanks = false) : CastBuffSpellAction(ai, spell), PartyMemberActionNameSupport(spell), ignoreTanks(ignoreTanks) {}
        
    protected:
        /// 获取动作名称
        virtual std::string getName() override { return PartyMemberActionNameSupport::getName(); }
        /// 获取当前动作的目标名称标识（为队友施放单体增益动作）
        virtual std::string GetTargetName() override { return "friendly unit without aura"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }

    protected:
        bool ignoreTanks;
    };

    //---------------------------------------------------------------------------------------------------------------------

    /// 为全队施放强效增益动作：施放覆盖同职业或全队的强效团队增益法术
    class GreaterBuffOnPartyAction : public CastBuffSpellAction, public PartyMemberActionNameSupport
    {
    public:
        /// 构造函数：初始化为全队施放强效增益动作
        GreaterBuffOnPartyAction(PlayerbotAI* ai, std::string spell, std::string lowerSpell, bool ignoreTanks = false) : CastBuffSpellAction(ai, spell), PartyMemberActionNameSupport(spell), lowerSpell(lowerSpell), ignoreTanks(ignoreTanks) {}

    protected:
        /// 获取动作名称
        virtual std::string getName() override { return PartyMemberActionNameSupport::getName(); }
        /// 获取当前动作的目标名称标识（为全队施放强效增益动作）
        virtual std::string GetTargetName() override { return "party member without aura"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override 
        { 
            const std::string spells = !lowerSpell.empty() ? GetSpellName() + "," + lowerSpell : GetSpellName();
            return spells + "-" + (ignoreTanks ? "1" : "0"); 
        }

    private:
        bool ignoreTanks;
        std::string lowerSpell;
    };

    //---------------------------------------------------------------------------------------------------------------------

    /// 坦克目标动作名称支持基类：为专门针对坦克施放的法术统一拼接动作名称后缀
    class PartyTankActionNameSupport
    {
    public:
        /// 构造函数：初始化坦克目标动作名称支持基类
        PartyTankActionNameSupport(std::string spell) : name(spell + " on tank") {}
        /// 获取动作名称
        std::string getName() { return name; }

    private:
        std::string name;
    };

    /// 为坦克施放增益动作：优先为队伍中的坦克目标补加专属增益法术
    class BuffOnTankAction : public CastBuffSpellAction, public PartyMemberActionNameSupport
    {
    public:
        /// 构造函数：初始化为坦克施放增益动作
        BuffOnTankAction(PlayerbotAI* ai, std::string spell) : CastBuffSpellAction(ai, spell), PartyMemberActionNameSupport(spell) {}

    protected:
        /// 获取动作名称
        virtual std::string getName() override { return PartyMemberActionNameSupport::getName(); }
        /// 获取当前动作的目标名称标识（为坦克施放增益动作）
        virtual std::string GetTargetName() override { return "party tank without aura"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
    };

    /// 施放远程射击/魔杖动作：使用弓、枪械、弩或魔杖进行自动远程射击
    class CastShootAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放远程射击/魔杖动作
        CastShootAction(PlayerbotAI* ai) : CastSpellAction(ai, "shoot"), rangedWeapon(nullptr), weaponDelay(0), needsAmmo(false) {}
        /// 获取动作产生的仇恨类型
        ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_LOW; }
        /// 执行动作主逻辑（施放远程射击/魔杖动作）
        bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（施放远程射击/魔杖动作）
        bool isPossible() override;

    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }

    private:
        /// 刷新并记录主副手武器及远程武器状态参数
        void UpdateWeaponInfo();

    private:
        const Item* rangedWeapon;
        uint32 weaponDelay;
        bool needsAmmo;
    };

    /// 移除自身增益动作：主动取消机器人身上指定的无用或冲突增益光环
    class RemoveBuffAction : public Action
    {
    public:
        /// 构造函数：初始化移除自身增益动作
        RemoveBuffAction(PlayerbotAI* ai, std::string spell) : Action(ai, "remove aura"), name(spell) {}
        /// 获取动作名称
        virtual std::string getName() override { return "remove " + name; }
        /// 判断当前状态下该动作是否可用/有效（移除自身增益动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（移除自身增益动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（移除自身增益动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    private:
        std::string name;
    };

    // racials (种族天赋动作)

    // heal (治疗)
#ifndef MANGOSBOT_ZERO
    HEAL_ACTION(CastGiftOfTheNaaruAction, "gift of the naaru");
#endif
    HEAL_ACTION(CastCannibalizeAction, "cannibalize");

    // buff (增益效果)

    BUFF_ACTION(CastShadowmeldAction, "shadowmeld");
    BUFF_ACTION(CastBerserkingAction, "berserking");
    BUFF_ACTION(CastBloodFuryAction, "blood fury");
    BUFF_ACTION(CastStoneformAction, "stoneform");
    BUFF_ACTION(CastPerceptionAction, "perception");

    // spells (法术列表)

#ifndef MANGOSBOT_ZERO
    SPELL_ACTION(CastManaTapAction, "mana tap");
    SPELL_ACTION(CastArcaneTorrentAction, "arcane torrent");
#endif

    /// 施放战争践踏动作：牛头人种族天赋战争践踏，击晕附近敌人
    class CastWarStompAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放战争践踏动作
        CastWarStompAction(PlayerbotAI* ai) : CastSpellAction(ai, "war stomp") {}
        /// 判断当前状态下该动作是否可用/有效（施放战争践踏动作）
        bool isUseful() override;

    };

    // cc breakers (解控技能)

    BUFF_ACTION(CastWillOfTheForsakenAction, "will of the forsaken");
    BUFF_ACTION_U(CastEscapeArtistAction, "escape artist", !ai->HasAura("stealth", ai->GetUnit(AI_VALUE(ObjectGuid, "self target"))));

#ifdef MANGOSBOT_TWO
    SPELL_ACTION(CastEveryManforHimselfAction, "every man for himself");
#endif

    /// 对敌方治疗者施法动作：优先以敌方治疗玩家为目标施放打断或限制法术
    class CastSpellOnEnemyHealerAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化对敌方治疗者施法动作
        CastSpellOnEnemyHealerAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) {}
        
    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }
        /// 获取当前动作的目标名称标识（对敌方治疗者施法动作）
        virtual std::string GetTargetName() override { return "enemy healer target"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
        /// 获取动作名称
        virtual std::string getName() override { return GetSpellName() + " on enemy healer"; }
    };

    /// 施放减速控制技能动作：对逃跑或风筝目标施加减速诱捕类法术
    class CastSnareSpellAction : public CastRangedDebuffSpellAction
    {
    public:
        /// 构造函数：初始化施放减速控制技能动作
        CastSnareSpellAction(PlayerbotAI* ai, std::string spell) : CastRangedDebuffSpellAction(ai, spell) {}
        
    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }
        /// 获取当前动作的目标名称标识（施放减速控制技能动作）
        virtual std::string GetTargetName() override { return "snare target"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
        /// 获取动作名称
        virtual std::string getName() override { return GetSpellName() + " on snare target"; }
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_NONE; }
    };

    /// 施放群体控制技能动作：对次要敌对目标施放变形、闷棍、冰冻等控场法术
    class CastCrowdControlSpellAction : public CastRangedDebuffSpellAction
    {
    public:
        /// 构造函数：初始化施放群体控制技能动作
        CastCrowdControlSpellAction(PlayerbotAI* ai, std::string spell) : CastRangedDebuffSpellAction(ai, spell) {}
        
    private:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }
        /// 获取当前动作的目标名称标识（施放群体控制技能动作）
        virtual std::string GetTargetName() override { return "cc target"; }
        /// 获取目标限定符参数
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_NONE; }
    };

    /// 施放保护技能动作：对处于危险中的队友施放保护祝福或援护类减伤技能
    class CastProtectSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放保护技能动作
        CastProtectSpellAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) {}
        /// 判断当前状态下该动作是否可用/有效（施放保护技能动作）
        virtual bool isUseful() override { return CastSpellAction::isUseful() && !ai->HasAura(GetSpellName(), GetTarget()); }

    protected:
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return "reach spell"; }
        /// 获取当前动作的目标名称标识（施放保护技能动作）
        virtual std::string GetTargetName() override { return "party member to protect"; }
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_NONE; }
    };

    /// 中断当前施法动作：目标无效或战术需要时立即打断自身当前施法读条
    class InterruptCurrentSpellAction : public Action
    {
    public:
        /// 构造函数：初始化中断当前施法动作
        InterruptCurrentSpellAction(PlayerbotAI* ai) : Action(ai, "interrupt current spell") {}
        /// 判断当前状态下该动作是否可用/有效（中断当前施法动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（中断当前施法动作）
        virtual bool Execute(Event& event) override;
    };

    //--------------------//
    //   Vehicle Actions  // (载具动作)
    //--------------------//

    /// 施放载具技能基类动作：控制载具对目标或坐标点施放专属载具技能
    class CastVehicleSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化施放载具技能基类动作
        CastVehicleSpellAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell)
        {
            range = 120.0f;
            speed = 30.0f;
            SetSpellName(spell, "vehicle spell id", !GetSpellID());
        }

        /// 执行动作主逻辑（施放载具技能基类动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（施放载具技能基类动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（施放载具技能基类动作）
        virtual bool isPossible() override;

    protected:
        /// 获取动作产生的仇恨类型
        virtual ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_NONE; }
        /// 获取当前动作的目标名称标识（施放载具技能基类动作）
        virtual std::string GetTargetName() override { return "current target"; }
        /// 获取接近目标阶段所使用的移动动作名称
        virtual std::string GetReachActionName() override { return ""; }
        float speed;
        bool needTurn = true;
    };

    /// 投掷巨石载具技能动作：驾驶投石车/巨人载具向目标投掷巨石
    class CastHurlBoulderAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化投掷巨石载具技能动作
        CastHurlBoulderAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "hurl boulder") {}
    };

    /// 蒸汽冲锋载具技能动作：驾驶攻城坦克向前方冲锋撞击敌人与建筑
    class CastSteamRushAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化蒸汽冲锋载具技能动作
        CastSteamRushAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "steam rush") {}
    };

    /// 冲撞载具技能动作：控制攻城车使用前部撞角猛烈撞击敌方城门或单位
    class CastRamAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化冲撞载具技能动作
        CastRamAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "ram") {}
    };

    /// 凝固汽油弹载具技能动作：驾驶工程载具向目标区域发射燃烧弹
    class CastNapalmAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化凝固汽油弹载具技能动作
        CastNapalmAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "napalm") {}
    };

    /// 发射火炮载具技能动作：操作防御炮台或攻城车炮塔向目标开火
    class CastFireCannonAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化发射火炮载具技能动作
        CastFireCannonAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "fire cannon") {}
    };

    /// 蒸汽冲击载具技能动作：发射高温蒸汽波对前方敌人造成伤害与击退
    class CastSteamBlastAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化蒸汽冲击载具技能动作
        CastSteamBlastAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "steam blast") {}
    };

    /// 发射燃烧火箭载具技能动作：向目标位置发射造成持续燃烧伤害的火箭弹
    class CastIncendiaryRocketAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化发射燃烧火箭载具技能动作
        CastIncendiaryRocketAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "incendiary rocket") {}
    };

    /// 火箭爆破载具技能动作：发射高爆火箭轰击敌方目标或建筑
    class CastRocketBlastAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化火箭爆破载具技能动作
        CastRocketBlastAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "rocket blast") {}
    };

    /// 投掷战刃载具技能动作：操作投刃车向目标发射旋转战刃
    class CastGlaiveThrowAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化投掷战刃载具技能动作
        CastGlaiveThrowAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "glaive throw") {}
    };

    /// 剑刃齐射载具技能动作：操作投刃车向区域倾泻大量飞刃进行范围打击
    class CastBladeSalvoAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化剑刃齐射载具技能动作
        CastBladeSalvoAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "blade salvo") {}
    };

    /// 交付被盗马匹任务载具动作：将骑乘的马匹送回任务交付点完成任务
    class CastDeliverStolenHorseAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化交付被盗马匹任务载具动作
        CastDeliverStolenHorseAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "deliver stolen horse") {}
    protected:
        /// 获取当前动作的目标名称标识（交付被盗马匹任务载具动作）
        virtual std::string GetTargetName() override { return "self target"; }
    };

    /// 无头骑士的召唤载具技能动作：在对应载具或任务状态下施放召唤技能
    class CastHorsemansCallAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化无头骑士的召唤载具技能动作
        CastHorsemansCallAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "horseman call") {
            range = 120.0f;
            SetSpellName("Horseman's Call", "vehicle spell id", true);
        }
    protected:
        /// 获取当前动作的目标名称标识（无头骑士的召唤载具技能动作）
        virtual std::string GetTargetName() override { return "self target"; }
    };

    /// 血色火炮载具技能动作：操作血色十字军火炮轰击敌方目标
    class CastScarletCannonAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化血色火炮载具技能动作
        CastScarletCannonAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "scarlet cannon") { speed = 3000.0f; }
    protected:
        /// 获取当前动作的目标名称标识（血色火炮载具技能动作）
        virtual std::string GetTargetName() override { return "grind target"; }
    };

    /// 电磁脉冲载具技能动作：释放电磁脉冲瘫痪周围敌方机械或单位
    class CastElectroMagneticPulseAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化电磁脉冲载具技能动作
        CastElectroMagneticPulseAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "electro - magnetic pulse") { range = 20.0f; }
    protected:
        /// 获取当前动作的目标名称标识（电磁脉冲载具技能动作）
        virtual std::string GetTargetName() override { return "grind target"; }
    };

    /// 骸骨狮鹫逃脱载具技能动作：骑乘骸骨狮鹫触发空中撤离技能
    class CastSkeletalGryphonEscapeAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化骸骨狮鹫逃脱载具技能动作
        CastSkeletalGryphonEscapeAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "skeletal gryphon escape") {}
    protected:
        /// 获取当前动作的目标名称标识（骸骨狮鹫逃脱载具技能动作）
        virtual std::string GetTargetName() override { return "self target"; }
    };

    /// 冰冻死亡箭载具技能动作：驾驶冰霜巨龙等载具对地面目标发射死亡寒冰箭
    class CastFrozenDeathboltAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化冰冻死亡箭载具技能动作
        CastFrozenDeathboltAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "frozen deathbolt")
        {
            needTurn = false;
            speed = 3000.0f;
        };
        /// 判断执行该动作的前置条件是否满足（冰冻死亡箭载具技能动作）
        virtual bool isPossible() override;
    protected:
        /// 获取当前动作的目标名称标识（冰冻死亡箭载具技能动作）
        virtual std::string GetTargetName() override { return "grind target"; }
    };

    /// 吞噬人形生物载具技能动作：控制任务载具吞噬目标人形生物以恢复能量或完成目标
    class CastDevourHumanoidAction : public CastVehicleSpellAction
    {
    public:
        /// 构造函数：初始化吞噬人形生物载具技能动作
        CastDevourHumanoidAction(PlayerbotAI* ai) : CastVehicleSpellAction(ai, "devour humanoid")
        {
            range = 15.0f;
            needTurn = false;
        }
        /// 判断执行该动作的前置条件是否满足（吞噬人形生物载具技能动作）
        virtual bool isPossible() override;
    protected:
        /// 获取当前动作的目标名称标识（吞噬人形生物载具技能动作）
        virtual std::string GetTargetName() override { return "grind target"; }
    };
}
