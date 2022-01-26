/*****************************************************************//**
 * @file   ScoreServer.cpp
 * @brief  ゲームスコアを管理するスコアサーバの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ScoreServer.h"
#include "ScoreBase.h"

namespace Gyro {
  namespace Score {

    ScoreServer::ScoreServer() : AppFrame::Server::ServerTemplateUnordered<std::string, ScoreBase>() {
#ifdef _DEBUG
      SetServerName("ScoreServer"); // サーバ名の設定
#endif
    }

    bool ScoreServer::Release() {
      using UnorderedServer = AppFrame::Server::ServerTemplateUnordered<std::string, ScoreBase>;
      return UnorderedServer::Release();
    }

    bool ScoreServer::AddScore(std::string_view key, ScoreBase score) {
      // キーが登録済みの場合はスコアの比較を行う
      if (!UseKey(key.data())) {
        // 登録対象は登録されているスコアを上回っているか
        if (_registry[key.data()].IsBig(score) != true) {
          return false; // 対象未満のため登録しない
        }
        // 対象スコアを削除する
        _registry.erase(key.data());
      }
      // スコアを登録する
      _registry.emplace(key.data(), score);
      return true;
    }

    int ScoreServer::GetScore(std::string_view key) const {
      // キーが登録されているか
      if (UseKey(key.data())) {
        return -1; // 未登録
      }
      // ゲームスコアを返す(整数値)
      return _registry.at(key.data()).GetInteger();
    }

    bool ScoreServer::EraceScore(std::string_view key) {
      // キーが登録されているか
      if (UseKey(key.data())) {
        return false; // 未登録
      }
      // 対象スコアデータを削除する
      _registry.erase(key.data());
      return true; // 削除成功
    }
  } // namespace Score
} // namespace Gyro