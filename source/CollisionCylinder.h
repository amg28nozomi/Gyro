/*****************************************************************//**
 * @file   CollisionCylinder.h
 * @brief  円柱の当たり判定クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"

#ifdef _DEBUG
namespace AppFrame::Data {
  class Color;
}
namespace AppData = AppFrame::Data;
#endif
namespace AppFrame::Math {
  class Vector4;
  class Line;
} // namespace AppFrame::Math

/**
 * @brief Gyro
 */
namespace Gyro {
  /**
   * @brief Object
   */
  namespace Object {

    namespace AppMath = AppFrame::Math;
    /**
     * @class CollisionCylinder
     * @brief 円柱の当たり判定
     */
    class CollisionCylinder : public CollisionBase {
    public:
      /**
       * @brief 空のコンストラクタ
       */
      CollisionCylinder();
      /**
       * @brief コンストラクタ
       * @param pos 座標
       * @param radius 円の半径
       * @param line 線分
       */
      CollisionCylinder(AppMath::Vector4 pos, float radius, AppMath::Line line);
      /**
       * @brief  当たり判定の更新処理
       * @param  pos 現在の座標
       */
      void Process(AppMath::Vector4 pos);
      /**
       * @brief  描画処理
       */
      void Draw() override;
      /**
       * @brief  座標ベクトルの取得
       * @return 3次元座標()
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  線分の取得
       * @return 線分ベクトル(2次元)
       */
      AppMath::Line GetLine() const {
        return _line;
      }
      /**
       * @brief  半径の取得
       * @return 半径ベクトル
       */
      float GetRadius() const {
        return _radius;
      }
      /**
       * @brief  各種パラメータの取得
       * @return 0:座標 1:線分の長さ 2:円の半径
       */
      std::tuple<AppMath::Vector4, AppMath::Line, float> GetParameter() const {
        return std::make_tuple(_position, _line, _radius);
      }
#ifdef _DEBUG
      /**
       * @brief 当たり判定の描画で使用するカラーコードの設定
       * @param color 使用するカラーコード
       */
      void SetColor(AppData::Color color) {
        _color = color;
      }
      /**
       * @brief 描画フラグの切り替え
       */
      void ChengeDrawFlag(bool flag) {
        _debug = flag;
      }
#endif
    private:
      AppMath::Vector4 _position; //!< 座標
      AppMath::Line _line; //!< 円柱の線分(2d)
      float _radius;       //!< 円の半径
#ifdef _DEBUG
      AppData::Color _color; //!< カプセル描画用カラーコード
      bool _debug{false}; //!< Debug描画判定フラグ
#endif
    };
  } // namespace Object
} // namespace Gyro