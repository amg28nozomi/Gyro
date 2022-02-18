/*****************************************************************//**
 * @file   Camera.h
 * @brief  �I�u�W�F�N�g�N���X�̃T�u�N���X
 *         �J�����̏������s��
 *
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"

namespace AppFrame::Math {}

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
    /**
     * @brief �J����
     */
    namespace Camera {
        /**
         * @class Camera
         * @brief �J�����N���X
         */
        class Camera {
        public:
            /**
             * @brief �J�����̏�Ԃ�\���񋓌^�N���X
             */
            enum class CameraState {
                Normal,         //!< �ʏ�
                SpecialMove,    //!< �K�E�Z
            };
            /**
             * @brief �R���X�g���N�^
             */
            Camera();
            /**
             * @brief �f�X�g���N�^
             */
             //~Camera();
             /**
              * @brief ������
              */
            bool Init();
            /**
             * @brief �X�V
             * @param stick     �E�X�e�B�b�N�̑傫��
             * @param target    �v���C���[�̈ʒu
             * @param move      �v���C���[�̈ړ���
             */
            bool Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
#ifdef _DEBUG
            /**
             * @brief �`��
             * @param position  �v���C���[�̈ʒu
             * @param move      �v���C���[�̈ړ���
             */
            bool Draw(const AppFrame::Math::Vector4 positoin, const AppFrame::Math::Vector4 move) const;
#endif // DEBUG
            float CamPosGetX() {
                return _position.GetX();
            }
            float CamPosGetZ() {
                return _position.GetZ();
            }
            float CamTarGetX() {
                return _target.GetX();
            }
            float CamTarGetZ() {
                return _target.GetZ();
            }
            float CamAddPos(const AppFrame::Math::Vector4 vector) {
                _position.Add(vector);
                return 0.0f;
            }
        private:
            AppFrame::Math::Vector4 _position{};    //!< �J�����̍��W
            AppFrame::Math::Vector4 _target{};  //!< �J�����̒����_(���Ă�����W)
            CameraState _cameraState{ CameraState::Normal }; //!< �J�������

            /**
             * @brief ��Ԃ̐ݒ�
             */
            void SetState();
        };
    }// namespace Camera
}// namespace Gyro
