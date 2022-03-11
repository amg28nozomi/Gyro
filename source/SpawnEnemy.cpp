/*****************************************************************//**
 * @file   SpawnEnemy.cpp
 * @brief  スポーンベースのサブクラス
 *         エネミー用のスポーン情報クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "SpawnEnemy.h"

namespace Gyro{
  namespace Object {

    SpawnEnemy::SpawnEnemy() : SpawnBase() {
      _enemyType = EnemyType::None;
    }

    SpawnEnemy::SpawnEnemy(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale) {
      _type = ObjectType::Enemy;
      _enemyType = NumberToEnemyType(type);
      SetTransForm(position, rotation, scale);
    }

    const SpawnEnemy::EnemyType SpawnEnemy::NumberToEnemyType(const int number) const {
      switch (number) {
      case EnemyWheel: // 陸上型エネミー
        return EnemyType::Wheel;
      case EnemyDrone: // 空中型エネミー
        return EnemyType::Drone;
      default:         // 該当なし
        return EnemyType::None;
      }
    }
  } // namespace Object
} // namespace Gyro