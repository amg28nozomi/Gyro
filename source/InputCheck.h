/*****************************************************************//**
 * @file   InputCheck.h
 * @brief  ���͔���p���N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>

namespace Gyro {
  namespace Application {
    /**
     * @class InputCheck
     * @brief 
     */
    class InputCheck {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      InputCheck();
      /**
       * @brief �X�V����
       * @param �o�ߎ���
       */
      void Process(float frame);
      /**
       * @brief  �R���X�g���N�^
       * @param  total �����莞��
       * @param  justStart �W���X�g���͂̔���J�n�t���[��
       * @param  justEnd   �W���X�g���͂̔���I���t���[��
       */
      InputCheck(float total, float justStart, float justEnd);
      /**
       * @brief  �����莞�Ԃ̎擾
       * @return �����莞��
       */
      const inline float TotalTime() const {
        return _total;
      }
      /**
       * @brief  �W���X�g����t���[���̎擾
       * @return �W���X�g����t���[��
       */
      const inline float JustFrame() const {
        return _just.second - _just.first;
      }
    protected:
      float _total; //!< �����莞��
      std::pair<float, float> _just; //!< �W���X�g����t���[��(frist:�J�n, second:�I��)
      /**
       * @brief  �W���X�g����t���[���̐ݒ�
       * @param  start �J�n�t���[��
       * @param  end   �I���t���[��
       * @return 
       */
      bool JustTime(float start, float end);
    };
  } // namespace Application
} // namespace Gyro