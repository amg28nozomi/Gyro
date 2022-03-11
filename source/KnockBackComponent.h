/*****************************************************************//**
 * @file   KnockBackComponent.h
 * @brief  �m�b�N�o�b�N�@�\�N���X
 * 
 * @author �y������
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include "appframe.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application
  namespace AppMath = AppFrame::Math;
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class EnemyBase;  //!< �G�l�~�[�x�[�X
    class ObjectBase; //!< �I�u�W�F�N�g�x�[�X
    /**
     * @class KnockBackComponent
     * @brief �m�b�N�o�b�N�p�R���|�[�l���g
     */
    class KnockBackComponent : public ObjectComponent {
    public:
      /**
       * @brief �m�b�N�o�b�N��Ԃ�\���񋓌^�N���X
       */
      enum class KnockBackState {
        NonActive,  // �m�[�A�N�V����
        Active,     // �������
      };
      /**
       * @brief �R���X�g���N�^
       */
      KnockBackComponent(ObjectBase& owner, Application::ApplicationMain& app);
      /**
       * @brief �m�b�N�o�b�N�����̊J�n
       */
      void Start() override;
      /**
       * @brief �m�b�N�o�b�N�̏I��
       */
      void Finish() override;
      /**
       * @brief  �m�b�N�o�b�N�̍X�V
       * @return true:����I�� false:�m�b�N�o�b�N��Ԃł͂Ȃ�
       */
      bool Process();
      /**
       * @brief  �m�b�N�o�b�N��Ԃ��̔���
       * @return true:�m�b�N�o�b�N�� false:�m�b�N�o�b�N��Ԃł͂Ȃ�
       */
      bool IsKnockBack() const {
        return _state == KnockBackState::Active;
      }
      /**
       * @brief  �m�b�N�o�b�N��Ԃ̎擾
       * @return �m�b�N�o�b�N���
       */
      const KnockBackState& GetState() {
        return _state;
      }
      /**
       * @brief  �ړ���(�x�N�g��)�̎擾
       * @return �ړ��ʃx�N�g��
       */
      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    protected:
      ObjectBase& _owner;                 //!< ���L�҂̎Q��
      //std::shared_ptr<EnemyBase> _enemy;  //!< �G�l�~�[
      Application::ApplicationMain& _app; //!< �A�v���P�[�V�����̎Q��
      KnockBackState _state;              //!< �m�b�N�o�b�N���
      AppMath::Vector4 _move{};           //!< �m�b�N�o�b�N�̈ړ���
      int _cnt{ 0 };                      //!< �J�E���g
    };
  } // namespace Player
} // namespace Gyro