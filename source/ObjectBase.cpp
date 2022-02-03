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
      if (-50.0f < _gravityScale) {
        _gravityScale += Gravity::Acceleration();
        if (_gravityScale <= -50.0f) {
          _gravityScale = -50.0f; // �����𒴉߂����ꍇ�͏C��
        }
      }
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
      using Utility = AppMath::Utility;
      // ���[���h���W�ϊ����s��
#ifndef _DEBUG
      _world = Utility::ToWorldMatrix(_position, _rotation, _scale);
#else
      _world = Utility::ToWorldMatrix(_position, _rotation, _scale, AppMath::Degree);
#endif
      
    }

#ifdef _DEBUG
    bool ObjectBase::DebugDraw() const {
      return _app.GetDebugFlag();
    }
#endif
  } // namespace Object
} // namespace Gyro