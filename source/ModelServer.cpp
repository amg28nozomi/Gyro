#include "ModelServer.h"
#include <DxLib.h>
#include "ApplicationMain.h"


namespace Gyro {
  namespace Model {

    ModelServer::ModelServer(Application::ApplicationMain& app) :
      AppServer::ServerTemplateUnordered<std::string, std::vector<int>>(),
      _app(app)
    {
      _animations.clear();
    }

    bool ModelServer::Release() {
      // �ǂݍ��܂�Ă���S�Ẵ��f���f�[�^�ƃA�j���[�V�������폜����
      for (auto&& [key, handles] : _registry) {
        // ���f���n���h���̍폜
        DeleteHandles(handles);
      }
      _directry.clear();   // �f�B���N�g���p�X���폜
      _animations.clear(); // �A�j���[�V�����̍폜
      return true;
    }

    bool ModelServer::SetDirectryPath(std::string_view directry) {
      namespace fs = std::filesystem;
      // �f�B���N�g���p�X�͐ݒ肳��Ă��Ȃ���
      if (!_directry.empty()) {
        return false; // ���ɓo�^����Ă���
      }
      // �Ώۃf�B���N�g���͑��݂��邩
      if (!fs::is_directory(directry.data())) {
        return false; // ���݂��Ȃ�
      }
      _directry = directry; // �f�B���N�g�p�X��o�^����
      return true;
    }

    bool ModelServer::LoadModel(std::string_view fileName) {
      // �t�@�C���͑��݂��邩
      if (!PathExist(fileName.data())) {
        return false; // ���݂��Ȃ�
      }
      // �L�[���d�����Ă邩�̔���
      if (_registry.contains(fileName.data())) {
        // �o�^����Ă���ꍇ�͊����f�[�^���폜����
        auto&& handles = _registry.at(fileName.data());
        DeleteHandles(handles);    // ���f���n���h�����폜
        _registry.erase(fileName.data()); // �����̗v�f���폜
        _animations.erase(fileName.data()); // �A�j���[�V�������폜
      }
      // ���f���n���h���̓ǂݎ��
      auto handle = ModelServer::MV1LoadModel(fileName.data());
      std::vector<int> handles(handle);
      // �A�j���[�V���������̎擾
      auto animNum = MV1GetAnimNum(handle);
      for (auto no = 0; no < animNum; ++no) {
        // �A�j���[�V�������̎擾
        auto animName = MV1GetAnimName(handle, no);
        // �A�j���[�V�������ƃA�j���ԍ���o�^
        _animations.emplace(animName, no);
      }
      return true;
    }

    const int ModelServer::GetModelHandle(std::string_view key, const int no) {
      // �o�^����Ă���ꍇ�͔�����s��
      if (_registry.contains(key.data())) {
        auto handles = _registry.at(key.data());
      }
      return;
    }

    bool ModelServer::PathExist(std::filesystem::path path) {
#ifndef _DEBUG
      return std::filesystem::exists(_directry / path);
#else
      // �Ώۃt�@�C���͑��݂��邩
      if (!std::filesystem::exists(_directry / path)) {
        // ���݂��Ȃ��ꍇ�̓��O�ɏo��
        DebugString(LogicError((_directry / path).string() + ":�͑��݂��܂���").what());
        return true;
      }
      return true; // ���݂���
#endif
    }

    void ModelServer::DeleteHandles(std::vector<int>& handles) {
      // �S���f���n���h���̍폜���s��
      for (auto&& handle : handles) {
        MV1DeleteModel(handle);
      }
      handles.clear(); // �R���e�i���폜
    }

    int ModelServer::MV1LoadModel(std::filesystem::path path) const {
      return DxLib::MV1LoadModel((_directry / path).string().c_str());
    }
  } // namespace Model
} // namespace Gyro