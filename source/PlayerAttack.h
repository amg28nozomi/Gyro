/*****************************************************************//**
 * @file   PlayerAttack.h
 * @brief  自機の攻撃処理クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AttackComponent.h"
#include <unordered_map>
  
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プレイヤーベース
   */
  namespace Player {

    //class PlayerAttackData; //!< 前方宣言
    ///**
    // * @class  PlaterAttack
    // * @brief  自機の攻撃処理クラス
    // */
    //class PlayerAttack : public Object::AttackComponent {
    //public:
    //  /**
    //   * @brief 攻撃の種類を表す列挙型クラス
    //   */
    //  enum class AttackType {
    //    None,   //!< なし
    //    Light1, //!< 弱攻撃1
    //    Light2, //!< 弱攻撃2
    //    Light3, //!< 弱攻撃3
    //    Heavy1, //!< 強攻撃1
    //    Heavy2, //!< 強攻撃2
    //    Heavy3, //!< 強攻撃3
    //    Trick   //!< トリック
    //  };
    //  /**
    //   * @brief コンストラクタ
    //   * @param owner 所有者の判定
    //   */
    //  PlayerAttack(Object::ObjectBase& owner);
    //  /**
    //   * @brief 開始処理
    //   */
    //  void Start() override;
    //  /**
    //   * @brief 終了勝利
    //   */
    //  void Finish() override;
    //  /**
    //   * @brief  攻撃状態の取得
    //   * @return 攻撃状態
    //   */
    //  AttackType GetAttackType() const {
    //    return _attackType;
    //  }
    //private:
    //  //!< 攻撃状態をキーとして、攻撃情報を管理する連想配列
    //  std::unordered_map<AttackType, PlayerAttackData> _registry;
    //  //!< 攻撃の種類
    //  AttackType _attackType{AttackType::None};
    //  //!< チェインカウント
    //  int _chain{0};
    //  /**
    //   * @brief  攻撃状態の切り替え
    //   * @param  attack
    //   * @return 
    //   */
    //  bool ChangeState(const AttackType& attack);
    //  /**
    //   * @brief データベースの生成
    //   */
    //  void CreateRegistry();
    //};
  } // namespace Player
} // namespace Gyro