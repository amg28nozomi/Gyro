/*****************************************************************//**
 * @file   ServerTemplateVector.h
 * @brief  サーバ用テンプレートクラス(vector)
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ServerBase.h"
#include <vector>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief サーバベース
   */
  namespace Server {
    /**
     * @class ServerTemplateVector
     * @brief 動的配列に対応したサーバテンプレート
     */
    template <typename T>
    class ServerTemplateVector : public ServerBase<std::vector<T>> {
    public:
      /**
       * @brief コンストラクタ
       */
      ServerTemplateVector();
      /**
       * @brief  リソースの解放処理
       * @return 
       */
      virtual bool Release() override;
      /**
       * @brief  デフォルトの登録処理
       * @param  value 登録データ
       * @return true:登録成功 false:登録失敗
       */
      virtual bool Register(T value);
    protected:
    };
    // 定義
    template <typename T>
    ServerTemplateVector<T>::ServerTemplateVector() : ServerBase<std::vector<T>>() {
#ifdef _DEBUG
      // デバッグ時はサーバ名を設定
      ServerBase<std::vector<T>>::_name = "ServerTemplate";
#endif
    }

    template <typename T>
    bool ServerTemplateVector<T>::Release() {
      // 全要素を削除する
      ServerBase<std::vector<T>>::_registry.clear();
      return true;
    }

    template <typename T>
    bool ServerTemplateVector<T>::Register(T value) {
      // 末尾に要素を構築
      ServerBase<std::vector<T>>::_registry.emplace_back(value);
      return true;
    }
  } // namespace Server
} // namespace AppFrame