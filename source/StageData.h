/*****************************************************************//**
 * @file   StageData.h
 * @brief  ステージ情報クラス
 * 
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <tuple>
#include <string>
#include <appframe.h>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief ステージ
   */
  namespace Stage {
    namespace AppMath = AppFrame::Math;
    class StageData {
    public:
      /**
       * @brief コンストラクタ
       * @param filename ファイル名
       * @param position 座標
       * @param ratation 回転
       * @param scale    拡大率
       */
      StageData(std::string filename, AppMath::Vector4 position, AppMath::Vector4 rotation, AppMath::Vector4 scale) : 
          _fileName(filename), _position(position), _rotation(rotation), _scale(scale) {
      };
      /**
       * @brief コンストラクタ
       */
      StageData ();
      /**
       * @brief デストラクタ
       */
      ~StageData () = default;
      /**
       * @brief  ファイル情報の取得
       * @return ファイル名
       */
      std::string_view FileName() const {
          return _fileName;
      }
      /**
       * @brief  ステージ情報の取得
       * @return 座標、回転、拡大率
       */
      std::tuple<AppMath::Vector4, AppMath::Vector4, AppMath::Vector4> GetStageParam() const {
          return { _position, _rotation, _scale };
      }
    private:
      std::string _fileName;      //!< ファイル名
      AppMath::Vector4 _position; //!< 座標
      AppMath::Vector4 _rotation; //!< 回転(Debug:デグリー Release:ラジアン)
      AppMath::Vector4 _scale;    //!< 拡大率
    };
  } // Stage
} // Gyro