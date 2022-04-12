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
      _vertex.reset(new std::vector<VERTEX3D>());
      _index.reset(new std::vector<unsigned short>());
    }

    PrimitiveBase::~PrimitiveBase() {
      ReleaseGraph();
      _vertex->clear();
      _index->clear();
    }

    bool PrimitiveBase::Load(const TCHAR* fileName) {
      UnLoad();

      _handle = LoadGraph("res/Primitive/コンポ 1 (00000)_1.png");
      //_handle = LoadGraph("res/Primitive/コンポ 1 (00000).png");
      //_handle2 = LoadGraph("res/Primitive/コンポ 1 (00010).png");
      //_handle3 = LoadGraph("res/Primitive/コンポ 1 (00020).png");
      //_handle4 = LoadGraph("res/Primitive/コンポ 1 (00030).png");
      //_handle5 = LoadGraph("res/Primitive/コンポ 1 (00040).png");
      //_handle6 = LoadGraph("res/Primitive/コンポ 1 (00050).png");
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
      _cnt++;
      if (_cnt > _interval * 6) {
        _cnt = 0;
      }
    }

    bool PrimitiveBase::Draw() const {
      auto vertexNum = static_cast<int>(_vertex->size());
      auto indexNum = static_cast<int>(_index->size());

      // ポリゴンが１つも無ければ描画しない
      if (3 > _vertexNum || 3 > _indexNum) {
          return false;
      }

      auto _polygonNum = _indexNum / 3;

      DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle, FALSE);
      /*if (_cnt < _interval) {
        DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle, FALSE);
      }else if (_cnt < _interval * 2) {
        DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle2, FALSE);
      }else if (_cnt < _interval * 3) {
        DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle3, FALSE);
      }else if (_cnt < _interval * 4) {
        DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle4, FALSE);
      }else if (_cnt < _interval * 5) {
        DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle5, FALSE);
      }else if (_cnt <= _interval * 6) {
        DrawPolygonIndexed3D(_vertex->data(), _vertexNum, _index->data(), _polygonNum, _handle6, FALSE);
      }*/
      return true;
    }

    void PrimitiveBase::ReleaseGraph() {
      // 画像の解放
      DeleteGraph(_handle);
      DeleteGraph(_handle2);
      DeleteGraph(_handle3);
      DeleteGraph(_handle4);
      DeleteGraph(_handle5);
      DeleteGraph(_handle6);
    }
  } // namespace Primitive
} // namespace Gyro
