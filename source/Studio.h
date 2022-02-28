/*****************************************************************//**
 * @file    Studio.h
 * @brief   ���[�h�p�X�^�W�I�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "ModelAnimComponent.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief �X�^�W�I�x�[�X
   */
  namespace Studio {
    namespace AppMath = AppFrame::Math;
    /**
     * @class Studio
     * @brief ���[�h�p�X�^�W�I�N���X
     */
    class Studio {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      Studio(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~Studio();
      /**
       * @brief  ������
       */
      void Init();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  �`��
       */
      void Draw() const;
      /**
       * @brief  �W���C���A�j���؂�ւ�
       * @param  key �A�j���L�[
       */
      void GyroChangeAnim(const std::string_view key);
      /**
       * @brief  �W���C���A�j���I������
       * @return true:�W���C���A�j���I��
       *         false:�W���C���A�j���Đ���
       */
      bool IsGyroAnimEnd() {
        return _modelAnim.GetMainAnimEnd();
      }

    private:
      /**
       * @brief  ���\�[�X�ǂݍ���
       */
      void LoadResource();
      /**
       * @brief  ���f���z�u
       */
      void LayOut();

      int _studioHandle{ -1 };  //!< �X�^�W�I���f��
      int _gyroHandle{ -1 };    //!< �W���C�����f��
      int _skyHandle{ -1 };     //!< �X�J�C���f��
      AppMath::Vector4 _skyRot{ 0.0f, 0.0f, 0.0f };  //!< �X�J�C����
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< ���f���A�j��
      ModelAnim::ModelAnimComponent _modelAnim;
    };
  }
}