/*****************************************************************//**
 * @file   Utility.h
 * @brief  算術処理用の補助機能クラス
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <numbers>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief 算術処理ベース
   */
  namespace Math {
    class Vector4;  // 前方宣言
    class Matrix44; // 前方宣言
    constexpr auto Degree = true;  //!< デグリーフラグ
    constexpr auto Radian = false; //!< ラジアンフラグ
    /**
     * @class Utility
     * @brief 算術処理用の補助機能をまとめたクラス
     */
    class Utility {
    public:
      //!< 円周率PIの定数
      static constexpr float _pi{ static_cast<float>(std::numbers::pi) };
      //!< 
      static constexpr float _degrees180{ 180.0f };
      /**
       * @brief  二つの値を比較して最小値を返す
       * @tparam T 比較するデータの型
       * @param  a 引数1
       * @param  b 引数2
       * @return 最小値
       */
      template <typename T>
      static T Min(const T a, const T b);
      /**
       * @brief  二つの値を比較して最大値を返す
       * @tparam T 比較するデータの型
       * @param  a 引数1
       * @param  b 引数2
       * @return   最大値
       */
      template <typename T>
      static T Max(const T a, const T b);
      /**
       * @brief  ワールド座標変換
       * @param  position ローカル座標
       * @param  rotatin  回転ベクトル
       * @param  scale    スケール
       * @param  angle    ローテーションフラグ(true:デグリー値 false:ラジアン値)
       * @return ワールド座標
       */
      static Matrix44 ToWorldMatrix(const Vector4& position, Vector4 rotation, const Vector4& scale , const bool angle = Radian);
      /**
       * @brief  対象の値を正数に変換する
       * @param  value 変換対象
       * @return 引数を正数に変換した値
       */
      static float ToPlus(float value);
      /**
       * @brief  デグリー値をラジアン値に変換する
       * @param  degree デグリー値
       * @return ラジアン値
       */
      static inline float DegreeToRadian(float degree) {
        return degree * _pi / _degrees180;
      }
      /**
       * @brief  ラジアン値をデグリー値に変換する
       * @param  radian ラジアン値
       * @return デグリー値
       */
      static inline float RadianToDegree(float radian) {
        return radian * _degrees180 / _pi;
      }
      /**
       * @brief  回転ベクトル(デグリー値)の各成分をラジアン値に変換する
       * @param  rotation 回転ベクトル(デグリー値)
       * @return 各成分をラジアン値に変換したベクトルを返す
       */
      static Vector4 RotationToRadian(const Vector4& rotation);
    };
  } // namespace Math
} // namespace AppFrame