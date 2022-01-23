/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  �C���Q�[���������s�����[�h
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"

namespace {
    constexpr auto TEXTURE = _T("res/Groundplants1_D.jpg");
}

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app), _player(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // �I�u�W�F�N�g�̐������s��
      return true;
    }

    bool ModeGame::Exit() {
      // ���������I�u�W�F�N�g�̌�n�����s��
      return true;
    }

    bool ModeGame::Init() {
      // �g�p����f�[�^�̓ǂݍ��݂��L�q����
        _player.Init();
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
        _app.RequestTerminate();
      }
      return true;
    }

    bool ModeGame::Process() {
      Input(_app.GetOperation());
      _player.Process();
      _plane.Process();
      _plane.Render();
      return true;
    }

    bool ModeGame::Draw() const {
        _player.Draw();

        // ���s������ 1 �ǉ�����
        VECTOR light_dir = VGet(-1.0f, -1.0f, -1.0f);
        auto light_handle = CreateDirLightHandle(light_dir);

      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }
  } // namespace Mode
} // namespace Gyro