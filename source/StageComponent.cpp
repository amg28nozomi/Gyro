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

    StageComponent::StageComponent(Application::ApplicationMain& app) {
      // リソースの解放
      ReleaseStageInfo();
    }

    StageComponent::~StageComponent() {
      // リソースの解放
      ReleaseStageInfo();
      _skySphere.reset();
    }

    bool StageComponent::Init(std::filesystem::path jsonName) {
      // キーが未登録なら続行
      if (!_stageModelMap.contains(jsonName.generic_string())) {
        // パスの生成
        std::filesystem::path p = "res/Stage";
        const auto jsonPath = (p / jsonName).generic_string() + ".json";
        // jsonファイルを読み取り専用で開く
        std::ifstream reading(jsonPath, std::ios::in);
#ifdef _DEBUG
        try {
          if (reading.fail()) {
            throw std::logic_error("-----------" + jsonPath + "ファイルが開けませんでした ----------\n");
          }
        }
        catch (const std::logic_error& e) {
          OutputDebugString(e.what());
          return false; // キーが不正
        }
#endif
        // ファイルが存在しない場合
        if (reading.fail()) {
          return false;
        }
        nlohmann::json value;
        // ファイルの中身を取り出す
        reading >> value;
        // ファイルを閉じる
        reading.close();

        // ステージの配置情報を取り出す
        for (auto&& stageData : value[jsonName.generic_string()]) {
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

          // filePathの作成
          const auto filePath = (p / fileName).generic_string() + ".mv1";
          namespace AppMath = AppFrame::Math;
          // jsonファイルから取り出した情報を座標、回転、拡大率に入れる
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
      // keyの配列がなければelse
      if (_stageModelMap.contains(key.data())) {
        for (auto& stageModel : _stageModelMap[key.data()]) {
          auto [originalHandle, Data] = stageModel;
          // すでに登録されていたらコピーしたものを使う
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
      // ステージネーム
      _stageName = key;
      auto stageModels = _stageModelMap[key.data()];
      for (auto stageModel : stageModels) {
        auto [handle, stageData] = stageModel;
        auto [position, rotation, scale] = stageData.GetStageParam();
        MV1SetPosition(handle, UtilityDX::ToVECTOR(position));
        // デグリー値をラジアン値に変換
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
      // モデルハンドル格納コンテナを回して描画する
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
      // モデルハンドル格納コンテナを回して描画する
      _model.clear();

      return true;
    }

    void StageComponent::AddSky(std::shared_ptr<Object::SkySphere> sky) {
      _skySphere = std::move(sky);
    }
  } // namespace Stage
} // namespace Gyro