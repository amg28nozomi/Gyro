///*****************************************************************//**
// * @file   GaugeServer.cpp
// * @brief  �Q�[���Q�[�W���Ǘ�����Q�[�W�T�[�o�̒�`
// * 
// * @author �y�� ����
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
//            // �e��R���e�i���������
//            //ServerTemplateVector<std::shared_ptr<GaugeBase>>::_registry.clear();
//            _addGauge.clear();
//        }
//
//        GaugeServer::~GaugeServer() {
//            Release(); // �Q�[�W�������
//        }
//
//        bool GaugeServer::Release() {
//            using VectorServer = AppFrame::Server::ServerTemplateVector<std::shared_ptr<GaugeBase>>;
//            _addGauge.clear(); // �o�^�\�񂳂�Ă���Q�[�W���폜
//            return true;
//        }
//
//        bool GaugeServer::Process() {
//            // �ǉ��\�񂳂�Ă���Q�[�W������ꍇ�͓o�^�������s��
//            if (!_addGauge.empty()) {
//                AddGauge(_addGauge); // ���W�X�g���[�ɓo�^
//            }
//            _play = true;  // �����J�n
//            for (auto object : _registry) {
//                object->Process(); // �X�V�����Ăяo��
//            }
//            _play = false; // �����I��
//            // �s�v�ɂȂ����Q�[�W���폜����
//            std::erase_if(_registry, [](auto&& gauge) {return gauge->IsDead(); });
//            return true;
//        }
//
//        bool GaugeServer::AddGauge(std::shared_ptr<GaugeBase> gauge) {
//            if (gauge == nullptr) {
//#ifdef _DEBUG
//                throw LogicError("�Q�[�W��nullptr�ł�");
//#endif
//                return false; // ���g��nullptr
//            }
//            // �R���e�i���񂵂Ă��邩�̗L���œo�^���؂�ւ�
//            if (_play) {
//#ifdef _DEBUG
//                auto flag = false; // �����t���O
//                try {
//                    flag = AddReserve(std::move(object));
//                    // ��O���L���b�`�����ꍇ�͏o�͂��s��
//                }
//                catch (std::logic_error error) {
//                    DebugString(error.what());
//                }
//                return flag; // �t���O��Ԃ�
//#else
//                return AddReserve(std::move(gauge));
//#endif // DEBUG
//            }
//            // �R���e�i���񂵂Ă��Ȃ��ꍇ�͒��ړo�^����
//            _registry.emplace_back(std::move(gauge));
//            return true; // �o�^����
//        }
//
//        void GaugeServer::DeleteGauge(std::vector<std::shared_ptr<GaugeBase>>& container) {
//            // �o�^�I�u�W�F�N�g���������
//            for (auto&& gau : container) {
//                // ����������s��
//            }
//            container.clear(); // �R���e�i�̉��
//        }
//
//        void GaugeServer::AddGauges(std::vector<std::shared_ptr<GaugeBase>>& container) {
//            // �I�u�W�F�N�g�𖖔��ɒǉ�
//            for (auto&& gau : container) {
//                _registry.emplace_back(std::move(gau));
//            }
//            container.clear(); // �R���e�i�̉��
//        }
//
//        bool GaugeServer::AddReserve(std::shared_ptr<GaugeBase> gauge) {
//            // ���L������ł͂Ȃ��ꍇ
//            if (gauge.use_count() != 1) {
//#ifdef _DEBUG
//                throw LogicError("���ɂ��I�u�W�F�N�g�̏��L�������݂��Ă��܂�");
//#endif
//                return false; // �\�񎸔s
//            }
//            // �o�^�\��
//            _addGauge.emplace_back(std::move(gauge));
//            return true; // �\�񐬌�
//        }
//
//        std::vector<std::shared_ptr<GaugeBase>> GaugeServer::GetGauge() {
//            return _registry; // �f�[�^�x�[�X��@������
//        }
//    }
//}
