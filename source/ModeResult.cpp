/*****************************************************************//**
 * @file    ModeResult.cpp
 * @brief   ���[�h���U���g�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeResult.h"
#include "ModeTitle.h"

namespace {
  constexpr int BgmVolume = 50;  //!< BGM�̍Đ��{�����[��
}

namespace Gyro {
  namespace Mode {
    ModeResult::ModeResult(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeResult::~ModeResult() {

    }

    bool ModeResult::Init() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      // �X�^�W�I������
      _studio = std::make_unique<Studio::Studio>(_appMain);
      _studio->Init();
      return true;
    }

    bool ModeResult::Enter() {
      // BGM�̍Đ��J�n
      _appMain.GetSoundComponent().PlayLoop("result");
      // �Đ����ʂ̐ݒ�
      _appMain.GetSoundComponent().SetVolume("result", BgmVolume);
      return true;
    }

    bool ModeResult::Exit() {
      // �J�����̏�����
      _appMain.GetCamera().Init();
      // �X�^�W�I���
      _studio->Release();
      return true;
    }

    bool ModeResult::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // B�{�^���������ꂽ�ꍇ�A�^�C�g���o�b�N
      if (device.GetButton(XINPUT_BUTTON_B, App::InputTrigger)) {
        _backTitle = true;
        // �W���C���A�j���ύX
        _studio->GyroChangeAnim("GyroExciteTrickActive");
      }
      return true;
    }

    bool ModeResult::Process() {
      // ���͏���
      Input(_appMain.GetOperation());
      // �X�^�W�I�X�V
      _studio->Process();
      // �^�C�g���o�b�N���ꂽ
      if (_backTitle) {
        // �W���C���̃A�j���[�V�������I�������
        if (_studio->IsGyroAnimEnd()) {
          // ���[�h�؂�ւ�
          ChangeMode();
        }
      }
      return true;
    }

    bool ModeResult::Draw() const {
      // �X�^�W�I�`��
      _studio->Draw();
      // ���U���g�`��
      DrawGraph(0, 0, _resultHandle, true);
      return true;
    }

    void ModeResult::LoadResource() {
      // �摜�ǂݍ���
      _resultHandle = LoadGraph("res/Result/result.png");
      // �T�E���h���̓ǂݍ���
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"result", "res/Sound/Result.mp3"}  // ���U���g
      };
      // �T�E���h�T�[�o�ɓo�^
      _appMain.GetSoundServer().AddSounds(soundMap);
    }

    void ModeResult::ChangeMode() {
      // ���[�h���U���g�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���[�h�^�C�g���̓o�^
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      _appMain.GetModeServer().TransionToMode("Title");
      // BGM�̍Đ����~����
      _appMain.GetSoundComponent().StopSound("result");
    }
  }
}