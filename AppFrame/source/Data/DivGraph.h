/*****************************************************************//**
 * @file   DivGraph.h
 * @brief  �摜�t�@�C���̏��N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../FileServer/FileBase.h"

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �f�[�^�x�[�X
   */
  namespace Data {
    /**
   * @class DivGraph
   * @brief �摜�t�@�C�����
   */
    class DivGraph : public FileServer::FileBase {
    public:
      /**
       * @brief ��̉摜��񐶐�
       */
      DivGraph();
      /**
       * @brief �摜���̐ݒ�
       * @param filePath �t�@�C���̃p�X
       * @param xNum     ��������
       * @param yNum     �c������
       * @param allNum   ��������
       * @param xSize    ������̉摜�T�C�Y(��)
       * @param ySize    ������̉摜�T�C�Y(�c)
       */
      DivGraph(std::filesystem::path filePath, int xNum, int yNum, int allNum, int xSize, int ySize);
      /**
       * @brief  �摜���̉��
       */
      void Clear();
      /**
       * @brief  �������̎擾
       * @return �摜�̕�������Ԃ�(xNum, yNum, allNum)
       */
      inline const std::tuple<int, int, int> GetNum() const {
        return { _xNum, _yNum, _allNum };
      }
      /**
       * @brief  ������̉摜�T�C�Y�̎擾
       * @return �摜�T�C�Y��Ԃ�(xSize, ySize)
       */
      inline const std::pair<int, int> GetSize() const {
        return { _xSize, _ySize };
      }
    private:
      int _xNum;   //!< �c������
      int _yNum;   //!< �c������
      int _allNum; //!< ��������
      int _xSize;  //!< ������̉摜�T�C�Y(��)
      int _ySize;  //!< ������̉摜�T�C�Y(����)
    };
  } // namespace Data
} // namespace AppFrame