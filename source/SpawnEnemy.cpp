/*****************************************************************//**
 * @file   SpawnEnemy.cpp
 * @brief  �X�|�[���x�[�X�̃T�u�N���X
 *         �G�l�~�[�p�̃X�|�[�����N���X�̒�`
 * 
 * @author ��؊�C
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
      case EnemyWheel: // ����^�G�l�~�[
        return EnemyType::Wheel;
      case EnemyDrone: // �󒆌^�G�l�~�[
        return EnemyType::Drone;
      default:         // �Y���Ȃ�
        return EnemyType::None;
      }
    }
  } // namespace Object
} // namespace Gyro