/*****************************************************************//**
 * @file    ModeTitle.cpp
 * @brief   ���[�h�^�C�g���N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeCredit.h"
#include "ModeLoading.h"

namespace {
  constexpr int BGMVolume = 50;  //!< BGM�̍Đ��{�����[��
  // ��ʐ؂�ւ��萔
  constexpr int PressAnyButtonNum = 0;  //!< �v���X�{�^��
  constexpr int GameStartNum = 1;       //!< �Q�[���J�n
  constexpr int CreditNum = 2;          //!< �N���W�b�g
  constexpr int QuitGameNum = 3;        //!< �Q�[���I��
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
      // ��ʔԍ�������
      _sceneNum = 0;
      // �X�^�W�I������
      _studio->Init();
      // �^�C�g��BGM�̍Đ��J�n
      PlayBgm("title", BGMVolume);
      return true;
    }

    bool ModeTitle::Exit() {
      // �ϐ����
      _gameStartExRate = 1.0f;
      _creditExRate = 1.0f;
      _quitGameExRate = 1.0f;
      _isStick = false;
      _decision = false;
      // �X�^�W�I���
      _studio->Release();
      return true;
    }

    bool ModeTitle::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // ��ʔԍ����v���X�{�^��
      if (_sceneNum == PressAnyButtonNum) {
        // ���炩�̃{�^���������ꂽ���ʐ؂�ւ�
        if (device.InputAnyButton()) {
          _sceneNum = GameStartNum;
        }
        return true;
      }
      // �I�𖢌���
      if (!_decision) {
        auto [leftX, leftY] = device.GetStick(false);
        // ���X�e�B�b�N�㉺����
        LeftStickYInput(leftY);
        // A�{�^���������ꂽ�ꍇ�A�I������
        if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
          // ��ʔԍ����Q�[���I��
          if (_sceneNum == QuitGameNum) {
            // �A�v���P�[�V�����̏I���������Ăяo��
            _appMain.RequestTerminate();
            // �I������
            _decision = true;
            return true;
          }
          // �I������
          _decision = true;
          // �X�^�[�gSE�Đ�
          _app.GetSoundComponent().PlayBackGround("bell", 75);
          // �W���C���A�j���ύX
          _studio->GyroChangeAnim("Gyro_Title_Start");
        }
      }
      return true;
    }

    bool ModeTitle::Process() {
      // ���[�h�폜�\�񔻒�
      PopBack();
      // ���͏���
      Input(_appMain.GetOperation());
      // �g�嗦�ݒ�
      SetExRate();
      // �X�^�W�I�X�V
      _studio->Process();
      // �I�����肳�ꂽ
      if (_decision) {
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
      DrawRotaGraph(700, 400, 0.75, 0, _titleHandle, true);
      // ��ʂɂ��؂�ւ�
      if (_sceneNum == PressAnyButtonNum) {
        DrawRotaGraph(650, 800, 1.0, 0, _pressButtonHandle, true);
      }
      else {
        DrawRotaGraph(650, 750, _gameStartExRate, 0, _gameStartHandle, true);
        DrawRotaGraph(650, 850, _creditExRate, 0, _creditHandle, true);
        DrawRotaGraph(650, 950, _quitGameExRate, 0, _quitGameHandle, true);
      }
      return true;
    }

    void ModeTitle::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �ʖ���`
      using ResourceServer = AppFrame::Resource::ResourceServer;
      // �摜���̐ݒ�
      const ResourceServer::DivGraphTable divGraphMap{
        {"title", {"res/Title/GYROtitle.png", 1, 1, 1, 1920, 1080}},  // �^�C�g��
        {"press", {"res/Title/pressbutton.png", 1, 1, 1, 721, 86}},   // �v���X�{�^��
        {"start", {"res/Title/gamestart.png", 1, 1, 1, 379, 73}},     // �Q�[���J�n
        {"credit", {"res/Title/credit.png", 1, 1, 1, 219, 73}},       // �N���W�b�g
        {"quitgame", {"res/Title/quitgame.png", 1, 1, 1, 336, 85}}    // �Q�[���I��
      };
      // ���\�[�X�T�[�o�ɓo�^
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // �ʖ���`
      using ModelServer = AppFrame::Model::ModelServer;
      // �e�탂�f���n���h���̓ǂݍ���
      const ModelServer::ModelDatas mv1Models{
        {"studio", "res/Stage/Studio_GEO.mv1"},           // �X�^�W�I
        {"player", "res/Player/Gyro Multimotion10.mv1"},  // ���@(�W���C��)
        {"sky", "res/SkySphere/skysphere.mv1"},           // �X�J�C�X�t�B�A
      };
      // ���f���T�[�o�œǂݎ����s��
      _appMain.GetModelServer().AddMV1Model(mv1Models);
      // �ʖ���`
      using SoundServer = AppFrame::Sound::SoundServer;
      // �T�E���h���̓ǂݍ���
      const SoundServer::SoundMap soundMap{
        {"title", "res/Sound/BGM/Title.mp3"},  // �^�C�g��BGM
        {"cursor", "res/Sound/SE/System/Cursor1.wav"},  // �J�[�\��SE
        {"bell", "res/Sound/SE/System/TitleStart.wav"}  // ���̉�SE
      };
      // �T�E���h�T�[�o�ɓo�^
      _appMain.GetSoundServer().AddSounds(soundMap);
      // �摜�ǂݍ���
      _titleHandle = _appMain.GetResourceServer().GetHandle("title");
      _pressButtonHandle = _appMain.GetResourceServer().GetHandle("press");
      _gameStartHandle = _appMain.GetResourceServer().GetHandle("start");
      _creditHandle = _appMain.GetResourceServer().GetHandle("credit");
      _quitGameHandle = _appMain.GetResourceServer().GetHandle("quitgame");
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeTitle::LeftStickYInput(const int leftY) {
      if (leftY == 0) {
        // �X�e�B�b�N���͂Ȃ�
        _isStick = false;
        return;
      }
      // �X�e�B�b�N���͂��ꂽ�܂܂̏ꍇ���f
      if (_isStick) {
        return;
      }
      // ���͒l�̐�������
      bool flag = 0 <= leftY;
      if (flag) {
        // ��������
        if (GameStartNum < _sceneNum) {
          // ��ʔԍ���1���炷
          _sceneNum--;
        }
      } else {
        // �������
        if (_sceneNum < QuitGameNum) {
          // ��ʔԍ���1���₷
          _sceneNum++;
        }
      }
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �J�[�\��SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround("cursor", 75);
    }

    void ModeTitle::SetExRate() {
      // �g�嗦������
      _gameStartExRate = 1.0f;
      _creditExRate = 1.0f;
      _quitGameExRate = 1.0f;
      // ��ʔԍ��̔���
      bool num1 = _sceneNum == GameStartNum;
      bool num2 = _sceneNum == CreditNum;
      bool num3 = _sceneNum == QuitGameNum;
      // ��ʔԍ�����ɂ��g��
      _gameStartExRate = num1 ? 1.25f : 1.0f;
      _creditExRate = num2 ? 1.25f : 1.0f;
      _quitGameExRate = num3 ? 1.25f : 1.0f;
    }

    void ModeTitle::ChangeMode() {
      if (_sceneNum == GameStartNum) {
        // �C���Q�[���J��
        InGame();
      }
      if (_sceneNum == CreditNum) {
        // �N���W�b�g�J��
        Credit();
      }
      // BGM�̍Đ����~����
      _appMain.GetSoundComponent().StopSound("title");
    }

    void ModeTitle::InGame() {
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("Game");
      if (!key) {
        if (GetASyncLoadNum() > 0) {
          // ���[�h���[�f�B���O�̓o�^
          _appMain.GetModeServer().AddMode("Loading", std::make_shared<Mode::ModeLoading>(_appMain));
        }
        else {
          // �񓯊������t���Ofalse
          SetUseASyncLoadFlag(false);
          // ���[�h�Q�[���̓o�^
          _appMain.GetModeServer().AddMode("Game", std::make_shared<Mode::ModeGame>(_appMain));
        }
      }
      // ���[�h�Q�[���J��
      _appMain.GetModeServer().TransionToMode("Game");
      // �����\��
      _popBack = true;
    }

    void ModeTitle::Credit() {
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("Credit");
      if (!key) {
        // ���[�h�N���W�b�g�̓o�^
        _appMain.GetModeServer().AddMode("Credit", std::make_shared<Mode::ModeCredit>(_appMain));
      }
      // ���[�h�N���W�b�g�J��
      _appMain.GetModeServer().TransionToMode("Credit");
      // �����\��
      _popBack = true;
    }
  } // namespace Mode
} // namespace Gyro