/*****************************************************************//**
 * @file   SoundComponent.h
 * @brief  �T�E���h�R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <string_view>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationBase;
  } // namespace Application
  /**
   * @brief �T�E���h�x�[�X
   */
  namespace Sound {
    constexpr auto Play = true;  //!< �T�E���h�Đ���
    constexpr auto Stop = false; //!< �T�E���h��~��
    /**
     * @class SoundComponent
     * @brief �T�E���h�R���|�[�l���g
     */
    class SoundComponent {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      SoundComponent(Application::ApplicationBase& app);
      /**
       * @brief  �T�E���h�̃o�b�N�O���E���h�Đ�
       * @param  key �T�E���h�ɕR�Â���ꂽ������
       * @return true:�Đ����� false:�Đ����s
       */
      bool PlayBackGround(std::string_view key) const;
      /**
       * @brief  �T�E���h�̃��[�v�Đ�
       * @param  key �T�E���h�ɕR�Â���ꂽ������
       * @return true:�Đ����� false:�Đ����s
       */
      bool PlayLoop(std::string_view key) const;
      /**
       * @brief  �w�肵�������̍Đ����~����
       * @param  key �T�E���h�ɕR�Â���ꂽ������
       * @return true:��~���� false:�L�[���s��
       */
      bool StopSound(std::string_view key) const;
      /**
       * @brief  �Ώۉ������Đ�����Ă��邩�̔���
       * @param  key �T�E���h�ɕR�Â���ꂽ������
       * @return true:�Đ��� false:�Đ�����Ă��Ȃ�
       */
      bool CheckSound(std::string_view key) const;
      /**
       * @brief  �w�肵���T�E���h�̉��ʂ�ݒ肷��
       * @param  key �T�E���h�ɕR�Â���ꂽ������
       * @param  volume �Đ�����(0~255)
       * @return true:�ݒ萬�� false:���s
       */
      bool SetVolume(std::string_view key, int volume) const;
      /**
       * @brief  �~���[�g�t���O�̐ݒ�
       * @param  flag �Z�b�g����t���O
       */
      inline void SetMute(const bool flag) {
        _mute = flag;
      }
    private:
      Application::ApplicationBase& _app; //!< �A�v���P�[�V�����̎Q��
      bool _mute{false}; //!< �~���[�g�t���O
      /**
       * @brief  �T�E���h�̍Đ�
       * @param  key �T�E���h�ɕR�Â���ꂽ������
       * @param  type �Đ��^�C�v
       * @return true:�Đ����� false:�Đ����s
       */
      bool Play(std::string_view key, const int type) const;
      /**
       * @brief  �T�E���h�n���h���̎擾
       * @return �擾�����T�E���h�n���h����Ԃ�
       *         �擾�Ɏ��s�����ꍇ��-1��Ԃ�
       */
      const int SoundHandle(std::string_view key) const;
    };
  } // namespace Sound;
} // namespace Gyro