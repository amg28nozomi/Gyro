/*****************************************************************//**
 * @file   ModeFadeOut.cpp
 * @brief  モードフェードのサブクラス
 *         フェードアウト処理を行う
 * 
 * @date   January 2022
 *********************************************************************/
#include "ModeFadeOut.h"
#include "../Application/ApplicationBase.h"

namespace AppFrame {
  namespace Mode {

    ModeFadeOut::ModeFadeOut(Application::ApplicationBase& app, const Data::Color color) : ModeFade(app, color) {
    }

    bool ModeFadeOut::Enter() {
      // 各種パラメータの初期化
      _alpha = AlphaMin;
      _deltaAlpha = AlphaDelta;
      return true;
    }

    bool ModeFadeOut::Process() {
      // アルファ値の加算
      _alpha += _deltaAlpha;
      return ModeFade::Process();
    }

    bool ModeFadeOut::IsFinish() {
      // アルファ値は上限以上になっているか
      return AlphaMax <= _alpha;
    }
  } // namespace Mode
} // namespace AppFrame