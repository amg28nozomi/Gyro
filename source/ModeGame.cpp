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

namespace {
    constexpr auto TEXTURE = _T("res/water.png");
}

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // �I�u�W�F�N�g�𐶐�
      SetSpawn();
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
      _plane.Initialize(35000.0, 150);
      _plane.Load(TEXTURE);
      _plane.Create();
      _appMain.GetStageComponent().Init();
      // �d�͉����x���Z�b�g����
      AppMath::GravityBase::SetScale(-9.8f);
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
        _app.ChengeDebugFlag(); // �f�o�b�O�t���O�̐؂�ւ�
        if (_app.GetDebugFlag()) {
          _app.GetSoundComponent().PlayLoop("bgm");
          _app.GetSoundComponent().SetVolume("bgm", 50);
        } else {
          _app.GetSoundComponent().StopSound("bgm");
        }
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // ���͏���
      Input(_app.GetOperation());
      // �I�u�W�F�N�g�T�[�o�̍X�V�������s
      _appMain.GetObjectServer().Process();
      _appMain.GetEffect().Process();
      _plane.Process();

      return true;
    }

    bool ModeGame::Draw() const {
      // �`�揈���Ăяo��
      _appMain.GetObjectServer().Draw();
      _appMain.GetEffect().Draw();
      _appMain.GetStageComponent().Draw();
      _plane.Draw();

      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }

    void ModeGame::LoadResource() const {
      using ModelServer = AppFrame::Model::ModelServer;
      // �e�탂�f���n���h���̓ǂݍ���
      const ModelServer::ModelDatas mv1Models{
        {"player", "res/Player/Gyro Multimotion8.mv1"},     // ���@
        {"enemy", "res/Enemy/Wheel/Enemy_multimotion.mv1"}, // �G
        {"sky", "res/SkySphere/skysphere.mv1"},             // �X�J�C�X�t�B�A
        {"stage", "res/Stage/houseGEO_1.mv1"}               // �X�e�[�W
      };
      // ���f���T�[�o�œǂݎ����s��
      _app.GetModelServer().AddMV1Model(mv1Models);
      // �T�E���h���̓ǂݎ��
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"bgm", "res/Sound/Stage.mp3"}
      };
      // �T�E���h�T�[�o�ɓo�^
      _app.GetSoundServer().AddSounds(soundMap);
      // �G�t�F�N�g���\�[�X�̓ǂݎ��
      LoadEffectResource();
    }

    void ModeGame::SetSpawn() {
      // �X�|�[�����̐ݒ�
      const Object::SpawnTable normal {
        // ���@�̐������
        // ����1:�I�u�W�F�N�g�^�C�v(0:���@�@1:�G)
        // ����2:���[�J�����W
        // ����3:����
        // ����4:�X�P�[��
        { Object::TypePlayer, {0.0f, 1500.0f, 0.0f,}, {0.0f, 0.0f, 0.0f,}, {1.0f, 1.0f, 1.0f}}
      };
      // �G�l�~�[�e�[�u��
      const Object::EnemyTable enemy {
        // ����^�G�l�~�[�̔z�u���
        { Object::EnemyWheel, { 100.0f, 1500.0f, 100.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -200.0f, 1500.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 300.0f, 1500.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -400.0f, 1500.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
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
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::LoadEffectResource() const {
      using EffectServer = Effect::EffectServer;
      // �G�t�F�N�g�n���h���̓ǂݍ���
      const EffectServer::EffectMap effectMap{
        {Effect::pWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack1_1.efkefc"},
        {Effect::pWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack2_2.efkefc"},
        {Effect::pWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack3.efkefc"},
        {Effect::pWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattackEX.efkefc"},
        {Effect::pHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc"},
        {Effect::pHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc"},
        {Effect::pAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc"},
        {Effect::pAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc"},
        {Effect::pAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc"},
        {Effect::pAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc"},
        {Effect::pAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc"},
        {Effect::pUltActivate, "res/Effect/Player/Ult_Activate/Player_ult_activate.efkefc"},
        {Effect::pUltSlash, "res/Effect/Player/Ult_Slash/Player_ult_slash.efkefc"},
        {Effect::pHit, "res/Effect/Player/Hit/Hit.efkefc"},
        {Effect::eEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc"},
        {Effect::eGroundAttack, "res/Effect/Enemy/GroundAttack/Enemy_ground_attack.efkefc"},
        {Effect::eHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc"},
        {Effect::eExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc"},
        {Effect::stageBarrier, "res/Effect/stage_barrier/stage_barrier.efkefc"}
      };
      // �G�t�F�N�g�g�嗦�̓o�^
      const EffectServer::EffectMagniMap effectMagniMap{
        {Effect::pWeakAttack1, 5.0f},
        {Effect::pWeakAttack2, 5.0f},
        {Effect::pWeakAttack3, 5.0f},
        {Effect::pWeakAttackEX, 2.0f},
        {Effect::pHeavyAttack1, 20.0f},
        {Effect::pHeavyAttack3, 20.0f},
        {Effect::pAirWeakAttack1, 10.0f},
        {Effect::pAirWeakAttack2, 10.0f},
        {Effect::pAirWeakAttack3, 10.0f},
        {Effect::pAirHeavyAttack1, 10.0f},
        {Effect::pAirHeavyAttack2, 10.0f},
        {Effect::pUltActivate, 10.0f},
        {Effect::pUltSlash, 10.0f},
        {Effect::pHit, 20.0f},
        {Effect::eEyeLight, 20.0f},
        {Effect::eGroundAttack, 10.0f},
        {Effect::eHit, 20.0f},
        {Effect::eExprosion, 10.0f},
        {Effect::stageBarrier, 20.0f}
      };
      // �G�t�F�N�g�T�[�o�ɓo�^
      _appMain.GetEffectServer().AddEffects(effectMap, effectMagniMap);
    }
  } // namespace Mode
} // namespace Gyro