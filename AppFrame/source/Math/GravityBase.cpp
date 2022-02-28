/*****************************************************************//**
 * @file   GravityBase.cpp
 * @brief  重力処理を行う静的クラスの定義
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "GravityBase.h"
#include "Matrix44.h"
#include "Vector4.h"

namespace AppFrame{
  namespace Math {

    float GravityBase::GravityScale(float speed, float mass) {
      // 質量がマイナスかどうかの判定
      if(mass <= 0.0f) {
        // マイナスの場合は質量を0にする
        mass = 0.0f;
      }
      // 重力スケールを返す
      return speed + (_acceleration * mass);
    }
  }
}