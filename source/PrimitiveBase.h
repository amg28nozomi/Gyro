/*****************************************************************//**
 * @file   PrimitiveBase.h
 * @brief  �v���~�e�B�u�̃X�[�p�[�N���X
 * 
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <memory>
#include <vector>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
    /**
     * @brief �v���~�e�B�u
     */
    namespace Primitive {
        /**
         * @class Primitive
         * @brief �v���~�e�B�u�̃X�[�p�[�N���X
         */
        class PrimitiveBase {
        public:
            /**
             * @brief �R���X�g���N�^
             */
            PrimitiveBase();

            /**
             * @brief �f�X�g���N�^
             */
            virtual ~PrimitiveBase();

            /**
             * @brief �摜�̃��[�h
             */
            virtual bool Load(const TCHAR* fileName);

            /**
             * @brief �摜�̃��[�h(false���̏���)
             */
            virtual bool UnLoad();

            /**
             * @brief �v���~�e�B�u�̍쐬(�������z�֐�)
             */
            virtual bool Create() = 0;

            /**
             * @brief ����
             */
            virtual void Process();

            /**
             * @brief �`��
             */
            virtual bool Render();

            /**
             * @brief ���_���̎擾
             * @return ���_����Ԃ�
             */
            const std::shared_ptr<std::vector<VERTEX3D>>& GetVertex() const { return _vertex; }

            /**
             * @brief �z��̗v�f���擾
             * @return �z��̗v�f��Ԃ�
             */
            const std::shared_ptr<std::vector<unsigned short>>& GetIndex() const { return _index; }

        protected:
            int _handle;        //!< �摜�n���h��

            std::shared_ptr<std::vector<VERTEX3D>> _vertex;         //!< ���_
            std::shared_ptr<std::vector<unsigned short>> _index;    //!< �v�f
        };
    }// namespace Primitive
}// namespace Gyro
