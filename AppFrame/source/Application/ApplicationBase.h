/*****************************************************************//**
 * @file   ApplicationBase.h
 * @brief  アプリケーションのスーパークラス
 *         全てのアプリケーションはこのクラスを派生する
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <tuple>
#include <memory>
#include "../FileServer/FileServer.h"
#include "../Mode/ModeServer.h"
#include "../SoundServer/SoundServer.h"
#include "../SoundServer/SoundComponent.h"
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  constexpr auto WindowWidth = 1920;  //!< デフォルトの解像度情報
  constexpr auto WindowHeight = 1080; //!< デフォルトの解像度情報
  constexpr auto BitColor32 = 32;     //!< 32ビットカラー
  constexpr auto BitColor16 = 16;     //!< 16ビットカラー
  constexpr auto Frame60 = 60;        //!< 60フレーム
  /**
   * @brief モードベース
   */
  namespace Mode {
    class ModeBase;
  } // namespace Mode
  /**
   * @brief モデルベース
   */
  namespace Model {
    class ModelServer;
  } // namespace Model
  /**
   * @brief リソースベース
   */
  namespace Resource {
    class ResourceServer;
  } // namespace Resource
  /**
   * @brief サウンドベース
   */
  namespace Sound {
    class SoundComponent; //!< 前方宣言
  } // namespace Sound
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    /**
     * @class ApplicationBase
     * @brief アプリケーションの基底クラス
     */
    class ApplicationBase {
    public:
      /**
       * @brief  アプリケーションの状態
       */
      enum class State {
        Play,   //!< 実行中
        Paused, //!< 一時停止
        Quit    //!< 終了
      };
      /**
       * @brief  画面サイズを表す列挙型クラス
       */
      enum class WindowType {
        Default //!< 1920*1080(デフォルト)
      };
      /**
       * @brief コンストラクタ
       * 
       */
      ApplicationBase();
      /**
       * @brief デストラクタ
       */
      virtual ~ApplicationBase();
      /**
       * @brief  アプリケーションの初期化
       * @return 初期化に成功した場合はtrue
       *         失敗した場合はfalseを返す
       */
      virtual bool Init();
      /**
       * @brief アプリケーションの解放
       */
      virtual void Release();
      /**
       * @brief  実行処理
       */
      virtual void Run();
      /**
       * @brief  終了処理
       */
      virtual void Terminate();
      /**
       * @brief  アプリケーションの終了要請
       */
      virtual void RequestTerminate();
      /**
       * @brief  アプリケーションの参照を取得
       * @return アプリケーションの参照
       */
      static std::shared_ptr<ApplicationBase> GetInstance() {
        return _instance;
      }
      /**
       * @brief  インプットオペレーションの取得
       * @return インプットオペレーションの参照
       */
      class InputOperation& GetOperation() {
        return *_input;
      }
      /**
       * @brief  モードサーバの取得
       * @return モードサーバの参照
       */
      Mode::ModeServer& GetModeServer() {
        return *_modeServer;
      }
      /**
       * @brief  ファイルサーバの取得
       * @return ファイルサーバの参照
       */
      FileServer::FileServer& GetFileServer() {
        return *_fileServer;
      }
      /**
       * @brief  サウンドサーバの取得
       * @return サウンドサーバの参照
       */
      Sound::SoundServer& GetSoundServer() {
        return *_soundServer;
      }
      /**
       * @brief  サウンドコンポーネントの取得
       * @return サウンドコンポーネントの参照
       */
      Sound::SoundComponent& GetSoundComponent();
      /**
       * @brief  リソースサーバの取得
       * @return リソースサーバの参照
       */
      Resource::ResourceServer& GetResourceServer();
      /**
       * @brief  モデルサーバの取得
       * @return モデルサーバの参照
       */
      Model::ModelServer& GetModelServer() const;
      /**
       * @brief  画面サイズの取得
       * @return 画面の縦幅と横幅を返す
       */
      inline const std::pair<int, int> GetWindowSize() {
        return std::make_pair(_width, _height);
      }
      /**
       * @brief  ウィンドウ情報の取得
       * @return ウィンドウサイズ・カラービット数を返す
       */
      inline const std::tuple<int, int, int> GetWidnowData() {
        return std::make_tuple(_width, _height, _colorBit);
      }
      /**
       * @brief  経過フレーム取得用の純粋仮想関数
       * @return 現在呼び出されているモードのフレームカウント
       */
      virtual const int GetFrameCount() const = 0;
#ifdef _DEBUG
      /**
       * @brief  デバッグフラグの取得
       * @return デバッグフラグ
       */
      static inline bool GetDebugFlag() {
        return _debug;
      }
      /**
       * @brief  デバッグフラグの切り替え
       */
      inline void ChengeDebugFlag() {
        _debug = !_debug;
      }
#endif
    protected:
      //!< アプリケーションの状態
      State _state{State::Paused};
      //!< ウィンドウ情報
      static inline WindowType _windowType{WindowType::Default};
      //!< 使用するパーティクル上限
      static inline int _particleMax{0};
      //!< ウィンドウサイズ(幅)
      static inline int _width{0};
      //!< ウィンドウサイズ(高さ)
      static inline int _height{0};
      static inline int _colorBit{0};       //!< カラービット数
      static inline bool _setInstance{false};   //!< 生成フラグ
      static inline bool _windowMode{false};    //!< ウィンドウモード
      //!< アプリケーションの実体
      static inline std::shared_ptr<ApplicationBase> _instance{nullptr};
      //!< ファイルサーバ
      std::unique_ptr<FileServer::FileServer> _fileServer{nullptr};
      //!< インプットオペレーション
      std::unique_ptr<InputOperation> _input{nullptr};
      //!< モードサーバ
      std::unique_ptr<Mode::ModeServer> _modeServer{nullptr};
      //!< サウンドサーバ
      std::unique_ptr<Sound::SoundServer> _soundServer{nullptr};
      //!< サウンドコンポーネント
      std::unique_ptr<Sound::SoundComponent> _soundComponent{nullptr};
      //!< リソースサーバ
      std::unique_ptr<Resource::ResourceServer> _resourceServer{nullptr};
      //!< モデルサーバ
      std::unique_ptr<Model::ModelServer> _modelServer{nullptr};
#ifdef _DEBUG
      //!< デバッグフラグ
      static inline bool _debug{false};
#endif
      /**
       * @brief  入力処理
       * @return true:処理成功 false:処理失敗
       */
      virtual bool Input();
      /**
       * @brief  更新処理
       * @return true:処理成功 false:処理失敗
       */
      virtual bool Process();
      /**
       * @brief  描画処理
       * @return true:処理成功 false:処理失敗
       */
      virtual bool Draw();
      /**
       * @brief  Instanceの生成を行うかの判定
       * @return true:生成に移行 false:既に実体が定義されている
       */
      static bool SetInstance();
      /**
       * @brief  ウィンドウ情報の設定
       * @param  window ウィンドウサイズ情報
       * @param  bit    カラービット数を変更するかのフラグ
       *                true:32ビットカラー(デフォルト)  false:16ビットカラー
       */
      void SetWindowSize(const WindowType& winodw, bool bit = true);
      /**
       * @brief  アプリケーションを終了するかの判定
       */
      virtual void IsQuit();
      /**
       * @brief  カラービット数の設定
       * @param  bit ビットカラーフラグ(true:32ビットカラー(デフォルト)  false:16ビットカラー)
       * @return 対応するカラービット
       */
      int ColorBit(const bool bit) const;
      /**
       * @brief  ウィンドウ情報と一致する画面サイズの取得
       * @return first:横幅 second:縦幅
       */
      virtual std::pair<int, int> WindowSize() const;
      /**
       * @brief Zバッファの設定を有効にするか
       * @param flag true:有効化(デフォルト) false:有効化しない
       */
      virtual void SetZBuffer(bool flag = true);
    };
  } // namespace Application
} // namespace AppFrame