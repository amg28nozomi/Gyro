/*****************************************************************//**
 * @file   ModelData.h
 * @brief  モデル情報を管理するデータクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
#include <unordered_map>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief モデルベース
   */
  namespace Model {
    class ModelServer;
    constexpr unsigned short Original = 0; // モデルハンドルの登録で使用するキー
    constexpr unsigned short MaxNumber = 65535; // キーの上限
    constexpr auto AnimNull = -1; //!< アニメーション番号該当なし
    /**
     * @class ModelData
     * @brief モデル情報クラス
     */
    class ModelData {
    public:
      /**
       * @brief コンストラクタ
       * @param filePath ファイルパス
       */
      ModelData();
      /**
       * @brief コンストラクタ
       * @param path    ファイルパス
       * @param handles モデルハンドルが格納されたコンテナ
       * @param animes  アニメーション情報が格納された連想配列
       */
      ModelData(std::string_view path, std::unordered_map<unsigned short, int> handles, std::unordered_map<std::string, int> animes);
      /**
       * @brief  モデルハンドルの取得
       * @param  number 通し番号
       * @return first:取得に成功した場合はモデルハンドルを返す 失敗した場合は-1を返す
       *         second:識別番号
       */
      std::pair<int, unsigned short> Handle(unsigned short number);
      /**
       * @brief  指定したアニメーション番号を取得
       * @param  animName アニメーション名
       * @return 取得に成功した場合はアニメーション番号を返す
       *         失敗した場合は-1を返す
       */
      int AnimIndex(std::string_view animName);
      /**
       * @brief  モデルハンドルが格納された連想配列を取得する
       * @return 連想配列の参照
       */
      std::unordered_map<unsigned short, int>& GetHandles() {
        return _handles;
      }
      /**
       * @brief アニメーション情報を削除する
       */
      inline void AnimeClear() {
        _animes.clear(); // アニメーション情報を削除
      }
    private:
      //!< ファイルパス
      std::string _filePath;
      //!< 通し番号をキーとしてモデルハンドルを管理する連想配列
      std::unordered_map<unsigned short, int> _handles;
      //!< アニメーション名をキーとしてアニメーション番号を管理する連想配列
      std::unordered_map<std::string, int> _animes;
    };
  } // namespace Model
} // namespace AppFrame