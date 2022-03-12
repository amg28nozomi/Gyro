/*****************************************************************//**
 * @file    ModeTitle.cpp
 * @brief   ���[�h�^�C�g���N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "UtilityDX.h"
#include "ModeGame.h"

namespace {
  constexpr int BgmVolume = 50;  //!< BGM�̍Đ��{�����[��
}

namespace Gyro {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeTitle::~ModeTitle() {

    }

    bool ModeTitle::Init() {
      // �X�^�W�I����
      _studio = std::make_unique<Studio::Studio>(_appMain);
      return true;
    }

    bool ModeTitle::Enter() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      // �ϐ�������
      _start = false;
      // �X�^�W�I������
      _studio->Init();
      // BGM�̍Đ��J�n
      _appMain.GetSoundComponent().PlayLoop("title");
      // �Đ����ʂ̐ݒ�
      _appMain.GetSoundComponent().SetVolume("title", BgmVolume);
      return true;
    }

    bool ModeTitle::Exit() {
      // �X�^�W�I���
      _studio->Release();
      return true;
    }

    bool ModeTitle::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();

      device.InputAnyButton();
      namespace App = AppFrame::Application;
      // START�{�^���������ꂽ�ꍇ�A�A�v���P�[�V�������I������(�f�o�b�O�p)
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _appMain.RequestTerminate(); // �A�v���P�[�V�����̏I���������Ăяo��
      }
      // A�{�^���������ꂽ�ꍇ�A�Q�[���J�n
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        if (_start == false) {
          _start = true;
          // �W���C���A�j���ύX
          _studio->GyroChangeAnim("Gyro_Title_Start");
        }
      }
      return true;
    }

    bool ModeTitle::Process() {
      // ���͏���
      Input(_appMain.GetOperation());
      // �X�^�W�I�X�V
      _studio->Process();
      // �Q�[���J�n���ꂽ
      if (_start) {
        // �W���C���̃A�j���[�V�������I�������
        if (_studio->IsGyroAnimEnd()) {
          // ���[�h�؂�ւ�
          ChangeMode();
        }
      }
      return true;
    }

    bool ModeTitle::Draw() const {
      // �X�^�W�I�`��
      _studio->Draw();
      // �^�C�g���`��
      DrawRotaGraph(720, 400, 0.75, 0, _titleHandle, true);
      return true;
    }

    void ModeTitle::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �^�C�g���ǂݍ���
      _titleHandle = LoadGraph("res/Title/GYROtitle.png");
      // �e�탂�f���n���h���̓ǂݍ���
      using ModelServer = AppFrame::Model::ModelServer;
      const ModelServer::ModelDatas mv1Models{
        {"studio", "res/Stage/Studio_GEO.mv1"},           // �X�^�W�I
        {"player", "res/Player/Gyro Multimotion10.mv1"},  // ���@(�W���C��)
        {"sky", "res/SkySphere/skysphere.mv1"},           // �X�J�C�X�t�B�A
      };
      // ���f���T�[�o�œǂݎ����s��
      _appMain.GetModelServer().AddMV1Model(mv1Models);
      // �T�E���h���̓ǂݍ���
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"title", "res/Sound/Title.mp3"}  // �^�C�g��
      };
      // �T�E���h�T�[�o�ɓo�^
      _appMain.GetSoundServer().AddSounds(soundMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeTitle::ChangeMode() {
      // ���[�h�^�C�g���̍폜
      _appMain.GetModeServer().PopBuck();
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("Game");
      if (!key) {
        // ���[�h�Q�[���̓o�^
        _appMain.GetModeServer().AddMode("Game", std::make_shared<Mode::ModeGame>(_appMain));
      }
      // ���[�h�Q�[���J��
      _appMain.GetModeServer().TransionToMode("Game");
      // BGM�̍Đ����~����
      _appMain.GetSoundComponent().StopSound("title");
    }
  }
}