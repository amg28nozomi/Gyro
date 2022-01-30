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

    void ObjectBase::Gravity() {
      using Gravitys = AppFrame::Math::GravityBase;
      // �d�̓X�P�[���̍X�V
      // _gravityScale = Gravitys::GravityScale(_gravityScale, _mass);
      // ���ɐڐG���Ă��邩������s��

      // �ڐG���Ă���ꍇ�͉����o�����������s
      // _gravityScale��0.0f�ŏ�����
    }

    AppMath::Matrix44 ObjectBase::WorldMatrix() {
      using Matrix = AppMath::Matrix44;
      auto world = Matrix::Identity(); // �P�ʍs��̎擾
      world.MulScaling(_scale);        // �g�k
      using Utility = AppMath::Utility;
      world.RotateZ(_rotation.GetZ()); // z����]
      world.RotateY(_rotation.GetY()); // y����]
      world.RotateX(_rotation.GetX()); // x����]
      world.MulTranslate(_position);   // ���s�ړ�
      return world; // �s���Ԃ�
    }

#ifdef _DEBUG
    bool ObjectBase::DebugDraw() const {
      return _app.GetDebugFlag();
    }
#endif
  } // namespace Object
} // namespace Gyro