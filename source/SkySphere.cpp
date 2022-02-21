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
      // ���@�̒��S���W��Ǐ]����
      _position = _owner.GetPosition();
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���W�̐ݒ�
      MV1SetMatrix(_handle ,UtilityDX::ToMATRIX(_world));
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