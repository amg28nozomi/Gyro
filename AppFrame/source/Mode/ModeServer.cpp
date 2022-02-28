/*****************************************************************//**
 * @file   ModeServer.cpp
 * @brief  �e�탂�[�h���Ǘ�����T�[�o�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "ModeServer.h"
#include "../Application/ApplicationBase.h"
#include "ModeFadeIn.h"
#include "ModeFadeOut.h"

namespace {
  constexpr auto FadeIn = "FadeIn";         // �t�F�[�h�C���o�^�p�̃L�[
  constexpr auto FadeOut = "FadeOut";       // �t�F�[�h�A�E�g�o�^�p�̃L�[
  constexpr auto ServerName = "ModeServer"; // �T�[�o��
} // namespace

namespace AppFrame {
  namespace Mode {

    ModeServer::ModeServer(Application::ApplicationBase& app) : Server::ServerTemplateUnordered<std::string, std::shared_ptr<ModeBase>>() {
#ifdef _DEBUGr
      // �T�[�o���̐ݒ�
      SetServerName(ServerName);
#endif
      // �R���e�i�̏�����
      _registry.clear();
      // �X�^�b�N�̏�����
      _modes.clear();
      // �t�F�[�h�C���̓o�^
      Register(FadeIn, std::make_shared<ModeFadeIn>(app));
      // �t�F�[�h�A�E�g�̓o�^
      Register(FadeOut, std::make_shared<ModeFadeOut>(app));
    }

    ModeServer::ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode) :
     Server::ServerTemplateUnordered<std::string, std::shared_ptr<ModeBase>>(){
#ifdef _DEBUG
      // �T�[�o���̐ݒ�
      SetServerName(ServerName);
#endif
      // �R���e�i�̏�����
      _registry.clear();
      // �X�^�b�N�̏�����
      _modes.clear();
      // �t�F�[�h�C���̓o�^
      Register(FadeIn, std::make_shared<ModeFadeIn>(mode->GetApplication()));
      // �t�F�[�h�A�E�g�̓o�^
      Register(FadeOut, std::make_shared<ModeFadeOut>(mode->GetApplication()));
      // �Ώۃ��[�h�̓o�^
      Register(key.data(), mode);
    }

    bool ModeServer::Release() {
      // �o�^����Ă���S�V�[���̉�����s��
      for (auto mode : _modes) {
        mode->Exit(); // �I�������Ăяo��
      }
      return false;
    }

    void ModeServer::AddMode(std::string_view key, std::shared_ptr<ModeBase> mode) {
      // �f�[�^�x�[�X�Ƀ��[�h��o�^����
      Register(key.data(), mode);
    }

    bool ModeServer::PushBack(std::string_view key) {
      // ���[�h�̎擾
      auto mode = FetchMode(key.data());
      // ���[�h�̎擾�ɐ���������
      if (mode == nullptr) {
#ifdef _DEBUG
        throw LogicError("�ΏۃL�[���s���ł�");
#endif
        return false; // �L�[���s��
      }
      // ���X�g�̖����ɒǉ�
      _modes.push_back(mode);
      return true;
    }

    void ModeServer::PopBuck() {
      // ���[�h�͓o�^����Ă��邩
      if (_modes.empty()) {
        return; // ���[�h�����o�^
      }
      // �I�������Ăяo��
      _modes.back()->Exit();
      // �����̃��[�h���폜����
      _modes.pop_back();
    }

    bool ModeServer::InsertBeforeBack(std::string_view key) {
      // ���[�h�̎擾
      auto mode = FetchMode(key.data());
      // �擾�ɐ���������
      if (mode == nullptr) {
        return false; // �擾���s
      }
      // ���[�h�̓X�^�b�N����Ă��邩
      if (_modes.empty()) {
        // ��̏ꍇ�͖����ɒǉ�����
        _modes.emplace_back(mode);
        return true;
      }
      _modes.insert(std::prev(_modes.end()), mode);
      return true;
    }

    bool ModeServer::Process() {
      // ���[�h�̓X�^�b�N����Ă��邩
      if (_modes.empty()) {
        return true; // ���o�^
      }
#ifndef _DEBUG
      return _modes.back()->Process();
#else
      auto flag = true; // �����t���O
      try {
        flag = _modes.back()->Process();
      } catch (std::logic_error error) {
        OutputDebugString(error.what());
      }
      return flag;
#endif
    }

    bool ModeServer::Draw() const {
      auto flag = true; // �����t���O
      // �X�^�b�N����Ă��郂�[�h�̕`��
      for (auto&& mode : _modes) {
#ifndef _DEBUG
        // �`�揈���͐���I��������
        if (!mode->Draw()) {
          flag = false; // ��蔭��
        }
#else
        try {
          if (!mode->Draw()) {
            flag = false; 
          }
        } catch (std::logic_error error) {
          // ��O�����������ꍇ�̓��O�ɏo��
          DebugString(error.what());
        }
#endif
      }
      return flag;
    }

    bool ModeServer::Register(std::string key, std::shared_ptr<ModeBase> mode) {
      // �L�[�͓o�^���Ă��邩
      if (!Contains(key)) {
        // �d�����Ă���ꍇ�͑Ώۂ��폜
        _registry.erase(key);
      }
      // ���[�h�̏�����
      mode->Init();
      // �f�[�^�x�[�X��ɓo�^����
      _registry.emplace(key, mode);
      return true;
    }

    std::shared_ptr<ModeBase> ModeServer::FetchMode(std::string_view key) {
      // ���[�h�͓o�^����Ă��邩
      if (!Contains(key.data())) {
        return nullptr; // ���o�^
      }
      // �L�[�ɑΉ��������[�h�̎擾
      auto mode = _registry.at(key.data());
      mode->Enter(); // �������������s
      return mode;
    }

    bool ModeServer::TransionToMode(std::string_view key) {
      InsertBeforeBack(key);
      InsertBeforeBack(FadeIn);
      PushBack(FadeOut);
      return true;
    }
  } // namespace Mode
} // namespace AppFrame