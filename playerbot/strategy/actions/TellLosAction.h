#pragma once
#include "GenericActions.h"

namespace ai
{
   /// 视野过滤修饰符类型枚举：定义 los 命令支持的筛选、排序与输出格式修饰符
   enum class LosModifierType
   {
      FilterName,   // filter:name:<text> (过滤：按名称匹配)
      SortRange,    // sort:range (排序：按距离由近到远)
      FilterRange,  // filter:range (过滤：按距离范围)
      FilterFirst,  // filter:first (过滤：仅首个)
      ShowRange,    // show:range (显示：距离)
      ShowGuid,     // show:guid (显示：GUID)
   };

   /// 视野过滤修饰符结构体：保存解析后的 los 命令过滤参数
   struct LosModifierStruct
   {
      LosModifierType typ;
      std::string param;
   };

    /// 汇报视野对象指令动作：列出机器人当前视野内的生物、玩家、宝箱或可交互物体
    class TellLosAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化汇报视野对象指令动作
        TellLosAction(PlayerbotAI* ai) : ChatCommandAction(ai, "los") {}
        /// 执行动作主逻辑（汇报视野对象指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（汇报视野对象指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 解析 los 命令附带的过滤、排序与展示修饰符
        static std::vector<LosModifierStruct> ParseLosModifiers(const std::string& str);
        /// 将 ObjectGuid 列表转换为有效的 GameObject 指针列表
        static std::list<GameObject*> GoGuidListToObjList(PlayerbotAI* ai, const std::list<ObjectGuid>& gos);
        /// 从候选游戏对象列表中过滤掉不可交互或无效的对象
        static std::list<GameObject*> FilterGameObjects(Player* requester, const std::list<GameObject*>& gos, const std::vector<LosModifierStruct>& mods);

    private:
        /// 列出周围或调试目标的单位信息列表
        void ListUnits(Player* requester, std::string title, std::list<ObjectGuid> units);

        /// 汇报视野或目标周围符合条件的游戏对象列表
        void TellGameObjects(Player* requester, std::string title, const std::list<GameObject*>& gos, const std::vector<LosModifierStruct>& mods);
    };
}
