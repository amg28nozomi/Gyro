/*****************************************************************//**
 * @file   InputBase.h
 * @brief  入力状態の基底クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーション
   */
  namespace Application {
    constexpr auto Error = -1; // 処理失敗
    /**
     * @class  InputBase
     * @brief  入力状態クラス
     */
    class InputBase {
    public:
      /**
       * @brief 入力デバイスの種類
       */
      enum class DeviceType {
        Joypad,  //!< ジョイパッド
        Mouse,   //!< マウス
        Keyborad //!< キーボード
      };
      /**
       * @brief 入力デバイスの状態
       */
      enum class State {
        Active,   //!< 接続有り
        NonActive //!< 接続無し
      };
      /**
       * @brief  コンストラクタ
       */
      InputBase();
      /**
       * @brief  デストラクタ
       */
      virtual ~InputBase();
      /**
       * @brief  更新処理
       */
      virtual void Process() = 0;
      /**
       * @brief  デバイスタイプの取得
       * @return デバイスタイプ
       */
      inline const DeviceType GetType() const {
        return _type;
      }
      /**
       * @brief  総接続数の取得
       * @return 総接続数
       */
      static inline int GetConnection() {
        return _connection;
      }
      /**
       * @brief  有効かどうかの判定
       * @return true:有効 false:非有効
       */
      bool IsActive() const {
        return _active;
      }
    protected:
      static inline int _connection{0}; //!< 総接続数
      DeviceType _type{0}; //!< デバイスの機種
      State _state;        //!< 状態
      bool _active{true};  //!< 有効かどうか
    };
  } // Application
} // AppFrame