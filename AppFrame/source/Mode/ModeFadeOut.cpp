/*****************************************************************//**
 * @file   ModeFadeOut.cpp
 * @brief  ���[�h�t�F�[�h�̃T�u�N���X
 *         �t�F�[�h�A�E�g�������s��
 * 
 * @date   January 2022
 *********************************************************************/
#include "ModeFadeOut.h"
#include "../Application/ApplicationBase.h"

namespace AppFrame {
  namespace Mode {

    ModeFadeOut::ModeFadeOut(Application::ApplicationBase& app, const Data::Color color) : ModeFade(app, color) {
    }

    bool ModeFadeOut::Enter() {
      // �e��p�����[�^�̏�����
      _alpha = AlphaMin;
      _deltaAlpha = AlphaDelta;
      return true;
    }

    bool ModeFadeOut::Process() {
      // �A���t�@�l�̉��Z
      _alpha += _deltaAlpha;
      return ModeFade::Process();
    }

    bool ModeFadeOut::IsFinish() {
      // �A���t�@�l�͏���ȏ�ɂȂ��Ă��邩
      return AlphaMax <= _alpha;
    }
  } // namespace Mode
} // namespace AppFrame