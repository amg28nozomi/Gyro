/*****************************************************************//**
 * @file   Box.h
 * @brief  破壊可能な箱情報クラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
#include "CollisionAABB.h"

namespace Gyro {

  namespace Object {
    class SpawnItem;
  }
  namespace Item {
    /**
     * @class Box
     * @brief 箱クラス
     */
    class Box : public Object::ObjectBase {
    public:
      /**
       * @brief ボックスタイプ
       */
      enum class BoxType {
        Normal, // 通常ボックス
        Heal    // 回復ボックス
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      Box(Application::ApplicationMain& app);
      /**
       * @brief
       * @return 
       */
      bool Process() override;

      bool Draw() const override;

      void Set(Object::SpawnItem& spawn);
      /**
       * @brief  モデルカウントの初期化
       */
      static inline void ModelNumReset() {
        _modelNum = 1;
      }

      Object::CollisionAABB GetCollision() const {
        return *_collision;
      }
    protected:
      //!< ボックスタイプ
      BoxType _boxType{BoxType::Normal};
      //!< モデルハンドル
      int _model;
      //!< サウンドキー
      std::string _sound;
      //!< コリジョン情報
      std::unique_ptr<Object::CollisionAABB> _collision{nullptr};
      //!< モデルハンドル用
      static inline unsigned short _modelNum{1};
      /**
       * @brief  破壊処理
       */
      void Break();
      /**
       * @brief  回復フィールドの生成
       */
      void CreateHeal();
      /**
       * @brief
       * @return 
       */
      bool IsDamage();
    };
  } // namespace Item
} // namespace Gyro