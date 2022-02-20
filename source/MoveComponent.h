/*****************************************************************//**
 * @file   MoveComponent.h
 * @brief  移動コンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase;
    namespace AppMath = AppFrame::Math;
    /**
     * @brief 移動コンポーネント
     */
    class MoveComponent : public ObjectComponent {
    public:
      /**
       * @brief コンストラクタ
       * @param owner 所有者
       */
      MoveComponent(ObjectBase& owner);
      /**
       * @brief 移動量の設定
       * @param speed
       */
      void Set(const float speed) {
        _speed = speed;
      }
      /**
       * @brief 移動処理の開始
       */
      void Start() override;
      /**
       * @brief 移動処理の更新
       */
      void Finish() override;
      /**
       * @brief 前フレーム座標の更新
       */
      void OldPosition();
      /**
       * @brief  移動量の更新
       * @param  x x軸の入力状態
       * @param  z z軸の入力状態
       * @return true:移動量有り false:移動量無し
       */
      bool Move(const float x, const float z);
      /**
       * @brief  移動量(平行移動行列)の取得
       * @return 平行移動行列
       */
      AppMath::Matrix44 MoveTranslate() {
        return AppMath::Matrix44::Translate(_move);
      }
      /**
       * @brief  所有者の前フレーム座標の取得
       * @return 所有者の前フレーム座標
       */
      AppMath::Vector4 OldPosition() const {
        return _oldPosition;
      }
      /**
       * @brief  移動量(ベクトル)の取得
       * @return 移動量ベクトル
       */
      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    private:
      //!< 所有者の参照
      ObjectBase& _owner;
      //!< 所有者の前フレーム座標
      AppMath::Vector4 _oldPosition{};
      //!< 移動ベクトル
      AppMath::Vector4 _move{};
      //!< 速度
      float _speed;
    };
  } // namespace Object
} // namespace Gyro