/*****************************************************************//**
 * @file   HealBox.h
 * @brief  回復ボックスクラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"

namespace Gyro {
  /**
   * @brief コリジョンベース
   */
  namespace Object {
    class CollisionCapsule;
    class CollisionAABB;
  } // namespace Collision
  namespace Object {
    /**
     * @class HealBox
     * @brief 回復ボックスクラス
     */
    class HealBox : public ObjectBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      HealBox(Application::ApplicationMain& app);
      /**
       * @brief  座標の設定
       * @param  totalTime 総再生時間
       * @param  speed     再生速度
       * @return 
       */
      bool SetParam(const AppMath::Vector4& position, const float totalTime, const float speed);
      /**
       * @brief 当たり判定の登録
       * @param collision コリジョン情報
       */
      inline void SetCollision(std::unique_ptr<Object::CollisionAABB> collision) {
        _collision = std::move(collision);
      }
      /**
       * @brief  更新処理
       * @return true
       */
      bool Process() override;
      /**
       * @brief  対象が回復判定内に存在するかの判定
       * @return true:存在する false:存在しない
       */
      bool IsInvasion(const CollisionCapsule& capsule) const;
      /**
       * @brief  回復ポイントの取得
       * @return 回復量
       */
      float HealPoint() const {
        return _healPoint;
      }
    private:
      //!< 衝突判定情報
      std::unique_ptr<Object::CollisionAABB> _collision{nullptr};
      //!< 再生速度
      float _speed{0.0f};
      //!< 生存時間
      float _totalTime{0.0f};
      //!< 回復量
      float _healPoint{0.0f};
    };
  } // namespace Object
} // 