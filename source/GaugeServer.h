/*****************************************************************//**
 * @file   GaugeServer.h
 * @brief  �Q�[���Q�[�W���Ǘ�����Q�[�W�T�[�o�[
 * 
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <appframe.h>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �Q�[�W�x�[�X
   */
  namespace Gauge {
    class GaugeBase; //!< �O���錾
    /**
     * @class GaugeServer
     * @brief �Q�[���Q�[�W���Ǘ�����Q�[�W�T�[�o�[
     */
    class GaugeServer : AppFrame::Server::ServerTemplateVector<std::shared_ptr<GaugeBase>> {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      GaugeServer();
      /**
       * @brief �f�X�g���N�^
       */
      ~GaugeServer();
      /**
       * @brief  ���\�[�X�̉��
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �o�^�Q�[�W�̍X�V
       * @return true
       */
      bool Process();
      /**
       * @brief  �`�揈���̌Ăяo��
       * @return true
       */
      bool Draw();
      /**
       * @brief  �O������Q�[�W��o�^����
       * @param  gauge �Q�[�W�̃X�}�[�g�|�C���^
       * @return true:�o�^���� false:�o�^���s
       */
      bool Register(std::shared_ptr<GaugeBase> gauge);
      /**
       * @brief  �Q�[�W�T�[�o�[�̎擾
       * @return �Q�[�W�T�[�o�[�̎Q��
       */
      std::vector<std::shared_ptr<GaugeBase>> GetGauge();
    private:
      bool _play{ false }; //!< �Q�[�W�T�[�o�[���񂵂Ă��邩�̃t���O
      std::vector<std::shared_ptr<GaugeBase>> _addGauge; //!< �o�^�\��p
      /**
       * @brief  �Q�[�W�̓o�^
       * @param  gauge �Q�[�W�̃X�}�[�g�|�C���^
       * @return true:�o�^���� false:�o�^���s
       */
      bool AddGauge(std::shared_ptr<GaugeBase> gauge);
      /**
       * @brief �Q�[�W���o�^����Ă���R���e�i���������
       * @param container �Q�[�W�̃V�F�A�[�h�|�C���^���i�[���ꂽ�R���e�i�̎Q��
       */
      void DeleteGauge(std::vector<std::shared_ptr<GaugeBase>>& container);
      /**
       * @brief �R���e�i�̃Q�[�W�����W�X�g���[�ɓo�^����
       * @param container �Q�[�W�̃V�F�A�[�h�|�C���^���i�[���ꂽ�R���e�i�̎Q��
       */
      void AddGauges(std::vector<std::shared_ptr<GaugeBase>>& container);
      /**
       * @brief  �Q�[�W�̓o�^�\��
       * @param  gauge �Q�[�W�̃V�F�A�[�h�|�C���^
       * @return true:�\�񐬌� false:�\�񎸔s
       */
      bool AddReserve(std::shared_ptr<GaugeBase> gauge);
    };
  } // namespace Gauge
} // namespace Gyro

