/*****************************************************************//**
 * @file   ScoreSystem.cpp
 * @brief  スコアデータの制御を行うシステムクラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ScoreSystem.h"
#include "ScoreBonus.h"

namespace {
  // スコア倍率値(デフォルト)
  constexpr auto MagnificationFirst = 1.0f;  // 最小倍率
  constexpr auto MagnificationSecond = 1.5f;
  constexpr auto MagnificationThird = 2.0f;
  constexpr auto MagnificationFinal = 2.5f;  // 最大倍率
  // スコア倍率が適応されるコンボ数(デフォルト)
  constexpr auto ComboFirst = 1;
  constexpr auto ComboSecond = 50;
  constexpr auto ComboThird = 100;
  constexpr auto ComboFinal = 175;
  // 各種基礎スコアのパラメータ(標準)
  constexpr auto LightScore = 5.0f;   // 弱攻撃
  constexpr auto HeavyScore = 10.0f;  // 強攻撃
  constexpr auto ExciteScore = 20.0f; // エキサイトトリック
}

namespace Gyro {
  namespace Score {

    ScoreSystem::ScoreSystem() {
      // 各種データの初期化
      _bonusTable.clear();
      _scores.clear();
    }

    bool ScoreSystem::Init(std::vector<ScoreBonus> table) {
      // 指定されたテーブルを使用するか
      if (!table.empty()) {
        // 対象のデータを登録
        _bonusTable = table;
        return true;
      }
      // デフォルトのテーブルを作成する
      std::vector<ScoreBonus> defaultTable {
        { ComboFirst, MagnificationFirst },
        { ComboSecond, MagnificationSecond },
        { ComboThird, MagnificationSecond },
        { ComboFinal, MagnificationFinal },
      };
      // 作成したテーブルを登録する
      _bonusTable = defaultTable;
      // 基礎スコアテーブルの登録
      SetScores();
      return true;
    }

    float ScoreSystem::GetComboScore(const int light, const int heavy, const int excite, const int combo) const {
      // 各種スコアデータの算出
      auto lightScore = light * _scores.at(LightAttack);
      auto heavyScore = heavy * _scores.at(HeavyAttack);
      auto exciteScore = excite * _scores.at(ExciteTrick);
      return (lightScore + heavyScore + exciteScore) * Bonus(combo);
    }

    void ScoreSystem::SetScores() {
      using ScoresMap = std::unordered_map<std::string, float>;
      // 基礎スコアテーブルの作成
      ScoresMap scores = {
        { LightAttack, LightScore },
        { HeavyAttack, HeavyScore },
        { ExciteTrick, ExciteScore }
      };
      // 標準テーブルを設定
      _scores = std::move(scores);
    }

    const float ScoreSystem::Bonus(const int combo) const {
      auto value = 0.0f; // コンボ倍率
      for (auto bonus : _bonusTable) {
        // スコアボーナスの取得
        auto [comboRate, score] = bonus.GetScoreBonus();
        // 標準を上回った場合
        if (comboRate <= score) {
          value = score;
        }
      }
      return value;
    }
    
    const float ScoreSystem::BasicScore(std::string_view key) const {
      return _scores.at(key.data());
    }
  } // namespace Score
} // namespace Gyro