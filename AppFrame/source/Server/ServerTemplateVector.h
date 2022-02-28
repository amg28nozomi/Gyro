/*****************************************************************//**
 * @file   ServerTemplateVector.h
 * @brief  �T�[�o�p�e���v���[�g�N���X(vector)
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ServerBase.h"
#include <vector>
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �T�[�o�x�[�X
   */
  namespace Server {
    /**
     * @class ServerTemplateVector
     * @brief ���I�z��ɑΉ������T�[�o�e���v���[�g
     */
    template <typename T>
    class ServerTemplateVector : public ServerBase<std::vector<T>> {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ServerTemplateVector();
      /**
       * @brief  ���\�[�X�̉������
       * @return 
       */
      virtual bool Release() override;
      /**
       * @brief  �f�t�H���g�̓o�^����
       * @param  value �o�^�f�[�^
       * @return true:�o�^���� false:�o�^���s
       */
      virtual bool Register(T value);
    protected:
    };
    // ��`
    template <typename T>
    ServerTemplateVector<T>::ServerTemplateVector() : ServerBase<std::vector<T>>() {
#ifdef _DEBUG
      // �f�o�b�O���̓T�[�o����ݒ�
      ServerBase<std::vector<T>>::_name = "ServerTemplate";
#endif
    }

    template <typename T>
    bool ServerTemplateVector<T>::Release() {
      // �S�v�f���폜����
      ServerBase<std::vector<T>>::_registry.clear();
      return true;
    }

    template <typename T>
    bool ServerTemplateVector<T>::Register(T value) {
      // �����ɗv�f���\�z
      ServerBase<std::vector<T>>::_registry.emplace_back(value);
      return true;
    }
  } // namespace Server
} // namespace AppFrame