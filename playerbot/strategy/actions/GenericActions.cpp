
#include "playerbot/playerbot.h"
#include "GenericActions.h"
#include "playerbot/PlayerbotFactory.h"

using namespace ai;

/// 判断当前状态下该动作是否可用/有效（近战攻击动作）
bool MeleeAction::isUseful()
{
    // do not allow if can't attack from vehicle (若在载具上无法攻击则不允许执行)
    if (ai->IsInVehicle() && !ai->IsInVehicle(false, false, true))
        return false;

    Unit* target = GetTarget();

    if (target)
    {
        // If the target has a damage shield, melee action not useful and we should actually stop attacking (若目标带有伤害反射护盾，近战动作无效且应停止攻击)
        std::set<Aura*> alreadyDone;
        Unit::AuraList const& vDamageShields = target->GetAurasByType(SPELL_AURA_DAMAGE_SHIELD);
        for (Unit::AuraList::const_iterator i = vDamageShields.begin(); i != vDamageShields.end();)
        {
            if (alreadyDone.find(*i) == alreadyDone.end())
            {
                alreadyDone.insert(*i);
                uint32 damage = (*i)->GetModifier()->m_amount;

                // If the damage shield does at least 10% of our max hp on each hit we do, we shouldn't melee (若反伤护盾每次反伤超过最大生命值的 10%，则不进行近战攻击)
                if (damage >= bot->GetMaxHealth() * 0.10f)
                {
                    bot->AttackStop();
                    return false;
                }

                i = vDamageShields.begin();
            }
            else
                ++i;
        }
    }

    return true;
}

