/*****************************************************************//**
 * @file   PlayerAttackData.h
 * @brief  ���@�̍U�������Ǘ�������N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "PlayerAttack.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    /**
     * @class  PlayerAttackData
     * @brief  ���@�̍U�������i�[����f�[�^
     */
    //class PlayerAttackData {
    //public:
    //  /**
    //   * @brief �R���X�g���N�^
    //   * @param next     �J�ڂ�����
    //   * @param start    ���͎�t�J�n
    //   * @param end      ���͎�t�I��
    //   * @param coolTime �d������
    //   */
    //  PlayerAttackData(const PlayerAttack::AttackState next, int start, int end, int coolTime);
    //  /**
    //   * @brief  �J�ڂ���U����Ԃ�Ԃ�
    //   * @return �J�ڏ�ԁB�R���{���p�����Ȃ��ꍇ��None��Ԃ�
    //   */
    //  PlayerAttack::AttackState NextState() const {
    //    return _next;
    //  }
    //  /**
    //   * @brief  ���͊J�n�t���[���̎擾
    //   * @return ���͊J�n�t���[��
    //   */
    //  float StartFrame() const {
    //    return static_cast<float>(_start);
    //  }
    //  /**
    //   * @brief  ���͏I���t���[���̎擾
    //   * @return ���͏I���t���[��
    //   */
    //  float EndFrame() const {
    //    return static_cast<float>(_end);
    //  }
    //  /**
    //   * @brief  �d�����Ԃ̎擾
    //   * @return �d������
    //   */
    //  float CoolTime() const {
    //    return static_cast<float>(_coolDown);
    //  }
    //private:
    //  //!< �J�ڂ���U�����
    //  PlayerAttack::AttackState _next;
    //  //!< ���͎�t�t���[��(�J�n)
    //  int _start;
    //  //!< ���͎�t�t���[��(�I��)
    //  int _end;
    //  //!< �N�[���^�C��(�d������)
    //  int _coolDown;
    //};
  } // namespace Player
} // namespace Gyro