/*****************************************************************//**
 * @file    ModeTitle.cpp
 * @brief   ���[�h�^�C�g���N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "UtilityDX.h"
#include "ModeGame.h"
#include "ModeCredit.h"
#include "ModeLoading.h"

namespace {
  constexpr int BgmVolume = 50;      //!< BGM�̍Đ��{�����[��
  // ��ʐ؂�ւ��萔
  constexpr int PressAnyButtonNum = 0;  //!< �v���X�{�^��
  constexpr int GameStartNum = 1;       //!< �Q�[���J�n
  //constexpr int CreditNum = 2;          //!< �N���W�b�g
  constexpr int QuitGameNum = 2;        //!< �Q�[���I��
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
      // �ϐ�������
      _sceneNum = PressAnyButtonNum;
      _isStick = false;
      _decision = false;
      // �X�^�W�I������
      _studio->Init();
      // BGM�̍Đ��J�n
      _appMain.GetSoundComponent().PlayLoop("title");
      // �Đ����ʂ̐ݒ�
      _appMain.GetSoundComponent().SetVolume("title", BgmVolume);
      return true;
    }

    bool ModeTitle::Exit() {
      // �X�^�W�I���
      _studio->Release();
      return true;
    }

    bool ModeTitle::Input(AppFrame::Application::InputOperation& input) {
      // ���͏�Ԃ̎擾
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // ��ʔ���
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
          if (_sceneNum == QuitGameNum) {
            // ��ʔԍ����Q�[���I��
            // �A�v���P�[�V�����̏I���������Ăяo��
            _appMain.RequestTerminate();
            return true;
          }
          // �I������
          _decision = true;
          // �X�^�[�gSE�Đ�
          _app.GetSoundComponent().PlayBackGround("start", 50);
          // �W���C���A�j���ύX
          _studio->GyroChangeAnim("Gyro_Title_Start");
        }
      }
      return true;
    }

    bool ModeTitle::Process() {
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
        //DrawRotaGraph(650, 850, _creditExRate, 0, _creditHandle, true);
        DrawRotaGraph(650, 950, _quitGameExRate, 0, _quitGameHandle, true);
      }
      return true;
    }

    void ModeTitle::LoadResource() {
      // ���\�[�X�̓ǂݍ��݂͍s���Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // �摜�ǂݍ���
      _titleHandle = LoadGraph("res/Title/GYROtitle.png");
      _pressButtonHandle = LoadGraph("res/Title/pressbutton.png");
      _gameStartHandle = LoadGraph("res/Title/gamestart.png");
      _creditHandle = LoadGraph("res/Title/credit.png");
      _quitGameHandle = LoadGraph("res/Title/quitgame.png");
      // �e�탂�f���n���h���̓ǂݍ���
      using ModelServer = AppFrame::Model::ModelServer;
      const ModelServer::ModelDatas mv1Models{
        {"studio", "res/Stage/Studio_GEO.mv1"},           // �X�^�W�I
        {"player", "res/Player/Gyro Multimotion10.mv1"},  // ���@(�W���C��)
        {"sky", "res/SkySphere/skysphere.mv1"},           // �X�J�C�X�t�B�A
      };
      // ���f���T�[�o�œǂݎ����s��
      _appMain.GetModelServer().AddMV1Model(mv1Models);
      // �T�E���h���̓ǂݍ���
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"title", "res/Sound/BGM/Title.mp3"},  // �^�C�g��BGM
        {"cursor", "res/Sound/SE/System/Cursor1.wav"},   // �J�[�\��SE
        {"start", "res/Sound/SE/System/TitleStart.wav"}  // �X�^�[�gSE
      };
      // �T�E���h�T�[�o�ɓo�^
      _appMain.GetSoundServer().AddSounds(soundMap);
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
      if (0 < leftY) {
        // �X�e�B�b�N����͂���
        _isStick = true;
        // �J�[�\��SE�Đ�
        _app.GetSoundComponent().PlayBackGround("cursor", 50);
        // ��ʔԍ���1���炷
        _sceneNum--;
        if (_sceneNum < GameStartNum) {
          // ��������
          _sceneNum = GameStartNum;
        }
      }
      else if (leftY < 0) {
        // �X�e�B�b�N�����͂���
        _isStick = true;
        // �J�[�\��SE�Đ�
        _app.GetSoundComponent().PlayBackGround("cursor", 50);
        // ��ʔԍ���1���₷
        _sceneNum++;
        if (QuitGameNum < _sceneNum) {
          // �������
          _sceneNum = QuitGameNum;
        }
      }
    }

    void ModeTitle::SetExRate() {
      // �g�嗦������
      _gameStartExRate = 1.0f;
      _creditExRate = 1.0f;
      _quitGameExRate = 1.0f;
      // ��ʂɂ��؂�ւ�
      switch (_sceneNum) {
      case GameStartNum:
        // �Q�[���J�n�g��
        _gameStartExRate = 1.25f;
        break;
      //case CreditNum:
      //  // �N���W�b�g�g��
      //  _creditExRate = 1.25f;
      //  break;
      case QuitGameNum:
        // �Q�[���I���g��
        _quitGameExRate = 1.25f;
        break;
      default:
        break;
      }
    }

    void ModeTitle::ChangeMode() {
      // ���[�h�^�C�g���̍폜
      _appMain.GetModeServer().PopBuck();
      if (_sceneNum == GameStartNum) {
        // �C���Q�[���J��
        InGame();
      }
      //else if (_sceneNum == CreditNum) {
      //  // �N���W�b�g�J��
      //  Credit();
      //}
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
    }
  } // namespace Mode
} // namespace Gyro