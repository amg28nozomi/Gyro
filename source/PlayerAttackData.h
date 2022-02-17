/*****************************************************************//**
 * @file   PlayerAttackData.h
 * @brief  自機の攻撃情報を管理する情報クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "PlayerAttack.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    /**
     * @class  PlayerAttackData
     * @brief  自機の攻撃情報を格納するデータ
     */
    //class PlayerAttackData {
    //public:
    //  /**
    //   * @brief コンストラクタ
    //   * @param next     遷移する状態
    //   * @param start    入力受付開始
    //   * @param end      入力受付終了
    //   * @param coolTime 硬直時間
    //   */
    //  PlayerAttackData(const PlayerAttack::AttackState next, int start, int end, int coolTime);
    //  /**
    //   * @brief  遷移する攻撃状態を返す
    //   * @return 遷移状態。コンボが継続しない場合はNoneを返す
    //   */
    //  PlayerAttack::AttackState NextState() const {
    //    return _next;
    //  }
    //  /**
    //   * @brief  入力開始フレームの取得
    //   * @return 入力開始フレーム
    //   */
    //  float StartFrame() const {
    //    return static_cast<float>(_start);
    //  }
    //  /**
    //   * @brief  入力終了フレームの取得
    //   * @return 入力終了フレーム
    //   */
    //  float EndFrame() const {
    //    return static_cast<float>(_end);
    //  }
    //  /**
    //   * @brief  硬直時間の取得
    //   * @return 硬直時間
    //   */
    //  float CoolTime() const {
    //    return static_cast<float>(_coolDown);
    //  }
    //private:
    //  //!< 遷移する攻撃状態
    //  PlayerAttack::AttackState _next;
    //  //!< 入力受付フレーム(開始)
    //  int _start;
    //  //!< 入力受付フレーム(終了)
    //  int _end;
    //  //!< クールタイム(硬直時間)
    //  int _coolDown;
    //};
  } // namespace Player
} // namespace Gyro