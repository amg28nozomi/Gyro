/*****************************************************************//**
 * @file   SpawnData.cpp
 * @brief  �I�u�W�F�N�g�������Ɏg�p����p�����[�^�N���X�̒�`
 *
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "SpawnData.h"

namespace Gyro {
  namespace Object {

    SpawnData::SpawnData() {
      _type = ObjectType::None;
      _position = Vector4();
      _rotation = Vector4();
      _scale = Vector4();
    }

    SpawnData::SpawnData(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale) {
      // �e��p�����[�^�̐ݒ�
      _type = NumberToType(type);
      _position = position;
      _rotation = rotation;
      _scale = scale;
    }

    const SpawnData::ObjectType SpawnData::NumberToType(const int number) const {
      // �Ή������I�u�W�F�N�g�^�C�v��Ԃ�
      switch (number) {
      case TypePlayer:
        return ObjectType::Player; // ���@
      default:
        return ObjectType::None;   // �Y���Ȃ�
      }
    }
  } // namespace Object
} // namespace AppFrame