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

    StageComponent::StageComponent(Application::ApplicationMain& app) {
      // ���\�[�X�̉��
      ReleaseStageInfo();
    }

    StageComponent::~StageComponent() {
      // ���\�[�X�̉��
      ReleaseStageInfo();
      _skySphere.reset();
    }

    bool StageComponent::Init(std::filesystem::path jsonName) {
      // �L�[�����o�^�Ȃ瑱�s
      if (!_stageModelMap.contains(jsonName.generic_string())) {
        // �p�X�̐���
        std::filesystem::path p = "res/Stage";
        const auto jsonPath = (p / jsonName).generic_string() + ".json";
        // json�t�@�C����ǂݎ���p�ŊJ��
        std::ifstream reading(jsonPath, std::ios::in);
#ifdef _DEBUG
        try {
          if (reading.fail()) {
            throw std::logic_error("-----------" + jsonPath + "�t�@�C�����J���܂���ł��� ----------\n");
          }
        }
        catch (const std::logic_error& e) {
          OutputDebugString(e.what());
          return false; // �L�[���s��
        }
#endif
        // �t�@�C�������݂��Ȃ��ꍇ
        if (reading.fail()) {
          return false;
        }
        nlohmann::json value;
        // �t�@�C���̒��g�����o��
        reading >> value;
        // �t�@�C�������
        reading.close();

        // �X�e�[�W�̔z�u�������o��
        for (auto&& stageData : value[jsonName.generic_string()]) {
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

          // filePath�̍쐬
          const auto filePath = (p / fileName).generic_string() + ".mv1";
          namespace AppMath = AppFrame::Math;
          // json�t�@�C��������o�����������W�A��]�A�g�嗦�ɓ����
          auto position = AppMath::Vector4(TargetX, TargetY, TargetZ);
          auto rotation = AppMath::Vector4(RotateX, RotateY, RotateZ);
          auto scale = AppMath::Vector4(ScaleX, ScaleY, ScaleZ);
          StageData stageData = StageData(filePath, position, rotation, scale);
          std::filesystem::path keyName = (jsonName.generic_string());
          LoadStage(keyName.generic_string(), stageData);
        }
        return true;
      }
      return false;
    }

    void StageComponent::LoadStage(std::string_view key, StageData& stageData) {
      // key�̔z�񂪂Ȃ����else
      if (_stageModelMap.contains(key.data())) {
        for (auto& stageModel : _stageModelMap[key.data()]) {
          auto [originalHandle, Data] = stageModel;
          // ���łɓo�^����Ă�����R�s�[�������̂��g��
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
      // �X�e�[�W�l�[��
      _stageName = key;
      auto stageModels = _stageModelMap[key.data()];
      for (auto stageModel : stageModels) {
        auto [handle, stageData] = stageModel;
        auto [position, rotation, scale] = stageData.GetStageParam();
        MV1SetPosition(handle, UtilityDX::ToVECTOR(position));
        // �f�O���[�l�����W�A���l�ɕϊ�
        auto rotX = AppFrame::Math::Utility::DegreeToRadian(rotation.GetX());
        auto rotY = AppFrame::Math::Utility::DegreeToRadian(rotation.GetY());
        auto rotZ = AppFrame::Math::Utility::DegreeToRadian(rotation.GetZ());
        rotation.Set(rotX, rotY, rotZ);
        MV1SetRotationXYZ(handle, UtilityDX::ToVECTOR(rotation));
        MV1SetScale(handle, UtilityDX::ToVECTOR(scale));
        _model.emplace_back(handle);
      }

      return true;
    }

    bool StageComponent::Process() {
      if (_skySphere) {
        _skySphere->Process();
      }
      return true;
    }

    bool StageComponent::Draw() const {
      // ���f���n���h���i�[�R���e�i���񂵂ĕ`�悷��
      for (auto ite : _model) {
        MV1DrawModel(ite);
      }
      if (_skySphere) {
        _skySphere->Draw();
      }
      return true;
    }

    bool StageComponent::ReleaseStageInfo() {
      for (auto& [key, stageModels] : _stageModelMap) {
        for (auto& [handle, stageData] : stageModels) {
          MV1DeleteModel(handle);
        }
        stageModels.clear();
      }
      _stageModelMap.clear();

      return true;
    }

    bool StageComponent::ReleaseModel() {
      // ���f���n���h���i�[�R���e�i���񂵂ĕ`�悷��
      _model.clear();

      return true;
    }

    void StageComponent::AddSky(std::shared_ptr<Object::SkySphere> sky) {
      _skySphere = std::move(sky);
    }
  } // namespace Stage
} // namespace Gyro