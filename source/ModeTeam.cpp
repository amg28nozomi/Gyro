/*****************************************************************//**
 * @file    ModeTeam.cpp
 * @brief   ���[�h�`�[���N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeTeam.h"
#include "ModeTitle.h"

namespace {
  // �e��萔
  constexpr int MaxCount = 60;  //!< ���[�h�ő�J�E���g
}

namespace Gyro {
  namespace Mode {
    ModeTeam::ModeTeam(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeTeam::~ModeTeam() {

    }

    bool ModeTeam::Init() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      return true;
    }

    bool ModeTeam::Process() {
      _count++;  // �J�E���g�𑝂₷
      // ���[�h�ő�J�E���g���߂�����
      if (MaxCount < _count) {
        // ���[�h�؂�ւ�
        ChangeMode();
      }
      return true;
    }

    bool ModeTeam::Draw() const {
      // �`�[���`��
      //DrawGraph(0, 0, _teamHandle, false);
      return true;
    }

    void ModeTeam::LoadResource() {
      // �`�[���ǂݍ���
      //_teamHandle = LoadGraph("res/Logo/.png");
    }

    void ModeTeam::ChangeMode() {
      // ���[�h�`�[���̍폜
      _appMain.GetModeServer().PopBuck();
      // ���[�h�^�C�g���̓o�^
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      _appMain.GetModeServer().TransionToMode("Title");
    }
  }
}