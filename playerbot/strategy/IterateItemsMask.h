/// 背包物品遍历范围位掩码（背包/已装备/银行/回购/全部）
enum class IterateItemsMask : uint8
{
    ITERATE_ITEMS_IN_BAGS = 1,
    ITERATE_ITEMS_IN_EQUIP = 2,
    ITERATE_ITEMS_IN_BANK = 4,
    ITERATE_ITEMS_IN_BUYBACK = 8,
    ITERATE_ALL_ITEMS = 255
};
