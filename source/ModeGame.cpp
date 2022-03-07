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
#include "EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"
#include "StageComponent.h"
#include "ModeGameOver.h"

namespace {
    constexpr auto TEXTURE = _T("res/Stage/water.png");
    constexpr auto GravityScale = -9.8f; //!< �d�̓X�P�[��
    constexpr auto BgmVolume = 50;       //!< BGM�̍Đ��{�����[��
} // namespace

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �G�t�F�N�g���\�[�X�̓ǂݎ��
      LoadEffectResource();
      // �X�e�[�W�̐؂�ւ�
      StageChange("stage");
      // �I�u�W�F�N�g�𐶐�
      SetSpawn();
      // BGM�̃��[�v�Đ��J�n
      _app.GetSoundComponent().PlayLoop("bgm");
      // �Đ����ʂ̐ݒ�
      _app.GetSoundComponent().SetVolume("bgm", BgmVolume);
      // �J�����̏�����
      _appMain.GetCamera().Init();
      // ���C�g�̐ݒ�
      _light = std::make_unique<Light::Light>();
      // �V���h�E�̐ݒ�
      _shadow = std::make_unique<Shadow::Shadow>(_appMain);

      return true;
    }

    bool ModeGame::Exit() {
      // ���C�g���f�t�H���g�ɖ߂�
      DeleteLightHandleAll();
      SetLightEnable(true);
      // ���������I�u�W�F�N�g���폜
      _appMain.GetObjectServer().Release();
      return true;
    }

    bool ModeGame::Init() {
      // �g�p����f�[�^�̓ǂݍ��݂��L�q����
      _plane.Initialize(35840.0, 35);
      _plane.Load(TEXTURE);
      _plane.Create();
      // �d�͉����x���Z�b�g����
      AppMath::GravityBase::SetScale(GravityScale);
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // START�{�^���������ꂽ�ꍇ�A�A�v���P�[�V�������I������
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _appMain.RequestTerminate(); // �A�v���P�[�V�����̏I���������Ăяo��
      }
