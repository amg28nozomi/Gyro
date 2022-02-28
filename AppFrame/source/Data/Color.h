/*****************************************************************//**
 * @file   Color.h
 * @brief  RGBAカラーモデルクラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <tuple>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief データベース
   */
  namespace Data {
    constexpr auto MaxColor = 255; //!< 色の上限
    constexpr auto MinColor = 0;   //!< 色の下限
    /**
     * @class Color
     * @brief RGBAカラー情報
     */
    class Color {
    public:
      /**
       * @brief RGBAカラー情報の設定
       */
      Color();
      /**
       * @brief RGBAカラー情報の生成
       * @param red   赤
       * @param green 緑
       * @param blue  愛
       * @param alpha 透過度(デフォルトでは255)
       */
      Color(const int red, const int green, const int blue, const int alpha = MaxColor);
      /**
       * @brief カラー情報の設定
       * @param red   輝度(赤)
       * @param green 輝度(緑)
       * @param blue  輝度(青)
       * @param alpha 透明度(デフォルトでは255)
       */
      void SetColor(const int red, const int green, const int blue, const int alpha = MaxColor);
      /**
       * @brief 透明度の設定
       * @param alpha 透明度
       */
      void SetAlpha(const int alpha);
      /**
       * @brief 輝度の加算処理
       * @param red   赤
       * @param green 緑
       * @param blue  青
       */
      void AddColor(const int red = MinColor, const int green = MinColor, const int blue = MinColor);
      /**
       * @brief α値の加算
       * @param add 加数
       */
      void AddAlpha(const int add);
      /**
       * @brief 輝度の減算処理
       * @param red   赤
       * @param green 緑
       * @param blue  青
       */
      void SubColor(const int red = MinColor, const int green = MinColor, const int blue = MinColor);
      /**
       * @brief 透明度の減算処理
       * @param sub 減数
       */
      void SubAlpha(const int sub);
      /**
       * @brief  カラーコードの取得
       * @param  red   輝度(赤)
       * @param  green 輝度(緑)
       * @param  blue  輝度(青)
       * @return カラーコード
       */
      static int GetColor(const int red, const int green, const int blue);
      /**
       * @brief  各輝度の取得
       * @return RGB値
       */
      inline const std::tuple<int, int, int> GetLuminace() const {
        return std::make_tuple(_red, _green, _blue);
      }
      /**
       * @brief  RGBA値の取得
       * @return 各輝度と透明度
       */
      inline const std::tuple<int, int, int, int> GetRgba() const {
        return std::make_tuple(_red, _green, _blue, _alpha);
      }
      /**
       * @brief  輝度値(赤)の取得
       * @return 赤の輝度値
       */
      inline const int GetRed() const {
        return _red;
      }
      /**
       * @brief  輝度値(緑)の取得
       * @return 緑の輝度値
       */
      inline const int GetGreen() const {
        return _green;
      }
      /**
       * @brief  輝度値(青)の取得
       * @return 青の輝度値
       */
      inline const int GetBlue() const {
        return _blue;
      }
      /**
       * @brief  アルファ値の取得
       * @return アルファ値
       */
      inline const int GetAlpha() const {
        return _alpha;
      }
      /**
       * @brief  カラーコードの取得
       * @return カラーコ―ド
       */
      inline const int GetColorCode() const {
        return _code;
      }
      /**
       * @brief  +演算子でのカラー情報同士の加算処理
       * @param  color カラー情報(加数)
       * @return 加算したカラー情報
       */
      Color operator +(const Color color) const;
      /**
       * @brief  -演算子でのカラー情報同士の減算処理
       * @param  color カラー情報(減数)
       * @return 減算したカラー情報
       */
      Color operator -(const Color color) const;
    private:
      int _red;   //!< 輝度値(赤)
      int _green; //!< 輝度値(緑)
      int _blue;  //!< 輝度値(青)
      int _alpha; //!< 透明度
      int _code;  //!< カラーコード
      /**
       * @brief RGBA値のクランプ処理
       * @param red   輝度(赤)
       * @param green 輝度(緑)
       * @param blue  輝度(青)
       * @param alpha 透明度(デフォルトでは255)
       */
      void Clamp(const int red, const int green, const int blue, const int alpha = MaxColor);
    };
  } // namespace Data
} // namespace AppFrame