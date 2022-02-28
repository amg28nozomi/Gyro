/*****************************************************************//**
 * @file   GravityBase.h
 * @brief  重力処理を行う静的クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief 算術ベース
   */
  namespace Math {
    class Matrix44; //!< 前方宣言
    constexpr auto DefaultAcceleration = -9.8f; //!< デフォルトの重力加速度
    /**
     * @class GravityBase
     * @brief 重力の基底クラス
     */
    class GravityBase {
    public:
      /**
       * @brief  重力スケールの取得
       * @param  speed 対象の加速度
       * @param  mass  対象の質量
       * @return 対象の重力スケール
       */
      static float GravityScale(float speed, float mass);
      /**
       * @brief  重力加速度の設定
       * @param  scale 設定する加速度
       */
      static void SetScale(const float scale) {
        _acceleration;
      }
      /**
       * @brief  重力加速度の取得
       * @return 重力加速度
       */
      static inline float Acceleration() {
        return _acceleration;
      }
    protected:
      static inline float _acceleration{DefaultAcceleration}; //!< 重力加速度
    };
  } // namespace Math
} // namespace AppFrame