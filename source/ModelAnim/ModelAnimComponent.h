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

 /** ��i�p���O��� */
namespace Gyro {
  /** ���f���A�j���p���O��� */
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
       * @brief  ������
       */
      void Init();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  ���C���A�j���[�V�����A�^�b�`
       *         (���������ȊO�g���Ă͂����Ȃ�)
       * @param  handle ���f���n���h��
       * @param  key �A�j���[�V������
       * @param  speed �A�j���[�V�����Đ����x
       * @param  loop ���[�v�Đ��L��
       */
      void SetMainAttach(const int handle, std::string_view key, const float speed, const bool loop);
      /**
       * @brief  �u�����h�A�j���[�V�����A�^�b�`
       *         (�A�j���[�V�����؂�ւ��͂�������g��)
       * @param  key �A�j���[�V������
       * @param  frame �u�����h�t���[��
       * @param  speed �A�j���[�V�����Đ����x
       * @param  loop ���[�v�Đ��L��
       */
      void SetBlendAttach(std::string_view key, const float frame, const float speed, const bool loop);
      /**
       * @brief  ���݂̃A�j���[�V�����̃A�^�b�`�ԍ��擾
       * @return �A�^�b�`�ԍ�
       */
      int GetMainAttachIndex() const {
        return _main.GetAttachIndex();
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
      void SetAttach(ModelAnimInfo& info, std::string_view key, const float speed, const bool loop);
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