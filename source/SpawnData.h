/*****************************************************************//**
 * @file   SpawnData.h
 * @brief  オブジェクト生成時に使用するパラメータクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <tuple>
#include <appframe.h>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    constexpr auto TypePlayer = 0; //!< 自機
    /**
     * @brief Vector4クラスの省略
     */
    using Vector4 = AppFrame::Math::Vector4;
    /**
     * @class SpawanData
     * @brief オブジェクト生成時に使用するパラメータクラス
     */
    class SpawnData {
    public:
      /**
       * @brief オブジェクトの種類を表す
       */
      enum class ObjectType {
        None,   // 無し
        Player, // 自機
      };
      /**
       * @brief コンストラクタ
       */
      SpawnData();
      /**
       * @brief コンストラクタ
       * @param type     オブジェクトタイプ
       * @param position 生成座標
       * @param rotation 生成時の向き
       * @param scale    生成時のスケール
       */
      SpawnData(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale);
      /**
       * @brief  オブジェクト番号をオブジェクトタイプに変換する
       * @param  number オブジェクトタイプ(整数)
       * @return オブジェクトタイプを返す
       */
      const ObjectType NumberToType(const int number) const;
      /**
       * @brief  オブジェクトタイプの取得
       * @return オブジェクトタイプ
       */
      const ObjectType GetType() const {
        return _type;
      }
      /**
       * @brief  座標情報の取得
       * @return 座標
       */
      const Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  向き情報の取得
       * @return 向き
       */
      const Vector4 GetRotation() const {
        return _rotation;
      }
      /**
       * @brief  スケール情報の取得
       * @return スケール
       */
      const Vector4 GetScale() const {
        return _scale;
      }
      /**
       * @brief  トランスフォームの取得
       * @return 0:座標 1:向き 2:スケール
       */
      std::tuple<Vector4, Vector4, Vector4> GetTransform() const {
        return std::make_tuple(_position, _rotation, _scale);
      }
    private:
      ObjectType _type;  //!< オブジェクトタイプ
      Vector4 _position; //!< 生成座標
      Vector4 _rotation; //!< 角度
      Vector4 _scale;    //!< スケール
    };
  } // namespace Object
} // namespace Gyro