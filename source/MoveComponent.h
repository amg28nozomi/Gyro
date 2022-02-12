#pragma once
#include "ObjectComponent.h"

namespace AppFrame {
  namespace Math {
    class Vector4;
  }
}

namespace Gyro {
  namespace Object {
    class ObjectBase;
    /**
     * @brief 移動コンポーネント
     */
    class MoveComponent : public ObjectComponent {
      using Vector4 = AppFrame::Math::Vector4;
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
       * @brief  移動量の算出(自機用)
       * @param  move アナログスティックの入力情報ベクトル
       * @return 移動ベクトル
       */
      Vector4 Move(const Vector4& move) const;
    private:
      float _speed;
    };
  } // namespace Object
} // namespace Gyro