/*****************************************************************//**
 * @file   PrimitiveBase.cpp
 * @brief  プリミティブのスーパークラスの定義
 * 
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#include "PrimitiveBase.h"

namespace {
  constexpr auto DEGREE_TO_RADIAN = DX_PI_F / 180.0f;
  MATRIX Identity = MGetIdent();
}

namespace Gyro {
  namespace Primitive {

    PrimitiveBase::PrimitiveBase() {
      _handle = -1;
      _vertexNum = 0;
      _indexNum = 0;
      _polygonNum = 0;

      _vertex.reset(new std::vector<VERTEX3D>());
      _index.reset(new std::vector<unsigned short>());
    }

    PrimitiveBase::~PrimitiveBase() {
      _vertex->clear();
      _index->clear();
    }

    bool PrimitiveBase::Load(const TCHAR* fileName) {
      UnLoad();

      _handle = LoadGraph(fileName);

      return (-1 != _handle);
    }

    bool PrimitiveBase::UnLoad() {
      if (-1 == _handle) {
          return false;
      }

      return (-1 != DeleteGraph(_handle));
    }

    void PrimitiveBase::Process() {
      _vertexNum = static_cast<int>(_vertex->size());
      _indexNum = static_cast<int>(_index->size());
      _polygonNum = _indexNum / 3;
    }

    bool PrimitiveBase::Draw() const {
      auto vertexNum = static_cast<int>(_vertex->size());
      auto indexNum = static_cast<int>(_index->size());

      // ポリゴンが１つも無ければ描画しない
      if (3 > _vertexNum || 3 > _indexNum) {
          return false;
      }

      auto _polygonNum = _indexNum / 3;
      auto useHandle = (_handle == -1) ? DX_NONE_GRAPH : _handle;

      DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, useHandle, FALSE);

      return true;
    }
  } // namespace Primitive
} // namespace Gyro
