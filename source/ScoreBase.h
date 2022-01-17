/*****************************************************************//**
 * @file   ScoreBase.h
 * @brief  �Q�[���X�R�A�̊��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �X�R�A�x�[�X
   */
  namespace Score {
    /**
     * @class ScoreBase
     * @brief �X�R�A�x�[�X
     */
    class ScoreBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ScoreBase();
      /**
       * @brief �R���X�g���N�^
       * @param score �X�R�A�|�C���g
       */
      ScoreBase(int score);
      /**
       * @brief �X�R�A�̉��Z����
       * @param value �l
       */
      void Add(float value);
      /**
       * @brief  �X�R�A�|�C���g�̎擾(�����l)
       * @return �����l�ɃL���X�g�����X�R�A�|�C���g
       */
      inline int GetInteger() const {
        return static_cast<int>(_point);
      }
      /**
       * @brief  �X�R�A�|�C���g�̎擾(�P���x���������_��)
       * @return ���̃X�R�A�|�C���g
       */
      inline float GetFloat() const {
        return _point;
      }
      /**
       * @brief  �X�R�A���m�̉��Z����
       * @param  score ���Z����X�R�A
       * @return ���Z�X�R�A
       */
      ScoreBase operator+ (const ScoreBase score);
    protected:
      float _point{0}; //!< �X�R�A�|�C���g
    };
  } // namespace Score
} // namespace Gyro