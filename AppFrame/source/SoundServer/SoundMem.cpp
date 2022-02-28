/*****************************************************************//**
 * @file   SoundMem.cpp
 * @brief  �����t�@�C�����N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "SoundMem.h"
#include <DxLib.h>

namespace AppFrame {
  namespace Sound {

    SoundMem::SoundMem(std::filesystem::path filePath, const int playType) : FileBase(filePath) {
      _playType = playType;
      _soundHandle = LoadSoundMem(filePath.string().data());
    }
  }
}