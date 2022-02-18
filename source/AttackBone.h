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
    protected:
      std::vector<int> _bone; //!< ボーン情報
    };
  } // namespace Object
} // namespace Gyro