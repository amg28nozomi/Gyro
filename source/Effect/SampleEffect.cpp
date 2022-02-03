/*****************************************************************//**
 * @file   SampleEffect.cpp
 * @brief  �������G�t�F�N�g�N���X
 *
 * @author �{�V�s��
 * @date   January 2021
 *********************************************************************/
#include "SampleEffect.h"

namespace Gyro {
    namespace Effect {
        SampleEffect::SampleEffect() {
            // ������
            Init();
        }

        SampleEffect::~SampleEffect() {

        }

        void SampleEffect::Init() {
            // ������
            _eScale = 10.0f;
            _eSpeed = 2.0f;
            // �G�t�F�N�g�ǂݍ���
            _eHandle = LoadEffekseerEffect("res/Effect/Laser01.efkefc", _eScale);
        }

        void SampleEffect::Process() {
            EffectBase::Process();
        }

        void SampleEffect::Draw() const{
            EffectBase::Draw();
        }
    } // namespace Effect
} // namespace Gyro