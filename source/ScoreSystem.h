/*****************************************************************//**
 * @file   ScoreSystem.h
 * @brief  スコアデータの制御を行うシステムクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
#include <unordered_map>
#include <vector>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief スコアベース
   */
  namespace Score {
    class ScoreBonus; //!< 前方宣言
    // 連想配列から基礎スコアを取り出すためのキー(文字列)
    constexpr auto LightAttack = "LightAttack"; //!< 弱攻撃(自機)のキー
    constexpr auto HeavyAttack = "HeavyAttack"; //!< 強攻撃(自機)のキー
    constexpr auto ExciteTrick = "ExciteTrick"; //!< エキサイトトリック(自機)のキー
    /**
     * @class ScoreSyatem
     * @brief ゲームスコア用のシステム
     */
    class ScoreSystem {
    public:
      /**
       * @brief コンストラクタ
       */
      ScoreSystem();
      /**
       * @brief  初期化処理
       * @return true
       */
      bool Init(std::vector<ScoreBonus> table = std::vector<ScoreBonus>());
    private:
      //!< スコア倍率テーブル(first:倍率が適応されるコンボ数 second:スコア倍率)
      std::vector<ScoreBonus> _bonusTable{};
      //!< 各種スコアの基準値を管理する連想配列
      std::unordered_map<std::string, float> _scores{};
      /**
       * @brief  各種基礎スコアの設定(標準)
       */
      void SetScores();
      /**
       * @brief  指定したコンボ倍率の取得
       * @param  key 数値
       * @return コンボ倍率
       */
      const float Bonus(std::string_view key) const;
      /**
       * @brief  指定した基礎スコアの取得
       * @param  key 基礎スコアに紐づけられた文字列
       * @return 基礎スコア
       */
      const float BasicScore(std::string_view key) const;
    };
  } // namespace Score
} // namespace Gyro