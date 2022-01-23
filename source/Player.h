/*****************************************************************//**
 * @file   Player.h
 * @brief  �I�u�W�F�N�g�x�[�X�̃T�u�N���X
 *         ���@�̏������s��
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
//#include "camera.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �J�����x�[�X
   */
  namespace Camera {
    /**
     * @class Camera
     * @brief �J�����N���X
     */
    class Camera {
    public:
      VECTOR _pos;
      VECTOR _target;
      float _clipNear, _clipFar;
    };
  } // namespace Camera
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    /**
     * @class Player
     * @brief �I�u�W�F�N�g�x�[�X�̃T�u�N���X
     */
    class Player : public Object::ObjectBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      Player(Application::ApplicationMain& app);
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
    private:
      int _model;          //!< ���f���n���h��
      int _animaIndex;     //!< �A�^�b�`����Ă���A�j���ԍ�
      float _totalTime;    //!< �A�j���[�V�����̑��Đ�����
      float _animaTime;    //!< �A�j���[�V�����̍Đ�����
      Camera::Camera _cam; //!< �J�����̎���

      int _handleMap;
      int _frameMapCollision;
      int _handleSkySphere;   //!< �X�J�C�X�t�B�A�n���h��
      /**
       * @brief ���͏���
       */
      void Input();
      /**
       * @brief ���\�[�X�̓ǂݎ�菈��
       */
      void LoadResource();
      /**
       * @brief ��Ԃ̐ݒ�
       */
      void SetState();
      /**
       * @brief �J�����̐ݒ�
       */
      void SetCamera();
      /**
       * @brief  �ړ��ʂ̎Z�o
       * @param  stick ���͒l
       * @return �ړ���
       */
      float Speed(const AppFrame::Math::Vector4 stick) const;
      /**
       * @brief �J�����̍X�V
       * @param stick 
       */
      void CameraUpdate(const AppFrame::Math::Vector4 stick);
      /**
       * @brief �����̐ݒ�
       * @param move �ړ���
       */
      void SetRotation(const AppFrame::Math::Vector4 move);
      /**
       * @brief �A�j���[�V��������
       */
      void Animation();
      /**
       * @brief �w�肵���A�j���[�V�����C���f�b�N�X�̎擾
       * @param key �A�j���[�V�����ɕR�Â���ꂽ������
       */
      int AnimaIndex(std::string_view key) const;
      /**
       * @brief �A�j���[�V�����̃A�^�b�`
       */
      bool AttachAnima(std::string_view key);
    };
  }
    /**
     * @brief �v���C���[
     */
    //namespace Player {
    //    /**
    //     * @class Player
    //     * @brief �I�u�W�F�N�g�x�[�X�̃T�u�N���X
    //     */
    //    class Player : public Object::ObjectBase {
    //    public:
    //      /**
    //       * @brief �R���X�g���N�^
    //       * @param app �A�v���P�[�V�����̎Q��
    //       */
    //      Player(Application::ApplicationMain& app);
    //      /**
    //       * @brief  ����������
    //       * @return true
    //       */
    //      bool Init() override;
    //      /**
    //       * @brief  �X�V����
    //       * @return true
    //       */
    //      bool Process() override;
    //      /**
    //       * @brief  �`�揈��
    //       * @return true
    //       */
    //      bool Draw() const override;


    //        /**
    //         * @enum class
    //         */
    //        enum class STATE {
    //            IDLE,
    //            WALK,
    //            RUN,
    //            ATTACK,
    //            JUMP,
    //        };
    //        /**
    //         * @brief �R���X�g���N�^
    //         */
    //        Player(Application::ApplicationMain& app);
    //        //Player();
    //        /**
    //         * @brief  ����������
    //         * @return true
    //         */
    //        bool Init() override;
    //        /**
    //         * @brief  �X�V����
    //         * @return true
    //         */
    //        bool Process() override;
    //        /**
    //         * @brief  �`�揈��
    //         * @return true
    //         */
    //        bool Draw() const override;
    //    protected:
    //        int _handleMap;
    //        int _frameMapCollision;
    //        int _handleModel;       //!< ���f���n���h��
    //        int _handleSkySphere;   //!< �X�J�C�X�t�B�A�n���h��
    //        int _attachIndex;       //!< �A�j���[�V�����̃A�^�b�`
    //        float _totalTime;       //!< ���Đ�����
    //        float _playTime;        //!< 
    //        VECTOR _position;       //!< ���W
    //        VECTOR _dir;            //!< ����

    //        STATE _state;           //!< ���

    //        Camera::Camera _cam;
    //        /**
    //         * @brief ���\�[�X�̓ǂݎ�菈��
    //         */
    //        void LoadResource();
    //        /**
    //         * @brief �J�����̐ݒ�
    //         */
    //        void SetCamera();
    //    };
    //} // namespace Player
} // namespace Gyro