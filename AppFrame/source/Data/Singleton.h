/*****************************************************************//**
 * @file   Singleton.h
 * @brief  �V���O���g���N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <Windows.h>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @class Singleton
   * @brief �V���O���g���N���X
   */
  template<class T>
  class Singleton {
  public:
    /**
     * @brief  �ΏۃN���X�̎Q�Ƃ��擾
     * @return
     */
    static T& GetInstance() {
      return *Singleton<T>::_instance;
    }
    /**
     * @brief  ���̂̐���
     * @return true:�������� false:�����ς�
     */
    static bool Create();
    /**
     * @brief  ���̂̍폜
     * @return true:���� false:���̂��Ȃ�
     */
    static bool Delete();
  protected:
    static inline std::unique_ptr<T> _instance{nullptr}; //!< ����
    /**
     * @brief �O���ł̃C���X�^���X�����͋֎~
     */
    Singleton();
    /**
     * @brief �f�X�g���N�^
     */
    virtual ~Singleton();
  private:
    /**
     * @brief ������Z�q�ɂ��쐬���֎~����
     */
    void operator=(const Singleton & singleton);
    /**
     * @brief �R�s�[�R���X�g���N�^���֎~����
     */
    Singleton(const Singleton& singleton)
  };

  template<class T>
  bool Singleton<T>::Create() {
    // ���̂��Ȃ��ꍇ�̂ݐ������s��
    if (Singleton<T>::_instance == nullptr) {
      Singleton<T>::_instance = std::make_unique<T>();
      return true; // ���̍쐬
    }
#ifdef _DEBUG
    OutputDebugString("Singleton:���ɃC���X�^���X�͐�������Ă��܂�\n");
#endif
    return false;
  }

  template<class T>
  bool Singleton<T>::Delete() {
    // ���̂�����ꍇ�̂ݍ폜���s��
    if (Singleton<T>::_instance) {
      // �ێ����Ă��郊�\�[�X���������
      Singleton<T>::_instance.reset();
      return true;
    }
    return false;
  }

  template<class T>
  Singleton<T>::Singleton() {
  }

  template<class T>
  Singleton<T>::~Singleton() {
  }

  template<class T>
  void Singleton<T>::operator=(const Singleton& singleton) {
  }

  template<class T>
  Singleton<T>::Singleton(const Singleton& singleton) {
  }
} // namespace AppFrame