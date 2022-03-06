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
      ~Camera();
      /**
       * @brief ������
       */
      bool Init();
      /**
       * @brief  �X�V
       * @param  stick     �E�X�e�B�b�N�̑傫��
       * @param  target    �v���C���[�̈ʒu
       * @param  move      �v���C���[�̈ړ���
       * @return true
       */
      bool Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
#ifdef _DEBUG
      /**
       * @brief  �`��
       * @param  position  �v���C���[�̈ʒu
       * @param  move      �v���C���[�̈ړ���
       * @return true
       */
      bool Draw(const AppFrame::Math::Vector4 positoin, const AppFrame::Math::Vector4 move) const;
#endif
      /**
       * @brief  �J������X���擾
       * @return �J������X���W
       */
      float CamPosGetX() {
          return _position.GetX();
      }
      /**
       * @brief  �J������Z���W���擾
       * @return �J������Z���W
       */
      float CamPosGetZ() {
          return _position.GetZ();
      }
      /**
       * @brief  �����_��X���W���擾
       * @return �����_��X���W
       */
      float CamTarGetX() {
          return _target.GetX();
      }
      /**
       * @brief  �����_��Z���W���擾
       * @return �����_��Z���W
       */
      float CamTarGetZ() {
          return _target.GetZ();
      }
      /**
       * @brief  �J�����̍��W�ɑ���
       * @param  vector
       * @return 0.0f
       */
      float CamAddPos(const AppFrame::Math::Vector4 vector) {
          _position.Add(vector);
          return 0.0f;
      }
      /**
       * @brief  �J�������W�̎擾
       * @return �J�������W
       */
      AppFrame::Math::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  �����_�̎擾
       * @return �����_
       */
      AppFrame::Math::Vector4 GetTarget() const {
        return _target;
      }
      /**
       * @brief  �J�����̏�Ԃ��擾
       * @return �J�����̏��
       */
      CameraState GetCamState() {
        return _cameraState;
      }
      /**
       * @brief  �J�����̏�Ԃ��X�y�V�����Ɉڍs
       * @return 
       */
      CameraState GoSpecial() {
        _cameraState = CameraState::SpecialMove;
        _cnt = 20;
        return _cameraState;
      }
    private:
      AppFrame::Math::Vector4 _position{};    //!< �J�����̍��W
      AppFrame::Math::Vector4 _target{};      //!< �J�����̒����_(���Ă�����W)
      CameraState _cameraState{ CameraState::Normal }; //!< �J�������
      int _cnt;                               //!< �J�E���g
      /**
       * @brief  Normal��Ԃ̏���
       * @param  stick   �E�X�e�B�b�N�̑傫��
       * @param  target  �v���C���[�̈ʒu
       * @param  move    �v���C���[�̈ړ���
       */
      void Normal(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
      /**
       * @brief  Special��Ԃ̏���
       * @param  target  �v���C���[�̈ʒu
       * @param  move    �v���C���[�̈ړ���
       */
      void Special(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
      /**
       * @brief ��Ԃ̐ݒ�
       */
      void SetState();
    };
  }// namespace Camera
}// namespace Gyro
