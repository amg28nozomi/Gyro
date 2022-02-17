#include "PlayerAttack.h"
#include "PlayerAttackData.h"

namespace Gyro {
  namespace Player {

    //PlayerAttack::PlayerAttack(Object::ObjectBase& owner) : Object::AttackComponent(owner, nullptr) {

    //}

    //void PlayerAttack::CreateRegistry() {
    //  // データベースが空の場合のみ生成を行う
    //  if (!_registry.empty()) {
    //    return; // 要素が登録されているの処理をスキップする
    //  }
    //  // デフォルトの攻撃情報を保持するコンテナ
    //  std::unordered_map<PlayerAttack::AttackType, PlayerAttackData> attacks {
    //    // 弱攻撃1→弱攻撃2
    //    {AttackType::Heavy1, {AttackType::Heavy2, 70, 90, 50}},
    //    // 弱攻撃2→弱攻撃3
    //    {AttackType::Heavy2, {AttackType::Heavy3, 70, 90, 50}},
    //    // 弱攻撃3(派生なし)
    //    {AttackType::Heavy3, {AttackType::None, 0, 0, 100}},
    //  };
    //}

    //bool PlayerAttack::ChangeState(const AttackType& attack) {
    //  return true;
    //}

  } // namespace Player
} // namespace Gyro