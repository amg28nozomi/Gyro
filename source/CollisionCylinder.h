/*****************************************************************//**
 * @file   CollisionCylinder.h
 * @brief  �~���̓����蔻��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"

#ifdef _DEBUG
namespace AppFrame::Data {
  class Color;
}
namespace AppData = AppFrame::Data;
#endif
namespace AppFrame::Math {
  class Vector4;
  class Line;
} // namespace AppFrame::Math

/**
 * @brief Gyro
 */
namespace Gyro {
  /**
   * @brief Object
   */
  namespace Object {

    namespace AppMath = AppFrame::Math;
    /**
     * @class CollisionCylinder
     * @brief �~���̓����蔻��
     */
    class CollisionCylinder : public CollisionBase {
    public:
      /**
       * @brief ��̃R���X�g���N�^
       */
      CollisionCylinder();
      /**
       * @brief �R���X�g���N�^
       * @param pos ���W
       * @param radius �~�̔��a
       * @param line ����
       */
      CollisionCylinder(AppMath::Vector4 pos, float radius, AppMath::Line line);
      /**
       * @brief  �����蔻��̍X�V����
       * @param  pos ���݂̍��W
       */
      void Process(AppMath::Vector4 pos);
      /**
       * @brief  �`�揈��
       */
      void Draw() override;
      /**
       * @brief  ���W�x�N�g���̎擾
       * @return 3�������W()
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  �����̎擾
       * @return �����x�N�g��(2����)
       */
      AppMath::Line GetLine() const {
        return _line;
      }
      /**
       * @brief  ���a�̎擾
       * @return ���a�x�N�g��
       */
      float GetRadius() const {
        return _radius;
      }
      /**
       * @brief  �e��p�����[�^�̎擾
       * @return 0:���W 1:�����̒��� 2:�~�̔��a
       */
      std::tuple<AppMath::Vector4, AppMath::Line, float> GetParameter() const {
        return std::make_tuple(_position, _line, _radius);
      }
#ifdef _DEBUG
      /**
       * @brief �����蔻��̕`��Ŏg�p����J���[�R�[�h�̐ݒ�
       * @param color �g�p����J���[�R�[�h
       */
      void SetColor(AppData::Color color) {
        _color = color;
      }
      /**
       * @brief �`��t���O�̐؂�ւ�
       */
      void ChengeDrawFlag(bool flag) {
        _debug = flag;
      }
#endif
    private:
      AppMath::Vector4 _position; //!< ���W
      AppMath::Line _line; //!< �~���̐���(2d)
      float _radius;       //!< �~�̔��a
#ifdef _DEBUG
      AppData::Color _color; //!< �J�v�Z���`��p�J���[�R�[�h
      bool _debug{false}; //!< Debug�`�攻��t���O
#endif
    };
  } // namespace Object
} // namespace Gyro