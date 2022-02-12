#pragma once
#include <appframe.h>

namespace Gyro {
  namespace Player {
    /**
     * @class 
     * @brief 
     */
    class WireComponent {
    public:
      /**
       * @brief �J�n����
       */
      void Start();
      /**
       * @brief �I������
       */
      void Finish();
    protected:
      //!< �^�[�Q�b�g���W
      AppFrame::Math::Vector4 _target{};
      //!< �^�[�Q�b�g�ւ̌���
      AppFrame::Math::Vector4 _forward{};
    };
  } // namespace Player
} // namespace Gyro