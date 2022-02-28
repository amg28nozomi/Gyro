/*****************************************************************//**
 * @file   WinMain.cpp
 * @brief  プログラムのエントリーポイント
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ApplicationBase.h"
#include <DxLib.h>

/**
 * @brief  プログラムのエントリーポイント
 * @return 0:正常終了 -1:異常終了
 */
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
  namespace App = AppFrame::Application;
  // アプリケーションの実体を取得
  auto app = App::ApplicationBase::GetInstance();
  // アプリケーションの実体判定
  if (app == nullptr) {
    return -1; // アプリケーションの生成が行われていない
  }
#ifndef _DEBUG
  // 初期化に成功した場合のみゲームに移行
  if (app->Init()) {
    app->Run(); // ゲームループ
  }
#else
  try {
    // 初期化に成功した場合のみゲームに移行
    if (app->Init()) {
      app->Run(); // ゲームループ
    }
  }
  // 例外をcatchした場合はプログラムを終了する
  catch (std::logic_error error) {
    // 発生した例外をログに出力する
    OutputDebugString(error.what());
  }
#endif
  // アプリケーション終了
  app->Terminate();
  return 0;
}