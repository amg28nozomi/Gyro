/*****************************************************************//**
 * @file   StateComponent.h
 * @brief  ��ԑJ�ڔ���p�̃R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <utility>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    /**
     * @class  ObjectComponent
     * @brief  ��ԑJ�ڔ���p�̃R���|�[�l���g
     */
    class StateComponent : public ObjectComponent {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      StateComponent();
      /**
       * @brief  ����������
       */
      void Init() override;
      /**
       * @brief  ���͏����̐ݒ�
       * @param  total �A�j���[�V�����̑��Đ��t���[����
       * @param  start ����J�n�t���[��(����)
       * @param  end   ����I���t���[��(����)
       * @return true:�ݒ萬�� false:�ݒ莸�s
       */
      bool Set(float total, int start, int end);
      /**
       * @brief  �J�n����
       */
      void Start() override;
      /**
       * @brief  �I������
       */
      void Finish() override;
      /**
       * @brief  �X�V����
       * @param  play �A�j���[�V�����̍Đ��t���[��
       * @return true:���͂��� false:���͂Ȃ�
       */
      bool Process(const float play);
    private:
      int _start{0};     //!< ���͎�t�t���[��(�J�n)
      int _end{0};       //!< ���͎�t�t���[��(�I��)
      bool _flag{false}; //!< ���͂���������
      /**
       * @brief  ����t���[���̎Z�o
       * @param  total   ���Đ��t���[��
       * @param  percent ����
       * @return ����t���[��
       */
      int Frame(float total, int percent);
    };
  } // namespace Object
} // namespace Gyro