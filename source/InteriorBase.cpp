/*****************************************************************//**
 * @file   InteriorBase.cpp
 * @brief  �C���e�����̊��N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "InteriorBase.h"
#include "ApplicationMain.h"
#include "SpawnBase.h"

namespace Gyro {
  namespace Interior {

    InteriorBase::InteriorBase(Application::ApplicationMain& app) : ObjectBase(app) {
    }

    bool InteriorBase::Init() {
      return true;
    }

    bool InteriorBase::Process() {
      // �X�V����
      return true;
    }

    bool InteriorBase::Draw() const {
#ifdef _DEBUG
      // �f�o�b�O�t���O�������Ă���ꍇ�͕`����s��
      if (_app.GetDebugFlag()) {
        _collision->Draw();
      }
#endif
      return true;
    }

    void InteriorBase::Set(Object::SpawnBase& spawn) {
      // �X�|�[��������ɐݒ���s��
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
    }
  } // namespace Interior
} // namespace Gyro