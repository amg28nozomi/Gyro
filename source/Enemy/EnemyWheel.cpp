/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   敵クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#include "EnemyWheel.h"
#include <DxLib.h>
#include "../CollisionSphere.h"
#include "../UtilityDX.h"
#include "../ApplicationMain.h"
#include "../ObjectServer.h"
#include "../Player.h"

namespace {
    // アニメーションキー
    constexpr std::string_view IdleKey = "EnemyIdle";       //!< 待機
    constexpr std::string_view MoveKey = "EnemyMove";       //!< 移動
    constexpr std::string_view AttackKey = "EnemyAttack";   //!< 攻撃
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
          auto[handle, key] = _app.GetModelServer().GetModel("enemy", _number);
          ++_number;
          _mHandle = handle; // ハンドル設定
          _this = key;
          // アニメーションアタッチ
          _modelAnim.SetMainAttach(_mHandle, IdleKey, 1.0f, true);
          _enemyMoveSpeed = 5.0f;
          return true;
        }

        bool EnemyWheel::Process() {
            EnemyState oldEnemyState = _enemyState;
            auto target = AppMath::Vector4();
            auto prot = AppMath::Vector4();
            _app.GetObjectServer().GetPlayerTransForm(target, prot);
            AppMath::Vector4 forword = target - (_position);
            forword.Normalize();
            AppMath::Vector4 move = forword * (_enemyMoveSpeed);
            // _sphere->Process();

                            // ラジアンを生成(z軸は反転させる)
            auto radian = std::atan2(move.GetX(), -move.GetZ());
            // 入力処理がある場合、更新を行う
            if (_app.GetOperation().GetXBoxState().GetButton(XINPUT_BUTTON_LEFT_THUMB, false)) {
              _iMove = !_iMove;
            }

            if (_iMove) {
                _enemyState = EnemyState::WALK;
                _position.Add(move);
                _capsule->Process(move);
#ifndef _DEBUG
                _rotation.SetY(radian); // y軸の回転量をセットする
#else
                // デグリー値をセットする(デバッグ用)
                _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif

        }
            else {
                _enemyState = EnemyState::WAIT;
            }
            Hit();         // 衝突判定
            WorldMatrix(); // ワールド座標の更新
            // ワールド座標の設定
            MV1SetMatrix(_mHandle, UtilityDX::ToMATRIX(_world));

            // アニメーション変更
            if (oldEnemyState != _enemyState) {
                switch (_enemyState) {
                case EnemyState::WAIT:
                    _modelAnim.SetBlendAttach(IdleKey, 10.0f, 1.0f, true);
                    break;
                case EnemyState::WALK:
                    _modelAnim.SetBlendAttach(MoveKey, 10.0f, 1.0f, true);
                    break;
                case EnemyState::ATTACK:
                    _modelAnim.SetBlendAttach(AttackKey, 10.0f, 1.0f, false);
                    break;
                case EnemyState::DEAD:
                    //_modelAnim.SetBlendAttach(1, 10.0f, 1.0f, false);
                    break;
                default:
                    break;
                }
            }

            _modelAnim.Process();
            return true;
        }

        bool EnemyWheel::Draw() const {
          EnemyBase::Draw(); // 基底側の描画を実行
#ifdef _DEBUG
          // デバッグフラグがある場合のみ描画処理を行う
          if (_app.GetDebugFlag()) {
            _capsule->Draw(); // 当たり判定の描画
          }
#endif
          return true; // 描画
        }

        void EnemyWheel::SetCollision() {
          // 球の当たり判定設定
          _sphere = std::make_unique<Object::CollisionSphere>(*this, _position.AddVectorY(100.0f), 50.0f);
          // カプセルコリジョンの設定
          _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 200.0f, 30.0f);
        }

        void EnemyWheel::Hit() {
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

        bool EnemyWheel::IsDamege() {
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
    } // namespace Enemy
} // namespace Gyro