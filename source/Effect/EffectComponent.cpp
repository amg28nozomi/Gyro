/*****************************************************************//**
 * @file    EffectComponent.cpp
 * @brief   �G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "EffectComponent.h"

namespace Gyro {
    namespace Effect {
        EffectComponent::EffectComponent(Application::ApplicationMain& app) : _app(app) {

        }

        EffectComponent::~EffectComponent() {

        }

        void EffectComponent::Process() {
            // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
            Effekseer_Sync3DSetting();
            // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
            UpdateEffekseer3D();
        }

        void EffectComponent::Draw() const {
            // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
            DrawEffekseer3D();
        }

        void EffectComponent::PlayEffect(const std::string_view key, const AppMath::Vector4 position, const float radian) {
            // �G�t�F�N�g�n���h���̎擾
            int handle = GetEffectHandle(key);
            if (handle == -1) {
                // ���o�^�̏ꍇ���f
                return;
            }
            // �G�t�F�N�g���Đ�����B
            int play = PlayEffekseer3DEffect(handle);
            // �G�t�F�N�g�̈ʒu��ݒ�
            auto& [x, y, z] = position.GetVector3();
            SetPosPlayingEffekseer3DEffect(play, x, y, z);
            // �G�t�F�N�g�̌�����ݒ�
            SetRotationPlayingEffekseer3DEffect(play, 0.0f, radian, 0.0f);
        }

        int EffectComponent::GetEffectHandle(const std::string_view key) {
            return _app.GetEffectServer().GetEffectHandle(key);
        }
    } // namespace Effect
} // namespace Gyro