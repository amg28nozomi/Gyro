/*****************************************************************//**
 * @file   Box.cpp
 * @brief  破壊可能な箱クラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "Box.h"
#include "ApplicationMain.h"
#include "SpawnItem.h"
#include "ObjectServer.h"
#include "HealBox.h"
#include "UtilityDX.h"
#include "Player.h"
#include "AttackComponent.h"

namespace {
  constexpr auto TotalTime = 600.0f;
  constexpr auto PlayTime = 1.0f;
  constexpr auto DefaultSound = "";
  constexpr auto HealSound = "";
}

namespace Gyro {
  namespace Item {

    Box::Box(Application::ApplicationMain& app) : ObjectBase(app) {
      // デフォルトのサウンドキーをセットする
      _id = ObjectId::Item;
      _sound = DefaultSound;
      _model = 0;
    }

    bool Box::Process() {
      // 更新処理
      ObjectBase::Process();
      return IsDamage();
    }

    bool Box::Draw() const {
      // モデルの描画を行う
      MV1DrawModel(_model);
      return true;
    }

    void Box::Set(Object::SpawnItem& spawn) {
      // スポーン情報をセットする
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
      // コリジョン情報をセットする
      using Vector4 = AppMath::Vector4;
      auto min = _position - Vector4(100.0f, 0.0f, 100.0f);
      auto max = _position + Vector4(100.0f, 100.0f, 100.0f);
      _collision = std::make_unique<Object::CollisionAABB>(*this, min, max);

      // モデルハンドルの取得
      auto [handle, num] = _app.GetModelServer().GetModel(spawn.ModelKey(), 2);
      // モデルハンドルの登録
      _model = handle;
      // モデルカウントを加算
      ++_modelNum;
      // アイテムタイプの設定
      using SpawnItemType = Object::SpawnItem::ItemType;
      switch (spawn.GetItemType()) {
      case SpawnItemType::Normal:
        _boxType = BoxType::Normal;
        break;
      case SpawnItemType::Heal:
        _boxType = BoxType::Heal;
        break;
      }
      // 向き情報を基に角度を算出する
      using Matrix44 = AppMath::Matrix44;
      _world = Matrix44::Identity();
      _world.MulScaling(_scale);
      _world.MulTranslate(_position);
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
    }

    void Box::Break() {
      // 既に箱は破壊されているか
      if (IsDead()) {
        return; // 破壊されている場合は処理を行わない
      }
      // オブジェクトを破壊状態に遷移する
      _state = ObjectState::Dead;
      // 回復フィールドを生成するか
      CreateHeal();
      // SEを再生する
      _app.GetSoundComponent().PlayBackGround(_sound);
    }

    void Box::CreateHeal() {
      // ボックスタイプがヒールではない場合処理を行わない
      if (_boxType != BoxType::Heal) return;
      // ヒールボックスの生成
      auto heal = std::make_shared<Object::HealBox>(_app);
      // パラメータの設定
      heal->SetParam(_position, TotalTime, PlayTime);
      // コリジョン情報の生成
      auto min = _position + AppMath::Vector4(-500.0f, 0.0f, -500.0f);
      auto max = _position + AppMath::Vector4(500.0f, 500.0f, 500.0f);
      auto collision = std::make_unique<Object::CollisionAABB>(*heal, min, max);
      // 生成したコリジョンを登録
      heal->SetCollision(std::move(collision));
      // オブジェクトサーバに登録する
      _app.GetObjectServer().Register(std::move(heal));
      // 回復SEをセットする
      _sound = HealSound;
    }

    bool Box::IsDamage() {
      // ダメージ判定を行う
      auto player = _app.GetObjectServer().GetPlayer();
      auto attack = player->AttackComponent();
      if (attack.GetState() != Object::AttackComponent::AttackState::Active) return false;
      // 当たり判定情報の取得
      auto collision = attack.GetCollisions();

      if (collision.empty()) return false;
      for (auto point : collision) {
        // AABBと球で衝突判定を行う
        if (_collision->CheckSphere(*std::dynamic_pointer_cast<Object::CollisionSphere>(point))) {
          Break(); // 破壊処理に遷移
          return true;
        }
      }
      return false;
    }
  } // namespace Item
} // namespace Gyro