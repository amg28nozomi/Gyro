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
    class EffectPlayerJump;
    class EffectPlayerHit;
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
    class EffectEnemyGroundAttack;
    class EffectEnemyHit;
    class EffectEnemyExprosion;
    class EffectStageBarrier;
    class EffectStageBoxDestroy;
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
       * @brief  �G�t�F�N�g����
       * @param  num �G�t�F�N�g���ʔԍ�
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       */
      void MakeEffect(const int num, const AppMath::Vector4 position, const float radian);

    private:
      /**
       * @brief  �G�t�F�N�g�̓o�^
       * @param  �G�t�F�N�g�̃V�F�A�[�h�|�C���^
       */
      void AddEffect(std::shared_ptr<EffectBase> effect);
      /**
       * @brief  �v���C���[�W�����v�̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[�W�����v�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerJump> PlayerJump(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  �v���C���[��_���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �v���C���[��_���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectPlayerHit> PlayerHit(const AppMath::Vector4 position, const float radian) const;
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
       * @brief  �G�n��U���̐���
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       * @return �G�n��U���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectEnemyGroundAttack> EnemyGroundAttack(const AppMath::Vector4 position, const float radian) const;
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

      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
    };
  } // namespace Effect

  // �G�t�F�N�g���ʔԍ��萔
  namespace EffectNum {
    // 1**:�v���C���[
      // 10*:�ėp
    constexpr int PlayerJump = 100;             //!< �v���C���[�W�����v
    constexpr int PlayerHit = 101;              //!< �v���C���[��_��
    // 11*:��U��
    constexpr int PlayerWeakAttack1 = 111;      //!< �v���C���[��U��1
    constexpr int PlayerWeakAttack2 = 112;      //!< �v���C���[��U��2
    constexpr int PlayerWeakAttack3 = 113;      //!< �v���C���[��U��3
    constexpr int PlayerWeakAttackEX = 114;     //!< �v���C���[��U��EX
    // 12*:���U��
    constexpr int PlayerHeavyAttack1 = 121;     //!< �v���C���[���U��1
    constexpr int PlayerHeavyAttack2 = 122;     //!< �v���C���[���U��2
    constexpr int PlayerHeavyAttack3 = 123;     //!< �v���C���[���U��3
    // 13*:�󒆎�U��
    constexpr int PlayerAirWeakAttack1 = 131;   //!< �v���C���[�󒆎�U��1
    constexpr int PlayerAirWeakAttack2 = 132;   //!< �v���C���[�󒆎�U��2
    constexpr int PlayerAirWeakAttack3 = 133;   //!< �v���C���[�󒆎�U��3
    // 14*:�󒆋��U��
    constexpr int PlayerAirHeavyAttack1 = 141;  //!< �v���C���[�󒆋��U��1
    constexpr int PlayerAirHeavyAttack2 = 142;  //!< �v���C���[�󒆋��U��2
    // 15*:�K�E�Z
    constexpr int PlayerUltActivate = 150;      //!< �v���C���[�K�E����
    constexpr int PlayerUltSlash = 151;         //!< �v���C���[�K�E�U��
  // 2**:�G
    constexpr int EnemyEyeLight = 200;      //!< �G���
    constexpr int EnemyGroundAttack = 201;  //!< �G�n��U��
    constexpr int EnemyHit = 202;           //!< �G��_��
    constexpr int EnemyExprosion = 203;     //!< �G����
  // 3**:�X�e�[�W
    constexpr int StageBarrier = 300;     //!< �X�e�[�W�o���A
    constexpr int StageBoxDestroy = 301;  //!< �X�e�[�W���j��
  } // namespace EffectNum
} // namespace Gyro