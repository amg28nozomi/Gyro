/*****************************************************************//**
 * @file    MotionInfo.h
 * @brief   ���f���A�j�����N���X
 *
 * @author  �{�V�s��
 * @date    December 2021
 *********************************************************************/
#pragma once

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief ���f���A�j���x�[�X
   */
  namespace ModelAnim {
    /**
     * @class MotionInfo
     * @brief ���f���A�j�����N���X
     */
    class ModelAnimInfo {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      ModelAnimInfo();
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModelAnimInfo();
      /**
       * @brief  ��񏉊���
       */
      void Reset();
      /**
       * @brief  �Đ����ԃJ�E���g
       */
      void CountPlayTime();
      /**
       * @brief  �A�j���[�V�����ԍ��̐ݒ�
       * @param  animNum �A�j���[�V�����ԍ�
       */
      void SetAnimNum(const int animNum) {
        _animNum = animNum;
      }
      /**
       * @brief  �A�^�b�`�ԍ��̐ݒ�
       * @param  index �A�^�b�`�ԍ�
       */
      void SetAttachIndex(const int index) {
        _attachIndex = index;
      }
      /**
       * @brief  �A�j���[�V���������Ԃ̐ݒ�
       * @param  time �A�j���[�V����������
       */
      void SetTotalTime(const float time) {
        _totalTime = time;
      }
      /**
       * @brief  �A�j���[�V�����Đ����Ԃ̐ݒ�
       * @param  time �A�j���[�V�����Đ�����
       */
      void SetPlayTime(const float time) {
        _playTime = time;
      }
      /**
       * @brief  �A�j���[�V�����Đ����x�̐ݒ�
       * @param  speed �A�j���[�V�����Đ����x
       */
      void SetPlaySpeed(const float speed) {
        _playSpeed = speed;
      }
      /**
       * @brief  �Đ����x�{���̐ݒ�
       * @param  rate �Đ����x�{��
       */
      void SetSpeedRate(const float rate) {
        _speedRate = rate;
      }
      /**
       * @brief  ���[�v�Đ��L���̐ݒ�
       * @param  loop ���[�v�Đ��L��
       */
      void SetAnimLoop(const bool loop) {
        _animLoop = loop;
      }
      /**
       * @brief  �A�j���[�V�����ԍ��̎擾
       * @return �A�j���[�V�����ԍ�
       */
      int GetAnimNum() const {
        return _animNum;
      }
      /**
       * @brief  �A�^�b�`�ԍ��̎擾
       * @return �A�^�b�`�ԍ�
       */
      int GetAttachIndex() const {
        return _attachIndex;
      }
      /**
       * @brief  �A�j���[�V���������Ԃ̎擾
       * @return �A�j���[�V����������
       */
      float GetTotalTime() const {
        return _totalTime;
      }
      /**
       * @brief  �A�j���[�V�����Đ����Ԃ̎擾
       * @return �A�j���[�V�����Đ�����
       */
      float GetPlayTime() const {
        return _playTime;
      }
      /**
       * @brief  �A�j���[�V�����I���̎擾
       * @return �A�j���[�V�����I��
       */
      bool GetAnimEnd() const {
        return _animEnd;
      }

    private:
      int _animNum{ -1 };        //!< �A�j���[�V�����ԍ�
      int _attachIndex{ -1 };    //!< �A�^�b�`�ԍ�
      float _totalTime{ 0.0f };  //!< �A�j���[�V����������
      float _playTime{ 0.0f };   //!< �A�j���[�V�����Đ�����
      float _playSpeed{ 0.0f };  //!< �A�j���[�V�����Đ����x
      float _speedRate{ 1.0f };  //!< �Đ����x�{��
      bool _animLoop{ false };   //!< ���[�v�Đ��L��
      bool _animEnd{ false };    //!< �A�j���[�V�����I��
    };
  } // namespace ModelAnim
} // namespace Gyro