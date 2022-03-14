/*****************************************************************//**
 * @file    EffectBase.h
 * @brief   �G�t�F�N�g�̊��N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "Player.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief �G�t�F�N�g�x�[�X
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    /**
     * @class EffectBase
     * @brief �G�t�F�N�g�̊��N���X
     */
    class EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectBase(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectBase();
      /**
       * @brief  ������
       */
      virtual void Init();
      /**
       * @brief  �X�V
       */
      virtual void Process();
      /**
       * @brief  �G�t�F�N�g�Đ�
       */
      virtual void PlayEffect();
      /**
       * @brief  �G�t�F�N�g����
       */
      virtual void DeadEffect();
      /**
       * @brief  �G�t�F�N�g�ʒu�E�����ݒ�
       * @param  position �ʒu
       * @param  radian ����(y��], ���W�A��)
       */
      virtual void SetEffectParameter(const AppMath::Vector4 position, const float radian) {
        _ePos = position, _eRadY = radian;
      }
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S���
       *         false:����ł��Ȃ�
       */
      virtual bool IsDead() const {
        return _effectState == EffectState::Dead;
      }

    protected:
      /**
       * @brief  �G�t�F�N�g�̏�Ԃ�\���񋓌^�N���X
       */
      enum class EffectState {
        Active,  //!< �������
        Paused,  //!< ��~���
        Dead     //!< ���S���
      };
      /**
       * @brief  �v���C���[��Ԃ̊m�F
       */
      virtual void CheckPlayerState();
      /**
       * @brief  �G�t�F�N�g�ǂݍ��݃n���h���̎擾
       * @param  key �G�t�F�N�g�L�[
       * @return �w�肵���G�t�F�N�g�̓ǂݍ��݃n���h��
       *         �L�[���L���łȂ��ꍇ-1��Ԃ�
       */
      virtual int GetEffectHandle(const std::string_view key) {
        return _app.GetEffectLoadServer().GetEffectHandle(key);
      }

      int _effectHandle{ -1 };  //!< �G�t�F�N�g�ǂݍ��݃n���h��
      int _playHandle{ -1 };    //!< �G�t�F�N�g�Đ��n���h��
      AppMath::Vector4 _ePos;   //!< �G�t�F�N�g�ʒu
      float _eRadY{ 0.0f };     //!< �G�t�F�N�gy����(���W�A��)
      int _playLag{ 0 };        //!< ��������Đ��܂ł̃��O
      int _lagCount{ 0 };       //!< ���O�J�E���g
      bool _isPlay{ false };    //!< �Đ�����
      bool _isCheck{ false };   //!< �v���C���[��Ԋm�F�̗L��

      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //! �G�t�F�N�g�̏�ԕێ��ϐ�
      EffectState _effectState{ EffectState::Paused };
      //!< �v���C���[��Ԃ��r����ϐ�
      Player::Player::PlayerState _checkState{ Player::Player::PlayerState::Idle };
    };
  } // namespace Effect
} // namespace Gyro