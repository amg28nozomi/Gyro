/*****************************************************************//**
 * @file   ModeFade.h
 * @brief  ���[�h�x�[�X�̃T�u�N���X
 *         �V�[���J�ڎ��̃t�F�[�h�������s��
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ModeBase.h"
#include "../Data/Color.h"
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    constexpr auto AlphaMax = 255.0f; //!< �A���t�@�l�̏��
    constexpr auto AlphaMin = 0.0f;   //!< �A���t�@�l�̉���
    constexpr auto FadeTime = 60.0f;  //!< �f�t�H���g�̃t�F�[�h����(�t���[��)
    constexpr auto AlphaDelta = (AlphaMax / FadeTime); //!< �A���t�@�l�̕ω���(�f�t�H���g)
    /**
     * @class ModeFade
     * @brief �V�[���J�ڗp���[�h
     *        �V�[���J�ڎ��̃t�F�[�h�������s��
     */
    class ModeFade : public ModeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       * @param color �t�F�[�h�����Ŏg�p����RGB�l
       */
      ModeFade(Application::ApplicationBase& app, const Data::Color color);
      /**
       * @brief �f�X�g���N�^
       */
      ~ModeFade() override;
      /**
       * @brief  ����������
       * @return true
       */
      bool Init() override;
      /**
       * @brief  ��������
       * @return true
       */
      virtual bool Enter() override;
      /**
       * @brief  �X�V����
       * @return true
       */
      virtual bool Process() override;
      /**
       * @brief  �`�揈��
       * @return true
       */
      virtual bool Draw() const override;
      /**
       * @brief �W���J���[�̐ݒ�
       * @param color �ݒ肷��RGB�l
       */
      void SetColor(const Data::Color color);
      /**
       * @brief �A���t�@�l�̕ω��ʂ�ݒ�
       * @param value 0~255�܂ł�float�l
       */
      void SetDeltaAlpha(const float value);
    protected:
      Data::Color _basic; //!< �W���J���[�l
      Data::Color _color; //!< �t�F�[�h�����Ŏg�p����RGB�l
      int _width;  //!< �t�F�[�h�{�b�N�X�̉���
      int _height; //!< �t�F�[�h�{�b�N�X�̏c��
      float _alpha{0.0f};      //!< �A���t�@�l
      float _deltaAlpha{0.0f}; //!< �A���t�@�l�̕ω���
      /**
       * @brief  �t�F�[�h�����̏I������
       * @return false
       */
      virtual bool IsFinish();
    };
  } // namespace Mode
} // namespace AppFrame