/*****************************************************************//**
 * @file   ModeLoading.cpp
 * @brief  ���[�h���[�f�B���O�N���X
 * 
 * @author �y������
 * @date   March 2022
 *********************************************************************/
#include "ModeLoading.h"
#include "ModeGame.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeLoading::ModeLoading(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeLoading::~ModeLoading() {

    }

    bool ModeLoading::Init() {
      return true;
    }

    bool ModeLoading::Enter() {
      // ���\�[�X�ǂݍ���
      LoadResource();
      return true;
    }

    bool ModeLoading::Exit() {
      // �񓯊������t���Ofalse
      SetUseASyncLoadFlag(false);
      return true;
    }

    bool ModeLoading::Process() {
      _cnt++;
      // �񓯊��̐���0�Ȃ�Game�ֈڍs
      if (GetASyncLoadNum() == 0) {
        ChangeMode();
      }
      return true;
    }

    bool ModeLoading::Draw() const {
      // ���F�̐ݒ�
      auto black = GetColor(0, 0, 0);
      // �w�i������
      DrawBox(0, 0, 1920, 1080, black, true);
      // ���[�f�B���O�摜�̕`��
      DrawGraph(1400, 950, _loadHandle[_cnt / 10 % 4], true);
      return true;
    }

    void ModeLoading::LoadResource() {
      // ���\�[�X�͓ǂݍ��܂�Ă��邩
      if (_isLoad) {
        return; // �ǂݍ��ݍς�
      }
      // ���[�h�摜�ǂݍ���
      LoadDivGraph("res/Loading/Loading2.png", 4, 2, 2, 500, 100, _loadHandle);
      _isLoad = true;
    }

    void ModeLoading::ChangeMode() {
      // ���[�h���[�f�B���O�̍폜
      _appMain.GetModeServer().PopBuck();
      // �L�[���o�^����Ă��邩
      bool key = _app.GetModeServer().Contains("Game");
      if (!key) {
        // ���[�h�Q�[���̓o�^
        _appMain.GetModeServer().AddMode("Game", std::make_shared<Mode::ModeGame>(_appMain));
      }
      // ���[�h�Q�[���J��
      _appMain.GetModeServer().TransionToMode("Game");
    }
  } // namespace Mode
} // namespace Gyro