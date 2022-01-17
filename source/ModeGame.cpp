#include "ModeGame.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(AppFrame::Application::ApplicationBase& app) : ModeBase(app) {
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
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetJoypadState();
      // A�L�[�����͂��ꂽ�ꍇ
      if (device.GetKey() ^ PAD_INPUT_10) {
        // �A�v���P�[�V�����̏I���v�����s��
        _app.RequestTerminate();
      }
      return true;
    }

    bool ModeGame::Process() {
      return true;
    }

    bool ModeGame::Draw() const {
      return true;
    }
  } // namespace Mode
} // namespace Gyro