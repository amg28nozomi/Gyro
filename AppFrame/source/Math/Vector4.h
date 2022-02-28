/*****************************************************************//**
 * @file   Vector4.h
 * @brief  四次元ベクトルクラス
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
   * @brief 算術ベース
   */
  namespace Math {

    class Matrix44;
    /**
     * @class Vector4
     * @brief 四次元ベクトル
     */
    class Vector4 {
    public:
      /**
       * @brief 空ベクトルの生成
       */
      Vector4();
      /**
       * @brief 2次元ベクトルの生成
       * @param x x成分
       * @param y y成分
       */
      Vector4(float x, float y);
      /**
       * @brief 型変換処理有り
       * @param x x成分(整数)
       * @param y y成分(整数)
       */
      Vector4(int x, int y);
      /**
       * @brief ベクトルの生成
       * @param x x成分
       * @param y y成分
       * @param z z成分
       * @param w w成分(デフォルトでは1.0)
       */
      Vector4(float x, float y, float z, float w = 1.0);
      /**
       * @brief ゼロベクトル化
       */
      void Zero();
      /**
       * @brief ベクトル同士の加算
       * @param vector ベクトル(加数)
       */
      void Add(const Vector4 vector);
      /**
       * @brief ベクトルの加算
       * @param x x成分
       * @param y y成分
       * @param z z成分
       */
      void Add(const float x, const float y, const float z);
      /**
       * @brief ベクトル同士の減算
       * @param vector ベクトル(減数)
       */
      void Sub(const Vector4 vector);
      /**
       * @brief ベクトルの減算
       * @param x x成分
       * @param y y成分
       * @param z z成分
       */
      void Sub(const float x, const float y, const float z);
      /**
       * @brief ベクトル同士の各成分を乗算する
       * @param vector 対象ベクトル
       */
      void Scale(const Vector4& vector);
      /**
       * @brief  ベクトル同士の各成分を乗算する
       * @param  left  左辺
       * @param  rigth 右辺
       * @return 乗算したベクトル
       */
      static Vector4 Scale(const Vector4& left, const Vector4& right);
      /**
       * @brief ベクトルの設定
       * @param vector セットするベクトル
       */
      void Set(const Vector4 vector);
      /**
       * @brief 指定した値をベクトルにセットする
       * @param x x成分にセットする値
       * @param y y成分にセットする値
       * @param z z成分にセットする値
       */
      void Set(const float x, const float y = 0.0f, const float z = 0.0f);
      /**
       * @brief 指定した値をx成分にセットする
       * @param x
       */
      inline void SetX(const float x) {
        _x = x;
      }
      /**
       * @brief 指定した値をy成分にセットする
       * @param y セットする値
       */
      inline void SetY(const float y) {
        _y = y;
      }
      /**
       * @brief 指定した値をz成分にセットする
       * @param z セットする値
       */
      inline void SetZ(const float z) {
        _z = z;
      }
      /**
       * @brief x成分の加算
       * @param x 加数
       */
      inline void AddX(const float x) {
        _x += x;
      }
      /**
       * @brief  x成分のみを加算したベクトルの取得
       * @param  x x成分に加算する値
       * @return x成分のみを加算したベクトル
       */
      Vector4 AddVectorX(const float x) const;
      /**
       * @brief  y成分のみを加算したベクトルの取得
       * @param  y y成分に加算する値
       * @return y成分のみを加算したベクトル
       */
      Vector4 AddVectorY(const float y) const;
      /**
       * @brief  z成分のみを加算したベクトルの取得
       * @param  z z成分に加算する値
       * @return z成分のみを加算したベクトル
       */
      Vector4 AddVectorZ(const float z) const;
      /**
       * @brief y成分の加算
       * @param x 加数
       */
      inline void AddY(const float y) {
        _y += y;
      }
      /**
       * @brief z成分の加算
       * @param z 加数
       */
      inline void AddZ(const float z) {
        _z += z;
      }
      /**
       * @brief  2次元ベクトルの取得
       * @return xy成分を返す
       */
      inline const std::pair<float, float> GetVector2() const {
        return {_x, _y};
      }
      /**
       * @brief  3次元ベクトルの取得
       * @return xyz成分を返す
       */
      inline const std::tuple<float, float, float> GetVector3() const {
        return {_x, _y, _z};
      }
      /**
       * @brief  4次元ベクトルの取得
       * @return xyzw成分
       */
      inline const std::tuple<float, float, float, float> GetVector4() const {
        return {_x, _y, _z, _w};
      }
      /**
       * @brief  x成分の取得
       * @return x成分
       */
      inline const float GetX() const {
        return _x;
      }
      /**
       * @brief  y成分の取得
       * @return y成分
       */
      inline const float GetY() const {
        return _y;
      }
      /**
       * @brief  z成分の取得
       * @return z成分
       */
      inline const float GetZ() const {
        return _z;
      }
      /**
       * @brief  w成分の取得
       * @return w成分
       */
      inline const float GetW() const {
        return _w;
      }
      /**
       * @brief  ベクトルの長さの取得
       * @return ベクトルの長さ
       */
      float Length() const;
      /**
       * @brief  指定したベクトルの長さを取得
       * @param  vector ベクトル
       * @return 対象ベクトルの長さ
       */
      static float Length(const Vector4& vector);
      /**
       * @brief  ベクトルの長さの取得(2次元)
       * @return ベクトルの長さ
       */
      float Length2D() const;
      /**
       * @brief  ベクトルの長さの二乗の取得
       * @return ベクトルの長さの二乗
       */
      float LengthSquared() const;
      /**
       * @brief  指定したベクトルの長さの二乗を取得
       * @param  vector ベクトル
       * @return 対象ベクトルの長さの二乗
       */
      static float LengthSquared(const Vector4& vector);
      /**
       * @brief  ベクトルの長さの二乗の取得(二次元)
       * @return ベクトルの長さの二乗(二次元)
       */
      float LengthSquared2D() const;
      /**
       * @brief  ベクトルの正規化
       */
      void Normalize();
      /**
       * @brief  単位ベクトルの取得
       * @param  vector ベクトル
       * @return 単位ベクトル
       */
      static Vector4 Normalize(const Vector4& vector);
      /**
       * @brief  ベクトル同士の内積
       * @param  vector ベクトル
       * @return 内積
       */
      float Dot(const Vector4& vecotr) const;
      /**
       * @brief  ベクトル同士の内積
       * @param  left ベクトル(左辺)
       * @param  right ベクトル(右辺)
       * @return 内積
       */
      static float Dot(const Vector4& right, const Vector4& left);
      /**
       * @brief  ベクトルの外積
       * @param  vector ベクトル
       * @return ベクトル
       */
      Vector4 Cross(const Vector4& vector) const;
      /**
       * @brief  ベクトルの外積を求める
       * @param  left  ベクトル
       * @param  right ベクトル
       * @return 外積
       */
      static Vector4 Cross(const Vector4& left, const Vector4& right);
      /**
       * @brief  ベクトル同士が平行かの判定
       * @param  left  ベクトル
       * @param  right ベクトル
       * @return true:平行である false:平行ではない
       */
      static bool IsParallel(const Vector4& left, const Vector4& right);
      /**
       * @brief  指定した値をxyz成分に代入する
       * @param  value 値
       */
      void Fill(const float value);
      /**
       * @brief  対象のベクトルが0かの判定
       * @param  vector ベクトル
       * @return true:ゼロ false:ゼロではない
       */
      static bool NearZero(const Vector4& vector);
      /**
       * @brief  上方向ベクトルの取得
       * @return 上方向ベクトル
       */
      static inline Vector4 Up() {
        return Vector4(0.0f, 1.0f, 0.0f);
      }
      /**
       * @brief  対象へと向かうベクトルの取得
       * @param  vector 対象ベクトル
       * @return 向きベクトル
       */
      Vector4 Direction(const Vector4& vector) const;
      /**
       * @brief  ベクトル同士の加算
       * @param  vector ベクトル(加数)
       * @return 加算した4次元ベクトル
       */
      Vector4 operator + (const Vector4& vector) const;
      /**
       * @brief  ベクトル同士の減算
       * @param  vector ベクトル(減数)
       * @return 減算した4次元ベクトル
       */
      Vector4 operator - (const Vector4& vector) const;
      /**
       * @brief  ベクトルのスカラー倍
       * @param  scalar スカラー値
       * @return スカラー倍した4次元ベクトル
       */
      Vector4 operator * (const float scalar) const;
      /**
       * @brief  ベクトルのスカラー割り
       * @param  scalar スカラー値
       * @return スカラー割りした4次元ベクトル
       */
      Vector4 operator/(const float scalar) const;
    private:
      float _x; //!< x成分
      float _y; //!< y成分
      float _z; //!< z成分
      float _w; //!< w成分
    };
  } // namespace Math
} // namespace AppFrame