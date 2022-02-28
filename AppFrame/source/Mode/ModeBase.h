/*****************************************************************//**
 * @file   ModeBase.h
 * @brief  モードの基底クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationBase;
    class InputOperation;
  } // namespace Application
  /**
   * @brief ファイルサーバ
   */
  namespace FileServer {
    class FileServer;
  } // namespace FileServer
  /**
   * @brief モードベース
   */
  namespace Mode {
    /**
     * @class ModeBase
     * @brief モードの基底クラス
     */
    class ModeBase {
    public:
      /**
       * @brief モードの生成
       * @param app アプリケーションの参照
       */
      ModeBase(Application::ApplicationBase &app);
      /**
       * @brief モードの削除
       */
      virtual ~ModeBase();
      /**
       * @brief  モードの初期化
       * @return true:初期化成功 false:初期化失敗
       */
      virtual bool Init();
      /**
       * @brief  入口処理
       * @return true:処理成功 false:処理失敗
       */
      virtual bool Enter();
      /**
       * @brief  出口処理
       * @return true:処理成功 false:失敗
       */
      virtual bool Exit();
      /**
       * @brief  モード専用の入力処理
       * @param  input インプットオペレーションの参照
       * @return true:処理成功 false:処理失敗
       */
      virtual bool Input(Application::InputOperation& input);
      /**
       * @brief  モードの更新
       * @return true:更新成功 false:更新失敗
       */
      virtual bool Process();
      /**
       * @brief  モードの描画
       * @return true:描画成功 false:描画失敗
       */
      virtual bool Draw() const;
      /**
       * @brief  経過フレームの初期化
       */
      virtual void TimeClear();
      /**
       * @brief  アプリケーションの取得
       * @return アプリケーションの参照
       */
      virtual Application::ApplicationBase& GetApplication();
      /**
       * @brief  モードサーバの取得
       * @return モードサーバの参照
       */
      class ModeServer& GetModeServer();
      /**
       * @brief  ファイルサーバの取得
       * @return ファイルサーバの参照
       */
      FileServer::FileServer& GetFileServer();
      /**
       * @brief  本モードの経過フレーム数を取得
       * @return フレームカウンタ
       */
      int GetFrameCount() const {
        return _count;
      }
      /**
       * @brief  ミリ秒の取得
       * @return 経過時間(ミリ秒)
       */
      long double GetMilliSecond() const {
        return _milli;
      }
    protected:
      //!< アプリケーションの参照
      Application::ApplicationBase& _app;
      //!< 本モード内での経過時間(フレーム)
      int _count{0};
      //!< 本モード内での経過時間(ミリ秒)
      long double _milli{0.0};
      //!< リソースの読み込みフラグ
      bool _isLoad{false};
      /**
       * @brief 時間経過処理
       */
      virtual void StepTime();
    };
  } // namespace Mode
} // namespace AppFrame