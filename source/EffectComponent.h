/*****************************************************************//**
 * @file    EffectComponent.h
 * @brief   �G�t�F�N�g�N���X
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
    namespace AppMath = AppFrame::Math;
    /**
     * @class EffecComponent
     * @brief �G�t�F�N�g�N���X
     */
    class EffectComponent {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectComponent(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectComponent();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  �`��
       */
      void Draw() const;
      /**
       * @brief  �G�t�F�N�g�Đ�
       * @param  key �G�t�F�N�g�L�[
       * @param  position �G�t�F�N�g�ʒu
       * @param  radian �G�t�F�N�g����
       */
      void PlayEffect(const std::string_view key, const AppMath::Vector4 position, const float radian);

    private:
      /**
       * @brief  �G�t�F�N�g�n���h���̎擾
       * @param  key �G�t�F�N�g�L�[
       */
      int GetEffectHandle(const std::string_view key);

      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
    };

    // �G�t�F�N�g�L�[�萔��
    // �v���C���[
    constexpr std::string_view pWeakAttack1 = "P_WeakAttack1";          //!< �v���C���[��U��1
    constexpr std::string_view pWeakAttack2 = "P_WeakAttack2";          //!< �v���C���[��U��2
    constexpr std::string_view pWeakAttack3 = "P_WeakAttack3";          //!< �v���C���[��U��3
    constexpr std::string_view pWeakAttackEX = "P_WeakAttackEX";        //!< �v���C���[��U��EX
    constexpr std::string_view pHeavyAttack1 = "P_HeavyAttack1";        //!< �v���C���[���U��1
    constexpr std::string_view pHeavyAttack3 = "P_HeavyAttack3";        //!< �v���C���[���U��3
    constexpr std::string_view pAirWeakAttack1 = "P_AirWeakAttack1";    //!< �v���C���[�󒆎�U��1
    constexpr std::string_view pAirWeakAttack2 = "P_AirWeakAttack2";    //!< �v���C���[�󒆎�U��1
    constexpr std::string_view pAirWeakAttack3 = "P_AirWeakAttack3";    //!< �v���C���[�󒆎�U��1
    constexpr std::string_view pAirHeavyAttack1 = "P_AirHeavyAttack1";  //!< �v���C���[�󒆎�U��1
    constexpr std::string_view pAirHeavyAttack2 = "P_AirHeavyAttack2";  //!< �v���C���[�󒆎�U��1
    constexpr std::string_view pUltActivate = "P_Ult_Activate";         //!< �v���C���[�K�E
    constexpr std::string_view pUltSlash = "P_Ult_Slash";               //!< �v���C���[�K�E
    constexpr std::string_view pHit = "P_Hit";                          //!< �v���C���[��_��
    // �G
    constexpr std::string_view eEyeLight = "E_EyeLight";          //!< �G����
    constexpr std::string_view eGroundAttack = "E_GroundAttack";  //!< �G��]�U��
    constexpr std::string_view eHit = "E_Hit";                    //!< �G��_��
    constexpr std::string_view eExprosion = "E_Exprosion";        //!< �G����
    // �X�e�[�W
    constexpr std::string_view stageBarrier = "Stage_Barrier";  //!< �X�e�[�W�o���A
  } // namespace Effect
} // namespace Gyro