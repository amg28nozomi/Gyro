/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  �R���W�����x�[�X�̃T�u�N���X
 *         ���̓����蔻��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"
#include <Dxlib.h>

namespace Gyro {
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
       * @param vector �ړ���
       */
      void Process(AppMath::Vector4 vector) override;
#ifdef _DEBUG
      void Draw() override;
#endif
      /**
       * @brief  �Փ˔���
       * @return 
       */
      bool IsHit() override;
    private:
      float _radius{0.0f}; //!< �~�̔��a
      /**
       * @brief  ���Ƌ��̏Փ˔���
       * @param  sphere �^�[�Q�b�g
       * @return 
       */
      bool IntersectSphere(const CollisionSphere& sphere);
    };

  } // namespace Object
} // namespace Gyro