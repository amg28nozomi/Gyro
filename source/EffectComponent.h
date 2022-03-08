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
  } // namespace Effect
} // namespace Gyro