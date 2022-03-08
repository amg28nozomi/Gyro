/*****************************************************************//**
 * @file   Shadow.cpp
 * @brief  ���[�h�Q�[�����̃V���h�E�N���X
 * 
 * @author �y������
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
      // �V���h�E�}�b�v���쐬
      _shadowHandle = MakeShadowMap(ShadowMapSize, ShadowMapSize);
      namespace AppMath = AppFrame::Math;
      auto shadowDir = AppMath::Vector4(-0.5f, -1.0f, -0.5f);
      // �V���h�E�̌����ݒ�
      SetShadowMapLightDirection(_shadowHandle, UtilityDX::ToVECTOR(shadowDir));
      // �V���h�E�}�b�v�̉e���͈͂�ݒ�
      auto shadowMinArea = AppMath::Vector4(-1200.0f, -1.0f, -16000.0f);
      auto shadowMaxArea = AppMath::Vector4(6000.0f, 1000.0f, 1000.0f);
      SetShadowMapDrawArea(_shadowHandle, UtilityDX::ToVECTOR(shadowMinArea), UtilityDX::ToVECTOR(shadowMaxArea));
    }

    void Shadow::Process() {
    }

    void Shadow::Draw() const {
      // �V���h�E�}�b�v�̕`����s��
      ShadowMap_DrawSetup(_shadowHandle);
      // �e��`�揈��
      _appMain.GetObjectServer().Draw();
      // �V���h�E�}�b�v�̕`����I������
      ShadowMap_DrawEnd();
      // �g�p����V���h�E�}�b�v�n���h���̐ݒ�
      SetUseShadowMap(0, _shadowHandle);
    }
  } // namespace Shadow
} // namespace Gyro