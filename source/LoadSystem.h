/*****************************************************************//**
 * @file   LoadSystem.h
 * @brief  非同期読み込み処理クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <future>
#include <unordered_map>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーション
   */
  namespace Application {
    class ApplicationMain; //!< 前方宣言
    constexpr auto LoadError = -1; //!< ロード対象ではない
    constexpr auto LoadQuit = 1;   //!< 読み込み終了
    constexpr auto Load = 0;       //!< ロード廚あ
    /**
     * @class LoadSystem
     * @brief 非同期読み込み
     */
    class LoadSystem {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      LoadSystem(ApplicationMain& app);
      /**
       * @brief  読み込み処理は終了したかの判定
       * @param  number 処理番号
       * @return 0:ロード中 1:ロード終了 -1:キーが不正
       */
      int LoadEnd(const int number) const;
    private:
      //!< アプリケーションの参照
      ApplicationMain& _app;
      //!< 処理番号をキーとして、非同期読みフラグを管理する連想配列
      std::unordered_map<int, bool> _registry;
      /**
       * @brief  要素が登録されているかの判定
       * @param  number キー
       * @return true:登録済み false:未登録
       */
      bool Contents(const int number) const;
    };

  } // namespace 
} // namespace Gyro