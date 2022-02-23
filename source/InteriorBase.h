/*****************************************************************//**
 * @file   InteriorBase.h
 * @brief  インテリアの基底クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
#include <memory>
#include "CollisionBase.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class SpawnBase;
  } // namespace Object
  /**
   * @brief インテリアベース
   */
  namespace Interior {
    /**
     * @class  InteriorBase
     * @brief  インテリアの基底クラス
     */
    class InteriorBase : public Object::ObjectBase {
    public:
      /**
       * @brief インテリアの種類を表す列挙型クラス
       */
      enum class InteriorType {
        None,  // 該当なし
        Box,   // 箱
      };
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      InteriorBase(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~InteriorBase() = default;
      /**
       * @brief  初期化処理
       * @return true
       */
      virtual bool Init() override;
      /**
       * @brief  更新処理
       * @return true
       */
      virtual bool Process() override;
      /**
       * @brief  描画処理
       * @return true
       */
      virtual bool Draw() const override;
      /**
       * @brief  設定処理
       * @param  spawn スポーン情報
       */
      virtual void Set(Object::SpawnBase& spawn) override;
      /**
       * @brief  インテリアタイプの取得
       * @return インテリアタイプ
       */
      InteriorType GetInteriorType() const {
        return _interior;
      }
    protected:
      //!< インテリアの種類
      InteriorType _interior{InteriorType::None};
      //!< 当たり判定情報
      std::unique_ptr<Object::CollisionBase> _collision{nullptr};
    };
  } // namespace Interior
} // namespace Gyro