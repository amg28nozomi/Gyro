/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  �Q�[���Q�[�W�̊��N���X
 *
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �Q�[�W�x�[�X
   */
  namespace Gauge {
    /**
     * @class GaugeBase
     * @brief �Q�[�W�x�[�X
     */
    class GaugeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      GaugeBase(Application::ApplicationMain& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~GaugeBase() = default;
      /**
       * @brief  ����������
       * @param  value �Q�[�W�̍ő�l
       * @return true
       */
      virtual bool Init(float value);
      /**
       * @brief  �X�V����
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  �`�揈��
       * @return true
       */
      virtual bool Draw() const;
      /**
       * @brief �Q�[�W�̑���
       * @param value �l
       */
      void Add(float value);
      /**
       * @brief �Q�[�W�̌���
       * @param value �l
       */
      void Sub(float value);
      /**
       * @brief  �ΏۃQ�[�W�Ƃ̔�r
       * @param  gauge ��r�Ώ�
       * @return true:�Ώۈȏ� false:�Ώۖ���
       */
      inline bool IsBig(const GaugeBase gauge) const {
          return gauge._point <= _point;
      }
      /**
       * @brief  �Q�[�W�|�C���g�̎擾(�����l)
       * @return �����l�ɃL���X�g�����Q�[�W�|�C���g
       */
      inline int GetIntPoint() const {
          return static_cast<int>(_point);
      }
      /**
       * @brief  �Q�[�W�|�C���g�̎擾(�P���x���������_��)
       * @return ���̃Q�[�W�|�C���g
       */
      inline float GetFloatPoint() const {
          return _point;
      }
      /**
       * @brief  �Q�[�W�̒l�̎擾
       * @return �Q�[�W�̒l
       */
      float Getvalue() const {
        return _value;
      }
      /**
       * @brief  ����l�̎擾
       * @return ����l
       */
      inline float GetMaxGauge() const {
        return _maxGauge;
      }
    protected:
      Application::ApplicationMain& _app; //!< �A�v���P�[�V�����̎Q��
      float _point{ 0 };       //!< �Q�[�W�|�C���g
      float _hitPoint{ 0 };    //!< �Q�[�W�|�C���g(HP�p)
      float _maxW{ 0 };        //!< �Q�[�W�̉���(�`�悷��ۂ̉���)
      float _maxGauge{ 0 };    //!< �Q�[�W�̉���(�ϓ�)
      float _value{ 0 };       //!< �l
    };
  }// namespace Gauge
}// namespace Gyro

