/*****************************************************************//**
 * @file   ModelData.cpp
 * @brief  モデル情報クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModelData.h"
#include <DxLib.h>
#include <Windows.h>

namespace {
  constexpr short Begine = 0;
  constexpr unsigned short MaxNumber = 65535;
} // namespace

namespace AppFrame {
  namespace Model {

    ModelData::ModelData() {
      // 各種データの初期化
      _filePath.clear();
      _handles.clear();
      _animes.clear();
    }

    ModelData::ModelData(std::string_view path, std::unordered_map<unsigned short, int> handles, std::unordered_map<std::string, int> animes) {
      _filePath = path;
      _handles = handles;
      _animes = animes;
    }

    std::pair<int, unsigned short> ModelData::Handle(unsigned short number) {
      // 対象の通し番号は登録されているか
      if (_handles.contains(number)) {
        return std::make_pair(_handles.at(number), number); // モデルハンドルを返す
      }
      // 未登録の場合はオリジナルのハンドルを複製
      auto handle = DxLib::MV1DuplicateModel(_handles.at(Begine));
      // 複製に成功したか
      if (handle == -1) {
#ifdef _DEBUG
        // ハンドルが未登録の場合
        if (!_handles.size()) {
          OutputDebugString("ハンドルの複製に失敗しました。対象ハンドルはNULLです\n");
        }
#endif
        return std::make_pair(-1, MaxNumber); // 複製失敗
      }
      auto no = static_cast<unsigned short>(_handles.size()); // 新規通し番号
      // 通し番号をキーとして、複製したモデルハンドルを登録する
      _handles.emplace(no, handle);
      return std::make_pair(handle, no);
    }

    int ModelData::AnimIndex(std::string_view animName) {
      // アニメーションは登録されているか
      if (!_animes.contains(animName.data())) {
        return AnimNull; // キーが未登録
      }
      // アニメーション番号を返す
      return _animes.at(animName.data());
    }
  } // namespace Model
} // namespace 