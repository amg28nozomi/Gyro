/*****************************************************************//**
 * @file   Singleton.h
 * @brief  シングルトンクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <Windows.h>

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @class Singleton
   * @brief シングルトンクラス
   */
  template<class T>
  class Singleton {
  public:
    /**
     * @brief  対象クラスの参照を取得
     * @return
     */
    static T& GetInstance() {
      return *Singleton<T>::_instance;
    }
    /**
     * @brief  実体の生成
     * @return true:生成成功 false:生成済み
     */
    static bool Create();
    /**
     * @brief  実体の削除
     * @return true:成功 false:実体がない
     */
    static bool Delete();
  protected:
    static inline std::unique_ptr<T> _instance{nullptr}; //!< 実体
    /**
     * @brief 外部でのインスタンス生成は禁止
     */
    Singleton();
    /**
     * @brief デストラクタ
     */
    virtual ~Singleton();
  private:
    /**
     * @brief 代入演算子による作成を禁止する
     */
    void operator=(const Singleton & singleton);
    /**
     * @brief コピーコンストラクタを禁止する
     */
    Singleton(const Singleton& singleton)
  };

  template<class T>
  bool Singleton<T>::Create() {
    // 実体がない場合のみ生成を行う
    if (Singleton<T>::_instance == nullptr) {
      Singleton<T>::_instance = std::make_unique<T>();
      return true; // 実体作成
    }
#ifdef _DEBUG
    OutputDebugString("Singleton:既にインスタンスは生成されています\n");
#endif
    return false;
  }

  template<class T>
  bool Singleton<T>::Delete() {
    // 実体がある場合のみ削除を行う
    if (Singleton<T>::_instance) {
      // 保持しているリソースを解放する
      Singleton<T>::_instance.reset();
      return true;
    }
    return false;
  }

  template<class T>
  Singleton<T>::Singleton() {
  }

  template<class T>
  Singleton<T>::~Singleton() {
  }

  template<class T>
  void Singleton<T>::operator=(const Singleton& singleton) {
  }

  template<class T>
  Singleton<T>::Singleton(const Singleton& singleton) {
  }
} // namespace AppFrame