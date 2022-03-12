/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   敵の基底クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "UtilityDX.h"
#include "ApplicationMain.h"
#include "ObjectServer.h"
#include "SpawnEnemy.h"
#include "Player.h"
#include "StageComponent.h"
namespace {
  // 無敵時間(フレーム)
  constexpr auto InvincibleTime = 120;
}

namespace Gyro {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : Object::ObjectBase(app) {
      // 初期化
      Init();
    }

    EnemyBase::~EnemyBase() {

    }

    bool EnemyBase::Init() {
      // 初期化
      SetParameter();
      // 無敵処理の生成
      _invincible = std::make_unique<Object::InvincibleComponent>(_app);
      // 無敵時間の設定
      _invincible->Set(InvincibleTime);

      return true;
    }

    bool EnemyBase::Process() {
      // 基底クラスの更新処理を呼び出し
      ObjectBase::Process();
      // 無敵状態か
      if (_invincible->Invincible()) {
        // 無敵時間の経過処理を呼び出し
        _invincible->Process();
      }
      // カウントが1以上あるか？
      if (_cnt > 0) {
          _cnt--;
      }
      // 場外に出た時死亡するようにする
      if (_position.GetY() < -100.0f) {
        _enemyHP -= 50000;
        _gaugeHp->Sub(50000);
      }
      if (_enemyHP <= 0) {
        _enemyState = EnemyState::Dead;
      }

      return true;
    }

    bool EnemyBase::Draw() const {
      // 死亡状態の場合は描画を行わない
      if (_state != ObjectState::Dead) {
        // 描画
        MV1DrawModel(_mHandle);
      }
#ifdef _DEBUG
      if (_app.GetDebugFlag()) {
        // _sphere->Draw();
      }
#endif
      return true;
    }

    void EnemyBase::Set(Object::SpawnEnemy& spawn) {
      // 座標情報をセットする
      ObjectBase::Set(spawn.GetInstance());
      // 当たり判定の設定
      SetCollision();
      // auto enemy = dynamic_cast<Object::SpawnEnemy*>(&spawn);
    }

    void EnemyBase::LoadModel() {

    }

    void EnemyBase::SetParameter() {
      _id = ObjectId::Enemy;
      _enemyState = EnemyState::Idle;
    }

    void EnemyBase::SetCollision() {

    }

    void EnemyBase::Move() {

    }

    void EnemyBase::Attack() {

    }

    void EnemyBase::NockBack() {

    }

    void EnemyBase::Search() {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      for (auto pla : objects) {
        if (pla->GetId() != ObjectId::Player) continue;
        auto position = pla->GetPosition();
        // 円と点の距離
        auto a = position.GetX() - _position.GetX();
        auto b = position.GetZ() - _position.GetZ();
        auto c = sqrt(a * a + b * b);
        // 距離と半径を比較して状態変化
        if (c < _attackRadius) {
          _enemyState = EnemyState::Attack;
          break;
        }
        else if (c < _serchRadius) {
          _enemyState = EnemyState::Move;
          break;
        }
        else {
          _enemyState = EnemyState::Idle;
          break;
        }
      }
    }

