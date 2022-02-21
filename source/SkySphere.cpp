/*****************************************************************//**
 * @file   SkySphere.cpp
 * @brief  �X�J�C�X�t�B�A�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "SkySphere.h"
#include "ApplicationMain.h"
#include "SpawnBase.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Object {

    SkySphere::SkySphere(Application::ApplicationMain& app, ObjectBase& owner) : ObjectBase(app), _owner(owner) {
      _id = ObjectId::SkySphere;
      _gravity = false;
      Init();
    }

    bool SkySphere::Init() {
      _handle = 0;
      return true;
    }

    void SkySphere::Set(Object::SpawnBase& spawn) {
      // �e����̐ݒ�
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
    }

    bool SkySphere::Process() {
      // ���[���h���W�s��
      _world= AppMath::Utility::ToWorldMatrix(_owner.GetPosition(), _rotation, _scale);
      // _world = AppMath::Matrix44::Identity();
      //_world.Translate(_position);
      //_world = _world * w;

      // _position = _owner.GetPosition();
      // MV1SetPosition(_handle, UtilityDX::ToVECTOR(_position));
      // ���[���h���W�̍X�V
      // WorldMatrix();
      // ���W�̐ݒ�
      auto num = MV1SetMatrix(_handle ,UtilityDX::ToMATRIX(_world));
      return true;
    }

    bool SkySphere::Draw() const {
      // ���f���̕`��ɐ����������̔���
      if (MV1DrawModel(_handle) == -1) {
        return false; // ���s
      }
      return true;
    }

    bool SkySphere::SetKey(std::string_view key) {
      // ���f���n���h���̎擾
      auto [handle, id] = _app.GetModelServer().GetModel(key, 1);
      // ���f���n���h���̎擾�ɐ���������
      if (handle == -1) {
        return false; // ���s
      }
      // �n���h����ݒ�
      _handle = handle;
      return true;
    }

  } // namespace Object
} // namespace Gyro