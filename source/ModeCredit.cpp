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
      // �폜�\�񏉊���
      _popBack = false;
      return true;
    }

    bool ModeCredit::Exit() {
      // �ϐ����
      _backTitle = false;
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

    void ModeCredit::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �ʖ���`
      using ResourceServer = AppFrame::Resource::ResourceServer;
      // �摜���̐ݒ�
      const ResourceServer::DivGraphTable divGraphMap{
        {"Credit", {"res/Credit/Credit.png", 1, 1, 1, 1920, 1080}}  // �N���W�b�g
      };
      // ���\�[�X�T�[�o�ɓo�^
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // �摜�ǂݍ���
      _creditHandle = _appMain.GetResourceServer().GetHandle("Credit");
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeCredit::ChangeMode() {
      // ���[�h�^�C�g���J��
      _appMain.GetModeServer().TransionToMode("Title");
      // �����\��
      _popBack = true;
      // ���̉�SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround("bell", 75);
    }
  } // namespace Mode
} // namespace Gyro