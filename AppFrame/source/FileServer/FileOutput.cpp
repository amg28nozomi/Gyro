/*****************************************************************//**
 * @file   FileOutput.cpp
 * @brief  �t�@�C���̓��o�̓N���X�̒�`
 *
 * @author ��؊�C
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
        OutputDebugString("�t�@�C���ւ̏o�͂Ɏ��s���܂���\n");
#endif
        return false; // �p�X���s��
      }
      std::ofstream output(_file.string(), std::ios::app);
      if (!output) {
#ifdef _DEBUG
        std::string message(_file.filename().string() + "���J���܂���ł���\n");
        OutputDebugString(message.data());
#endif
        return false; // �������s
      }
      output << text.data();
      output.close();
      return true; // �o�͐���
    }

    bool FileOutput::SetFilePath(std::filesystem::path file) {
      if (!IsPath(file)) {
        return false; // ��Ή�
      }
      // �Ώۃt�@�C���ƌ��݂̃t�@�C���͈�v���Ă��Ȃ���
      if (_file == file) {
#ifdef _DEBUG
        std::string message(file.string() + ":����t�@�C���ł��B�قȂ�t�@�C����ݒ肵�ĉ�����\n");
        OutputDebugString(message.data());
        return false;
#endif
      }
      _file = file;
      return true;  // �ݒ芮��
    }

    bool FileOutput::IsPath(std::filesystem::path path) {
      // �g���q�͑Ή����Ă��邩
      bool flag = path.extension() == ".text";
      if (!flag) {
#ifdef _DEBUG
        OutputDebugString("�g���q���s���ł�\n");
#endif
        return false; // �e�L�X�g�t�@�C���ł͂Ȃ�
      }
      // �p�X�͗L����
      if (!std::filesystem::exists(path)) {
        // �L���ł͂Ȃ�
#ifdef _DEBUG
        std::string message(path.string() + ":�p�X���L���ł͂���܂���\n");
        OutputDebugString(message.data());
#endif
        return false;
      }
      return true; // �L��
    }
  } // namespace FileServer
} // namespace AppFrame