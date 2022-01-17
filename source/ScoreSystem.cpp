/*****************************************************************//**
 * @file   ScoreSystem.cpp
 * @brief  �X�R�A�f�[�^�̐�����s���V�X�e���N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ScoreSystem.h"
#include "ScoreBonus.h"

namespace {
  // �X�R�A�{���l(�f�t�H���g)
  constexpr auto MagnificationFirst = 1.0f;  // �ŏ��{��
  constexpr auto MagnificationSecond = 1.5f;
  constexpr auto MagnificationThird = 2.0f;
  constexpr auto MagnificationFinal = 2.5f;  // �ő�{��
  // �X�R�A�{�����K�������R���{��(�f�t�H���g)
  constexpr auto ComboFirst = 1;
  constexpr auto ComboSecond = 50;
  constexpr auto ComboThird = 100;
  constexpr auto ComboFinal = 175;
  // �e���b�X�R�A�̃p�����[�^(�W��)
  constexpr auto LightScore = 5.0f;   // ��U��
  constexpr auto HeavyScore = 10.0f;  // ���U��
  constexpr auto ExciteScore = 20.0f; // �G�L�T�C�g�g���b�N
}

namespace Gyro {
  namespace Score {

    ScoreSystem::ScoreSystem() {
      // �e��f�[�^�̏�����
      _bonusTable.clear();
      _scores.clear();
    }

    bool ScoreSystem::Init(std::vector<ScoreBonus> table) {
      // �w�肳�ꂽ�e�[�u�����g�p���邩
      if (!table.empty()) {
        // �Ώۂ̃f�[�^��o�^
        _bonusTable = table;
        return true;
      }
      // �f�t�H���g�̃e�[�u�����쐬����
      std::vector<ScoreBonus> defaultTable {
        { ComboFirst, MagnificationFirst },
        { ComboSecond, MagnificationSecond },
        { ComboThird, MagnificationSecond },
        { ComboFinal, MagnificationFinal },
      };
      // �쐬�����e�[�u����o�^����
      _bonusTable = defaultTable;
      // ��b�X�R�A�e�[�u���̓o�^
      SetScores();
      return true;
    }

    float ScoreSystem::GetComboScore(const int light, const int heavy, const int excite, const int combo) const {
      // �e��X�R�A�f�[�^�̎Z�o
      auto lightScore = light * _scores.at(LightAttack);
      auto heavyScore = heavy * _scores.at(HeavyAttack);
      auto exciteScore = excite * _scores.at(ExciteTrick);
      return (lightScore + heavyScore + exciteScore) * Bonus(combo);
    }

    void ScoreSystem::SetScores() {
      using ScoresMap = std::unordered_map<std::string, float>;
      // ��b�X�R�A�e�[�u���̍쐬
      ScoresMap scores = {
        { LightAttack, LightScore },
        { HeavyAttack, HeavyScore },
        { ExciteTrick, ExciteScore }
      };
      // �W���e�[�u����ݒ�
      _scores = std::move(scores);
    }

    const float ScoreSystem::Bonus(const int combo) const {
      auto value = 0.0f; // �R���{�{��
      for (auto bonus : _bonusTable) {
        // �X�R�A�{�[�i�X�̎擾
        auto [comboRate, score] = bonus.GetScoreBonus();
        // �W�����������ꍇ
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