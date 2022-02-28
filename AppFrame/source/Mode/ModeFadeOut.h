/*****************************************************************//**
 * @file   ModeFadeOut.h
 * @brief  ���[�h�t�F�[�h�̃T�u�N���X
 *         �t�F�[�h�A�E�g�������s��
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ModeFade.h"
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    /**
     * @class ModeFadeOut
     * @brief �t�F�[�h�A�E�g�������s�����[�h
     */
    class ModeFadeOut : public ModeFade {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeFadeOut(Application::ApplicationBase& app, const Data::Color color = Data::Color());
      /**
       * @brief  ��������
       * @return true
       */
      bool Enter() override;
      /**
       * @brief  �X�V����
       * @return true
       */
      bool Process() override;
    private:
      /**
       * @brief  �t�F�[�h�����̏I������
       * @return true:�I�� false:�����p��
       */
      bool IsFinish() override;
    };
  } // namespace Mode
} // namespace AppFrame