#ifdef _DEBUG
      // �f�o�b�O������:���X�e�B�b�N�������ꂽ�ꍇ�A�f�o�b�O�t���O��؂�ւ���
      if (device.GetButton(XINPUT_BUTTON_RIGHT_THUMB, App::InputTrigger)) {
        // �f�o�b�O�t���O�̐؂�ւ�
        _app.ChengeDebugFlag();
        // �T�E���h�t���O�ɉ����ď�����؂�ւ���
        switch (_app.GetSoundComponent().CheckSound("bgm")) {
          // �T�E���h�Đ���
        case AppFrame::Sound::Play:
          // BGM�̍Đ����~����
          _app.GetSoundComponent().StopSound("bgm");
          break;
          // �T�E���h��~��
        case AppFrame::Sound::Stop:
          // BGM�̍Đ��J�n
          _app.GetSoundComponent().PlayLoop("bgm");
          // �Đ����ʂ̐ݒ�
          _app.GetSoundComponent().SetVolume("bgm", 50);
          break;
        }
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // ���[�h�Q�[���̓��͏���
      Input(_app.GetOperation());
      // �Q�[���I�[�o�[����
      bool gameover = _appMain.GetObjectServer().GetPlayer()->GetGameOver();
      if (gameover) {
        GameOver();
        return true;
      }
      // �I�u�W�F�N�g�T�[�o�̍X�V����
      _appMain.GetObjectServer().Process();
      // �G�t�F�N�g�̍X�V����
      _appMain.GetEffect().Process();
      // �n�`�̍X�V����
      _plane.Process();
      // �e��X�e�[�W�̕`��
      _appMain.GetStageComponent().Process();
      return true;
    }

    bool ModeGame::Draw() const {
      // �e�̕`��
      _shadow->Draw();
      // �e��X�e�[�W�̕`��
      _appMain.GetStageComponent().Draw();
      // �n�`�̕`��
      _plane.Draw();
      // �e��`�揈��
      _appMain.GetObjectServer().Draw();
      // �V���h�E�}�b�v�̐ݒ����
      SetUseShadowMap(0, -1);
      // �G�t�F�N�g�̕`��
      _appMain.GetEffect().Draw();
      return true;
    }

    bool ModeGame::StageChange(std::string_view key) {
      // �X�e�[�W�f�ނ̍폜
      _appMain.GetStageComponent().ReleaseStageInfo();
      // �X�e�[�W�R���|�[�l���g�̏�����
      if (!_appMain.GetStageComponent().Init(key.data())) {
        return false;
      }
      // �X�e�[�W�L�[��ݒ�
      _key = key.data();
      // �t�F�[�h�C���E�t�F�[�h�A�E�g���Z�b�g����

      return true; // �ݒ萬��
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }

    void ModeGame::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �ʖ���`
      using ModelServer = AppFrame::Model::ModelServer;
      // �e�탂�f���n���h���̓ǂݍ���
      const ModelServer::ModelDatas mv1Models{
        {"enemy", "res/Enemy/Wheel/Enemy_multimotion.mv1"}, // �G
        {"stage", "res/Stage/houseGEO_1.mv1"}               // �X�e�[�W
      };
      // ���f���T�[�o�œǂݎ����s��
      _app.GetModelServer().AddMV1Model(mv1Models);
      // �T�E���h���̓ǂݎ��
      using SoundServer = AppFrame::Sound::SoundServer;
      // Sound���̐ݒ�
      const SoundServer::SoundMap soundMap{
        {"bgm", "res/Sound/Stage.mp3"}
      };
      // �T�E���h�T�[�o�ɓo�^
      _app.GetSoundServer().AddSounds(soundMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGame::LoadEffectResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isEffectLoad) {
        return; // �ǂݍ��ݍς�
      }
      using EffectLoadServer = Effect::EffectLoadServer;
      // �G�t�F�N�g�n���h���̓ǂݍ���
      const EffectLoadServer::EffectMap effectMap{
        {Effect::PlayerWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack_1.efkefc", 5.0f},
        {Effect::PlayerWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack_2.efkefc", 5.0f},
        {Effect::PlayerWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack_3.efkefc", 5.0f},
        {Effect::PlayerWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattack_EX.efkefc", 5.0f},
        {Effect::PlayerHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc", 20.0f},
        {Effect::PlayerHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc", 20.0f},
        {Effect::PlayerAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc", 5.0f},
        {Effect::PlayerAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc", 5.0f},
        {Effect::PlayerAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc", 5.0f},
        {Effect::PlayerAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc", 5.0f},
        {Effect::PlayerAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc", 5.0f},
        {Effect::PlayerUltActivate, "res/Effect/Player/Ult_Activate/Player_ult_activate.efkefc", 5.0f},
        {Effect::PlayerUltSlash, "res/Effect/Player/Ult_Slash/Player_ult_slash.efkefc", 5.0f},
        {Effect::PlayerJump, "res/Effect/Player/Jump/jump.efkefc", 5.0f},
        {Effect::PlayerHit, "res/Effect/Player/Hit/Hit.efkefc", 5.0f},
        {Effect::EnemyEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc", 20.0f},
        {Effect::EnemyGroundAttack, "res/Effect/Enemy/GroundAttack/Enemy_ground_attack.efkefc", 10.0f},
        {Effect::EnemyHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc", 20.0f},
        {Effect::EnemyExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc", 10.0f},
        {Effect::StageBarrier, "res/Effect/Stage/stage_barrier/stage_barrier.efkefc", 5.0f},
        {Effect::BoxDestroy, "res/Effect/Stage/Box_Destroy/Box_Destroy.efkefc", 5.0f}
      };
      // �G�t�F�N�g�T�[�o�ɓo�^
      _appMain.GetEffectLoadServer().AddEffects(effectMap);
      // �ǂݍ��݊���
      _isEffectLoad = true;
    }

    void ModeGame::SetSpawn() {
      // �X�|�[�����̐ݒ�
      const Object::SpawnTable normal {
        // ���@�̐������
        // ����1:�I�u�W�F�N�g�^�C�v(0:���@�@1:�G)
        // ����2:���[�J�����W
        // ����3:����
        // ����4:�X�P�[��
        { Object::TypePlayer, {0.0f, 200.0f, -200.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
      };
      // �G�l�~�[�e�[�u��
      const Object::EnemyTable enemy {
        // ����^�G�l�~�[�̔z�u���
        { Object::EnemyWheel, { 100.0f, 250.0f, 100.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -200.0f, 250.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 300.0f, 250.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -400.0f, 250.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
      };
      // �e��e�[�u������ɃX�|�[���e�[�u�����쐬
      Object::SpawnData table{
        {0, std::make_tuple(normal, enemy)}
      };
      // �X�|�[���e�[�u���̓o�^
      _appMain.GetSpawnServer().AddSpawnTable("test", table);
#ifndef _DEBUG
      _appMain.GetSpawnServer().SetStage("test");
#else
      try {
        _appMain.GetSpawnServer().SetStage("test");
      } catch (std::logic_error error) {
        OutputDebugString(error.what());
      }
#endif
      // �w�肵���X�|�[��������ɃI�u�W�F�N�g�𐶐�����
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::GameOver() {
      // ���[�h�Q�[���̍폜
      _appMain.GetModeServer().PopBuck();
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("GameOver");
      if (!key) {
        // ���[�h�Q�[���I�[�o�[�̓o�^
        _appMain.GetModeServer().AddMode("GameOver", std::make_shared<Mode::ModeGameOver>(_appMain));
      }
      // ���[�h�Q�[���I�[�o�[�J��
      _appMain.GetModeServer().TransionToMode("GameOver");
      // BGM�̍Đ����~����
      _appMain.GetSoundComponent().StopSound("bgm");
    }
  } // namespace Mode
} // namespace Gyro