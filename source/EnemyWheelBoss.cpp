/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   地上敵ボスクラス
 *
 * @author  土橋峡介
 * @date    March 2022
 *********************************************************************/
#include "EnemyWheelBoss.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "Player.h"
#include <algorithm>

namespace {
  // 各種定数
  constexpr int WheelHP = 10000;          //!< 地上敵最大体力
  constexpr float WheelMoveSpead = 5.0f;  //!< 地上的移動速度
  constexpr float WheelAttackSpead = 10.0f;  //!< 地上的攻撃移動速度
  constexpr float Height = 530.0f;        //!< 高さ
  // アニメーションキー
  constexpr std::string_view IdleKey = "idle";      //!< 待機
  constexpr std::string_view MoveKey = "idle";      //!< 移動
  constexpr std::string_view AttackKey = "attack";  //!< 攻撃
  constexpr std::string_view AttackReadyKey = "attack_ready";  //!< 攻撃準備
  constexpr std::string_view AttackFinishKey = "attack_finish"; //!< 攻撃終了
  constexpr std::string_view DamageKey = "damage";  //!< ダメージ
  constexpr std::string_view DeadKey = "dead";      //!< 死亡
}

namespace Gyro {
  namespace Enemy {
    EnemyWheelBoss::EnemyWheelBoss(Application::ApplicationMain& app) : EnemyBase(app) {
      // 初期化
      Init();
      _gravity = true;
    }

    EnemyWheelBoss::~EnemyWheelBoss() {
    }

    bool EnemyWheelBoss::Init() {
      // モデル読み込み
      LoadModel();
      // パラメータの設定
      SetParameter();
      // アニメーションアタッチ
      _modelAnim.SetMainAttach(_mHandle, IdleKey, 1.0f, true);

      return true;
    }

    bool EnemyWheelBoss::Process() {
      // 基底クラスの更新処理を呼び出し
      EnemyBase::Process();
      // 前フレームの状態
      EnemyState oldEnemyState = _enemyState;
      // 索敵範囲に入ったら状態をMoveに変化
      // 状態もどき
      switch (_enemyState) {
      case Gyro::Enemy::EnemyBase::EnemyState::Move:
        Move();  //!< 移動
        Sercth(); //!< 探索
        break;
      case Gyro::Enemy::EnemyBase::EnemyState::AttackReady:
        AttackReady();
        break;
      case Gyro::Enemy::EnemyBase::EnemyState::Attack:
        Attack();  //!< 攻撃
        break;
      case EnemyState::Damage:
        NockBack(); //!< ノックバック
        break;
      case Gyro::Enemy::EnemyBase::EnemyState::Dead:
        Dead();  //!< 死亡
        break;
      default:
        _enemyState = EnemyState::Idle;
        Sercth(); //!< 探索
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
      // 地形との当たり判定
      //IsStand();
      // 場外に出た時死亡するようにする
      if (_position.GetY() < -100.0f) {
        _enemyHP -= 50000;
        _gaugeHp->Sub(50000);
      }
      if (_enemyHP <= 0) {
        _enemyState = EnemyState::Dead;
      }
      // 状態遷移したか
      if (IsChangeState(oldEnemyState)) {
        // アニメーション変更
        ChangeAnim();
        // エフェクト再生
        PlayEffect();
      }
      // 体力ゲージの更新
      _gaugeHp->Process();
      // モデルアニメの更新
      _modelAnim.Process();

      return true;
    }

    bool EnemyWheelBoss::Draw() const {
      // 基底側の描画
      EnemyBase::Draw();
      // 体力ゲージの描画
      _gaugeHp->Draw(_position, Height);
#ifdef _DEBUG
      // デバッグフラグがある場合のみ描画処理を行う
      if (_app.GetDebugFlag()) {
        // 当たり判定の描画
        if (_enemyState == EnemyState::Attack) {
          _sphere->Draw();
        }
        _capsule->Draw();
        auto pos = _position.AddVectorY(10.0f);
        DrawCone3D(UtilityDX::ToVECTOR(pos), UtilityDX::ToVECTOR(_position), _attackRadius, 16, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
        DrawCone3D(UtilityDX::ToVECTOR(pos), UtilityDX::ToVECTOR(_position), _serchRadius, 16, GetColor(0, 0, 255), GetColor(255, 255, 255), false);
      }
#endif
      return true;
    }

    void EnemyWheelBoss::LoadModel() {
      // モデルハンドルの取得
      auto [handle, key] = _app.GetModelServer().GetModel("enemyWheelBoss", _number);
      // モデルデータ設定
      ++_number;
      _mHandle = handle;
      _this = key;
    }

    void EnemyWheelBoss::SetParameter() {
      // 各種設定
      _enemyHP = WheelHP;
      _gaugeHp = std::make_shared<Gauge::GaugeEnemy>(_app);
      _gaugeHp->Init(WheelHP);
      _serchRadius = 350.0f;
      _attackRadius = 200.0f;
      _sort = 0;
      _gravity = false;
    }

    void EnemyWheelBoss::SetCollision() {
      // 球の当たり判定設定
      _sphere = std::make_unique<Object::CollisionSphere>(*this, _position.AddVectorY(100.0f), 50.0f);
      // カプセルコリジョンの設定
      _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 450.0f, 70.0f);
    }

    void EnemyWheelBoss::Move() {
      using Vector4 = AppMath::Vector4;
      // ターゲット座標
      auto target = Vector4();
      auto prot = AppMath::Vector4();
      _app.GetObjectServer().GetPlayerTransForm(target, prot);
      auto forward = _position.Direction(target);
      // 高さがいらないので分解してy以外を取り出す
      auto [x, y, z] = forward.GetVector3();
      auto efor = AppMath::Vector4(x, 0.0f, z);
      // 正規化
      efor.Normalize();
      auto move = efor * (WheelMoveSpead);
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
        _enemyState = EnemyState::Idle;
      }
    }

