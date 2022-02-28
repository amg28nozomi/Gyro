/*****************************************************************//**
 * @file   ModeServer.h
 * @brief  各種モードを管理するサーバクラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <memory>
#include <list>

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationBase; //!< 前方宣言
  } // namespace Application
  /**
   * @brief モードベース
   */
  namespace Mode {
    class ModeBase; //!< 前方宣言
    /**
     * @class ModeServer
     * @brief モードの管理を行うサーバ
     */
    class ModeServer : public Server::ServerTemplateUnordered<std::string, std::shared_ptr<ModeBase>> {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeServer(Application::ApplicationBase& app);
      /**
       * @brief  コンストラクタ
       * @param  key  登録に使用する文字列
       * @param  mode 最初に登録するシーンのポインタ
       */
      ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode);
      /**
       * @brief  モードの解放
       * @return true:開放成功 false:解放失敗
       */
      bool Release() override;
      /**
       * @brief  データベースにモードを登録する
       * @param  key 登録に使用する文字列
       * @param  mode 登録するモードのシェアードポインタ
       */
      void AddMode(std::string_view key, std::shared_ptr<ModeBase> mode);
      /**
       * @brief  指定したモードをリストの末尾に追加する
       * @param  key 対象モードに紐づけられた文字列
       * @return true:追加成功 false:追加失敗
       */
      bool PushBack(std::string_view key);
      /**
       * @brief  リストの末尾に登録されているモードを削除する
       */
      void PopBuck();
      /**
       * @brief  モードの遷移処理
       * @param  key 対象モードに紐づけられた文字列
       * @return true
       */
      bool TransionToMode(std::string_view key);
      /**
       * @brief  モードの更新
       * @return true:正常終了 false:問題発生
       */
      bool Process();
      /**
       * @brief  モードの描画
       * @return true:描画成功 false:問題発生
       */
      bool Draw() const;
    private:
      //!< モードリスト
      std::list<std::shared_ptr<ModeBase>> _modes;
      /**
       * @brief  モードの登録
       * @param  key  モードに紐づける文字列
       * @param  mode 登録するモード
       * @return true
       */
      bool Register(std::string key, std::shared_ptr<ModeBase> mode) override;
      /**
       * @brief  データベースから指定したモードを取得する
       * @param  key 対象モードに紐づけられた文字列
       * @return 指定したモードを返す
       *         キーが有効ではない場合、nullptrを返す
       */
      std::shared_ptr<ModeBase> FetchMode(std::string_view key);
      /**
       * @brief  リストの末尾の要素の直前に指定したモードを追加する
       * @param  key 対象モードに紐づけられた文字列
       * @return true:追加成功 false:追加失敗
       */
      bool InsertBeforeBack(std::string_view key);
    };
  } // namespace Mode
} // namespace AppFrame