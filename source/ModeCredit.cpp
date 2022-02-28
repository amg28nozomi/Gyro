/*****************************************************************//**
 * @file    ModeCredit.cpp
 * @brief   モードクレジットクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeCredit.h"

namespace Gyro {
  namespace Mode {
    ModeCredit::ModeCredit(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeCredit::~ModeCredit() {

    }

    bool ModeCredit::Init() {
      // リソース読み込み
      LoadResource();
      return true;
    }

    bool ModeCredit::Enter() {
      return true;
    }

    bool ModeCredit::Exit() {
      return true;
    }

    bool ModeCredit::Input(AppFrame::Application::InputOperation& input) {
      return true;
    }

    bool ModeCredit::Process() {
      return true;
    }

    bool ModeCredit::Draw() const {
      return true;
    }

    void ModeCredit::LoadResource() {

    }

    void ModeCredit::ChangeMode() {

    }
  }
}