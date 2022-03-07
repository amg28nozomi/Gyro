/*****************************************************************//**
 * @file   Shadow.h
 * @brief  ���[�h�Q�[�����̃V���h�E�N���X
 * 
 * @author �y������
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �V���h�E
   */
  namespace Shadow {
    /**
     * @class Shadow
     * @brief ���[�h�Q�[���p�V���h�E�N���X
     */
    class Shadow {
    public:
      /**
       * @brief �R���X�g���N�^
       * 
       */
      Shadow(Application::ApplicationMain& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~Shadow();
      /**
       * @brief ����������
       */
      void Init();
      /**
       * @brief �X�V����
       */
      void Process();
      /**
       * @brief �`�揈��
       */
      void Draw() const;
    private:
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;

      int _shadowHandle; //!< �V���h�E�}�b�v�n���h��
    };
  } // namespace Shadow
} // namespace Gyro