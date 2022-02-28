/*****************************************************************//**
 * @file   FileBase.cpp
 * @brief  �t�@�C���f�[�^��ێ�����X�[�p�[�N���X�̒�`
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "FileBase.h"
#ifdef _DEBUG
#include <stdexcept>
#endif

namespace AppFrame {
  namespace FileServer {

    FileBase::FileBase() {
      Clear();
    }

    FileBase::FileBase(std::filesystem::path filePath) {
      // �t�@�C���͑��݂��Ă��邩
      if (!std::filesystem::exists(filePath)) {
        Clear();
        return; // �Ώۃt�@�C���͑��݂��Ȃ�
      }
      _path = filePath;
    }

    FileBase::FileBase(std::filesystem::path filePath, std::string_view key) {
      // �t�@�C���͑��݂��Ă��邩
      if (!std::filesystem::exists(filePath)) {
        Clear();
#ifdef _DEBUG
        throw std::logic_error("�t�@�C���̃p�X���s���ł�\n");
#endif
        return;
      }
      _path = filePath;
      _key = key.data();
    }

    void FileBase::Clear() {
      // �����o�̉��
      _path.clear();
      _key.clear();
    }

    FileBase::~FileBase() {
      Clear();
    }
  } // namespace FileServer
} // namespace AppFrame