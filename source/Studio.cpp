/*****************************************************************//**
 * @file    Studio.cpp
 * @brief   モード用スタジオクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "Studio.h"
#include "UtilityDX.h"

namespace {
  // 各種定数
  namespace AppMath = AppFrame::Math;
  const AppMath::Vector4 StudioPos{ 0.0f, 0.0f, 2750.0f };        //!< スタジオ位置
  const AppMath::Vector4 GyroPos{ 250.0f, 0.0f, 300.0f };         //!< ジャイロ位置
  const AppMath::Vector4 SkyPos{ 0.0f, 0.0f, 0.0f };              //!< スカイ位置
  const AppMath::Vector4 CamPos{ 225.0f, 150.0f, 50.0f };         //!< カメラ位置
  const AppMath::Vector4 CamTarget{ 200.0f, 145.0f, 100.0f };     //!< カメラ注視点
  constexpr float AnimSpeed = 0.5f;        //!< ジャイロアニメ再生速度
  constexpr float AnimBlendFlame = 10.0f;  //!< ジャイロアニメブレンドフレーム
  constexpr float SkyAddRot = 0.0001f;     //!< スカイ回転率
}

namespace Gyro {
  namespace Studio {
    Studio::Studio(Application::ApplicationMain& app) : _app(app) {

    }

    Studio::~Studio() {
      // モデルアニメ解放
      _modelAnim.Release();
    }

    void Studio::Init() {
      _app.GetModelServer().DeleteDuplicateModels("studio", false);
      _app.GetModelServer().DeleteDuplicateModels("player", false);
      _app.GetModelServer().DeleteDuplicateModels("sky", false);
      // リソース読み込み
      LoadResource();
      // モデル配置
      LayOut();
    }

    void Studio::Release() {
      // モデルアニメ解放
      _modelAnim.Release();
    }

    void Studio::Process() {
      // スカイ回転
      _skyRot.AddY(SkyAddRot);
      MV1SetRotationXYZ(_skyHandle, UtilityDX::ToVECTOR(_skyRot));
      // モデルアニメ更新
      _modelAnim.Process();
    }

    void Studio::Draw() const {
      // モデル描画
      MV1DrawModel(_studioHandle);
      MV1DrawModel(_gyroHandle);
      MV1DrawModel(_skyHandle);
    }

    void Studio::GyroChangeAnim(const std::string_view key) {
      // ジャイロアニメ変更
      _modelAnim.SetBlendAttach(key, AnimBlendFlame, AnimSpeed, false);
    }

    void Studio::LoadResource() {
      // スタジオ読み込み
      auto [title, key1] = _app.GetModelServer().GetModel("studio", 1);
      _studioHandle = title;
      // ジャイロ読み込み
      auto [gyro, key2] = _app.GetModelServer().GetModel("player", 1);
      _gyroHandle = gyro;
      // スカイ読み込み
      auto [sky, key3] = _app.GetModelServer().GetModel("sky", 1);
      _skyHandle = sky;
    }

    void Studio::LayOut() {
      // スタジオ設定
      MV1SetPosition(_studioHandle, UtilityDX::ToVECTOR(StudioPos));
      // ジャイロ設定
      MV1SetPosition(_gyroHandle, UtilityDX::ToVECTOR(GyroPos));
      _modelAnim.SetMainAttach(_gyroHandle, "GyroTitleSleeper", AnimSpeed, true);
      // スカイ設定
      MV1SetPosition(_skyHandle, UtilityDX::ToVECTOR(SkyPos));
      // カメラ設定
      SetCameraPositionAndTarget_UpVecY(UtilityDX::ToVECTOR(CamPos), UtilityDX::ToVECTOR(CamTarget));
    }
  }
}