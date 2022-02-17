/*****************************************************************//**
 * @file   StageBase.h
 * @brief  ステージのスーパークラス
 * 
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
      class ApplicationMain; //!< 前方宣言
  } // namespace Application
  /**
   * @brief ステージベース
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class SpawnBase; //!< スポーン情報
    /**
     * @class StageBase
     * @brief ステージのスーパークラス
     */
    class StageBase {
    public:
      /**
       * @brief オブジェクト識別番号の列挙型クラス
       */
      enum class ObjectId {
          House,        //!< 家
          LongHouse,    //!< 長屋
          Board,        //!< 板
          Box,          //!< 箱
          Tower         //!< 時計塔
      };
      /**
       * @brief ステージの状態を表す列挙型クラス
       */
      enum class StageState {
        Active, //!< 活動状態
        Dead    //!< 死亡状態
      };
      /**
       * @brief コンストラクタ
       * @param アプリケーションの参照
       */
      StageBase(Application::ApplicationMain& app);
      /**
       * @brief  初期化処理
       * @return true
       */
      virtual bool Init();
      /**
       * @brief  更新処理
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  描画処理
       * @return true
       */
      virtual bool Draw() const;
      /**
       * @brief スポーン情報の読み取り
       * @param spawn スポーン情報
       */
      virtual void Set(SpawnBase& spawn);
      /**
       * @brief  状態の取得
       * @return 状態
       */
      StageState GetState() const {
          return _state;
      }
      /**
       * @brief  死亡状態かの判定
       * @return true:死亡状態 false:死んでいない
       */
      virtual bool IsDead() const {
          return _state == StageState::Dead;
      }
      /**
       * @brief  ローカル座標の取得
       * @return ローカル座標
       */
      AppMath::Vector4 GetPosition() const {
          return _position;
      }
      /**
       * @brief  回転値の取得
       * @return 回転値
       */
      AppMath::Vector4 GetRotation() const {
          return _rotation;
      }
      /**
       * @brief  拡大率の取得
       * @return 拡大率
       */
      AppMath::Vector4 GetScale() const {
          return _scale;
      }
      /**
       * @brief  モデルハンドル格納コンテナの取得
       * @return モデルハンドル格納コンテナ
       */
      std::vector<int> GetStageModel() {
          return _model;
      }
    protected:
      Application::ApplicationMain& _app;        //!< アプリケーションの参照
      StageState _state{ StageState::Active };   //!< 状態
      AppFrame::Math::Vector4 _position;         //!< ローカル座標
      AppFrame::Math::Vector4 _rotation;         //!< 回転(Debug:デグリー Release:ラジアン)
      AppFrame::Math::Vector4 _scale{ 0, 0, 0 }; //!< 拡大率
      std::vector<int> _model{ -1 }; //!< モデルハンドル格納用コンテナ
    };
  } // namespace Stage
} // namespace Gyro
