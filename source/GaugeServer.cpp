///*****************************************************************//**
// * @file   GaugeServer.cpp
// * @brief  ゲームゲージを管理するゲージサーバの定義
// * 
// * @author 土橋 峡介
// * @date   February 2022
// *********************************************************************/
//#include "GaugeServer.h"
//#include "GaugeBase.h"
//
//namespace Gyro {
//    namespace Gauge {
//
//        GaugeServer::GaugeServer() : AppFrame::Server::ServerTemplateVector<std::shared_ptr<GaugeBase>>() {
//#ifdef _DEBUG
//            SetServerName("GaugeServer");
//#endif // _DEBUG
//            // 各種コンテナを解放する
//            //ServerTemplateVector<std::shared_ptr<GaugeBase>>::_registry.clear();
//            _addGauge.clear();
//        }
//
//        GaugeServer::~GaugeServer() {
//            Release(); // ゲージ解放する
//        }
//
//        bool GaugeServer::Release() {
//            using VectorServer = AppFrame::Server::ServerTemplateVector<std::shared_ptr<GaugeBase>>;
//            _addGauge.clear(); // 登録予約されているゲージを削除
//            return true;
//        }
//
//        bool GaugeServer::Process() {
//            // 追加予約されているゲージがある場合は登録処理を行う
//            if (!_addGauge.empty()) {
//                AddGauge(_addGauge); // レジストリーに登録
//            }
//            _play = true;  // 処理開始
//            for (auto object : _registry) {
//                object->Process(); // 更新処理呼び出し
//            }
//            _play = false; // 処理終了
//            // 不要になったゲージを削除する
//            std::erase_if(_registry, [](auto&& gauge) {return gauge->IsDead(); });
//            return true;
//        }
//
//        bool GaugeServer::AddGauge(std::shared_ptr<GaugeBase> gauge) {
//            if (gauge == nullptr) {
//#ifdef _DEBUG
//                throw LogicError("ゲージはnullptrです");
//#endif
//                return false; // 中身がnullptr
//            }
//            // コンテナを回しているかの有無で登録先を切り替え
//            if (_play) {
//#ifdef _DEBUG
//                auto flag = false; // 処理フラグ
//                try {
//                    flag = AddReserve(std::move(object));
//                    // 例外をキャッチした場合は出力を行う
//                }
//                catch (std::logic_error error) {
//                    DebugString(error.what());
//                }
//                return flag; // フラグを返す
//#else
//                return AddReserve(std::move(gauge));
//#endif // DEBUG
//            }
//            // コンテナを回していない場合は直接登録する
//            _registry.emplace_back(std::move(gauge));
//            return true; // 登録完了
//        }
//
//        void GaugeServer::DeleteGauge(std::vector<std::shared_ptr<GaugeBase>>& container) {
//            // 登録オブジェクトを解放する
//            for (auto&& gau : container) {
//                // 解放処理を行う
//            }
//            container.clear(); // コンテナの解放
//        }
//
//        void GaugeServer::AddGauges(std::vector<std::shared_ptr<GaugeBase>>& container) {
//            // オブジェクトを末尾に追加
//            for (auto&& gau : container) {
//                _registry.emplace_back(std::move(gau));
//            }
//            container.clear(); // コンテナの解放
//        }
//
//        bool GaugeServer::AddReserve(std::shared_ptr<GaugeBase> gauge) {
//            // 所有権が一つではない場合
//            if (gauge.use_count() != 1) {
//#ifdef _DEBUG
//                throw LogicError("他にもオブジェクトの所有権が存在しています");
//#endif
//                return false; // 予約失敗
//            }
//            // 登録予約
//            _addGauge.emplace_back(std::move(gauge));
//            return true; // 予約成功
//        }
//
//        std::vector<std::shared_ptr<GaugeBase>> GaugeServer::GetGauge() {
//            return _registry; // データベースを叩きつける
//        }
//    }
//}
