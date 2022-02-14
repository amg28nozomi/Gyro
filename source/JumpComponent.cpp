/*****************************************************************//**
 * @file   JumpComponent.cpp
 * @brief  �W�����v�@�\�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "JumpComponent.h"
#include <appframe.h>
#include <cmath>

namespace Gyro {
  namespace Player {

    JumpComponent::JumpComponent() {
      _type = ComponentType::Jump;
    }

    void JumpComponent::Set(const float range, const int fright) {
      _range = range;
      _fright = fright;
      _f = fright;
    }

    void JumpComponent::Start() {
      // �W�����v�����̊J�n
      _count = 0;
      _jump = true;
    }

    void JumpComponent::Finish() {
      // �W�����v�����̌�n�����s��
      _count = 0;
      _power = 0.0f;
      _jump = false;
    }

    float JumpComponent::JumpPower() {
      ++_count; // ���Ԍo��
      // �o�ߎ��Ԃ����΋󎞊Ԃ𒴉߂����ꍇ�̓��Z�b�g
      if (_fright == _count) {
        _old = _power - _old;
        Finish();
        return _old;
      }
      // cast
      auto t = static_cast<float>(_count);
      auto fi = static_cast<float>(_f);
      _old = _power; // �O�t���[���̒�����
      auto radian = AppFrame::Math::Utility::_pi / _f;
      _power = _range * std::sin(radian * _count);
      return _power - _old;
    }

  } // namespace Player
} // namespace Gyro