/*****************************************************************//**
 * @file   ResourceServer.cpp
 * @brief  2D�f�ނ��Ǘ����郊�\�[�X�T�[�o�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "ResourceServer.h"
#include <DxLib.h>
#include "../Math/Arithmetic.h"

namespace AppFrame{
  namespace Resource {

    ResourceServer::ResourceServer(std::string_view path) : Server::ServerTemplateUnordered<std::string, std::pair<Data::DivGraph, std::vector<int>>>() {
#ifdef _DEBUG
      SetServerName("ResourceServer"); // �T�[�o���̐ݒ�
#endif
      SetDirectryPath(path.data());    // �f�B���N�g���p�X�̐ݒ�
    }

    bool ResourceServer::Release() {
      // �o�^����Ă���摜���̉��
      for (auto&& [key , graphs] : _registry) {
        auto&& [divGraph, handles] = graphs;
        // �O���t�B�b�N�n���h���̍폜
        DeleteGraphs(std::move(handles));
        handles.clear();
      }
      _registry.clear();
      return true;
    }

    bool ResourceServer::LoadDivGraph(std::string_view key, Data::DivGraph divGraph) {
      // �L�[�͓o�^����Ă��邩
      if (_registry.contains(key.data())) {
        // �L�[���d�����Ă���ꍇ�͊����f�[�^���폜
        auto&& [graph, handles] = _registry.at(key.data());
        // �O���t�B�b�N�n���h���̍폜
        DeleteGraphs(std::move(handles));
      }
      namespace fs = std::filesystem;
      // �t�@�C�����̎擾
      auto filePath = FilePath(divGraph.GetFilePath());
      // �Ώۃt�@�C���͑��݂��Ă��邩
      if (!fs::exists(filePath)) {
        return false; // �p�X���L���ł͂Ȃ�
      }
      // �摜���̎擾
      auto [xNum, yNum, allNum] = divGraph.GetNum();
      auto [xSize, ySize] = divGraph.GetSize();
      // �O���t�B�b�N�n���h�����i�[����R���e�i��p��
      std::vector<int> handles;
      handles.resize(allNum);
      // �O���t�B�b�N�n���h���̓ǂݎ��
      if (DxLib::LoadDivGraph(filePath.string().data(), xNum, yNum, allNum, xSize, ySize, handles.data()) == -1) {
        return false; // �ǂݎ��Ɏ��s
      }
      // �f�[�^�x�[�X��ɓo�^����
      _registry.emplace(key.data(), std::make_pair(divGraph, handles));
      return true; // �o�^����
    }

    void ResourceServer::DeleteGraphs(std::vector<int> handles) const {
      for (auto handle : handles) {
        // �O���t�B�b�N�n���h���̍폜
        DeleteGraph(handle);
      }
    }

    Data::DivGraph ResourceServer::GetDivGraph(std::string_view key) const {
      // �L�[�͓o�^����Ă��邩
      if (!UseKey(key.data())) {
        return Data::DivGraph(); // �o�^����Ă��Ȃ��ꍇ�͋����Ԃ�
      }
      // �Ώۂ̉摜����Ԃ�
      return _registry.at(key.data()).first;
    }

    const int ResourceServer::GetHandle(std::string_view key, const int no) const {
      // �L�[�͓o�^����Ă��邩
      if (!UseKey(key.data())) {
        return -1; // ���o�^
      }
      // ���̎擾
      auto [divGraph, handles] = _registry.at(key.data());
      // �ȗ�
      using MathA = Math::Arithmetic;
      // �͈͓��Ɏ��܂��Ă��邩
      if (!MathA::IsRange(no, 0, static_cast<int>(handles.size()) - 1)) {
        return -1; // �n���h���ԍ����͈͊O
      }
      return handles.at(no); // �Ή�����O���t�B�b�N�n���h����Ԃ�
    }

    bool ResourceServer::SetDirectryPath(std::filesystem::path path) {
      // �f�B���N�g���͋�
      if (!_directory.empty()) {
        return true; // �o�^����Ă���
      }
      // �p�X�͗L����
      if (std::filesystem::is_directory(path)) {
        _directory = path;
        return true;
      }
      return false;
    }
  } // namespace Resource
} // namespace AppFrame