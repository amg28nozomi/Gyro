/*****************************************************************//**
 * @file    ModePause.cpp
 * @brief   ���[�h�|�[�Y�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModePause.h"

namespace Gyro {
  namespace Mode {
    ModePause::ModePause(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModePause::~ModePause() {

    }

    bool ModePause::Init() {
      return true;
    }

    bool ModePause::Enter() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      // �ϐ�������
      _continue = 0;
      _quitGame = 0;
      _decision = false;
      return true;
    }

    bool ModePause::Exit() {
      return true;
    }

    bool ModePause::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // ���X�e�B�b�N����
      if (leftY > 100) {
        _continue = 1;
        _quitGame = 0;
      }
      else if (leftY < -100) {
        _continue = 0;
        _quitGame = 1;
      }
      // A�{�^���������ꂽ�ꍇ�A�I������
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
      }
      return true;
    }

    bool ModePause::Process() {
      // ���͏���
      Input(_appMain.GetOperation());
      // �I�����肳�ꂽ
      if (_decision) {
        // ���[�h�؂�ւ�
        ChangeMode();
      }
      return true;
    }

    bool ModePause::Draw() const {
      // �|�[�Y�`��
      DrawGraph(0, 0, _pauseHandle, true);
      // �I���ɂ���ĕ`��؂�ւ�
      DrawGraph(0, 0, _continueHandle[_continue], true);
      DrawGraph(0, 0, _quitGameHandle[_quitGame], true);
      return true;
    }

    void ModePause::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �摜�ǂݍ���
      _pauseHandle = LoadGraph("res/Pause/pause.png");
      _continueHandle[0] = LoadGraph("res/Pause/continue0.png");
      _continueHandle[1] = LoadGraph("res/Pause/continue1.png");
      _quitGameHandle[0] = LoadGraph("res/Pause/quitgame0.png");
      _quitGameHandle[1] = LoadGraph("res/Pause/quitgame1.png");
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModePause::ChangeMode() {
      // ���[�h�|�[�Y�̍폜
      _appMain.GetModeServer().PopBuck();
      // �Q�[���I���I����
      if (_quitGame == 1) {
        // �A�v���P�[�V�����̏I���������Ăяo��
        _appMain.RequestTerminate();
      }
    }
  }
}