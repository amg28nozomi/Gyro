/*****************************************************************//**
 * @file   SoundComponent.cpp
 * @brief  サウンドコンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "SoundComponent.h"
#include <DxLib.h>
#include "../Application/ApplicationBase.h"

namespace AppFrame {
  namespace Sound {

    SoundComponent::SoundComponent(Application::ApplicationBase& app) : _app(app) {
    }

    bool SoundComponent::PlayBackGround(std::string_view key) const {
      // 指定した音源ファイルのバックグラウンド再生を行う
      return Play(key, DX_PLAYTYPE_BACK);
    }

    bool SoundComponent::PlayLoop(std::string_view key) const {
      // 指定した音源ファイルのループ再生を行う
      return Play(key, DX_PLAYTYPE_LOOP);
    }

    bool SoundComponent::StopSound(std::string_view key) const {
      // サウンドハンドルを取得
      auto handle = SoundHandle(key);
      if (handle == -1) {
        return false; // 取得失敗
      }
      // サウンドの再生を停止する
      if (StopSoundMem(handle) == -1) {
        return false; // 問題発生
      }
      return true; // 停止成功
    }

    bool SoundComponent::CheckSound(std::string_view key) const {
      // サウンドハンドルの取得
      const auto handle = SoundHandle(key);
      // サウンドハンドルの取得に成功したか
      if (handle == -1) {
        return false; // 失敗
      }
      // 音源が再生中かに応じてフラグを返す
      return (CheckSoundMem(handle) == 1) ? true : false;
    }

    bool SoundComponent::SetVolume(std::string_view key, int volume) const {
      // サウンドハンドルを取得
      auto handle = SoundHandle(key);
      // サウンドハンドルの取得に成功したか
      if (handle == -1) {
        return false; // サウンドハンドルの取得に失敗
      }
      // サウンドの音量を設定する
      if (ChangeVolumeSoundMem(volume, handle) == -1) {
        return false;
      }
      return true;
    }

    bool SoundComponent::Play(std::string_view key, const int type) const {
      // ミュート状態になっていないか
      if (_mute) {
        return false; // 再生を行わない
      }
      // 取得したサウンドハンドルの再生
      if (PlaySoundMem(SoundHandle(key), type, TRUE) == -1) {
        return false; // 再生失敗
      }
      return true; // 再生成功
    }

    const int SoundComponent::SoundHandle(std::string_view key) const {
      // 取得したサウンドハンドルを返す
      return _app.GetSoundServer().GetSoundMem(key);
    }
  } // namespace Sound
} // namespace Gyro