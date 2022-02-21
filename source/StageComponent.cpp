/*****************************************************************//**
 * @file   StageComponent.cpp
 * @brief  �X�e�[�W���쐬����N���X
 * 
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#include "StageComponent.h"
#include "ApplicationMain.h"
#include "UtilityDX.h"
#include "appframe.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include "UtilityDX.h"
namespace Gyro {
  namespace Stage {

    StageComponent::StageComponent(Application::ApplicationMain& app) : Object::StageBase(app) {
      _stageModelMap.clear();
    }

    bool StageComponent::Init() {
      // �p�X�̐���
      std::filesystem::path p = "res/Stage";
      const auto jsonPath = (p / "stage.json").generic_string();
      // json�t�@�C����ǂݎ���p�ŊJ��
      std::ifstream reading(jsonPath, std::ios::in);
#ifdef _DEBUG
      try {
        if (reading.fail()) {
          throw std::logic_error("----------- �t�@�C�����J���܂���ł��� ----------\n");
        }
      }
      catch (const std::logic_error& e) {
        OutputDebugString(e.what());
      }
#endif

      nlohmann::json value;
      // �t�@�C���̒��g�����o��
      reading >> value;
      // �t�@�C�������
      reading.close();

      // �X�e�[�W�̔z�u�������o��
      for (auto && stageData : value["Stage"]) {
        const auto fileName = stageData["filename"];    // �t�@�C����
        const auto TargetX = stageData["tx"];           // x���W
        const auto TargetY = stageData["ty"];           // y���W
        const auto TargetZ = stageData["tz"];           // z���W
        const auto RotateX = stageData["rx"];           // x��]
        const auto RotateY = stageData["ry"];           // y��]
        const auto RotateZ = stageData["rz"];           // z��]
        const auto ScaleX = stageData["sx"];            // x�g��l
        const auto ScaleY = stageData["sy"];            // y�g��l
        const auto ScaleZ = stageData["sz"];            // z�g��l

        // SetPosition��SetRotation�ɓǂݍ��񂾏�񂢂�Ďg��
        const auto filePath = (p / fileName).generic_string() + ".mv1";
        namespace AppMath = AppFrame::Math;
        auto position = AppMath::Vector4(TargetX, TargetY, TargetZ);
        auto rotation = AppMath::Vector4(RotateX, RotateY, RotateZ);
        auto scale = AppMath::Vector4(ScaleX, ScaleY, ScaleZ);
        StageData stageData = StageData(filePath, position, rotation, scale);
        std::filesystem::path keyName = ("Stage");
        LoadStage(keyName.generic_string(), stageData);
      }
      CreateStage("Stage");

      return true;
    }

    void StageComponent::LoadStage(std::string_view key, StageData& stageData) {
      if (_stageModelMap.contains(key.data())) {
        for (auto& stageModel : _stageModelMap[key.data()]) {
          auto [originalHandle, Data] = stageModel;
          if (stageData.FileName() == Data.FileName()) {
            auto copyHandle = MV1DuplicateModel(originalHandle);
            _stageModelMap[key.data()].emplace_back(copyHandle, stageData);
            return;
          }
          auto fileName = stageData.FileName().data();
          auto handle = MV1LoadModel(fileName);
          _stageModelMap[key.data()].emplace_back(handle, stageData);
          return;
        }
      }else {
        auto filename = stageData.FileName().data();
        auto handle = MV1LoadModel(filename);
        std::vector<std::pair<int, StageData>> stageDatas;
        stageDatas.emplace_back(handle, stageData);
        _stageModelMap.emplace(key, stageDatas);
      }
    }

    bool StageComponent::CreateStage(std::string key) {
      auto stageModels = _stageModelMap[key.data()];
      for (auto stageModel : stageModels) {
        auto [handle, stageData] = stageModel;
        auto [position, rotation, scale] = stageData.GetStageParam();
        MV1SetPosition(handle, UtilityDX::ToVECTOR(position));
        MV1SetRotationXYZ(handle, UtilityDX::ToVECTOR(rotation));
        MV1SetScale(handle, UtilityDX::ToVECTOR(scale));
        _model.emplace_back(handle);
      }
      return true;
    }

    bool StageComponent::Draw() const {
      for (auto ite : _model) {
          if (ite == -1) {
              int i = 0;
        }
        auto f = MV1DrawModel(ite);
        if (f == -1) {
            int i = 0;
        }
      }

      return true;
    }
  } // namespace Stage
} // namespace Gyro
