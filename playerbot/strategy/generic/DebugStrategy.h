/// 各类 AI 调试日志与可视化反馈策略头文件
#pragma once

namespace ai
{
    /// 策略：通用调试，在聊天框输出当前尝试执行的动作、权重及触发器
    class DebugStrategy : public Strategy
    {
    public:
        DebugStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback on the current actions (relevance) [triggers] it is trying to do.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug action", "debug move" , "debug rpg", "debug spell",  "debug travel", "debug threat" }; }
#endif
    };
    /// 策略：动作调试，反馈被考虑但判定为不可用/无用的动作
    class DebugActionStrategy : public DebugStrategy
    {
    public:
        DebugActionStrategy(PlayerbotAI* ai) : DebugStrategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug action"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug action"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback on the current actions the bot is considering to do but are impossible or not usefull.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug"}; }
#endif
    };
    /// 策略：移动调试，输出当前移动目标与路径反馈
    class DebugMoveStrategy : public Strategy
    {
    public:
        DebugMoveStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug move"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug move"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat and visual feedback for it's current movement actions.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug", "rpg", "travel", "follow"}; }
#endif
    };
    /// 策略：RPG 调试，输出 RPG 目标选择与移动决策详情
    class DebugRpgStrategy : public Strategy
    {
    public:
        DebugRpgStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug rpg"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug rpg"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback on rpg target selection during [h:action|choose rpg target] and  [h:action|move to rpg target].";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug", "rpg"}; }
#endif
    };

    /// 策略：施法调试，输出当前正在施放的法术信息
    class DebugSpellStrategy : public Strategy
    {
    public:
        DebugSpellStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug spell"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug spell"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback on the current spell it is casting.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug"}; }
#endif
    };

    /// 策略：旅行调试，输出长途旅行目的地评估与选择过程
    class DebugTravelStrategy : public Strategy
    {
    public:
        DebugTravelStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug travel"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug travel"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback on the locations it is considering during [h:action|choose travel target].";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" , "travel"}; }
#endif
    };

    /// 策略：心跳调试，每帧向 bot_heartbeat.csv 写入运行状态记录
    class DebugHeartbeatStrategy : public Strategy
    {
    public:
        DebugHeartbeatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug heartbeat"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug heartbeat"; }
        virtual std::string GetHelpDescription() {
            return "This strategy makes the bot write per-tick rows to bot_heartbeat.csv.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug"}; }
#endif
    };

    /// 策略：反应调试，向 bot_reactions.csv 写入已执行动作记录
    class DebugReactionsStrategy : public Strategy
    {
    public:
        DebugReactionsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug reactions"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug reactions"; }
        virtual std::string GetHelpDescription() {
            return "This strategy makes the bot write executed-action rows to bot_reactions.csv.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug"}; }
#endif
    };

    /// 策略：仇恨调试，在聊天或场景中反馈当前仇恨值计算
    class DebugThreatStrategy : public Strategy
    {
    public:
        DebugThreatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug threat"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug threat"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat (noncombat) or visual (combat) feedback on it's current [h:value:threat|threat value].";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" , "threat" }; }
#endif
    };

    /// 策略：骑乘调试，输出坐骑上下马决策反馈
    class DebugMountStrategy : public Strategy
    {
    public:
        DebugMountStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug mount"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug mount"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback during mount actions.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" , "threat" }; }
#endif
    };
    
    /// 策略：刷怪调试，输出打怪目标选择过程反馈
    class DebugGrindStrategy : public Strategy
    {
    public:
        DebugGrindStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug grind"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug grind"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback about grind target selection.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" , "threat" }; }
#endif
    };

    /// 策略：拾取调试，输出战利品搜寻与拾取反馈
    class DebugLootStrategy : public Strategy
    {
    public:
        DebugLootStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug loot"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug loot"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot give chat feedback about looting.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" }; }
#endif
    };

    /// 策略：日志调试，将对主人发送的消息写入日志文件
    class DebugLogStrategy : public Strategy
    {
    public:
        DebugLogStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug log"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug log"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will bots log anything they say to master to a logfile";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" }; }
#endif
    };

    /// 策略：按角色名分文件记录机器人聊天输出日志
    class DebugLogNameStrategy : public Strategy
    {
    public:
        DebugLogNameStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug logname"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug logname"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will bots log anything they say to master to a logfile with the bot's name";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" }; }
#endif
    };

    /// 策略：AI 闲聊，启用大语言模型（LLM）回复玩家聊天
    class AIChatStrategy : public Strategy
    {
    public:
        AIChatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "ai chat"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "ai chat"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "Uses the LLM system to respond to player chats.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "" }; }
#endif
    };

    /// 策略：LLM 调试，输出大语言模型对话调用调试信息
    class DebugLLMStrategy : public Strategy
    {
    public:
        DebugLLMStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug llm"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug llm"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will give debug output while using the ai chat sytem";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" }; }
#endif
    };

    /// 策略：卡死调试，输出卡死检测触发的诊断详情
    class DebugStuckStrategy : public Strategy
    {
    public:
        DebugStuckStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug stuck"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug stuck"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will give debug output when the bot is stuck";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "debug" }; }
#endif
    };

    /// 策略：经验调试，在机器人获得经验时输出调试信息
    class DebugXpStrategy : public Strategy
    {
    public:
        DebugXpStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug xp"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug xp"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() { return "This strategy will give debug output when the bot gains xp"; }
        virtual std::vector<std::string> GetRelatedStrategies() { return {"debug"}; }
#endif
    };

    /// 策略：装备调试，在自动更换或对比装备时输出反馈
    class DebugEquipStrategy : public Strategy
    {
    public:
        DebugEquipStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "debug equip"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName()
        {
            return "debug equip";
        } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription()
        {
            return "This strategy will make the bot give chat feedback on equip actions.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {"debug"}; }
#endif
    };

}
