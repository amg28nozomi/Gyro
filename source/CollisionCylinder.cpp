/*****************************************************************//**
 * @file   CollisionCylinder.cpp
 * @brief  �~���̓����蔻��N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "CollisionCylinder.h"
#include <DxLib.h>
#include "UtilityDX.h"
#include "ObjectBase.h"

namespace Gyro {

  namespace Object {

    CollisionCylinder::CollisionCylinder(ObjectBase& owner) : _owner(owner), _position(), _radius(), _line() {
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
      // �~�̍��W���X�V����

    }

    void CollisionCylinder::Draw() {
#ifdef _DEBUG
      // �x�N�g���̎擾
      auto [start, end] = _line.GetVector();
      // �n�_�E�I�_
      auto sVector = UtilityDX::ToVECTOR(start);
      auto eVector = UtilityDX::ToVECTOR(end);
      // �������ɃX�t�B�A�̕`����s��
      DrawCapsule3D(sVector, eVector, _radius * 2, 10, 0, 0, TRUE);
      // ������`�悷��
      DrawLine3D(sVector, eVector, _color.GetColorCode());
#endif
    }
  } // namespace Object
} // namespace Gyro