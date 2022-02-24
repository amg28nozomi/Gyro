/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   地上敵クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#include "EnemyWheel.h"
#include <DxLib.h>
#include "UtilityDX.h"
#include "ApplicationMain.h"
#include "ObjectServer.h"
#include "Player.h"

namespace {
  // 各種定数
  constexpr int WheelHP = 5000;           //!< 地上敵最大体力
  constexpr float WheelMoveSpead = 5.0f;  //!< 地上的移動速度
  // アニメーションキー
  constexpr std::string_view IdleKey = "EnemyIdle";      //!< 待機
  constexpr std::string_view MoveKey = "EnemyMove";      //!< 移動
  constexpr std::string_view AttackKey = "EnemyAttack";  //!< 攻撃
}

namespace Gyro {
  namespace Enemy {
    EnemyWheel::EnemyWheel(Application::ApplicationMain& app) : EnemyBase(app) {
      // 初期化
      Init();
    }

    EnemyWheel::~EnemyWheel() {

    }

    bool EnemyWheel::Init() {
      // モデル読み込み
      LoadModel();
      // パラメータの設定
      SetParameter();
      // アニメーションアタッチ
      _modelAnim.SetMainAttach(_mHandle, IdleKey, 1.0f, true);
      _radius = 300.0f;

      return true;
    }

    bool EnemyWheel::Process() {
      // 基底クラスの更新処理を呼び出し
      EnemyBase::Process();
      // 前フレームの状態
      EnemyState oldEnemyState = _enemyState;
      // 索敵範囲に入ったら状態をMoveに変化
      // 状態もどき
      switch (_enemyState) {
        case Gyro::Enemy::EnemyBase::EnemyState::Move:
          Move();  //!< 移動
          break;
        case Gyro::Enemy::EnemyBase::EnemyState::Attack:
          Attack();  //!< 攻撃
          break;
        case Gyro::Enemy::EnemyBase::EnemyState::Dead:
          Dead();  //!< 死亡
          break;
        default:
          _enemyState = EnemyState::Idle;
          Sercth(_radius);
          break;
      }
      // 衝突判定
      Hit();
      // 無敵状態ではない場合、ダメージ判定を行う
      if (!_invincible->Invincible()) {
        IsDamege();
      }
      // ワールド座標の更新
      WorldMatrix();
      // ワールド座標の設定
      MV1SetMatrix(_mHandle, UtilityDX::ToMATRIX(_world));

      // 状態遷移したか
      if (IsChangeState(oldEnemyState)) {
        // アニメーション変更
        ChangeAnim();
        // エフェクト再生
        PlayEffect();
      }
      // 体力ゲージの更新
      _gaugeHp.Process();
      // モデルアニメの更新
      _modelAnim.Process();

      return true;
    }

    bool EnemyWheel::Draw() const {
      // 基底側の描画
      EnemyBase::Draw();
      // 体力ゲージの描画
      _gaugeHp.Draw();
#ifdef _DEBUG
      // デバッグフラグがある場合のみ描画処理を行う
      if (_app.GetDebugFlag()) {
        // 当たり判定の描画
        _capsule->Draw();
        auto pos = _position.AddVectorY(10.0f);
        DrawCone3D(UtilityDX::ToVECTOR(pos), UtilityDX::ToVECTOR(_position), _radius, 16, GetColor(0, 0, 255), GetColor(255, 255, 255), false);
      }
#endif
      return true;
    }

    void EnemyWheel::LoadModel() {
      // モデルハンドルの取得
      auto [handle, key] = _app.GetModelServer().GetModel("enemy", _number);
      // モデルデータ設定
      ++_number;
      _mHandle = handle;
      _this = key;
    }

    void EnemyWheel::SetParameter() {
      // 各種設定
      _enemyHP = WheelHP;
    }

    void EnemyWheel::SetCollision() {
      // 球の当たり判定設定
      _sphere = std::make_unique<Object::CollisionSphere>(*this, _position.AddVectorY(100.0f), 50.0f);
      // カプセルコリジョンの設定
      _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 200.0f, 30.0f);
    }

