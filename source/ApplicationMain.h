/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  �A�v���P�[�V�����x�[�X�̃T�u�N���X
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <EffekseerForDXLib.h>
#include "Camera.h"
#include "Effect/EffectServer.h"
#include "Effect/EffectComponent.h"

 /**
  * @brief �Q�[���X�y�[�X
  */
namespace Gyro {
    /**
     * @brief �I�u�W�F�N�g�x�[�X
     */
    namespace Object {
        // �O���錾
        class ObjectServer; //!< �I�u�W�F�N�g�T�[�o
        class SpawnServer;  //!< �X�|�[���T�[�o
    } // namespace Object
    /**
     * @brief �G�t�F�N�g�x�[�X
     */
    namespace Effect {
        // �O���錾
        class EffectServer;     //!< �G�t�F�N�g�T�[�o
        class EffectComponent;  //!< �G�t�F�N�g
    } // namespace Effect
    /**
     * @brief �A�v���P�[�V����
     */
    namespace Application {
        /**
         * @class ApplicationMain
         * @brief �A�v���P�[�V�������C��
         */
        class ApplicationMain : public AppFrame::Application::ApplicationBase {
        public:
            /**
             * @brief  �R���X�g���N�^
             */
            ApplicationMain();
            /**
             * @brief  ������
             * @return true:���������� false:���������s
             */
            bool Init() override;
            /**
             * @brief  ���͏���
             * @return
             */
            bool Input() override;
            /**
             * @brief  �I������
             */
            void Terminate() override;
            /**
             * @brief  �t���[���J�E���^�̎擾
             * @return �t���[���J�E���^
             */
            const int GetFrameCount() const override {
                return 0;
            }
            /**
             * @brief  �I�u�W�F�N�g�T�[�o�̎擾
             * @return �I�u�W�F�N�g�T�[�o�̎Q��
             */
            Object::ObjectServer& GetObjectServer() {
                return *_objectServer;
            }
            /**
             * @brief  �X�|�[���T�[�o�̎擾
             * @return �X�|�[���T�[�o�̎Q��
             */
            Object::SpawnServer& GetSpawnServer() {
                return *_spawnServer;
            }
            /**
             * @brief  �J�����̎擾
             * @return �J�����̎Q��
             */
            Camera::Camera& GetCamera() {
                return *_camera;
            }
            /**
             * @brief  �G�t�F�N�g�T�[�o�̎擾
             * @return �G�t�F�N�g�T�[�o�̎Q��
             */
            Effect::EffectServer& GetEffectServer() {
                return *_effectServer;
            }
            /**
             * @brief  �G�t�F�N�g�̎擾
             * @return �G�t�F�N�g�̎Q��
             */
            Effect::EffectComponent& GetEffect() {
                return *_effect;
            }
        private:
            //!< �I�u�W�F�N�g�T�[�o
            std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
            //!< �X�|�[���T�[�o
            std::unique_ptr<Object::SpawnServer> _spawnServer{ nullptr };
            //!< �J����
            std::unique_ptr<Camera::Camera> _camera{ nullptr };
            //!< �G�t�F�N�g�T�[�o
            std::unique_ptr<Effect::EffectServer> _effectServer{ nullptr };
            //! �G�t�F�N�g
            std::unique_ptr<Effect::EffectComponent> _effect{ nullptr };
            /**
             * @brief  �X�V����
             * @return
             */
            bool Process() override;
            /**
             * @brief  Effekseer�ݒ�
             * @return true �ݒ萬��
             *         false �ݒ莸�s
             */
            bool Effekseer();
        };
    } // namespace Application
} // namespace Gyro