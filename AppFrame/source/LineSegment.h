/*****************************************************************//**
 * @file   LineSegment.h
 * @brief  �����N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
#include "Vector4.h"

namespace AppFrame {
  namespace Math {
    /**
     * @class LineSegment
     * @brief �����x�N�g��
     */
    class LineSegment {
    public:
      /**
       * @brief ��̃R���X�g���N�^
       */
      LineSegment();
      /**
       * @brief �R���X�g���N�^
       */
      LineSegment(Vector4 first, Vector4 end);
      /**
       * @brief  �����Ɠ_�̍ŒZ�����̓��̎擾
       * @param  point ���W
       * @return �����Ɠ_�̍ŒZ�����̓��
       */
      float MinDistSq(const Vector4& point) const;
      /**
       * @brief  �����Ɛ����̍ŒZ�����̓����擾
       * @param  line ����
       * @return �����Ɛ����̍ŒZ����(���)
       */
      float MinDistSq(const LineSegment& line) const;
      /**
       * @brief  �����̒������擾
       * @return �����̒���
       */
      float Length() const;
      /**
       * @brief  �����̒����̓����擾
       * @return �����̒����̓��
       */
      float LengthSquared() const;
      /**
       * @brief  �x�N�g���̎擾
       * @return first:��[ second:�I�[
       */
      std::pair<Vector4, Vector4> GetVector() const {
        return std::make_pair(_start, _end);
      }
      /**
       * @brief  ��[�x�N�g���̎擾
       * @return ��[�x�N�g��
       */
      Vector4 GetStart() const {
        return _start;
      }
      /**
       * @brief  �I�[�x�N�g���̎擾
       * @return �I�[�x�N�g��
       */
      Vector4 GetEnd() const {
        return _end;
      }
    private:
      Vector4 _start; //!< ��[�x�N�g��
      Vector4 _end;   //!< �I�[�x�N�g��
    };
  } // namespace Math
} // namespace AppFrame