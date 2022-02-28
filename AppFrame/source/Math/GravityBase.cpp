/*****************************************************************//**
 * @file   GravityBase.cpp
 * @brief  �d�͏������s���ÓI�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "GravityBase.h"
#include "Matrix44.h"
#include "Vector4.h"

namespace AppFrame{
  namespace Math {

    float GravityBase::GravityScale(float speed, float mass) {
      // ���ʂ��}�C�i�X���ǂ����̔���
      if(mass <= 0.0f) {
        // �}�C�i�X�̏ꍇ�͎��ʂ�0�ɂ���
        mass = 0.0f;
      }
      // �d�̓X�P�[����Ԃ�
      return speed + (_acceleration * mass);
    }
  }
}