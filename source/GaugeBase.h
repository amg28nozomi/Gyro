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
       * @brief �Q�[�W���ʔԍ��̗񋓌^�N���X
       */
      enum class GaugeId {
        Gauge,  //!< �Q�[�W
        Player, //!< �v���C���[
        Enemy   //!< �G�l�~�[
      };
      /**
       * @brief �Q�[�W�̏�Ԃ�\���񋓌^�N���X
       */
      enum class GaugeState {
        Active, //!< �������
        Paused, //!< ��~���
        Dead    //!< ���S���
      };
      /**
       * @brief �R���X�g���N�^
       */
      GaugeBase(Application::ApplicationMain& app);
      /**
       * @brief �R���X�g���N�^
       * @param gauge �Q�[�W�|�C���g
       */
      GaugeBase(int gauge);
      /**
       * @brief �R���X�g���N�^
       * @param gauge �Q�[�W�|�C���g
       */
      GaugeBase(float gauge);
      /**
       * @brief �f�X�g���N�^
       */
      ~GaugeBase() = default;
      /**
       * @brief  ����������
       * @return true
       */
      virtual bool Init();
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
       * @brief  ���ʔԍ��̎擾
       * @return ���ʔԍ�
       */
      GaugeId GetId() const {
          return _id;
      }
      /**
       * @brief  ��Ԃ̎擾
       * @return ���
       */
      GaugeState GetState() const {
          return _state;
      }
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S��� false:����ł��Ȃ�
       */
      virtual bool IsDead() const {
          return _state == GaugeState::Dead;
      }
      /**
       * @brief �Q�[�W�̑���
       * @param value �l
       */
      void Add(float value);
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
      inline int GetInteger() const {
          return static_cast<int>(_point);
      }
      /**
       * @brief  �Q�[�W�|�C���g�̎擾(�P���x���������_��)
       * @return ���̃Q�[�W�|�C���g
       */
      inline float GetFloat() const {
          return _point;
      }
    protected:
      Application::ApplicationMain& _app; //!< �A�v���P�[�V�����̎Q��
      float _point{ 0 };       //!< �Q�[�W�|�C���g
      float _hitPoint{ 0 };    //!< �Q�[�W�|�C���g(HP�p)
      float _maxW{ 0 };        //!< �Q�[�W�̉���(�`�悷��ۂ̉���)
      float _maxGauge{ 0 };    //!< �Q�[�W�̉���(�ϓ�)
      float _value{ 0 };       //!< �l
      GaugeId _id{ GaugeId::Gauge }; //!< �Q�[�W�̎��ʔԍ�
      GaugeState _state{ GaugeState::Active }; //!< ���
    };
  }// namespace Gauge
}// namespace Gyro

