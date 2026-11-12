#pragma once

#include "SeeSpellAction.h"
#include "playerbot/strategy/values/RTSCValues.h"

namespace ai
{    
    #define RTSC_MOVE_SPELL 30758 // Aedm (Awesome Energetic do move) (Aedm（快速活力移动调试命令）)

    /// RTS 战术指令控制动作：处理即时战略式多机器人点选、编队、定点移动与施法指令
    class RTSCAction : public SeeSpellAction, public Qualified
    {
    public:
        /// 构造函数：初始化RTS 战术指令控制动作
        RTSCAction(PlayerbotAI* ai) : SeeSpellAction(ai, "rtsc"), Qualified() {}
        /// 执行动作主逻辑（RTS 战术指令控制动作）
        virtual bool Execute(Event& event) override;
    };
}
