/*****************************************************************//**
 * @file   Box.h
 * @brief  �j��\�Ȕ����N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"

namespace Gyro {

  namespace Object {
    class SpawnItem;
    class CollisionAABB;
  }
  namespace Item {
    /**
     * @class Box
     * @brief ���N���X
     */
    class Box : public Object::ObjectBase {
    public:
      /**
       * @brief �{�b�N�X�^�C�v
       */
      enum class BoxType {
        Normal, // �ʏ�{�b�N�X
        Heal    // �񕜃{�b�N�X
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      Box(Application::ApplicationMain& app);
      /**
       * @brief
       * @return 
       */
      bool Process() override;

      void Set(Object::SpawnItem& spawn);
      /**
       * @brief  �����蔻����̎擾
       * @return �����蔻����
       */
      Object::CollisionAABB& GetCollision() {
        return *_collision;
      }
      /**
       * @brief  ���f���J�E���g�̏�����
       */
      static inline void ModelNumReset() {
        _modelNum = 1;
      }
    protected:
      //!< �{�b�N�X�^�C�v
      BoxType _boxType{BoxType::Normal};
      //!< ���f���n���h��
      int _model;
      //!< �T�E���h�L�[
      std::string _sound;
      //!< �R���W�������
      std::unique_ptr<Object::CollisionAABB> _collision;
      //!< ���f���n���h���p
      static inline unsigned short _modelNum{1};
      /**
       * @brief  �j�󏈗�
       */
      void Break();
      /**
       * @brief  �񕜃t�B�[���h�̐���
       */
      void CreateHeal();
    };
  } // namespace Item
} // namespace Gyro