/*****************************************************************//**
 * @file   JsonServer.cpp
 * @brief  jsonファイルの読み取り・書き出しを行うサーバクラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "JsonServer.h"
#include <fstream>
#ifdef _DEBUG
#include <stdexcept>
#include <Windows.h>
#endif


namespace AppFrame {
  namespace FileServer{

    //JsonServer::JsonServer() : ServerTemplateUnordered<std::string, nlohmann::json>() {
    //  // コンテナの解放
    //  _registry.clear();
    //}

    //bool JsonServer::Release() {

    //}

    //bool JsonServer::SetJsonDirectory(std::string_view key) {
    //  // ディレクトリパスの設定
    //  _directory = key.data();
    //}

//    JsonServer::JsonServer() : ServerBase() {
//      _registry.clear();
//    }
//
//    JsonServer::~JsonServer() {
//    }
//
//    bool JsonServer::Init() {
//      ServerBase::Init();
//      _extension.clear();
//      return true; 
//    }
//
//    bool JsonServer::LoadJsonFile(std::filesystem::path jsonFile) {
//      namespace fs = std::filesystem;
//      if (!fs::exists(jsonFile)) {
//        // jsonファイルは存在していない
//      }
//    }
//
//    bool JsonServer::Register(std::string_view key, std::filesystem::path jsonFile) {
//#ifndef _DEBUG
//      // 対象は登録可能か
//      if (!IsTarget(key, jsonFile)) {
//        return false;
//      }
//#else
//      try {
//        IsTarget(key, jsonFile);
//      }
//      catch (std::logic_error error) {
//        OutputDebugString(error.what());
//        return false;
//      }
//#endif
//      _registry.emplace(key, jsonFile);
//    }
//
//    bool JsonServer::IsTarget(std::string_view key, std::filesystem::path filePath, std::string_view extension) const {
//      std::string stem;
//      // 文字列の有無で使用する形式を切り替える
//      if (extension.empty()) {
//        stem = _extension; // デフォルトのファイル形式を使用
//      }
//      else {
//        stem = extension;  // 引数の拡張子を使用する
//      }
//#ifndef _DEBUG
//
//#else
//      // ファイル形式は対応しているか
//      if (filePath.extension() != stem) {
//        throw std::logic_error("ファイル形式が正しくありません\n");
//        return false;
//      }
//      // 形式はあっているか
//      if (_registry.contains(key.data())) {
//        throw std::logic_error("キーが重複しています\n");
//        return false; // キーが使用されています
//      }
//      return true; // 登録可能
//#endif
//    }
  }
}
