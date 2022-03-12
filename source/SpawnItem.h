/*****************************************************************//**
 * @file   SpawnItem.h
 * @brief  �A�C�e���̐������N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "SpawnBase.h"

namespace Gyro {

  namespace Item {
    constexpr auto ItemNormal = 0;
  } // namespace Item

  namespace Object {
    class SpawnItem : public Object::SpawnBase {
    public:
      /**
       * @brief �A�C�e���̎�ނ�\���񋓌^�N���X
       */
      enum class ItemType {
        Normal, //
        Heal    //
      };
      /**
       * @brief  �R���X�g���N�^
       * @param  key  ���f���n���h���ɕR�Â���������
       * @param  type �A�C�e���^�C�v
       * @param  position �������W
       * @param  rotation �������̌���
       * @param  scale    �������̊g�嗦
       */
      SpawnItem(std::string_view key, const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale);
      /**
       * @brief  �A�C�e�����̎Q�Ƃ��擾
       * @return 
       */
      SpawnItem& GetInstanceItem() {
        return *this;
      }
      /**
       * @brief �A�C�e���^�C�v�̎擾
       */
      ItemType GetItemType() {
        return _itemType;
      }
      /**
       * @brief  ���f���L�[�̎擾
       * @return ���f���L�[
       */
      std::string_view ModelKey() const {
        return _modelKey;
      }
      /**
       * @brief  �A�C�e���ԍ��ւ̕ϊ�
       * @return
       */
      int ItemToNumber();
    private:
      //!< �A�C�e���^�C�v
      ItemType _itemType;
      //!< ���f���L�[
      std::string _modelKey;
      /**
       * @brief  
       * @param  type �A�C�e���ԍ�
       */
      void SetItemType(const int type);
    };
  } // namespace Object
} // namespace Gyro