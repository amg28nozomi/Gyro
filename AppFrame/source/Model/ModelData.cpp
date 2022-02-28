/*****************************************************************//**
 * @file   ModelData.cpp
 * @brief  ���f�����N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ModelData.h"
#include <DxLib.h>
#include <Windows.h>

namespace {
  constexpr short Begine = 0;
  constexpr unsigned short MaxNumber = 65535;
} // namespace

namespace AppFrame {
  namespace Model {

    ModelData::ModelData() {
      // �e��f�[�^�̏�����
      _filePath.clear();
      _handles.clear();
      _animes.clear();
    }

    ModelData::ModelData(std::string_view path, std::unordered_map<unsigned short, int> handles, std::unordered_map<std::string, int> animes) {
      _filePath = path;
      _handles = handles;
      _animes = animes;
    }

    std::pair<int, unsigned short> ModelData::Handle(unsigned short number) {
      // �Ώۂ̒ʂ��ԍ��͓o�^����Ă��邩
      if (_handles.contains(number)) {
        return std::make_pair(_handles.at(number), number); // ���f���n���h����Ԃ�
      }
      // ���o�^�̏ꍇ�̓I���W�i���̃n���h���𕡐�
      auto handle = DxLib::MV1DuplicateModel(_handles.at(Begine));
      // �����ɐ���������
      if (handle == -1) {
#ifdef _DEBUG
        // �n���h�������o�^�̏ꍇ
        if (!_handles.size()) {
          OutputDebugString("�n���h���̕����Ɏ��s���܂����B�Ώۃn���h����NULL�ł�\n");
        }
#endif
        return std::make_pair(-1, MaxNumber); // �������s
      }
      auto no = static_cast<unsigned short>(_handles.size()); // �V�K�ʂ��ԍ�
      // �ʂ��ԍ����L�[�Ƃ��āA�����������f���n���h����o�^����
      _handles.emplace(no, handle);
      return std::make_pair(handle, no);
    }

    int ModelData::AnimIndex(std::string_view animName) {
      // �A�j���[�V�����͓o�^����Ă��邩
      if (!_animes.contains(animName.data())) {
        return AnimNull; // �L�[�����o�^
      }
      // �A�j���[�V�����ԍ���Ԃ�
      return _animes.at(animName.data());
    }
  } // namespace Model
} // namespace 