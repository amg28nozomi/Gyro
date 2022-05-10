/*****************************************************************//**
 * @file    Studio.cpp
 * @brief   ���[�h�p�X�^�W�I�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "Studio.h"
#include "UtilityDX.h"

namespace {
  // �e��萔
  namespace AppMath = AppFrame::Math;
  const AppMath::Vector4 StudioPos{ 0.0f, 0.0f, 2750.0f };        //!< �X�^�W�I�ʒu
  const AppMath::Vector4 GyroPos{ 250.0f, 0.0f, 300.0f };         //!< �W���C���ʒu
  const AppMath::Vector4 SkyPos{ 0.0f, 0.0f, 0.0f };              //!< �X�J�C�ʒu
  const AppMath::Vector4 CamPos{ 225.0f, 150.0f, 50.0f };         //!< �J�����ʒu
  const AppMath::Vector4 CamTarget{ 200.0f, 145.0f, 100.0f };     //!< �J���������_
  constexpr float AnimSpeed = 0.5f;        //!< �W���C���A�j���Đ����x
  constexpr float AnimBlendFlame = 10.0f;  //!< �W���C���A�j���u�����h�t���[��
  constexpr float SkyAddRot = 0.0001f;     //!< �X�J�C��]��
}

namespace Gyro {
  namespace Studio {
    Studio::Studio(Application::ApplicationMain& app) : _app(app) {

    }

    Studio::~Studio() {
      // ���f���A�j�����
      _modelAnim.Release();
    }

    void Studio::Init() {
      _app.GetModelServer().DeleteDuplicateModels("studio", false);
      _app.GetModelServer().DeleteDuplicateModels("player", false);
      _app.GetModelServer().DeleteDuplicateModels("sky", false);
      // ���\�[�X�ǂݍ���
      LoadResource();
      // ���f���z�u
      LayOut();
    }

    void Studio::Release() {
      // ���f���A�j�����
      _modelAnim.Release();
    }

    void Studio::Process() {
      // �X�J�C��]
      _skyRot.AddY(SkyAddRot);
      MV1SetRotationXYZ(_skyHandle, UtilityDX::ToVECTOR(_skyRot));
      // ���f���A�j���X�V
      _modelAnim.Process();
    }

    void Studio::Draw() const {
      // ���f���`��
      MV1DrawModel(_studioHandle);
      MV1DrawModel(_gyroHandle);
      MV1DrawModel(_skyHandle);
    }

    void Studio::GyroChangeAnim(const std::string_view key) {
      // �W���C���A�j���ύX
      _modelAnim.SetBlendAttach(key, AnimBlendFlame, AnimSpeed, false);
    }

    void Studio::LoadResource() {
      // �X�^�W�I�ǂݍ���
      auto [title, key1] = _app.GetModelServer().GetModel("studio", 1);
      _studioHandle = title;
      // �W���C���ǂݍ���
      auto [gyro, key2] = _app.GetModelServer().GetModel("player", 1);
      _gyroHandle = gyro;
      // �X�J�C�ǂݍ���
      auto [sky, key3] = _app.GetModelServer().GetModel("sky", 1);
      _skyHandle = sky;
    }

    void Studio::LayOut() {
      // �X�^�W�I�ݒ�
      MV1SetPosition(_studioHandle, UtilityDX::ToVECTOR(StudioPos));
      // �W���C���ݒ�
      MV1SetPosition(_gyroHandle, UtilityDX::ToVECTOR(GyroPos));
      _modelAnim.SetMainAttach(_gyroHandle, "GyroTitleSleeper", AnimSpeed, true);
      // �X�J�C�ݒ�
      MV1SetPosition(_skyHandle, UtilityDX::ToVECTOR(SkyPos));
      // �J�����ݒ�
      SetCameraPositionAndTarget_UpVecY(UtilityDX::ToVECTOR(CamPos), UtilityDX::ToVECTOR(CamTarget));
    }
  }
}