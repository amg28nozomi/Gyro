/*****************************************************************//**
 * @file    ModeCredit.cpp
 * @brief   ���[�h�N���W�b�g�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeCredit.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeCredit::ModeCredit(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeCredit::~ModeCredit() {

    }

    bool ModeCredit::Init() {
      return true;
    }

    bool ModeCredit::Enter() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      return true;
    }

    bool ModeCredit::Exit() {
      // �ϐ����
      Release();
      return true;
    }

    bool ModeCredit::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // B�{�^���������ꂽ�ꍇ�A�^�C�g���o�b�N
      if (device.GetButton(XINPUT_BUTTON_B, App::InputTrigger)) {
        _backTitle = true;
      }
      return true;
    }

    bool ModeCredit::Process() {
      // ���͏���
      Input(_appMain.GetOperation());
      // �^�C�g���o�b�N���ꂽ
      if (_backTitle) {
        // ���[�h�؂�ւ�
        ChangeMode();
      }
      return true;
    }

    bool ModeCredit::Draw() const {
      // �N���W�b�g�摜�`��
      DrawGraph(0, 0, _creditHandle, false);
      return true;
    }

    void ModeCredit::Release() {
      // �ϐ����
      _creditHandle = -1;
      _backTitle = false;
    }

    void ModeCredit::LoadResource() {
      // �N���W�b�g�摜�ǂݍ���
      _creditHandle = LoadGraph("res/Credit/Credit.png");
    }

    void ModeCredit::ChangeMode() {
      // ���[�h�N���W�b�g�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���[�h�^�C�g���J��
      _appMain.GetModeServer().TransionToMode("Title");
      // ���̉�SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround("bell");
    }
  } // namespace Mode
} // namespace Gyro