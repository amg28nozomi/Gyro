/*****************************************************************//**
 * @file   ObjectServer.h
 * @brief  オブジェクトを管理するサーバクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <appframe.h>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  namespace AppMath = AppFrame::Math;

  namespace Player {
    class Player;
  }
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase; //!< 前方宣言
    /**
     * @class ObjectServer
     * @brief オブジェクトを管理するサーバクラス
     */
    class ObjectServer : public AppFrame::Server::ServerTemplateVector<std::shared_ptr<ObjectBase>> {
    public:
      /**
       * @brief コンストラクタ
       */
      ObjectServer();
      /**
       * @brief デストラクタ
       */
      ~ObjectServer();
      /**
       * @brief  リソースの解放処理
       * @return true
       */
      bool Release() override;
      /**
       * @brief  登録オブジェクトの更新
       * @return true
       */
      bool Process();
      /**
       * @brief  描画処理の呼び出し
       * @return true
       */
      bool Draw();
      /**
       * @brief  外部からオブジェクトを登録する
       * @param  object オブジェクトのスマートポインタ
       * @return true:登録成功 false:登録失敗
       */
      bool Register(std::shared_ptr<ObjectBase> object);

      std::vector<std::shared_ptr<ObjectBase>> GetObjects();
      /**
       * @brief  自機の取得
       * @return 自機ポインタの参照
       */
      std::shared_ptr<Player::Player> GetPlayer();
      /**
       * @brief  自機のトランスフォームを取得する
       * @param  position Vector4クラスの参照(自機座標格納用)
       * @param  rotation Vector4クラスの参照(自機回転量格納用)
       * @return true:取得成功 false:取得失敗
       */
      bool GetPlayerTransForm(AppMath::Vector4& position, AppMath::Vector4& rotation);
    private:
      bool _play{false}; //!< オブジェクトサーバを回しているかのフラグ
      std::vector<std::shared_ptr<ObjectBase>> _addObject; //!< 登録予約用
      /**
       * @brief  オブジェクトの登録処理
       * @param  obj オブジェクトのシェアードポインタ
       * @return true:登録成功 false:登録失敗
       */
      bool AddObject(std::shared_ptr<ObjectBase> obj);
      /**
       * @brief  オブジェクトが登録されているコンテナを解放する
       * @param  container オブジェクトのシェアードポインタが格納されたコンテナの参照
       */
      void DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& container);
      /**
       * @brief コンテナのオブジェクトをレジストリ―に登録する
       * @param container オブジェクトのシェアードポインタが格納されたコンテナの参照
       */
      void AddObjects(std::vector<std::shared_ptr<ObjectBase>>& container);
      /**
       * @brief  オブジェクトの登録予約
       * @param  object オブジェクトのシェアードポインタ
       * @return ture:予約成功 false:予約失敗
       */
      bool AddReserve(std::shared_ptr<ObjectBase> object);
    };
  } // namespace Object
} // namespace Gyro