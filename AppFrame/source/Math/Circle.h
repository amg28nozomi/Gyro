/*****************************************************************//**
 * @file   Circle.h
 * @brief  円の情報クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "Vector4.h"
/**
 * @brief フレームワーク
 */
namespace AppFrame {
  /**
   * @brief 算術ベース
   */
  namespace Math {
    /**
     * @class Circle
     * @brief 円の情報クラス
     */
    class Circle {
    public:
      /**
       * @brief コンストラクタ
       * @param center 中心座標
       * @param radius 半径
       */
      Circle(const Vector4& center, const float radius);
      /**
       * @brief 中心座標の更新
       * @param move 移動量
       */
      void Process(const Vector4& move);
      /**
       * @brief  中心座標の取得
       * @return 中心座標
       */
      Vector4 GetCenter() const {
        return _center;
      }
      /**
       * @brief  半径の取得
       * @return 半径
       */
      float GetRadius() const {
        return _radius;
      }
    private:
      Vector4 _center; //!< 中心座標
      float _radius;   //!< 半径
    };
  } // namespace Math
} // namespaece AppFrame