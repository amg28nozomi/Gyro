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
  constexpr int BGMVolume = 50;  //!< BGM�̍Đ��{�����[��
}

namespace Gyro {
  namespace Mode {
    ModeResult::ModeResult(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeResult::~ModeResult() {

    }

    bool ModeResult::Init() {
      // �X�^�W�I����
      _studio = std::make_unique<Studio::Studio>(_appMain);
      return true;
    }

    bool ModeResult::Enter() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      // �X�^�W�I������
      _studio->Init();
      // �Đ����ʂ̐ݒ�
      _appMain.GetSoundComponent().SetVolume("result", BGMVolume);
      // BGM�̍Đ��J�n
      _appMain.GetSoundComponent().PlayLoop("result");
      return true;
    }

    bool ModeResult::Exit() {
      // �ϐ����
      Release();
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

    void ModeResult::Release() {
      // �ϐ����
      _resultHandle = -1;
      _backTitle = false;
    }

    void ModeResult::LoadResource() {
      // �摜�ǂݍ���
      _resultHandle = LoadGraph("res/Result/result.png");
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �T�E���h���̓ǂݍ���
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"result", "res/Sound/BGM/Result.mp3"}  // ���U���g
      };
      // �T�E���h�T�[�o�ɓo�^
      _appMain.GetSoundServer().AddSounds(soundMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeResult::ChangeMode() {
      // ���[�h���U���g�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���̉�SE�̍Đ�
      _appMain.GetSoundComponent().PlayBackGround("bell");
      // ���[�h�^�C�g���J��
      _appMain.GetModeServer().TransionToMode("Title");
      // ���U���gBGM�̒�~
      _appMain.GetSoundComponent().StopSound("result");
    }
  } // namespace Mode
} // namespace Gyro