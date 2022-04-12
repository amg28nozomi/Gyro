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
#include "SpawnBase.h"
#include "UtilityDX.h"

namespace {
  constexpr auto MaxGravity = -50.0f;
} // namespace

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

    void ObjectBase::Set(SpawnBase& spawn) {
      // �e��p�����[�^�̎擾
      auto [position, rotation, scale] = spawn.GetTransform();
      // ���W�E�����E�X�P�[���̐ݒ�
      _position = position;
      _rotation = rotation;
      _scale = scale;
    }

    void ObjectBase::Gravity() {
      // �O���r�e�B�X�P�[���̍X�V
      GravityScale();
      // �����t���O�̍X�V
      _isStand = IsStand();
      // �n�`�Ƃ̏Փ˔���
      if (_isStand) {
        GravityReset(); // �d�̓X�P�[���̏�����
      }
    }

    void ObjectBase::GravityScale() {
      // �f�t�H���g�̏d�͉����x���d�̓X�P�[���ɉ��Z����
      using Gravity = AppFrame::Math::GravityBase;
      if (MaxGravity < _gravityScale) {
        _gravityScale += Gravity::Acceleration();
        if (_gravityScale <= MaxGravity) {
          _gravityScale = MaxGravity; // �����𒴉߂����ꍇ�͏C��
        }
      }
    }

    bool ObjectBase::IsStand() {
      return true;
    }

    void ObjectBase::GravityReset() {
      // �d�̓X�P�[��������������
      _gravityScale = 0.0f;
    }

    void ObjectBase::WorldMatrix(bool angle) {
      using Utility = AppMath::Utility;
      // ���[���h���W�ϊ����s��
#ifndef _DEBUG
      _world = Utility::ToWorldMatrix(_position, _rotation, _scale);
#else
      _world = Utility::ToWorldMatrix(_position, _rotation, _scale, angle);
#endif
    }

#ifdef _DEBUG
    bool ObjectBase::DebugDraw() const {
      return _app.GetDebugFlag();
    }
#endif
  } // namespace Object
} // namespace Gyro