/*****************************************************************//**
 * @file   ModelServer.cpp
 * @brief  ��������L�[�Ƃ��ă��f�����ƃA�j���[�V�������Ǘ�����T�[�o�N���X�̒�`
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ModelServer.h"
#include <utility>
#include <DxLib.h>
#include "../Math/Arithmetic.h"

namespace AppFrame {
  namespace Model {

    ModelServer::ModelServer() : Server::ServerTemplateUnordered<std::string, ModelData>() {
#ifdef _DEBUG
      SetServerName("ModelServer");
#endif
      Server::ServerTemplateUnordered<std::string, ModelData>::Release();
    }

    bool ModelServer::Init() {
      return Server::ServerTemplateUnordered<std::string, ModelData>::Init();
    }

    bool ModelServer::Release() {
      // �e��R���e�i�̉���������s��
      for (auto&& [key, value] : _registry) {
        DeleteModels(value.GetHandles()); // ���f���n���h�����폜����
        value.AnimeClear(); // �A�j���[�V�������̍폜
      }
      _registry.clear(); // �R���e�i���������
      return true;
    }

    bool ModelServer::AddMV1Model(std::string_view key, std::string_view path) {
      // �L�[���d�����Ă邩�̔���
      if (!UseKey(key.data())) {
        // �L�[���d�����Ă���ꍇ�͊����f�[�^���폜
        auto&& model = _registry.at(key.data());
        DeleteModels(model.GetHandles()); // ���f���n���h�����폜
        model.AnimeClear(); // �A�j���[�V�������폜����
        _registry.erase(key.data()); // �v�f���폜����
      }
      // ���f���n���h���̓ǂݎ��
      auto handle = MV1LoadModel(path.data());
      // ���f���n���h���̎擾�ɐ���������
      if (handle == -1) {
#ifdef _DEBUG
        // ���f���n���h���̓ǂݎ��Ɏ��s�����ꍇ�̓��O�ɏo�͂���
        auto message = static_cast<std::string>(path) + ":mv1�t�@�C���̓ǂݎ��Ɏ��s���܂���\n";
        DebugString(message);
#endif
        return false; // �擾���s
      }
      // ���f���n���h�����i�[����R���e�i
      std::unordered_map<unsigned short, int> handles{ {Original, handle} };
      auto animNum = MV1GetAnimNum(handle); // �A�j���[�V�����ԍ��̎擾
      // �A�j���[�V���������i�[����A�z�z��
      std::unordered_map<std::string, int> animes;
      // �A�j���[�V��������o�^����
      for (auto num = 0; num < animNum; ++num) {
        // �A�j���[�V�������̎擾
        auto animName = MV1GetAnimName(handle, num);
        // �擾�����f�[�^����ɗv�f���\�z
        animes.emplace(animName, num);
      }
      // �ǂݎ�����f�[�^��o�^����
      _registry.emplace(key.data(), ModelData(path, handles, animes));
      return true; // �o�^����
    }

    void ModelServer::AddMV1Model(const ModelDatas& mv1Files) {
      // �R���e�i����������o���o�^���s��
      for (auto [key, path] : mv1Files) {
        AddMV1Model(key, path); // �o�^���s��
      }
    }

    void ModelServer::DeleteModels() {
      Release(); // �S�Ẵ��f���n���h�����폜
    }

    bool ModelServer::DeleteDuplicateModels(std::string_view key, bool flag) {
      // �t���O�������Ă���ꍇ�͑S�v�f�ɏ������s��
      if (flag) {
        for (auto [key, value] : _registry) {
          // �������ꂽ���f���n���h���݂̂��폜
          DeleteDuplicateModels(value.GetHandles());
        }
        return true; // �폜����
      }
      // �v�f�͂��邩
      if (!_registry.contains(key.data())) {
        return false; // ���o�^
      }
      // �������ꂽ���f���n���h���݂̂��폜����
      DeleteDuplicateModels(_registry.at(key.data()).GetHandles());
      return true; // �폜����
    }

    std::pair<int, unsigned short> ModelServer::GetModel(std::string_view key, unsigned short number) {
      // �L�[���o�^����Ă��邩�̔���
      if (!_registry.contains(key.data())) {
        return std::make_pair(-1, MaxNumber); // �L�[�����o�^
      }
      // ���f���n���h����Ԃ�
      return _registry.at(key.data()).Handle(number);
    }

    int ModelServer::GetAnimIndex(std::string_view key, std::string_view animName) {
      // �L�[�͗L����
      if (!_registry.contains(key.data())) {
        return -1; // ���o�^
      }
      // �A�j���[�V�����ԍ���Ԃ�
      return AnimNumber(key, animName);
    }

    void ModelServer::DeleteModels(std::unordered_map<unsigned short, int>& handles) {
      for (auto [number, handle] : handles) {
        MV1DeleteModel(handle); // ���f���n���h�����폜
      }
      handles.clear(); // �R���e�i���������
    }

    void ModelServer::DeleteDuplicateModels(std::unordered_map<unsigned short, int>& handles) {
      // �n���h���͓o�^����Ă��邩
      if (!handles.size()) {
        return; // ���o�^
      }
      // �I���W�i���̃��f���n���h�����R�s�[
      auto original = handles.at(0);
      handles.erase(0); // �I���W�i���n���h�����R���e�i����폜
      // �����������f���n���h�����폜
      for (auto [key, handle] : handles) {
        MV1DeleteModel(handle);
      }
      // �I���W�i���n���h�����ēo�^
      handles.emplace(0, original);
    }

    int ModelServer::AnimNumber(std::string_view key, std::string_view animeName) const {
      auto model = _registry.at(key.data());
      // �w�肵���A�j���[�V�����ԍ���Ԃ�
      return model.AnimIndex(animeName);
    }
  } // namespace Model
} // namespace AppFrame