/*****************************************************************//**
 * @file   PrimitivePlane.h
 * @brief  プリミティブベースのサブクラス
 * 
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "PrimitiveBase.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プリミティブ
   */
  namespace Primitive {
    /**
     * @brief 床
     */
    class Plane : public PrimitiveBase {
    public:
      /**
       * @brief 空のコンストラクタ
       */
      Plane();
      /**
       * @brief サイズ指定できるコンストラクタ
       * @param size サイズ
       * @param devisionNum 分割数
       */
      Plane(double size, int devisionNum);
      /**
       * @brief デストラクタ
       */
      virtual ~Plane() = default;
      /**
       * @brief 初期化 インスタンス後にセットできるようにしている
       * @param size サイズ
       * @param divisionNum 分割数
       */
      bool Initialize(double size, int divisionNum);
      /**
       * @brief プリミティブの作成
       */
      bool Create() override;

    protected:
      double _size;       //!< サイズ
      int _divisionNum;   //!< 床全体のサイズを分割した数
    };
  } // namespace Gyro
} // namespace Gyro

