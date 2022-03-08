/*****************************************************************//**
 * @file   SpawnServer.h
 * @brief  オブジェクトのスポーン情報を管理するサーバクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "SpawnBase.h"
#include "SpawnEnemy.h"
#include "StageComponent.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    class Player; //!< プレイヤー
  } // namespace Player
  /**
   * @brief エネミーベース
   */
  namespace Enemy {
    class EnemyWheel; //!< 前方宣言
    class EnemyDrone; //!< 前方宣言
  } // namespace 
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationMain; //!< 前方宣言
  } // namespace Application
  namespace Stage {
    class StageComponent;
  }
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase; //!< 前方宣言
    class SkySphere;  //!< スカイスフィア
    /**
     * @brief スポーン情報を格納する動的配列の別名
     */
    using SpawnTable = std::vector<SpawnBase>;
    /**
     * @brief エネミーのスポーン情報を格納する動的配列の別名
     */
    using EnemyTable = std::vector<SpawnEnemy>;
    /**
     * @brief 登録時に使用する各種スポーン情報を数値で管理する連想配列
     *        0:スポーンテーブル 1:エネミーテーブル
     */
    using SpawnData = std::unordered_map<int, std::tuple<SpawnTable, EnemyTable>>;
    /**
     * @brief 番号をキーとしてスポーン情報のシェアードポインタを管理する連想配列の別名
     */
    using SpawnMap = std::unordered_map<int, std::vector<std::shared_ptr<SpawnBase>>>;
    /**
     * @class SpawnServer
     * @brief ステージ名をキーとしてスポーン情報を管理するサーバクラス
     */
    class SpawnServer : public AppFrame::Server::ServerTemplateUnordered<std::string, SpawnMap> {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションメインの参照
       */
      SpawnServer(Application::ApplicationMain& app);
      /**
       * @brief  解放処理
       * @return true
       */
      bool Release() override;
      /**
       * @brief  スポーン情報の登録
       * @param  key スポーン情報に紐づける文字列(ステージ名)
       * @param  spawnMap スポーン情報のインスタンスが登録された連想配列
       * @return true:登録成功 false:問題発生
       */
      bool AddSpawnTable(std::string_view key, SpawnData spawnMap);
      /**
       * @brief  オブジェクトの生成処理
       * @param  number 生成番号
       * @return true:生成成功 false:生成失敗
       */
      bool Spawn(const int number);
      /**
       * @brief  ステージキーの設定
       * @param  key ステージキー
       * @return true:切り替え成功 false:切り替え失敗
       */
      bool SetStage(std::string_view key);
    private:
      Application::ApplicationMain& _appMain; //!< アプリケーションの参照
      std::string _stage; //!< ステージキー
      //!< エネミーのテーブル情報を管理する連想配列
      std::unordered_map<std::string, std::unordered_map<int, EnemyTable>> _enemyTable;
      /**
       * @brief  現在のステージに対応するコンテナの取得
       * @return ステージに紐づけられたスポーン情報
       */
      SpawnMap& NowSpawnMap();
      /**
       * @brief 指定したスポーン情報を削除する
       * @param key ステージキー
       */
      void Delete(std::string_view key);
      /**
       * @brief  オブジェクトの生成処理
       * @param  spawn スポーン情報の参照
       * @return true:生成成功 false:生成失敗
       */
      bool SpawnObject(const int numebr);
      /**
       * @brief  オブジェクトサーバに生成したオブジェクトを登録する
       * @param  object オブジェクトのシェアードポインタ
       * @return true:登録成功 false:登録失敗
       */
      bool AddObject(std::shared_ptr<ObjectBase> object) const;
      /**
       * @brief
       * @param  skysphere
       * @return 
       */
      void AddSkySphere(std::shared_ptr<SkySphere> skysphere);
      /**
       * @brief  自機の生成
       * @param  spawn スポーン情報
       * @return 自機のシェアードポインタ
       *         自機が既に登録されている場合はnullptrを返す
       */
      std::shared_ptr<Player::Player> Player(std::shared_ptr<SpawnBase>& spawn) const;
      /**
       * @brief  エネミーの生成
       * @param  spawn スポーン情報
       * @return エネミーのシェアードポインタ
       */
      std::shared_ptr<ObjectBase> Enemy(std::shared_ptr<SpawnBase>& spawn) const;
      /**
       * @brief  陸上型敵の生成
       * @param  spawn スポーン情報
       * @return 陸上型敵のシェアードポインタ
       */
      std::shared_ptr<Enemy::EnemyWheel> EnemyWheel(SpawnEnemy& spawn) const;
      /**
       * @brief  空中型敵の生成
       * @param  spawn スポーン情報
       * @return 空中型敵のシェアードポインタ
       */
      std::shared_ptr<Enemy::EnemyDrone> EnemyDrone(SpawnEnemy& spawn) const;
      /**
       * @brief  スカイスフィアの生成
       * @param  spawn スポーン情報
       * @return スカイスフィアのシェアードポインタ
       */
      std::shared_ptr<SkySphere> Skysphere(std::shared_ptr<SpawnBase>& spawn) const;
#ifdef _DEBUG
      /**
       * @brief  スポーン失敗メッセージの生成
       * @param  number 処理回数
       */
      std::logic_error SpawnError(const int number) const;
#endif
    };
  } // namespace Object
} // namespace Gyro