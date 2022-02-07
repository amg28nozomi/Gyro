/*****************************************************************//**
 * @file   SpawnServer.h
 * @brief  オブジェクトのスポーン情報を管理するサーバクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "SpawnData.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationMain; //!< 前方宣言
  } // namespace Application
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase; //!< 前方宣言
    /**
     * @brief スポーン情報を格納した動的配列の別名
     */
    using SpawnTable = std::vector<SpawnData>;
    /**
     * @brief 番号をキーとしてスポーン情報を管理する連想配列
     */
    using SpawnMap = std::unordered_map<int, SpawnTable>;
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
       * @param  spawnMap スポーン情報が格納された連想配列
       * @return true:登録成功 false:問題発生
       */
      bool AddSpawnTable(std::string_view key, const SpawnMap& spawnMap);
      /**
       * @brief  オブジェクトの生成処理
       * @param  number 生成番号
       * @return true:生成成功 false:生成失敗
       */
      bool Spawn(const int number) const;
      /**
       * @brief  ステージキーの設定
       * @param  key ステージキー
       * @return true:切り替え成功 false:切り替え失敗
       */
      bool SetStage(std::string_view key);
    private:
      Application::ApplicationMain& _appMain; //!< アプリケーションの参照
      std::string _stage; //!< ステージキー
      /**
       * @brief  現在のステージに対応するコンテナの取得
       * @return ステージに紐づけられたスポーン情報
       */
      const SpawnMap NowSpawnMap() const;
      /**
       * @brief 指定したステージ情報を削除する
       * @param key ステージキー
       */
      void DeleteSpawnMap(std::string_view key);
      /**
       * @brief  オブジェクトの生成処理
       * @param  spawn スポーン情報
       * @return true:生成成功 false:生成失敗
       */
      bool Spawn(const SpawnTable& table) const;
      /**
       * @brief  オブジェクトサーバに生成したオブジェクトを登録する
       * @param  object オブジェクトのシェアードポインタ
       * @return true:登録成功 false:登録失敗
       */
      bool AddObject(std::shared_ptr<ObjectBase> object) const;
      /**
       * @brief  自機の生成
       * @param  spawn スポーン情報
       * @return 自機のシェアードポインタ
       *         自機が既に登録されている場合はnullptrを返す
       */
      std::shared_ptr<Player::Player> Player(const SpawnData& spawn) const;
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