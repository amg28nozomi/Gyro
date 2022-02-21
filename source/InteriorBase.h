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