/*****************************************************************//**
 * @file   Camera.cpp
 * @brief  �J�����N���X�̏���
 *
 * @author �y�� ����
 * @date   January 2022
 *********************************************************************/
#include "Camera.h"
#include "ApplicationMain.h"
#include "UtilityDX.h"

namespace {
  constexpr auto Near = 2.0f;             //!< ��O�N���b�v����
  constexpr auto Far = 20000.0f;          //!< ���N���b�v����
  constexpr auto InputMin = 2000.0f;      //!< ���͂��󂯕t����Œ�l
}

namespace Gyro {
  namespace Camera {

    Camera::Camera() {
      Init();
    }

    Camera::~Camera() {

    }

    bool Camera::Init() {
      SetState(); // �����ݒ�

      return true;
    }

    bool Camera::Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move) {
      // ��Ԃ����ď����ύX
      switch (_cameraState) {
      case CameraState::Normal:
        Normal(stick, target, move);
      case CameraState::SpecialMove:
        Special(target, move);
      }
      
      return true;
    }

#ifdef _DEBUG
    bool Camera::Draw(const AppFrame::Math::Vector4 positoin, const AppFrame::Math::Vector4 move) const {
      int x = 0, y = 80, size = 16;
      SetFontSize(size);
      DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
      DrawFormatString(x, y, GetColor(255, 0, 0), " target = (%5.2f, %5.2f, %5.2f)", positoin.GetX(), positoin.GetY(), positoin.GetZ()); y += size;
      DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _position.GetX(), _position.GetY(), _position.GetZ());; y += size;
      float sx = _position.GetX() - positoin.GetX();
      float sz = _position.GetZ() - positoin.GetZ();
      float radian = atan2(sz, sx);
      float length = sqrt(sz * sz + sx * sx);
      float degree = AppFrame::Math::Utility::RadianToDegree(radian);
      DrawFormatString(x, y, GetColor(255, 0, 0), " length = %5.2f, radian = %5.2f, degree = %5.2f", length, radian, degree); y += size;

      return true;
    }
#endif // _DEBUG

    void Camera::SetState() {
      // �J�����̏�����
      namespace AppMath = AppFrame::Math;
      _position = AppMath::Vector4(0.0f, 120.0f, 2300.0f, 1.0f);
      _target = AppMath::Vector4(0.0f, 80.0f, 0.0f, 1.0f);
      SetCameraNearFar(Near, Far);
    }

    void Camera::Normal(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move) {
      // �^�[�Q�b�g���W�܂ł̌������Z�o
      auto direction = target.Direction(_position);
      // �����x�N�g���̊e�������擾
      auto [dX, dY, dZ] = direction.GetVector3();
      // ��������Ɋp�x�ƒ������Z�o
      auto radian = atan2(dZ, dX);
      auto length = AppFrame::Math::Arithmetic::Length(dZ, dX);
      // X���̓��͋�ɉ����Č�������
      if (stick.GetX() > InputMin) { radian -= 0.1f; }
      if (stick.GetX() < -InputMin) { radian += 0.1f; }
      // x,z�ʒu
      auto x = target.GetX() + move.GetX() + cos(radian) * length;
      _position.SetX(x);
      auto z = target.GetZ() + move.GetZ() + sin(radian) * length;
      _position.SetZ(z);
      // y�ʒu
      if (stick.GetY() > InputMin) {
        auto py = _position.GetY() - 4.0f;
        _position.SetY(py);
      }
      if (stick.GetY() < -InputMin) {
        auto my = _position.GetY() + 4.0f;
        _position.SetY(my);
      }
      if (_target.GetY() > target.GetY()) {
        auto a = _target.GetY() - target.GetY();
        auto py = _position.GetY() - a;
        _position.SetY(py);
      }
      if (_target.GetY() < target.GetY()) {
        auto a = target.GetY() - _target.GetY();
        auto my = _position.GetY() + a;
        _position.SetY(my);
      }
      // ���W�̐ݒ�
      _target.Set(target);
      // �኱�����_����ɂ���
      AppFrame::Math::Vector4 tar = _target.AddVectorY(75.f);
      //�J�����̈ʒu�X�V
      SetCameraPositionAndTarget_UpVecY(UtilityDX::ToVECTOR(_position), UtilityDX::ToVECTOR(tar));
    }

    void Camera::Special(const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move) {
        
    }
  }// namespace Camera
}// namespace Gyro
