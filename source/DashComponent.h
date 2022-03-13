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
       * @return true
       */
      bool Process();
      /**
       * @brief  �_�b�V���̐ݒ�
       * @param  direction ����
       * @param  power ���ړ���
       * @param  totalTime �_�b�V������
       * @return true:�J�ڊ��� false:�J�ڎ��s
       */
      bool SetDash(const AppMath::Vector4& direction, const float power, float totalTime);
      /**
       * @brief �C���^�[�o���̐ݒ�
       */
      void SetIniterval(const float interval);
      /**
       * @brief �C���^�[�o������
       */
      bool Interval();
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
       * @brief  �_�b�V����Ԃ��̔���
       * @return true:�_�b�V����� false:�_�b�V����Ԃł͂Ȃ�
       */
      bool IsDash() const {
        return _dashState == DashState::Active;
      }
      /**
       * @brief  �C���^�[�o�������邩�̔���
       * @return true:�C���^�[�o���� false:�C���^�[�o���ł͂Ȃ�
       */
      bool IsInterval() const {
        return _dashState == DashState::Interval;
      }
      /**
       * @brief  �_�b�V���̏I������
       * @return true:�I�� false:���I��
       */
      bool GetDashEnd() const {
        return _dashEnd;
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
      // �I������
      bool _dashEnd{false};
      //!< �ړ���
      AppMath::Vector4 _move{};
      //!< �i�s�����x�N�g��
      AppMath::Vector4 _direction{};
    };
  } // namespace Object
} // namespace Gyro