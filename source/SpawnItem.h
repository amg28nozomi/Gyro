/*****************************************************************//**
 * @file   SpawnItem.h
 * @brief  アイテムの生成情報クラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "SpawnBase.h"

namespace Gyro {

  namespace Item {
    constexpr auto ItemNormal = 0;
  } // namespace Item

  namespace Object {
    class SpawnItem : public Object::SpawnBase {
    public:
      /**
       * @brief アイテムの種類を表す列挙型クラス
       */
      enum class ItemType {
        Normal, //
        Heal    //
      };
      /**
       * @brief  コンストラクタ
       * @param  key  モデルハンドルに紐づけた文字列
       * @param  type アイテムタイプ
       * @param  position 生成座標
       * @param  rotation 生成時の向き
       * @param  scale    生成時の拡大率
       */
      SpawnItem(std::string_view key, const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale);
      /**
       * @brief  アイテム情報の参照を取得
       * @return 
       */
      SpawnItem& GetInstanceItem() {
        return *this;
      }
      /**
       * @brief アイテムタイプの取得
       */
      ItemType GetItemType() {
        return _itemType;
      }
      /**
       * @brief  モデルキーの取得
       * @return モデルキー
       */
      std::string_view ModelKey() const {
        return _modelKey;
      }
      /**
       * @brief  アイテム番号への変換
       * @return
       */
      int ItemToNumber();
    private:
      //!< アイテムタイプ
      ItemType _itemType;
      //!< モデルキー
      std::string _modelKey;
      /**
       * @brief  
       * @param  type アイテム番号
       */
      void SetItemType(const int type);
    };
  } // namespace Object
} // namespace Gyro