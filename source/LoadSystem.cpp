/*****************************************************************//**
 * @file   LoadSystem.cpp
 * @brief  �񓯊��ǂݍ��ݏ����N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "LoadSystem.h"

namespace Gyro {
  namespace Application {

    LoadSystem::LoadSystem(ApplicationMain& app) : _app(app) {
      _registry.clear(); // �f�[�^�x�[�X�̍폜
    }

    int LoadSystem::LoadEnd(const int number) const {
      // �L�[���o�^����Ă��邩
      if (!Contents(number)) {
        return LoadError; // ���o�^
      }
      // �����t���O��Ԃ�
      return _registry.at(number);
    }

    bool LoadSystem::Contents(const int number) const {
      return _registry.contains(number);
    }

  } // namespace 
} // namespace Gyro