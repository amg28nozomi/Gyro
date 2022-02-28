/*****************************************************************//**
 * @file   LineSegment.cpp
 * @brief  線分クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "LineSegment.h"
#include <DxLib.h>
#include "Arithmetic.h"
#include "Vector4.h"
#include "Plane.h"

namespace AppFrame {
  namespace Math {

    LineSegment::LineSegment() : _start(), _end() {
    }

    LineSegment::LineSegment(Vector4 start, Vector4 end) : _start(start), _end(end){
    }

    float LineSegment::Length() const {
      // 長さを返す
      return (_end - _start).Length();
    }

    float LineSegment::LengthSquared() const {
      return (_end - _start).LengthSquared();
    }

    float LineSegment::MinDistSq(const Vector4& point) const {
      // 各種ベクトル
      auto lineA = _end - _start; // ベクトルの長さ
      auto LineB = lineA * -1.0f;
      auto sC = point - _start;
      auto endC = point - _end;
      // 
      if (Vector4::Dot(lineA, sC) < 0.0f) {
        return sC.LengthSquared(); // 長さの二乗を返す
      }
      else if (Vector4::Dot(LineB, endC) < 0.0f) {
        return endC.LengthSquared();
      }
      auto scalar = Vector4::Dot(sC, lineA) / Vector4::Dot(lineA, lineA);
      auto p = lineA * scalar;
      return (sC - p).LengthSquared();
    }

    bool LineSegment::IntersectPlane(const Plane& plane) const {
      auto pNormal = plane.GetNormal();
      auto d = Vector4::Dot(Segment(), pNormal);
      // 平面と線分は平行か
      if (Arithmetic::NearZero(d)) {
        if (Arithmetic::NearZero(Vector4::Dot(_start, pNormal) - plane.GetDistance())) {
          return true; // 衝突
        }
        return false; // 衝突していない
      }
      auto numer = -Vector4::Dot(_start, pNormal) - plane.GetDistance();
      auto t = numer / d;
      // tが線分の境界内に存在するか
      if (0.0f <= t && t <= 1.0f) {
        return true; // 衝突した
      }
      return false;  // 衝突していない
    }

    float LineSegment::MinDist(const LineSegment& line) const {
      auto [start, end] = line.GetVector(); // 線分ベクトルの取得
      // 応急措置用
      VECTOR startA(_start.GetX(), _start.GetY(), _start.GetZ());
      VECTOR startB(start.GetX(), start.GetY(), start.GetZ());
      VECTOR endA(_end.GetX(), _end.GetY(), _end.GetZ());
      VECTOR endB(end.GetX(), end.GetY(), end.GetZ());
      // 最短距離を返す
      return Segment_Segment_MinLength_Square(startA, endA, startB, endB);

      //// 線分は縮退しているか
      //if (LengthSquared() < 0.0f) {
      //  // 対象の線分は縮退しているか
      //  if (line.LengthSquared() < 0.0f) {
      //    // 点と点の距離を算出する
      //    return (_start - line._start).LengthSquared();
      //  }
      //  // 線分と点の最短距離(二乗)を返す
      //  return line.MinDistSq(_start);
      //}
      //// 対象の線分が縮退しているか
      //else if (line.LengthSquared() < 0.0f) {
      //  return MinDistSq(line._start);
      //}
      //// 線分同士が平行な場合
      //if (Vector4::IsParallel(_start, line._start)) {

      //}
    }
  }
}