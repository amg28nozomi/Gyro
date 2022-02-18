/*****************************************************************//**
 * @file   Camera.cpp
 * @brief  カメラクラスの処理
 *
 * @author amg
 * @date   January 2022
 *********************************************************************/
#include "Camera.h"
#include "ApplicationMain.h"
#include "UtilityDX.h"

namespace {
    constexpr auto Near = 2.0f;             //!< 手前クリップ距離
    constexpr auto Far = 10000.0f;          //!< 奥クリップ距離
    constexpr auto InputMin = 2000.0f;      //!< 入力を受け付ける最低値
    constexpr auto Pi = 3.141596535897932f; //!< 円周率
    constexpr auto Rad2Deg = 180.0f / Pi;   //!< 
}

namespace Gyro {
    namespace Camera {

        Camera::Camera() {
          Init();
        }

        bool Camera::Init() {
          SetState(); // 初期設定
          return true;
        }

        bool Camera::Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move) {
          auto s = _position - target;
          float radian = atan2(s.GetZ(), s.GetX());
          float length = sqrt(s.GetZ() * s.GetZ() + s.GetX() * s.GetX());
          if (stick.GetX() > InputMin) { radian -= 0.1f; }
          if (stick.GetX() < -InputMin) { radian += 0.1f; }
          // x,z位置
          auto x = target.GetX() + move.GetX() + cos(radian) * length;
          _position.SetX(x);
          auto z = target.GetZ() + move.GetZ() + sin(radian) * length;
          _position.SetZ(z);
          // y位置
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
          // 座標の設定
          _target.Set(target);
          // VECTOR position(_position.GetX(), _position.GetY(), _position.GetZ());
          // VECTOR target(target.GetX(), target.GetY(), target.GetZ());
          //カメラの位置更新
          SetCameraPositionAndTarget_UpVecY(UtilityDX::ToVECTOR(_position), UtilityDX::ToVECTOR(target));

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
          // カメラの初期化
          namespace AppMath = AppFrame::Math;
          _position = AppMath::Vector4(0.0f, 120.0f, -500.0f, 1.0f);
          _target = AppMath::Vector4(0.0f, 80.0f, 0.0f, 1.0f);
          SetCameraNearFar(Near, Far);
        }
    }// namespace Camera
}// namespace Gyro
