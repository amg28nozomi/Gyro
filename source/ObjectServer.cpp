/*****************************************************************//**
 * @file   ObjectServer.cpp
 * @brief  �I�u�W�F�N�g���Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"
#include "Player.h"

namespace Gyro {
  namespace Object {

    ObjectServer::ObjectServer() : ServerTemplateVector<std::shared_ptr<ObjectBase>>() {
#ifdef _DEBUG
      SetServerName("ObjectServer");
#endif
      // �e��R���e�i���������
      ServerTemplateVector<std::shared_ptr<ObjectBase>>::_registry.clear();
      _addObject.clear();
    }

    ObjectServer::~ObjectServer() {
      Release(); // �I�u�W�F�N�g���������
    }

    bool ObjectServer::Release() {
      // �R���e�i�̒��g���������
      for (auto object : _registry) {
        // �f�[�^�̔j���������Ăяo��
      }
      _registry.clear();     // �R���e�i�̒��g���������
      _addObject.clear();    // �o�^�\�񂳂�Ă���I�u�W�F�N�g���폜
      return true;
    }

    bool ObjectServer::Process() {
      // �ǉ��\�񂳂�Ă���I�u�W�F�N�g������ꍇ�͓o�^�������s��
      if (!_addObject.empty()) {
        AddObjects(_addObject); // ���W�X�g���\�ɓo�^
      }
      _play = true;  // �����J�n
      for (auto object : _registry) {
        object->Process(); // �X�V�����Ăяo��
      }
      _play = false; // �����I��
      // �s�v�ɂȂ����I�u�W�F�N�g���폜����
      std::erase_if(_registry, [](auto&& obj) {return obj->IsDead(); });
      return true;
    }

    bool ObjectServer::Draw() {
      for (auto&& obj : _registry) {
        obj->Draw(); // �`�揈���Ăяo��
      }
      return true;
    }

    bool ObjectServer::Register(std::shared_ptr<ObjectBase> object) {
      return AddObject(std::move(object)); // �o�^�����Ɉڍs
    }

    bool ObjectServer::AddObject(std::shared_ptr<ObjectBase> object) {
      // �I�u�W�F�N�g��null�ł͂Ȃ���
      if (object == nullptr) {
#ifdef _DEBUG
        throw LogicError("�I�u�W�F�N�g��nullptr�ł�");
#endif
        return false; // ���g��nullptr
      }
      // �R���e�i���񂵂Ă��邩�̗L���œo�^���؂�ւ�
      if (_play) {
#ifndef _DEBUG
        return AddReserve(std::move(object)); // �ǉ��\��
#else
        auto flag = false; // �����t���O
        try {
          flag = AddReserve(std::move(object));
          // ��O���L���b�`�����ꍇ�͏o�͂��s��
        } catch (std::logic_error error) {
          DebugString(error.what());
        }
        return flag; // �t���O��Ԃ�
#endif
      }
      // �R���e�i���񂵂Ă��Ȃ��ꍇ�͒��ړo�^����
      _registry.emplace_back(std::move(object));
      return true; // �o�^����
    }

    void ObjectServer::DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& container) {
      // �o�^�I�u�W�F�N�g���������
      for (auto&& obj : container) {
        // ����������s��
      }
      container.clear(); // �R���e�i�̉��
    }

    void ObjectServer::AddObjects(std::vector<std::shared_ptr<ObjectBase>>& container) {
      // �I�u�W�F�N�g�𖖔��ɒǉ�
      for (auto&& obj : container) {
        _registry.emplace_back(std::move(obj));
      }
      container.clear(); // �R���e�i�̉��
    }

    bool ObjectServer::AddReserve(std::shared_ptr<ObjectBase> object) {
      // ���L������ł͂Ȃ��ꍇ
      if (object.use_count() != 1) {
#ifdef _DEBUG
        throw LogicError("���ɂ��I�u�W�F�N�g�̏��L�������݂��Ă��܂�");
#endif
        return false; // �\�񎸔s
      }
      // �o�^�\��
      _addObject.emplace_back(std::move(object));
      return true; // �\�񐬌�
    }

    std::vector<std::shared_ptr<ObjectBase>> ObjectServer::GetObjects() {
      return _registry; // �f�[�^�x�[�X��@������
    }

    bool ObjectServer::GetPlayerTransForm(AppMath::Vector4& position, AppMath::Vector4& rotation) {
      auto player = GetPlayer(); // ���@�̎擾
      // ���g��nullptr�̏ꍇ�͏������s��Ȃ�
      if (player == nullptr) {
        return false; // �擾���s
      }
      position = player->GetPosition(); // ���[�J�����W
      rotation = player->GetRotation(); // ��]��
      return true; // �擾����
    }

    std::shared_ptr<Player::Player> ObjectServer::GetPlayer() {
      std::shared_ptr<Player::Player> player = nullptr;
      for (auto obj : _registry) {
        // ���@�̏ꍇ�̓|�C���^���擾
        if (obj->GetId() == ObjectBase::ObjectId::Player) {
          player = std::dynamic_pointer_cast<Player::Player>(obj); // ���@���R�s�[
          break;
        }
      }
#ifdef _DEBUG
      try {
        LogicError("���@�̎擾�Ɏ��s���܂���");
      }
      catch (std::logic_error error) {
        DebugString(error.what()); // �o�͂���
      }
#endif
      return player; // ���@�̎Q�Ƃ�Ԃ�
    }
  } // namespace Object
} // namespace Gyro