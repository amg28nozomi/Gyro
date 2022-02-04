/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  �Q�[������HP�Q�[�W�̏�������N���X
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
    class GaugeHP : public Gauge::GaugeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      GaugeHP();
      /**
       * �f�X�g���N�^
       */
      ~GaugeHP();
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
