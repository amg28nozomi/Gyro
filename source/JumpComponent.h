/*****************************************************************//**
 * @file   JumpComponent.h
 * @brief  ジャンプ機能クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    /**
     * @brief ジャンプ処理
     */
    class JumpComponent {
    public:
      /**
       * @brief コンストラクタ
       */
      JumpComponent() {}
      /**
       * @brief  ジャンプの設定
       * @param  range  跳躍距離
       * @param  frigth 対空時間
       */
      void Set(const float range, const int frigth);
      /**
       * @brief ジャンプ処理の開始
       */
      void Start();
      /**
       * @brief ジャンプの終了
       */
      void Finish();
      /**
       * @brief  ジャンプ力の取得
       * @return ジャンプ力
       */
      float JumpPower();
      /**
       * @brief カウンタの初期化
       */
      inline void CountClear() {
        _count = 0;
      }
      /**
       * @brief  総対空時間の取得
       * @return 総対空時間(カウント)
       */
      int Fright() const {
        return _fright;
      }
      /**
       * @brief  経過フレームの取得
       * @return 経過フレーム
       */
      int Count() const {
        return _count;
      }
      /**
       * @brief  現在設定されている対空時間の取得
       * @return 対空時間
       */
      float Range() const {
        return _range;
      }
      /**
       * @brief  ジャンプフラグの取得
       * @return ジャンプフラグ
       */
      bool IsJump() const {
        return _jump;
      }
    protected:
      int _fright{0};     //!< 総対空時間
      int _count{0};      //!< 経過カウンタ
      float _range{0.0f}; //!< 跳躍距離
      int _f{0};
      bool _jump{false};  //!< ジャンプフラグ
    };
  } // namespace Player
} // namespace Gyro