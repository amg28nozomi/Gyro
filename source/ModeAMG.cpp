/*****************************************************************//**
 * @file    ModeAMG.cpp
 * @brief   ���[�hAMG�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeAMG.h"
#include "ModeTeam.h"

namespace {
  // �e��萔
  constexpr int MaxCount = 60;  //!< ���[�h�ő�J�E���g
}

namespace Gyro {
  namespace Mode {
    ModeAMG::ModeAMG(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeAMG::~ModeAMG() {

    }

    bool ModeAMG::Init() {
      // ���\�[�X�ǂݍ���
      LoadResource();
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
      // AMG�ǂݍ���
      _amgHandle = LoadGraph("res/Logo/amglogo.png");
    }

    void ModeAMG::ChangeMode() {
      // ���[�hAMG�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���[�h�`�[���̓o�^
      _appMain.GetModeServer().AddMode("Team", std::make_shared<Mode::ModeTeam>(_appMain));
      _appMain.GetModeServer().TransionToMode("Team");
    }
  }
}