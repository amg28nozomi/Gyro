/*****************************************************************//**
 * @file   CollisionCylinder.cpp
 * @brief  �~���̓����蔻��N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "CollisionCylinder.h"
#include <appframe.h>
#include <DxLib.h>

namespace Gyro {

  namespace Object {

    CollisionCylinder::CollisionCylinder() : _position(), _radius(), _line() {
#ifdef _DEBUG
      _color = AppData::Color();
#endif
    }

    CollisionCylinder::CollisionCylinder(AppMath::Vector4 pos, float radius, AppMath::Line line) {
      _position = pos;
      _radius = radius;
      _line = line;
#ifdef _DEBUG
      _color = AppData::Color();
#endif
    }

    void CollisionCylinder::Process(AppMath::Vector4 pos) {
      // ���W���X�V����
      _position = pos;
    }

    void CollisionCylinder::Draw() {
#ifdef _DEBUG
      
      auto [start, end] = _line.GetVector();
      // �n�_�E�I�_
      VECTOR sVector(start.GetX(), start.GetY(), start.GetZ());
      VECTOR eVector(end.GetX(), end.GetY(), end.GetZ());
      // �������ɕ`����s��
      DrawCapsule3D();
#endif
    }
  } // namespace Object
} // namespace Gyro