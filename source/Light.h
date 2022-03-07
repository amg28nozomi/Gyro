/*****************************************************************//**
 * @file   Light.h
 * @brief  ���[�h�Q�[�����̃��C�g�N���X
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
   * @brief ���C�g
   */
  namespace Light {
    /**
     * @class Light
     * @brief ���[�h�Q�[���p���C�g�N���X
     */
    class Light {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      Light();
      /**
       * @brief �f�X�g���N�^
       */
      ~Light();
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
    };
  } // namespace Light
} // namespace Gyro