    void EnemyBase::Hit() {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      // 衝突判定を行う
      for (auto obj : objects) {
        // 敵の場合のみ処理を行う
        if (obj->GetId() != ObjectId::Enemy) continue;
        // 一致している場合は除外
        if (std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->Equals(_mHandle)) {
          continue; // 同一オブジェクトのため除外
        }
        // 球と球の衝突判定
        if (_sphere->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCollision())) {
          // 衝突した場合は押し出し処理を行う
        }
        // カプセルとカプセルの衝突判定
        if (_capsule->IntersectCapsule(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule())) {
          // 衝突している場合は押し出し処理を行う
          auto y = _position.GetY(); // Y座標は変更を行わない
          // 二つの座標から押し出し力を算出する
          auto mPos = _capsule->GetPosition();
          auto ePos = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule().GetPosition();
          auto v = (mPos - ePos);   // 中心距離
          auto length2 = v.LengthSquared(); // 二点間の長さを算出
          auto radius2 = _capsule->GetRadius() + std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule().GetRadius();
          auto l7 = radius2 - std::sqrtf(v.GetX() * v.GetX() + v.GetZ() * v.GetZ());
          v.Normalize();
          AppMath::Vector4 vv(v.GetX() * l7, 0.0f, v.GetZ());
          _position.Add(vv);
          _capsule->SetPosition(_position);
        }
      }
    }

    void EnemyBase::ChangeAnim() {
      // 対応アニメーション切り替え
      switch (_enemyState) {
      case EnemyState::Idle:    //!< 待機
        break;
      case EnemyState::Move:    //!< 移動
        break;
      case EnemyState::Attack:  //!< 攻撃
        break;
      case EnemyState::Damage:  //!< 被ダメ
        break;
      case EnemyState::Dead:    //!< 死亡
        break;
      default:
        break;
      }
    }

    void EnemyBase::PlayEffect() {
      // 対応エフェクト再生
      switch (_enemyState) {
      case EnemyState::Idle:    //!< 待機
        break;
      case EnemyState::Move:    //!< 移動
        break;
      case EnemyState::Attack:  //!< 攻撃
        break;
      case EnemyState::Damage:  //!< 被ダメ
        break;
      case EnemyState::Dead:    //!< 死亡
        break;
      default:
        break;
      }
    }

    void EnemyBase::Dead() {
      // アニメーション終了でDeadへ移行
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _state = ObjectState::Dead;
      }
    }

    bool EnemyBase::IsDamege() {
      // 各種データの取得
      const auto player = _app.GetObjectServer().GetPlayer();
      auto attack = player->AttackComponent();
      using AtkComponent = Object::AttackComponent;
      // 対象は攻撃状態か？
      if (attack.GetState() == AtkComponent::AttackState::NonActive) {
        return false; // 攻撃状態ではない
      }
      // 攻撃状態の場合は攻撃コリジョンと当たり判定を行う
      if (_capsule->IntersectCapsule(*std::dynamic_pointer_cast<Object::CollisionCapsule>(attack.GetCollision()))) {
        return true; // 衝突判定
      }
      return false;  // 衝突なし
    }

    bool EnemyBase::IsStand() {
      // 新しい座標
      auto newPos = _position.AddVectorY(_gravityScale);
      // 新しいカプセル
      auto newCapsule = *_capsule;
      // カプセル座標をセット
      newCapsule.SetPosition(newPos);
      // 線分の取得
      auto [start, end] = newCapsule.LineSegment().GetVector();

      auto flag = false;
      // 地形(床)と線分の衝突判定
      for (int i = 0; i < _app.GetStageComponent().GetStageModel().size(); i++) {
        auto handleMap = _app.GetStageComponent().GetStageModel()[i];
        auto hit = MV1CollCheck_Line(handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
        // 衝突フラグがない場合
        if (hit.HitFlag == 0) {
          continue;
        }
        // 衝突座標を座標に代入
        _position = UtilityDX::ToVector(hit.HitPosition);
        // 新しい座標をコリジョンに反映
        _capsule->SetPosition(_position);
        flag = true;
        break;
      }
      // 衝突フラグがfalseの時落下
      if (flag == false) {
        // 新しい座標をセット
        _position = newPos;
        // コリジョン情報に更新をかける
        _capsule->SetPosition(_position);
      }
      return flag;
    }

    bool EnemyBase::ProcessFlag() {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      for (auto pla : objects) {
        if (pla->GetId() != ObjectId::Player) continue;
        auto position = pla->GetPosition();
        // 円と点の距離
        auto a = position.GetX() - _position.GetX();
        auto b = position.GetZ() - _position.GetZ();
        auto c = sqrt(a * a + b * b);
        // 距離と半径を比較してflag変化
        if (c < _flagRadius) {
          _gravity = true;
          return true;
          break;
        }
      }
      _gravity = false;
      return false;
    }
  } // namespace Enemy
} // namespace Gyro