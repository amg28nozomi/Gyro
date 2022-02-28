/*****************************************************************//**
 * @file   FileBase.h
 * @brief  ファイルデータを保持するスーパークラス
 *
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>

/** FileWorker用名前空間 */
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    /**
     * @class FileBase
     * @brief ファイルデータ
     */
    class FileBase {
    public:
      /**
       * @brief 空データを生成
       */
      FileBase();
      /**
       * @brief ファイルデータの生成(キー情報無し)
       * @param filePath ファイルのパス
       */
      FileBase(std::filesystem::path filePath);
      /**
       * @brief ファイルデータの生成(キー情報有り)
       * @param filrPath 
       * @param key
       */
      FileBase(std::filesystem::path filrPath, std::string_view key);
      /**
       * @brief ファイルデータの破棄
       */
      ~FileBase();
      /**
       * @brief ファイルデータのリセット
       */
      void Clear();
      /**
       * @brief  パスの取得
       * @return ファイルパスを返す
       */
      inline std::filesystem::path GetFilePath() const {
        return _path;
      }
      /**
       * @brief  ファイル名の取得
       * @return 拡張子を除いたファイル名を返す
       */
      inline std::string GetFileName() const {
        return _path.stem().string();
      }
      /**
       * @brief  キー情報の取得
       * @return 連想配列に登録するキー
       */
      inline std::string GetKey() const {
        return _key;
      }
      /**
       * @brief  キーとパスの取得
       * @return 左辺:キー 右辺:パス
       */
      inline std::pair<std::string_view, std::filesystem::path> GetFileData() {
        return { _key, _path };
      }
    protected:
      std::filesystem::path _path; //!< ファイルパス
      std::string _key;            //!< 連想配列で使用するキー
    };
  } // namespace FileServer
} // namespace AppFrame