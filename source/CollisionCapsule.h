/*****************************************************************//**
 * @file   CollisionCapsule.h
 * @brief  �R���W�����x�[�X�̃T�u�N���X
 *         �J�v�Z���̏Փ˔��菈���N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"

namespace AppFrame::Math {
  class Plane;
}

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class CollisionSphere; //!< �O���錾
    /**
     * @class CollisionCapsule
     * @brief �J�v�Z���̏Փ˔��菈���N���X
     */
    class CollisionCapsule : public CollisionBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param owner ���L�҂̎Q��
       * @param center ���S���W(��)
       * @param line   �����̒���
       * @param radius ���a
       */
      CollisionCapsule(ObjectBase& owner, AppMath::Vector4 center, float line, float radius);
      /**
       * @brief �����蔻��̍X�V����
       */
      void Process(AppMath::Vector4 move) override;
#ifdef _DEBUG
      /**
       * @brief �����蔻��̕`�揈��
       */
      void Draw() override;
#endif
      /**
       * @brief  �J�v�Z���Ɛ����̏Փ˔���
       * @param  line �Փ˔�����s�������̎Q��
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IntersectLine(const AppMath::LineSegment& line);
      /**
       * @brief  �J�v�Z���Ƌ��̏Փ˔���
       * @param  sphere �Փ˔�����s�����R���W����
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IntersectSphere(const CollisionSphere& sphere);
      /**
       * @brief  �J�v�Z���ƃJ�v�Z���̏Փ˔���
       * @param  capsule �Փ˔�����s���J�v�Z���R���W����
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IntersectCapsule(const CollisionCapsule& capsule);
      /**
       * @brief  ���ʂƂ̏Փ˔���(����)
       * @param  plane
       * @return 
       */
      bool IntersectPlane(const AppFrame::Math::Plane& plane);
      /**
       * @brief  ���a�̎擾
       * @return ���a
       */
      float GetRadius() const {
        return _radius;
      }
    private:
      float _length; //!< �����̒���
      float _radius; //!< ���a
      /**
       * @brief  �����̎擾
       * @return ������Ԃ�
       */
      AppMath::LineSegment LineSegment() const;
    };
  } // namespace Object
} // namespace Gyro