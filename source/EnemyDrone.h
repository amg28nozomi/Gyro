/*****************************************************************//**
 * @file   EnemyDrone.h
 * @brief  �󒆓G�N���X
 * 
 * @author �y������
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �G�x�[�X
   */
  namespace Enemy {
    /**
     * @class EnemyDrone
     * @brief �󒆓G�N���X
     */
    class EnemyDrone : public EnemyBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V����
       */
      EnemyDrone(Application::ApplicationMain& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~EnemyDrone();
      /**
       * @brief  ������
       * @return true
       */
      bool Init() override;
      /**
       * @brief  �X�V
       * @return true
       */
      bool Process() override;
      /**
       * @brief  �`��
       * @return true
       */
      bool Draw() const override;
      /**
       * @brief  �U����Ԃ̍��W�̎擾
       * @return �U����Ԃ̍��W
       */
      AppFrame::Math::Vector4 GetAttackPosition() {
        return _oldPosition;
      }
      unsigned short GetThis() const override {
        return _this;
      }
    private:
      /**
       * @brief  ���f���̓ǂݍ���
       */
      void LoadModel() override;
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameter() override;
      /**
       * @brief  �����蔻��̐ݒ菈��
       * @author ��؊�C
       */
      void SetCollision() override;
      /**
       * @brief  �ړ�����
       */
      void Move() override;
      /**
       * @brief  �U������
       */
      void Attack() override;
      /**
       * @brief  �m�b�N�o�b�N����
       */
      void NockBack() override;
      /**
       * @brief  �Փˏ���
       */
      void Hit() override;
      /**
       * @brief  �A�j���[�V�����؂�ւ�
       */
      void ChangeAnim() override;
      /**
       * @brief  �G�t�F�N�g�Đ�
       */
      void PlayEffect() override;
      /**
       * @brief  �_���[�W���󂯂����̔���
       * @return true:�Փ�
       *         false:�_���[�W����
       */
      bool IsDamege() override;

      bool _iMove{ false };  //!< �ړ��t���O
      AppFrame::Math::Vector4 _oldPosition;   //!< �U����ԂɈڍs�����^�C�~���O�̍��W
      static inline unsigned short _number{ 1 };  //!< �����ԍ�
      unsigned short _this{ 0 };  //!< ����ID
    };
  } // namespace Enemy
} // namespace Gyro