/*****************************************************************//**
 * @file   ScoreBonus.h
 * @brief  �X�R�A�{���f�[�^
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �X�R�A�x�[�X
   */
  namespace Score {
    /**
     * @class ScoreBonus
     * @brief �X�R�A�{���f�[�^
     */
    class ScoreBonus {
    public:
      /**
       * @brief ��̃R���X�g���N�^
       */
      ScoreBonus();
      /**
       * @brief �R���X�g���N�^
       * @param combo �R���{��(����)
       * @param bouns �X�R�A�{��
       */
      ScoreBonus(unsigned int combo, const float bouns);
      /**
       * @brief  �R���{���̎擾
       * @return �R���{��
       */
      inline int GetCombo() const {
        return _combo;
      }
      /**
       * @brief  �X�R�A�{���̎擾
       * @return �X�R�A�{��
       */
      inline float GetBouns() const {
        return _bonus;
      }
      /**
       * @brief  �S�f�[�^�̎擾
       * @return first:�R���{�� second:�X�R�A�{��
       */
      inline std::pair<int, float> GetScoreBonus() const {
        return { _combo, _bonus };
      }
    private:
      int _combo{0};      //!< �{�����K�������R���{��
      float _bonus{1.0f}; //!< �X�R�A�{��
    };
  } // namespace Score
} // namespace Gyro