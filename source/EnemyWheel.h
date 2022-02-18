/*****************************************************************//**
 * @file    EnemyWheel.h
 * @brief   �n��G�N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
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
     * @class EnemyWheel
     * @brief �n��G�N���X
     */
    class EnemyWheel : public EnemyBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      EnemyWheel(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EnemyWheel();
      /**
       * @brief  ������
       */
      bool Init() override;
      /**
       * @brief  �X�V
       */
      bool Process() override;
      /**
       * @brief  �`��
       */
      bool Draw() const override;

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
      static inline unsigned short _number{ 0 };  //!< �����ԍ�
      unsigned short _this{ 0 };  //!< ����ID
    };
  } // namespace Enemy
} // namespace Gyro