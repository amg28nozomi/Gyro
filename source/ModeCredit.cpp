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
      // �ϐ�������
      _backTitle = false;
      return true;
    }

    bool ModeCredit::Exit() {
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
      DrawExtendGraph(0, 0, 1920, 1080, _creditHandle, false);
      return true;
    }

    void ModeCredit::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }


      //// �N���W�b�g�摜�ǂݍ���
      //_creditHandle = _app.GetResourceServer().LoadDivGraph()
      //  LoadGraph("res/Credit/Credit.png");
      //// �ǂݍ��݊���
      //_isLoad = true;
    }

    void ModeCredit::ChangeMode() {
      // ���[�h�N���W�b�g�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���[�h�^�C�g���J��
      _appMain.GetModeServer().TransionToMode("Title");
    }
  } // namespace Mode
} // namespace Gyro