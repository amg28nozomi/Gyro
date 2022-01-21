/*****************************************************************//**
 * @file   PrimitiveBase.h
 * @brief  プリミティブのスーパークラス
 * 
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <memory>
#include <vector>

/**
 * @brief ゲームベース
 */
namespace Gyro {
    /**
     * @brief プリミティブ
     */
    namespace Primitive {
        /**
         * @class Primitive
         * @brief プリミティブのスーパークラス
         */
        class PrimitiveBase {
        public:
            /**
             * @brief コンストラクタ
             */
            PrimitiveBase();

            /**
             * @brief デストラクタ
             */
            virtual ~PrimitiveBase();

            /**
             * @brief 画像のロード
             */
            virtual bool Load(const TCHAR* fileName);

            /**
             * @brief 画像のロード(false時の処理)
             */
            virtual bool UnLoad();

            /**
             * @brief プリミティブの作成(純粋仮想関数)
             */
            virtual bool Create() = 0;

            /**
             * @brief 処理
             */
            virtual void Process();

            /**
             * @brief 描画
             */
            virtual bool Render();

            /**
             * @brief 頂点情報の取得
             * @return 頂点情報を返す
             */
            const std::shared_ptr<std::vector<VERTEX3D>>& GetVertex() const { return _vertex; }

            /**
             * @brief 配列の要素を取得
             * @return 配列の要素を返す
             */
            const std::shared_ptr<std::vector<unsigned short>>& GetIndex() const { return _index; }

        protected:
            int _handle;        //!< 画像ハンドル

            std::shared_ptr<std::vector<VERTEX3D>> _vertex;         //!< 頂点
            std::shared_ptr<std::vector<unsigned short>> _index;    //!< 要素
        };
    }// namespace Primitive
}// namespace Gyro
