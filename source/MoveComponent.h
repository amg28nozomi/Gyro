#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

namespace Gyro {
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

      void Start() override;

      void Finish() override;
      /**
       * @brief  移動量の算出(自機用)
       * @param  move アナログスティックの入力情報ベクトル
       * @return 移動ベクトル
       */
      AppMath::Vector4 Move(const AppMath::Vector4& move);

      AppMath::Matrix44 GetTranslate() {
        return AppMath::Matrix44::Translate(_move);
      }

      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    private:
      ObjectBase& _owner;
      AppMath::Vector4 _move{}; //!< 移動ベクトル
      float _speed;  //!< 速度
    };
  } // namespace Object
} // namespace Gyro