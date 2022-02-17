/*****************************************************************//**
 * @file   InvincibleComponent.h
 * @brief  ���G�����p�̃R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {

  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    /**
     * @class InvincibleComponent
     * @brief ���G�����p�R���|�[�l���g
     */
    class InvincibleComponent : public ObjectComponent {
    public:
      /**
       * @brief  ���G��Ԃ�\���񋓌^�N���X
       */
      enum class InvincibleState {
        Normal,    //!< �ʏ���
        Invincible //!< ���G���
      };
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�������C���̎Q��
       */
      InvincibleComponent(Application::ApplicationMain& app);
      /**
       * @brief  ������
       */
      void Init() override;
      /**
       * @brief  ���G���Ԃ̐ݒ�
       * @param  limit �����G����
       */
      inline void Set(const int limit) {
        _limit = limit;
      }
      /**
       * @brief  ���G�����̊J�n
       */
      void Start() override;
      /**
       * @brief  ���G�����̏I��
       */
      void Finish() override;
      /**
       * @brief  �X�V����
       * @param  speed �o�ߎ���(�f�t�H���g��1)
       */
      void Process(const int speed = 1);
      /**
       * @brief  ���G��Ԃ��̔���
       * @return true:���G��� false:���G��Ԃł͂Ȃ�
       */
      bool Invincible() const {
        return _invincible == InvincibleState::Invincible;
      }
    protected:
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< ���G���
      InvincibleState _invincible{InvincibleState::Normal};
      //!< �����G����
      int _limit;
      //!< ���G����
      int _time;
      /**
       * @brief  ���G���Ԃ𒴉߂������̔���
       * @param  speed ����
       * @return true:�I�� false:�p��
       */
      bool TimeEnd(const int speed);
    };
  } // namespace Object
} // namespace Gyro