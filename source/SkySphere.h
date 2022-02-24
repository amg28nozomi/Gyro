/*****************************************************************//**
 * @file   SkySphere.h
 * @brief  スカイスフィアクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class  SkySphere
     * @brief  スカイスフィアクラス
     */
    class SkySphere : public ObjectBase {
    public:
      /**
       * @brief コンストラクタ
       */
      SkySphere(Application::ApplicationMain& app, ObjectBase& owner);
      /**
       * @brief 初期化処理
       */
      bool Init() override;
      /**
       * @brief  オブジェクトの設定
       * @param  spawn 生成情報
       */
      void Set(Object::SpawnBase& spawn) override;
      /**
       * @brief  更新処理
       * @return true:更新成功 false:更新失敗
       */
      bool Process() override;
      /**
       * @brief  描画処理
       */
      bool Draw() const override;
      /**
       * @brief  モデルハンドルの設定
       * @param  key モデルハンドルに紐づけられた文字列
       * @return true:設定成功 false:設定失敗
       */
      bool SetKey(std::string_view key);
      /**
       * @brief  ハンドルの取得
       * @return モデルハンドル
       */
      int GetHandle() const {
        return _handle;
      }
    protected:
      //!< 所有者の参照
      Object::ObjectBase& _owner;
      //!< モデルハンドル
      int _handle;
    };
  } // namespace Interior
} // namespace Gyro