/*****************************************************************//**
 * @file   LoadSystem.cpp
 * @brief  非同期読み込み処理クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "LoadSystem.h"

namespace Gyro {
  namespace Application {

    LoadSystem::LoadSystem(ApplicationMain& app) : _app(app) {
      _registry.clear(); // データベースの削除
    }

    int LoadSystem::LoadEnd(const int number) const {
      // キーが登録されているか
      if (!Contents(number)) {
        return LoadError; // 未登録
      }
      // 処理フラグを返す
      return _registry.at(number);
    }

    bool LoadSystem::Contents(const int number) const {
      return _registry.contains(number);
    }

  } // namespace 
} // namespace Gyro