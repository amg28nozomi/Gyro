/*****************************************************************//**
 * @file    EnemyWheelBoss.h
 * @brief   �n��G�{�X�N���X
 *          
 * @author  �y������
 * @date    March 2022
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
     * @class EnemyWheelBoss
     * @brief �n��G�{�X�N���X
     */
    class EnemyWheelBoss : public EnemyBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      EnemyWheelBoss(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EnemyWheelBoss();
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
      /**
       * @brief  ���f���ԍ��̏�����
       */
      static inline void ModelNumberReset() {
        _number = 1;
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
       * @brief  �U����������
       */
      void AttackReady();
      /**
       * @brief  �U������
       */
      void Attack() override;
      /**
       * @brief  �m�b�N�o�b�N����
       */
      void NockBack() override;
      /**
       * @brief  �T������
       */
      void Search() override;
      /**
       * @brief  �Փˏ���
       */
      void Hit() override;
      /**
       * @brief  �A�j���[�V�����؂�ւ�
       */
      void ChangeAnim() override;
      /**
       * @brief  �G�t�F�N�g������(����)
       */
      void EffectInit() override;
      /**
       * @brief  �G�t�F�N�g�X�V�Ăяo��
       */
      void EffectProcess() override;
      /**
       * @brief  �G�t�F�N�g�Đ��Ăяo��
       */
      void EffectPlay() override;
      /**
       * @brief  �G�t�F�N�g�����Ăяo��
       */
      void EffectDead() override;
      /**
       * @brief  ��]�U���G�t�F�N�g
       */
      void SlashEffect();
      /**
       * @brief  �I�u�W�F�N�g�̎��S����
       */
      void Dead() override;
      /**
       * @brief  �_���[�W���󂯂����̔���
       * @return true:�Փ�
       *         false:�_���[�W����
       */
      bool IsDamege() override;

      bool _iMove{ false };  //!< �ړ��t���O
      bool _slash{ false };  //!< ��]�U���t���O
      AppFrame::Math::Vector4 _oldPosition;   //!< �U����ԂɈڍs�����^�C�~���O�̍��W
      AppFrame::Math::Vector4 _move;          //!< �ړ�����
      static inline unsigned short _number{ 1 };  //!< �����ԍ�
      unsigned short _this{ 0 };  //!< ����ID

      //!< ����G�t�F�N�g
      std::shared_ptr<Effect::EffectEnemyBossEyeLight> _eyeLight{ nullptr };
      //!< �ːi�U���G�t�F�N�g
      std::shared_ptr<Effect::EffectEnemyBossGroundAttack1> _groundAttack1{ nullptr };
      //!< ��]�U���G�t�F�N�g
      std::shared_ptr<Effect::EffectEnemyBossGroundAttack2> _groundAttack2{ nullptr };
      //!< ��_���G�t�F�N�g
      std::shared_ptr<Effect::EffectEnemyBossHit> _hit{ nullptr };
      //!< �����G�t�F�N�g
      std::shared_ptr<Effect::EffectEnemyBossExprosion> _exprosion{ nullptr };
    };
  } // namespace Enemy
} // namespace Gyro