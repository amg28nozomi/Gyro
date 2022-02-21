/*****************************************************************//**
 * @file   InteriorBase.h
 * @brief  �C���e���A�̊��N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
#include <memory>
#include "CollisionBase.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class SpawnBase;
  } // namespace Object
  /**
   * @brief �C���e���A�x�[�X
   */
  namespace Interior {
    /**
     * @class  InteriorBase
     * @brief  �C���e���A�̊��N���X
     */
    class InteriorBase : public Object::ObjectBase {
    public:
      /**
       * @brief �C���e���A�̎�ނ�\���񋓌^�N���X
       */
      enum class InteriorType {
        None,  // �Y���Ȃ�
        Box,   // ��
      };
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      InteriorBase(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~InteriorBase() = default;
      /**
       * @brief  ����������
       * @return true
       */
      virtual bool Init() override;
      /**
       * @brief  �X�V����
       * @return true
       */
      virtual bool Process() override;
      /**
       * @brief  �`�揈��
       * @return true
       */
      virtual bool Draw() const override;
      /**
       * @brief  �ݒ菈��
       * @param  spawn �X�|�[�����
       */
      virtual void Set(Object::SpawnBase& spawn) override;
      /**
       * @brief  �C���e���A�^�C�v�̎擾
       * @return �C���e���A�^�C�v
       */
      InteriorType GetInteriorType() const {
        return _interior;
      }
    protected:
      //!< �C���e���A�̎��
      InteriorType _interior{InteriorType::None};
      //!< �����蔻����
      std::unique_ptr<Object::CollisionBase> _collision{nullptr};
    };
  } // namespace Interior
} // namespace Gyro