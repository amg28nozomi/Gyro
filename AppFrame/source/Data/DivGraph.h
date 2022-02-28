/*****************************************************************//**
 * @file   DivGraph.h
 * @brief  画像ファイルの情報クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../FileServer/FileBase.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief データベース
   */
  namespace Data {
    /**
   * @class DivGraph
   * @brief 画像ファイル情報
   */
    class DivGraph : public FileServer::FileBase {
    public:
      /**
       * @brief 空の画像情報生成
       */
      DivGraph();
      /**
       * @brief 画像情報の設定
       * @param filePath ファイルのパス
       * @param xNum     横分割数
       * @param yNum     縦分割数
       * @param allNum   総分割数
       * @param xSize    分割後の画像サイズ(横)
       * @param ySize    分割後の画像サイズ(縦)
       */
      DivGraph(std::filesystem::path filePath, int xNum, int yNum, int allNum, int xSize, int ySize);
      /**
       * @brief  画像情報の解放
       */
      void Clear();
      /**
       * @brief  分割情報の取得
       * @return 画像の分割数を返す(xNum, yNum, allNum)
       */
      inline const std::tuple<int, int, int> GetNum() const {
        return { _xNum, _yNum, _allNum };
      }
      /**
       * @brief  分割後の画像サイズの取得
       * @return 画像サイズを返す(xSize, ySize)
       */
      inline const std::pair<int, int> GetSize() const {
        return { _xSize, _ySize };
      }
    private:
      int _xNum;   //!< 縦分割数
      int _yNum;   //!< 縦分割数
      int _allNum; //!< 総分割数
      int _xSize;  //!< 分割後の画像サイズ(幅)
      int _ySize;  //!< 分割後の画像サイズ(高さ)
    };
  } // namespace Data
} // namespace AppFrame