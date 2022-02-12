#pragma once
#include <appframe.h>

namespace Gyro {
  namespace Player {
    /**
     * @class 
     * @brief 
     */
    class WireComponent {
    public:
      /**
       * @brief 開始処理
       */
      void Start();
      /**
       * @brief 終了処理
       */
      void Finish();
    protected:
      //!< ターゲット座標
      AppFrame::Math::Vector4 _target{};
      //!< ターゲットへの向き
      AppFrame::Math::Vector4 _forward{};
    };
  } // namespace Player
} // namespace Gyro