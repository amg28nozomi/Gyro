#include "StateComponent.h"
#include <appframe.h>

namespace {
  // ����
  constexpr auto Max = 100;
  constexpr auto Min = 0;
}

namespace Gyro {
  namespace Object {

    StateComponent::StateComponent() {
      // ������
      _type = ComponentType::State;
      Init();
    }

    void StateComponent::Init() {
      // ����������
    }

    bool StateComponent::Set(float total, int start, int end) {
      // �͈͓��Ɏ��܂��Ă��邩�̔���
      if (AppFrame::Math::Arithmetic::IsRange(start, Min, Max)) {
        // �͈͓��Ɏ��܂��Ă��邩�̔���
        if (AppFrame::Math::Arithmetic::IsRange(end, Min, Max)) {
          // �J�n�t���[���ƏI���t���[�����Z�b�g����
          _start = Frame(total, static_cast<float>(start));
          _end = Frame(total, static_cast<float>(end));
          return true; // �Z�b�g����
        }
      }
      return false;    // �ݒ莸�s
    }

    void StateComponent::Start() {
      _flag = false; // ���͏�Ԃ�false�ɂ���
    }

    void StateComponent::Finish() {
      _flag = true;
    }

    bool StateComponent::Process(const float play) {
      if (_flag) {
        return false;
      }
      using Arithmetic = AppFrame::Math::Arithmetic;
      // ����͈͓����܂��Ă��邩�H
      if (Arithmetic::IsRange(play, static_cast<float>(_start), static_cast<float>(_end))) {
        // �I�����������s
        Finish();
        return true; // ���͗L��
      }
      return false;  // ����O
    }

    int StateComponent::Frame(float total, int percent) {
      float num = percent / Max;
      return static_cast<int>(total * num);
    }

  } // namespace Object
} // namespace Gyro