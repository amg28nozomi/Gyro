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
      // �摜�؂�ւ��ԍ��̏�����
      _continue = 0;
      _quitGame = 0;
      // �|�[�Y�C��SE�Đ�
      _app.GetSoundComponent().PlayBackGround("pauseIn");
      return true;
    }

    bool ModePause::Exit() {
      // �ϐ����
      Release();
      return true;
    }

    bool ModePause::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // ���X�e�B�b�N�㉺����
      LeftStickYInput(leftY);
      // A�{�^���������ꂽ�ꍇ�A�I������
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
        return true;
      }
      // START�{�^���������ꂽ�ꍇ�A�R���e�j���[
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _continue = 1;
        _quitGame = 0;
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

    void ModePause::Release() {
      // �ϐ����
      _pauseHandle = -1;
      _continueHandle[0] = -1;
      _continueHandle[1] = -1;
      _quitGameHandle[0] = -1;
      _quitGameHandle[1] = -1;
      _isStick = false;
      _decision = false;
    }

    void ModePause::LoadResource() {
      // �摜�ǂݍ���
      _pauseHandle = LoadGraph("res/Pause/pause.png");
      _continueHandle[0] = LoadGraph("res/Pause/continue0.png");
      _continueHandle[1] = LoadGraph("res/Pause/continue1.png");
      _quitGameHandle[0] = LoadGraph("res/Pause/quitgame0.png");
      _quitGameHandle[1] = LoadGraph("res/Pause/quitgame1.png");
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �T�E���h���̓ǂݍ���
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"pauseIn", "res/Sound/SE/System/PauseIn.wav"},    // �|�[�Y�C��SE
        {"pauseOut", "res/Sound/SE/System/PauseOut.wav"},  // �|�[�Y�A�E�gSE
      };
      // �T�E���h�T�[�o�ɓo�^
      _appMain.GetSoundServer().AddSounds(soundMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModePause::LeftStickYInput(const int leftY) {
      if (leftY == 0) {
        // �X�e�B�b�N���͂Ȃ�
        _isStick = false;
        return;
      }
      // ���͂��ꑱ���Ă���ꍇ���f
      if (_isStick) {
        return;
      }
      // ���͒l�̐�������
      bool flag = 0 <= leftY;
      // �摜�؂�ւ��ԍ��̐ݒ�
      _continue = flag ? 1 : 0;
      _quitGame = flag ? 0 : 1;
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �J�[�\��SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround("cursor", 75);
    }

    void ModePause::ChangeMode() {
      // ���[�h�|�[�Y�̍폜
      _appMain.GetModeServer().PopBuck();
      // �|�[�Y�I��
      _appMain.SetGamePause(false);
      // �|�[�Y�A�E�gSE�Đ�
      _app.GetSoundComponent().PlayBackGround("pauseOut");
      // �Q�[���I���I����
      if (_quitGame == 1) {
        // �A�v���P�[�V�����̏I���������Ăяo��
        _appMain.RequestTerminate();
      }
    }
  } // namespace Mode
} // namespace Gyro