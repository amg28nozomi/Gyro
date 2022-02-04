/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  �Q�[�����̃g���b�N�Q�[�W�̏�������N���X
 *
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
#include "GaugeServer.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �Q�[�W
   */
  namespace Gauge {
    /**
     * @class �Q�[�WHP
     * @brief �Q�[������HP�̏�������N���X
     */
    class GaugeTrick : public Gauge::GaugeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      GaugeTrick();
      /**
       * �f�X�g���N�^
       */
      ~GaugeTrick();
      /**
       * @brief ������
       */
      bool Init() override;
      /**
       * @brief �X�V
       */
      bool Process() override;
      /**
       * @brief �`��
       */
      bool Draw() const override;
    private:
    };
  } // namesapce Gauge
} // namespace Gyro