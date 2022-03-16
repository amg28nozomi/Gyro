/*****************************************************************//**
 * @file   PrimitivePlane.h
 * @brief  �v���~�e�B�u�x�[�X�̃T�u�N���X
 * 
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "PrimitiveBase.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���~�e�B�u
   */
  namespace Primitive {
    /**
     * @brief ��
     */
    class Plane : public PrimitiveBase {
    public:
      /**
       * @brief ��̃R���X�g���N�^
       */
      Plane();
      /**
       * @brief �T�C�Y�w��ł���R���X�g���N�^
       * @param size �T�C�Y
       * @param devisionNum ������
       */
      Plane(float size, int devisionNum);
      /**
       * @brief �f�X�g���N�^
       */
      virtual ~Plane() = default;
      /**
       * @brief ������ �C���X�^���X��ɃZ�b�g�ł���悤�ɂ��Ă���
       * @param size �T�C�Y
       * @param divisionNum ������
       */
      bool Initialize(float size, int divisionNum);
      /**
       * @brief �v���~�e�B�u�̍쐬
       */
      bool Create() override;

    protected:
      float _size;       //!< �T�C�Y
      int _divisionNum;   //!< ���S�̂̃T�C�Y�𕪊�������
    };
  } // namespace Gyro
} // namespace Gyro