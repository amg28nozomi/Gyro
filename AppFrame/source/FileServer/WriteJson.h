/*****************************************************************//**
 * @file   WriteJson.h
 * @brief  jsonファイルの書き込み処理クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    /**
     * @class WriteJson
     * @brief jsonファイルの書き込み処理クラス
     */
    class WriteJson {
    public:
    private:
      static std::filesystem::path _path; //!< 処理を行うディレクトリ
      /**
       * @brief  jsonファイルの生成
       * @param  jsonName jsonファイルの名前
       * @return 生成したjsonファイルのパス
       * @throw  logic_error
       */
      static std::filesystem::path AddJson(std::filesystem::path jsonName);
      /**
       * @brief  jsonファイルのセーブ
       * @param  path
       * @return 
       */
      static bool Save(std::string_view path);
    };
  } // namespace FileServer
} // namespace AppFrame