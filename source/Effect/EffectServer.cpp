/*****************************************************************//**
 * @file    EffectServer.cpp
 * @brief   エフェクトを管理するサーバクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "EffectServer.h"

namespace Gyro {
    namespace Effect {
        EffectServer::EffectServer() : AppServer::ServerTemplateUnordered<std::string, int>() {
#ifdef _DEBUG
            SetServerName("EffectServer"); // サーバ名の設定
#endif
        }

        bool EffectServer::Release() {
            if (_registry.empty()) {
                return true; // データが空
            }
            // エフェクトハンドルの全開放を行う
            for (auto [key, handle] : _registry) {
                // エフェクトハンドルの解放を行う
                DeleteEffekseerEffect(handle);
            }
            _registry.clear(); // レジストリを解放する
            return true; // 正常終了
        }

        bool EffectServer::AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni) {
            // キーは未使用か
            if (_registry.contains(key.data())) {
                return false; // キーが重複している
            }
            // エフェクト情報の読み取り
            auto handle = LoadEffekseerEffect(effectFile.string().data(), magni);
            // エフェクトハンドルの取得に成功したか
            if (handle == -1) {
                return false; // 読み取り失敗
            }
            // レジストリに登録
            _registry.emplace(key.data(), handle);
            return true;
        }

        void EffectServer::AddEffects(const EffectMap& effectMap, const EffectMagniMap& effectMagniMap) {
            // コンテナの情報を基にデータを読み取る
            for (auto [key, path] : effectMap) {
                for (auto [magniKey, magni] : effectMagniMap) {
                    if (magniKey == key) {
                        AddEffect(key, path, magni);
                    }
                }
            }
        }

        int EffectServer::GetEffectHandle(std::string_view key) const {
            if (!_registry.contains(key.data())) {
                return -1; // キーが有効ではない
            }
            // エフェクトハンドルを返す
            return _registry.at(key.data());
        }
    } // namespace Effect
} // namespace Gyro