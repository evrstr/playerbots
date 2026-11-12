# Playerbots
Bot AI Core from ike3 for cmangos classic, tbc and wotlk  
适用于 CMaNGOS Classic、TBC 与 WotLK 的机器人 AI 核心（源自 ike3）

This system brings the following features:  
本系统提供以下功能特性：
- Populate the open world with playerbots  
  （使用玩家机器人填充大世界）
- Populate BGs and Arenas with playerbots  
  （使用玩家机器人填充战场与竞技场）
- Use alt characters as playerbots  
  （将同账号/小号角色作为玩家机器人召唤出战）
- Do any kind of PvE content (with some guidance on complex mechanics)  
  （参与各类 PvE 内容，复杂机制配合少量指令引导即可应对）
- Very detailed configurations of playerbot behaviors (for the min-maxers out there :D)  
  （提供极其详尽的玩家机器人行为配置项，适合喜欢极致调优的玩家 :D）
- Multiple commands to request playerbots do what you require  
  （提供丰富命令，随时指示玩家机器人执行各种操作）

# How to install
> 中文：安装指南
## Compiling Code
> 中文：编译代码
If you're new to building CMaNGOS, check the official guide  
https://github.com/cmangos/issues/wiki/Installation-Instructions  
如果你是首次编译 CMaNGOS，请先参阅官方编译指南：  
https://github.com/cmangos/issues/wiki/Installation-Instructions

Important: to enable the playerbots you need to check it in cmake ( `BUILD_PLAYERBOTS` ✅ )  
重要提示：要启用 Playerbots 模块，必须在 CMake 中勾选 `BUILD_PLAYERBOTS`（✅）。

After successful build get aiplayerbot.conf file from "src/modules/Bots/playerbot/aiplayerbot%expansion.conf.dist" (based on expansion you use) and put it to the same folder where mangosd.conf and realmd.conf are, and remove ".dist" from its name  
编译成功后，根据所使用的资料片版本，从 `"src/modules/Bots/playerbot/aiplayerbot%expansion.conf.dist"` 获取配置文件，将其复制到 `mangosd.conf` 和 `realmd.conf` 所在的同一目录中，并去掉文件名末尾的 `".dist"`（重命名为 `aiplayerbot.conf`）。

## Apply DB modifications
> 中文：应用数据库变更
- Using the `InstallFullDB.sh` script:  
  （使用 `InstallFullDB.sh` 脚本自动导入：）
  1. Execute the script once to generate the `InstallFullDB.config` file, after that close the script  
     （先运行一次脚本以生成 `InstallFullDB.config` 文件，随后关闭脚本）
  2. Edit `InstallFullDB.config` and add `PLAYERBOTS_DB="YES"` at the end and save it  
     （编辑 `InstallFullDB.config`，在文件末尾添加 `PLAYERBOTS_DB="YES"` 并保存）
  3. Depending on if you have a previous installation or want to do a fresh installation:  
     （根据你是已有旧库还是全新安装，选择对应选项：）
     - For a fresh install pick the option `4) Full installation`  
       （全新安装请选择 `4) Full installation`）
     - To install only the playerbots DB pick the option `5) Advanced DB management` and then `8) Create and fill playerbots db`  
       （若仅需安装 playerbots 数据库，请选择 `5) Advanced DB management`，再选择 `8) Create and fill playerbots db`）

- Manually:  
  （手动导入方式：）
  1.  Go to "src/modules/Bots/sql"  
      （进入 `"src/modules/Bots/sql"` 目录）
  2.  Apply .sql files from "characters" folder to characters database  
      （将 `"characters"` 文件夹下的 `.sql` 文件导入到 `characters` 数据库）
  3.  Apply .sql files from "world" folder to world database  
      （将 `"world"` 文件夹下的 `.sql` 文件导入到 `world` 数据库）
  
  **IMPORTANT**: There are several .sql files that are in a `vanilla`, `tbc` or `wotlk` folder. You should only use the files in the folder for the core expansion you are currently using.  
  **重要提示**：部分 `.sql` 文件按版本存放在 `vanilla`、`tbc` 或 `wotlk` 子目录中，请务必只导入与当前服务端资料片对应的目录中的文件。

After you complete all steps above you can check bots config and start your server. It'll take some time for the first time, as gear/characters for bots will be generated at first launch. Have fun! 🥳  
完成上述所有步骤后，即可检查机器人配置并启动服务器。首次启动会花费一些时间用于自动生成机器人角色与装备。祝游戏愉快！🥳

## How to Use
> 中文：使用方式与相关资源
- [List of Commands](https://docs.google.com/document/d/1xIdu5l5lAKLSKhqZ2Hb6vaU8qJgbbLwCw4MxmhCW_gI/edit#heading=h.vsmxe9r82yc7) — 命令列表
- [Playerbots Behavior AddOn](https://github.com/celguar/mangosbot-addon) — Playerbots 行为控制插件
- [Playerbot Inventory AddOn](https://github.com/davidonete/mangosbot-EngBags) — Playerbot 背包管理插件
- [Playerbots Discord Channel](https://discord.gg/vmjZUnPUdr) — Playerbots Discord 频道
