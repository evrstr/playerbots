/// 区域触发器（AreaTrigger）范围检测
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 触发器：检测机器人当前坐标是否位于最近一次记录的 AreaTrigger 区域内
    class WithinAreaTrigger : public Trigger {
    public:
        WithinAreaTrigger(PlayerbotAI* ai) : Trigger(ai, "within area trigger") {}

        virtual bool IsActive() override
        {


            LastMovement& movement = context->GetValue<LastMovement&>("last area trigger")->Get();
            if (!movement.lastAreaTrigger)
                return false;

            AreaTriggerEntry const* atEntry = sAreaTriggerStore.LookupEntry(movement.lastAreaTrigger);
            if(!atEntry)
                return false;

            AreaTrigger const* at = sObjectMgr.GetAreaTrigger(movement.lastAreaTrigger);
            if (!at)
                return false;

            return IsPointInAreaTriggerZone(atEntry, bot->GetMapId(), bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), 0.5f);
        }

    private:
        /// 判断指定三维坐标是否在球形或旋转长方体 AreaTrigger 范围内
        bool IsPointInAreaTriggerZone(AreaTriggerEntry const* atEntry, uint32 mapid, float x, float y, float z, float delta)
        {
            if (mapid != atEntry->mapid)
                return false;

            if (atEntry->radius > 0)
            {
                // if we have radius check it | 若定义了球形半径则按距离平方检测
                float dist2 = (x - atEntry->x) * (x - atEntry->x) + (y - atEntry->y) * (y - atEntry->y) + (z - atEntry->z) * (z - atEntry->z);
                if (dist2 > (atEntry->radius + delta) * (atEntry->radius + delta))
                    return false;
            }
            else
            {
                // we have only extent | 否则按长方体边界范围检测

                // rotate the players position instead of rotating the whole cube, that way we can make a simplified | 旋转玩家坐标而非旋转整个立方体，从而简化为轴对齐包围盒判定
                // is-in-cube check and we have to calculate only one point instead of 4 | 这样只需变换一个点而无需计算四个顶点

                // 2PI = 360, keep in mind that ingame orientation is counter-clockwise | 2PI = 360度，注意游戏内朝向为逆时针方向
                double rotation = 2 * M_PI - atEntry->box_orientation;
                double sinVal = sin(rotation);
                double cosVal = cos(rotation);

                float playerBoxDistX = x - atEntry->x;
                float playerBoxDistY = y - atEntry->y;

                float rotPlayerX = float(atEntry->x + playerBoxDistX * cosVal - playerBoxDistY * sinVal);
                float rotPlayerY = float(atEntry->y + playerBoxDistY * cosVal + playerBoxDistX * sinVal);

                // box edges are parallel to coordiante axis, so we can treat every dimension independently :D | 立方体边与坐标轴平行，因此可以独立检验每个坐标轴
                float dz = z - atEntry->z;
                float dx = rotPlayerX - atEntry->x;
                float dy = rotPlayerY - atEntry->y;
                if ((fabs(dx) > atEntry->box_x / 2 + delta) ||
                        (fabs(dy) > atEntry->box_y / 2 + delta) ||
                        (fabs(dz) > atEntry->box_z / 2 + delta))
                {
                    return false;
                }
            }

            return true;
        }
    };
}
