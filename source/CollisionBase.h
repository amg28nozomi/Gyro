/*****************************************************************//**
 * @file   CollisionBase.h
 * @brief  �����蔻��p���̊��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once

namespace AppFrame::Math {
  class Vector4;
}

 /**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    /**
     * @class CollisionBase
     * @brief �����蔻����
     */
    class CollisionBase {
    public:
      /**
       * @brief �����蔻��̊��N���X
       */
      CollisionBase();
      /**
       * @brief �����蔻��̍X�V
       */
      virtual void Process();
      /**
       * @brief �����蔻��̕`��
       */
      virtual void Draw();
    protected:
    };
  } // namespace Object
} // namespace Gyro