/*****************************************************************//**
 * @file   ObjectComponent.cpp
 * @brief  オブジェクト用機能のスーパークラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "ObjectComponent.h"

namespace Gyro {
  namespace Object {

    ObjectComponent::ObjectComponent() {
      _type = ComponentType::None;
    }
  } // namespace Player
} // namespace Gyro