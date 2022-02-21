/*****************************************************************//**
 * @file   StageComponent.cpp
 * @brief  ステージを作成するクラス
 * 
 * @author 土橋峡介
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
      // パスの生成
      std::filesystem::path p = "res/Stage";
      const auto jsonPath = (p / "stage.json").generic_string();
      // jsonファイルを読み取り専用で開く
      std::ifstream reading(jsonPath, std::ios::in);
#ifdef _DEBUG
      try {
        if (reading.fail()) {
          throw std::logic_error("----------- ファイルが開けませんでした ----------\n");
        }
      }
      catch (const std::logic_error& e) {
        OutputDebugString(e.what());
      }
#endif

      nlohmann::json value;
      // ファイルの中身を取り出す
      reading >> value;
      // ファイルを閉じる
      reading.close();

      // ステージの配置情報を取り出す
      for (auto && stageData : value["Stage"]) {
        const auto fileName = stageData["filename"];    // ファイル名
        const auto TargetX = stageData["tx"];           // x座標
        const auto TargetY = stageData["ty"];           // y座標
        const auto TargetZ = stageData["tz"];           // z座標
        const auto RotateX = stageData["rx"];           // x回転
        const auto RotateY = stageData["ry"];           // y回転
        const auto RotateZ = stageData["rz"];           // z回転
        const auto ScaleX = stageData["sx"];            // x拡大値
        const auto ScaleY = stageData["sy"];            // y拡大値
        const auto ScaleZ = stageData["sz"];            // z拡大値

        // SetPositionやSetRotationに読み込んだ情報いれて使う
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
