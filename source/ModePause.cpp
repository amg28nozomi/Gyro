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
      // �|�[�Y�C��SE�Đ�
      _app.GetSoundComponent().PlayBackGround("pauseIn");
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
      if (0 < leftY) {
        // ��I��(�R���e�j���[)
        _continue = 1;
        _quitGame = 0;
      }
      else if (leftY < 0) {
        // ���I��(�Q�[���I��)
        _continue = 0;
        _quitGame = 1;
      }
      // A�{�^���������ꂽ�ꍇ�A�I������
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
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

    void ModePause::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �摜�ǂݍ���
            // �ʖ���`
      using ResourceServer = AppFrame::Resource::ResourceServer;
      const ResourceServer::DivGraphTable table = {
        { "pause", {"res/Pause/pause.png", 1, 1, 1, 1920, 1080}},
        { "continue0", {"res/Pause/continue0.png", 1, 1, 1, 1920, 1080}},
        { "continue1", {"res/Pause/continue1.png", 1, 1, 1, 1920, 1080}},
        { "quitgame0", {"res/Pause/quitgame0.png", 1, 1, 1, 1920, 1080}},
        { "quitgame1", {"res/Pause/quitgame1.png", 1, 1, 1, 1920, 1080}}
      };
      // �f�ނ̓ǂݍ���
      _app.GetResourceServer().LoadDivGraph(table);

      _pauseHandle = _app.GetResourceServer().GetHandle("pause");
      _continueHandle[0] = _app.GetResourceServer().GetHandle("continue0");
      _continueHandle[1] = _app.GetResourceServer().GetHandle("continue1");
      _quitGameHandle[0] = _app.GetResourceServer().GetHandle("quitgame0");
      _quitGameHandle[1] = _app.GetResourceServer().GetHandle("guitgame1");
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

    void ModePause::ChangeMode() {
      // ���[�h�|�[�Y�̍폜
      _appMain.GetModeServer().PopBuck();
      // �|�[�Y�I��
      _appMain.SetGamePause(false);
      // �R���e�B�j���[�I����
      if (_continue == 1) {
        // �|�[�Y�A�E�gSE�Đ�
        _app.GetSoundComponent().PlayBackGround("pauseOut");
      }
      // �Q�[���I���I����
      if (_quitGame == 1) {
        // �A�v���P�[�V�����̏I���������Ăяo��
        _appMain.RequestTerminate();
      }
    }
  } // namespace Mode
} // namespace Gyro