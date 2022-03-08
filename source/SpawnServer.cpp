/*****************************************************************//**
 * @file   SpawnServer.cpp
 * @brief  オブジェクトのスポーン情報を管理するサーバクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "SpawnServer.h"
#include "ApplicationMain.h"
#include "ObjectBase.h"
#include "ObjectServer.h"
#include "Player.h"
#include "EnemyWheel.h"
#include "EnemyDrone.h"
#include "SkySphere.h"
#include "StageComponent.h"

namespace Gyro {
  namespace Object {

    SpawnServer::SpawnServer(Application::ApplicationMain& app) : AppFrame::Server::ServerTemplateUnordered<std::string, SpawnMap>(), _appMain(app) {
#ifdef _DEBUG
      // サーバ名設定
      SetServerName("SpawnServer");
#endif
      _stage.clear(); // ステージ名を削除
    }

    bool SpawnServer::Release() {
      // 各ステージのスポーン情報を削除する
      for (auto&& [key, stage] : _registry) {
        stage.clear(); // ステージのスポーン情報を解放する
      }
      _registry.clear(); // データベース削除
      return true;
    }

    bool SpawnServer::AddSpawnTable(std::string_view key, SpawnData spawnMap) {
      // データが登録されているか
      if (spawnMap.empty()) [[unlikely]] {
#ifdef _DEBUG
        throw LogicError("スポーン情報が空です");
#endif
        return false; // 問題発生
      }
      // キーが重複しているか
      if (Contains(key.data())) {
        // 重複している場合は既存データを削除する
        Delete(key);
      }
      // スポーン情報用の連想配列
      SpawnMap map;
      // スポーン情報を管理する動的配列
      std::vector<std::shared_ptr<SpawnBase>> table;
      // スポーン情報をシェアードポインタに変換して登録を行う
      for (auto&& [number, spawn] : spawnMap) {
        // 生成テーブルの取得
        auto [normal, enemy] = spawn;
        // 通常のスポーン情報を変換
        for (auto&& value : normal) {
          table.emplace_back(std::make_shared<SpawnBase>(value));
        }
        // 敵のスポーン情報を変換
        for (auto&& value : enemy) {
          table.emplace_back(std::make_shared<SpawnEnemy>(value));
        }
        // 変換したテーブルをコンテナに登録
        map.emplace(number, table);
      }
      // データベースに情報を登録する
      _registry.emplace(key.data(), map);
      return true; // 登録成功
    }

    bool SpawnServer::Spawn(const int number) {
      // キーが不正な場合は生成を行わない
      if (!_registry.contains(_stage)) [[unlikely]] {
        return false; // キーが不正です
      }
      // レジストリーに登録されているか
      if (!NowSpawnMap().contains(number)) {
        return false; // 生成番号が不正
      }
      // オブジェクトを生成する
      return SpawnObject(number);
    }

    bool SpawnServer::SetStage(std::string_view key) {
      // キーは登録されているか
      if (!_registry.contains(key.data())) {
        return false; // キーが未登録のため切り替えない
      }
      // 現在のキーと重複しているかの判定
      if (key.data() == _stage) {
        return false; // キーが重複している
      }
      // キーの切り替え
      _stage = key.data();
      return true; // 設定完了
    }

    SpawnMap& SpawnServer::NowSpawnMap() {
      // ステージに対応したスポーン情報が格納されたステージ情報を返す
      return _registry.at(_stage);
    }

    void SpawnServer::Delete(std::string_view key) {
      // ステージのスポーン情報取り出し
      auto stageMap = _registry[key.data()];
      // ステージ情報を削除
      stageMap.clear();
      // データベース上から削除する
      _registry.erase(key.data());
    }

    bool SpawnServer::SpawnObject(const int number) {
      // スポーン情報を基にオブジェクトの生成を行う
      for (auto num = 0; auto spawn : NowSpawnMap().at(number)) {
        // オブジェクトタイプを基に生成を行う
        switch (spawn->GetType()) {
          // 自機
        case SpawnBase::ObjectType::Player:
          // 自機の生成・登録
          AddObject(Player(spawn));
          break;
          // 敵
        case SpawnBase::ObjectType::Enemy:
          // 敵の生成・登録を行う
          AddObject(Enemy(spawn));
          break;
          // スカイスフィア
        case SpawnBase::ObjectType::SkySphere:
          // スカイスフィアの生成・登録を行う
          AddSkySphere(Skysphere(spawn));
          break;
          // オブジェクトタイプの該当がない場合
        case SpawnBase::ObjectType::None:
#ifdef _DEBUG
          try {
            // スポーン失敗用のメッセージを出力
            SpawnError(num);
          } catch (std::logic_error error) {
            DebugString(error.what());
          }
#endif
          break; // 生成失敗
        }
        ++num; // 処理回数をカウント
      }
      return true;
    }

    bool SpawnServer::AddObject(std::shared_ptr<ObjectBase> object) const {
#ifndef _DEBUG
      // オブジェクトサーバへの登録を行う
      return _appMain.GetObjectServer().Register(std::move(object));
#else
      auto flag = false; // 処理フラグ
      try {
        flag = _appMain.GetObjectServer().Register(std::move(object));
        // 例外を取得した場合はログに出力する
      } catch (std::logic_error error) {
        DebugString(error.what());
      }
      return flag;
#endif
    }

    void SpawnServer::AddSkySphere(std::shared_ptr<SkySphere> skysphere) {
      // ステージに登録する
      auto skySkysphere = skysphere;
      return _appMain.GetStageComponent().AddSky(skySkysphere);
    }

    std::shared_ptr<Player::Player> SpawnServer::Player(std::shared_ptr<SpawnBase>& spawn) const {
      // 自機は既に登録されていないか
      if (_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // 登録されている場合はnullptrを返す
      }
      // 自機の生成
      auto player = std::make_shared<Player::Player>(_appMain);
      player->Set(*spawn.get());       // スポーン情報の設定
      return std::move(player); // 生成したシェアードポインタを返す
    }

    std::shared_ptr<ObjectBase> SpawnServer::Enemy(std::shared_ptr<SpawnBase>& spawn) const {
      // エネミータイプの取得
      auto enemy = std::dynamic_pointer_cast<SpawnEnemy>(spawn);
      // エネミータイプに応じたシェアードポインタを生成して返す
      switch (enemy->GetEnemyType()) {
      case SpawnEnemy::EnemyType::Wheel: // 陸上型
        return EnemyWheel(*enemy.get());
      case SpawnEnemy::EnemyType::Drone: // 空中型
        return EnemyDrone(*enemy.get());
      case SpawnEnemy::EnemyType::None:  // 該当なし
        return nullptr;  // 該当がない場合はnullptrを返す
      default:
        return nullptr;  // 設定されていない場合もnullptrを返す
      }
    }

    std::shared_ptr<Enemy::EnemyWheel> SpawnServer::EnemyWheel(SpawnEnemy& enemy) const {
      // 陸上型エネミーの生成
      auto wheel = std::make_shared<Enemy::EnemyWheel>(_appMain);
      wheel->Set(enemy);       // スポーン情報の設定
      return std::move(wheel); // 生成したシェアードポインタを返す
    }

    std::shared_ptr<Enemy::EnemyDrone> SpawnServer::EnemyDrone(SpawnEnemy& enemy) const {
      // 空中型エネミーの生成
      auto drone = std::make_shared<Enemy::EnemyDrone>(_appMain);
      drone->Set(enemy);       // スポーン情報の設定
      return std::move(drone); // 生成したシェアードポインタを返す
    }

    std::shared_ptr<SkySphere> SpawnServer::Skysphere(std::shared_ptr<SpawnBase>& spawn) const {
      // 自機は登録されているか
      if (!_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // 未登録
      }
      // スカイスフィアの生成
      auto skySphere = std::make_shared<SkySphere>(_appMain, *_appMain.GetObjectServer().GetPlayer());
      skySphere->SetKey("sky");
      skySphere->Set(*spawn);
      return std::move(skySphere);
    }

#ifdef _DEBUG
    std::logic_error SpawnServer::SpawnError(const int number) const {
      std::string message = _stage + ":" + std::to_string(number) + ":の情報が有効ではありません";
      return LogicError(message);
    }
#endif
  } // namespace Object
} // namespace Gyro
