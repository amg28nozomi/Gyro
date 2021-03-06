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
      /**
       * @brief  コンテナに登録されているオブジェクトを解放する
       * @param  flag 自機を解放するかの判定(true:自機も削除する(デフォルト) false:自機のみ残す)
       */
      void ObjectClear(const bool flag);
      /**
       * @brief  登録オブジェクトの取得
       * @return オブジェクトのシェアードポインタが格納された動的配列
       */
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
      /**
       * @brief  自機が登録されているかの判定
       * @return true:登録されている false:登録されていない
       */
      bool FindPlayer() const;
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
       * @brief  末尾の前にオブジェクトを登録する
       * @param  obj オブジェクトのシェアードポインタ
       * @return true:登録成功 false:登録失敗
       */
      void Insert(std::shared_ptr<ObjectBase> obj);
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
      /**
       * @brief  末尾のオブジェクトが自機かの判定
       * @return true:自機が登録されている false:自機は登録されていない
       */
      bool LastPlayer() const;
      /**
       * @brief  自機のシェアードポインタの所有権を取得する
       * @return 自機が登録されている場合は自機のシェアードポインタを返す
       *         未登録の場合はnullptrを返す
       */
      std::shared_ptr<ObjectBase> MovePlayer();
    };
  } // namespace Object
} // namespace Gyro