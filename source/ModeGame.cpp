/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  �C���Q�[���������s�����[�h
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include <memory>
#include "ApplicationMain.h"
#include "Player.h"
#include "Enemy/EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"

namespace {
    constexpr auto TEXTURE = _T("res/Groundplants1_D.jpg");
}

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // �I�u�W�F�N�g�𐶐�
      _appMain.GetObjectServer().Register(std::move(std::make_shared<Player::Player>(_appMain)));
      _appMain.GetObjectServer().Register(std::move(std::make_shared<Enemy::EnemyWheel>(_appMain)));
      return true;
    }

    bool ModeGame::Exit() {
      // ���������I�u�W�F�N�g����菜��
      _appMain.GetObjectServer().Release();
      return true;
    }

    bool ModeGame::Init() {
      LoadResource(); // �e�탊�\�[�X�̓ǂݎ����s��
      // �g�p����f�[�^�̓ǂݍ��݂��L�q����
      _plane.Initialize(45000.0, 150);
      _plane.Load(TEXTURE);
      _plane.Create();
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // START�{�^���������ꂽ�ꍇ�A�A�v���P�[�V�������I������
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _appMain.RequestTerminate();
      }
#ifdef _DEBUG
      // �f�o�b�O������:���X�e�B�b�N�������ꂽ�ꍇ�A�f�o�b�O�t���O��؂�ւ���
      if (device.GetButton(XINPUT_BUTTON_RIGHT_THUMB, App::InputTrigger)) {
        _app.GetSoundComponent().PlayLoop("bgm");
        _app.ChengeDebugFlag(); // �f�o�b�O�t���O�̐؂�ւ�
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // ���͏���
      Input(_app.GetOperation());
      // �I�u�W�F�N�g�T�[�o�̍X�V�������s
      _appMain.GetObjectServer().Process();
      _plane.Process();
      _plane.Render();
      return true;
    }

    bool ModeGame::Draw() const {
      // �`�揈���Ăяo��
      _appMain.GetObjectServer().Draw();
      // ���s������ 1 �ǉ�����
      VECTOR light_dir = VGet(0.0f, 1.0f, 0.0f);
      auto light_handle = CreateDirLightHandle(light_dir);

      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }

    void ModeGame::LoadResource() const {
      using ModelServer = AppFrame::Model::ModelServer;
      // �e�탂�f���n���h���̓ǂݍ���
      const ModelServer::ModelDatas mv1Models{
        {"player" , "res/Player/Gyro multibag.mv1"},  // ���@
        {"enemy", "res/Enemy/Enemy_multimotion.mv1"}, // �G
        {"sky", "res/SkySphere/skysphere.mv1"},       // �X�J�C�X�t�B�A
        {"stage", "res/Stage/houseGEO_1.mv1"}         // �X�e�[�W
      };
      // ���f���T�[�o�œǂݎ����s��
      _app.GetModelServer().AddMV1Model(mv1Models);
      // �T�E���h���̓ǂݎ��
      using SoundServer = AppFrame::Sound::SoundServer;
      // 
      const SoundServer::SoundMap soundMap{
        {"test", "res/Sound/pose.wav"},
        {"bgm", "res/Sound/stage1.wav"}
      };
      // �T�E���h�T�[�o�ɓo�^
      _app.GetSoundServer().AddSounds(soundMap);
    }
  } // namespace Mode
} // namespace Gyro