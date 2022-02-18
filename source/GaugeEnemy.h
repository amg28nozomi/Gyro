/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  �Q�[�����̃G�l�~�[��HP�Q�[�W�̏�������N���X
 *
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
#include "GaugeServer.h"
#include "ObjectBase.h"
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
    class GaugeEnemy : public Gauge::GaugeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      GaugeEnemy(Application::ApplicationMain& app);
      /**
       * �f�X�g���N�^
       */
      ~GaugeEnemy();
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
      AppFrame::Math::Vector4 _position;  //!< ���W
      int _handle{ 0 };
      int _handle2{ 0 };
      int _handle3{ 0 };
    };
  } // namesapce Gauge
} // namespace Gyro
