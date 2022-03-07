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

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class ObjectBase; //!< �O���錾
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
       * @param owner ���L�҂̎Q��
       */
      DashComponent(ObjectBase& onwer);
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
       * @param dashPower ���ړ���
       * @param totalTime �_�b�V������
       * @param playSpeed �Đ����x
       */
      void SetDash(const float dashPower, float totalTime, float playSpeed);
      /**
       * @brief �C���^�[�o���̐ݒ�
       */
      void SetIniterval(const float interval);
      /**
       * @brief �C���^�[�o������
       */
      void Interval();
      /**
       * @brief  �ړ��ʂ̎擾
       * @return �ړ���
       */
      AppMath::Vector4 GetMovePower() const {
        return _move;
      }
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
      //!< ���L�҂̎Q��
      ObjectBase& _owner;
      //!< �_�b�V�����
      DashState _dashState{DashState::NoActive};
      //!< �ړ���
      float _power{0.0f};
      //!< �C���^�[�o������
      float _intervalTime{0.0f};
      //!< ������
      int _count{0};
      //!< �ړ���
      AppMath::Vector4 _move{};
    };
  } // namespace Object
} // namespace Gyro