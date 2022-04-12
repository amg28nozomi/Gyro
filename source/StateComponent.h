/*****************************************************************//**
 * @file   StateComponent.h
 * @brief  状態遷移判定用のコンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <utility>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class  ObjectComponent
     * @brief  状態遷移判定用のコンポーネント
     */
    class StateComponent : public ObjectComponent {
    public:
      /**
       * @brief コンストラクタ
       */
      StateComponent();
      /**
       * @brief  初期化処理
       */
      void Init() override;
      /**
       * @brief  入力処理の設定
       * @param  total アニメーションの総再生フレーム数
       * @param  start 判定開始フレーム(割合)
       * @param  end   判定終了フレーム(割合)
       * @return true:設定成功 false:設定失敗
       */
      bool Set(float total, int start, int end);
      /**
       * @brief  開始処理
       */
      void Start() override;
      /**
       * @brief  終了処理
       */
      void Finish() override;
      /**
       * @brief  更新処理
       * @param  play アニメーションの再生フレーム
       * @return true:入力あり false:入力なし
       */
      bool Process(const float play);
    private:
      int _start{0};     //!< 入力受付フレーム(開始)
      int _end{0};       //!< 入力受付フレーム(終了)
      bool _flag{false}; //!< 入力があったか
      /**
       * @brief  判定フレームの算出
       * @param  total   総再生フレーム
       * @param  percent 割合
       * @return 判定フレーム
       */
      int Frame(float total, int percent);
    };
  } // namespace Object
} // namespace Gyro