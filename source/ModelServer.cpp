#include "ModelServer.h"
#include <DxLib.h>
#include "ApplicationMain.h"


namespace Gyro {
  namespace Model {

    ModelServer::ModelServer(Application::ApplicationMain& app) :
      AppServer::ServerTemplateUnordered<std::string, std::vector<int>>(),
      _app(app)
    {
      _animations.clear();
    }

    bool ModelServer::Release() {
      // 読み込まれている全てのモデルデータとアニメーションを削除する
      for (auto&& [key, handles] : _registry) {
        // モデルハンドルの削除
        DeleteHandles(handles);
      }
      _directry.clear();   // ディレクトリパスを削除
      _animations.clear(); // アニメーションの削除
      return true;
    }

    bool ModelServer::SetDirectryPath(std::string_view directry) {
      namespace fs = std::filesystem;
      // ディレクトリパスは設定されていないか
      if (!_directry.empty()) {
        return false; // 既に登録されている
      }
      // 対象ディレクトリは存在するか
      if (!fs::is_directory(directry.data())) {
        return false; // 存在しない
      }
      _directry = directry; // ディレクトパスを登録する
      return true;
    }

    bool ModelServer::LoadModel(std::string_view fileName) {
      // ファイルは存在するか
      if (!PathExist(fileName.data())) {
        return false; // 存在しない
      }
      // キーが重複してるかの判定
      if (_registry.contains(fileName.data())) {
        // 登録されている場合は既存データを削除する
        auto&& handles = _registry.at(fileName.data());
        DeleteHandles(handles);    // モデルハンドルを削除
        _registry.erase(fileName.data()); // 既存の要素を削除
        _animations.erase(fileName.data()); // アニメーションも削除
      }
      // モデルハンドルの読み取り
      auto handle = ModelServer::MV1LoadModel(fileName.data());
      std::vector<int> handles(handle);
      // アニメーション総数の取得
      auto animNum = MV1GetAnimNum(handle);
      for (auto no = 0; no < animNum; ++no) {
        // アニメーション名の取得
        auto animName = MV1GetAnimName(handle, no);
        // アニメーション名とアニメ番号を登録
        _animations.emplace(animName, no);
      }
      return true;
    }

    const int ModelServer::GetModelHandle(std::string_view key, const int no) {
      // 登録されている場合は判定を行う
      if (_registry.contains(key.data())) {
        auto handles = _registry.at(key.data());
      }
      return;
    }

    bool ModelServer::PathExist(std::filesystem::path path) {
#ifndef _DEBUG
      return std::filesystem::exists(_directry / path);
#else
      // 対象ファイルは存在するか
      if (!std::filesystem::exists(_directry / path)) {
        // 存在しない場合はログに出力
        DebugString(LogicError((_directry / path).string() + ":は存在しません").what());
        return true;
      }
      return true; // 存在する
#endif
    }

    void ModelServer::DeleteHandles(std::vector<int>& handles) {
      // 全モデルハンドルの削除を行う
      for (auto&& handle : handles) {
        MV1DeleteModel(handle);
      }
      handles.clear(); // コンテナを削除
    }

    int ModelServer::MV1LoadModel(std::filesystem::path path) const {
      return DxLib::MV1LoadModel((_directry / path).string().c_str());
    }
  } // namespace Model
} // namespace Gyro