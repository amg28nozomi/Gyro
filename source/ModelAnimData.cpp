/*****************************************************************//**
 * @file   ModelAnimData.cpp
 * @brief  アニメーション情報クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "ModelAnimData.h"

namespace Gyro {
  namespace ModelAnim {

    ModelAnimData::ModelAnimData() {
      // 各種パラメータの初期化
      _name.clear();
      _effect.clear();
      _blendFrame = 0.0f;
      _speed = 0.0f;
      _loop = false;
    }

    ModelAnimData::ModelAnimData(std::string_view name, const float frame, const float speed, bool loop, std::string_view effect) {
      // 各種パラメータの設定
      _name = name.data();
      _effect = effect.data();
      _blendFrame = frame;
      _speed = speed;
      _loop = loop;
    }
  } // namespace ModelAnim
} // namespace Gyro