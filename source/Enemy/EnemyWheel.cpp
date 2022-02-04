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
          auto[handle, key] = _app.GetModelServer().GetModel("enemy", 0);
          _mHandle = handle; // ハンドル設定
          // MV1SetScale(_mHandle, VGet(1.0f, 1.0f, 1.0f));
          // アニメーションアタッチ
          _modelAnim.SetMainAttach(_mHandle, 1, 1.0f, true);
          // 初期化
          //MV1SetScale(_mHandle, VGet(2,2,2));
          _scale = { 2.0f, 2.0f, 2.0f };
          SetEnemyPos(VGet(100, 0, 100));
          _position = UtilityDX::ToVector(_enemyPos);
          auto center = UtilityDX::ToVector(_enemyPos);
          center.AddY(100.0f);
          _sphere = std::make_unique<Object::CollisionSphere>(*this, center, 50.0f);
          _enemyDir = VGet(0, 0, 1);
          _enemyMoveSpeed = 5.0f;
          // カプセルコリジョンの設定
          _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 200.0f, 20.0f);
          return true;
        }

        bool EnemyWheel::Process() {
            EnemyState oldEnemyState = _enemyState;
            AppMath::Vector4 target = AppMath::Vector4();
            AppMath::Vector4 prot = AppMath::Vector4();
            _app.GetObjectServer().GetPlayerTransForm(target, prot);
            AppMath::Vector4 forword = target-(_position);
            forword.Normalize();
            AppMath::Vector4 move = forword*(_enemyMoveSpeed);
            // _sphere->Process();

                            // ラジアンを生成(z軸は反転させる)
            auto radian = std::atan2(move.GetX(), -move.GetZ());

            if (_app.GetOperation().GetXBoxState().GetButton(XINPUT_BUTTON_LEFT_THUMB, true)) {
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

            WorldMatrix(); // ワールド座標の更新
                  // ワールド座標の設定
            MV1SetMatrix(_mHandle, UtilityDX::ToMATRIX(_world));

            // アニメーション変更
            if (oldEnemyState != _enemyState) {
                switch (_enemyState) {
                case EnemyState::WAIT:
                    _modelAnim.SetBlendAttach(1, 10.0f, 1.0f, true);
                    break;
                case EnemyState::WALK:
                    _modelAnim.SetBlendAttach(2, 10.0f, 1.0f, true);
                    _eff.PlayEffect();
                    break;
                case EnemyState::ATTACK:
                    _modelAnim.SetBlendAttach(0, 10.0f, 1.0f, false);
                    break;
                case EnemyState::DEAD:
                    //_modelAnim.SetBlendAttach(1, 10.0f, 1.0f, false);
                    break;
                default:
                    break;
                }
            }

            _modelAnim.Process();
            _eff.SetPosition(_position);
            _eff.SetDirection(radian);
            _eff.Process();
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
    } // namespace Enemy
} // namespace Gyro