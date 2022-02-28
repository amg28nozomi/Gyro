/*****************************************************************//**
 * @file   LineSegment.cpp
 * @brief  線分クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "LineSegment.h"
#include "Vector4.h"

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

    float LineSegment::MinDistSq(const LineSegment& line) const {
      // 線分は縮退しているか
      if (LengthSquared() < 0.0f) {
        // 対象の線分は縮退しているか
        if (line.LengthSquared() < 0.0f) {
          // 点と点の距離を算出する
          return (_start - line._start).LengthSquared();
        }
        // 線分と点の最短距離(二乗)を返す
        return line.MinDistSq(_start);
      }
      // 対象の線分が縮退しているか
      else if (line.LengthSquared() < 0.0f) {
        return MinDistSq(line._start);
      }
      // 線分同士が平行な場合
      if (Vector4::IsParallel(_start, line._start)) {

      }
    }
  }
}