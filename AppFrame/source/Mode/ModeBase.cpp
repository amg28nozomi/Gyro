/*****************************************************************//**
 * @file   ModeBase.cpp
 * @brief  モードの基底クラスの定義
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "ModeBase.h"
#include <time.h>
#include "../Application/ApplicationBase.h"
#include "ModeServer.h"
#include "../FileServer/FileServer.h"

namespace AppFrame {
  namespace Mode {

    ModeBase::ModeBase(Application::ApplicationBase& app) : _app(app) {
    }

    ModeBase::~ModeBase() {
    }

    bool ModeBase::Init() {
      return true;
    }

    bool ModeBase::Enter() {
      return true;
    }

    bool ModeBase::Exit() {
      return true;
    }

    bool ModeBase::Input(Application::InputOperation& input) {
      return true;
    }

    bool ModeBase::Process() {
      return true;
    }

    bool ModeBase::Draw() const {
      return true;
    }

    void ModeBase::TimeClear() {
      // 経過時間の初期化
      _count = 0;
    }

    Application::ApplicationBase& ModeBase::GetApplication() {
      return _app;
    }

    ModeServer& ModeBase::GetModeServer() {
      return _app.GetModeServer();
    }

    FileServer::FileServer& ModeBase::GetFileServer() {
      return _app.GetFileServer();
    }

    void ModeBase::StepTime() {
      ++_count; // カウンタの経過
    }
  } // namespace Mode
} // namespace AppFrame