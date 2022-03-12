/*****************************************************************//**
 * @file   Box.cpp
 * @brief  �j��\�Ȕ��N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "Box.h"
#include "ApplicationMain.h"
#include "SpawnItem.h"
#include "ObjectServer.h"
#include "HealBox.h"
#include "UtilityDX.h"
#include "Player.h"
#include "AttackComponent.h"

namespace {
  constexpr auto TotalTime = 600.0f;
  constexpr auto PlayTime = 1.0f;
  constexpr auto DefaultSound = "";
  constexpr auto HealSound = "";
}

namespace Gyro {
  namespace Item {

    Box::Box(Application::ApplicationMain& app) : ObjectBase(app) {
      // �f�t�H���g�̃T�E���h�L�[���Z�b�g����
      _id = ObjectId::Item;
      _sound = DefaultSound;
      _model = 0;
    }

    bool Box::Process() {
      // �X�V����
      ObjectBase::Process();
      return IsDamage();
    }

    bool Box::Draw() const {
      // ���f���̕`����s��
      MV1DrawModel(_model);
      return true;
    }

    void Box::Set(Object::SpawnItem& spawn) {
      // �X�|�[�������Z�b�g����
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
      // �R���W���������Z�b�g����
      using Vector4 = AppMath::Vector4;
      auto min = _position - Vector4(100.0f, 0.0f, 100.0f);
      auto max = _position + Vector4(100.0f, 100.0f, 100.0f);
      _collision = std::make_unique<Object::CollisionAABB>(*this, min, max);

      // ���f���n���h���̎擾
      auto [handle, num] = _app.GetModelServer().GetModel(spawn.ModelKey(), 2);
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
      _app.GetObjectServer().Register(std::move(heal));
      // ��SE���Z�b�g����
      _sound = HealSound;
    }

    bool Box::IsDamage() {
      // �_���[�W������s��
      auto player = _app.GetObjectServer().GetPlayer();
      auto attack = player->AttackComponent();
      if (attack.GetState() != Object::AttackComponent::AttackState::Active) return false;
      // �����蔻����̎擾
      auto collision = attack.GetCollisions();

      if (collision.empty()) return false;
      for (auto point : collision) {
        // AABB�Ƌ��ŏՓ˔�����s��
        if (_collision->CheckSphere(*std::dynamic_pointer_cast<Object::CollisionSphere>(point))) {
          Break(); // �j�󏈗��ɑJ��
          return true;
        }
      }
      return false;
    }
  } // namespace Item
} // namespace Gyro