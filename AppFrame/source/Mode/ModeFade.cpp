/*****************************************************************//**
 * @file   ModeFade.cpp
 * @brief  モードベースのサブクラスの定義
 *         シーン遷移時のフェード処理を行う
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeFade.h"
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <DxLib.h>
#include "../Application/ApplicationBase.h"
#include "../Math/Arithmetic.h"

namespace AppFrame{
  namespace Mode {

    ModeFade::ModeFade(Application::ApplicationBase& app, const Data::Color color) : ModeBase(app) {
      // カラー値の設定
      _basic = color;
      _color = _basic;
      // ウィンドウサイズの取得
      auto [width, height] = app.GetWindowSize();
      // ボックスサイズをウィンドウサイズと同じに設定
      _width = width;
      _height = height;
    }

    ModeFade::~ModeFade() {
    }

    bool ModeFade::Init() {
      _color = _basic;
      return true;
    }

    bool ModeFade::Enter() {
      return true;
    }

    bool ModeFade::Process() {
      // フェードイン処理の終了判定
      if (IsFinish()) {
        // 自身を削除する
        _app.GetModeServer().PopBuck();
        return true;
      }
      return false;
    }

    bool ModeFade::Draw() const {
      // ブレンドモードの切り替え
      SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
      // フェード処理用のボックスを描画
      DrawBox(0, 0, _width, _height, _color.GetColorCode(), TRUE);
      // ブレンドモードをノーマルに戻す
      SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
      return true;
    }

    void ModeFade::SetColor(const Data::Color color) {
      // 現在のRGB情報を変更する
      _basic = color;
    }

    void ModeFade::SetDeltaAlpha(const float value) {
      // 値が範囲内に収まっていない場合は処理を実行しない
      if (!Math::Arithmetic::IsRange(value, AlphaMin, AlphaMax)) {
#ifdef _DEBUG
        throw std::logic_error("ModeFade:対象の値が範囲内に収まっていません\n");
#endif
        return; // 設定を行わない
      }
      // 問題がない場合は代入
      _deltaAlpha = value;
    }

    bool ModeFade::IsFinish() {
      return false;
    }
  } // namespace Mode
} // namespace AppFrame