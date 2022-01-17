/*****************************************************************//**
 * @file   ScoreSystem.h
 * @brief  �X�R�A�f�[�^�̐�����s���V�X�e���N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
#include <unordered_map>
#include <vector>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �X�R�A�x�[�X
   */
  namespace Score {
    class ScoreBonus; //!< �O���錾
    // �A�z�z�񂩂��b�X�R�A�����o�����߂̃L�[(������)
    constexpr auto LightAttack = "LightAttack"; //!< ��U��(���@)�̃L�[
    constexpr auto HeavyAttack = "HeavyAttack"; //!< ���U��(���@)�̃L�[
    constexpr auto ExciteTrick = "ExciteTrick"; //!< �G�L�T�C�g�g���b�N(���@)�̃L�[
    /**
     * @class ScoreSyatem
     * @brief �Q�[���X�R�A�p�̃V�X�e��
     */
    class ScoreSystem {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ScoreSystem();
      /**
       * @brief  ����������
       * @return true
       */
      bool Init(std::vector<ScoreBonus> table = std::vector<ScoreBonus>());
      /**
       * @brief  �R���{�X�R�A�̎Z�o
       * @param  light  ��U���q�b�g�̃q�b�g��
       * @param  heavy  ���U���q�b�g�̃q�b�g��
       * @param  excite �G�L�T�C�g�g���b�N�̃q�b�g��
       * @param  combo  �R���{��
       * @return �R���{�X�R�A
       */
      float GetComboScore(const int light, const int heavy, const int excite, const int combo) const;
    private:
      //!< �X�R�A�{���e�[�u��(first:�{�����K�������R���{�� second:�X�R�A�{��)
      std::vector<ScoreBonus> _bonusTable{};
      //!< �e��X�R�A�̊�l���Ǘ�����A�z�z��
      std::unordered_map<std::string, float> _scores{};
      /**
       * @brief  �e���b�X�R�A�̐ݒ�(�W��)
       */
      void SetScores();
      /**
       * @brief  �w�肵���R���{�{���̎擾
       * @param  combo �R���{��
       * @return �R���{�{��
       */
      const float Bonus(const int combo) const;
      /**
       * @brief  �w�肵����b�X�R�A�̎擾
       * @param  key ��b�X�R�A�ɕR�Â���ꂽ������
       * @return ��b�X�R�A
       */
      const float BasicScore(std::string_view key) const;
    };
  } // namespace Score
} // namespace Gyro