/*****************************************************************//**
 * @file   StageTransition.cpp
 * @brief  �X�e�[�W�J�ڂ��Ǘ�����}�l�[�W���[�N���X�̒�`
 *
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "StageTransition.h"
#include "ApplicationMain.h"

namespace Gyro {
  /**
   * @brief
   */
  namespace Stage {

    StageTransition::StageTransition(Application::ApplicationMain& app) : _app(app) {
      // �X�e�[�W�J�ڏ��̐ݒ�
      _stageType = StageType::Null;
      // �f�[�^�x�[�X�̍폜
      _registry.clear();
    }

    bool StageTransition::Register(const StageType& stage, std::string_view key) {
      // �f�[�^�x�[�X�ɓo�^����Ă��邩
      if (_registry.contains(stage)) {
        return false; // �L�[�͓o�^�ς�
      }
      // ���o�^�̏ꍇ�̓X�e�[�W�L�[���Z�b�g����
      _registry.emplace(stage, key.data());
      return true; // �o�^����
    }

    std::string StageTransition::StageKey() const {
      // �X�e�[�W�L�[�͓o�^����Ă��邩
      if (!_registry.contains(_stageType)) {
        return "";
      }
      // �Ή�����X�e�[�W�L�[��Ԃ�
      return _registry.at(_stageType);
    }

    bool StageTransition::Transition() {
      return true;
    }
  } // namespace Stage
} // namespace Gyro