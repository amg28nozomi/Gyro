/*****************************************************************//**
 * @file   ModeFadeIn.cpp
 * @brief  モードフェードのサブクラス
 *         フェードイン処理を行う
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeFadeIn.h"
#include "../Application/ApplicationBase.h"

namespace AppFrame{
  namespace Mode {

    ModeFadeIn::ModeFadeIn(Application::ApplicationBase& app, const Data::Color color) : ModeFade(app, color) {
    }

    bool ModeFadeIn::Enter() {
      // 各種パラメータの初期化
      _alpha = AlphaMax;
      _deltaAlpha = AlphaDelta;
      return true;
    }

    bool ModeFadeIn::Process() {
      // アルファ値の減算
      _alpha -= _deltaAlpha;
      return ModeFade::Process();
    }

    bool ModeFadeIn::IsFinish() {
      // アルファ値は下限以下か
      return _alpha <= AlphaMin;
    }
  } // namespace Mode
} // namespace AppFrame