/// 透传（PassThrough）策略基类头文件
#pragma once

namespace ai
{
    /// 策略基类：将 supported 列表中的触发器名称直接 1:1 透传映射为同名执行动作
    class PassTroughStrategy : public Strategy
    {
    public:
        PassTroughStrategy(PlayerbotAI* ai, float relevance = ACTION_PASSTROUGH) : Strategy(ai), relevance(relevance) {}

    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override
        {
            for (std::list<std::string>::iterator i = supported.begin(); i != supported.end(); i++)
            {
                std::string s = i->c_str();
                triggers.push_back(new TriggerNode(
                    s, 
                    NextAction::array(0, new NextAction(s, relevance), NULL)));
            }
        }

        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override
        {
            for (std::list<std::string>::iterator i = supported.begin(); i != supported.end(); i++)
            {
                std::string s = i->c_str();
                triggers.push_back(new TriggerNode(
                    s,
                    NextAction::array(0, new NextAction(s, relevance), NULL)));
            }
        }

        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override
        {
            for (std::list<std::string>::iterator i = supported.begin(); i != supported.end(); i++)
            {
                std::string s = i->c_str();
                triggers.push_back(new TriggerNode(
                    s,
                    NextAction::array(0, new NextAction(s, relevance), NULL)));
            }
        }

    protected:
        std::list<std::string> supported;
        float relevance;
    };
}
