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
#include "Enemy/EnemyWheel.h"

namespace Gyro {
  namespace Object {

    SpawnServer::SpawnServer(Application::ApplicationMain& app) : AppFrame::Server::ServerTemplateUnordered<std::string, SpawnMap>(), _appMain(app) {
#ifdef _DEBUG
      // サーバ名設定
      SetServerName("SpawnServer");
#endif
      _stage.clear();
    }

    bool SpawnServer::Release() {
      // スポーン情報を解放する
      for (auto&& [key, stage] : _registry) {
        stage.clear();
      }
      _registry.clear(); // 情報削除
      return true;
    }

    bool SpawnServer::AddSpawnTable(std::string_view key, const SpawnMap& spawnMap) {
      // データが登録されているか
      if (spawnMap.empty()) [[unlikely]] {
#ifdef _DEBUG
        throw LogicError("スポーン情報が空です");
#endif
        return false; // 問題発生
      }
      // キーが重複しているか
      if (!UseKey(key.data())) {
        // 重複している場合は既存データを削除する
        DeleteSpawnMap(key);
      }
      // データベース上にステージ情報を登録する
      _registry.emplace(key.data(), std::move(spawnMap));
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
      return Spawn(NowSpawnMap().at(number));
    }

    bool SpawnServer::SetStage(std::string_view key) {
      // キーは登録されているか
      if (!_registry.contains(key.data())) {
        return false; // キーが未登録のため切り替えない
      }
      // 現在のキーと重複しているかの判定
      if (key.data() == _stage) {
#ifdef _DEBUG
        throw LogicError("キーが重複しています");
#endif
        return false; // キーが同一
      }
      // キーの切り替え
      _stage = key.data();
      return true; // 設定完了
    }

    void SpawnServer::EmplaceBack(SpawnTable& table, EnemyTable& enemy) {
      // エネミーのスポーン情報を登録する
      for (auto&& spawn : enemy) {
        // スポーン情報を末尾にmoveする
        table.emplace_back(std::move(spawn));
      }
    }

    SpawnMap& SpawnServer::NowSpawnMap() {
      return _registry.at(_stage);
    }

    void SpawnServer::DeleteSpawnMap(std::string_view key) {
      // ステージのスポーン情報取り出し
      auto stageMap = _registry[key.data()];
      // ステージ情報を削除
      stageMap.clear();
      // データベース上から削除する
      _registry.erase(key.data());
    }

    bool SpawnServer::Spawn(SpawnTable& table) const {
      // スポーン情報を基にオブジェクトの生成を行う
      for (auto num = 0; auto&& spawn : table) {
        // オブジェクトタイプを基に生成を行う
        switch (spawn.GetType()) {
          // 自機
        case SpawnBase::ObjectType::Player:
          // 自機の場合は登録を行う
          AddObject(Player(spawn));
          break;
          // 敵
        case SpawnBase::ObjectType::Enemy:
          // 敵の登録を行う
          AddObject(Enemy(spawn));
          break;
          // オブジェクトタイプの該当がない場合
        case SpawnBase::ObjectType::None:
#ifdef _DEBUG
          try {
            SpawnError(num);
          } catch (std::logic_error error) {
            DebugString(error.what()); // 例外文を出力する
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

    std::shared_ptr<Player::Player> SpawnServer::Player(const SpawnBase& spawn) const {
      // 自機は既に登録されていないか
      if (_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // 登録されている場合はnullptrを返す
      }
      // 自機の生成
      auto player = std::make_shared<Player::Player>(_appMain);
      player->Set(spawn);       // スポーン情報の設定
      return std::move(player); // 生成したシェアードポインタを返す
    }

    std::shared_ptr<ObjectBase> SpawnServer::Enemy(SpawnBase spawn) const {
      // エネミータイプの取得
      auto type = dynamic_cast<SpawnEnemy*>(&spawn)->GetEnemyType();
      // エネミータイプに応じたシェアードポインタを返す
      switch (type) {
      case SpawnEnemy::EnemyType::Wheel: // 陸上型
        return EnemyWheel(spawn);
      case SpawnEnemy::EnemyType::None:  // 該当なし
        return nullptr;  // 該当がない場合はnullptrを返す
      }
    }

    std::shared_ptr<Enemy::EnemyWheel> SpawnServer::EnemyWheel(SpawnBase spawn) const {
      // 陸上型エネミーの生成
      auto wheel = std::make_shared<Enemy::EnemyWheel>(_appMain);
      wheel->Set(spawn);       // スポーン情報の設定
      return std::move(wheel); // 生成したシェアードポインタを返す
    }

#ifdef _DEBUG
    std::logic_error SpawnServer::SpawnError(const int number) const {
      std::string message = _stage + ":" + std::to_string(number) + ":の情報が有効ではありません";
      return LogicError(message);
    }
#endif
  } // namespace Object
} // namespace Gyro
