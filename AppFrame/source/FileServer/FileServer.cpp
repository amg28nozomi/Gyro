/*****************************************************************//**
 * @file   FileServer.cpp
 * @brief  �t�@�C���f�[�^���Ǘ�����T�[�o�N���X�̒�`
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "FileServer.h"
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <Windows.h>
#include "LoadJson.h"

namespace {
  constexpr auto ServerName = "FileServer";
  constexpr auto LogText = "FileWorkerLog.txt"; // ���O�p�t�@�C����
} // namespace

namespace AppFrame {
  namespace FileServer {

    FileServer::FileServer(Application::ApplicationBase& app) : Server::ServerTemplateUnordered<std::string, std::filesystem::path>() {
      // LoadJson�̐���
      _loadJson = std::make_unique<LoadJson>(app);
      _extensions.clear();
#ifdef _DEBUG
      SetServerName("FileServer");
#endif
    }

    bool FileServer::Init() {
      using UnorderedServer = Server::ServerTemplateUnordered<std::string, std::filesystem::path>;
      return UnorderedServer::Init();
    }

    bool FileServer::LoadJsonFile(std::string_view jsonFile) const {
      // �Ώۂ�json�t�@�C����
      if (!_loadJson->IsJson(jsonFile)) {
        return false; // json�t�@�C���ł͂Ȃ�
      }
      // json�t�@�C���̏ꍇ�͓ǂݎ����s��
      _loadJson->LoadJsonFile(jsonFile.data());
      return true;
    }

    bool FileServer::SetExtension(std::vector<std::string> extensions) {
      // �t�@�C���`���̎w��͍s���Ă��邩
      if (_setExtension) {
        return false; // �o�^�ς�
      }
      for (auto extension : extensions) {
        // ��f�[�^�̏ꍇ�̓X�L�b�v
        if (extension.empty()) {
          continue;
        }
        // ����g���q���o�^����Ă��Ȃ����̔���
        for (auto number = 0; auto data : _extensions) {
          // �d�����Ă���ꍇ�͏��������[�v�I��
          if (extension == data) {
            break; // �d�����Ă���
          }
          ++number; // �����J�E���g�����Z
          // �S�v�f�̔��肪���������ꍇ�͖����ɓo�^
          if (number == static_cast<int>(_extensions.size())) {
            _extensions.emplace_back(extension); // �o�^
          }
        }
      }
      // �v�f�̗L���œo�^����������������
      _setExtension = !_extensions.empty();
      // �����ɐ��������ꍇ�͎g�p�̈��؂�l�߂�
      if (_setExtension) {
        _extensions.shrink_to_fit();
      }
#ifndef _DEBUG
      return _setExtension;
#else
      // �o�^�Ɏ��s�����ꍇ�͗�O��throw����
      else {
        throw LogicError("�g���q�̓o�^�Ɏ��s���܂���");
        return false; // �o�^���s
      }
      return true;    // �o�^����
#endif
    }

    bool FileServer::IsTarget(std::filesystem::path filePath, std::string_view extension) const {
      namespace fs = std::filesystem;
#ifndef _DEBUG
      // �p�X���L�����̔���
      if (!Exist(filePath)) {
        return false; // �p�X���s��
      }
      // �Ώۂ̃t�@�C���`���͗L����
      return HasExtension(filePath, extension);
#else
      auto flag = false;
      try {
        flag = Exist(filePath);
        if (flag) {
          flag = HasExtension(filePath, extension);
        }
      } catch (std::logic_error error) {
        DebugString(error.what()); // ��O�������͏o��
      }
      return flag; // �����t���O��Ԃ�
#endif
    }

    bool FileServer::HasExtension(std::filesystem::path filePath, std::string_view extension) const {
#ifndef _DEBUG
      return filePath.extension().string() == extension;
#else
      // �t�@�C���`���͈�v���Ă��邩�H
      if (filePath.extension().string() != extension) {
        throw LogicError(filePath.filename().string() + "�t�@�C���`�����L���ł͂���܂���");
        return false; // �t�@�C���`�����قȂ�
      }
      return true;    // �t�@�C���`���͗L��
#endif
    }

    bool FileServer::Exist(std::filesystem::path filePath) const {
      namespace fs = std::filesystem;
      // �p�X���L�����̔���
      if (!fs::exists(filePath)) {
#ifdef _DEBUG
        throw LogicError(filePath.string() + ":�t�@�C���p�X���L���ł͂���܂���");
#endif
        return false; // �p�X���s��
      }
      return true;    // �L��
    }


//
//#ifndef _DEBUG
//    FileServer::FileServer() : ServerBase() {
//    }
//#else
//    FileServer::FileServer(std::filesystem::path filePath) : ServerBase(), _fileLog(filePath) {
//      _name = ServerName;
//    }
//#endif
//
//    FileServer::~FileServer() {
//      Release();
//    }
//
//    bool FileServer::Init() {
//      return ServerBase::Init();
//    }
//
//    bool FileServer::Release() {
//      // �o�^����Ă���t�@�C�������ꊇ�폜����
//      _registry.clear();
//      return true;
//    }
//
//    bool FileServer::Register(std::string_view key, const std::filesystem::path path) {
//#ifndef _DEBUG
//      // �Ώۂ͓o�^�\���H
//      if (!IsTarget({key, path})) {
//        return false;
//      }
//#else
//      try {
//        IsTarget((key, path));
//      } catch (std::logic_error error) {
//        DebugString(error.what());
//        return false; // �o�^���s
//      }
//#endif
//      _registry.emplace(key, path); // ���W�X�g���ɓo�^
//      return true;
//    }
//
//    bool FileServer::LoadFiles(std::filesystem::path jsonPath) {
//#ifndef _DEBUG
//      // �p�X�͗L����
//      if (!IsTarget(jsonPath, ".json")) {
//        return false; // �ǂݎ��Ώۂł͂Ȃ�
//      }
//#else
//      try {
//        IsTarget(jsonPath, ".json");
//      } catch (std::logic_error error) {
//        DebugString(error.what());
//        return false;
//      }
//#endif
//      LoadJson::LoadJsonFile(jsonPath);
//      
//      return true;
//    }



//    FileServer::FileServer() : _debugLog(LogText) {
//      _debug = true;
//      _fileMap.clear();
//#ifdef _DEBUG
//      _debugLog = FileOutput(LogText);
//#endif
//      Release();
//    }
//
//    FileServer::~FileServer() {
//      Release();
//    }
//
//    bool FileServer::Init() {
//      Release();
//      return true;
//    }
//
//    void FileServer::Release() {
//      _fileMap.clear(); // ���
//    }
//
//    bool FileServer::LoadFileMap(std::filesystem::path jsonPath) {
//#ifdef _DEBUG
//      auto stringPath = jsonPath.string();
//#endif
//      // �Ώۃt�@�C���͑��݂��Ă��邩
//      if (!std::filesystem::exists(jsonPath)) {
//#ifdef _DEBUG
//        const std::string message(stringPath + ":�p�X���s���ł�");
//        DebugStringLog(message);
//#endif
//        return false; // �p�X���s��
//      }
//      // �Ώۂ�json�t�@�C�����̔���
//      if (!LoadJson::IsJson(jsonPath)) {
//#ifdef _DEBUG
//        const std::string message(stringPath + ":�Ώۂ�json�t�@�C���ł͂���܂���");
//        DebugStringLog(message);
//#endif
//        return false; // �t�@�C���`�����قȂ�
//      }
//      auto fileMap = LoadJson::LoadJsonFile(jsonPath); // �t�@�C�����
//      if (fileMap.empty()) {
//        return false; // �t�@�C����񂪋�
//      }
//      auto counter = 0; // �o�^���s��
//      // �擾�����t�@�C�����̓o�^
//      for (auto [key, value] : fileMap) {
//        if (_fileMap.contains(key)) {
//#ifdef _DEBUG
//          const std::string message = "�L�[:" + key + "�͊��ɓo�^����Ă��܂�";
//          DebugStringLog(message);
//#endif
//          ++counter;
//          continue;
//        }
//        _fileMap.emplace(key, value);
//      }
//#ifdef _DEBUG
//      // �r���A�o�^�����Ɏ��s�������H
//      if (counter) {
//        const std::string message(counter + "�񏈗��Ɏ��s���܂���");
//        DebugStringLog(message);
//      }
//#endif
//      return true; // �o�^�I��
//    }
//
//    bool FileServer::SetLogTextFlag(bool flag, std::filesystem::path logPath) {
//      return true;
//    }
//
//    bool FileServer::LoadFileMap(FileBaseMap& fileMap) {
//      return true;
//    }
//
//    bool FileServer::FileCheck(const std::filesystem::path path) {
//      return true;
//    }
//
//#ifdef _DEBUG
//    void FileServer::DebugStringLog(const std::string text) {
//      // ���O�ւ̏o��
//      std::string message("FileServer:" + text + "\n");
//      OutputDebugString(message.data());
//      if (!_debug) {
//        return;
//      }
//      // �e�L�X�g�t�@�C���ւ̏o��
//      _debugLog.OutputText(text);
//    }
//#endif
  } // namespace FileServer
} // namespace AppFrame