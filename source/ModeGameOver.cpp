/*****************************************************************//**
 * @file    ModeGameOver.cpp
 * @brief   ���[�h�Q�[���I�[�o�[�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeGameOver.h"
#include <appframe.h>
#include "ModeGame.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeGameOver::~ModeGameOver() {

    }

    bool ModeGameOver::Init() {
      return true;
    }

    bool ModeGameOver::Enter() {


      // ���\�[�X�ǂݍ���
      LoadResource();
      // �ϐ�������
      _retry = 0;
      _backTitle = 0;
      _decision = false;
      return true;
    }

    bool ModeGameOver::Exit() {
      return true;
    }

    bool ModeGameOver::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // ���X�e�B�b�N����
      if (leftY > 100) {
        _retry = 1;
        _backTitle = 0;
      }
      else if (leftY < -100) {
        _retry = 0;
        _backTitle = 1;
      }
      // A�{�^���������ꂽ�ꍇ�A�I������
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
      }
      return true;
    }

    bool ModeGameOver::Process() {
      // ���͏���
      Input(_appMain.GetOperation());
      // �I�����肳�ꂽ
      if (_decision) {
        // ���[�h�؂�ւ�
        ChangeMode();
      }
      return true;
    }

    bool ModeGameOver::Draw() const {
      // �|�[�Y�`��
      DrawGraph(0, 0, _gameOverHandle, true);
      // �I���ɂ���ĕ`��؂�ւ�
      DrawGraph(0, 0, _retryHandle[_retry], true);
      DrawGraph(0, 0, _backTitleHandle[_backTitle], true);
      return true;
    }

    void ModeGameOver::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �ʖ���`
      using ResourceServer = AppFrame::Resource::ResourceServer;
      const ResourceServer::DivGraphTable table = {
        { "gameover", {"res/GameOver/gameover.png", 1, 1, 1, 1920, 1080}},
        { "retry0", {"res/GameOver/retry0.png", 1, 1, 1, 1920, 1080}},
        { "retry1", {"res/GameOver/retry1.png", 1, 1, 1, 1920, 1080}},
        { "backtitle0", {"res/GameOver/backtitle0.png", 1, 1, 1, 1920, 1080}},
        { "backtitle1", {"res/GameOver/backtitle1.png", 1, 1, 1, 1920, 1080}}
      };
      // �f�ނ̓ǂݍ���
      _app.GetResourceServer().LoadDivGraph(table);
      // �摜�ǂݍ���
      _gameOverHandle = _app.GetResourceServer().GetHandle("gameover");
      _retryHandle[0] = _app.GetResourceServer().GetHandle("retry0");
      _retryHandle[1] = _app.GetResourceServer().GetHandle("retry1");
      _backTitleHandle[0] = _app.GetResourceServer().GetHandle("backtitle0");
      _backTitleHandle[1] = _app.GetResourceServer().GetHandle("backtitle1");
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGameOver::ChangeMode() {
      // ���[�h�Q�[���I�[�o�[�̍폜
      _appMain.GetModeServer().PopBuck();
      // ���g���C�I����
      if (_retry == 1) {
        // ���[�h�Q�[���J��
        _appMain.GetModeServer().TransionToMode("Game");
      }
      // �^�C�g���o�b�N�I����
      if (_backTitle == 1) {
        // ���[�h�^�C�g���J��
        _appMain.GetModeServer().TransionToMode("Title");
      }
    }
  } // namespace Mode
} // namespace Gyro