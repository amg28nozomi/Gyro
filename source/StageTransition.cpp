/*****************************************************************//**
 * @file   StageTransition.cpp
 * @brief  �X�e�[�W�J�ڂ��Ǘ�����}�l�[�W���[�N���X�̒�`
 *
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "StageTransition.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "StageComponent.h"

namespace Gyro {
  /**
   * @brief
   */
  namespace Stage {

    StageTransition::StageTransition(Application::ApplicationMain& app) : _app(app) {
      Init();
    }

    void StageTransition::Init(const bool haveData) {
      // �e��f�[�^�̏�����
      _stageType = StageType::Null;
      _reserveType = StageType::Null;
      _transition = false;
      // �f�[�^��ێ�����ꍇ�͏������s��Ȃ�
      if (haveData) {
        return;
      }
      // �f�[�^�x�[�X���������
      _registry.clear();
    }

    bool StageTransition::Register(const std::unordered_map<StageType, std::string_view> stageMap) {
      // �f�[�^�͓o�^����Ă��邩
      if (stageMap.empty()) {
        return false; // ���o�^
      }
      // �o�^���s�񐔌v���p
      auto count = 0;
      // �f�[�^�x�[�X��ɓo�^����
      for (auto [stageType, stageKey] : stageMap) {
#ifndef _DEBUG
        Register(stageType, stageKey);
#else
        // �o�^������ɏI�������ꍇ�͎���
        if (Register(stageType, stageKey)) {
          continue;
        }
        // ���s�����ꍇ�̓J�E���g����
        ++count;
#endif
      }
#ifdef _DEBUG
      // �o�^�Ɏ��s�����ꍇ�̓��O�ɏo�͂���
      if (count) {
        OutputDebugString(("StageTransition:" + std::to_string(count) + "��o�^�Ɏ��s���܂���\n").data());
      }
#endif
      return true;
    }

    bool StageTransition::Register(const StageType& stage, std::string_view key) {
      // �f�[�^�x�[�X�ɓo�^����Ă��邩
      if (_registry.contains(stage)) {
        return false; // �L�[�͓o�^�ς�
      }
      // �X�e�[�W�^�C�v��NULL���̔���
      if (StageNull(stage)) {
        return false; // �^�C�v��NULL
      }
      // ���o�^�̏ꍇ�̓X�e�[�W�L�[���Z�b�g����
      _registry.emplace(stage, key.data());
      return true; // �o�^����
    }

    bool StageTransition::ChangeReserve(const StageType& stage) {
      // ���ɑJ�ڗ\�񂪍s���Ă���ꍇ�͒��f
      if (!StageNull(_reserveType)) {
        return false;
      }
      // �L�[���擾
      const auto key = StageKey(stage);
      // �L�[�͓o�^����Ă��邩
      if (key.empty()) {
        return false; // �L�[�����o�^
      }
      // �X�e�[�W�^�C�v���󂩂̔���
      if (StageNull(stage)) {
        return false;
      }
      // ���݂̃X�e�[�W�Ɠ������̔���
      if (!StageDifferent(stage)) {
        return false; // �L�[���d�����Ă���
      }
      // �J�ڗ\����s��
      _transition = true;
      _reserveType = stage;
      return true;
    }

    bool StageTransition::ChangeStage(const StageType& stage) {
      // �L�[���擾
      const auto key = StageKey(stage);
      // �L�[�͓o�^����Ă��邩
      if (key.empty()) {
        return false; // �L�[�����o�^
      }
      // �X�e�[�W�^�C�v���󂩂̔���
      if (StageNull(stage)) {
        return false;
      }
      // �X�e�[�W���̍폜
      _app.GetStageComponent().ReleaseStageInfo();
      // �X�e�[�W�̓ǂݍ���
      _app.GetStageComponent().Init(key);
      // �X�e�[�W�L�[�̐؂�ւ�
      _stageType = stage;
      return true;
    }

    bool StageTransition::IsTransition() {
      // �X�e�[�W�J�ڃt���O�͗����Ă��邩
      if (!_transition) {
        return false; // �t���O�͗����Ă��Ȃ�
      }
      // �t�F�[�h�A�E�g���I�������ꍇ
      if (!_app.GetModeServer().IsFadeOutEnd()) {
        return false; // �������I�����Ă��Ȃ�
      }
      // �X�e�[�W�J�ڂ��s��
      return Transition();
    }

    std::string StageTransition::GetStageKey() const {
      // ���݂̃X�e�[�W�ɑΉ������L�[��Ԃ�
      return StageKey(_stageType);
    }

    bool StageTransition::Transition() {
      // �O�X�e�[�W�̏����폜����
      _app.GetStageComponent().ReleaseStageInfo();
      // �X�e�[�W�R���|�[�l���g�̏��������s��
      _app.GetStageComponent().Init(StageKey(_reserveType));
      // ���݂̃L�[���X�V
      _stageType = _reserveType;
      _reserveType = StageType::Null;
      // �J�ڃt���O���I�t�ɂ���
      _transition = false;
      return true;
    }

    std::string StageTransition::StageKey(const StageType& stage) const {
      // �X�e�[�W�L�[�͓o�^����Ă��邩
      if (!_registry.contains(stage)) {
        return ""; // ���o�^
      }
      // �Ή�����X�e�[�W�L�[��Ԃ�
      return _registry.at(stage);
    }
  } // namespace Stage
} // namespace Gyro