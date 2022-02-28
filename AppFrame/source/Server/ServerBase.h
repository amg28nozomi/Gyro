/*****************************************************************//**
 * @file   ServerBase.h
 * @brief  サーバの基底クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#ifdef _DEBUG
#include <stdexcept>
#include <Windows.h>
#endif
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief サーバベース
   */
  namespace Server {
    /**
     * @class ServerBase
     * @brief サーバのテンプレート
     */
    template <typename T>
    class ServerBase {
    public:
      /**
       * @brief サーバの状態を表す列挙型クラス
       */
      enum class ServerState {
        Active, // 活動
        Paused, // 停止
        Error   // 異常
      };
      /**
       * @brief コンストラクタ
       */
      ServerBase();
      /**
       * @brief デストラクタ
       */
      virtual ~ServerBase() = default;
      /**
       * @brief  初期化
       * @return true:初期化成功 false:初期化失敗
       */
      virtual bool Init();
      /**
       * @brief  保持しているリソースの解放処理
       *         派生先で必ず再定義を行う
       * @return true:解放成功 false:問題発生
       */
      virtual bool Release() = 0;
    protected:
      ServerState _state; //!< 状態
      T _registry{};      //!< データベース
#ifdef _DEBUG
      std::string _name;  //!< サーバ名
      /**
       * @brief デバッグ処理で使用するサーバ名の設定
       * @param name サーバ名
       */
      void SetServerName(std::string_view name);
      /**
       * @brief  logic_errorの生成
       * @param  message 出力する文字列
       * @return logic_error
       */
      virtual std::logic_error LogicError(std::string_view message) const;
      /**
       * @brief デバッグ用メッセージの出力
       * @param message デバッグ用の文字列
       */
      virtual void DebugString(std::string_view message) const;
#endif
    };
    /**
     * @brief コンストラクタの定義
     */
    template <typename T>
    ServerBase<T>::ServerBase() {
      _state = ServerState::Active;
    }
    /**
     * @brief 初期化の定義
     */
    template <typename T>
    bool ServerBase<T>::Init() {
#ifndef _DEBUG
      // リソースの解放処理に成功したか
      if (!Release()) {
        _state = ServerState::Error;
        return false; // 失敗
      }
      return true;    //正常終了
#else
      bool flag;
      try {
        flag = Release(); // リソースの解放
      }
      catch (std::logic_error error) {
        // 例外をcatchした場合は、出力を行う
        DebugString(error.what());
      }
      // 解放に失敗した場合はエラー状態に遷移する
      if (!flag) {
        _state = ServerState::Error;
      }
      return flag;
#endif
    }

#ifdef _DEBUG
    template <typename T>
    void ServerBase<T>::SetServerName(std::string_view name) {
      _name = name.data(); // 引数の文字列をサーバ名として使用する
    }

    template <typename T>
    std::logic_error ServerBase<T>::LogicError(std::string_view message) const {
      std::string error = _name + ":" + message.data() + "\n";
      return std::logic_error(error);
    }

    template <typename T>
    void ServerBase<T>::DebugString(std::string_view message) const {
      // デバッグウィンドウに出力する
      OutputDebugString(message.data());
    }
#endif
  } // namespace Server
//  namespace FileServer {
//    class FileBase;
//  }
//  /**
//   * @brief データベース
//   */
//  namespace Data {
//    /**
//     * @class ServerBase
//     * @brief サーバの基底となるテンプレートクラス
//     * @tparam T 連想配列の値に該当する型
//     * @tparam I 登録処理で使用する型
//     */
//    template <typename T, typename I>
//    class ServerBase {
//    public:
//#ifndef _DEBUG
//      /**
//       * @brief  コンストラクタ(Release)
//       */
//      ServerBase();
//#else
//      /**
//       * @brief  コンストラクタ(Debug)
//       * @param  flag ログ出力フラグ(デフォルトではfalse)
//       */
//      ServerBase(const bool flag = false);
//#endif
//      /**
//       * @brief  デストラクタ
//       */
//      virtual ~ServerBase() = default;
//      /**
//       * @brief  初期化
//       */
//      virtual bool Init();
//      /**
//       * @brief  解放処理
//       * @return true:処理成功 false:問題発生
//       */
//      virtual bool Release() = 0;
//      /**
//       * @brief  登録処理用純粋仮想関数
//       *         登録処理は派生クラス側で実装すること
//       * @param  key 登録に使用する文字列
//       * @param  value 登録する値
//       * @return true:登録成功 false:登録失敗
//       */
//      virtual bool Register(std::string_view key, const I value) = 0;
//      /**
//       * @brief  ファイル情報の読み込み
//       * @param  files ファイル情報
//       * @return true:処理成功 false:問題発生
//       */
//      virtual bool LoadFiles(std::vector<FileServer::FileBase> files);
//    protected:
//      std::unordered_map<std::string, T> _registry; //!< レジストリー
//      /**
//       * @brief  対象ファイルが存在するかの判定
//       * @param  filePath 対象ファイルのパス
//       * @return true:ファイルは存在する false:ファイルは存在しない
//       * @throw  Debug:パスが有効ではない場合、logic_errorを返す
//       */
//      bool Exist(std::filesystem::path filePath) const;
//      /**
//       * @brief  ファイル拡張子が一致しているかの判定(Debug)
//       * @param  filePath ファイルのパス
//       * @param  extension 対応するファイル拡張子
//       * @return true:一致 false:一致していない
//       * @throw  一致していない場合、logic_errorを返す
//       */
//      bool HasExtension(std::filesystem::path filePath, std::string_view extension) const;
//      /**
//       * @brief  キーが使用可能かの判定
//       * @param  key レジストリへの登録で使用する文字列
//       * @return true:使用可能 false:すでに使用されている
//       */
//      bool UseKey(std::string_view key) const;
//      /**
//       * @brief  対象データが有効かの判定
//       * @param  file ファイルデータ
//       * @param  extension ファイル拡張子(デフォルトは拡張子なし)
//       * @return true:有効 false:有効ではない
//       */
//      bool IsTarget(FileServer::FileBase file, std::string_view extension = "") const;
//#ifdef _DEBUG
//      std::string _name; //!< サーバー名
//      bool _debug;       //!< ログ出力フラグ
//      /**
//       * @brief  logic_errorの生成
//       * @param  message 使用するエラー文
//       * @return 指定した形式に変換したlogic_error
//       */
//      std::logic_error LogicError(std::string_view message) const;
//      /**
//       * @brief ログへの出力処理
//       * @param message 出力する文字列
//       */
//      void DebugString(std::string_view message) const;
//#endif
//    };
//  } // namespace Data
} // namespace AppFrame