/*****************************************************************//**
 * @file   DivGraph.cpp
 * @brief  �摜�t�@�C���̏��N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "DivGraph.h"

namespace AppFrame {

  namespace Data {
    DivGraph::DivGraph() : FileBase() {
      Clear();
    }

    DivGraph::DivGraph(std::filesystem::path filePath, int xNum, int yNum, int allNum, int xSize, int ySize) : FileBase(filePath) {
      _xNum = xNum;
      _yNum = yNum;
      _allNum = allNum;
      _xSize = xSize;
      _ySize = ySize;
    }

    void DivGraph::Clear() {
      _path.clear();
      _xNum = 0;
      _yNum = 0;
      _allNum = 0;
      _xSize = 0;
      _ySize = 0;
    }
  } // namespace Data
} // namespace AppFrame