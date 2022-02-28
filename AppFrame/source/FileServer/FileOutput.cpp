/*****************************************************************//**
 * @file   FileOutput.cpp
 * @brief  ファイルの入出力クラスの定義
 *
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "FileOutput.h"
#include <Windows.h>
#include <fstream>

namespace AppFrame {
  namespace FileServer {

    FileOutput::FileOutput(std::filesystem::path path) : _file(path) {
    }

    FileOutput::~FileOutput() {
      _file.clear();
    }

    bool FileOutput::OutputText(std::string_view text) {
      if (!IsPath(_file)) {
#ifdef _DEBUG
        OutputDebugString("ファイルへの出力に失敗しました\n");
#endif
        return false; // パスが不正
      }
      std::ofstream output(_file.string(), std::ios::app);
      if (!output) {
#ifdef _DEBUG
        std::string message(_file.filename().string() + "を開けませんでした\n");
        OutputDebugString(message.data());
#endif
        return false; // 処理失敗
      }
      output << text.data();
      output.close();
      return true; // 出力成功
    }

    bool FileOutput::SetFilePath(std::filesystem::path file) {
      if (!IsPath(file)) {
        return false; // 非対応
      }
      // 対象ファイルと現在のファイルは一致していないか
      if (_file == file) {
#ifdef _DEBUG
        std::string message(file.string() + ":同一ファイルです。異なるファイルを設定して下さい\n");
        OutputDebugString(message.data());
        return false;
#endif
      }
      _file = file;
      return true;  // 設定完了
    }

    bool FileOutput::IsPath(std::filesystem::path path) {
      // 拡張子は対応しているか
      bool flag = path.extension() == ".text";
      if (!flag) {
#ifdef _DEBUG
        OutputDebugString("拡張子が不正です\n");
#endif
        return false; // テキストファイルではない
      }
      // パスは有効か
      if (!std::filesystem::exists(path)) {
        // 有効ではない
#ifdef _DEBUG
        std::string message(path.string() + ":パスが有効ではありません\n");
        OutputDebugString(message.data());
#endif
        return false;
      }
      return true; // 有効
    }
  } // namespace FileServer
} // namespace AppFrame