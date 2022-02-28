/*****************************************************************//**
 * @file   FileServer.h
 * @brief  ファイルデータを管理するサーバクラス
 *
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <filesystem>
#include "FileOutput.h"
#include "FileBase.h"

/** FileWorker用名前空間 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationBase; //!< アプリケーション
  } // namespace Application
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    class LoadJson; //!< 前方宣言
    /**
     * @class FileServer
     * @brief ファイル管理用サーバ
     */
    class FileServer : public Server::ServerTemplateUnordered<std::string, std::filesystem::path> {
    public:
      /**
       * @brief コンストラクタ
       */
      FileServer(Application::ApplicationBase& app);
      /**
       * @brief  初期化
       * @return true:初期化成功 false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  jsonファイルの読み取り
       * @param  jsonFile jsonファイルのパス
       * @return true:読み取り実行 false:問題発生
       */
      bool LoadJsonFile(std::string_view jsonFile) const;
      /**
       * @brief  対象ファイル形式の指定(Instance後、一度のみ設定可能)
       * @param  extensions ファイル拡張子(文字列)を格納した動的配列
       */
      bool SetExtension(std::vector<std::string> extensions);
    protected:
      std::unique_ptr<LoadJson> _loadJson;  //!< jsonファイルの読み取り
      std::vector<std::string> _extensions; //!< 対応ファイル形式
      bool _setExtension{false}; //!< 対象ファイル形式を指定したかの判定
      /**
       * @brief  対象ファイルが登録対象かの判定
       * @param  filePath 対象ファイルのパス
       * @param  extension 登録可能なファイル形式
       * @return true:登録対象 false:非登録対象
       */
      bool IsTarget(std::filesystem::path filePath, std::string_view extension = "") const;
      /**
       * @brief  ファイル形式が一致しているかの判定
       * @param  filePath 対象ファイルのパス
       * @return true:一致 false:対象ではない
       */
      bool HasExtension(std::filesystem::path filePath, std::string_view extension = "") const;
      /**
       * @brief  対象パスが存在するかの判定
       * @param  filePath 対象ファイルのパス
       * @return true:有効 false:パスが不正
       */
      bool Exist(std::filesystem::path filePath) const;
    };

//    class FileServer : public Data::ServerBase < FileBase, std::filesystem::path > {
//    public:
//#ifndef _DEBUG
//      /**
//       * @brief コンストラクタ
//       */
//      FileServer();
//#else
//      /**
//       * @brief コンストラクタ
//       * @param filePath ログ出力用ファイルのパス(デフォルトでは空)
//       */
//      FileServer(std::filesystem::path filePath = "");
//#endif
//      /**
//       * @brief デストラクタ
//       */
//      ~FileServer() override;
//      /**
//       * @brief  初期化
//       */
//      bool Init() override;
//      /**
//       * @brief  レジストリの初期化
//       * @return 
//       */
//      bool Release() override;
//      /**
//       * @brief  ファイル情報の登録
//       * @param  key  登録に使用する文字列
//       * @param  path ファイルのパス
//       * @return true:登録成功 false:登録失敗
//       */
//      bool Register(std::string_view key, const std::filesystem::path path) override;
//      /**
//       * @brief  ファイル情報の読み取り
//       * @param  jsonPath jsonファイルのポス
//       * @return true:読み取り成功 false:問題発生
//       */
//      bool LoadFiles(std::filesystem::path jsonPath);
//    protected:
//#ifdef _DEBUG
//      class FileOutput _fileLog; //!< ファイル出力システム
//      bool _debug{false};        //!< ログ出力フラグ
//#endif
//    };

    /**
     * @class FileServer
     * @brief ファイルデータを管理するサーバ
     */
//    class FileServer {
//    private:
//      /** 文字列をキーとしてファイルデータを管理する連想配列 */
//      using FileBaseMap = std::unordered_map<std::string, FileBase>;
//    public:
//      /**
//       * @brief  ファイルサーバの生成
//       */
//      FileServer();
//      /**
//       * @brief  ファイルサーバの破棄
//       */
//      ~FileServer();
//      /**
//       * @brief  サーバの初期化処理
//       * @return 初期化フラグ
//       */
//      bool Init();
//      /**
//       * @brief  データの解放処理
//       */
//      void Release();
//      /**
//       * @brief  ファイル情報の読み取り処理
//       * @param  jsonPath 読み取るJsonファイルのパス
//       * @return 読み取り処理に成功した場合はtrueを返す
//       */
//      bool LoadFileMap(std::filesystem::path jsonPath);
//      /**
//       * @brief  ログ出力フラグの設定
//       * @param  flag 出力フラグ
//       * @param  logPath ログファイルを出力するディレクトリパス
//       * @return 設定に成功した場合はtrue
//       *         失敗した場合はfalseを返す
//       */
//      bool SetLogTextFlag(bool flag, std::filesystem::path logPath);
//    private:
//      FileBaseMap _fileMap; //!< ファイル情報を管理するコンテナ
//      FileOutput _debugLog; //!< デバッグ用ファイル出力システム
//      bool _debug;          //!< デバッグ出力用フラグ
//      /**
//       * @brief  ファイル情報の登録処理
//       * @param  fileMap 登録を行うファイル情報
//       * @return 登録処理が正常終了した場合はtrue
//       *         失敗した場合はfalseを返す
//       */
//      bool LoadFileMap(FileBaseMap& fileMap);
//      /**
//       * @brief      識別子の判定を行う
//       * @param path 判定ファイル
//       * @return
//       */
//      bool FileCheck(const std::filesystem::path path);
//#ifdef _DEBUG
//      /**
//       * @brief  ログ出力
//       * @param  text 出力する文字列
//       */
//      void DebugStringLog(const std::string text);
//#endif
//    };
  } // namespace FileServer
} // namespace AppFrame