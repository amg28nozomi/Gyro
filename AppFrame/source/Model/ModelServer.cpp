/*****************************************************************//**
 * @file   ModelServer.cpp
 * @brief  文字列をキーとしてモデル情報とアニメーションを管理するサーバクラスの定義
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModelServer.h"
#include <utility>
#include <DxLib.h>
#include "../Math/Arithmetic.h"

namespace AppFrame {
  namespace Model {

    ModelServer::ModelServer() : Server::ServerTemplateUnordered<std::string, ModelData>() {
#ifdef _DEBUG
      SetServerName("ModelServer");
#endif
      Server::ServerTemplateUnordered<std::string, ModelData>::Release();
    }

    bool ModelServer::Init() {
      return Server::ServerTemplateUnordered<std::string, ModelData>::Init();
    }

    bool ModelServer::Release() {
      // 各種コンテナの解放処理を行う
      for (auto&& [key, value] : _registry) {
        DeleteModels(value.GetHandles()); // モデルハンドルを削除する
        value.AnimeClear(); // アニメーション情報の削除
      }
      _registry.clear(); // コンテナを解放する
      return true;
    }

    bool ModelServer::AddMV1Model(std::string_view key, std::string_view path) {
      // キーが重複してるかの判定
      if (!UseKey(key.data())) {
        // キーが重複している場合は既存データを削除
        auto&& model = _registry.at(key.data());
        DeleteModels(model.GetHandles()); // モデルハンドルを削除
        model.AnimeClear(); // アニメーションを削除する
        _registry.erase(key.data()); // 要素を削除する
      }
      // モデルハンドルの読み取り
      auto handle = MV1LoadModel(path.data());
      // モデルハンドルの取得に成功したか
      if (handle == -1) {
#ifdef _DEBUG
        // モデルハンドルの読み取りに失敗した場合はログに出力する
        auto message = static_cast<std::string>(path) + ":mv1ファイルの読み取りに失敗しました\n";
        DebugString(message);
#endif
        return false; // 取得失敗
      }
      // モデルハンドルを格納するコンテナ
      std::unordered_map<unsigned short, int> handles{ {Original, handle} };
      auto animNum = MV1GetAnimNum(handle); // アニメーション番号の取得
      // アニメーション情報を格納する連想配列
      std::unordered_map<std::string, int> animes;
      // アニメーション情報を登録する
      for (auto num = 0; num < animNum; ++num) {
        // アニメーション名の取得
        auto animName = MV1GetAnimName(handle, num);
        // 取得したデータを基に要素を構築
        animes.emplace(animName, num);
      }
      // 読み取ったデータを登録する
      _registry.emplace(key.data(), ModelData(path, handles, animes));
      return true; // 登録成功
    }

    void ModelServer::AddMV1Model(const ModelDatas& mv1Files) {
      // コンテナから情報を取り出し登録を行う
      for (auto [key, path] : mv1Files) {
        AddMV1Model(key, path); // 登録を行う
      }
    }

    void ModelServer::DeleteModels() {
      Release(); // 全てのモデルハンドルを削除
    }

    bool ModelServer::DeleteDuplicateModels(std::string_view key, bool flag) {
      // フラグが立っている場合は全要素に処理を行う
      if (flag) {
        for (auto [key, value] : _registry) {
          // 複製されたモデルハンドルのみを削除
          DeleteDuplicateModels(value.GetHandles());
        }
        return true; // 削除完了
      }
      // 要素はあるか
      if (!_registry.contains(key.data())) {
        return false; // 未登録
      }
      // 複製されたモデルハンドルのみを削除する
      DeleteDuplicateModels(_registry.at(key.data()).GetHandles());
      return true; // 削除完了
    }

    std::pair<int, unsigned short> ModelServer::GetModel(std::string_view key, unsigned short number) {
      // キーが登録されているかの判定
      if (!_registry.contains(key.data())) {
        return std::make_pair(-1, MaxNumber); // キーが未登録
      }
      // モデルハンドルを返す
      return _registry.at(key.data()).Handle(number);
    }

    int ModelServer::GetAnimIndex(std::string_view key, std::string_view animName) {
      // キーは有効か
      if (!_registry.contains(key.data())) {
        return -1; // 未登録
      }
      // アニメーション番号を返す
      return AnimNumber(key, animName);
    }

    void ModelServer::DeleteModels(std::unordered_map<unsigned short, int>& handles) {
      for (auto [number, handle] : handles) {
        MV1DeleteModel(handle); // モデルハンドルを削除
      }
      handles.clear(); // コンテナを解放する
    }

    void ModelServer::DeleteDuplicateModels(std::unordered_map<unsigned short, int>& handles) {
      // ハンドルは登録されているか
      if (!handles.size()) {
        return; // 未登録
      }
      // オリジナルのモデルハンドルをコピー
      auto original = handles.at(0);
      handles.erase(0); // オリジナルハンドルをコンテナから削除
      // 複製したモデルハンドルを削除
      for (auto [key, handle] : handles) {
        MV1DeleteModel(handle);
      }
      // オリジナルハンドルを再登録
      handles.emplace(0, original);
    }

    int ModelServer::AnimNumber(std::string_view key, std::string_view animeName) const {
      auto model = _registry.at(key.data());
      // 指定したアニメーション番号を返す
      return model.AnimIndex(animeName);
    }
  } // namespace Model
} // namespace AppFrame