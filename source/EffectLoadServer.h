/*****************************************************************//**
 * @file    EffectLoadServer.h
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
    /**
     * @class EffectLoadServer
     * @brief �G�t�F�N�g���Ǘ�����T�[�o�N���X
     */
    class EffectLoadServer : AppServer::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief  �G�t�F�N�g�����i�[���铮�I�z��
       * @param  �G�t�F�N�g�t�@�C���ɕR�Â��镶����
       * @param  �G�t�F�N�g�t�@�C���̃p�X
       * @param  �G�t�F�N�g�g�嗦
       */
      using EffectMap = std::vector<std::tuple<std::string_view, std::string_view, float>>;
      /**
       * @brief  �R���X�g���N�^
       */
      EffectLoadServer();
      /**
       * @brief  �������
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �R���e�i���g�p�����G�t�F�N�g�t�@�C���̓ǂݎ��
       * @param  effectMap �G�t�F�N�g��񂪊i�[���ꂽ�R���e�i
       */
      void AddEffects(const EffectMap& effectMap);
      /**
       * @brief  �w�肵���G�t�F�N�g�n���h���̎擾
       * @param  key �Ώۂ̃G�t�F�N�g�n���h���ɕR�Â���ꂽ������
       * @return �G�t�F�N�g�n���h��
       *         �L�[���L���ł͂Ȃ��ꍇ��-1��Ԃ�
       */
      int GetEffectHandle(std::string_view key) const;

    private:
      /**
       * @brief  �G�t�F�N�g�t�@�C���̓ǂݎ��
       * @param  key �G�t�F�N�g�n���h���ɕR�Â��镶����
       * @param  effectFile �G�t�F�N�g�t�@�C���̃p�X
       * @param  magni �G�t�F�N�g�g�嗦
       * @return true:����I��
       *         false:�ǂݎ�莸�s
       */
      bool AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni);
    };
  } // namespace Effect

  // �G�t�F�N�g�L�[�萔
  namespace EffectKey {
  // �v���C���[
    constexpr std::string_view PlayerJump = "PlayerJump";                        //!< �v���C���[�W�����v
    constexpr std::string_view PlayerHit = "PlayerHit";                          //!< �v���C���[��_��
    constexpr std::string_view PlayerWeakAttack1 = "PlayerWeakAttack1";          //!< �v���C���[��U��1
    constexpr std::string_view PlayerWeakAttack2 = "PlayerWeakAttack2";          //!< �v���C���[��U��2
    constexpr std::string_view PlayerWeakAttack3 = "PlayerWeakAttack3";          //!< �v���C���[��U��3
    constexpr std::string_view PlayerWeakAttackEX = "PlayerWeakAttackEX";        //!< �v���C���[��U��EX
    constexpr std::string_view PlayerHeavyAttack1 = "PlayerHeavyAttack1";        //!< �v���C���[���U��1
    constexpr std::string_view PlayerHeavyAttack2 = "PlayerHeavyAttack2";        //!< �v���C���[���U��2
    constexpr std::string_view PlayerHeavyAttack3 = "PlayerHeavyAttack3";        //!< �v���C���[���U��3
    constexpr std::string_view PlayerAirWeakAttack1 = "PlayerAirWeakAttack1";    //!< �v���C���[�󒆎�U��1
    constexpr std::string_view PlayerAirWeakAttack2 = "PlayerAirWeakAttack2";    //!< �v���C���[�󒆎�U��2
    constexpr std::string_view PlayerAirWeakAttack3 = "PlayerAirWeakAttack3";    //!< �v���C���[�󒆎�U��3
    constexpr std::string_view PlayerAirHeavyAttack1 = "PlayerAirHeavyAttack1";  //!< �v���C���[�󒆋��U��1
    constexpr std::string_view PlayerAirHeavyAttack2 = "PlayerAirHeavyAttack2";  //!< �v���C���[�󒆋��U��2
    constexpr std::string_view PlayerUltActivate = "PlayerUltActivate";          //!< �v���C���[�K�E����
    constexpr std::string_view PlayerUltSlash = "PlayerUltSlash";                //!< �v���C���[�K�E�U��
  // �G
    constexpr std::string_view EnemyEyeLight = "EnemyEyeLight";            //!< �G���
    constexpr std::string_view EnemyGroundAttack1 = "EnemyGroundAttack1";  //!< �G�n��U��1
    constexpr std::string_view EnemyGroundAttack2 = "EnemyGroundAttack2";  //!< �G�n��U��2
    constexpr std::string_view EnemyAirAttack = "EnemyAirAttack";          //!< �G�󒆍U��
    constexpr std::string_view EnemyHit = "EnemyHit";                      //!< �G��_��
    constexpr std::string_view EnemyExprosion = "EnemyExprosion";          //!< �G����
    //�{�X
    constexpr std::string_view EnemyBossEyeLight = "EnemyBossEyeLight";            //!< �G�{�X���
    constexpr std::string_view EnemyBossGroundAttack1 = "EnemyBossGroundAttack1";  //!< �G�{�X�n��U��1
    constexpr std::string_view EnemyBossGroundAttack2 = "EnemyBossGroundAttack2";  //!< �G�{�X�n��U��2
    constexpr std::string_view EnemyBossAirAttack = "EnemyBossAirAttack";          //!< �G�{�X�󒆍U��
    constexpr std::string_view EnemyBossHit = "EnemyBossHit";                      //!< �G�{�X��_��
    constexpr std::string_view EnemyBossExprosion = "EnemyBossExprosion";          //!< �G�{�X����
  // �X�e�[�W
    constexpr std::string_view StageBarrier = "StageBarrier";        //!< �X�e�[�W�o���A
    constexpr std::string_view StageBoxDestroy = "StageBoxDestroy";  //!< �X�e�[�W���j��
  } // namespace EffectKey
} // namespace Gyro