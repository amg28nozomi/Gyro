/*****************************************************************//**
 * @file   UtilityDX.h
 * @brief  DX���C�u�����\���̂ւ̑��ݕϊ��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace AppFrame::Math {
  class Vector4;
  class Matrix44;
}

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @class UtilityDX
   * @brief DX���C�u�����ɗp�ӂ��ꂽ�\���̂ւ̑��ݕϊ��N���X
   */
  class UtilityDX {
  public:
    /**
     * @brief  Vector4�N���X�̒l��VECTOR�\���̂ɕϊ�����
     * @param  vector �ϊ��Ώ�
     * @return VECTOR�\����
     */
    static VECTOR ToVECTOR(AppFrame::Math::Vector4 vector);
    /**
     * @brief  VECTOR�\���̂�Vector4�N���X�ɕϊ�����
     * @param  vector �ϊ��Ώ�
     * @return Vector4�N���X
     */
    static AppFrame::Math::Vector4 ToVector(VECTOR& vector);
    /**
     * @brief  Matrix44�N���X��MATRIX�\���̂ɕϊ�����
     * @param  matrix �ϊ��ΏۂƂȂ�Matrix44�N���X
     * @return MATRIX�\����
     */
    static MATRIX ToMATRIX(AppFrame::Math::Matrix44 matrix);
  };
} // namespae AppFrame