/// 执行动作主逻辑（更新策略依赖动作）
bool UpdateStrategyDependenciesAction::Execute(Event& event)
{
    if (!strategiesToAdd.empty() || !strategiesToRemove.empty())
    {
        // Strategies to add (待添加的策略列表)
        for (const StrategyToUpdate* strategy : strategiesToAdd)
        {
            std::stringstream changeStr;
            changeStr << "+" << strategy->name;
            ai->ChangeStrategy(changeStr.str(), strategy->state);
        }

        // Strategies to remove (待移除的策略列表)
        for (const StrategyToUpdate* strategy : strategiesToRemove)
        {
            std::stringstream changeStr;
            changeStr << "-" << strategy->name;
            ai->ChangeStrategy(changeStr.str(), strategy->state);
        }

        return true;
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（更新策略依赖动作）
bool UpdateStrategyDependenciesAction::isUseful()
{
    if (!strategiesToUpdate.empty())
    {
        strategiesToAdd.clear();
        strategiesToRemove.clear();
        for (const StrategyToUpdate& strategy : strategiesToUpdate)
        {
            // Ignore if the strategies required are not found (若未找到所需策略则忽略)
            bool requiredStrategyMissing = false;
            for (const std::string& strategyRequired : strategy.strategiesRequired)
            {
                // Check if the strategy required has any aliases (检查所需策略是否存在别名)
                std::vector<std::string> strategyRequiredAliases = { strategyRequired };
                if (strategyRequired.find("/") != std::string::npos)
                {
                    strategyRequiredAliases.clear();
                    std::string alias;
                    std::stringstream ss(strategyRequired);
                    while (std::getline(ss, alias, '/'))
                    {
                        strategyRequiredAliases.push_back(alias);
                    }
                }

                bool synonymFound = false;
                for (const std::string& strategyRequiredAlias : strategyRequiredAliases)
                {
                    if (ai->HasStrategy(strategyRequiredAlias, strategy.state))
                    {
                        synonymFound = true;
                        break;
                    }
                }

                if (!synonymFound)
                {
                    requiredStrategyMissing = true;
                    break;
                }
            }

            if (requiredStrategyMissing)
            {
                // Check if we need to remove the strategy (检查是否需要移除该策略)
                if (ai->HasStrategy(strategy.name, strategy.state))
                {
                    strategiesToRemove.emplace_back(&strategy);
                }
            }
            else
            {
                // Check if we need to add the strategy (检查是否需要添加该策略)
                if (!ai->HasStrategy(strategy.name, strategy.state))
                {
                    strategiesToAdd.emplace_back(&strategy);
                }
            }
        }
    }

    return !strategiesToAdd.empty() || !strategiesToRemove.empty();
}

/// 执行动作主逻辑（初始化宠物动作）
bool InitializePetAction::Execute(Event& event)
{
    PlayerbotFactory factory(bot, bot->GetLevel(), ITEM_QUALITY_LEGENDARY);
    factory.InitPet();
    factory.InitPetSpells();
    return true;
}

/// 判断当前状态下该动作是否可用/有效（初始化宠物动作）
bool InitializePetAction::isUseful()
{
    // Only for random bots with item cheats enabled (仅适用于开启了物品作弊的随机机器人)
    if ((ai->HasCheat(BotCheatMask::item) && sPlayerbotAIConfig.IsInRandomAccountList(bot->GetSession()->GetAccountId())) ||
        // Or if alt bot and autoLearnTrainerSpells is true (或为小号机器人且开启了自动向训练师学习法术配置)
        (!sPlayerbotAIConfig.IsInRandomAccountList(bot->GetSession()->GetAccountId()) && sPlayerbotAIConfig.autoLearnTrainerSpells))
    {
        if (bot->getClass() == CLASS_HUNTER)
        {
            bool hasTamedPet = bot->GetPet();
            if (!hasTamedPet)
            {
                std::unique_ptr<QueryResult> queryResult = CharacterDatabase.PQuery("SELECT id, entry, owner "
                                                                                    "FROM character_pet WHERE owner = '%u' AND (slot = '%u' OR slot > '%u') ",
                                                                                    bot->GetGUIDLow(), PET_SAVE_AS_CURRENT, PET_SAVE_LAST_STABLE_SLOT);
            
                if (queryResult)
                {
                    Field* fields = queryResult->Fetch();
                    const uint32 entry = fields[1].GetUInt32();
                    hasTamedPet = ObjectMgr::GetCreatureTemplate(entry);
                }
            }

            return !hasTamedPet;
        }
// Warlock pets should auto learn spells in WOTLK (WLK 版本下术士宠物应自动学习等级技能)
#ifndef MANGOSBOT_TWO
        else if (bot->getClass() == CLASS_WARLOCK)
        {
            // Only initialize if warlock has the pet summoned (仅在术士已召唤出宠物时才进行初始化)
            Pet* pet = bot->GetPet();
            if (pet)
            {
                constexpr uint32 PET_IMP = 416;
                constexpr uint32 PET_FELHUNTER = 417;
                constexpr uint32 PET_VOIDWALKER = 1860;
                constexpr uint32 PET_SUCCUBUS = 1863;
                constexpr uint32 PET_FELGUARD = 17252;

                //      pet type                    pet level  pet spell id (宠物类型  宠物等级  宠物法术 ID)
                std::map<uint32, std::vector<std::pair<uint32, uint32>>> spellList;

                // Imp spells (小鬼技能)
                {
                    // Blood Pact (血之契印)
                    spellList[PET_IMP].push_back(std::pair(4, 6307));
                    spellList[PET_IMP].push_back(std::pair(14, 7804));
                    spellList[PET_IMP].push_back(std::pair(26, 7805));
                    spellList[PET_IMP].push_back(std::pair(38, 11766));
                    spellList[PET_IMP].push_back(std::pair(50, 11767));
                    spellList[PET_IMP].push_back(std::pair(62, 27268));
                    spellList[PET_IMP].push_back(std::pair(74, 47982));

                    // Fire Shield (火焰之盾)
                    spellList[PET_IMP].push_back(std::pair(14, 2947));
                    spellList[PET_IMP].push_back(std::pair(24, 8316));
                    spellList[PET_IMP].push_back(std::pair(34, 8317));
                    spellList[PET_IMP].push_back(std::pair(44, 11770));
                    spellList[PET_IMP].push_back(std::pair(54, 11771));
                    spellList[PET_IMP].push_back(std::pair(64, 27269));
                    spellList[PET_IMP].push_back(std::pair(76, 47983));

                    // Firebolt (火焰箭)
                    spellList[PET_IMP].push_back(std::pair(1, 3110));
                    spellList[PET_IMP].push_back(std::pair(8, 7799));
                    spellList[PET_IMP].push_back(std::pair(18, 7800));
                    spellList[PET_IMP].push_back(std::pair(28, 7801));
                    spellList[PET_IMP].push_back(std::pair(38, 7802));
                    spellList[PET_IMP].push_back(std::pair(48, 11762));
                    spellList[PET_IMP].push_back(std::pair(58, 11763));
                    spellList[PET_IMP].push_back(std::pair(68, 27267));
                    spellList[PET_IMP].push_back(std::pair(78, 47964));

                    // Phase Shift (相位变换)
                    spellList[PET_IMP].push_back(std::pair(12, 4511));
                }

                // Felhunter spells (地狱猎犬技能)
                {
                    // Devour Magic (吞噬魔法)
                    spellList[PET_FELHUNTER].push_back(std::pair(30, 19505));
                    spellList[PET_FELHUNTER].push_back(std::pair(38, 19731));
                    spellList[PET_FELHUNTER].push_back(std::pair(46, 19734));
                    spellList[PET_FELHUNTER].push_back(std::pair(54, 19736));
                    spellList[PET_FELHUNTER].push_back(std::pair(62, 27276));
                    spellList[PET_FELHUNTER].push_back(std::pair(70, 27277));
                    spellList[PET_FELHUNTER].push_back(std::pair(77, 48011));

                    // Paranoia (多疑/侦测隐形)
                    spellList[PET_FELHUNTER].push_back(std::pair(42, 19480));

                    // Spell Lock
                    spellList[PET_FELHUNTER].push_back(std::pair(36, 19244));
                    spellList[PET_FELHUNTER].push_back(std::pair(52, 19647));

                    // Tainted Blood (堕落之血)
                    spellList[PET_FELHUNTER].push_back(std::pair(32, 19478));
                    spellList[PET_FELHUNTER].push_back(std::pair(40, 19655));
                    spellList[PET_FELHUNTER].push_back(std::pair(48, 19656));
                    spellList[PET_FELHUNTER].push_back(std::pair(56, 19660));
                    spellList[PET_FELHUNTER].push_back(std::pair(64, 27280));
                }

                // Voidwalker spells (虚空行者技能)
                {
                    // Consume Shadows (吞噬暗影)
                    spellList[PET_VOIDWALKER].push_back(std::pair(18, 17767));
                    spellList[PET_VOIDWALKER].push_back(std::pair(26, 17850));
                    spellList[PET_VOIDWALKER].push_back(std::pair(34, 17851));
                    spellList[PET_VOIDWALKER].push_back(std::pair(42, 17852));
                    spellList[PET_VOIDWALKER].push_back(std::pair(50, 17853));
                    spellList[PET_VOIDWALKER].push_back(std::pair(58, 17854));
                    spellList[PET_VOIDWALKER].push_back(std::pair(66, 27272));
                    spellList[PET_VOIDWALKER].push_back(std::pair(73, 47987));
                    spellList[PET_VOIDWALKER].push_back(std::pair(78, 47988));

                    // Sacrifice (牺牲)
                    spellList[PET_VOIDWALKER].push_back(std::pair(16, 7812));
                    spellList[PET_VOIDWALKER].push_back(std::pair(24, 19438));
                    spellList[PET_VOIDWALKER].push_back(std::pair(32, 19440));
                    spellList[PET_VOIDWALKER].push_back(std::pair(40, 19441));
                    spellList[PET_VOIDWALKER].push_back(std::pair(48, 19442));
                    spellList[PET_VOIDWALKER].push_back(std::pair(56, 19443));
                    spellList[PET_VOIDWALKER].push_back(std::pair(64, 27273));
                    spellList[PET_VOIDWALKER].push_back(std::pair(72, 47985));
                    spellList[PET_VOIDWALKER].push_back(std::pair(79, 47986));

                    // Suffering (受难)
                    spellList[PET_VOIDWALKER].push_back(std::pair(24, 17735));
                    spellList[PET_VOIDWALKER].push_back(std::pair(36, 17750));
                    spellList[PET_VOIDWALKER].push_back(std::pair(48, 17751));
                    spellList[PET_VOIDWALKER].push_back(std::pair(60, 17752));
                    spellList[PET_VOIDWALKER].push_back(std::pair(63, 27271));
                    spellList[PET_VOIDWALKER].push_back(std::pair(69, 33701));
                    spellList[PET_VOIDWALKER].push_back(std::pair(75, 47989));
                    spellList[PET_VOIDWALKER].push_back(std::pair(80, 47990));

                    // Torment (折磨)
                    spellList[PET_VOIDWALKER].push_back(std::pair(10, 3716));
                    spellList[PET_VOIDWALKER].push_back(std::pair(20, 7809));
                    spellList[PET_VOIDWALKER].push_back(std::pair(30, 7810));
                    spellList[PET_VOIDWALKER].push_back(std::pair(40, 7811));
                    spellList[PET_VOIDWALKER].push_back(std::pair(50, 11774));
                    spellList[PET_VOIDWALKER].push_back(std::pair(60, 11775));
                    spellList[PET_VOIDWALKER].push_back(std::pair(70, 27270));
                    spellList[PET_VOIDWALKER].push_back(std::pair(80, 47984));
                }

                // Succubus spells (魅魔技能)
                {
                    // Lash of Pain (剧痛鞭笞)
                    spellList[PET_SUCCUBUS].push_back(std::pair(20, 7814));
                    spellList[PET_SUCCUBUS].push_back(std::pair(28, 7815));
                    spellList[PET_SUCCUBUS].push_back(std::pair(36, 7816));
                    spellList[PET_SUCCUBUS].push_back(std::pair(44, 11778));
                    spellList[PET_SUCCUBUS].push_back(std::pair(52, 11779));
                    spellList[PET_SUCCUBUS].push_back(std::pair(60, 11780));
                    spellList[PET_SUCCUBUS].push_back(std::pair(68, 27274));
                    spellList[PET_SUCCUBUS].push_back(std::pair(74, 47991));
                    spellList[PET_SUCCUBUS].push_back(std::pair(80, 47992));

                    // Lesser Invisibility (次级隐形术)
                    spellList[PET_SUCCUBUS].push_back(std::pair(32, 7870));

                    // Seduction (诱惑)
                    spellList[PET_SUCCUBUS].push_back(std::pair(26, 6358));

                    // Soothing Kiss (安抚之吻)
                    spellList[PET_SUCCUBUS].push_back(std::pair(22, 6360));
                    spellList[PET_SUCCUBUS].push_back(std::pair(34, 7813));
                    spellList[PET_SUCCUBUS].push_back(std::pair(46, 11784));
                    spellList[PET_SUCCUBUS].push_back(std::pair(58, 11785));
                    spellList[PET_SUCCUBUS].push_back(std::pair(70, 27275));
                }

                // Felguard spells (恶魔卫士技能)
                {
                    // Anguish (痛苦)
                    spellList[PET_FELGUARD].push_back(std::pair(50, 33698));
                    spellList[PET_FELGUARD].push_back(std::pair(60, 33699));
                    spellList[PET_FELGUARD].push_back(std::pair(69, 33700));
                    spellList[PET_FELGUARD].push_back(std::pair(78, 47993));

                    // Avoidance (躲避伤害)
                    spellList[PET_FELGUARD].push_back(std::pair(60, 32233));

                    // Cleave (顺劈斩)
                    spellList[PET_FELGUARD].push_back(std::pair(50, 30213));
                    spellList[PET_FELGUARD].push_back(std::pair(60, 30219));
                    spellList[PET_FELGUARD].push_back(std::pair(68, 30223));
                    spellList[PET_FELGUARD].push_back(std::pair(76, 47994));

                    // Demonic Frenzy (恶魔狂乱)
                    spellList[PET_FELGUARD].push_back(std::pair(56, 32850));

                    // Intercept (拦截)
                    spellList[PET_FELGUARD].push_back(std::pair(52, 30151));
                    spellList[PET_FELGUARD].push_back(std::pair(61, 30194));
                    spellList[PET_FELGUARD].push_back(std::pair(69, 30198));
                    spellList[PET_FELGUARD].push_back(std::pair(79, 47996));
                }

                // Get the appropriate spell list by level and type (按等级与类型获取对应的法术列表)
                const auto& petSpellListItr = spellList.find(pet->GetEntry());
                if (petSpellListItr != spellList.end())
                {
                    const auto& petSpellList = petSpellListItr->second;
                    for (const auto& pair : petSpellListItr->second)
                    {
                        const uint32& levelRequired = pair.first;
                        const uint32& spellID = pair.second;

                        // Check if the pet is missing the spells for it's current level (检查宠物是否缺少当前等级应学会的技能)
                        if (pet->GetLevel() >= levelRequired && !pet->HasSpell(spellID))
                        {
                            return true;
                        }
                    }
                }
            }
        }
#endif
    }

    return false;
}

/// 执行动作主逻辑（设置宠物行为动作）
bool SetPetAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    std::string command = event.getParam();

    // Extract the command and the parameters (提取指令名称与参数)
    std::string parameter;
    size_t spacePos = command.find_first_of(" ");
    if (spacePos != std::string::npos)
    {
        parameter = command.substr(spacePos + 1);
        command = command.substr(0, spacePos);
    }

    Pet* pet = bot->GetPet();
    if (pet)
    {
        if (command == "autocast")
        {
            const std::string& spellName = parameter;
            if (!spellName.empty())
            {
                const uint32 spellId = AI_VALUE2(uint32, "spell id", spellName);
                if (pet->HasSpell(spellId) && IsAutocastable(spellId))
                {
                    auto IsAutocastActive = [&pet, &spellId]() -> bool
                    {
                        for (AutoSpellList::iterator i = pet->m_autospells.begin(); i != pet->m_autospells.end(); ++i)
                        {
                            if (*i == spellId)
                            {
                                return true;
                            }
                        }

                        return false;
                    };

                    const bool autocastActive = IsAutocastActive();
                    pet->ToggleAutocast(spellId, !autocastActive);

                    std::ostringstream out;
                    out << (autocastActive ? "Disabling" : "Enabling") << " pet autocast for ";
                    out << ChatHelper::formatSpell(sServerFacade.LookupSpellInfo(spellId));
                    ai->TellPlayer(GetMaster(), out);

                    return true;
                }
                else
                {
                    ai->TellPlayer(requester, "I can't set to autocast that spell.");
                }
            }
            else
            {
                ai->TellPlayer(requester, "Please specify a pet spell to set the autocast.");
            }
        }
        else if (command == "aggressive")
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const uint8 flag = ACT_REACTION;
            const uint32 spellId = REACT_AGGRESSIVE;
            const uint32 data = (flag << 24) | spellId;

            WorldPacket packet(CMSG_PET_ACTION);
            packet << petGuid;
            packet << data;
            packet << uint64(0);
            bot->GetSession()->HandlePetAction(packet);
            bot->PetSpellInitialize();

            ai->TellPlayer(requester, "Setting pet to aggressive mode");
            return true;
        }
        else if (command == "defensive")
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const uint8 flag = ACT_REACTION;
            const uint32 spellId = REACT_DEFENSIVE;
            const uint32 data = (flag << 24) | spellId;

            WorldPacket packet(CMSG_PET_ACTION);
            packet << petGuid;
            packet << data;
            packet << uint64(0);
            bot->GetSession()->HandlePetAction(packet);
            bot->PetSpellInitialize();

            ai->TellPlayer(requester, "Setting pet to defensive mode");
            return true;
        }
        else if (command == "passive")
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const uint8 flag = ACT_REACTION;
            const uint32 spellId = REACT_PASSIVE;
            const uint32 data = (flag << 24) | spellId;

            WorldPacket packet(CMSG_PET_ACTION);
            packet << petGuid;
            packet << data;
            packet << uint64(0);
            bot->GetSession()->HandlePetAction(packet);
            bot->PetSpellInitialize();

            ai->TellPlayer(requester, "Setting pet to passive mode");
            return true;
        }
        else if (command == "follow")
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const ObjectGuid& targetGuid = ObjectGuid();
            const uint8 flag = ACT_COMMAND;
            const uint32 spellId = COMMAND_FOLLOW;
            const uint32 command = (flag << 24) | spellId;

            WorldPacket data(CMSG_PET_ACTION);
            data << petGuid;
            data << command;
            data << targetGuid;
            bot->GetSession()->HandlePetAction(data);

            ai->TellPlayer(requester, "Setting pet to follow me");
            return true;
        }
        else if (command == "stay")
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const ObjectGuid& targetGuid = ObjectGuid();
            const uint8 flag = ACT_COMMAND;
            const uint32 spellId = COMMAND_STAY;
            const uint32 command = (flag << 24) | spellId;

            WorldPacket data(CMSG_PET_ACTION);
            data << petGuid;
            data << command;
            data << targetGuid;
            bot->GetSession()->HandlePetAction(data);

            ai->TellPlayer(requester, "Setting pet to stay in place");
            return true;
        }
        else if (command == "attack")
        {
            if (requester->GetTarget())
            {
                constexpr uint32 PET_IMP = 416;
                constexpr uint32 PHASE_SHIFT = 4511;
                if (bot->getClass() == CLASS_WARLOCK &&
                    pet->AI() && pet->AI()->HasReactState(REACT_PASSIVE) &&
                    pet->GetEntry() == PET_IMP && pet->HasAura(PHASE_SHIFT))
                {
                    ai->TellPlayer(requester, "Pet has Phase Shift active, cannot attack");
                    return false;
                }

                // Send pet action packet (发送宠物动作控制封包)
                const ObjectGuid& petGuid = pet->GetObjectGuid();
                const ObjectGuid& targetGuid = requester->GetTarget()->GetObjectGuid();
                const uint8 flag = ACT_COMMAND;
                const uint32 spellId = COMMAND_ATTACK;
                const uint32 command = (flag << 24) | spellId;

                WorldPacket data(CMSG_PET_ACTION);
                data << petGuid;
                data << command;
                data << targetGuid;
                bot->GetSession()->HandlePetAction(data);

                ai->TellPlayer(requester, "Sending pet to attack");
                return true;
            }
            else
            {
                ai->TellPlayer(requester, "Please select a target to attack");
            }
        }
        else if (command == "dismiss")
        {
            if (pet->getPetType() == HUNTER_PET)
            {
                if (ai->DoSpecificAction("dismiss pet", event, true))
                {
                    ai->ChangeStrategy("-pet", BotState::BOT_STATE_COMBAT);
                    ai->ChangeStrategy("-pet", BotState::BOT_STATE_NON_COMBAT);
                    ai->TellPlayer(requester, "Dismissing pet");
                    return true;
                }
                else
                {
                    ai->TellPlayer(requester, "I can't dismiss my pet");
                }
            }
            else
            {
                // Send pet action packet (发送宠物动作控制封包)
                const ObjectGuid& petGuid = pet->GetObjectGuid();
                const ObjectGuid& targetGuid = ObjectGuid();
                const uint8 flag = ACT_COMMAND;
                const uint32 spellId = COMMAND_DISMISS;
                const uint32 command = (flag << 24) | spellId;

                WorldPacket data(CMSG_PET_ACTION);
                data << petGuid;
                data << command;
                data << targetGuid;
                bot->GetSession()->HandlePetAction(data);

                ai->ChangeStrategy("+pet", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("+pet", BotState::BOT_STATE_NON_COMBAT);
                ai->ChangeStrategy("-pet", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("-pet", BotState::BOT_STATE_NON_COMBAT);
                ai->TellPlayer(requester, "Dismissing pet");

                return true;
            }
        }
        else if (command == "abandon")
        {
            if (bot->getClass() == CLASS_HUNTER)
            {
                //std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_PET_ABANDON, 8));
                //*packet << pet->GetObjectGuid();
                //bot->GetSession()->QueuePacket(std::move(packet));

                // Send pet action packet (发送宠物动作控制封包)
                const ObjectGuid& petGuid = pet->GetObjectGuid();

                WorldPacket packet(CMSG_PET_ABANDON);
                packet << petGuid;

                bot->GetSession()->HandlePetAbandon(packet);

                return true;
            }
            else
            {
                ai->TellPlayer(requester, "Please specify a pet command (Like autocast).");
            }
        }
        else
        {
            ai->TellPlayer(requester, "Please specify a pet command (Like autocast).");
        }
    }
    else if (command == "call")
    {
        if (bot->getClass() == CLASS_HUNTER || bot->getClass() == CLASS_WARLOCK)
        {
            ai->ChangeStrategy("+pet", BotState::BOT_STATE_COMBAT);
            ai->ChangeStrategy("+pet", BotState::BOT_STATE_NON_COMBAT);
            ai->TellPlayer(requester, "Calling my pet");
            return true;
        }
        else
        {
            ai->TellPlayer(requester, "I can't call any pets");
        }
    }
    else
    {
        ai->TellPlayer(requester, "I don't have any pets");
    }

    return false;
}