    void EnemyWheelBoss::AttackReady() {
      // ターゲット座標
      auto target = AppMath::Vector4();
      auto prot = AppMath::Vector4();
      _app.GetObjectServer().GetPlayerTransForm(target, prot);
      auto forward = _position.Direction(target);
      // 高さがいらないので分解してy以外を取り出す
      auto [x, y, z] = forward.GetVector3();
      auto efor = AppMath::Vector4(x, 0.0f, z);
      auto move = efor * (WheelMoveSpead);
      // ラジアンを生成(z軸は反転させる)
      auto radian = std::atan2(move.GetX(), -move.GetZ());
      _rotation.SetY(radian); // y軸の回転量をセットする
      // アニメーション終了でAttackへ移行
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Attack;
        _iMove = false;
      }
    }


    void EnemyWheelBoss::Attack() {
      if (_iMove != true) {
        _iMove = true;
        // アニメーションから指定したボーンのローカル座標を取得
        auto attachIndex = _modelAnim.GetMainAttachIndex();
        auto rPos = MV1GetFramePosition(_mHandle, 13);
        _sphere->SetPosition(UtilityDX::ToVector(rPos));
        _sphere->Process();
        // ターゲット座標
        auto target = AppMath::Vector4();
        auto prot = AppMath::Vector4();
        _app.GetObjectServer().GetPlayerTransForm(target, prot);
        auto forward = _position.Direction(target);
        // 高さがいらないので分解してy以外を取り出す
        auto [x, y, z] = forward.GetVector3();
        auto efor = AppMath::Vector4(x, 0.0f, z);
        // 正規化
        efor.Normalize();
        _move = efor * (WheelAttackSpead);
        _position.Add(_move);
        _capsule->Process(_move);
      }
      else {
        // アニメーションから指定したボーンのローカル座標を取得
        auto attachIndex = _modelAnim.GetMainAttachIndex();
        auto rPos = MV1GetFramePosition(_mHandle, 13);
        _sphere->SetPosition(UtilityDX::ToVector(rPos));
        _sphere->Process();
        _position.Add(_move);
        _capsule->Process(_move);
      }
      // アニメーション終了でIdleへ移行
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Idle;
        _iMove = false;
      }
    }

    void EnemyWheelBoss::NockBack() {
      if (_cnt > 0) {
        // 自機の取得
        const auto player = _app.GetObjectServer().GetPlayer();
        // ノックバックベクトルを設定
        auto knockBackVector = _position - player.get()->GetPosition();
        // 高さがいらないのでｙ以外を分解して取り出す
        auto [x, y, z] = knockBackVector.GetVector3();
        auto knockBack = AppMath::Vector4(x, 0.0f, z);
        knockBack.Normalize();
        auto kB = knockBack * 10;
        _position.Add(kB);
        _capsule->SetPosition(_position);
      }
      else {
        _enemyState = EnemyState::Idle;
      }
    }

    void EnemyWheelBoss::Sercth() {
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
          _enemyState = EnemyState::AttackReady;
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

    void EnemyWheelBoss::Hit() {
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

    void EnemyWheelBoss::ChangeAnim() {
      // 対応アニメーション切り替え
      switch (_enemyState) {
      case EnemyState::Idle:    //!< 待機
        _modelAnim.SetBlendAttach(IdleKey, 10.0f, 1.0f, true);
        break;
      case EnemyState::Move:    //!< 移動
        _modelAnim.SetBlendAttach(MoveKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::AttackReady:  //!< 攻撃準備
        _modelAnim.SetBlendAttach(AttackReadyKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Attack:  //!< 攻撃
        _modelAnim.SetBlendAttach(AttackKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Damage:  //!< 被ダメ
        _modelAnim.SetBlendAttach(DamageKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Dead:    //!< 死亡
        _modelAnim.SetBlendAttach(DeadKey, 10.0f, 1.0f, false);
        break;
      default:
        break;
      }
    }

    void EnemyWheelBoss::PlayEffect() {
      // パラメータ設定
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
        ePos.AddY(350.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossEyeLight, ePos, eRad);
        break;
      case EnemyState::Attack:  //!< 攻撃
        ePos.AddY(0.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossGroundAttack, ePos, eRad);
        break;
      case EnemyState::Damage:  //!< 被ダメ
        ePos.AddY(100.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossHit, ePos, eRad);
        break;
      case EnemyState::Dead:    //!< 死亡
        ePos.AddY(100.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossExprosion, ePos, eRad);
        break;
      default:
        break;
      }
    }

    void EnemyWheelBoss::Dead() {
      // 状態をPausedにする
      _state = ObjectState::Paused;
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
      // 動的配列に一致する要素があるか判定する
      auto activeBoss = std::any_of(objects.begin(), objects.end(),
        [](std::shared_ptr<Object::ObjectBase>& obj) {
          // 生存状態の敵はいるか
          return (obj->GetId() == Object::ObjectBase::ObjectId::Enemy) && obj->GetState() == ObjectState::Active; });
      // アニメーション終了でDeadへ移行
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _state = ObjectState::Dead;
        // 生存状態の敵がいないか
        if (!activeBoss) {
          // ゲームクリア処理
          _app.SetGameClear(true);
        }
      }
    }

    bool EnemyWheelBoss::IsDamege() {
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
        _gaugeHp->Sub(1000);
        if (_enemyHP <= 0) {
          _enemyState = EnemyState::Dead;
        }
        else {
          _enemyState = EnemyState::Damage;
          _cnt = 20;
        }
        // 衝突フラグがある場合は無敵時間を開始する
        //_invincible->Start();
        return true; // 衝突判定
      }
      return false;  // 衝突なし
    }
  } // namespace Enemy
} // namespace Gyro