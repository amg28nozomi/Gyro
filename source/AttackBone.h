/*****************************************************************//**
 * @file   AttackBone.h
 * @brief  攻撃判定で使用するボーン情報クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <vector>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class  AttackBone
     * @brief  アタックボーン情報
     */
    class AttackBone {
    public:
      /**
       * @brief コンストラクタ
       */
      AttackBone();
      /**
       * @brief  ボーン
       * @param  bone ボーン番号
       */
      AttackBone(int bone);

      AttackBone(int a, int b);
      /**
       * @brief  ボーン情報の取得
       * @return ボーン情報
       */
      std::vector<int> GetBone() const {
        return _bone;
      }
    protected:
      std::vector<int> _bone; //!< ボーン情報
    };
  } // namespace Object
} // namespace Gyro