#ifndef _PerformanceMonitor_H
#define _PerformanceMonitor_H
#define PMO_MEMTEST

#include "Common.h"
#include "PlayerbotAIBase.h"

#include <mutex>
#include <chrono>
#include <ctime>

typedef std::vector<std::string> PerformanceStack;

/// 单项性能统计数据（最小耗时、最大耗时、总耗时与调用次数）
struct PerformanceData
{
    uint32 minTime, maxTime, totalTime, count;
    std::mutex lock;
};

/// 性能监控维度枚举（状态值/触发器/动作/随机机器人/总计）
enum PerformanceMetric
{
    PERF_MON_VALUE,
    PERF_MON_TRIGGER,
    PERF_MON_ACTION,
    PERF_MON_RNDBOT,
    PERF_MON_TOTAL
};

/// RAII 作用域性能计时器，析构时自动累计耗时并弹出调用栈
class PerformanceMonitorOperation
{
public:
    PerformanceMonitorOperation(PerformanceData& data, std::string name, PerformanceStack* stack);
    ~PerformanceMonitorOperation();

private:
    void finish();

    PerformanceData& data;
    std::string name;
    PerformanceStack* stack;
#ifdef CMANGOS
    std::chrono::milliseconds started;
#endif
};

/// 字符串调用栈向量的哈希仿函数
struct VectorStringHash
{
    std::size_t operator()(const std::vector<std::string>& v) const
    {
        std::size_t seed = 0;
        for (const auto& str : v)
        {
            // Combine with XOR and bit shifting (fast)
            seed ^= std::hash<std::string> {}(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

using performanceMap = std::unordered_map<std::vector<std::string>, PerformanceData, VectorStringHash>;
using performanceMetricMap = std::map<PerformanceMetric, performanceMap>;
using performanceInstanceMap = std::map<uint32, performanceMetricMap>;
using performanceMapMap = std::map<uint32, performanceInstanceMap>;

/// 机器人 AI 性能分析器，按地图与实例维度统计各模块耗时
class PerformanceMonitor
{
    public:
        PerformanceMonitor();
        virtual ~PerformanceMonitor();
        static PerformanceMonitor& instance()
        {
            static PerformanceMonitor instance;
            return instance;
        }

    public:
        std::unique_ptr<PerformanceMonitorOperation> start(PerformanceMetric metric, std::string name, PerformanceStack* stack = nullptr, uint32 mapId = 0, uint32 instanceId = 0);
        std::unique_ptr<PerformanceMonitorOperation> start(PerformanceMetric metric, std::string name, PlayerbotAI* ai);
        void PrintStats(bool perTick = false,  bool fullStack = false, bool showMap = false);
        void Reset();
        void Init(uint32 mapId, uint32 instanceId);
    private:
        performanceMetricMap data;
        performanceMapMap mapsData;
        //std::mutex lock;
};


#define sPerformanceMonitor PerformanceMonitor::instance()

#endif

