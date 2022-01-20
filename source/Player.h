#pragma once
#include "ObjectBase.h"
//#include "camera.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
    namespace Camera {
        class Camera {
        public:
            VECTOR _pos;
            VECTOR _target;
            float _clipNear, _clipFar;
        };
    }
    /**
     * @brief �v���C���[
     */
    namespace Player {
        /**
         * @class Player
         * @brief �I�u�W�F�N�g�x�[�X�̃T�u�N���X
         */
        class Player : public Object::ObjectBase {
            public:
            /**
             * @enum class
             */
            enum class STATE {
                IDLE,
                WALK,
                RUN,
                ATTACK,
                JUMP,
            };
            /**
             * @brief �R���X�g���N�^
             */
            Player(Application::ApplicationMain& app);
            //Player();
            /**
             * @brief  ����������
             * @return true
             */
            bool Init() override;
            /**
             * @brief  �X�V����
             * @return true
             */
            bool Process() override;
            /**
             * @brief  �`�揈��
             * @return true
             */
            bool Draw() const override;
        protected:
            int _handleMap;
            int _frameMapCollision;
            int _handleModel;       //!< ���f���n���h��
            int _handleSkySphere;   //!< �X�J�C�X�t�B�A�n���h��
            int _attachIndex;       //!< �A�j���[�V�����̃A�^�b�`
            float _totalTime;       //!< ���Đ�����
            float _playTime;        //!< 
            VECTOR _position;       //!< ���W
            VECTOR _dir;            //!< ����

            STATE _state;           //!< ���

            Camera::Camera _cam;
        };
    } // namespace Player
} // namespace Gyro

