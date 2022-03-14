/*****************************************************************//**
 * @file    EffectServer.h
 * @brief   �G�t�F�N�g���Ǘ�����T�[�o�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief �G�t�F�N�g�x�[�X
   */
  namespace Effect {
    namespace AppServer = AppFrame::Server;
    namespace AppMath = AppFrame::Math;
    class EffectBase;
    class EffectPlayerDash;
    class EffectPlayerJump;
    class EffectPlayerLanding;
    class EffectPlayerHit;
    class EffectPlayerAvoidance;
    class EffectPlayerWeakAttack1;
    class EffectPlayerWeakAttack2;
    class EffectPlayerWeakAttack3;
    class EffectPlayerWeakAttackEX;
    class EffectPlayerHeavyAttack1;
    class EffectPlayerHeavyAttack2;
    class EffectPlayerHeavyAttack3;
    class EffectPlayerAirWeakAttack1;
    class EffectPlayerAirWeakAttack2;
    class EffectPlayerAirWeakAttack3;
    class EffectPlayerAirHeavyAttack1;
    class EffectPlayerAirHeavyAttack2;
    class EffectPlayerUltActivate;
    class EffectPlayerUltSlash;
    class EffectEnemyEyeLight;
    class EffectEnemyGroundAttack1;
    class EffectEnemyGroundAttack2;
    class EffectEnemyAirAttack;
    class EffectEnemyHit;
    class EffectEnemyExprosion;
    class EffectEnemyBossEyeLight;
    class EffectEnemyBossGroundAttack1;
    class EffectEnemyBossGroundAttack2;
    class EffectEnemyBossAirAttack;
    class EffectEnemyBossHit;
    class EffectEnemyBossExprosion;
    class EffectStageBarrier;
    class EffectStageBoxDestroy;
    class EffectStageHeal;
    /**
     * @class EffectServer
     * @brief �G�t�F�N�g���Ǘ�����T�[�o�N���X
     */
    class EffectServer : AppServer::ServerTemplateVector<std::shared_ptr<EffectBase>> {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�������C���̎Q��
       */
      EffectServer(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectServer();
      /**
       * @brief  ���
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �X�V
       * @return true
       */
      bool Process();
      /**
       * @brief  �`��
       * @return true
       */
      bool Draw();
      /**
       * @brief  �G�t�F�N�g����(�T�[�o�ɓo�^)
       * @param  num �G�t�F�N�g���ʔԍ�
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       */
      void MakeEffect(const int num, const AppMath::Vector4 position, const float radian);
      /**
       * @brief  �K�E�U���G�t�F�N�g�I������̐ݒ�
       * @param  flag �I���t���O
       */
      void SetUltSlashEnd(const bool flag) {
        _ultSlashEnd = flag;
      }
      /**
       * @brief  �K�E�U���G�t�F�N�g�I������̎擾
       * @return true:�I��
       *         false:�Đ���(���Đ�)
       */
      bool GetUltSlashEnd() {
        return _ultSlashEnd;
      }

    private:
      /**
       * @brief  �G�t�F�N�g�̓o�^
       * @param  �G�t�F�N�g�̃V�F�A�[�h�|�C���^
       */
      void AddEffect(std::shared_ptr<EffectBase> effect);
      /**
       * @brief  �v���C���[�_�b�V���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�_�b�V���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerDash> PlayerDash(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�W�����v�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�W�����v�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerJump> PlayerJump(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[���n�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[���n�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerLanding> PlayerLanding(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[��_���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[��_���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerHit> PlayerHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[����̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[����̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerAvoidance> PlayerAvoidance(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[��U��1�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[��U��1�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerWeakAttack1> PlayerWeakAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[��U��2�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[��U��2�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerWeakAttack2> PlayerWeakAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[��U��3�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[��U��3�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerWeakAttack3> PlayerWeakAttack3(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[��U��EX�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[��U��EX�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerWeakAttackEX> PlayerWeakAttackEX(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[���U��1�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[���U��1�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerHeavyAttack1> PlayerHeavyAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[���U��2�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[���U��2�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerHeavyAttack2> PlayerHeavyAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[���U��3�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[���U��3�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerHeavyAttack3> PlayerHeavyAttack3(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�󒆎�U��1�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�󒆎�U��1�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerAirWeakAttack1> PlayerAirWeakAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�󒆎�U��2�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�󒆎�U��2�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerAirWeakAttack2> PlayerAirWeakAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�󒆎�U��3�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�󒆎�U��3�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerAirWeakAttack3> PlayerAirWeakAttack3(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�󒆋��U��1�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�󒆋��U��1�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerAirHeavyAttack1> PlayerAirHeavyAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�󒆋��U��2�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�󒆋��U��2�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerAirHeavyAttack2> PlayerAirHeavyAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�K�E�����̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�K�E�����̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerUltActivate> PlayerUltActivate(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[�K�E�U���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�K�E�U���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerUltSlash> PlayerUltSlash(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G����̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G����̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyEyeLight> EnemyEyeLight(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�n��U��1�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�n��U��1�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyGroundAttack1> EnemyGroundAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�n��U��2�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�n��U��2�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyGroundAttack2> EnemyGroundAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�󒆍U���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�󒆍U���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyAirAttack> EnemyAirAttack(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G��_���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G��_���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyHit> EnemyHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�����̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�����̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyExprosion> EnemyExprosion(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�{�X����̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�{�X����̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyBossEyeLight> EnemyBossEyeLight(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�{�X�n��U��1�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�{�X�n��U��1�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyBossGroundAttack1> EnemyBossGroundAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�{�X�n��U��2�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�{�X�n��U��2�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyBossGroundAttack2> EnemyBossGroundAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�{�X�󒆍U���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�{�X�󒆍U���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyBossAirAttack> EnemyBossAirAttack(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�{�X��_���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�{�X��_���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyBossHit> EnemyBossHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �G�{�X�����̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�{�X�����̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyBossExprosion> EnemyBossExprosion(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �X�e�[�W�o���A�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �X�e�[�W�o���A�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectStageBarrier> StageBarrier(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �X�e�[�W���j��̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �X�e�[�W���j��̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectStageBoxDestroy> StageBoxDestroy(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �X�e�[�W�񕜂̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �X�e�[�W�񕜂̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectStageHeal> StageHeal(const AppMath::Vector4 position, const float radian) const;

      bool _ultSlashEnd{ false };  //!< �K�E�U���G�t�F�N�g�I������
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
    };
  } // namespace Effect

  // �G�t�F�N�g���ʔԍ��萔
  namespace EffectNum {
  // 1**:�v���C���[
    // 10*:�ėp
    constexpr int PlayerDash = 100;       //!< �v���C���[�_�b�V��
    constexpr int PlayerJump = 101;       //!< �v���C���[�W�����v
    constexpr int PlayerLanding = 102;    //!< �v���C���[���n
    constexpr int PlayerHit = 103;        //!< �v���C���[��_��
    constexpr int PlayerAvoidance = 104;  //!< �v���C���[���
    // 11*:��U��
    constexpr int PlayerWeakAttack1 = 111;   //!< �v���C���[��U��1
    constexpr int PlayerWeakAttack2 = 112;   //!< �v���C���[��U��2
    constexpr int PlayerWeakAttack3 = 113;   //!< �v���C���[��U��3
    constexpr int PlayerWeakAttackEX = 114;  //!< �v���C���[��U��EX
    // 12*:���U��
    constexpr int PlayerHeavyAttack1 = 121;  //!< �v���C���[���U��1
    constexpr int PlayerHeavyAttack2 = 122;  //!< �v���C���[���U��2
    constexpr int PlayerHeavyAttack3 = 123;  //!< �v���C���[���U��3
    // 13*:�󒆎�U��
    constexpr int PlayerAirWeakAttack1 = 131;  //!< �v���C���[�󒆎�U��1
    constexpr int PlayerAirWeakAttack2 = 132;  //!< �v���C���[�󒆎�U��2
    constexpr int PlayerAirWeakAttack3 = 133;  //!< �v���C���[�󒆎�U��3
    // 14*:�󒆋��U��
    constexpr int PlayerAirHeavyAttack1 = 141;  //!< �v���C���[�󒆋��U��1
    constexpr int PlayerAirHeavyAttack2 = 142;  //!< �v���C���[�󒆋��U��2
    // 15*:�K�E�Z
    constexpr int PlayerUltActivate = 150;  //!< �v���C���[�K�E����
    constexpr int PlayerUltSlash = 151;     //!< �v���C���[�K�E�U��
  // 2**:�G
    // 20*:�ʏ�
    constexpr int EnemyEyeLight = 200;       //!< �G���
    constexpr int EnemyGroundAttack1 = 201;  //!< �G�n��U��1
    constexpr int EnemyGroundAttack2 = 202;  //!< �G�n��U��2
    constexpr int EnemyAirAttack = 203;      //!< �G�󒆍U��
    constexpr int EnemyHit = 204;            //!< �G��_��
    constexpr int EnemyExprosion = 205;      //!< �G����
    // 21*:�{�X
    constexpr int EnemyBossEyeLight = 210;       //!< �G�{�X���
    constexpr int EnemyBossGroundAttack1 = 211;  //!< �G�{�X�n��U��1
    constexpr int EnemyBossGroundAttack2 = 212;  //!< �G�{�X�n��U��2
    constexpr int EnemyBossAirAttack = 213;      //!< �G�{�X�󒆍U��
    constexpr int EnemyBossHit = 214;            //!< �G�{�X��_��
    constexpr int EnemyBossExprosion = 215;      //!< �G�{�X����
  // 3**:�X�e�[�W
    constexpr int StageBarrier = 300;     //!< �X�e�[�W�o���A
    constexpr int StageBoxDestroy = 301;  //!< �X�e�[�W���j��
    constexpr int StageHeal = 302;        //!< �X�e�[�W��
  } // namespace EffectNum
} // namespace Gyro