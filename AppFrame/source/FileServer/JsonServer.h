/*****************************************************************//**
 * @file   JsonServer.h
 * @brief  jsonファイルの読み取り・書き出しを行うサーバクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <nlohmann/json.hpp>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    /**
     * @class JsonServer
     * @brief ファイルパスをキーとしてjsonデータを管理するサーバクラス
     */
    //class JsonServer : public Server::ServerTemplateUnordered<std::filesystem::path, nlohmann::json> {
    //public:
    //  /**
    //   * @brief コンストラクタ
    //   */
    //  JsonServer();
    //  /**
    //   * @brief デストラクタ
    //   */
    //  ~JsonServer();
    //  /**
    //   * @brief  コンテナの解放処理
    //   * @return 
    //   */
    //  bool Release() override;


    //private:
    //  static inline std::filesystem::path _directory{}; //!< 共通のディレクトリパス
    //  /**
    //   * @brief  
    //   * @param  filePath jsonファイルのパス
    //   * @return 
    //   */
    //  bool LoadJsonFile(std::filesystem::path);

    //  /**
    //   * @brief  jsonファイルが格納されているディレクトリパスの設定
    //   * @param  path ディレクトリパス
    //   * @return true:設定完了 false:設定失敗
    //   */
    //  static bool SetJsonDirectory(std::string_view path);
    //};

    //class JsonServer : public Data::ServerBase < std::filesystem::path, std::filesystem::path> {
    //public:
    //  /**
    //   * @brief コンストラクタ
    //   */
    //  JsonServer();
    //  /**
    //   * @brief デストラクタ
    //   */
    //  ~JsonServer() override;
    //  /**
    //   * @brief  サーバの初期化
    //   * @return true:初期化成功 false:初期化失敗
    //   */
    //  bool Init() override;
    //  /**
    //   * @brief  
    //   * @param  key
    //   * @param  path
    //   * @return 
    //   */
    //  bool Register(std::string_view key, std::filesystem::path path) override;

    //  /**
    //   * @brief  jsonファイルの読み取り処理
    //   * @param  jsonFile 読み取りを行うjsonファイルのパス
    //   * @return true:読み取り成功 false:読み取り失敗
    //   */
    //  bool LoadJsonFile(std::filesystem::path jsonFile);
    //  /**
    //   * @brief  最後に開いたjsonファイルのパスを取得
    //   * @return 最後に開いたjsonファイルのパス
    //   *         ファイルを開いていない場合は空のpathを返す
    //   */
    //  inline std::filesystem::path OpendFile() const {
    //    return _opendFile;
    //  }
    //protected:
    //  //!< jsonファイルのパスを管理するデータベース
    //  std::string _extension{".json"}; //!< 対応しているファイル形式
    //  std::filesystem::path _opendFile{}; //!< 最後に開いたファイルのパス
    //  /**
    //   * @brief  データベースへの登録
    //   * @param  key 登録時に紐づける文字列
    //   * @param  jsonFile jsonファイルのパス
    //   * @return true:登録成功 false:登録失敗
    //   * @throw  Debug:logic_error
    //   */
    //  bool Register(std::string_view key, std::filesystem::path jsonFile);
    //  /**
    //   * @brief  対象ファイルが登録可能かの判定
    //   * @param  key 登録に使用する文字列
    //   * @param  filePath 登録するjsonファイルのパス
    //   * @param  extension 対応しているファイル拡張子(デフォルトは空)
    //   * @return 
    //   */
    //  bool IsTarget(std::string_view key, std::filesystem::path filePath, std::string_view extension = "") const;
    //};
  } // namespace FileServer
} // namespace AppFrame