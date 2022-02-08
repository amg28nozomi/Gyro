/*****************************************************************//**
 * @file   SpawnEnemy.h
 * @brief  スポーンベースのサブクラス
 *         エネミー用のスポーン情報クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "SpawnBase.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    constexpr auto EnemyWheel = 0; //!< 陸上型エネミー
    /**
     * @class SpawnEnemy
     * @brief エネミーのスポーン情報
     */
    class SpawnEnemy : public SpawnBase {
    public:
      /**
       * @brief エネミーの種類
       */
      enum class EnemyType {
        None, // 該当なし
        Wheel // 陸上型
      };
      /**
       * @brief  空のコンストラクタ
       */
      SpawnEnemy();
      /**
       * @brief  コンストラクタ
       * @param  type オブジェクトタイプ
       * @param  position 生成座標
       * @param  rotation 向き
       * @param  scale    拡大率
       * 
       */
      SpawnEnemy(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale);
      /**
       * @brief ムーブコンストラクタ
       * @param spawn ムーブ対象
       */
      SpawnEnemy(SpawnEnemy&& spawn) = default;
      /**
       * @brief  エネミータイプの取得
       * @return エネミータイプを返す
       */
      const EnemyType GetEnemyType() const {
        return _enemyType;
      }
      /**
       * @brief  エネミー情報の参照の取得
       * @return 参照を返す
       */
      SpawnEnemy& GetInstanceEnemy() {
        return *this;
      }
    private:
      EnemyType _enemyType; //!< エネミータイプ
      /**
       * @brief  番号をエネミータイプに変換する
       * @param  number 番号
       * @return 該当するエネミータイプを返す
       *         番号が該当しない場合はNoneを返す
       */
      const EnemyType NumberToEnemyType(const int number) const;
    };
  } // namespace Object
} // namespace Gyro

