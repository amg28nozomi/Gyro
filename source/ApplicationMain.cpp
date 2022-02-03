/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�����x�[�X�̃T�u�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "appframe.h"
#include <DxLib.h>
#include "ObjectServer.h"
#include "ModeGame.h"

namespace Gyro {
  namespace Application {
    // �A�v���P�[�V�����̎���
    ApplicationMain application;
    
    ApplicationMain::ApplicationMain() : ApplicationBase() {
      // ���̂̓o�^���s����
      if (SetInstance()) {
        // ���̍쐬
        _instance = std::make_shared<ApplicationMain>();
      }
    }

    bool ApplicationMain::Init() {
      if (!ApplicationBase::Init()) {
        return false; // ���������s
      }
      // Effekseer�̐ݒ�
      if (!Effekseer()) {
          return false; // �ݒ莸�s
      }
      // �I�u�W�F�N�g�T�[�o�̐���
      _objectServer = std::make_unique<Object::ObjectServer>();
      _objectServer->Init();
      // �J�����̐���
      _camera = std::make_unique<Camera::Camera>();
      _camera->Init();
      // ���[�h�Q�[���̓o�^
      _modeServer->AddMode("Game", std::make_shared<Mode::ModeGame>(*this));
      _modeServer->TransionToMode("Game");
      return true;
    }

    bool ApplicationMain::Input() {
      auto flag = ApplicationBase::Input();
      // ���͏�Ԃ̎擾
      //auto state = _input->GetJoypadState();
      //// �Q�[�����I�����邩�̔���
      //if (state.GetKey() & PAD_INPUT_1) {
      //  _state = State::Quit;
      //  return true;
      //}
      return flag;
    }

    void ApplicationMain::Terminate() {
        // Effekseer���I������B
        Effkseer_End();
    }

    bool ApplicationMain::Process() {
      return ApplicationBase::Process();
    }

    bool ApplicationMain::Effekseer() {
        //DirectX11���g�p
        SetUseDirect3DVersion(DX_DIRECT3D_11);
        //Effekseer�̏�����
        //�����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ�
        if (Effekseer_Init(8000) == -1) {
            return false;
        }
        //�t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
        SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
        //DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ�
        Effekseer_SetGraphicsDeviceLostCallbackFunctions();
        return true;
    }
  } // namespace Application
} // namespace Gyro