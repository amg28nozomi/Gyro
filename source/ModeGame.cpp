/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  �C���Q�[���������s�����[�h
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include <memory>
#include <algorithm>
#include "ApplicationMain.h"
#include "Player.h"
#include "EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"
#include "StageComponent.h"
#include "ModeGameOver.h"
#include "ModeResult.h"
#include "ModePause.h"
#include "ModeLoading.h"
#include "EnemyDrone.h"
#include "EnemyDroneBoss.h"
#include "EnemyWheel.h"
#include "EnemyWheelBoss.h"

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
      // �X�e�[�W�t���O�ɉ����Ďg�p����L�[�؂�ւ�
      auto k = (_stageFlag) ? "stage" : "boss";
      _appMain.GetStageComponent().CreateStage(k);
      // BGM�̃��[�v�Đ��J�n
      PlayBgm("bgm", BgmVolume);
      // �Q�[����Ԃ̐ݒ�
      _gameState = GameState::Play;
      SetSpawn(); // �I�u�W�F�N�g�𐶐�
      // �J�����̏�����
      _appMain.GetCamera().Init();
      // ���C�g�̐ݒ�
      _light = std::make_unique<Light::Light>();
      // �V���h�E�̐ݒ�
      _shadow = std::make_unique<Shadow::Shadow>(_appMain);
      // �Q�[���t���O�̏�����
      _appMain.SetGameOver(false);
      _appMain.SetGameClear(false);
      _appMain.SetGamePause(false);
      // �X�e�[�W�ɉ����ăt���O�؂�ւ�
      _wave1 = (_stageFlag) ? true : false;
      _wave2 = (_stageFlag) ? true : false;
      _wave3 = (_stageFlag) ? true : false;
      _wave4 = (_stageFlag) ? true : false;
      _bossStage = true;
      _waveNum = 0;
      return true;
    }

    bool ModeGame::Exit() {
      // ���C�g���f�t�H���g�ɖ߂�
      DeleteLightHandleAll();
      // 
      SetLightEnable(true);
      // ���������I�u�W�F�N�g���폜
      _appMain.GetObjectServer().Release();
      // ���������n���h�����폜
      ResetObjectNumber();
      // ���������G�t�F�N�g���폜
      _appMain.GetEffectServer().Release();
      // �����������f�����폜
      _appMain.GetStageComponent().ReleaseModel();
      // �N���A���肪�����Ă���ꍇ
      if (_appMain.GetGameClear()) {
        _stageFlag = true;
      }
      BossCountReset();
      return true;
    }

    bool ModeGame::Init() {
      // �g�p����f�[�^�̓ǂݍ��݂��L�q����
      _plane.Initialize(40960.0f, 40);
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
      // START�{�^���������ꂽ�ꍇ�A�|�[�Y���Ăяo��
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        // �|�[�Y
        Pause();
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
          // BGM�̃��[�v�Đ��J�n
          PlayBgm("bgm", BgmVolume);
          break;
        }
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // ���[�h�폜�\�񔻒�
      PopBack();
      // ���[�h�Q�[���̓��͏���
      Input(_app.GetOperation());
      // �Q�[���I�[�o�[����
      if (GameOver()) {
        return true;
      }
      // �Q�[���N���A����
      if (_appMain.GetGameClear()) {
        Result();
        return true;
      }
      // �|�[�Y����
      if (_appMain.GetGamePause()) {
        return true;
      }
      // �I�u�W�F�N�g�T�[�o�̍X�V����
      _appMain.GetObjectServer().Process();
      // �G�t�F�N�g�̍X�V����
      _appMain.GetEffectServer().Process();
      // �n�`�̍X�V����
      _plane.Process();
      // �e��X�e�[�W�̕`��
      _appMain.GetStageComponent().Process();
      // �X�|�[������^�C�~���O
      SpawnTiming();
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
      _appMain.GetEffectServer().Draw();
      return true;
    }

    bool ModeGame::StageChange(const Stage::StageTransition::StageType& key) {
      // �X�e�[�W�̑J�ڗ\����s��
      return _appMain.GetStageTransition().ChangeReserve(key);
    }

    std::string_view ModeGame::BossStageSpawn() {
      // �{�X�X�e�[�W
      const Object::SpawnTable bossP{
        { Object::TypePlayer, {0.0f, 1000.f, -200.f}, {}, {1.0f, 1.0f, 1.0f} },
        { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f}},
      };
      const Object::EnemyTable bossE{
        { Object::EnemyWheelBoss, { -200.0f, 394.0f, -10000.0f}, {0.0f, -180.0f, 0.0f }, {5.0f, 5.0f, 5.0f}},
        { Object::EnemyDroneBoss, { 300.0f, 394.0f, -10000.0f}, {0.0f, -180.0f, 0.0f }, {7.0f, 7.0f, 7.0f}},
      };
      // �X�|�[�����
      Object::SpawnData bossTable{
      {0, std::make_tuple(bossP, bossE)},
      };
      // �{�X�X�e�[�W�L�[
      std::string_view key = "bossTable";
      // �X�|�[���e�[�u���̓o�^
      _appMain.GetSpawnServer().AddSpawnTable(key.data(), bossTable);
      return key;
    }

    bool ModeGame::ToGameClear() {
      // �{�X�J�E���g���C���N�������g
      ++_bossCount;
      // �Q�[���N���A�ɑJ�ڂ��邩�̔�����s��
      if (IsGameClear()) {
        _stageFlag = true;
        return true; // �J�ڂ���
      }
      return false; // �N���A�ɑJ�ڂ��Ȃ�
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
        {"enemyWheel", "res/Enemy/Wheel/enemy1_set.mv1"},                 // �n��G
        {"enemyWheelBoss", "res/Enemy/Wheel/enemy1_boss_set.mv1"},        // �n��G�{�X
        {"enemyDrone", "res/Enemy/Drone/enemy2 Multimotion fin.mv1"},     // �󒆓G
        {"enemyDroneBoss", "res/Enemy/Drone/enemy2 Bos Multimotion fin1.mv1"},  // �󒆓G�{�X
      };
      // ���f���T�[�o�œǂݎ����s��
      _app.GetModelServer().AddMV1Model(mv1Models);
      // �T�E���h���̓ǂݎ��
      using SoundServer = AppFrame::Sound::SoundServer;
      // Sound���̐ݒ�
      const SoundServer::SoundMap soundMap{
        {"bgm", "res/Sound/BGM/Stage.mp3"},
        {"walk", "res/Sound/SE/Player/Walk.wav"},            // ����SE
        {"dash", "res/Sound/SE/Player/Dash.wav"},            // ����SE
        {"jump", "res/Sound/SE/Player/Jump.wav"},            // �W�����vSE
        {"landing", "res/Sound/SE/Player/Landing.wav"},      // ���nSE
        {"avoidance", "res/Sound/SE/Player/Avoidance.wav"},  // ���SE
        {"ready", "res/Sound/SE/Player/TrickReady.wav"},     // �K�E����SE
        {"barst", "res/Sound/SE/Player/TrickBarst.wav"},     // �K�E�U��SE
        {"wMove", "res/Sound/SE/Enemy/WheelMove.wav"},       // �n��ړ�SE
        {"wAttack", "res/Sound/SE/Enemy/WheelAttack.wav"},   // �n��U��SE
        {"dAttack", "res/Sound/SE/Enemy/DroneAttack.wav"},   // �󒆍U��SE
        {"hitLow", "res/Sound/SE/Enemy/EnemyHitLow.wav"},       // �q�b�g��SE
        {"hitHigh", "res/Sound/SE/Enemy/EnemyHitHigh.wav"},     // �q�b�g��SE
        {"destroy", "res/Sound/SE/Enemy/EnemyDestroy.wav"},     // �j��SE
        // �v���C���[��
        {"idle", "res/Sound/SE/Player/Voice/idle.wav"},         // �ҋ@
        {"jump", "res/Sound/SE/Player/Voice/jump.wav"},         // �W�����v
        {"damage", "res/Sound/SE/Player/Voice/damage.wav"},     // �_���[�W
        {"excite1", "res/Sound/SE/Player/Voice/excite1.wav"},   // �K�E�Z�\��
        {"excite2", "res/Sound/SE/Player/Voice/excite2.wav"},   // �K�E�Z��
        {"excite3", "res/Sound/SE/Player/Voice/excite3.wav"},   // �K�E�Z��
        {"low1", "res/Sound/SE/Player/Voice/low1.wav"},         // ��U��1
        {"low2", "res/Sound/SE/Player/Voice/low2.wav"},         // ��U��2
        {"low3", "res/Sound/SE/Player/Voice/low3.wav"},         // ��U��3
        {"lowex", "res/Sound/SE/Player/Voice/lowex.wav"},       // ��U��EX
        {"high1", "res/Sound/SE/Player/Voice/high1.wav"},       // ���U��1
        {"high2", "res/Sound/SE/Player/Voice/high2.wav"},       // ���U��2
        {"high3", "res/Sound/SE/Player/Voice/high3.wav"},       // ���U��3
        {"jlow1", "res/Sound/SE/Player/Voice/jweak1.wav"},      // �󒆎�U��1
        {"jlow2", "res/Sound/SE/Player/Voice/jlow2.wav"},       // �󒆎�U��2
        {"jlow3", "res/Sound/SE/Player/Voice/jlow3.wav"},       // �󒆎�U��3
        {"jhigh1", "res/Sound/SE/Player/Voice/jhigh.wav"},      // �󒆋��U��1
        {"jhigh2", "res/Sound/SE/Player/Voice/jhigh2.wav"},     // �󒆋��U��2
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
        {EffectKey::PlayerDash, "res/Effect/Player/Dash/player_dash.efkefc", 5.0f},
        {EffectKey::PlayerJump, "res/Effect/Player/Jump/jump.efkefc", 5.0f},
        {EffectKey::PlayerLanding, "res/Effect/Player/Landing/landing.efkefc", 5.0f},
        {EffectKey::PlayerHit, "res/Effect/Player/Hit/Player_hit.efkefc", 5.0f},
        {EffectKey::PlayerAvoidance, "res/Effect/Player/Avoidance/player_avoidance.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack_1.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack_2.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack_3.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattack_EX.efkefc", 5.0f},
        {EffectKey::PlayerHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc", 30.0f},
        {EffectKey::PlayerHeavyAttack2, "res/Effect/Player/HeavyAttack2/Player_attack_heavy_02.efkefc", 10.0f},
        {EffectKey::PlayerHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc", 20.0f},
        {EffectKey::PlayerAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc", 10.0f},
        {EffectKey::PlayerAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc", 10.0f},
        {EffectKey::PlayerAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc", 10.0f},
        {EffectKey::PlayerAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc", 10.0f},
        {EffectKey::PlayerAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc", 5.0f},
        {EffectKey::PlayerUltActivate, "res/Effect/Player/UltActivate/Player_ult_activate.efkefc", 5.0f},
        {EffectKey::PlayerUltSlash, "res/Effect/Player/UltSlash/Player_ult_slash.efkefc", 20.0f},
        {EffectKey::EnemyEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc", 20.0f},
        {EffectKey::EnemyGroundAttack1, "res/Effect/Enemy/GroundAttack1/Enemy_ground_attack1.efkefc", 10.0f},
        {EffectKey::EnemyGroundAttack2, "res/Effect/Enemy/GroundAttack2/Enemy_ground_attack2.efkefc", 10.0f},
        {EffectKey::EnemyAirAttack, "res/Effect/Enemy/AirAttack/Enemy_air_attack.efkefc", 15.0f},
        {EffectKey::EnemyHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc", 20.0f},
        {EffectKey::EnemyExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc", 10.0f},
        {EffectKey::EnemyBossEyeLight, "res/Effect/Enemy/Boss/EyeLight/Enemy_EyeLight.efkefc", 40.0f},
        {EffectKey::EnemyBossGroundAttack1, "res/Effect/Enemy/Boss/GroundAttack1/Enemy_ground_attack1.efkefc", 20.0f},
        {EffectKey::EnemyBossGroundAttack2, "res/Effect/Enemy/Boss/GroundAttack2/Enemy_ground_attack2.efkefc", 20.0f},
        {EffectKey::EnemyBossAirAttack, "res/Effect/Enemy/Boss/AirAttack/Enemy_air_attack.efkefc", 30.0f},
        {EffectKey::EnemyBossHit, "res/Effect/Enemy/Boss/Hit/Enemy_Hit.efkefc", 40.0f},
        {EffectKey::EnemyBossExprosion, "res/Effect/Enemy/Boss/Exprosion/Enemy_Exprosion.efkefc", 20.0f},
        {EffectKey::StageBarrier, "res/Effect/Stage/Barrier/stage_barrier.efkefc", 5.0f},
        {EffectKey::StageBoxDestroy, "res/Effect/Stage/BoxDestroy/Box_Destroy.efkefc", 5.0f},
        {EffectKey::StageHeal, "res/Effect/Stage/Heal/Player_heal.efkefc", 5.0f}
      };
      // �G�t�F�N�g�T�[�o�ɓo�^
      _appMain.GetEffectLoadServer().AddEffects(effectMap);
      // �ǂݍ��݊���
      _isEffectLoad = true;
    }

    void ModeGame::SetSpawn() {
      // �����L�[
      std::string stageKey;
      // �����X�e�[�W�̏ꍇ
      if (_stageFlag) {
        // �X�|�[�����̐ݒ�
        const Object::SpawnTable normal{
          // ���@�̐������
          // ����1:�I�u�W�F�N�g�^�C�v(0:���@�@1:�G)
          // ����2:���[�J�����W
          // ����3:����
          // ����4:�X�P�[��
          { Object::TypePlayer, {0.0f, 675.0f, 1800.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
          { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f}},
        };
        // ��̃X�|�[�����
        const Object::SpawnTable none{
        };
        // �G�l�~�[�e�[�u��
        const Object::EnemyTable wave1{
          // ����^�G�l�~�[�̔z�u���
          { Object::EnemyWheel, { 100.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyWheel, { -200.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        };
        const Object::EnemyTable wave2{
          { Object::EnemyDrone, { 100.0f, 845.0f, -4500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        };
        const Object::EnemyTable wave3{
          { Object::EnemyWheel, { 4100.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyWheel, { 4200.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyDrone, { 4400.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        };
        const Object::EnemyTable wave4{
          { Object::EnemyDrone, { 2100.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
          { Object::EnemyWheel, { 2200.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyWheel, { 2300.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyDrone, { 2400.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        };
        const Object::EnemyTable wave5{
          { Object::EnemyWheel, { 1600.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyDrone, { 1700.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
          { Object::EnemyDrone, { 1800.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
          { Object::EnemyWheel, { 1900.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        };
        // �A�C�e���e�[�u��
        const Object::ItemTable item{
          { "player", 1, {0.0f, 200.0f, -100.0f}, {}, {1.0f, 1.0f, 1.0f}}
        };
        // �e��e�[�u������ɃX�|�[���e�[�u�����쐬
        Object::SpawnData3 table1{
          {0, std::make_tuple(normal, wave1, item)},
        };
        Object::SpawnData table2{
          {0, std::make_tuple(none, wave2)},
        };
        Object::SpawnData table3{
          {0, std::make_tuple(none, wave3)},
        };
        Object::SpawnData table4{
          {0, std::make_tuple(none, wave4)},
        };
        Object::SpawnData table5{
          {0, std::make_tuple(none, wave5)},
        };
        // �X�|�[���e�[�u���̓o�^
        _appMain.GetSpawnServer().AddSpawnTable("wave1", table1);
        _appMain.GetSpawnServer().AddSpawnTable("wave2", table2);
        _appMain.GetSpawnServer().AddSpawnTable("wave3", table3);
        _appMain.GetSpawnServer().AddSpawnTable("wave4", table4);
        _appMain.GetSpawnServer().AddSpawnTable("wave5", table5);
        stageKey = "wave1";
      }
      // �{�X�X�e�[�W�̏ꍇ
      else {
        stageKey = BossStageSpawn().data();
      }
#ifndef _DEBUG
      _appMain.GetSpawnServer().SetStage(stageKey);
#else
      try {
        _appMain.GetSpawnServer().SetStage(stageKey);
      } catch (std::logic_error error) {
        OutputDebugString(error.what());
      }
#endif
      // �w�肵���X�|�[��������ɃI�u�W�F�N�g�𐶐�����
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::SpawnTiming() {
      // �E�F�[�u��
      const auto waveMax = 4;
      // ���@�̎擾
      auto player = _appMain.GetObjectServer().GetPlayer();
      // �擾�Ɏ��s�����ꍇ�͍X�V���s��Ȃ�
      if (player == nullptr) {
        return;
      }
      // �v���C���[�̈ʒu�����ēG�X�|�[��������
      const auto pPos = player->GetPosition();
      // ��������
      if (pPos.GetZ() < -2244.f && _wave1 == true) {
        _appMain.GetSpawnServer().SetStage("wave2");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave1 = false;
      }else if (pPos.GetZ() < -6600.f && _wave2 == true) {
        _appMain.GetSpawnServer().SetStage("wave3");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave2 = false;
      }else if (pPos.GetZ() < -9600.f && _wave3 == true) {
        _appMain.GetSpawnServer().SetStage("wave4");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave3 = false;
      }else if (pPos.GetZ() < -13500.f && _wave4 == true) {
        _appMain.GetSpawnServer().SetStage("wave5");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave4 = false;
      }
      // �ŏI�E�F�[�u����
      if (waveMax <= _waveNum && _bossStage == true) {
        //// �I�u�W�F�N�g�̃R�s�[
        //auto objects = _appMain.GetObjectServer().GetObjects();
        //// ���I�z��Ɉ�v����v�f�����邩���肷��
        //auto activeEnemy = std::any_of(objects.begin(), objects.end(),
        //  [](std::shared_ptr<Object::ObjectBase>& obj) {
        //    // ������Ԃ̓G�͂��邩
        //    return (obj->GetId() == Object::ObjectBase::ObjectId::Enemy) && obj->GetState() == Object::ObjectBase::ObjectState::Active; });
        //if (!activeEnemy) {
        //  // ���Ȃ��Ȃ�X�e�[�W�̐؂�ւ�
        //  StageChange("boss");
        //}else {
        //  for (auto obj : objects) {
        //    // �G�Ȃ瑱��
        //    if (obj->GetId() != Object::ObjectBase::ObjectId::Enemy)continue;
        //    auto enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj).get()->GetState();
        //    enemy = Object::ObjectBase::ObjectState::Dead;
        //  }
        //  // �X�e�[�W�̐؂�ւ�
        //  StageChange("boss");
        //}
        // �X�e�[�W�̐؂�ւ�
        //StageChange("boss");
        // ���[�h���[�f�B���O�֑J��
        Loading();
        _appMain.GetSpawnServer().SetStage(BossStageSpawn().data());
        // �w�肵���X�|�[��������ɃI�u�W�F�N�g�𐶐�����
        _appMain.GetSpawnServer().Spawn(0);
        _stageFlag = false;
        _bossStage = false;
      }
    }

    bool ModeGame::GameOver() {
      // �Q�[���I�[�o�[�t���O�������Ă��邩�̔���
      if (_gameState != GameState::GameOver) {
        return false; // �Q�[���I�[�o�[�ł͂Ȃ����ߏ������s��Ȃ�
      }
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
      // �����\��
      _popBack = true;
      return true;
    }

    void ModeGame::Result() {
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("Result");
      if (!key) {
        // ���[�h���U���g�̓o�^
        _appMain.GetModeServer().AddMode("Result", std::make_shared<Mode::ModeResult>(_appMain));
      }
      // ���[�h���U���g�J��
      _appMain.GetModeServer().TransionToMode("Result");
      // BGM�̍Đ����~����
      _appMain.GetSoundComponent().StopSound("bgm");
      // �����\��
      _popBack = true;
    }

    void ModeGame::ToGameOver() {
      _gameState = GameState::GameOver;
    }

    void ModeGame::Pause() {
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("Pause");
      if (!key) {
        // ���[�h�|�[�Y�̓o�^
        _appMain.GetModeServer().AddMode("Pause", std::make_shared<Mode::ModePause>(_appMain));
      }
      // ���[�h�|�[�Y�J��
      _appMain.GetModeServer().PushBack("Pause");
      // �|�[�Y�J�n
      _appMain.SetGamePause(true);
    }

    void ModeGame::Loading() {
      // �L�[���o�^����Ă��邩
      bool key = _appMain.GetModeServer().Contains("Loading");
      if (!key) {
        // ���[�h���[�h�f�B���O�̓o�^
        _appMain.GetModeServer().AddMode("Loading", std::make_shared<Mode::ModeLoading>(_appMain));
      }
      // ���[�h���[�h�f�B���O�J��
      _appMain.GetModeServer().PushBack("Loading");
    }

    void ModeGame::ResetObjectNumber() {
      // �e��I�u�W�F�N�g�ԍ���������
      Enemy::EnemyDrone::ModelNumberReset();
      Enemy::EnemyDroneBoss::ModelNumberReset();
      Enemy::EnemyWheel::ModelNumberReset();
      Enemy::EnemyWheelBoss::ModelNumberReset();
      // �I�u�W�F�N�g�T�[�o���畡���i���폜����
      _appMain.GetModelServer().DeleteDuplicateModels("", true);
    }
  } // namespace Mode
} // namespace Gyro