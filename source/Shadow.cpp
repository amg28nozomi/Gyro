/*****************************************************************//**
 * @file   Shadow.cpp
 * @brief  モードゲーム時のシャドウクラス
 * 
 * @author 土橋峡介
 * @date   March 2022
 *********************************************************************/
#include "Shadow.h"
#include "UtilityDX.h"
#include "ObjectServer.h"

namespace {
  constexpr auto ShadowMapSize = 16384;
}

namespace Gyro {
  namespace Shadow {

    Shadow::Shadow(Application::ApplicationMain& app) : _appMain(app) {
      Init();
    }

    Shadow::~Shadow() {
      DeleteShadowMap(_shadowHandle);
    }

    void Shadow::Init() {
      // シャドウマップを作成
      _shadowHandle = MakeShadowMap(ShadowMapSize, ShadowMapSize);
      namespace AppMath = AppFrame::Math;
      auto shadowDir = AppMath::Vector4(-0.5f, -1.0f, -0.5f);
      // シャドウの向き設定
      SetShadowMapLightDirection(_shadowHandle, UtilityDX::ToVECTOR(shadowDir));
      // シャドウマップの影響範囲を設定
      auto shadowMinArea = AppMath::Vector4(-1200.0f, -1.0f, -16000.0f);
      auto shadowMaxArea = AppMath::Vector4(6000.0f, 1000.0f, 1000.0f);
      SetShadowMapDrawArea(_shadowHandle, UtilityDX::ToVECTOR(shadowMinArea), UtilityDX::ToVECTOR(shadowMaxArea));
    }

    void Shadow::Process() {
    }

    void Shadow::Draw() const {
      // シャドウマップの描画を行う
      ShadowMap_DrawSetup(_shadowHandle);
      // 各種描画処理
      _appMain.GetObjectServer().Draw();
      // シャドウマップの描画を終了する
      ShadowMap_DrawEnd();
      // 使用するシャドウマップハンドルの設定
      SetUseShadowMap(0, _shadowHandle);
    }
  } // namespace Shadow
} // namespace Gyro