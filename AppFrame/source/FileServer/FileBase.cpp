/*****************************************************************//**
 * @file   FileBase.cpp
 * @brief  ファイルデータを保持するスーパークラスの定義
 *
 * @author 鈴木希海
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
      // ファイルは存在しているか
      if (!std::filesystem::exists(filePath)) {
        Clear();
        return; // 対象ファイルは存在しない
      }
      _path = filePath;
    }

    FileBase::FileBase(std::filesystem::path filePath, std::string_view key) {
      // ファイルは存在しているか
      if (!std::filesystem::exists(filePath)) {
        Clear();
#ifdef _DEBUG
        throw std::logic_error("ファイルのパスが不正です\n");
#endif
        return;
      }
      _path = filePath;
      _key = key.data();
    }

    void FileBase::Clear() {
      // メンバの解放
      _path.clear();
      _key.clear();
    }

    FileBase::~FileBase() {
      Clear();
    }
  } // namespace FileServer
} // namespace AppFrame