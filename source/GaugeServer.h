/*****************************************************************//**
 * @file   GaugeServer.h
 * @brief  ゲームゲージを管理するゲージサーバー
 * 
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <appframe.h>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief ゲージベース
   */
  namespace Gauge {
    class GaugeBase; //!< 前方宣言
    /**
     * @class GaugeServer
     * @brief ゲームゲージを管理するゲージサーバー
     */
    class GaugeServer : AppFrame::Server::ServerTemplateVector<std::shared_ptr<GaugeBase>> {
    public:
      /**
       * @brief コンストラクタ
       */
      GaugeServer();
      /**
       * @brief デストラクタ
       */
      ~GaugeServer();
      /**
       * @brief  リソースの解放
       * @return true
       */
      bool Release() override;
      /**
       * @brief  登録ゲージの更新
       * @return true
       */
      bool Process();
      /**
       * @brief  描画処理の呼び出し
       * @return true
       */
      bool Draw();
      /**
       * @brief  外部からゲージを登録する
       * @param  gauge ゲージのスマートポインタ
       * @return true:登録成功 false:登録失敗
       */
      bool Register(std::shared_ptr<GaugeBase> gauge);
      /**
       * @brief  ゲージサーバーの取得
       * @return ゲージサーバーの参照
       */
      std::vector<std::shared_ptr<GaugeBase>> GetGauge();
    private:
      bool _play{ false }; //!< ゲージサーバーを回しているかのフラグ
      std::vector<std::shared_ptr<GaugeBase>> _addGauge; //!< 登録予約用
      /**
       * @brief  ゲージの登録
       * @param  gauge ゲージのスマートポインタ
       * @return true:登録成功 false:登録失敗
       */
      bool AddGauge(std::shared_ptr<GaugeBase> gauge);
      /**
       * @brief ゲージが登録されているコンテナを解放する
       * @param container ゲージのシェアードポインタが格納されたコンテナの参照
       */
      void DeleteGauge(std::vector<std::shared_ptr<GaugeBase>>& container);
      /**
       * @brief コンテナのゲージをレジストリーに登録する
       * @param container ゲージのシェアードポインタが格納されたコンテナの参照
       */
      void AddGauges(std::vector<std::shared_ptr<GaugeBase>>& container);
      /**
       * @brief  ゲージの登録予約
       * @param  gauge ゲージのシェアードポインタ
       * @return true:予約成功 false:予約失敗
       */
      bool AddReserve(std::shared_ptr<GaugeBase> gauge);
    };
  } // namespace Gauge
} // namespace Gyro

