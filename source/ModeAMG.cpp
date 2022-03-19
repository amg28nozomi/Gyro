/*****************************************************************//**
 * @file    ModeAMG.cpp
 * @brief   ���[�hAMG�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeAMG.h"
#include "ModeTitle.h"
#include "StageComponent.h"
#include "StageTransition.h"

namespace {
  // �e��萔
  constexpr int MaxCount = 30;  //!< ���[�h�ő�J�E���g
}

namespace Gyro {
  namespace Mode {
    ModeAMG::ModeAMG(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeAMG::~ModeAMG() {

    }

    bool ModeAMG::Init() {
      // �ʖ���`
      using StageType = Stage::StageTransition::StageType;
      // �X�e�[�W���X�g�̐���
      const std::unordered_map<StageType, std::string_view> stageMap = {
        {StageType::Normal, "stage"},
        {StageType::Boss, "boss"},
      };
      // �����������X�g��o�^����
      _appMain.GetStageTransition().Register(stageMap);
      return true;
    }

    bool ModeAMG::Enter() {
      // ���\�[�X�ǂݍ���
      _appMain.GetStageTransition().ChangeReserve(Stage::StageTransition::StageType::Normal);
      LoadResource();
      return true;
    }

    bool ModeAMG::Exit() {
      // �ϐ����
      Release();
      return true;
    }

    bool ModeAMG::Process() {
      _count++;  // �J�E���g�𑝂₷
      // ���[�h�ő�J�E���g���߂�����
      if (MaxCount < _count) {
        // ���[�h�؂�ւ�
        ChangeMode();
      }
      return true;
    }

    bool ModeAMG::Draw() const {
      // AMG�`��
      DrawGraph(0, 0, _amgHandle, false);
      return true;
    }

    void ModeAMG::Release() {
      // �ϐ����
      _amgHandle = -1;
    }

    void ModeAMG::LoadResource() {
      // AMG�ǂݍ���
      _amgHandle = LoadGraph("res/Logo/amglogo.png");
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �񓯊������t���Otrue
      SetUseASyncLoadFlag(true);
      // �ʏ�X�e�[�W�̓ǂݍ��݊J�n
      _appMain.GetStageTransition().IsTransition();
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeAMG::ChangeMode() {
      // ���[�hAMG�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���o�^�̂��߃��[�h�`�[���̓o�^
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      // ���[�h�`�[���J��
      _appMain.GetModeServer().TransionToMode("Title");
    }
  } // namespace Mode
} // namespace Gyro