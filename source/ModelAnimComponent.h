/*****************************************************************//**
 * @file    ModelAnimComponent.h
 * @brief   ���f���A�j���N���X
 *
 * @author  �{�V�s��
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ModelAnimInfo.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief ���f���A�j���x�[�X
   */
  namespace ModelAnim {
    /**
     * @class ModelAnimComponent
     * @brief ���f���A�j���N���X
     */
    class ModelAnimComponent {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      ModelAnimComponent();
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModelAnimComponent();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  ���C���A�j���[�V�����A�^�b�`
       *         (���������ȊO�g���Ă͂����Ȃ�)
       * @param  handle ���f���n���h��
       * @param  key    �A�j���[�V������
       * @param  speed  �A�j���[�V�����Đ����x
       * @param  loop   ���[�v�Đ��L��
       */
      void SetMainAttach(const int handle, const std::string_view key, const float speed, const bool loop);
      /**
       * @brief  �u�����h�A�j���[�V�����A�^�b�`
       *         (�A�j���[�V�����؂�ւ��͂�������g��)
       * @param  key   �A�j���[�V������
       * @param  frame �u�����h�t���[��
       * @param  speed �A�j���[�V�����Đ����x
       * @param  loop  ���[�v�Đ��L��
       */
      void SetBlendAttach(const std::string_view key, const float frame, const float speed, const bool loop);
      /**
       * @brief  ���݂̃A�j���[�V�����̍Đ����x�{���̐ݒ�
       * @param  rate �Đ����x�{��
       */
      void SetMainSpeedRate(const float rate) {
        _main.SetSpeedRate(rate);
      }
      /**
       * @brief  �w��A�j���[�V�������Z�b�g����Ă��邩�̔���
       * @param  key    �A�j���[�V������
       * @return true:�Z�b�g����Ă��� false:�Z�b�g����Ă��Ȃ�
       */
      bool IsSetMainAnim(std::string_view key);
      /**
       * @brief  �A�j���[�V�������̃A�j���[�V�����ԍ��ϊ�
       * @param  key �A�j���[�V������
       * @return �A�j���[�V�����ԍ�
       */
      int AnimKeyConversion(const std::string_view key) const {
        return MV1GetAnimIndex(_mHandle, key.data());
      }
      /**
       * @brief  ���݂̃A�j���[�V�����̃A�j���[�V�����ԍ��̎擾
       * @return �A�j���[�V�����ԍ�
       */
      int GetMainAnimNum() const {
        return _main.GetAnimNum();
      }
      /**
       * @brief  ���݂̃A�j���[�V�����̃A�^�b�`�ԍ��̎擾
       * @return �A�^�b�`�ԍ�
       */
      int GetMainAttachIndex() const {
        return _main.GetAttachIndex();
      }
      /**
       * @brief  ���݂̃A�j���[�V�����̑����Ԃ̎擾
       * @return �A�j���[�V����������
       */
      float GetMainTotalTime() const {
        return _main.GetTotalTime();
      }
      /**
       * @brief  ���݂̃A�j���[�V�����̍Đ����Ԃ̎擾
       * @return �A�j���[�V�����Đ�����
       */
      float GetMainPlayTime() const {
        return _main.GetPlayTime();
      }
      /**
       * @brief  ���݂̃A�j���[�V�����I������
       * @return true:�A�j���[�V�����I��
       *         false:�A�j���[�V�����Đ���
       */
      bool GetMainAnimEnd() const {
        return _main.GetAnimEnd();
      }
      /**
       * @brief  �A�j���[�V�����u�����h������
       * @return true:�A�j���[�V�����u�����h��
       *         false:�A�j���[�V�����u�����h���Ă��Ȃ�
       */
      bool IsBlending() const {
        return _blending;
      }

    private:
      /**
       * @brief  �A�j���[�V�����A�^�b�`
       * @param  info ���f�����
       * @param  key �A�j���[�V������
       * @param  speed �A�j���[�V�����Đ����x
       * @param  loop ���[�v�Đ��L��
       */
      void SetAttach(ModelAnimInfo& info, const std::string_view key, const float speed, const bool loop);
      /**
       * @brief  �A�j���[�V�����f�^�b�`
       * @param  info ���f�����
       */
      void SetDetach(ModelAnimInfo& info);
      /**
       * @brief  �A�j���[�V�����Đ�
       * @param  info ���f�����
       */
      void PlayAnim(ModelAnimInfo& info);
      /**
       * @brief  �A�j���[�V�����u�����h
       */
      void AnimBlend();
      /**
       * @brief  ���f���̃A�^�b�`����
       * @param  info ���f�����
       * @return true:�A�j���[�V�����o�^�ς�
       *         false:�A�j���[�V�������o�^
       */
      bool IsAttachIndex(ModelAnimInfo& info) const {
        return info.GetAttachIndex() != -1;
      }

      int _mHandle{ -1 };         //!< ���f���n���h��
      int _blendCnt{ 0 };         //!< �u�����h�J�E���g
      float _blendFrame{ 0.0f };  //!< �u�����h�t���[��
      bool _blending{ false };    //!< �u�����h��

      ModelAnimInfo _main;   //!< ���݂̃��f�����
      ModelAnimInfo _blend;  //!< �؂�ւ�郂�f�����
    };
  } // namespace ModelAnim
} // namespace Gyro