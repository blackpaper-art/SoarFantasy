123
# SoarFantasy

## 📖 Description | 説明

SoarFantasy is a lightweight endless runner game demo built with Unreal Engine.
In this game, the player needs to avoid obstacles and missiles, collect as many coins as possible — and most importantly, don’t die!
The player can jump, crouch, collect coins, activate a magnet buff, and avoid missiles and death zones.
The project showcases core features such as level generation, Data Layer switching, HUD overlays, and score saving.

SoarFantasy は、Unreal Engine で構築された軽量エンドレスランナーゲームのデモです。
プレイヤーは障害物やミサイルを避けながら、できるだけ多くのコインを集めてください。そして、絶対に死んではいけません！
また、ジャンプ、しゃがみ、コインの収集、マグネット バフの有効化、ミサイルやデスゾーンの回避を行うことができます。
このプロジェクトでは、レベル生成、データ レイヤーの切り替え、HUD オーバーレイ、スコア保存などのコア機能を紹介しています。

Demo video URL:
https://youtu.be/VNuQdBr7ri4

## 📌 Modules | モジュール

- ACharactersKix: Main character class with jump, double jump, score and magnet functions
- AKixPlayerController: Player controller handling input bindings and pause logic
- ASFHUD: HUD manager to toggle Start / Pause / End UI
- USFOverlay, UPauseOverlay, UEndOverlay, UStartOverlay: Various UI layers
- AMapSpawnerBASE, ALevelGenerator: Level generators based on external files
- AGroundBASE: Platform Actor with coins and enemy components
- ACoinBASE: Coin Actor implementing SoarFantasyInterface
- AMissileSpawnerBASE, AMissileBASE: Enemy missile spawner and missile behavior
- ABuffBASE: Buff spawner (magnet)
- ADeathzoneBASE: Death zone Actor
- ISoarFantasyInterface: Common interface for characters and objects
- USysSaveGame: Save and load best score
##
- ACharactersKix: メインキャラクタークラス（ジャンプ、ダブルジャンプ、スコア、マグネット）
- AKixPlayerController: プレイヤーコントローラー（入力バインド、ポーズ制御）
- ASFHUD: HUD マネージャー（Start / Pause / End UI 切替）
- USFOverlay, UPauseOverlay, UEndOverlay, UStartOverlay: 各種 UI レイヤー
- AMapSpawnerBASE, ALevelGenerator: 外部ファイルに基づくレベルジェネレーター
- AGroundBASE: プラットフォーム Actor（コイン、敵コンポーネントを含む）
- ACoinBASE: コイン Actor（SoarFantasyInterface 実装）
- AMissileSpawnerBASE, AMissileBASE: 敵ミサイルスポナーと挙動
- ABuffBASE: バフスポナー（マグネット）
- ADeathzoneBASE: デスゾーン Actor
- ISoarFantasyInterface: キャラクターとオブジェクト用の共通インターフェース
- USysSaveGame: ベストスコア保存とロード


## ✅ Features | 機能
- CSV file & DataTable-based level generation
- Double jump, distance score, magnet collection
- Start / Pause / End overlays
- SaveGame for best score
- DataLayer switching
##
- CSVファイル＆DataTableベースのレベル生成
- ダブルジャンプ、距離スコア、マグネットコレクション
- 開始/一時停止/終了オーバーレイ
- ベストスコアのためのセーブゲーム
- データレイヤー切り替え

## ⚙️ Engine | エンジン
- Unreal Engine 5.4.4
