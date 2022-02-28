/*****************************************************************//**
 * @file   ModeFadeIn.cpp
 * @brief  ���[�h�t�F�[�h�̃T�u�N���X
 *         �t�F�[�h�C���������s��
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ModeFadeIn.h"
#include "../Application/ApplicationBase.h"

namespace AppFrame{
  namespace Mode {

    ModeFadeIn::ModeFadeIn(Application::ApplicationBase& app, const Data::Color color) : ModeFade(app, color) {
    }

    bool ModeFadeIn::Enter() {
      // �e��p�����[�^�̏�����
      _alpha = AlphaMax;
      _deltaAlpha = AlphaDelta;
      return true;
    }

    bool ModeFadeIn::Process() {
      // �A���t�@�l�̌��Z
      _alpha -= _deltaAlpha;
      return ModeFade::Process();
    }

    bool ModeFadeIn::IsFinish() {
      // �A���t�@�l�͉����ȉ���
      return _alpha <= AlphaMin;
    }
  } // namespace Mode
} // namespace AppFrame