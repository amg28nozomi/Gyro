/*****************************************************************//**
 * @file   UtilityDX.h
 * @brief  
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace AppFrame::Math {
  class Vector4;
}

namespace Gyro {
  /**
   * @class UtilityDX
   * @brief 
   */
  class UtilityDX {
  public:
    /**
     * @brief  Vector4�N���X�̒l��VECTOR�\���̂ɕϊ�����
     * @param  vector �ϊ��Ώ�
     * @return VECTOR�\����
     */
    static VECTOR ToVECTOR(AppFrame::Math::Vector4& vector);
    /**
     * @brief  VECTOR�\���̂�Vector4�N���X�ɕϊ�����
     * @param  vector �ϊ��Ώ�
     * @return Vector4�N���X
     */
    static AppFrame::Math::Vector4 ToVector(VECTOR& vector);
  };
}
