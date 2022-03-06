/*****************************************************************//**
 * @file   DashComponent.h
 * @brief  �_�b�V���R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class ObjectBase;
    /**
     * @class DashComponent
     * @brief �_�b�V���R���|�[�l���g�N���X
     */
    class DashComponent : public ObjectComponent {
    public:
      /**
       * @brief �_�b�V����Ԃ�\���񋓌^�N���X
       */
      enum class DashState {
        Active,   //!< �������
        NoActive, //!< �񊈓�
        Interval  //!< �ҋ@���
      };
      /**
       * @brief �R���X�g���N�^
       */
      DashComponent();
      /**
       * @brief ������
       */
      void Init() override;
      /**
       * @brief �J�n����
       */
      void Start() override;
      /**
       * @brief �I������
       */
      void Finish() override;
      /**
       * @brief  �X�V����
       * @param  move �ړ��ʂ��i�[���邽�߂̃x�N�g��4�N���X�̎Q��
       * @return true
       */
      bool Process(AppMath::Vector4& move);
      /**
       * @brief �_�b�V���̐ݒ�
       * @param move ���ړ���
       * @param time ���ړ�����
       */
      void SetMove(const AppMath::Vector4& move, float time);
      /**
       * @brief �C���^�[�o���̐ݒ�
       */
      void SetIniterval(const float interval);
      /**
       * @brief �C���^�[�o������
       */
      void Interval();
      /**
       * @brief  �_�b�V����Ԃ̎擾
       * @return �_�b�V�����
       */
      DashState GetDashState() const {
        return _dashState;
      }
      /**
       * @brief  �C���^�[�o�������邩�̔���
       * @return true:�C���^�[�o���� false:�C���^�[�o���ł͂Ȃ�
       */
      bool IsInterval() const {
        return _dashState == DashState::Interval;
      }
    private:
      //!< �_�b�V�����
      DashState _dashState{DashState::NoActive};
      //!< ���ړ���
      AppMath::Vector4 _length{};
      //!< �ړ���
      AppMath::Vector4 _move{};
      //!< �C���^�[�o������
      float _time{0.0f};
    };
  } // namespace Object
} // namespace Gyro