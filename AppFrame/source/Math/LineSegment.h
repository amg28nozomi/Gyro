/*****************************************************************//**
 * @file   LineSegment.h
 * @brief  線分クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
#include "Vector4.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief 算術ベース
   */
  namespace Math {
    class Plane; //!< 
    /**
     * @class LineSegment
     * @brief 線分ベクトル
     */
    class LineSegment {
    public:
      /**
       * @brief 空のコンストラクタ
       */
      LineSegment();
      /**
       * @brief コンストラクタ
       */
      LineSegment(Vector4 first, Vector4 end);
      /**
       * @brief  線分と点の最短距離の二乗の取得
       * @param  point 座標
       * @return 線分と点の最短距離の二乗
       */
      float MinDistSq(const Vector4& point) const;
      /**
       * @brief  線分と線分の最短距離を取得
       * @param  line 線分
       * @return 線分と線分の最短距離
       */
      float MinDist(const LineSegment& line) const;
      /**
       * @brief  線分の長さを取得
       * @return 線分の長さ
       */
      float Length() const;
      /**
       * @brief  線分の長さの二乗を取得
       * @return 線分の長さの二乗
       */
      float LengthSquared() const;
      /**
       * @brief  平面との衝突判定
       * @param  plane 平面
       * @return true:衝突 false:衝突していない
       */
      bool IntersectPlane(const Plane& plane) const;
      /**
       * @brief  ベクトルの取得
       * @return first:先端 second:終端
       */
      std::pair<Vector4, Vector4> GetVector() const {
        return std::make_pair(_start, _end);
      }
      /**
       * @brief  先端ベクトルの取得
       * @return 先端ベクトル
       */
      Vector4 GetStart() const {
        return _start;
      }
      /**
       * @brief  終端ベクトルの取得
       * @return 終端ベクトル
       */
      Vector4 GetEnd() const {
        return _end;
      }
      /**
       * @brief  線分の取得
       * @return 終端から先端を引いたベクトル
       */
      Vector4 Segment() const {
        return _end - _start;
      }
    private:
      Vector4 _start; //!< 先端ベクトル
      Vector4 _end;   //!< 終端ベクトル
    };
  } // namespace Math
} // namespace AppFrame