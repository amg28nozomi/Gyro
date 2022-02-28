/*****************************************************************//**
 * @file   Matrix44.h
 * @brief  4*4行列クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <array>

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief 算術ベース
   */
  namespace Math {
    class Vector4;
    constexpr auto MaxRow = 4;    //!< 行の上限
    constexpr auto MaxColumn = 4; //!< 列の上限
    /**
     * @class Matrix4x4
     * @brief 4*4行列クラス
     */
    class Matrix44 {
    private:
      /** float型の4*4行列を表す2次元配列 */
      using MatrixArray = std::array<std::array<float, MaxColumn>, MaxRow>;
    public:
      /**
       * @brief 空の行列を生成
       */
      Matrix44();
      /**
       * @brief 行列のコピー
       * @param values 
       */
      Matrix44(const MatrixArray values);
      /**
       * @brief 行列の削除
       */
      ~Matrix44() = default;
      /**
       * @brief  行列の再設定
       * @param  matrix 行列クラスの参照
       * @return 初期化した行列を返す
       */
      static void Reset(MatrixArray& matrix);
      /**
       * @brief
       * @param matrix
       * @return 
       */
      static Matrix44 Identity(const Matrix44& matrix);
      /**
       * @brief  単位行列の作成
       * @return 単位行列
       */
      static Matrix44 Identity();
      /**
       * @brief  平行移動行列の取得
       * @param  x x軸方向ベクトル
       * @param  y y軸方向ベクトル
       * @param  z z軸平行ベクトル
       * @return 平行移動行列
       */
      static Matrix44 Translate(float x, float y, float z);
      /**
       * @brief  ベクトルを平行移動行列に変換する
       * @param  vector 対象ベクトル
       * @return 平行移動行列
       */
      static Matrix44 Translate(const Vector4& vector);
      /**
       * @brief  拡大縮小行列の取得
       * @param  x
       * @param  y
       * @param  z
       * @return 拡大縮小行列
       */
      static Matrix44 Scaling(float x, float y, float z);
      /**
       * @brief  ベクトルを拡大縮小行列に変換する
       * @param  vector ベクトル
       * @return 拡大縮小行列
       */
      static Matrix44 Scaling(const Vector4& vector);
      /**
       * @brief 行列の平行移動
       * @param translate 平行移動ベクトル
       */
      void MulTranslate(const AppFrame::Math::Vector4 translate);
      /**
       * @brief 行列のスケーリング
       * @param scale 拡縮ベクトル
       */
      void MulScaling(const AppFrame::Math::Vector4 scale);
      /**
       * @brief  回転行列(x軸)
       * @param  radian 角度(ラジアン値)
       */
      void RotateX(float angle);
      /**
       * @brief  回転行列(y軸)
       * @param  radian 角度(ラジアン値)
       */
      void RotateY(float radian);
      /**
       * @brief  回転行列(z軸)
       * @param  radian 角度(ラジアン値)
       */
      void RotateZ(float radian);
      /**
       * @brief  行列同士の乗算
       * @return 
       */
      Matrix44 operator* (const Matrix44 rhs) const;
      /**
       * @brief  行列*ベクトルの乗算
       * @param  vector ベクトル
       * @return 
       */
      Vector4 operator* (const Vector4& vector) const;
      /**
       * @brief  指定した行列の値を取得する
       * @param  row 行
       * @param  column 列
       * @return 指定した行列の値
       */
      float GetValue(const int row, const int column) const;
      /**
       * @brief  指定した行列の逆行列を取得する
       * @param  matrix 行列
       * @return 逆行列
       */
      static Matrix44 Inverse(const Matrix44 matrix);
      /**
       * @brief  注視行列の生成
       * @param  position カメラの座標
       * @param  target   対象物の座標
       * @param  up       空ベクトル
       * @return 注視行列
       */
      static Matrix44 CreateLookAt(const Vector4 & position, const Vector4 & target, const Vector4 & up);
    private:
      MatrixArray _rowColumn; //!< 行列
    };
  } // namespace Math
} // namespace AppFrame