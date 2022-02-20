/*****************************************************************//**
 * @file   ModelAnimData.h
 * @brief  アニメーション情報クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <string>
#include <tuple>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief モデルアニメ
   */
  namespace ModelAnim {
    /**
     * @brief アニメーション情報クラス
     */
    class ModelAnimData {
    public:
      /**
       * @brief  空のコンストラクタ
       */
      ModelAnimData();
      /**
       * @brief  コンストラクタ
       * @param  name  アニメーション名
       * @param  frame ブレンドフレーム
       * @param  speed 再生速度
       * @param  loop  ループフラグ(デフォルトはfalse)
       */
      ModelAnimData(std::string_view name, const float frame, const float speed, bool loop = false);
      /**
       * @brief  アニメーション名の取得
       * @return アニメーション名
       */
      std::string AnimName() const {
        return _name;
      }
      /**
       * @brief  ブレンドフレームの取得
       * @return ブレンドフレーム
       */
      float BlendFrame() const {
        return _blendFrame;
      }
      /**
       * @brief  再生速度の取得
       * @return 再生速度
       */
      float Speed() const {
        return _speed;
      }
      /**
       * @brief  ループフラグの取得
       * @return ループフラグ
       */
      bool Loop() const {
        return _loop;
      }
      /**
       * @brief  アニメーション情報の取得
       * @return アニメーション情報
       */
      std::tuple<std::string, float, float, bool> ModelAnim() const {
        return std::make_tuple(_name, _blendFrame, _speed, _loop);
      }
    protected:
      std::string _name; //!< アニメーション名
      float _blendFrame; //!< ブレンドフレーム
      float _speed;      //!< 再生速度
      bool _loop;        //!< ループフラグ(true:ループする false:ループしない)
    };
  } // namespace ModelAnim
} // namespace Gyro