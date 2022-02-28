/*****************************************************************//**
 * @file   ResourceServer.h
 * @brief  2D素材を管理するリソースサーバクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <filesystem>
#include "../Data/DivGraph.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief リソースベース
   */
  namespace Resource {
    /**
     * @class  ResourceServer
     * @brief  文字列をキーとして画像情報とグラフィックハンドルを管理するサーバ
     *         Key 画像情報に紐づける文字列
     *         Value first:画像情報 second:グラフィックハンドルを格納するコンテナ
     */
    class ResourceServer : Server::ServerTemplateUnordered<std::string, std::pair<Data::DivGraph, std::vector<int>>> {
    public:
      /**
       * @brief 
       * @param first:紐づける文字列
       * @param second:画像情報
       */
      using DivGraphTable = std::pair<std::string, Data::DivGraph>;
      /**
       * @brief コンストラクタ
       * @param path ディレクトリパス
       */
      ResourceServer(std::string_view path = "");
      /**
       * @brief  グラフィック情報の解放
       * @return 
       */
      bool Release() override;
      /**
       * @brief  画像の読み取り
       * @param  グラフィックハンドルに紐づける文字列
       * @param  divGraph 画像情報
       * @return true:登録成功 false:登録失敗
       */
      bool LoadDivGraph(std::string_view key, Data::DivGraph divGraph);
      /**
       * @brief  指定した画像情報の取得
       * @param  key 対象情報に紐づけられた文字列
       * @return first:画像情報 second:グラフィックハンドルが格納されたコンテナ
       */
      Data::DivGraph GetDivGraph(std::string_view key) const;
      /**
       * @brief  指定したグラフィックハンドルの取得
       * @param  key 対象に紐づけられた文字列
       * @param  no  対象のハンドル番号
       * @return 取得に成功した場合はグラフィックハンドルを返す
       *         失敗した場合は-1を返す
       */
      const int GetHandle(std::string_view key ,const int no = 0) const;
      /**
       * @brief  ディレクトリパスの設定(未登録の場合のみ登録可能)
       * @param  path ディレクトリパス
       * @return true:設定成功 false:失敗
       */
      bool SetDirectryPath(std::filesystem::path path);
    private:
      std::filesystem::path _directory{}; //!< ディレクトリパス
      /**
       * @brief  ファイルパスの結合
       * @param  filePath 対象のファイル名
       * @return ファイルパス
       */
      inline std::filesystem::path FilePath(std::filesystem::path filePath) const {
        return (_directory / filePath);
      }
      /**
       * @brief  グラフィックハンドルの削除
       * @param  handles グラフィックハンドルが格納されたコンテナ
       */
      void DeleteGraphs(std::vector<int> handles) const;
    };
  } // namespace Resource
} // namespace AppFrame