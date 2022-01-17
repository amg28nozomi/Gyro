/*****************************************************************//**
 * @file   ScoreServer.h
 * @brief  �Q�[���X�R�A���Ǘ�����X�R�A�T�[�o
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �X�R�A�x�[�X
   */
  namespace Score {
    /**
     * @class ScoreServer
     * @brief �Q�[���X�R�A�̊Ǘ����s���X�R�A�T�[�o
     */
    class ScoreServer : AppFrame::Server::ServerTemplateUnordered<std::string, class ScoreBase> {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ScoreServer();
      /**
       * @brief  �������
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �X�R�A�̓o�^
       * @param  key �X�R�A�ɕR�Â��镶����
       * @param  score �o�^�X�R�A
       * @return true:�o�^���� false:�o�^���s
       */
      bool AddScore(std::string_view key, ScoreBase score);
      /**
       * @brief  �w�肵���L�[�̃X�R�A���擾����
       * @param  key �X�R�A�ɕR�Â���ꂽ������
       * @return �ΏۃX�R�A��Ԃ�
       *         �擾�Ɏ��s�����ꍇ��-1��Ԃ�
       */
      int GetScore(std::string_view key) const;
      /**
       * @brief  �w�肵���X�R�A�f�[�^���폜����
       * @param  key �X�R�A�ɕR�Â���ꂽ������
       * @return true:���� false:���s
       */
      bool EraceScore(std::string_view key);
    private:
      /**
       * @brief  �Q�[���X�R�A���m�̔�r����
       * @param  left  �Q�[���X�R�A
       * @param  right �Q�[���X�R�A
       * @return 
       */
      bool ScoreCheck(const ScoreBase left, const ScoreBase right) const;
    };
  } // namespace Score
} // namespace Gyro