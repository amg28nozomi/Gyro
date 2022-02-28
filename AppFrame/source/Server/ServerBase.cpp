/*****************************************************************//**
 * @file   ServerBase.h
 * @brief  �T�[�o�̊��N���X�̒�`
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "ServerBase.h"
#include <vector>
namespace AppFrame {
  namespace Server {
  } // export namespace Server
} // namespace AppFrame

//namespace AppFrame {
//  namespace Data {
//
//#ifndef _DEBUG
//    template <typename T, typename I>
//    ServerBase<T, I>::ServerBase() {
//      _registry.clear();
//    }
//
//    ServerBase<FileServer::FileBase, std::filesystem::path>::ServerBase() {
//      _registry.clear();
//    }
//#else
//    template <typename T, typename I>
//    ServerBase<T, I>::ServerBase(const bool flag) {
//      _registry.clear();
//      _name = "ServerBase";
//      _debug = flag;
//    }
//
//    ServerBase<FileServer::FileBase, std::filesystem::path>::ServerBase(const bool flag) {
//      _registry.clear();
//      _name = "ServerBase";
//      _debug = flag;
//    }
//#endif
//
//    //template<typename T, typename I>
//    //ServerBase<T, I>::~ServerBase() {
//    //}
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::Init() {
//      _registry.clear();
//      return true;
//    }
//
//    bool ServerBase<FileServer::FileBase, std::filesystem::path>::Init() {
//      _registry.clear();
//      return true;
//    }
//
//    //template <typename T, typename I>
//    //bool ServerBase<T, I>::Register(std::string_view key, const I value) {
//    //}
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::LoadFiles(std::vector<FileServer::FileBase> files) {
//      // �t�@�C���͑��݂��邩�H
//      if (files.empty()) {
//        return false; // �f�[�^����
//      }
//      for (auto file : files) {
//        auto [key, path] = file.GetFileData();
//        // �L�[�͊��ɓo�^����Ă��邩
//        if (_registry.contains(key.data())) {
//          continue; // �o�^�ς�
//        }
//        // �p�X�͗L����
//        if (!std::filesystem::exists(path)) {
//          continue; // �L���ł͂Ȃ�
//        }
//#ifndef _DEBUG
//        Register(key, path); // �o�^�����Ɉڍs
//#else
//        try {
//          Register(key, path);
//        } catch (std::logic_error error) {
//          // ��O������ꍇ�͏o��
//          DebugString(error.what());
//        }
//#endif
//      }
//      return true; // �����I��
//    }
//
//    bool ServerBase<FileServer::FileBase, std::filesystem::path>::LoadFiles(std::vector<FileServer::FileBase> files) {
//      // �t�@�C���͑��݂��邩�H
//      if (files.empty()) {
//        return false; // �f�[�^����
//      }
//      for (auto file : files) {
//        auto [key, path] = file.GetFileData();
//        // �L�[�͊��ɓo�^����Ă��邩
//        if (_registry.contains(key.data())) {
//          continue; // �o�^�ς�
//        }
//        // �p�X�͗L����
//        if (!std::filesystem::exists(path)) {
//          continue; // �L���ł͂Ȃ�
//        }
//#ifndef _DEBUG
//        Register(key, path); // �o�^�����Ɉڍs
//#else
//        try {
//          Register(key, path);
//        }
//        catch (std::logic_error error) {
//          // ��O������ꍇ�͏o��
//          DebugString(error.what());
//        }
//#endif
//      }
//      return true; // �����I��
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::IsTarget(FileServer::FileBase file, std::string_view extension) const {
//      // �L�[�Ɏg�p���镶����ƃt�@�C���p�X
//      auto [key, path] = file.GetFileData();
//#ifndef _DEBUG
//      // �t�@�C���`���͈�v���Ă��邩
//      if (!HasExtension(path, extension)) {
//        return false; // �t�@�C���`�����قȂ�
//      }
//      // �t�@�C���͑��݂��邩
//      if (!Exist(path)) {
//        return false; // �p�X���L���ł͂Ȃ�
//      }
//#else
//      try {
//        HasExtension(path, extension);
//        Exist(path);
//      } catch (std::logic_error error) {
//        DebugString(error); // ��O�����������ꍇ�͏o��
//        return false;
//      }
//#endif
//      return true;  // �o�^�Ώ�
//    }
//
//    bool ServerBase<FileServer::FileBase, std::filesystem::path>::IsTarget(FileServer::FileBase file, std::string_view extension) const {
//      // �L�[�Ɏg�p���镶����ƃt�@�C���p�X
//      auto [key, path] = file.GetFileData();
//#ifndef _DEBUG
//      // �t�@�C���`���͈�v���Ă��邩
//      if (!HasExtension(path, extension)) {
//        return false; // �t�@�C���`�����قȂ�
//      }
//      // �t�@�C���͑��݂��邩
//      if (!Exist(path)) {
//        return false; // �p�X���L���ł͂Ȃ�
//      }
//#else
//      try {
//        HasExtension(path, extension);
//        Exist(path);
//      }
//      catch (std::logic_error error) {
//        DebugString(error.what()); // ��O�����������ꍇ�͏o��
//        return false;
//      }
//#endif
//      return true;  // �o�^�Ώ�
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::Exist(std::filesystem::path filePath) const {
//      // �t�@�C���͑��݂��邩
//      auto flag = std::filesystem::exists(filePath);
//#ifdef _DEBUG
//      if (!flag) {
//        // �t�@�C�������݂��Ȃ��ꍇ
//        throw LogicError(filePath.string() + ":�t�@�C�������݂��܂���");
//      }
//#endif
//      return flag;
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::HasExtension(std::filesystem::path filePath, std::string_view extension) const {
//      if (extension.empty()) {
//        return true; // �g���q�̎w��Ȃ�
//      }
//#ifndef _DEBUG
//      return _filePath.stem() == extension;
//#else
//      if (filePath.stem() != extension) {
//        throw LogicError(filePath.string() + ":�g���q����v���Ă��܂���");
//        return false; // ���v
//      }
//      return true; // ��v
//#endif
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::UseKey(std::string_view key) const {
//#ifndef _DEBUG
//      // �L�[�͎g�p�\��
//      return !_registry.contains(key.data());
//#else
//      if (_registry.contains(key.data())) {
//        std::string message = key.data();
//        throw LogicError(message + ":�͊��ɓo�^����Ă��܂�");
//        return false; // �o�^�ς�
//      }
//      return true; // ���g�p
//#endif
//    }
//
//#ifdef _DEBUG
//    template <typename T, typename I>
//    std::logic_error ServerBase<T, I>::LogicError(std::string_view message) const {
//      // �w�肵���`���ɏC��
//      std::string m = _name + ":" + message.data() + "\n";
//      return std::logic_error(m);
//    }
//
//    template <typename T, typename I>
//    void ServerBase<T, I>::DebugString(std::string_view message) const {
//      OutputDebugString(message.data());
//      if (_debug) {
//        // ���O�ւ̏����o�����s��
//      }
//    }
//#endif
//  } // namespace Data
//} // namespace AppFrame