#include "ComboState.h"
#include <stdexcept>

namespace Gyro{
  namespace Player {

    ComboState::ComboState() {
    }

    ComboState::ComboState(std::string_view animName, float total, float start, float end) {
      _animName = animName.data();
      _totalTime = total;
      SetJustTime(start, end);
    }
    
    bool ComboState::Process(float animFrame) {
      // 
      return true;
    }

    void ComboState::SetJustTime(float start, float end) {
#ifdef _DEBUG
      // ����p�e�[�u��
      auto table = { start, end };
      for (auto value : table) {
        // ���Ԃ��}�C�i�X�̏ꍇ
        if (value < 0.0f) {
          throw std::logic_error("ComboState:�W���X�g���莞�Ԃ��s���ł�\n");
        }
      }
#endif
      // �J�n�t���[�����I���t���[���ȏ�̏ꍇ�͒l���X���b�v
      if (end < start) {
        std::swap(start, end);
      }
      // �W���X�g���莞�Ԃ��Z�b�g����
      _justStart = start;
      _justEnd = end;
    }
  } // namespace Player
} // namespace Gyro