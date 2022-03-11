/*****************************************************************//**
 * @file   Box.cpp
 * @brief  破壊可能な箱クラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "Box.h"
#include "ApplicationMain.h"
#include "CollisionAABB.h"
#include "SpawnItem.h"
#include "ObjectServer.h"
#include "HealBox.h"
#include "UtilityDX.h"

namespace {
  constexpr auto TotalTime = 0.0f;
  constexpr auto PlayTime = 0.0f;
  constexpr auto DefaultSound = "";
  constexpr auto HealSound = "";
}

namespace Gyro {
  namespace Item {

    Box::Box(Application::ApplicationMain& app) : ObjectBase(app) {
      // デフォルトのサウンドキーをセットする
      _sound = DefaultSound;
    }

    bool Box::Process() {
      // 更新処理
      return ObjectBase::Process();
    }

    void Box::Set(Object::SpawnItem& spawn) {
      // スポーン情報をセットする
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
      // モデルハンドルの取得
      auto [handle, num] = _app.GetModelServer().GetModel(spawn.ModelKey(), _modelNum);
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
      _app.GetObjectServer().Register(heal);
      // 回復SEをセットする
      _sound = HealSound;
    }
  } // namespace Item
} // namespace Gyro