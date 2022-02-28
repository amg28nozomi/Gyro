/*****************************************************************//**
 * @file   ServerBase.h
 * @brief  �T�[�o�̊��N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#ifdef _DEBUG
#include <stdexcept>
#include <Windows.h>
#endif
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �T�[�o�x�[�X
   */
  namespace Server {
    /**
     * @class ServerBase
     * @brief �T�[�o�̃e���v���[�g
     */
    template <typename T>
    class ServerBase {
    public:
      /**
       * @brief �T�[�o�̏�Ԃ�\���񋓌^�N���X
       */
      enum class ServerState {
        Active, // ����
        Paused, // ��~
        Error   // �ُ�
      };
      /**
       * @brief �R���X�g���N�^
       */
      ServerBase();
      /**
       * @brief �f�X�g���N�^
       */
      virtual ~ServerBase() = default;
      /**
       * @brief  ������
       * @return true:���������� false:���������s
       */
      virtual bool Init();
      /**
       * @brief  �ێ����Ă��郊�\�[�X�̉������
       *         �h����ŕK���Ē�`���s��
       * @return true:������� false:��蔭��
       */
      virtual bool Release() = 0;
    protected:
      ServerState _state; //!< ���
      T _registry{};      //!< �f�[�^�x�[�X
#ifdef _DEBUG
      std::string _name;  //!< �T�[�o��
      /**
       * @brief �f�o�b�O�����Ŏg�p����T�[�o���̐ݒ�
       * @param name �T�[�o��
       */
      void SetServerName(std::string_view name);
      /**
       * @brief  logic_error�̐���
       * @param  message �o�͂��镶����
       * @return logic_error
       */
      virtual std::logic_error LogicError(std::string_view message) const;
      /**
       * @brief �f�o�b�O�p���b�Z�[�W�̏o��
       * @param message �f�o�b�O�p�̕�����
       */
      virtual void DebugString(std::string_view message) const;
#endif
    };
    /**
     * @brief �R���X�g���N�^�̒�`
     */
    template <typename T>
    ServerBase<T>::ServerBase() {
      _state = ServerState::Active;
    }
    /**
     * @brief �������̒�`
     */
    template <typename T>
    bool ServerBase<T>::Init() {
#ifndef _DEBUG
      // ���\�[�X�̉�������ɐ���������
      if (!Release()) {
        _state = ServerState::Error;
        return false; // ���s
      }
      return true;    //����I��
#else
      bool flag;
      try {
        flag = Release(); // ���\�[�X�̉��
      }
      catch (std::logic_error error) {
        // ��O��catch�����ꍇ�́A�o�͂��s��
        DebugString(error.what());
      }
      // ����Ɏ��s�����ꍇ�̓G���[��ԂɑJ�ڂ���
      if (!flag) {
        _state = ServerState::Error;
      }
      return flag;
#endif
    }

#ifdef _DEBUG
    template <typename T>
    void ServerBase<T>::SetServerName(std::string_view name) {
      _name = name.data(); // �����̕�������T�[�o���Ƃ��Ďg�p����
    }

    template <typename T>
    std::logic_error ServerBase<T>::LogicError(std::string_view message) const {
      std::string error = _name + ":" + message.data() + "\n";
      return std::logic_error(error);
    }

    template <typename T>
    void ServerBase<T>::DebugString(std::string_view message) const {
      // �f�o�b�O�E�B���h�E�ɏo�͂���
      OutputDebugString(message.data());
    }
#endif
  } // namespace Server
//  namespace FileServer {
//    class FileBase;
//  }
//  /**
//   * @brief �f�[�^�x�[�X
//   */
//  namespace Data {
//    /**
//     * @class ServerBase
//     * @brief �T�[�o�̊��ƂȂ�e���v���[�g�N���X
//     * @tparam T �A�z�z��̒l�ɊY������^
//     * @tparam I �o�^�����Ŏg�p����^
//     */
//    template <typename T, typename I>
//    class ServerBase {
//    public:
//#ifndef _DEBUG
//      /**
//       * @brief  �R���X�g���N�^(Release)
//       */
//      ServerBase();
//#else
//      /**
//       * @brief  �R���X�g���N�^(Debug)
//       * @param  flag ���O�o�̓t���O(�f�t�H���g�ł�false)
//       */
//      ServerBase(const bool flag = false);
//#endif
//      /**
//       * @brief  �f�X�g���N�^
//       */
//      virtual ~ServerBase() = default;
//      /**
//       * @brief  ������
//       */
//      virtual bool Init();
//      /**
//       * @brief  �������
//       * @return true:�������� false:��蔭��
//       */
//      virtual bool Release() = 0;
//      /**
//       * @brief  �o�^�����p�������z�֐�
//       *         �o�^�����͔h���N���X���Ŏ������邱��
//       * @param  key �o�^�Ɏg�p���镶����
//       * @param  value �o�^����l
//       * @return true:�o�^���� false:�o�^���s
//       */
//      virtual bool Register(std::string_view key, const I value) = 0;
//      /**
//       * @brief  �t�@�C�����̓ǂݍ���
//       * @param  files �t�@�C�����
//       * @return true:�������� false:��蔭��
//       */
//      virtual bool LoadFiles(std::vector<FileServer::FileBase> files);
//    protected:
//      std::unordered_map<std::string, T> _registry; //!< ���W�X�g���[
//      /**
//       * @brief  �Ώۃt�@�C�������݂��邩�̔���
//       * @param  filePath �Ώۃt�@�C���̃p�X
//       * @return true:�t�@�C���͑��݂��� false:�t�@�C���͑��݂��Ȃ�
//       * @throw  Debug:�p�X���L���ł͂Ȃ��ꍇ�Alogic_error��Ԃ�
//       */
//      bool Exist(std::filesystem::path filePath) const;
//      /**
//       * @brief  �t�@�C���g���q����v���Ă��邩�̔���(Debug)
//       * @param  filePath �t�@�C���̃p�X
//       * @param  extension �Ή�����t�@�C���g���q
//       * @return true:��v false:��v���Ă��Ȃ�
//       * @throw  ��v���Ă��Ȃ��ꍇ�Alogic_error��Ԃ�
//       */
//      bool HasExtension(std::filesystem::path filePath, std::string_view extension) const;
//      /**
//       * @brief  �L�[���g�p�\���̔���
//       * @param  key ���W�X�g���ւ̓o�^�Ŏg�p���镶����
//       * @return true:�g�p�\ false:���łɎg�p����Ă���
//       */
//      bool UseKey(std::string_view key) const;
//      /**
//       * @brief  �Ώۃf�[�^���L�����̔���
//       * @param  file �t�@�C���f�[�^
//       * @param  extension �t�@�C���g���q(�f�t�H���g�͊g���q�Ȃ�)
//       * @return true:�L�� false:�L���ł͂Ȃ�
//       */
//      bool IsTarget(FileServer::FileBase file, std::string_view extension = "") const;
//#ifdef _DEBUG
//      std::string _name; //!< �T�[�o�[��
//      bool _debug;       //!< ���O�o�̓t���O
//      /**
//       * @brief  logic_error�̐���
//       * @param  message �g�p����G���[��
//       * @return �w�肵���`���ɕϊ�����logic_error
//       */
//      std::logic_error LogicError(std::string_view message) const;
//      /**
//       * @brief ���O�ւ̏o�͏���
//       * @param message �o�͂��镶����
//       */
//      void DebugString(std::string_view message) const;
//#endif
//    };
//  } // namespace Data
} // namespace AppFrame