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
#include "SpawnServer.h"

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
      _plane.Initialize(45000.0, 150);
      _plane.Load(TEXTURE);
      _plane.Create();
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
        {"player" , "res/Player/Gyro Multimotion7.mv1"},    // ���@
        {"enemy", "res/Enemy/Wheel/Enemy_multimotion.mv1"}, // �G
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
      // �G�t�F�N�g���̓ǂݎ��
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
        { Object::TypePlayer, {0.0f, 0.0f, 0.0f,}, {0.0f, 0.0f, 0.0f,}, {1.0f, 1.0f, 1.0f}}
      };
      // �G�l�~�[�e�[�u��
      const Object::EnemyTable enemy {
        // ����^�G�l�~�[�̔z�u���
        { Object::EnemyWheel, { 100.0f, 0.0f, 100.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 200.0f, 0.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}}
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
        // �G�t�F�N�g�L�[�萔��
        const std::string_view eExprosion = "E_Exprosion";
        const std::string_view eEyeLight = "E_EyeLight";
        const std::string_view eHit = "E_Hit";
        const std::string_view pUltActivate = "P_ult_activate";
        const std::string_view pUltSlash = "P_ult_slash";
        // �G�t�F�N�g�n���h���̓ǂݍ���
        const EffectServer::EffectMap effectMap{
            {eExprosion, "res/Effect/Enemy_Exprosion/Enemy_Exprosion.efkefc"},
            {eEyeLight, "res/Effect/Enemy_EyeLight/Enemy_EyeLight.efkefc"},
            {eHit, "res/Effect/Enemy_Hit/Enemy_Hit.efkefc"},
            {pUltActivate, "res/Effect/Player_ult_activate/Player_ult_activate.efkefc"},
            {pUltSlash, "res/Effect/Player_ult_slash/Player_ult_slash.efkefc"}
        };
        // �G�t�F�N�g�g�嗦�̓o�^
        const EffectServer::EffectMagniMap effectMagniMap{
            {eExprosion, 5.0f},
            {eEyeLight, 20.0f},
            {eHit, 10.0f},
            {pUltActivate, 10.0f},
            {pUltSlash, 5.0f}
        };
        // �G�t�F�N�g�T�[�o�ɓo�^
        _appMain.GetEffectServer().AddEffects(effectMap, effectMagniMap);
    }
  } // namespace Mode
} // namespace Gyro