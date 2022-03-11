/*****************************************************************//**
 * @file   SpawnItem.cpp
 * @brief  アイテムの生成情報クラスの定義
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "SpawnItem.h"

namespace Gyro {
  namespace Object {

    SpawnItem::SpawnItem(std::string_view key, const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale) {
      _type = ObjectType::Item;
      _modelKey = key.data();
      SetItemType(type);
      SetTransForm(position, rotation, scale);
    }

    int SpawnItem::ItemToNumber() {
      switch (_itemType) {
      case ItemType::Normal:
        return 0;
      case ItemType::Heal:
        return 1;
      }
      return -1;
    }

    void SpawnItem::SetItemType(const int type) {
      if (type == 1) {
        _itemType = ItemType::Heal;
        return;
      }
      _itemType = ItemType::Normal;
    }
  } // namespace Object
} // namespace Gyro
