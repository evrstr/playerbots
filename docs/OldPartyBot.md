# Old PartyBot compatibility (`AiPlayerbot.PartyBotOnly`)
> 中文：旧版 PartyBot 兼容模式（`AiPlayerbot.PartyBotOnly`）

This document describes how the PlayerBots module covers the use case of the **deprecated in-core PlayerBot** (the "old playerbot" or "partybot", built with `BUILD_DEPRECATED_PLAYERBOT`, sources in `src/game/PlayerBot/`, docs in `doc/PlayerBot/`). It lists the configuration, what the compatibility mode changes, and every old command with its counterpart in this module.  
本文档说明 PlayerBots 模块如何覆盖**已弃用的核心内建 PlayerBot**（即“旧版 playerbot”或“partybot”，编译选项为 `BUILD_DEPRECATED_PLAYERBOT`，源码位于 `src/game/PlayerBot/`，文档位于 `doc/PlayerBot/`）的使用场景。文档列出相关配置项、兼容模式带来的行为变化，以及所有旧命令在本模块中的对应命令。

Contents / 目录

1. [What the old system was / 旧系统简介](#1-what-the-old-system-was)
2. [Configuration reference / 配置参考](#2-configuration-reference)
3. [What `PartyBotOnly = 1` does / `PartyBotOnly = 1` 的作用](#3-what-partybotonly--1-does)
4. [Getting started (old workflow) / 快速上手（旧版工作流）](#4-getting-started-old-workflow)
5. [Command reference: old command to module command / 命令参考：旧命令到模块命令映射](#5-command-reference-old-command-to-module-command)
6. [Native commands added for old-system parity / 为对齐旧系统新增的原生命令](#6-native-commands-added-for-old-system-parity)
7. [Known differences and limits / 已知差异与限制](#7-known-differences-and-limits)
8. [Expansions / 资料片差异](#8-expansions)
9. [Testing and debugging / 测试与调试](#9-testing-and-debugging)

---

## 1. What the old system was
> 中文：1. 旧系统是什么

- Bots were **real player characters from the master's own account** (up to 9), logged in with `.bot add <character>` and controlled with whispers or party chat (`/t BOTNAME ...`, `/p ...`). There was no random bot population, no travel or questing agenda: a bot only followed, fought, looted and did what its master said.  
  （机器人是**主人自己账号下的真实玩家角色**（最多 9 个），通过 `.bot add <character>` 登录，并使用密语或队伍聊天（`/t BOTNAME ...`、`/p ...`）控制。没有随机机器人生态，也没有自行游历或做任务的日程：机器人只会跟随、战斗、拾取并严格执行主人的指令。）
- Orders used a fixed syntax such as `orders combat tank`, `follow far`, `pull test`, `survey`, `get [object]`, `process mill [herbs]`, `auction add [item]`.  
  （指令采用固定语法，例如 `orders combat tank`、`follow far`、`pull test`、`survey`、`get [object]`、`process mill [herbs]`、`auction add [item]`。）
- Extras: a "bot guy" NPC that sold bots, per-bot summon costs, a set of loot-collection flags (`collect`), and gameobject fetching (`survey`, `find`, `get`).  
  （附加功能包括：出售机器人的“bot guy”NPC、按次计费的召唤费用、一组拾取采集标志（`collect`），以及游戏对象采集（`survey`、`find`、`get`）。）

The PlayerBots module already shares the core-level login plumbing of the old system (`PlayerbotHolder`, `PlayerbotLoginQueryHolder`), so bots added by a player are the same kind of characters. What the module lacked for a partybot user was:  
PlayerBots 模块本身已经复用了旧系统的核心登录底层（`PlayerbotHolder`、`PlayerbotLoginQueryHolder`），因此玩家添加的机器人本质上是同一类角色。对于 partybot 用户而言，本模块此前缺少的是：

- a quiet profile (player-added bots used to run the full strategy tree),  
  （安静的行为配置：此前玩家添加的机器人也会运行完整的自主策略树，）
- the old command spellings,  
  （旧版命令拼写，）
- a handful of features (object fetching, mill/prospect, combat orders by name, resistance orders, costs, auction commands).  
  （以及少数专项功能：物体采集、研磨/选矿、按角色名指定战斗指令、抗性指令、费用机制、拍卖行命令。）

All of these are now covered by the switch described below and by new native commands that work in every mode.  
上述所有能力现已通过下文介绍的开关以及在所有模式下均可使用的新增原生命令全面覆盖。

---

## 2. Configuration reference
> 中文：2. 配置参考

All settings live in `aiplayerbot.conf` (template: `aiplayerbot.conf.dist.in`). A restart is required after changing `PartyBotOnly`. `.rndbot reload` re-reads the file at runtime, but bots that are already online keep the agenda they were created with.  
所有配置均位于 `aiplayerbot.conf`（模板文件：`aiplayerbot.conf.dist.in`）。修改 `PartyBotOnly` 后需要重启服务器。虽然 `.rndbot reload` 可在运行时重新读取配置文件，但已经在线的机器人仍会保留其创建时所加载的行为日程。

| Key | Default | Meaning |
|---|---|---|
| `AiPlayerbot.PartyBotOnly` | `0` | Master switch for the compatibility mode. See [section 3](#3-what-partybotonly--1-does). `0` leaves every behaviour unchanged.<br>兼容模式总开关，详见[第 3 节](#3-what-partybotonly--1-does)。设为 `0` 时所有行为保持默认不变。 |
| `AiPlayerbot.BotAddCost` | `0` | Copper charged to a **non-GM player** for each bot added with `.bot add` or `.bot login`. Charged once the bot is actually online. Never applies to random bots, autologin or console adds. Negative values are treated as `0`.<br>**非 GM 玩家**每次通过 `.bot add` 或 `.bot login` 添加机器人时扣除的铜币数量。在机器人实际登录上线后扣费。对随机机器人、自动登录或控制台添加绝不收费。负值按 `0` 处理。 |
| `AiPlayerbot.BotSummonCost` | `0` | Copper charged to a **non-GM player** each time the `summon` command brings a bot to them. Applies on top of `AiPlayerbot.NonGmFreeSummon`. Meeting stone rituals and short-range unstuck teleports are free.<br>**非 GM 玩家**每次使用 `summon` 命令将机器人召唤到身边时扣除的铜币数量。该费用在 `AiPlayerbot.NonGmFreeSummon` 之上额外生效。集合石召唤仪式和短距离防卡死传送免费。 |
| `AiPlayerbot.LootDistanceMax` | `50.0` | Upper limit (yards) for the per-bot loot distance a player can set with `collect ... distance:N` or `range loot`.<br>玩家通过 `collect ... distance:N` 或 `range loot` 为单个机器人设置拾取距离时的上限（单位：码）。 |

Existing settings that interact with the mode:  
与该模式存在交互的现有配置项：

| Key | Interaction |
|---|---|
| `AiPlayerbot.AllowMultiAccountAltBots` | Ignored while `PartyBotOnly = 1`: only the requesting player's own account is allowed.<br>当 `PartyBotOnly = 1` 时忽略此项：仅允许添加请求玩家自己账号下的角色。 |
| `AiPlayerbot.NonCombatStrategies` | Filtered for player-added bots while `PartyBotOnly = 1` (see section 3).<br>当 `PartyBotOnly = 1` 时，对玩家添加的机器人进行过滤（参见第 3 节）。 |
| `AiPlayerbot.NonGmFreeSummon` | Lets non-GM players summon without a meeting stone or innkeeper. `BotSummonCost` still applies.<br>允许非 GM 玩家无需集合石或旅店老板即可召唤机器人；`BotSummonCost` 依然生效。 |
| `AiPlayerbot.SightDistance` | Search radius used by `survey`, `find` and `get`.<br>`survey`、`find` 和 `get` 命令使用的搜索半径。 |
| `AiPlayerbot.LootDistance`, `AiPlayerbot.GroupMemberLootDistance` | Default loot distances. A per-bot value set with `collect`/`range loot` overrides them.<br>默认拾取距离。通过 `collect` / `range loot` 为单个机器人设置的值会覆盖这两项默认配置。 |
| `AiPlayerbot.CommandSeparator` | Separator for multiple commands in one message. The old-wording translation does not rely on it.<br>单条消息中分隔多个命令的分隔符。旧版命令拼写转换不依赖此项。 |

Money values are in copper: `10000` = 1 gold, `100` = 1 silver.  
金额单位均为铜币：`10000` = 1 金，`100` = 1 银。

### Example: classic partybot setup
> 中文：示例：经典 partybot 配置

```
AiPlayerbot.Enabled = 1
AiPlayerbot.PartyBotOnly = 1
AiPlayerbot.BotAddCost = 0
AiPlayerbot.BotSummonCost = 0
```

---

## 3. What `PartyBotOnly = 1` does
> 中文：3. `PartyBotOnly = 1` 的作用

One switch, four effects.  
一个开关，带来四项效果。

### 3.1 No bot population
> 中文：3.1 关闭随机机器人生态

The random bot system is switched off completely: spawning, login churn, wandering, guild, quest and battleground agendas, free bots and offline-group bots. After startup `.rndbot stats` reports `0 online` until a player adds a bot. The player-facing bot machinery (sessions, per-bot updates, `.bot add`) keeps working normally.  
随机机器人系统完全关闭：包括生成、上下线轮换、游荡、公会/任务/战场日程、自由机器人以及离线组队机器人。服务器启动后，在玩家手动添加机器人之前，`.rndbot stats` 将报告 `0 online`。面向玩家的机器人机制（会话管理、单机器人更新循环、`.bot add`）均正常运作。

### 3.2 Own-account adds only
> 中文：3.2 仅限添加自己账号下的角色

`.bot add` / `.bot login` accept only characters of the **requesting player's own account**, like the old system. Characters of other accounts, random-account characters and multi-account alt bots are refused with `Not in your account`. `.bot create` brings the new character online immediately (subject to `BotAddCost`).  
与旧系统一致，`.bot add` / `.bot login` 仅接受**请求玩家本人账号下**的角色。其他账号的角色、随机机器人账号角色以及跨账号小号机器人均会被拒绝，并返回 `Not in your account`。`.bot create` 会立即将新建角色登录上线（受 `BotAddCost` 扣费限制）。

### 3.3 Quiet agenda for player-added bots
> 中文：3.3 玩家所添机器人的安静日程（精简非战斗策略）

A bot that has a real player as master gets this non-combat set:  
以真实玩家为主人的机器人将仅获得以下非战斗策略集合：

- class strategies (talent spec, `dps assist` / `tank assist`, `cure`, `buff`, `boost` where the class has them), `wbuff`, `avoid mobs`, `dungeon`  
  （职业相关策略：天赋专精、`dps assist` / `tank assist`、`cure`、`buff`、`boost`（若该职业具备），以及 `wbuff`、`avoid mobs`、`dungeon`）
- `racials`, `nc`, `food`, `follow` (or `wander` when configured), `default`, `quest` (quest sharing), `loot`, `collision`, `buff`, `mount`  
  （种族特长 `racials`、`nc`、食物恢复 `food`、`follow`（或在配置时为 `wander`）、`default`、`quest`（任务共享）、`loot`、`collision`、`buff`、`mount`）
- `return` and `delayed roll` from `AiPlayerbot.NonCombatStrategies`  
  （来自 `AiPlayerbot.NonCombatStrategies` 的 `return` 与 `delayed roll`）
- `rpg jump` and `follow jump` if the corresponding jump options are enabled  
  （若启用了对应的跳跃选项，则包含 `rpg jump` 与 `follow jump`）

Not loaded: `grind`, `travel`, `tfish`, `gather`, `maintenance`, `free`, `bg`, `lfg`, `start duel`, `attack tagged`, `dksquest`, every `rpg ...` strategy except `rpg jump`, duels and emotes.  
不会加载的策略：`grind`、`travel`、`tfish`、`gather`、`maintenance`、`free`、`bg`、`lfg`、`start duel`、`attack tagged`、`dksquest`、除 `rpg jump` 以外的所有 `rpg ...` 策略，以及决斗和表情动作策略。

Strategies **saved in the database** for the character are filtered the same way when the bot logs in, so an alt that was once a random bot does not bring its old agenda back. Removals (`-strategy`) are never filtered. You can still switch a strategy on by hand (`nc +grind`); it is filtered again at the next login.  
角色**保存在数据库中的策略**在登录时也会按相同规则进行过滤，因此曾经做过随机机器人的小号不会把旧日程带回来。移除项（`-strategy`）不会被过滤。你仍然可以手动开启某项策略（如 `nc +grind`），但下次登录时会再次被过滤。

Random bots, bots without a real player master and every run with `PartyBotOnly = 0` are unaffected.  
随机机器人、没有真实玩家作为主人的机器人，以及 `PartyBotOnly = 0` 下的所有运行均不受此过滤影响。

### 3.4 Old command wording
> 中文：3.4 旧版命令写法兼容

The old whisper spellings listed in [section 5](#5-command-reference-old-command-to-module-command) are rewritten to module commands. The rewrite is plain text only; permission checks run afterwards exactly as for any other command. The native module commands from [section 6](#6-native-commands-added-for-old-system-parity) work in **all** modes.  
[第 5 节](#5-command-reference-old-command-to-module-command)中列出的旧版密语写法会被改写为本模块命令。该改写仅作纯文本替换；权限检查随后与其他任何命令完全一致地执行。[第 6 节](#6-native-commands-added-for-old-system-parity)中的原生模块命令则在**所有**模式下均可用。

---

## 4. Getting started (old workflow)
> 中文：4. 快速上手（旧版工作流）

1. Set `AiPlayerbot.PartyBotOnly = 1` and restart the server.  
   （设置 `AiPlayerbot.PartyBotOnly = 1` 并重启服务器。）
2. Log in with your account and add bots from your own characters: `.bot add Name` (several: `.bot add Name1,Name2`).  
   （使用你的账号登录游戏，从自己的角色中添加机器人：`.bot add Name`；添加多个可使用 `.bot add Name1,Name2`。）
3. Whisper or use party chat: `/t Name follow`, `/p attack`. Party chat commands are obeyed by every bot in the group, as in the old system.  
   （使用密语或队伍聊天发送指令：`/t Name follow`、`/p attack`。与旧系统相同，队伍聊天中的命令会由小队中的所有机器人共同执行。）
4. Give orders: `orders combat tank`, `orders delay 3`, `pull test`, `survey`, ...  
   （下达指令：`orders combat tank`、`orders delay 3`、`pull test`、`survey` 等。）
5. `.bot remove Name` (or `logout`) when done.  
   （使用完毕后执行 `.bot remove Name` 或 `logout` 离线。）

Bot ownership, grouping, invitations and master detection are unchanged from the standard module behaviour.  
机器人归属权、组队、邀请与主人识别机制与标准模块行为完全一致。

---

## 5. Command reference: old command to module command
> 中文：5. 命令参考：旧命令到模块命令的映射

Legend: **alias** = the old spelling is rewritten only while `PartyBotOnly = 1`; **native** = the same words already work in every mode; **changed** = works but behaves differently from the old bot.  
图例：**alias（别名）** = 仅在 `PartyBotOnly = 1` 时将旧拼写改写为模块命令；**native（原生）** = 相同词句在所有模式下均可直接工作；**changed（行为有变）** = 可用但行为与旧版机器人有所差异。

### 5.1 Lifecycle
> 中文：5.1 生命周期管理

| Old | Module | Notes |
|---|---|---|
| `.bot add <char>` | `.bot add <char>` | native. With `PartyBotOnly = 1`: own account only.<br>原生支持。`PartyBotOnly = 1` 时仅限本人账号角色。 |
| `.bot remove <char>` | `.bot remove` / `logout` | native<br>原生支持。 |
| Auto-accept invites, rejoin group | handled by the module | native<br>原生支持：由模块自动处理组队邀请接受与重新入队。 |
| Bot guy NPC (bots for sale) | not implemented | See [section 7](#7-known-differences-and-limits).<br>未实现，详见[第 7 节](#7-known-differences-and-limits)。 |
| Cost per bot / per summon | `AiPlayerbot.BotAddCost`, `AiPlayerbot.BotSummonCost` | see [6.7](#67-costs)<br>见 [6.7](#67-costs)。 |

### 5.2 Movement and basic orders
> 中文：5.2 移动与基础指令

| Old | Module | Notes |
|---|---|---|
| `attack`, `assist`, `stay`, `follow` | same words | native<br>原生支持，命令相同。 |
| `follow far` / `follow near` | `range follow <distance>` | alias. Moves the follow distance by 0.5 yd per command. `range follow ?` shows the value.<br>别名。每次命令将跟随距离增减 0.5 码。`range follow ?` 可查看当前值。 |
| `follow reset`, `follow auto`, `follow info` | `range follow ...` | the module has no automatic variable follow distance; use `range follow` directly<br>本模块没有自动动态跟随距离，请直接使用 `range follow`。 |
| `pull` | `pull` | native<br>原生支持。 |
| `pull test` | `pull capability` | alias. Reports whether the bot can pull and with which ability, even if the `pull` strategy is off ("I can pull with serpent sting.").<br>别名。即使未开启 `pull` 策略，也会报告机器人能否开怪以及使用何种技能（如 `"I can pull with serpent sting."`）。 |
| `pull ready` | `pull readiness` | alias. Checks your selected target: range, line of sight, ability.<br>别名。检查你当前选中目标的距离、视野（LoS）与可用技能状态。 |
| `neutralize` | `cast <crowd control spell>` | alias, class aware: mage Polymorph, priest Shackle Undead, druid Hibernate, hunter Scare Beast. Other classes get no reply. Needs the spell to be known.<br>别名，具备职业感知：法师变形术、牧师束缚亡灵、德鲁伊休眠、猎人恐吓野兽。其他职业无响应。机器人需已学会对应法术。 |
| `reset` | `reset` | native: resets states and orders<br>原生支持：重置状态与指令。 |
| `spells`, `cast`, `c` | same | native<br>原生支持，命令相同。 |
| `stats` | `stats` | native<br>原生支持。 |

### 5.3 Combat orders
> 中文：5.3 战斗指令

All `orders combat ...` spellings are **alias** and need `PartyBotOnly = 1`. The first old-style order after a restore point saves the bot's current combat setup, so `resumeorders` can bring it back.  
所有 `orders combat ...` 写法均为 **alias（别名）**，需要开启 `PartyBotOnly = 1`。在恢复点之后的第一个旧式战斗指令会自动保存机器人当前的战斗配置快照，以便随后通过 `resumeorders` 还原。

| Old | Module | Notes |
|---|---|---|
| `orders combat tank` / `maintank` | `co +tank` | Primary orders replace each other, like the old bot.<br>主职责指令之间互斥替换，与旧版机器人一致。 |
| `orders combat heal` / `mainheal` | `co +heal` | |
| `orders combat notmainheal` | `co +offheal` | closest module equivalent<br>模块中最接近的等效职责。 |
| `orders combat assist` | `co +dps assist` | |
| `orders combat passive` | `co +passive` | |
| `orders combat nodispell` | `co +heal` | **changed.** The old order was a *secondary* order (heal, never dispel). Here it adds `heal` without clearing other roles and does not stop dispelling.<br>**行为有变。** 旧指令为*次级*指令（治疗且永不驱散）；此处仅添加 `heal` 而不清除其他职责，且不会禁止驱散。 |
| `orders combat assist <NAME>` | `order assist <NAME>` | see [6.1](#61-named-assist-and-protect)<br>见 [6.1](#61-named-assist-and-protect)。 |
| `orders combat protect <NAME>` | `order protect <NAME>` | see [6.1](#61-named-assist-and-protect)<br>见 [6.1](#61-named-assist-and-protect)。 |
| `orders combat resistfire` / `resistfrost` / `resistnature` / `resistshadow` | `resist <school>` | see [6.2](#62-resistance-orders). Also accepted with a space: `orders combat resist fire`.<br>见 [6.2](#62-resistance-orders)。同样支持带空格写法：`orders combat resist fire`。 |
| `orders combat reset` | clears primary orders, the named assist/protect target and the resist order | 清除主战斗职责、按名指定的协助/保护目标以及抗性指令。 |
| `orders delay <n>` | `wait for attack time <n>` | The module accepts a wider range than the old 0 to 10 seconds.<br>本模块接受比旧版 0~10 秒更宽的延迟范围。 |
| `orders` (show orders) | `order`, `co ?` | different spelling, not translated. `order` reports the named assist/protect state, `co ?` lists all combat strategies.<br>拼写不同，未做自动改写。`order` 报告按名协助/保护状态，`co ?` 列出所有战斗策略。 |
| `resumeorders` | `co restore` | alias. Restores the snapshot taken by the first order.<br>别名。恢复首个指令时保存的战斗配置快照。 |

Native module equivalents work in every mode: `co +tank`, `co -tank`, `co ?`, `co save`, `co restore`, `order ...`, `resist ...`, `wait for attack time N`.  
本模块原生等效命令在所有模式下均可用：`co +tank`、`co -tank`、`co ?`、`co save`、`co restore`、`order ...`、`resist ...`、`wait for attack time N`。

### 5.4 Looting and gameobjects
> 中文：5.4 拾取与游戏对象采集

| Old | Module | Notes |
|---|---|---|
| `collect` | `collect` | native, see [6.3](#63-collect)<br>原生支持，见 [6.3](#63-collect)。 |
| `collect <flags> distance:N` | same | native<br>原生支持，命令相同。 |
| `survey` | `survey` | native, see [6.4](#64-survey-find-get)<br>原生支持，见 [6.4](#64-survey-find-get)。 |
| `find [object]` | `find [object]` | native<br>原生支持。 |
| `get [object]` | `get [object]` | native<br>原生支持。 |

### 5.5 Items, professions and services
> 中文：5.5 物品、专业技能与系统服务

| Old | Module | Notes |
|---|---|---|
| `use [item]`, `u` | same | native (items, quest items, containers, on target or object)<br>原生支持（物品、任务物品、容器，可对目标或对象使用）。 |
| `equip [item]`, `e` | same | native. `equip auto/info` toggles are not provided; the module decides gear upgrades itself.<br>原生支持。不提供 `equip auto/info` 开关，装备升级由模块自行评估决定。 |
| `sell [item]` | `sell` / `s` | native (see also below)<br>原生支持（亦见下文说明）。 |
| `sell all` | `sell` of junk | alias, see below<br>别名，出售垃圾物品，见下文说明。 |
| `buy [item]`, `drop [item]` | `buy`, `destroy` / `d` | native<br>原生支持。 |
| `repair`, `repair all` | `repair` | native<br>原生支持。 |
| `craft <profession>` | `craft <profession>` | native: lists learnt recipes as links. Accepts `alchemy a`, `blacksmithing b`, `cooking c`, `engineering e`, `firstaid f`, `leatherworking l`, `magic m` (enchanting), `smelting s`, `tailoring t`.<br>原生支持：以可点击链接形式列出已学配方。支持参数：`alchemy a`、`blacksmithing b`、`cooking c`、`engineering e`、`firstaid f`、`leatherworking l`、`magic m`（附魔）、`smelting s`、`tailoring t`。 |
| `craft [recipe]` | `craft [recipe]` | native<br>原生支持。 |
| `process disenchant [item]` (`process d`) | `cast 13262 [item]` | alias<br>别名（对应分解法术 13262）。 |
| `process mill [item]` (`process m`) | `mill [item]` | alias, see [6.5](#65-mill-and-prospect)<br>别名，见 [6.5](#65-mill-and-prospect)。 |
| `process prospect [item]` (`process p`) | `prospect [item]` | alias, see [6.5](#65-mill-and-prospect)<br>别名，见 [6.5](#65-mill-and-prospect)。 |
| `enchant [spell][item]`, `nt` | enchanting through trade and item-for-spell actions | native, behaviour unverified against the old flow<br>原生支持：通过交易窗口与对物品施法动作实现附魔，与旧流程的细节差异尚未逐一验证。 |
| `auction`, `auction add`, `auction remove` | `auction ...` | native, see [6.6](#66-auction)<br>原生支持，见 [6.6](#66-auction)。 |
| `mail inbox/getcash/getitem/delete` | `mail ?`, `mail take`, `mail delete`, `mail read` | native, different spelling. Note: a mail with both money and items is handled money first; check the result.<br>原生支持，拼写不同。注意：同时含金币与物品的邮件会优先取钱，请留意返回结果。 |
| `bank`, `bank deposit/withdraw` | `bank [+item]` / `bank [-item]` | native<br>原生支持。 |
| `talent ...`, `skill ...` | `talents`, `trainer`, `skill` | native, different spelling<br>原生支持，拼写不同。 |
| `quest ...` | `q`, `quests`, accept/drop/reward | native, different spelling<br>原生支持，拼写不同。 |
| `pet ...` | `pet ...` | native (call, dismiss, stay, follow, attack, autocast, aggressive/defensive/passive). Taming is not available.<br>原生支持（召唤、解散、停留、跟随、攻击、自动施法、主动/防御/被动模式）。不支持驯服宠物。 |
| Money request while trading (`10g`, `6g500s25c`) | `10g` | native: whisper the amount with a trade window open<br>原生支持：在打开交易窗口时密语对应金额即可。 |
| `help` | `help` | native<br>原生支持。 |

`sell all` (alias): sells **only junk** to a vendor in range: grey items and items the bot cannot use that have a sell price. It never sells equipped items, quest items or anything the bot could use or still needs. Replies `Sold N items for <money>`, `Nothing to sell.` or `I need a vendor nearby.` The module's own `sell` family is unchanged.  
`sell all`（别名）：向范围内的商人**仅出售垃圾物品**——包括灰色物品以及机器人无法使用且有售价的物品。绝不会出售已装备物品、任务物品或机器人仍可使用/需要的任何物品。机器人会回复 `Sold N items for <money>`、`Nothing to sell.` 或 `I need a vendor nearby.`。模块自身的 `sell` 命令族保持不变。

---

## 6. Native commands added for old-system parity
> 中文：6. 为对齐旧系统新增的原生命令

These commands work in every mode (`PartyBotOnly = 0` as well). Only the old spellings in the tables above need the switch.  
这些命令在所有模式下均可使用（`PartyBotOnly = 0` 时同样有效）。只有上表中的旧版命令拼写才依赖兼容开关。

### 6.1 Named assist and protect
> 中文：6.1 按名指定协助（assist）与保护（protect）

```
order assist <name>
order protect <name>
order clear
order
```

- **assist**: the bot attacks the target of the named group member while that member is in combat.  
  （**assist**：当指定的队友处于战斗状态时，机器人攻击该队友当前的目标。）
- **protect**: the bot attacks a non-crowd-controlled attacker whose victim is the named member (damage dealers pick the lowest-health attacker, tanks the one with the lowest own threat). Healers do not take the protect role.  
  （**protect**：机器人攻击正在攻击该指定队友的、未被控场的敌人——输出职业优先选择血量最低的攻击者，坦克优先选择自身仇恨最低的攻击者。治疗职业不承担 protect 职责。）
- Adds `dps assist` unless the bot already has a tank or dps assist strategy.  
  （除非机器人已具备坦克或输出协助策略，否则会自动添加 `dps assist`。）
- `order` on its own reports the current state, `order clear` removes it.  
  （单独输入 `order` 会报告当前状态，`order clear` 用于清除。）
- The setting is saved per bot and is part of `co save` / `co restore`.  
  （该设置按机器人独立保存，并纳入 `co save` / `co restore` 快照管理。）
- The named member must be in the bot's group.  
  （指定的成员必须与机器人在同一队伍中。）

### 6.2 Resistance orders
> 中文：6.2 抗性指令（`resist`）

```
resist fire | frost | nature | shadow
resist none        (also: clear, reset, off)
resist
```

Per class:  
各职业对应策略/技能：

| Class | fire | frost | nature | shadow |
|---|---|---|---|---|
| Paladin | `aura fire` | `aura frost` | none | `aura shadow` |
| Shaman | Fire Resistance Totem | Frost Resistance Totem | Nature Resistance Totem | none |
| Hunter | none | none | `aspect wild` | none |
| Other classes | gear only<br>仅换装 | gear only<br>仅换装 | gear only<br>仅换装 | gear only<br>仅换装 |

- The automatic aura / totem / aspect choice is saved before the order and **restored** when you clear or switch it.  
  （下达指令前会保存机器人原有的自动光环/图腾/守护选择，并在清除或切换抗性指令时**恢复**。）
- **Gear:** if the bot has a saved outfit named `<school>`, `<school>res`, `resist<school>` or `<school>resist` (for example `fire` or `fireres`, created with the `outfit` command), it equips it. The current gear is first saved as the outfit `noresist` and put back when the order is cleared. No gear swap happens in combat; the strategy part still applies and the reply says gear will not change.  
  （**装备切换：** 如果机器人存在名为 `<school>`、`<school>res`、`resist<school>` 或 `<school>resist` 的已保存套装——例如通过 `outfit` 命令创建的 `fire` 或 `fireres`——会自动换上该套装。换装前当前装备会先保存为 `noresist` 套装，并在清除抗性指令时换回。战斗中不会切换装备，但抗性策略部分仍会生效，且回复中会提示装备暂不变更。）
- While a resist outfit is worn, automatic gear upgrades are paused so the resist set is not replaced.  
  （穿戴抗性套装期间，自动换装升级会暂停，以免抗性装备被替换掉。）
- The order is saved per bot and is part of `co save` / `co restore`.  
  （该指令按机器人独立保存，并纳入 `co save` / `co restore` 快照管理。）

### 6.3 `collect`
> 中文：6.3 拾取与采集标志（`collect`）

```
collect
collect [none | all | combat | loot | quest | profession | objects | skin] [distance:N]
```

Flags are **additive**, as in the old bot. `collect` alone reports the current state.  
各标志为**累加生效**，与旧版机器人一致。单独输入 `collect` 将报告当前状态。

| Flag | Effect |
|---|---|
| `combat` | loot after combat (non-combat `loot` strategy)<br>战后拾取（非战斗 `loot` 策略）。 |
| `loot` | grab all loot from corpses<br>拾取尸体上的所有战利品。 |
| `quest` | only quest items<br>仅拾取任务物品。 |
| `profession` | profession-related loot<br>仅拾取专业技能相关战利品。 |
| `objects` | gather objects (non-combat `gather` strategy)<br>采集世界物体（非战斗 `gather` 策略）。 |
| `skin` | informational; skinning follows the bot's skill<br>仅作信息提示；剥皮行为取决于机器人自身是否掌握剥皮技能。 |
| `all` | everything above<br>启用以上全部标志。 |
| `none` | removes loot and gather behaviour<br>移除所有拾取与采集行为。 |
| `distance:N` | per-bot loot distance in yards, capped by `AiPlayerbot.LootDistanceMax`. Same as `range loot N`.<br>单机器人的拾取距离（单位：码），上限受 `AiPlayerbot.LootDistanceMax` 限制。等效于 `range loot N`。 |

### 6.4 `survey`, `find`, `get`
> 中文：6.4 勘察、定位与采集物体（`survey`、`find`、`get`）

```
survey
find [gameobject link]
get  [gameobject link]
```

- **survey** lists, in one line of clickable links and nearest first, the objects within `AiPlayerbot.SightDistance` that the bot could actually collect: ore and herbs it has the skill (and pick) for, chests, and quest objects it needs. Without any: `I see nothing to collect around here.`  
  （**survey**：按距离由近到远，以一行可点击链接的形式列出 `AiPlayerbot.SightDistance` 范围内机器人实际能够采集/开启的物体——包括拥有对应技能（及矿锄）的矿脉与草药、宝箱以及所需的任务物体。若附近没有可采集物体，则回复 `I see nothing to collect around here.`。）
- **find** walks to a spot about 2.5 yards from the chosen object and **stays** there until you give a movement order (`follow`, `stay`, ...).  
  （**find**：走到距离目标物体约 2.5 码处并**停留**在原地，直到你下达新的移动指令如 `follow`、`stay` 等。）
- **get** checks the bot can collect the object (the reply names the reason if not: no skill, skill too low, no mining pick, no key, someone else is using it, nothing to take), then:  
  （**get**：先检查机器人是否满足采集条件——若不满足，回复中会说明具体原因：无技能、技能等级不足、缺少矿锄、缺少钥匙、他人正在使用、无可拾取物品——随后执行以下步骤：）
  1. stops following (remembering whether it was following, staying, guarding or wandering),  
     （停止当前移动状态，并记住此前处于跟随、停留、守护还是游荡模式，）
  2. walks there, gathers or opens the object and loots it,  
     （走过去采集或打开该物体并拾取，）
  3. goes back to the remembered movement mode (follow your master by default).  
     （完成后恢复先前记住的移动模式，默认为跟随主人。）
  
  `get` ends when the object is no longer collectable, after it has been opened once (multi-use ore veins and herbs continue until empty), or after **90 seconds** out of combat (`I could not get [..], coming back.`). Fights on the way pause it. Giving `follow`, `stay`, `guard` or `wander` cancels it.  
  （当物体不再可采集、已开启一次（可多次采集的矿脉与草药会持续采集直到耗尽），或脱战超过 **90 秒**仍未完成时（回复 `I could not get [..], coming back.`），`get` 即结束。途中的战斗会暂停该动作。下达 `follow`、`stay`、`guard` 或 `wander` 可随时取消。）
- In party chat every bot in range answers `survey`.  
  （在队伍聊天中发送 `survey` 时，范围内的每个机器人都会作出回应。）

### 6.5 `mill` and `prospect`
> 中文：6.5 研磨（`mill`）与选矿（`prospect`）

```
mill [herb link]
prospect [ore link]
```

Without a link the bot picks its largest qualifying stack. Requirements: the bot knows the spell (Inscription / Jewelcrafting), the item is flagged millable / prospectable, the required skill is high enough, and a **single stack of at least 5**. Not usable in combat or while flying; the bot dismounts and leaves shapeshift forms first.  
未指定物品链接时，机器人会自动选择数量最多且符合条件的堆叠。前置条件：机器人已学会对应法术（铭文/珠宝加工）、物品标记为可研磨/可选矿、专业技能等级足够，且**单个堆叠至少有 5 个**。战斗中或飞行中不可用；执行前机器人会自动下马并解除变形形态。

Availability: prospecting exists from TBC, milling from WotLK. In older versions the bot replies that it is not possible in this version of the game.  
版本可用性：选矿自 TBC 起可用，研磨自 WotLK 起可用。在更早的游戏版本中，机器人会回复当前游戏版本不支持该操作。

### 6.6 `auction`
> 中文：6.6 拍卖行命令（`auction`）

```
auction                             (or: auction list)
auction add [item link] [price]
auction remove [item link]          (or: auction remove #<id> / <id>)
```

- **list** works anywhere: id, item and count, current bid (or minimum bid), buyout, time left and auction house, up to 15 lines.  
  （**list**：在任何地点均可使用，列出拍卖 ID、物品与数量、当前竞价（或起拍价）、一口价、剩余时间及所属拍卖行，最多显示 15 行。）
- **add** needs an auctioneer in range. The price is the buyout for the whole stack; a bare number means **gold** (`5` = 5g, `5g50s`, `50s`, `5g 50s`). The starting bid is 95% of the buyout. Without a price the bot uses the same automatic pricing as `ah vendor`. The bot checks it can pay the deposit first.  
  （**add**：需要附近有拍卖师。价格表示整组物品的一口价；纯数字默认单位为**金**（如 `5` = 5g，`5g50s`、`50s`、`5g 50s`）。起拍价为一口价的 95%。若未指定价格，则采用与 `ah vendor` 相同的自动定价逻辑。机器人会先检查是否有足够金币支付保管费。）
- **remove** needs an auctioneer in range and cancels the bot's own auctions through the normal client path (deposit and mail rules apply). An item link cancels every matching auction **that has no bid**; an id cancels exactly one. Auctions with a bid are refused.  
  （**remove**：需要附近有拍卖师，通过正常客户端路径取消机器人自己的拍卖（适用常规保管费与邮件退回规则）。传入物品链接会取消所有匹配且**尚无人竞价**的拍卖；传入 ID 则精确取消指定的一条。已有出价的拍卖会被拒绝取消。）
- Differences to the old bot: no queue that waits until the next auctioneer is met, no clickable auction link (use the `#id` from the list).  
  （与旧版机器人的差异：不会排队等到下次遇见拍卖师再挂拍，也没有可点击的拍卖链接，请使用列表中的 `#id`。）

### 6.7 Costs
> 中文：6.7 费用机制

`AiPlayerbot.BotAddCost` and `AiPlayerbot.BotSummonCost` (section 2).  
`AiPlayerbot.BotAddCost` 与 `AiPlayerbot.BotSummonCost`（详见第 2 节）。

- **Add:** the cost is checked when you type `.bot add` (money already reserved for other bots that are still logging in counts), and taken when the bot is online with the message `Paid <amount> to add <bot>.` If you cannot pay: `You need <amount> to add a bot.` and nothing happens. A bot that logs in while you can no longer pay is logged out again.  
  （**添加费用：** 输入 `.bot add` 时即检查余额（正在登录中的其他机器人已预留的金额也计入在内），并在机器人正式上线后扣款并提示 `Paid <amount> to add <bot>.`。若余额不足，则提示 `You need <amount> to add a bot.` 且不执行添加；若机器人上线瞬间玩家余额已不足，该机器人会被立即登出。）
- **Summon:** taken when the summon goes through; `You need <amount> to summon me.` otherwise.  
  （**召唤费用：** 在召唤成功执行时扣费；否则提示 `You need <amount> to summon me.`。）
- GM accounts are always free. Random bots, autologin, `.always` and console adds are free.  
  （GM 账号始终免费。随机机器人、自动登录、`.always` 以及控制台添加均免费。）
- With `PartyBotOnly = 1`, `.bot create` charges the add cost as well; if you cannot pay, the character is created but stays offline.  
  （在 `PartyBotOnly = 1` 时，`.bot create` 同样会收取添加费用；若无法支付，角色仍会被创建但保持离线状态。）

### 6.8 Pull checks and combat order snapshots
> 中文：6.8 开怪检查与战斗指令快照

- `pull capability` / `pull readiness` are the native names behind `pull test` / `pull ready`.  
  （`pull capability` / `pull readiness` 分别是 `pull test` / `pull ready` 背后的原生命令名。）
- `co save` stores the bot's combat role strategies and attack delay, `co restore` brings them back, `co ?` lists the combat strategies.  
  （`co save` 保存机器人的战斗职责策略与攻击延迟，`co restore` 恢复保存的配置，`co ?` 列出当前战斗策略。）

---

## 7. Known differences and limits
> 中文：7. 已知差异与限制

- **Bot guy NPC and bot shop:** not implemented. It needs creature gossip and menu flows the module does not have. Use `.bot add`, optionally with `BotAddCost`.  
  （**“Bot guy” NPC 与机器人商店：** 未实现。这需要本模块目前没有的生物对话（gossip）与菜单交互流程。请直接使用 `.bot add`，如需收费可配合 `BotAddCost`。）
- **`nodispell`** is approximated (see 5.3).  
  （**`nodispell`**：仅为近似行为，参见 5.3 节。）
- **`follow auto/reset/info`:** no automatic variable follow distance.  
  （**`follow auto/reset/info`：** 不支持自动动态调整跟随距离。）
- **`equip auto on/off/once`:** not provided; the module's usage calculator decides on gear.  
  （**`equip auto on/off/once`：** 未提供；由模块的装备价值计算器自行决定穿戴。）
- **Pet taming:** not available (factory-managed pets only).  
  （**驯服宠物：** 不支持，仅支持工厂自动管理的宠物。）
- **Auction queue / auction links:** see 6.6.  
  （**拍卖队列 / 拍卖链接：** 见 6.6 节。）
- **Runtime flip of `PartyBotOnly`:** does not retire bots that are already online or change their agenda; restart the server.  
  （**运行时热切换 `PartyBotOnly`：** 不会下线已在线的机器人或改变其既有日程；修改后请重启服务器。）
- **Old wording needs the mode:** `orders combat ...`, `resumeorders`, `follow near/far`, `pull test/ready`, `neutralize`, `process ...` and `sell all` are only understood while `PartyBotOnly = 1`. Their native counterparts always work.  
  （**旧版写法依赖兼容模式：** `orders combat ...`、`resumeorders`、`follow near/far`、`pull test/ready`、`neutralize`、`process ...` 和 `sell all` 仅在 `PartyBotOnly = 1` 时可被识别；对应的原生命令在任何模式下始终有效。）
- **One command per bot and tick:** chat commands are single slots; two commands in the same instant for the same bot can overwrite each other. The old-order translations are single commands for exactly this reason.  
  （**每个机器人每 Tick 仅处理一条命令：** 聊天命令槽位为单槽设计，同一瞬间向同一机器人发送两条命令可能会互相覆盖。旧版指令映射成单条命令正是出于此原因。）
- **Verified in game:** the commands were verified on live bots through the console; paths that need a real client master (agenda of an own-account alt after `.bot add`, `sell all` next to a vendor, real `get` return to the master, outfit swaps, costs, auction add/remove at an auctioneer, `neutralize` with the spell known) are covered by code review and should be checked on your server.  
  （**游戏内验证情况：** 各命令已通过控制台在运行中的机器人上验证；依赖真实客户端主人的分支路径（如 `.bot add` 登录同账号小号后的日程、商人旁执行 `sell all`、`get` 完成后返回主人、套装切换、扣费、拍卖师旁上架/取消拍卖、已学会法术时的 `neutralize`）已通过代码审查覆盖，建议在你的服务器上进一步实测。）

---

## 8. Expansions
> 中文：8. 资料片差异

All commands are expansion independent except:  
除以下项目外，所有命令均与资料片版本无关：

| Feature | Vanilla | TBC | WotLK |
|---|---|---|---|
| `prospect` | not available<br>不可用 | yes<br>可用 | yes<br>可用 |
| `mill` | not available<br>不可用 | not available<br>不可用 | yes<br>可用 |
| `auction` times | 8 h posts<br>8 小时上架 | 12 h posts<br>12 小时上架 | 12 h posts; sold auctions stay listed while payment is pending (shown as pending, not cancellable)<br>12 小时上架；已售出但货款待结算的拍卖仍会保留在列表中（显示为 pending，不可取消） |

Resist orders use the resistance strategies the class has in that expansion; combinations without a spell reply `no <school> resist spell for my class` and use gear only.  
抗性指令使用该职业在对应资料片所拥有的抗性策略；若职业本身没有对应抗性法术，则会回复 `no <school> resist spell for my class` 并仅切换抗性装备。

---

## 9. Testing and debugging
> 中文：9. 测试与调试

### 9.1 Quick checks (player side)
> 中文：9.1 快速自检（玩家侧）

1. `.rndbot stats` shows `0 online` after the startup ramp.  
   （启动流程结束后，`.rndbot stats` 显示 `0 online`。）
2. `.bot add` of a character from another account answers `Not in your account`.  
   （使用 `.bot add` 添加其他账号的角色时，返回 `Not in your account`。）
3. `.bot add` of your own alt; `/t Name nc ?` shows no `grind`, `travel`, `rpg ...`.  
   （使用 `.bot add` 添加自己的小号后，`/t Name nc ?` 中不应包含 `grind`、`travel`、`rpg ...`。）
4. `orders combat tank`, then `co ?` (tank strategy present), `resumeorders` (original setup back).  
   （执行 `orders combat tank`，再用 `co ?` 确认存在 tank 策略，最后执行 `resumeorders` 确认恢复原有配置。）
5. `survey`, then `get [link]` on a nearby ore, herb or chest.  
   （执行 `survey`，再对附近的矿脉、草药或宝箱执行 `get [link]`。）
6. `pull test`, `orders delay 3`, `resist fire`, `resist none`, `auction`.  
   （依次测试 `pull test`、`orders delay 3`、`resist fire`、`resist none`、`auction`。）

### 9.2 Console tools (RA / GM)
> 中文：9.2 控制台调试工具（RA / GM）

| Command | Use |
|---|---|
| `.rndbot cmd <bot> <command>` | Run a chat command on a bot as if parsed from chat (skips the old-wording translation).<br>直接在机器人上执行一条已解析的聊天命令（跳过旧版命令拼写转换）。 |
| `.rndbot cmd <bot> chat <text>` | Run `<text>` through the **real chat handler** of the bot, including the old-wording translation and permission checks. Pair with the two commands below to read the reply.<br>将 `<text>` 送入机器人的**真实聊天处理器**，包含旧版命令改写与权限检查。配合下方两条命令可读取机器人回复。 |
| `.rndbot record <bot> enable` | Capture the bot's next reply. Re-enable before each command.<br>捕获机器人的下一条回复。每次发送命令前需重新启用。 |
| `.rndbot read <bot>` | Print the captured reply (wait about two seconds after the command).<br>打印已捕获的回复（发送命令后大约等待两秒再读取）。 |
| `.rndbot reload` | Re-read the configuration (does not retire online bots).<br>重新读取配置文件（不会下线已在线机器人）。 |
| `.rndbot debug <bot> why` / `history` | Why the bot does what it does; recent actions (enable with `.rndbot history on`).<br>查看机器人当前行为原因（`why`）与近期动作记录（`history`，需先通过 `.rndbot history on` 开启）。 |

To test the old wording without a client: start with `PartyBotOnly = 0` and a few random bots, set the switch to `1` in the file, run `.rndbot reload`, then use `.rndbot cmd <bot> chat orders combat tank`.  
无需客户端即可测试旧版命令写法的方法：先以 `PartyBotOnly = 0` 启动并生成几个随机机器人，随后在配置文件中将该开关改为 `1`，执行 `.rndbot reload`，再运行 `.rndbot cmd <bot> chat orders combat tank`。

### 9.3 Reading failures
> 中文：9.3 常见异常排查

- No reply to an old spelling: check the switch (`AiPlayerbot.PartyBotOnly = 1`) and that you are the bot's master or allowed to command it.  
  （发送旧版命令无响应：检查是否已设置 `AiPlayerbot.PartyBotOnly = 1`，以及你是否为该机器人的主人或拥有控制权限。）
- `get` seems stuck: it pauses during fights and gives up after 90 seconds out of combat.  
  （`get` 看似卡住：战斗期间会自动暂停，脱战累计超过 90 秒后会自动放弃并返回。）
- `sell all` says `I need a vendor nearby.`: stand next to the vendor (interaction range) and target nothing special.  
  （`sell all` 提示 `I need a vendor nearby.`：请确保站在商人交互范围内，且未选中其他特殊目标。）