    void EnemyWheel::Move() {
      using Vector4 = AppMath::Vector4;
      // ターゲット座標
      auto target = Vector4();
      auto prot = AppMath::Vector4();
      _app.GetObjectServer().GetPlayerTransForm(target, prot);
      auto forward = _position.Direction(target);
      // 正規化
      forward.Normalize();
      auto move = forward * (WheelMoveSpead);
      // _sphere->Process();
      // ラジアンを生成(z軸は反転させる)
      auto radian = std::atan2(move.GetX(), -move.GetZ());
      _position.Add(move);
      _capsule->Process(move);
#ifndef _DEBUG
      _rotation.SetY(radian); // y軸の回転量をセットする
#else
      // デグリー値をセットする(デバッグ用)
      _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Attack;
      }
    }

    void EnemyWheel::Attack() {
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Idle;
        _iMove = false;
      }
    }

    void EnemyWheel::Hit() {
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
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

    void EnemyWheel::ChangeAnim() {
      // 対応アニメーション切り替え
      switch (_enemyState) {
      case EnemyState::Idle:    //!< 待機
        _modelAnim.SetBlendAttach(IdleKey, 10.0f, 1.0f, true);
        break;
      case EnemyState::Move:    //!< 移動
        _modelAnim.SetBlendAttach(MoveKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Attack:  //!< 攻撃
        _modelAnim.SetBlendAttach(AttackKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Damage:  //!< 被ダメ
        break;
      case EnemyState::Dead:    //!< 死亡
        break;
      default:
        break;
      }
    }

    void EnemyWheel::PlayEffect() {
      // パラメータ設定
      auto effect = _app.GetEffect();
      auto ePos = _position;
#ifndef _DEBUG
      auto eRad = -_rotation.GetY();
#else
      auto eRad = -AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
      // 対応エフェクト再生
      switch (_enemyState) {
      case EnemyState::Idle:    //!< 待機
        break;
      case EnemyState::Move:    //!< 移動
        ePos.AddY(135.0f);
        effect.PlayEffect(Effect::eEyeLight, ePos, eRad);
        break;
      case EnemyState::Attack:  //!< 攻撃
        effect.PlayEffect(Effect::eGroundAttack, ePos, eRad);
        break;
      case EnemyState::Damage:  //!< 被ダメ
        ePos.AddY(100.0f);
        effect.PlayEffect(Effect::eHit, ePos, eRad);
        break;
      case EnemyState::Dead:    //!< 死亡
        ePos.AddY(100.0f);
        effect.PlayEffect(Effect::eExprosion, ePos, eRad);
        break;
      default:
        break;
      }
    }

    bool EnemyWheel::IsDamege() {
      // 無敵状態かの判定

      // 自機の取得
      const auto player = _app.GetObjectServer().GetPlayer();
      // 攻撃コンポーネントの取得
      auto attack = player->AttackComponent();
      using AtkComponent = Object::AttackComponent;
      // 対象は攻撃状態か？
      if (attack.GetState() == AtkComponent::AttackState::NonActive) {
        return false; // 攻撃状態ではない
      }
      // 攻撃状態の場合は攻撃コリジョンと当たり判定を行う
      if (_capsule->IntersectSphere(*std::dynamic_pointer_cast<Object::CollisionSphere>(attack.GetCollision()))) {
#ifdef _DEBUG
        // 衝突時に対象球の色を変える
        std::dynamic_pointer_cast<Object::CollisionSphere>(attack.GetCollision())->HitOn();
#endif
        _enemyHP -= 1000;
        if (_enemyHP <= 0) {
          _enemyState = EnemyState::Dead;
        }
        else {
          _enemyState = EnemyState::Damage;
        }
        // 衝突フラグがある場合は無敵時間を開始する
        _invincible->Start();
        return true; // 衝突判定
      }
      return false;  // 衝突なし
    }
  } // namespace Enemy
} // namespace Gyro