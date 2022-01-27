/*****************************************************************//**
 * @file   Camera.cpp
 * @brief  �J�����N���X�̏���
 *
 * @author amg
 * @date   January 2022
 *********************************************************************/
#include "Camera.h"
#include "ApplicationMain.h"

namespace {
    constexpr auto Near = 2.0f;             //!< ��O�N���b�v����
    constexpr auto Far = 10000.0f;           //!< ���N���b�v����
    constexpr auto InputMin = 2000.0f;      //!< ���͂��󂯕t����Œ�l
    constexpr auto Pi = 3.141596535897932f; //!< �~����
    constexpr auto Rad2Deg = 180.0f / Pi;   //!< 
}

namespace Gyro {
    namespace Camera {

        Camera::Camera(Application::ApplicationMain& app) : ObjectBase(app) {
            Init();
        }

        bool Camera::Init() {
            SetState(); // �����ݒ�
            return true;
        }

        bool Camera::Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 positoin, const AppFrame::Math::Vector4 move) {
            float sx = _position.GetX() - positoin.GetX();
            float sz = _position.GetZ() - positoin.GetZ();
            float radian = atan2(sz, sx);
            float length = sqrt(sz * sz + sx * sx);
            if (stick.GetX() > InputMin) { radian -= 0.1f; }
            if (stick.GetX() < -InputMin) { radian += 0.1f; }
            // x,z�ʒu
            auto x = positoin.GetX() + move.GetX() + cos(radian) * length;
            _position.SetX(x);
            auto z = positoin.GetZ() + move.GetZ() + sin(radian) * length;
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
            // ���W�̐ݒ�
            VECTOR position(_position.GetX(), _position.GetY(), _position.GetZ());
            VECTOR target(positoin.GetX(), positoin.GetY(), positoin.GetZ());
            //�J�����̈ʒu�X�V
            SetCameraPositionAndTarget_UpVecY(position, target);

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
            _position = AppMath::Vector4(0.0f, 120.0f, -500.0f, 1.0f);
            _target = AppMath::Vector4(0.0f, 80.0f, 0.0f, 1.0f);
            SetCameraNearFar(Near, Far);
        }
    }// namespace Camera
}// namespace Gyro
