/*****************************************************************//**
 * @file   ObjectServer.cpp
 * @brief  オブジェクトを管理するサーバクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"
#include "Player.h"

namespace Gyro {
  namespace Object {

    ObjectServer::ObjectServer() : ServerTemplateVector<std::shared_ptr<ObjectBase>>() {
#ifdef _DEBUG
      SetServerName("ObjectServer");
#endif
      // 各種コンテナを解放する
      ServerTemplateVector<std::shared_ptr<ObjectBase>>::_registry.clear();
      _addObject.clear();
    }

    ObjectServer::~ObjectServer() {
      Release(); // オブジェクトを解放する
    }

    bool ObjectServer::Release() {
      // コンテナの中身を解放する
      for (auto object : _registry) {
        // データの破棄処理を呼び出す
      }
      _registry.clear();     // コンテナの中身を解放する
      _addObject.clear();    // 登録予約されているオブジェクトを削除
      return true;
    }

    bool ObjectServer::Process() {
      // 追加予約されているオブジェクトがある場合は登録処理を行う
      if (!_addObject.empty()) {
        AddObjects(_addObject); // レジストリ―に登録
      }
      _play = true;  // 処理開始
      for (auto object : _registry) {
        object->Process(); // 更新処理呼び出し
      }
      _play = false; // 処理終了
      // 不要になったオブジェクトを削除する
      std::erase_if(_registry, [](auto&& obj) {return obj->IsDead(); });
      return true;
    }

    bool ObjectServer::Draw() {
      for (auto&& obj : _registry) {
        obj->Draw(); // 描画処理呼び出し
      }
      return true;
    }

    bool ObjectServer::Register(std::shared_ptr<ObjectBase> object) {
      return AddObject(std::move(object)); // 登録処理に移行
    }

    bool ObjectServer::AddObject(std::shared_ptr<ObjectBase> object) {
      // オブジェクトはnullではないか
      if (object == nullptr) {
#ifdef _DEBUG
        throw LogicError("オブジェクトはnullptrです");
#endif
        return false; // 中身がnullptr
      }
      // コンテナを回しているかの有無で登録先を切り替え
      if (_play) {
#ifndef _DEBUG
        return AddReserve(std::move(object)); // 追加予約
#else
        auto flag = false; // 処理フラグ
        try {
          flag = AddReserve(std::move(object));
          // 例外をキャッチした場合は出力を行う
        } catch (std::logic_error error) {
          DebugString(error.what());
        }
        return flag; // フラグを返す
#endif
      }
      // コンテナを回していない場合は直接登録する
      _registry.emplace_back(std::move(object));
      return true; // 登録完了
    }

    void ObjectServer::DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& container) {
      // 登録オブジェクトを解放する
      for (auto&& obj : container) {
        // 解放処理を行う
      }
      container.clear(); // コンテナの解放
    }

    void ObjectServer::AddObjects(std::vector<std::shared_ptr<ObjectBase>>& container) {
      // オブジェクトを末尾に追加
      for (auto&& obj : container) {
        _registry.emplace_back(std::move(obj));
      }
      container.clear(); // コンテナの解放
    }

    bool ObjectServer::AddReserve(std::shared_ptr<ObjectBase> object) {
      // 所有権が一つではない場合
      if (object.use_count() != 1) {
#ifdef _DEBUG
        throw LogicError("他にもオブジェクトの所有権が存在しています");
#endif
        return false; // 予約失敗
      }
      // 登録予約
      _addObject.emplace_back(std::move(object));
      return true; // 予約成功
    }

    std::vector<std::shared_ptr<ObjectBase>> ObjectServer::GetObjects() {
      return _registry; // データベースを叩きつける
    }

    bool ObjectServer::GetPlayerTransForm(AppMath::Vector4& position, AppMath::Vector4& rotation) {
      auto player = GetPlayer(); // 自機の取得
      // 中身がnullptrの場合は処理を行わない
      if (player == nullptr) {
        return false; // 取得失敗
      }
      position = player->GetPosition(); // ローカル座標
      rotation = player->GetRotation(); // 回転量
      return true; // 取得成功
    }

    std::shared_ptr<Player::Player> ObjectServer::GetPlayer() {
      std::shared_ptr<Player::Player> player = nullptr;
      for (auto obj : _registry) {
        // 自機の場合はポインタを取得
        if (obj->GetId() == ObjectBase::ObjectId::Player) {
          player = std::dynamic_pointer_cast<Player::Player>(obj); // 自機をコピー
          break;
        }
      }
#ifdef _DEBUG
      try {
        LogicError("自機の取得に失敗しました");
      }
      catch (std::logic_error error) {
        DebugString(error.what()); // 出力する
      }
#endif
      return player; // 自機の参照を返す
    }
  } // namespace Object
} // namespace Gyro