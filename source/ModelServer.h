#pragma once
#include <appframe.h>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief モデルベース
   */
  namespace Model {
    /**
     * @brief 名前空間の別名定義
     */
    namespace AppServer = AppFrame::Server;
    /**
     * @class ModelServer
     * @brief モデルデータとアニメーションを管理するサーバクラス
     */
    class ModelServer : public AppServer::ServerTemplateUnordered<std::string, std::vector<int>> {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションメインの参照
       */
      ModelServer(Application::ApplicationMain& app);
      /**
       * @brief  リソースの解放処理
       * @return 
       */
      bool Release() override;
      /**
       * @brief  モデルファイルが格納されているディレクトリパスの設定
       * @param  directry ディレクトリパス
       * @return true:設定完了 false:失敗
       */
      bool SetDirectryPath(std::string_view directry);
      /**
       * @brief  モデルハンドルの読み取り
       * @param  filePath 対象モデルのファイルパス
       * @return true:読み取り成功 false:読み取り失敗
       */
      bool LoadModel(std::string_view fileName);
      /**
       * @brief  指定したモデルハンドルの取得
       * @param  key モデル情報に紐づけられた文字列
       * @param  no モデル番号
       * @return keyが有効な場合はモデルハンドルを返す
       *         有効ではない場合は-1を返す
       */
      const int GetModelHandle(std::string_view key, const int no);
    private:
      Application::ApplicationMain& _app; //!< アプリケーションメインの参照
      //!< モーションデータをファイル名(文字列)で管理する連想配列
      std::unordered_map<std::string, int> _animations{};
      std::filesystem::path _directry{}; //!< ディレクトリパス
      /**
       * @brief  パスが有効かの判定
       * @param  path 判定パス
       * @return true:有効 false:有効ではない
       */
      bool PathExist(std::filesystem::path path);
      /**
       * @brief モデルハンドルの削除を行う
       * @param handles モデルハンドルが格納されたコンテナの参照
       */
      void DeleteHandles(std::vector<int>& handles);
      /**
       * @brief  Mv1モデルの読み取り
       * @param  path ファイル名
       * @return モデルハンドル
       *         読み取りに失敗した場合は-1を返す
       */
      int MV1LoadModel(std::filesystem::path path) const;
    };
  } // namespace Model
} // namespace Gyro