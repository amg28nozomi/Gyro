/*****************************************************************//**
 * @file   AttackBone.cpp
 * @brief  ボーン情報クラスの定義クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "AttackBone.h"

namespace Gyro {
  namespace Object {

    AttackBone::AttackBone() {
      _bone.clear(); // コンテナをクリアする
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