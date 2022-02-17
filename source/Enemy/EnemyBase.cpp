/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   敵の基底クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../ApplicationMain.h"
#include "../SpawnEnemy.h"
#include "../UtilityDX.h"
#include "../Player.h"
#include "../ObjectServer.h"

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
            _mHandle = -1;
            _enemyMoveSpeed = 0.0f;
            _id = ObjectId::Enemy;
            _enemyState = EnemyState::Idle;
            return true;
        }

        bool EnemyBase::Process() {
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

        void EnemyBase::SetCollision() {
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
          // 
          const auto player = _app.GetObjectServer().GetPlayer();
          // 地形(床)と線分の衝突判定
          auto hit = MV1CollCheck_Line(player->StageHandle(), 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
          // 衝突フラグがない場合
          if (hit.HitFlag == 0) {
            // 新しい座標をセット
            _position = newPos;
            // コリジョン情報に更新をかける
            _capsule->SetPosition(_position);
            return false; // 床に立っていない
          }
          // 衝突座標を座標に代入
          _position = UtilityDX::ToVector(hit.HitPosition);
          // 新しい座標をコリジョンに反映
          _capsule->SetPosition(_position);
          return true; // 床に立っている
        }

        void EnemyBase::Dead() {
          _state = ObjectState::Dead;
          // オブジェクトサーバに死亡処理を行う
          // _app.GetObjectServer().
        }
    } // namespace Enemy
} // namespace Gyro