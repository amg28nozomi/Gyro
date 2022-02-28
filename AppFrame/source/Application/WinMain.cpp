/*****************************************************************//**
 * @file   WinMain.cpp
 * @brief  �v���O�����̃G���g���[�|�C���g
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ApplicationBase.h"
#include <DxLib.h>

/**
 * @brief  �v���O�����̃G���g���[�|�C���g
 * @return 0:����I�� -1:�ُ�I��
 */
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
  namespace App = AppFrame::Application;
  // �A�v���P�[�V�����̎��̂��擾
  auto app = App::ApplicationBase::GetInstance();
  // �A�v���P�[�V�����̎��̔���
  if (app == nullptr) {
    return -1; // �A�v���P�[�V�����̐������s���Ă��Ȃ�
  }
#ifndef _DEBUG
  // �������ɐ��������ꍇ�̂݃Q�[���Ɉڍs
  if (app->Init()) {
    app->Run(); // �Q�[�����[�v
  }
#else
  try {
    // �������ɐ��������ꍇ�̂݃Q�[���Ɉڍs
    if (app->Init()) {
      app->Run(); // �Q�[�����[�v
    }
  }
  // ��O��catch�����ꍇ�̓v���O�������I������
  catch (std::logic_error error) {
    // ����������O�����O�ɏo�͂���
    OutputDebugString(error.what());
  }
#endif
  // �A�v���P�[�V�����I��
  app->Terminate();
  return 0;
}