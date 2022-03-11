/*****************************************************************//**
 * @file   Box.cpp
 * @brief  �j��\�Ȕ��N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "Box.h"
#include "ApplicationMain.h"
#include "CollisionAABB.h"
#include "SpawnItem.h"
#include "ObjectServer.h"
#include "HealBox.h"
#include "UtilityDX.h"

namespace {
  constexpr auto TotalTime = 0.0f;
  constexpr auto PlayTime = 0.0f;
  constexpr auto DefaultSound = "";
  constexpr auto HealSound = "";
}

namespace Gyro {
  namespace Item {

    Box::Box(Application::ApplicationMain& app) : ObjectBase(app) {
      // �f�t�H���g�̃T�E���h�L�[���Z�b�g����
      _sound = DefaultSound;
    }

    bool Box::Process() {
      // �X�V����
      return ObjectBase::Process();
    }

    void Box::Set(Object::SpawnItem& spawn) {
      // �X�|�[�������Z�b�g����
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
      // ���f���n���h���̎擾
      auto [handle, num] = _app.GetModelServer().GetModel(spawn.ModelKey(), _modelNum);
      // ���f���n���h���̓o�^
      _model = handle;
      // ���f���J�E���g�����Z
      ++_modelNum;
      // �A�C�e���^�C�v�̐ݒ�
      using SpawnItemType = Object::SpawnItem::ItemType;
      switch (spawn.GetItemType()) {
      case SpawnItemType::Normal:
        _boxType = BoxType::Normal;
        break;
      case SpawnItemType::Heal:
        _boxType = BoxType::Heal;
        break;
      }
      // ����������Ɋp�x���Z�o����
      using Matrix44 = AppMath::Matrix44;
      _world = Matrix44::Identity();
      _world.MulScaling(_scale);
      _world.MulTranslate(_position);
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
    }

    void Box::Break() {
      // ���ɔ��͔j�󂳂�Ă��邩
      if (IsDead()) {
        return; // �j�󂳂�Ă���ꍇ�͏������s��Ȃ�
      }
      // �I�u�W�F�N�g��j���ԂɑJ�ڂ���
      _state = ObjectState::Dead;
      // �񕜃t�B�[���h�𐶐����邩
      CreateHeal();
      // SE���Đ�����
      _app.GetSoundComponent().PlayBackGround(_sound);
    }

    void Box::CreateHeal() {
      // �{�b�N�X�^�C�v���q�[���ł͂Ȃ��ꍇ�������s��Ȃ�
      if (_boxType != BoxType::Heal) return;
      // �q�[���{�b�N�X�̐���
      auto heal = std::make_shared<Object::HealBox>(_app);
      // �p�����[�^�̐ݒ�
      heal->SetParam(_position, TotalTime, PlayTime);
      // �R���W�������̐���
      auto min = _position + AppMath::Vector4(-500.0f, 0.0f, -500.0f);
      auto max = _position + AppMath::Vector4(500.0f, 500.0f, 500.0f);
      auto collision = std::make_unique<Object::CollisionAABB>(*heal, min, max);
      // ���������R���W������o�^
      heal->SetCollision(std::move(collision));
      // �I�u�W�F�N�g�T�[�o�ɓo�^����
      _app.GetObjectServer().Register(heal);
      // ��SE���Z�b�g����
      _sound = HealSound;
    }
  } // namespace Item
} // namespace Gyro