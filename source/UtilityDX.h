/*****************************************************************//**
 * @file   UtilityDX.h
 * @brief  DXライブラリ構造体への相互変換クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace AppFrame::Math {
  class Vector4;
  class Matrix44;
}

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @class UtilityDX
   * @brief DXライブラリに用意された構造体への相互変換クラス
   */
  class UtilityDX {
  public:
    /**
     * @brief  Vector4クラスの値をVECTOR構造体に変換する
     * @param  vector 変換対象
     * @return VECTOR構造体
     */
    static VECTOR ToVECTOR(AppFrame::Math::Vector4 vector);
    /**
     * @brief  VECTOR構造体をVector4クラスに変換する
     * @param  vector 変換対象
     * @return Vector4クラス
     */
    static AppFrame::Math::Vector4 ToVector(VECTOR& vector);
    /**
     * @brief  Matrix44クラスをMATRIX構造体に変換する
     * @param  matrix 変換対象となるMatrix44クラス
     * @return MATRIX構造体
     */
    static MATRIX ToMATRIX(AppFrame::Math::Matrix44 matrix);
  };
} // namespae AppFrame