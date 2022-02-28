/*****************************************************************//**
 * @file   ApplicationBase.cpp
 * @brief  �A�v���P�[�V�����̃X�[�p�[�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "ApplicationBase.h"
#include <string>
#include <algorithm>
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <unordered_map>
#include "InputOperation.h"
#include "../FileServer/FileServer.h"
#include "../FileServer/FileBase.h"
#include "../Mode/ModeBase.h"
#include "../Mode/ModeFadeIn.h"
#include "../Resource/ResourceServer.h"
#include "../Model/ModelServer.h"

namespace {
  constexpr auto InitError = -1;   // ���������s
} // namespace

namespace AppFrame {
  namespace Application {

    /**
     * @brief �E�B���h�E�����L�[�Ƃ��āA��ʃT�C�Y����pair�^�ŕێ�����A�z�z��
     */
    const std::unordered_map<ApplicationBase::WindowType, std::pair<int, int>> WindowMap{
      // �f�t�H���g�̉�ʃT�C�Y���
      {ApplicationBase::WindowType::Default, {1920, 1080}}
    };

    ApplicationBase::ApplicationBase() {
      _particleMax = 4000;
#ifndef _DEBUG
      _windowMode = false;
#else
      _windowMode = true;
#endif
    }

    ApplicationBase::~ApplicationBase() {
    }

    bool ApplicationBase::SetInstance() {
      // ���̂��o�^����Ă��邩�̔���
      if (!_setInstance) {
        if (_instance == nullptr) {
          _setInstance = true;
          return true; // �o�^���s��
        }
      }
      return false; // �o�^�ς�
    }

    bool ApplicationBase::Init() {
      // ���O�t�@�C���̏o�͂��s�����̐ݒ�
      SetOutApplicationLogValidFlag(_windowMode);
      // ��ʃ��[�h�̐ݒ�
      SetWindowSize(_windowType);
      // �E�B���h�E���[�h�̐ݒ�
      ChangeWindowMode(_windowMode);
      // DX���C�u�����̏�����
      if (DxLib::DxLib_Init() == InitError) {
#ifdef _DEBUG
        throw std::logic_error("ApplicationBase:DX���C�u�����̏������Ɏ��s���܂���\n");
#endif
        return false; // ���������s
      }
      // �w�i�F�̐ݒ�
      SetBackgroundColor(0, 0, 255);
      SetDrawScreen(DX_SCREEN_BACK);
      // Z�o�b�t�@�̐ݒ�
      SetZBuffer();
      // �t�@�C���T�[�o�̐���
      _fileServer = std::make_unique<FileServer::FileServer>(*this);
      // �C���v�b�g�I�y���[�V�����̐���
      _input = std::make_unique<InputOperation>(*this);
      // ���[�h�T�[�o�̐���
      _modeServer = std::make_unique<Mode::ModeServer>(*this);
      // ���\�[�X�T�[�o�̐���
      _resourceServer = std::make_unique<Resource::ResourceServer>();
      // �T�E���h�T�[�o�̐���
      _soundServer = std::make_unique<Sound::SoundServer>();
      // �T�E���h�R���|�[�l���g�̐���
      _soundComponent = std::make_unique<Sound::SoundComponent>(*this);
      // ���f���T�[�o�̐���
      _modelServer = std::make_unique<Model::ModelServer>();
#ifndef _DEBUG
      if (!_fileServer->Init()) {
        return false; // ���������s
      }
#else
      try {
        // �t�@�C���T�[�o�̏�����
        // �������Ɏ��s�����ꍇ�͑Ή������G���[�𔭎�
        _fileServer->Init();
      }
      catch (std::logic_error error) {
        OutputDebugString(error.what());
        return false; // ���������s
      }
#endif
      // ���f���T�[�o������
      _modelServer->Init();
      return true; // ����������
    }

    void ApplicationBase::Release() {
      DxLib_End();
    }

    void ApplicationBase::Run() {
      // ���C�����[�v
      while (_state != State::Quit) {
#ifndef _DEBUG
        Input();   // ����
        Process(); // �X�V
        Draw();    // �`��
#else
        try {
          Input();   // ����
          Process(); // �X�V
          Draw();    // �`��
        } catch (std::logic_error error) {
          // ��O�������A�o�͂��s��
          OutputDebugString(error.what());
        }
#endif
      }
    }

    bool ApplicationBase::Input() {
      IsQuit();          // �I������
      _input->Process(); // ���͏�Ԃ̍X�V
      return true;
    }

    bool ApplicationBase::Process() {
      // ���[�h�T�[�o�̍X�V���������s
      _modeServer->Process();
      return true;
    }

    bool ApplicationBase::Draw() {
      ClearDrawScreen();   // ��ʂ��N���A
      _modeServer->Draw(); // ���[�h�T�[�o�̕`�揈�����s
      ScreenFlip();        // ����ʂ̓��e��\��ʂɔ��f
      return true;
    }

    void ApplicationBase::Terminate() {
      // DX���C�u�����̏I��
      DxLib_End();
    }

    void ApplicationBase::RequestTerminate() {
      // �A�v���P�[�V�������I����Ԃł͂Ȃ��ꍇ
      if (_state != State::Quit) {
        _state = State::Quit;
      }
    }

    void ApplicationBase::SetWindowSize(const WindowType& window, bool bit) {
      // ��ʃT�C�Y�̎擾
      auto [width, height] = WindowSize();
      // �擾�����T�C�Y����o�^����
      _width = width;
      _height = height;
      // �J���[�r�b�g���̐ݒ�
      _colorBit = ColorBit(bit);
      // ��ʃ��[�h�̕ύX
      SetGraphMode(_width, _height, _colorBit);
    }

    int ApplicationBase::ColorBit(const bool bit) const {
      // bit�t���O�ɉ������l��Ԃ�
      if (bit) {
        return BitColor32;
      }
      return BitColor16;
    }

    std::pair<int, int> ApplicationBase::WindowSize() const {
      // ���݂̃E�B���h�E�^�C�v�ɑΉ������ʃT�C�Y��Ԃ�
      return WindowMap.at(_windowType);
    }

    void ApplicationBase::SetZBuffer(bool flag) {
      // Z�o�b�t�@���g�p���邩�̐ݒ�
      SetUseZBuffer3D(flag);
      SetWriteZBuffer3D(flag);
    }

    void ApplicationBase::IsQuit() {
      // ���b�Z�[�W���[�v�Ɏ��s�����ꍇ�͏I��
      if (ProcessMessage() == Error) {
        _state = State::Quit; // �I����ԂɑJ��
      }
    }

    Resource::ResourceServer& ApplicationBase::GetResourceServer() {
      return *_resourceServer;
    }

    Sound::SoundComponent& ApplicationBase::GetSoundComponent() {
      return *_soundComponent;
    }

    Model::ModelServer& ApplicationBase::GetModelServer() const {
      return *_modelServer;
    }
  } // namespace Application
} // namespace AppFrame