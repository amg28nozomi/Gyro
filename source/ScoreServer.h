/*****************************************************************//**
 * @file   ScoreServer.h
 * @brief  ゲームスコアを管理するスコアサーバ
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief スコアベース
   */
  namespace Score {
    /**
     * @class ScoreServer
     * @brief ゲームスコアの管理を行うスコアサーバ
     */
    class ScoreServer : AppFrame::Server::ServerTemplateUnordered<std::string, class ScoreBase> {
    public:
      /**
       * @brief コンストラクタ
       */
      ScoreServer();
      /**
       * @brief  解放処理
       * @return true
       */
      bool Release() override;
      /**
       * @brief  スコアの登録
       * @param  key スコアに紐づける文字列
       * @param  score 登録スコア
       * @return true:登録成功 false:登録失敗
       */
      bool AddScore(std::string_view key, ScoreBase score);
      /**
       * @brief  指定したキーのスコアを取得する
       * @param  key スコアに紐づけられた文字列
       * @return 対象スコアを返す
       *         取得に失敗した場合は-1を返す
       */
      int GetScore(std::string_view key) const;
      /**
       * @brief  指定したスコアデータを削除する
       * @param  key スコアに紐づけられた文字列
       * @return true:成功 false:失敗
       */
      bool EraceScore(std::string_view key);
    private:
      /**
       * @brief  ゲームスコア同士の比較処理
       * @param  left  ゲームスコア
       * @param  right ゲームスコア
       * @return 
       */
      bool ScoreCheck(const ScoreBase left, const ScoreBase right) const;
    };
  } // namespace Score
} // namespace Gyro