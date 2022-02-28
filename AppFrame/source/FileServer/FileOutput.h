/*****************************************************************//**
 * @file   FileOutput.h
 * @brief  ファイルの入出力クラス
 *
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>
#include <string_view>

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    /**
     * @class FileOutput
     * @brief ファイルの入出力処理クラス
     */
    class FileOutput {
    public:
      /**
       * @brief  コンストラクタ
       * @param  path ファイルのパス
       */
      FileOutput(std::filesystem::path path);
      /**
       * @brief  デストラクタ
       */
      ~FileOutput();
      /**
       * @brief  テキストファイルへの出力
       * @param  text 出力する文字列
       * @return 処理に成功した場合はtrue
       *         失敗した場合はfalseを返す
       */
      bool OutputText(std::string_view text);
      /**
       * @brief  入出力ファイルの設定
       * @param  file 設定するファイルのパス
       * @return 設定に成功したかの判定
       */
      bool SetFilePath(std::filesystem::path file);
    private:
      std::filesystem::path _file; //!< 入出力ファイル
      /**
       * @brief  パスが有効かの判定
       * @param  path 判定ファイル
       * @return パスが有効な場合はtrue
       *         有効ではない場合はfalseを返す
       */
      bool IsPath(std::filesystem::path path);
    };
  } // namespace FileServer
} // namespace AppFrame