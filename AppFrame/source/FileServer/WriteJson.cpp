/*****************************************************************//**
 * @file   WriteJson.cpp
 * @brief  jsonファイルの書き込み処理クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "WriteJson.h"
#include "FileBase.h"
#include <fstream>
#ifdef _DEBUG
#include <stdexcept>
#endif

namespace AppFrame {
  namespace FileServer {

    std::filesystem::path WriteJson::AddJson(std::filesystem::path jsonName) {
      // ファイルは既に生成されているか？
      if (std::filesystem::exists(jsonName)) {
        return jsonName; // 生成済み
      }
      if (jsonName.extension() == ".json") {
        // 拡張子がjsonでない場合も弾く
        throw std::logic_error("WriteJson::AddJson:対象ファイルの拡張子がjson形式ではありません\n");
        return "";
      }
      // 存在していない場合はjsonファイルを作成
      std::ofstream jsonFile;
      jsonFile.open(jsonName.filename().string(), std::ios::out);
      jsonFile.close();
      return jsonName;
    }

    bool WriteJson::Save(std::string_view path) {
      std::ofstream jsonFile;
      // ファイルを開く
      jsonFile.open(path.data(), std::ios::out);
      jsonFile.close(); // ファイルを閉じる
      return false;
    }
  } // namespace FileServer
} // namespace AppFrame