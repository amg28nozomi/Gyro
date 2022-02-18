/*****************************************************************//**
 * @file   StageBase.cpp
 * @brief  �X�e�[�W�̃X�[�p�[�N���X�̒�`
 * 
 * @author �y������
 * @date   February 2022
 *********************************************************************/
#include "StageBase.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "SpawnBase.h"

namespace Gyro {
  namespace Object {

    StageBase::StageBase(Application::ApplicationMain& app) : _app(app) {
    }

    bool StageBase::Init() {
      // ���\�[�X�̉��
      _model.clear();
      return true;
    }

    bool StageBase::Process() {
      return true;
    }

    bool StageBase::Draw() const {
      return true;
    }

    void StageBase::Set(SpawnBase& spawn) {
      // �e��p�����[�^�̎擾
      auto [position, rotation, scale] = spawn.GetTransform();
      // ���W�E�����E�X�P�[���̐ݒ�
      _position = position;
      _rotation = rotation;
      _scale = scale;
    }
  }
}
