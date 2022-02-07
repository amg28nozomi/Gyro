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
      _registry.emplace(key.data(), spawnMap);
      return true; // 登録成功
    }

    bool SpawnServer::Spawn(const int number) const {
      // キーが不正な場合は生成を行わない
      if (!UseKey(_stage)) [[unlikely]] {
        return false; // キーが不正です
      }
      // レジストリーに登録されているか
      if (NowSpawnMap().contains(number)) {
        return false; // 生成番号が不正
      }
      // オブジェクトを生成する
      Spawn(NowSpawnMap().at(number));
    }

    bool SpawnServer::SetStage(std::string_view key) {
      // キーが登録されているか
      if (UseKey(key.data())) {
#ifdef _DEBUG
        std::string error = key.data();
        throw LogicError(error + ":キーが登録されていません");
#endif
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

    const SpawnMap SpawnServer::NowSpawnMap() const {
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

    bool SpawnServer::Spawn(const SpawnTable& table) const {
      // スポーン情報を基にオブジェクトの生成を行う
      for (auto num = 0; const auto spawn : table) {
        // オブジェクトタイプを基に生成を行う
        switch (spawn.GetType()) {
          // 自機
        case SpawnData::ObjectType::Player:
          // 自機の場合は登録を行う
          AddObject(Player(spawn));
          break;
          // オブジェクトタイプの該当がない場合
        case SpawnData::ObjectType::None:
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

    std::shared_ptr<Player::Player> SpawnServer::Player(const SpawnData& spawn) const {
      // 自機は既に登録されていないか
      if (_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // 登録されている場合はnullptrを返す
      }
      // 自機の生成
      auto player = std::make_shared<Player::Player>(_appMain);
      // 生成情報の取り出し
      auto [position, rotation, scale] = spawn.GetTransform();
      // 生成座標の設定
      player->Set(position, rotation, scale);
      // 生成した自機を返す
      return std::move(player);
    }

#ifdef _DEBUG
    std::logic_error SpawnServer::SpawnError(const int number) const {
      std::string message = _stage + ":" + std::to_string(number) + ":の情報が有効ではありません";
      return LogicError(message);
    }
#endif
  } // namespace Object
} // namespace Gyro
