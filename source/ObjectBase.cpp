/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  �I�u�W�F�N�g�̃X�[�p�[�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ObjectBase.h"
#include "appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

namespace Gyro {
  namespace Object {

    ObjectBase::ObjectBase(Application::ApplicationMain& app) : _app(app) {
      _gravity = false;
      _mass = 0.0f;
      _position;
      _rotation;
      _scale = AppFrame::Math::Vector4(1.0f, 1.0f, 1.0f);
      _world = AppFrame::Math::Matrix44::Identity();
    }

    bool ObjectBase::Init() {
      return true;
    }

    bool ObjectBase::Process() {
      // �d�͏������s�����̔���
      if (_gravity) {
        Gravity(); // �d�͏������s
      }
      return true;
    }

    bool ObjectBase::Draw() const {
      // ���f���̕`����s��
      return true;
    }

    bool ObjectBase::WorldMatrixUpdate() {
      namespace AppMath = AppFrame::Math;
      // ���[���h���W�ϊ�
      _world.MulScaling(_scale);        // �g��k��
      _world.RotateZ(_rotation.GetZ()); // z����]
      _world.RotateY(_rotation.GetY()); // y����]
      _world.RotateX(_rotation.GetX()); // x����]
      _world.MulTranslate(_position);   // ���s�ړ�
    }

    void ObjectBase::Gravity() {
      using Gravitys = AppFrame::Math::GravityBase;
      // �d�̓X�P�[���̍X�V
      // _gravityScale = Gravitys::GravityScale(_gravityScale, _mass);
      // ���ɐڐG���Ă��邩������s��

      // �ڐG���Ă���ꍇ�͉����o�����������s
      // _gravityScale��0.0f�ŏ�����
    }
  } // namespace Object
} // namespace Gyro