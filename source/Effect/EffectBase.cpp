/*****************************************************************//**
 * @file   EffectBase.cpp
 * @brief  �G�t�F�N�g�̊��N���X
 *
 * @author �{�V�s��
 * @date   January 2021
 *********************************************************************/
#include "EffectBase.h"

namespace Gyro {
    namespace Effect {
        EffectBase::EffectBase() {
            // ������
            Init();
        }

        EffectBase::~EffectBase() {

        }

        void EffectBase::Init() {
            // ������
            _eHandle = 0;
            _playEff = -1;
            _eScale = 0.0f;
            _eSpeed = 0.0f;
            _ePos = AppMath::Vector4();
            _eRot = AppMath::Vector4();
        }

        void EffectBase::Process() {
            // �G�t�F�N�g�����Đ��̏ꍇ���f
            if (!IsEffectPlaying()) {
                return;
            }
            // �Đ����̃G�t�F�N�g�̈ʒu��ݒ�
            SetPosPlayingEffekseer3DEffect(_playEff, _ePos.GetX(), 100.0f, _ePos.GetZ());
            // �Đ����̃G�t�F�N�g�̌�����ݒ�
            SetRotationPlayingEffekseer3DEffect(_playEff, 0, _eRot.GetY() *-1, 0);
            // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V
            UpdateEffekseer3D();
        }

        void EffectBase::Draw() const{
            // �G�t�F�N�g�����Đ��̏ꍇ���f
            //if (!IsEffectPlaying()) {
            //    return;
            //}
            // DX���C�u�����̃J������Effekseer�̃J�����𓯊�
            Effekseer_Sync3DSetting();
            // Effekseer�ɂ��Đ�����3D�G�t�F�N�g�̕`����J�n
            DrawEffekseer3D_Begin();
            // �w�肳�ꂽEffekseer�ɂ��Đ����̃G�t�F�N�g��`��
            DrawEffekseer3D_Draw(_playEff);
            // Effekseer�ɂ��Đ�����3D�G�t�F�N�g�̕`����I��
            DrawEffekseer3D_End();
        }

        void EffectBase::PlayEffect() {
            // �G�t�F�N�g�Đ����̏ꍇ���f
            if (IsEffectPlaying()) {
                return;
            }
            //�G�t�F�N�g���Đ�
            _playEff = PlayEffekseer3DEffect(_eHandle);
            SetSpeedPlayingEffekseer3DEffect(_playEff, _eSpeed);
        }
    } // namespace Effect
} // namespace Gyro