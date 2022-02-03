/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   敵クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#include "EnemyWheel.h"
#include "../CollisionSphere.h"
#include "../UtilityDX.h"
#include "../ApplicationMain.h"

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
          MV1SetScale(_mHandle, VGet(2,2,2));
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
            VECTOR target = VGet(0, 0, 0);
            VECTOR forword = VSub(target, _enemyPos);
            forword = VNorm(forword);
            VECTOR move = VScale(forword, _enemyMoveSpeed);
            // _sphere->Process();

            if (CheckHitKey(KEY_INPUT_A)) {
                _enemyState = EnemyState::WALK;
                _enemyPos = VAdd(_enemyPos, move);
                _enemyDir = forword;
            }
            else {
                _enemyState = EnemyState::WAIT;
            }

            // アニメーション変更
            if (oldEnemyState != _enemyState) {
                switch (_enemyState) {
                case EnemyState::WAIT:
                    _modelAnim.SetBlendAttach(1, 10.0f, 1.0f, true);
                    break;
                case EnemyState::WALK:
                    _modelAnim.SetBlendAttach(2, 10.0f, 1.0f, true);
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