/*****************************************************************//**
 * @file   ModeFade.h
 * @brief  モードベースのサブクラス
 *         シーン遷移時のフェード処理を行う
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ModeBase.h"
#include "../Data/Color.h"
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief モードベース
   */
  namespace Mode {
    constexpr auto AlphaMax = 255.0f; //!< アルファ値の上限
    constexpr auto AlphaMin = 0.0f;   //!< アルファ値の下限
    constexpr auto FadeTime = 60.0f;  //!< デフォルトのフェード時間(フレーム)
    constexpr auto AlphaDelta = (AlphaMax / FadeTime); //!< アルファ値の変化量(デフォルト)
    /**
     * @class ModeFade
     * @brief シーン遷移用モード
     *        シーン遷移時のフェード処理を行う
     */
    class ModeFade : public ModeBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       * @param color フェード処理で使用するRGB値
       */
      ModeFade(Application::ApplicationBase& app, const Data::Color color);
      /**
       * @brief デストラクタ
       */
      ~ModeFade() override;
      /**
       * @brief  初期化処理
       * @return true
       */
      bool Init() override;
      /**
       * @brief  入口処理
       * @return true
       */
      virtual bool Enter() override;
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
       * @brief 標準カラーの設定
       * @param color 設定するRGB値
       */
      void SetColor(const Data::Color color);
      /**
       * @brief アルファ値の変化量を設定
       * @param value 0~255までのfloat値
       */
      void SetDeltaAlpha(const float value);
    protected:
      Data::Color _basic; //!< 標準カラー値
      Data::Color _color; //!< フェード処理で使用するRGB値
      int _width;  //!< フェードボックスの横幅
      int _height; //!< フェードボックスの縦幅
      float _alpha{0.0f};      //!< アルファ値
      float _deltaAlpha{0.0f}; //!< アルファ値の変化量
      /**
       * @brief  フェード処理の終了判定
       * @return false
       */
      virtual bool IsFinish();
    };
  } // namespace Mode
} // namespace AppFrame