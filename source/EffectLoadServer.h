/*****************************************************************//**
 * @file    EffectLoadServer.h
 * @brief   エフェクトを管理するサーバクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief エフェクトベース
   */
  namespace Effect {
    namespace AppServer = AppFrame::Server;
    /**
     * @class EffectLoadServer
     * @brief エフェクトを管理するサーバクラス
     */
    class EffectLoadServer : AppServer::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief  エフェクト情報を格納する動的配列
       * @param  エフェクトファイルに紐づける文字列
       * @param  エフェクトファイルのパス
       * @param  エフェクト拡大率
       */
      using EffectMap = std::vector<std::tuple<std::string_view, std::string_view, float>>;
      /**
       * @brief  コンストラクタ
       */
      EffectLoadServer();
      /**
       * @brief  解放処理
       * @return true
       */
      bool Release() override;
      /**
       * @brief  コンテナを使用したエフェクトファイルの読み取り
       * @param  effectMap エフェクト情報が格納されたコンテナ
       */
      void AddEffects(const EffectMap& effectMap);
      /**
       * @brief  指定したエフェクトハンドルの取得
       * @param  key 対象のエフェクトハンドルに紐づけられた文字列
       * @return エフェクトハンドル
       *         キーが有効ではない場合は-1を返す
       */
      int GetEffectHandle(std::string_view key) const;

    private:
      /**
       * @brief  エフェクトファイルの読み取り
       * @param  key エフェクトハンドルに紐づける文字列
       * @param  effectFile エフェクトファイルのパス
       * @param  magni エフェクト拡大率
       * @return true:正常終了
       *         false:読み取り失敗
       */
      bool AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni);
    };
  } // namespace Effect
} // namespace Gyro