/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  �R���W�����x�[�X�̃T�u�N���X
 *         ���̏Փ˔���N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"
#include <Dxlib.h>

namespace Gyro {
  /**
   * @brief 
   */
  namespace Object {
    /**
     * @class CollisionSphere
     * @brief ���̓����蔻��N���X
     */
    class CollisionSphere : public CollisionBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param owner  ���L�҂̎Q��
       * @param center ���S���W
       * @param radius �~�̔��a
       */
      CollisionSphere(ObjectBase& owner, AppMath::Vector4 center, float radius);
      /**
       * @brief �����蔻��̍X�V����
       */
      void Process() override;
      /**
       * @brief �X�V����
       * @param move �ړ���
       */
      void Process(AppMath::Vector4 move) override;
#ifdef _DEBUG
      void Draw() override;
#endif
      /**
       * @brief  �Փ˔���
       * @return 
       */
      bool IsHit() override;
      /**
       * @brief  ���Ƌ��̏Փ˔���
       * @param  sphere �^�[�Q�b�g
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IntersectSphere(const CollisionSphere& sphere);
      /**
       * @brief  ���Ɠ_�̓����蔻��
       * @param  point �_�̍��W
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IntersectPoint(const AppMath::Vector4& point);
    private:
      float _radius{0.0f}; //!< �~�̔��a
    };

  } // namespace Object
} // namespace Gyro