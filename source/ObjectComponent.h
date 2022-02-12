/*****************************************************************//**
 * @file   ObjectComponentComponent.h
 * @brief  オブジェクト用機能のスーパークラス
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
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class ObjectComponent 
     * @brief オブジェクト用機能の基底クラス
     */
    class ObjectComponent {
    public:
      /**
       * @brief 機能の種類を表す列挙型クラス
       */
      enum class ComponentType {
        None, // 該当なし
        Jump, // ジャンプ
        Wire  // ワイヤー
      };
      /**
       * @brief コンストラクタ
       */
      ObjectComponent();
      /**
       * @brief 初期化処理
       */
      virtual void Init(){}
      /**
       * @brief 開始処理
       */
      virtual void Start() = 0;
      /**
       * @brief 終了処理
       */
      virtual void Finish(){}
      /**
       * @brief  コンポーネントタイプの取得
       * @return コンポーネントタイプ
       */
      ComponentType GetType() const {
        return _type;
      }
    protected:
      ComponentType _type; //!< 機能を表す列挙型
    };
  } // namespace Player
} // namespace Gyro