/*****************************************************************//**
 * @file   WriteJson.cpp
 * @brief  json�t�@�C���̏������ݏ����N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "WriteJson.h"
#include "FileBase.h"
#include <fstream>
#ifdef _DEBUG
#include <stdexcept>
#endif

namespace AppFrame {
  namespace FileServer {

    std::filesystem::path WriteJson::AddJson(std::filesystem::path jsonName) {
      // �t�@�C���͊��ɐ�������Ă��邩�H
      if (std::filesystem::exists(jsonName)) {
        return jsonName; // �����ς�
      }
      if (jsonName.extension() == ".json") {
        // �g���q��json�łȂ��ꍇ���e��
        throw std::logic_error("WriteJson::AddJson:�Ώۃt�@�C���̊g���q��json�`���ł͂���܂���\n");
        return "";
      }
      // ���݂��Ă��Ȃ��ꍇ��json�t�@�C�����쐬
      std::ofstream jsonFile;
      jsonFile.open(jsonName.filename().string(), std::ios::out);
      jsonFile.close();
      return jsonName;
    }

    bool WriteJson::Save(std::string_view path) {
      std::ofstream jsonFile;
      // �t�@�C�����J��
      jsonFile.open(path.data(), std::ios::out);
      jsonFile.close(); // �t�@�C�������
      return false;
    }
  } // namespace FileServer
} // namespace AppFrame