# PlayerBots documentation
> 中文：PlayerBots 模块文档

This folder holds the documentation for the PlayerBots module.  
本目录存放 PlayerBots 模块的相关文档。

## Status
> 中文：文档状态

The documentation for the **new playerbot system** (strategies, triggers, actions, values, commands, configuration, random bot population, travel and questing) is **pending**. It is being written and will be added to this folder as separate files.  
**新版 playerbot 系统**（策略 strategies、触发器 triggers、动作 actions、数值 values、命令、配置、随机机器人生态、移动寻路与任务系统）的文档**仍在编写中**，完成后将作为独立文档陆续添加到本目录。

Until then, more information about the new system can be found on the **CMaNGOS Discord** (look for the playerbots channels). The configuration template `playerbot/aiplayerbot.conf.dist.in` documents every setting inline, and `.rndbot help` / `help` in game list the available commands.  
在此之前，你可以在 **CMaNGOS Discord**（查找 playerbots 相关频道）获取更多关于新系统的信息。配置模板 `playerbot/aiplayerbot.conf.dist.in` 中对每个配置项都附有行内注释，游戏内执行 `.rndbot help` / `help` 也可列出可用命令。

## Available documents
> 中文：可用文档列表

| File | Content |
|---|---|
| [OldPartyBot.md](OldPartyBot.md) | Replacement for the deprecated in-core PlayerBot ("old playerbot" / "partybot"): the `AiPlayerbot.PartyBotOnly` compatibility mode, the related settings, and a command reference mapping every old command to this module. （用于替代已弃用核心内建 PlayerBot / "partybot" 的兼容方案：介绍 `AiPlayerbot.PartyBotOnly` 兼容模式、相关配置项，以及旧系统全部命令到本模块的完整映射参考。） |
