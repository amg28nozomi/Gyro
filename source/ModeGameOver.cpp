/*****************************************************************//**
 * @file    ModeGameOver.cpp
 * @brief   ���[�h�Q�[���I�[�o�[�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeGameOver.h"
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
      // �摜�؂�ւ��ԍ��̏�����
      _retry = 1;
      _backTitle = 0;
      // �폜�\�񏉊���
      _popBack = false;
      return true;
    }

    bool ModeGameOver::Exit() {
      // �ϐ����
      _isStick = false;
      _decision = false;
      return true;
    }

    bool ModeGameOver::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // ���X�e�B�b�N�㉺����
      LeftStickYInput(leftY);
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
      // �Q�[���I�[�o�[�`��`��
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
      // �摜���̐ݒ�
      const ResourceServer::DivGraphTable divGraphMap{
        {"gameover", {"res/GameOver/gameover.png", 1, 1, 1, 1920, 1080}},      // �Q�[���I�[�o�[
        {"retry0", {"res/GameOver/retry0.png", 1, 1, 1, 1920, 1080}},          // ���g���C0
        {"retry1", {"res/GameOver/retry1.png", 1, 1, 1, 1920, 1080}},          // ���g���C1
        {"backtitle0", {"res/GameOver/backtitle0.png", 1, 1, 1, 1920, 1080}},  // �^�C�g���o�b�N0
        {"backtitle1", {"res/GameOver/backtitle1.png", 1, 1, 1, 1920, 1080}}   // �^�C�g���o�b�N1
      };
      // ���\�[�X�T�[�o�ɓo�^
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // �摜�ǂݍ���
      _gameOverHandle = _appMain.GetResourceServer().GetHandle("gameover");
      _retryHandle[0] = _appMain.GetResourceServer().GetHandle("retry0");
      _retryHandle[1] = _appMain.GetResourceServer().GetHandle("retry1");
      _backTitleHandle[0] = _appMain.GetResourceServer().GetHandle("backtitle0");
      _backTitleHandle[1] = _appMain.GetResourceServer().GetHandle("backtitle1");
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGameOver::LeftStickYInput(const int leftY) {
      if (leftY == 0) {
        // �X�e�B�b�N���͂Ȃ�
        _isStick = false;
        return;
      }
      // ���͂��ꑱ���Ă���ꍇ���f
      if (_isStick) {
        return;
      }
      // ���͒l�̐�������
      bool flag = 0 <= leftY;
      // �摜�؂�ւ��ԍ��̐ݒ�
      _retry = flag ? 1 : 0;
      _backTitle = flag ? 0 : 1;
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �J�[�\��SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround("cursor", 75);
    }

    void ModeGameOver::ChangeMode() {
      // ���̉�SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround("bell", 75);
      // ���g���C�I����
      if (_retry == 1) {
        // ���[�h�Q�[���J��
        _appMain.GetModeServer().TransionToMode("Game");
        // �����\��
        _popBack = true;
        return;
      }
      // �^�C�g���o�b�N�I����
      if (_backTitle == 1) {
        // ���[�h�^�C�g���J��
        _appMain.GetModeServer().TransionToMode("Title");
        // �����\��
        _popBack = true;
        return;
      }
    }
  } // namespace Mode
} // namespace Gyro