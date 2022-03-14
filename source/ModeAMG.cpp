/*****************************************************************//**
 * @file    ModeAMG.cpp
 * @brief   ���[�hAMG�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeAMG.h"
#include <appframe.h>
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

    void ModeAMG::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      const AppFrame::Data::DivGraph divGraph("res/Logo/amglogo.png", 1, 1, 1, 1920, 1080);
      // AMG�ǂݍ���
      _app.GetResourceServer().LoadDivGraph("amglogo", divGraph);
      // �n���h���̐ݒ�
      _amgHandle = _app.GetResourceServer().GetHandle("amglogo");
      // �ǂݍ��݊���
      _isLoad = true;
      // �񓯊������t���Otrue
      SetUseASyncLoadFlag(true);
      // �ʏ�X�e�[�W�̓ǂݍ��݊J�n
      _appMain.GetStageTransition().IsTransition();
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