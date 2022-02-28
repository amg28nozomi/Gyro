/*****************************************************************//**
 * @file   SoundMem.h
 * @brief  �����t�@�C�����N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include <tuple>
#include "../FileServer/FileBase.h"
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �T�E���h�x�[�X
   */
  namespace Sound {
    /**
     * @class SoundMem
     * @brief �����t�@�C���N���X
     */
    class SoundMem : public FileServer::FileBase {
    public:
      /**
       * @brief �������̐���
       * @param filePath �����t�@�C���̃p�X
       */
      SoundMem(std::filesystem::path filePath, const int playType);
      /**
       * @brief  �T�E���h�n���h���̎擾
       * @return �T�E���h�n���h��
       */
      inline const int GetSoundHandle() const {
        return _soundHandle;
      }
      /**
       * @brief  �Đ��^�C�v�̎擾
       * @return �Đ��^�C�v
       */
      inline const int GetPlayType() const {
        return _playType;
      }
      /**
       * @brief  �������̎擾
       * @return �T�E���h�n���h�� �Đ��^�C�v
       */
      inline const std::pair<int, int> GetSoundData() const {
        return { _soundHandle, _playType };
      }
    private:
      int _soundHandle; //!< �T�E���h�n���h��
      int _playType;    //!< �Đ��^�C�v
    };
  } // namespace Sound
} // namespace AppFrame