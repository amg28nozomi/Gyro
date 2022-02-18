/*****************************************************************//**
 * @file   AttackBone.cpp
 * @brief  �{�[�����N���X�̒�`�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "AttackBone.h"

namespace Gyro {
  namespace Object {

    AttackBone::AttackBone() {
      _bone.clear(); // �R���e�i���N���A����
    }

    AttackBone::AttackBone(int bone) {
      _bone.clear();
      _bone.emplace_back(bone);
    }

    AttackBone::AttackBone(int a, int b) {
      _bone.emplace_back(a);
      _bone.emplace_back(b);
    }

  } // namespace Object
} // namespace Gyro