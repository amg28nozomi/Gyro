/*****************************************************************//**
 * @file   WireComponent.h
 * @brief  ワイヤーアクション機能クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {
    class ObjectBase;
  }
  namespace Player {
    namespace AppMath = AppFrame::Math;
    using Vector4 = AppMath::Vector4;
    /**
     * @class 
     * @brief ワイヤーアクション機能
     */
    class WireComponent : public Object::ObjectComponent {
    public:

      WireComponent(Object::ObjectBase& owner);
      /**
       * @brief  ターゲット座標の設定
       * @param  target 対象の座標ベクトル
       * @param  time   移動時間
       * @return true:設定成功 false:設定失敗
       */
      bool SetTarget(const Vector4& target, const float time);
      /**
       * @brief 開始処理
       */
      void Start() override;
      /**
       * @brief 終了処理
       */
      void Finish() override;
      /**
       * @brief  
       * @return 
       */
      Vector4 WireMove();
      /**
       * @brief  ワイヤーアクション中かの判定
       * @return true:アクション中 false:アクション外
       */
      bool IsAction() const {
        return _wire;
      }
      /**
       * @brief  目標地点の取得
       * @return 目標地点
       */
      Vector4 Target() const {
        return _target;
      }
    private:
      //!< 所有者の参照
      Object::ObjectBase& _owner;
      //!< アクション開始座標
      Vector4 _start{};
      //!< ターゲット座標
      Vector4 _target{};
      //!< ターゲットへの向き
      Vector4 _forward{};
      //!< 移動時間
      float _time{0.0f};
      //!< ワイヤーアクションフラグ
      bool _wire{false};
    };
  } // namespace Player
} // namespace Gyro