/*****************************************************************//**
 * @file   FileServer.cpp
 * @brief  ファイルデータを管理するサーバクラスの定義
 *
 * @author 鈴木希海
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
  constexpr auto LogText = "FileWorkerLog.txt"; // ログ用ファイル名
} // namespace

namespace AppFrame {
  namespace FileServer {

    FileServer::FileServer(Application::ApplicationBase& app) : Server::ServerTemplateUnordered<std::string, std::filesystem::path>() {
      // LoadJsonの生成
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
      // 対象はjsonファイルか
      if (!_loadJson->IsJson(jsonFile)) {
        return false; // jsonファイルではない
      }
      // jsonファイルの場合は読み取りを行う
      _loadJson->LoadJsonFile(jsonFile.data());
      return true;
    }

    bool FileServer::SetExtension(std::vector<std::string> extensions) {
      // ファイル形式の指定は行われているか
      if (_setExtension) {
        return false; // 登録済み
      }
      for (auto extension : extensions) {
        // 空データの場合はスキップ
        if (extension.empty()) {
          continue;
        }
        // 同一拡張子が登録されていないかの判定
        for (auto number = 0; auto data : _extensions) {
          // 重複している場合は処理をループ終了
          if (extension == data) {
            break; // 重複している
          }
          ++number; // 処理カウントを加算
          // 全要素の判定が完了した場合は末尾に登録
          if (number == static_cast<int>(_extensions.size())) {
            _extensions.emplace_back(extension); // 登録
          }
        }
      }
      // 要素の有無で登録が成功したか判定
      _setExtension = !_extensions.empty();
      // 処理に成功した場合は使用領域を切り詰める
      if (_setExtension) {
        _extensions.shrink_to_fit();
      }
#ifndef _DEBUG
      return _setExtension;
#else
      // 登録に失敗した場合は例外をthrowする
      else {
        throw LogicError("拡張子の登録に失敗しました");
        return false; // 登録失敗
      }
      return true;    // 登録成功
#endif
    }

    bool FileServer::IsTarget(std::filesystem::path filePath, std::string_view extension) const {
      namespace fs = std::filesystem;
#ifndef _DEBUG
      // パスが有効かの判定
      if (!Exist(filePath)) {
        return false; // パスが不正
      }
      // 対象のファイル形式は有効か
      return HasExtension(filePath, extension);
#else
      auto flag = false;
      try {
        flag = Exist(filePath);
        if (flag) {
          flag = HasExtension(filePath, extension);
        }
      } catch (std::logic_error error) {
        DebugString(error.what()); // 例外発生時は出力
      }
      return flag; // 処理フラグを返す
#endif
    }

    bool FileServer::HasExtension(std::filesystem::path filePath, std::string_view extension) const {
#ifndef _DEBUG
      return filePath.extension().string() == extension;
#else
      // ファイル形式は一致しているか？
      if (filePath.extension().string() != extension) {
        throw LogicError(filePath.filename().string() + "ファイル形式が有効ではありません");
        return false; // ファイル形式が異なる
      }
      return true;    // ファイル形式は有効
#endif
    }

    bool FileServer::Exist(std::filesystem::path filePath) const {
      namespace fs = std::filesystem;
      // パスが有効かの判定
      if (!fs::exists(filePath)) {
#ifdef _DEBUG
        throw LogicError(filePath.string() + ":ファイルパスが有効ではありません");
#endif
        return false; // パスが不正
      }
      return true;    // 有効
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
//      // 登録されているファイル情報を一括削除する
//      _registry.clear();
//      return true;
//    }
//
//    bool FileServer::Register(std::string_view key, const std::filesystem::path path) {
//#ifndef _DEBUG
//      // 対象は登録可能か？
//      if (!IsTarget({key, path})) {
//        return false;
//      }
//#else
//      try {
//        IsTarget((key, path));
//      } catch (std::logic_error error) {
//        DebugString(error.what());
//        return false; // 登録失敗
//      }
//#endif
//      _registry.emplace(key, path); // レジストリに登録
//      return true;
//    }
//
//    bool FileServer::LoadFiles(std::filesystem::path jsonPath) {
//#ifndef _DEBUG
//      // パスは有効か
//      if (!IsTarget(jsonPath, ".json")) {
//        return false; // 読み取り対象ではない
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
//      _fileMap.clear(); // 解放
//    }
//
//    bool FileServer::LoadFileMap(std::filesystem::path jsonPath) {
//#ifdef _DEBUG
//      auto stringPath = jsonPath.string();
//#endif
//      // 対象ファイルは存在しているか
//      if (!std::filesystem::exists(jsonPath)) {
//#ifdef _DEBUG
//        const std::string message(stringPath + ":パスが不正です");
//        DebugStringLog(message);
//#endif
//        return false; // パスが不正
//      }
//      // 対象がjsonファイルかの判定
//      if (!LoadJson::IsJson(jsonPath)) {
//#ifdef _DEBUG
//        const std::string message(stringPath + ":対象はjsonファイルではありません");
//        DebugStringLog(message);
//#endif
//        return false; // ファイル形式が異なる
//      }
//      auto fileMap = LoadJson::LoadJsonFile(jsonPath); // ファイル情報
//      if (fileMap.empty()) {
//        return false; // ファイル情報が空
//      }
//      auto counter = 0; // 登録失敗回数
//      // 取得したファイル情報の登録
//      for (auto [key, value] : fileMap) {
//        if (_fileMap.contains(key)) {
//#ifdef _DEBUG
//          const std::string message = "キー:" + key + "は既に登録されています";
//          DebugStringLog(message);
//#endif
//          ++counter;
//          continue;
//        }
//        _fileMap.emplace(key, value);
//      }
//#ifdef _DEBUG
//      // 途中、登録処理に失敗したか？
//      if (counter) {
//        const std::string message(counter + "回処理に失敗しました");
//        DebugStringLog(message);
//      }
//#endif
//      return true; // 登録終了
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
//      // ログへの出力
//      std::string message("FileServer:" + text + "\n");
//      OutputDebugString(message.data());
//      if (!_debug) {
//        return;
//      }
//      // テキストファイルへの出力
//      _debugLog.OutputText(text);
//    }
//#endif
  } // namespace FileServer
} // namespace AppFrame