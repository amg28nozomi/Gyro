/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  �I�u�W�F�N�g�̃X�[�p�[�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ObjectBase.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "ModeGame.h"

namespace Gyro {
  namespace Object {

    ObjectBase::ObjectBase(Application::ApplicationMain& app) : _app(app) {
      _gravity = false;
      _mass = 0.0f;
      _world = AppMath::Matrix44::Identity();
    }

    bool ObjectBase::Init() {
      return true;
    }

    bool ObjectBase::Process() {
      // �d�͉e���t���O��true�̏ꍇ�d�͏������s��
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
      GravityScale(); // �O���r�e�B�X�P�[���̍X�V
      // �n�`�Ƃ̏Փ˔���
      if (IsStand()) {
        GravityReset(); // �d�̓X�P�[���̏�����
      }
    }

    void ObjectBase::GravityScale() {
      // �f�t�H���g�̏d�͉����x���d�̓X�P�[���ɉ��Z����
      using Gravity = AppFrame::Math::GravityBase;
      _gravityScale += Gravity::Acceleration();
    }

    bool ObjectBase::IsStand() {
      return true;
    }

    void ObjectBase::GravityReset() {
      // �d�̓X�P�[��������������
      _gravity = 0.0f;
      // �����ƃX�e�[�W�̉����o���������s��
    }

    void ObjectBase::WorldMatrix() {
      // ���[���h���W�ϊ����s��
      _world = AppMath::Utility::ToWorldMatrix(_position, _rotation, _scale);
    }

#ifdef _DEBUG
    bool ObjectBase::DebugDraw() const {
      return _app.GetDebugFlag();
    }
#endif
  } // namespace Object
} // namespace Gyro