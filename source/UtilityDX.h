/*****************************************************************//**
 * @file   UtilityDX.h
 * @brief  
 * 
 * @author 鈴木希海
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
     * @brief  Vector4クラスの値をVECTOR構造体に変換する
     * @param  vector 変換対象
     * @return VECTOR構造体
     */
    static VECTOR ToVECTOR(AppFrame::Math::Vector4& vector);
    /**
     * @brief  VECTOR構造体をVector4クラスに変換する
     * @param  vector 変換対象
     * @return Vector4クラス
     */
    static AppFrame::Math::Vector4 ToVector(VECTOR& vector);
  };
}
