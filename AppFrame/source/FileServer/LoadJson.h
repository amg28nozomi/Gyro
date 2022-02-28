/*****************************************************************//**
 * @file   LoadJson.h
 * @brief  jsonファイルの読み取り処理クラス
 *
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <vector>
#include <filesystem>
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <nlohmann/json.hpp>
#include "../Data/DivGraph.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationBase;
  }
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    constexpr auto JSON = ".json"; //!< jsonファイルのフォーマット
    /**
     * @class LoadJson
     * @brief jsonファイルの読み取りを行う静的クラス
     */
    class LoadJson {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      LoadJson(Application::ApplicationBase& app);
      /**
       * @brief  jsonファイルの読み取り処理
       * @param  path jsonファイルのパス
       * @return true:読み取り成功 false:読み取り失敗
       */
      bool LoadJsonFile(std::string_view path);
      /**
       * @brief  jsonファイルの読み取り処理(DivGraph用)
       * @param  jsonPath
       * @return DivGraph用のデータが格納された動的配列
       *         first:連想配列の登録に使用するキー pair:画像ファイル情報
       */
      //static std::vector<std::pair<std::string_view,
      //  std::filesystem::path>> LoadDivGraoh(std::filesystem::path jsonPath);
      /**
       * @brief  jsonファイルの読み取り処理
       * @param  jsonPath jsonファイルのパス
       * @return 取得したファイルデータを返す
       * @throw  std::logic_error
       */
      //static std::vector<std::pair<std::string, Data::DivGraph>> LoadJsonFile(std::filesystem::path jsonPath);
      /**
       * @brief  対象ファイルがjsonファイルかを判定する
       * @param  path 判定ファイルのパス
       * @return jsonファイルの場合はtrue
       *         そうではない場合はfalseを返す
       */
      static bool IsJson(const std::filesystem::path path);
    private:
      Application::ApplicationBase& _app; //!< アプリケーションの参照
      /**
       * @brief  モデル情報の読み取り処理
       * @param  json モデル情報が格納されたjsonオブジェクト
       * @return true:読み取り成功 false:問題発生
       */
      bool LoadModelData(const nlohmann::json json);
      /**
       * @brief  LoadDivGraph情報の読み取り
       * @param  json 画像情報が格納されたjsonオブジェクト
       * @return 
       */
      bool LoadDivGraphData(const nlohmann::json json);
      /**
       * @brief  Jsonファイルパスへの変換
       * @param  directory ディレクトリパス
       * @param  fileName  jsonファイル名
       * @return jsonファイルのパス
       */
      std::filesystem::path ToJsonName(std::string directory, std::string fileName) const;
      /**
       * @brief  jsonファイルの読み取り
       * @param  jsonFile 対象ファイルのパス
       * @return 読み取りに成功した場合は対象のjsonオブジェクトを返す
       *         読み取りに失敗した場合は空のオブジェクトを返す
       */
      //static nlohmann::json LoadJsonFile(std::filesystem::path jsonFile);
#ifdef _DEBUG
      /**
       * @brief  エラーメッセージの取得
       * @param  left  左辺値
       * @param  right 右辺値
       * @return 差分に応じたエラーメッセージを返す
       * @throw  std::logic_error
       */
      std::string_view Differebce(const int key, const int path) noexcept;
      /**
       * @brief  std::logic_errorの取得
       * @param  message エラーに持たせる文字列
       * @return 設定したlogic_errorを返す
       */
      static std::logic_error GetLogicError(std::string message);
#endif
    };
  } // namespace FileServer
} // namespace AppFrame