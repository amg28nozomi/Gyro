/*****************************************************************//**
 * @file   SpawnBase.cpp
 * @brief  オブジェクト生成時に使用するパラメータクラスの定義
 *
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "SpawnBase.h"

namespace Gyro {
  namespace Object {

    SpawnBase::SpawnBase() {
      _type = ObjectType::None;
      _position = Vector4();
      _rotation = Vector4();
      _scale = Vector4();
    }

    SpawnBase::SpawnBase(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale) {
      // 各種パラメータの設定
      _type = NumberToType(type);
      _position = position;
      _rotation = rotation;
      _scale = scale;
    }

    const SpawnBase::ObjectType SpawnBase::NumberToType(const int number) const {
      // 対応したオブジェクトタイプを返す
      switch (number) {
      case TypePlayer:
        return ObjectType::Player; // 自機
      case TypeEnemyWheel:
        return ObjectType::Enemy;  // エネミー
      default:
        return ObjectType::None;   // 該当なし
      }
    }
  } // namespace Object
} // namespace AppFrame