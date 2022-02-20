/*****************************************************************//**
 * @file   ModelAnimData.cpp
 * @brief  �A�j���[�V�������N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "ModelAnimData.h"

namespace Gyro {
  namespace ModelAnim {

    ModelAnimData::ModelAnimData() {
      // �e��p�����[�^�̏�����
      _name.clear();
      _effect.clear();
      _blendFrame = 0.0f;
      _speed = 0.0f;
      _loop = false;
    }

    ModelAnimData::ModelAnimData(std::string_view name, const float frame, const float speed, bool loop, std::string_view effect) {
      // �e��p�����[�^�̐ݒ�
      _name = name.data();
      _effect = effect.data();
      _blendFrame = frame;
      _speed = speed;
      _loop = loop;
    }
  } // namespace ModelAnim
} // namespace Gyro