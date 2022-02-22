/*****************************************************************//**
 * @file   LoadSystem.h
 * @brief  �񓯊��ǂݍ��ݏ����N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <future>
#include <unordered_map>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V����
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
    constexpr auto LoadError = -1; //!< ���[�h�Ώۂł͂Ȃ�
    constexpr auto LoadQuit = 1;   //!< �ǂݍ��ݏI��
    constexpr auto Load = 0;       //!< ���[�h�C��
    /**
     * @class LoadSystem
     * @brief �񓯊��ǂݍ���
     */
    class LoadSystem {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      LoadSystem(ApplicationMain& app);
      /**
       * @brief  �ǂݍ��ݏ����͏I���������̔���
       * @param  number �����ԍ�
       * @return 0:���[�h�� 1:���[�h�I�� -1:�L�[���s��
       */
      int LoadEnd(const int number) const;
    private:
      //!< �A�v���P�[�V�����̎Q��
      ApplicationMain& _app;
      //!< �����ԍ����L�[�Ƃ��āA�񓯊��ǂ݃t���O���Ǘ�����A�z�z��
      std::unordered_map<int, bool> _registry;
      /**
       * @brief  �v�f���o�^����Ă��邩�̔���
       * @param  number �L�[
       * @return true:�o�^�ς� false:���o�^
       */
      bool Contents(const int number) const;
    };

  } // namespace 
} // namespace Gyro