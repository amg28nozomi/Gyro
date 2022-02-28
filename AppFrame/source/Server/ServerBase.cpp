/*****************************************************************//**
 * @file   ServerBase.h
 * @brief  サーバの基底クラスの定義
 *
 * @author 鈴木希海
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
//      // ファイルは存在するか？
//      if (files.empty()) {
//        return false; // データが空
//      }
//      for (auto file : files) {
//        auto [key, path] = file.GetFileData();
//        // キーは既に登録されているか
//        if (_registry.contains(key.data())) {
//          continue; // 登録済み
//        }
//        // パスは有効か
//        if (!std::filesystem::exists(path)) {
//          continue; // 有効ではない
//        }
//#ifndef _DEBUG
//        Register(key, path); // 登録処理に移行
//#else
//        try {
//          Register(key, path);
//        } catch (std::logic_error error) {
//          // 例外がある場合は出力
//          DebugString(error.what());
//        }
//#endif
//      }
//      return true; // 処理終了
//    }
//
//    bool ServerBase<FileServer::FileBase, std::filesystem::path>::LoadFiles(std::vector<FileServer::FileBase> files) {
//      // ファイルは存在するか？
//      if (files.empty()) {
//        return false; // データが空
//      }
//      for (auto file : files) {
//        auto [key, path] = file.GetFileData();
//        // キーは既に登録されているか
//        if (_registry.contains(key.data())) {
//          continue; // 登録済み
//        }
//        // パスは有効か
//        if (!std::filesystem::exists(path)) {
//          continue; // 有効ではない
//        }
//#ifndef _DEBUG
//        Register(key, path); // 登録処理に移行
//#else
//        try {
//          Register(key, path);
//        }
//        catch (std::logic_error error) {
//          // 例外がある場合は出力
//          DebugString(error.what());
//        }
//#endif
//      }
//      return true; // 処理終了
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::IsTarget(FileServer::FileBase file, std::string_view extension) const {
//      // キーに使用する文字列とファイルパス
//      auto [key, path] = file.GetFileData();
//#ifndef _DEBUG
//      // ファイル形式は一致しているか
//      if (!HasExtension(path, extension)) {
//        return false; // ファイル形式が異なる
//      }
//      // ファイルは存在するか
//      if (!Exist(path)) {
//        return false; // パスが有効ではない
//      }
//#else
//      try {
//        HasExtension(path, extension);
//        Exist(path);
//      } catch (std::logic_error error) {
//        DebugString(error); // 例外が発生した場合は出力
//        return false;
//      }
//#endif
//      return true;  // 登録対象
//    }
//
//    bool ServerBase<FileServer::FileBase, std::filesystem::path>::IsTarget(FileServer::FileBase file, std::string_view extension) const {
//      // キーに使用する文字列とファイルパス
//      auto [key, path] = file.GetFileData();
//#ifndef _DEBUG
//      // ファイル形式は一致しているか
//      if (!HasExtension(path, extension)) {
//        return false; // ファイル形式が異なる
//      }
//      // ファイルは存在するか
//      if (!Exist(path)) {
//        return false; // パスが有効ではない
//      }
//#else
//      try {
//        HasExtension(path, extension);
//        Exist(path);
//      }
//      catch (std::logic_error error) {
//        DebugString(error.what()); // 例外が発生した場合は出力
//        return false;
//      }
//#endif
//      return true;  // 登録対象
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::Exist(std::filesystem::path filePath) const {
//      // ファイルは存在するか
//      auto flag = std::filesystem::exists(filePath);
//#ifdef _DEBUG
//      if (!flag) {
//        // ファイルが存在しない場合
//        throw LogicError(filePath.string() + ":ファイルが存在しません");
//      }
//#endif
//      return flag;
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::HasExtension(std::filesystem::path filePath, std::string_view extension) const {
//      if (extension.empty()) {
//        return true; // 拡張子の指定なし
//      }
//#ifndef _DEBUG
//      return _filePath.stem() == extension;
//#else
//      if (filePath.stem() != extension) {
//        throw LogicError(filePath.string() + ":拡張子が一致していません");
//        return false; // 非一致
//      }
//      return true; // 一致
//#endif
//    }
//
//    template <typename T, typename I>
//    bool ServerBase<T, I>::UseKey(std::string_view key) const {
//#ifndef _DEBUG
//      // キーは使用可能か
//      return !_registry.contains(key.data());
//#else
//      if (_registry.contains(key.data())) {
//        std::string message = key.data();
//        throw LogicError(message + ":は既に登録されています");
//        return false; // 登録済み
//      }
//      return true; // 未使用
//#endif
//    }
//
//#ifdef _DEBUG
//    template <typename T, typename I>
//    std::logic_error ServerBase<T, I>::LogicError(std::string_view message) const {
//      // 指定した形式に修正
//      std::string m = _name + ":" + message.data() + "\n";
//      return std::logic_error(m);
//    }
//
//    template <typename T, typename I>
//    void ServerBase<T, I>::DebugString(std::string_view message) const {
//      OutputDebugString(message.data());
//      if (_debug) {
//        // ログへの書き出しを行う
//      }
//    }
//#endif
//  } // namespace Data
//} // namespace AppFrame