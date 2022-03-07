/*****************************************************************//**
 * @file   Light.cpp
 * @brief  ���[�h�Q�[�����̃��C�g�N���X
 * 
 * @author �y������
 * @date   March 2022
 *********************************************************************/
#include "Light.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Light {

    Light::Light() {
      Init();
    }

    Light::~Light() {
      // ���C�g���f�t�H���g�ɖ߂�
      DeleteLightHandleAll();
      SetLightEnable(true);
    }

    void Light::Init() {
      namespace AppMath = AppFrame::Math;
      // ���C�g�̐ݒ�
      AppMath::Vector4 light_dir = AppMath::Vector4(-1.0f, -1.0f, -1.0f);
      auto light_handle = CreateDirLightHandle(UtilityDX::ToVECTOR(light_dir));
      AppMath::Vector4 left_dir = AppMath::Vector4(1.0f, -1.0f, 1.0f);
      auto left_handle = CreateDirLightHandle(UtilityDX::ToVECTOR(left_dir));
      SetLightEnable(false);
    }

    void Light::Process() {
    }

    void Light::Draw() const {
    }
  }
}
