/*****************************************************************//**
 * @file   JsonServer.cpp
 * @brief  json�t�@�C���̓ǂݎ��E�����o�����s���T�[�o�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "JsonServer.h"
#include <fstream>
#ifdef _DEBUG
#include <stdexcept>
#include <Windows.h>
#endif


namespace AppFrame {
  namespace FileServer{

    //JsonServer::JsonServer() : ServerTemplateUnordered<std::string, nlohmann::json>() {
    //  // �R���e�i�̉��
    //  _registry.clear();
    //}

    //bool JsonServer::Release() {

    //}

    //bool JsonServer::SetJsonDirectory(std::string_view key) {
    //  // �f�B���N�g���p�X�̐ݒ�
    //  _directory = key.data();
    //}

//    JsonServer::JsonServer() : ServerBase() {
//      _registry.clear();
//    }
//
//    JsonServer::~JsonServer() {
//    }
//
//    bool JsonServer::Init() {
//      ServerBase::Init();
//      _extension.clear();
//      return true; 
//    }
//
//    bool JsonServer::LoadJsonFile(std::filesystem::path jsonFile) {
//      namespace fs = std::filesystem;
//      if (!fs::exists(jsonFile)) {
//        // json�t�@�C���͑��݂��Ă��Ȃ�
//      }
//    }
//
//    bool JsonServer::Register(std::string_view key, std::filesystem::path jsonFile) {
//#ifndef _DEBUG
//      // �Ώۂ͓o�^�\��
//      if (!IsTarget(key, jsonFile)) {
//        return false;
//      }
//#else
//      try {
//        IsTarget(key, jsonFile);
//      }
//      catch (std::logic_error error) {
//        OutputDebugString(error.what());
//        return false;
//      }
//#endif
//      _registry.emplace(key, jsonFile);
//    }
//
//    bool JsonServer::IsTarget(std::string_view key, std::filesystem::path filePath, std::string_view extension) const {
//      std::string stem;
//      // ������̗L���Ŏg�p����`����؂�ւ���
//      if (extension.empty()) {
//        stem = _extension; // �f�t�H���g�̃t�@�C���`�����g�p
//      }
//      else {
//        stem = extension;  // �����̊g���q���g�p����
//      }
//#ifndef _DEBUG
//
//#else
//      // �t�@�C���`���͑Ή����Ă��邩
//      if (filePath.extension() != stem) {
//        throw std::logic_error("�t�@�C���`��������������܂���\n");
//        return false;
//      }
//      // �`���͂����Ă��邩
//      if (_registry.contains(key.data())) {
//        throw std::logic_error("�L�[���d�����Ă��܂�\n");
//        return false; // �L�[���g�p����Ă��܂�
//      }
//      return true; // �o�^�\
//#endif
//    }
  }
}
