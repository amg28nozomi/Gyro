/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  �Q�[�����̃G�l�~�[��HP�Q�[�W�̏�������N���X
 *
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
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
       * @brief  ������
       * @param  valu �Q�[�W�̍ő�l
       * @return true
       */
      bool Init(float value) override;
      /**
       * @brief �X�V
       */
      bool Process() override;
      /**
       * @brief �`��
       * @param position ���W
       * @param height ���W
       */
      bool Draw(const AppFrame::Math::Vector4 position, const float height) const;
      /**
       * @brief �摜�̓ǂݍ���
       */
      void LoadGraphs();
      /**
       * @brief �摜�̉��
       */
      void ReleaseGraph();
    private:
      AppFrame::Math::Vector4 _position;  //!< ���W
      int _gaugeFrontHandle{ 0 }; //!< HP�Q�[�W�摜(��)
      int _gaugeBackHandle{ 0 };  //!< HP�Q�[�W�摜(��)
      int _hpFrame{ 0 };          //!< HP�t���[���摜(�O�g)
    };
  } // namesapce Gauge
} // namespace Gyro
