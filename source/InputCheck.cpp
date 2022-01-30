/*****************************************************************//**
 * @file   InputCheck.cpp
 * @brief  
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "InputCheck.h"

namespace Gyro {
  namespace Application {

    InputCheck::InputCheck() {
      _total = 0.0f;
      _just = std::make_pair(0.0f, 0.0f);
    }

    InputCheck::InputCheck(float total, float justStart, float justEnd) {
      _total = total;

    }

    void InputCheck::Process(float frame) {
      // ���͔�����s��
      
    }

    bool InputCheck::JustTime(float start, float end) {
      // �J�n�t���[�����I���t���[�����傫���ꍇ�͒l���X���b�v
      if (end < start) {
        std::swap(start, end);
      }
      // �W���X�g���͎��Ԃ�ݒ�
      _just = std::make_pair(start, end);
      return true;
    }
  } // namespace Application
} // namespace Gyro