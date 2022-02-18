/*****************************************************************//**
 * @file   PrimitivePlane.cpp
 * @brief  プリミティブベースのサブクラス
 * 
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#include <array>
#include "PrimitivePlane.h"

namespace {
  constexpr auto DEFAULT_SIZE = 100.0;
  constexpr auto DEFAULT_DIVISION_NUM = 10;
  constexpr auto DEGREE_TO_RADIAN = DX_PI_F / 180.0f;
  constexpr COLOR_U8 DEFAULT_DIFFUSE = { 255, 255, 255, 255 };
  constexpr COLOR_U8 DEFAULT_SPECULAR = { 0, 0, 0, 0 };
  constexpr VECTOR DEFAULT_NORMAL = { 0.0f, 1.0f, 0.0f };
}

namespace Gyro {
  namespace Primitive {

    // 何も指定しない場合デフォルト値が入る
    Plane::Plane() : PrimitiveBase() {
      _size = DEFAULT_SIZE;
      _divisionNum = DEFAULT_DIVISION_NUM;
    }

    // newしたとき値をそのまま指定できる
    Plane::Plane(double size, int divisionNum) : PrimitiveBase() {
      _size = size;
      _divisionNum = divisionNum;
    }

    bool Plane::Initialize(double size, int divisionNum) {
      _size = size;
      _divisionNum = divisionNum;

      return true;
    }

    bool Plane::Create() {
      auto divisionNumD = static_cast<double>(_divisionNum);
      auto polygonSize = _size / divisionNumD;
      // 地面全体の中心を原点にするオフセット
      auto halfPolygonSize = polygonSize * 0.5f;
      auto startX = -halfPolygonSize * divisionNumD;
      auto startZ = -halfPolygonSize * divisionNumD;
      // 地面の基本の正方形テーブル
      VECTOR position0 = { 0.0f, 0.0f, 0.0f };
      VECTOR position1 = { 0.0f, 0.0f, polygonSize };
      VECTOR position2 = { polygonSize, 0.0f, 0.0f };
      VECTOR position3 = { polygonSize, 0.0f, polygonSize };
      std::array<VECTOR, 4> positionList = {
          position0, position1, position2, position3
      };
      // uvテーブル
      constexpr std::array<float, 4> uList = { 0.0f, 0.0f, 1.0f, 1.0f };
      constexpr std::array<float, 4> vList = { 0.0f, 1.0f, 0.0f, 1.0f };

      auto offsetX = startX;
      auto offsetZ = startZ;
      unsigned short offsetIndex = 0;

      for (auto z = 0; z < _divisionNum; ++z) {
        offsetX = startX;

        for (auto x = 0; x < _divisionNum; ++x) {
          // 正方形を形成する
          for (auto i = 0; i < 4; ++i) {
            VERTEX3D vertex;

            VECTOR base = positionList[i];

            base.x += offsetX;
            base.z += offsetZ;

            vertex.pos = base;
            vertex.norm = DEFAULT_NORMAL;
            vertex.dif = DEFAULT_DIFFUSE;
            vertex.spc = DEFAULT_SPECULAR;
            vertex.u = uList[i];
            vertex.v = vList[i];

            _vertex->push_back(vertex);
          }

          // 1つめの三角形
          _index->push_back(offsetIndex);
          _index->push_back(offsetIndex + 1);
          _index->push_back(offsetIndex + 2);

          // 2つめの三角形
          _index->push_back(offsetIndex + 2);
          _index->push_back(offsetIndex + 1);
          _index->push_back(offsetIndex + 3);

          offsetIndex += 4;

          offsetX += polygonSize;
        }

        offsetZ += polygonSize;
      }

      return true;
    }
  } // namespace Primitive
} // namespace Gyro
