#pragma once

namespace ai
{
    /// 机器人测试日志分析工具类，用于汇总 PID、事件、任务、计数与测试结果
    class LogAnalysis
    {
    public:
        //Constructors | 构造函数
        LogAnalysis() {};

        static void RunAnalysis();

        static void AnalysePid();
        static void AnalyseEvents();
        static void AnalyseQuests();
        static void AnalyseCounts();
        static void AnalyseTestResults();
    };    
}
