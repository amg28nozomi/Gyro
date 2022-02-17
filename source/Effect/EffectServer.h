/*****************************************************************//**
 * @file    EffectServer.h
 * @brief   エフェクトを管理するサーバクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "../ApplicationMain.h"

 /** 作品用名前空間 */
namespace Gyro {
  /** エフェクト用名前空間 */
  namespace Effect {
    namespace AppServer = AppFrame::Server;
    /**
     * @class EffectServer
     * @brief エフェクトを管理するサーバクラス
     */
    class EffectServer : AppServer::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief  エフェクト情報を格納する動的配列
                 first:エフェクトファイルに紐づける文字列
                 second:エフェクトファイルのパス
       */
      using EffectMap = std::vector<std::pair<std::string_view, std::string_view>>;
      /**
       * @brief  エフェクト情報を格納する動的配列
                 first:エフェクトファイルに紐づける文字列
                 second:エフェクト拡大率
       */
      using EffectMagniMap = std::vector<std::pair<std::string_view, float>>;
      /**
       * @brief  コンストラクタ
       */
      EffectServer();
      /**
       * @brief  解放処理
       * @return true:正常
       *         false:異常終了
       */
      bool Release() override;
      /**
       * @brief  エフェクトファイルの読み取り
       * @param  key エフェクトハンドルに紐づける文字列
       * @param  effectFile エフェクトファイルのパス
       * @param  magni エフェクト拡大率
       * @return true:正常終了
       *         false:読み取り失敗
       */
      bool AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni);
      /**
       * @brief  コンテナを使用したエフェクトファイルの読み取り
       * @param  effectMap エフェクト情報が格納されたコンテナ
       * @param  effectMagniMap エフェクト拡大率が格納されたコンテナ
       */
      void AddEffects(const EffectMap& effectMap, const EffectMagniMap& effectMagniMap);
      /**
       * @brief  指定したエフェクトハンドルの取得
       * @param  key 対象のエフェクトハンドルに紐づけられた文字列
       * @return エフェクトハンドル
       *         キーが有効ではない場合は-1を返す
       */
      int GetEffectHandle(std::string_view key) const;
    };
  } // namespace Effect
} // namespace Gyro