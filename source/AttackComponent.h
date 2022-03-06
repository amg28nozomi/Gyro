/*****************************************************************//**
 * @file   AttackComponent.h
 * @brief  �U���p�R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <memory>
#include <vector>
#include <appframe.h>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class ObjectBase;
    class CollisionBase;
    namespace AppMath = AppFrame::Math;
    constexpr auto DefaultSpeed = 10.0f;
    /**
     * @class AttackComponent
     * @brief �U���p�R���|�[�l���g
     */
    class AttackComponent : public ObjectComponent {
    public:
      /**
       * @brief �U����Ԃ�\���񋓌^�N���X
       */
      enum class AttackState {
        NonActive, // �m�[�A�N�V����
        Active,    // �������
        Interval   // �C���^�[�o��
      };
      /**
       * @brief  �R���X�g���N�^
       * @param  owner     ���L�҂̎Q��
       * @param  key       ���f���T�[�o�ɕR�Â���ꂽ���L�҂�
       * @param  collision �����蔻��̃V�F�A�[�h�|�C���^
       */
      AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision);
      /**
       * @brief  �R���X�g���N�^
       * @param  owner     ���L�҂̎Q��
       * @param  key       ���f���T�[�o�ɕR�Â���ꂽ���L�҂�
       * @param  collision �����蔻����i�[�������I�z��
       */
      AttackComponent(ObjectBase& owner, std::vector<std::shared_ptr<CollisionBase>> collision);
      /**
       * @brief �U������̊J�n
       */
      virtual inline void Start() override {
        _state = AttackState::Active;
      }
      /**
       * @brief �U������̏I��
       */
      virtual void Finish() override;
      /**
       * @brief  �U������̍X�V
       * @param  localPosition ���[�J�����W
       * @return true:����I�� false:�U����Ԃł͂Ȃ�
       */
      virtual bool Process(const AppMath::Vector4& localPosition);
      /**
       * @brief  �U������̏C������
       * @return true:����I�� false:��蔭��
       */
      virtual bool Process();
      /**
       * @brief  �����蔻��Ɏg�p����t���[���̐ݒ�
       * @param  frames     �t���[���ԍ�
       * @param  collisions �R���W�������
       */
      void SetFrame(std::vector<int> frames, std::vector<std::shared_ptr<CollisionBase>> collisions);
#ifdef _DEBUG
      /**
       * @brief �����蔻��̕`�揈��(�f�o�b�O��p)
       */
      void Draw() const;
#endif
      /**
       * @brief  �C���^�[�o�����Ԃ̐ݒ�
       * @param  time  �C���^�[�o������
       * @param  speed �o�ߎ���(�f�t�H���g����10.0f)
       */
      void SetInterval(const float time, const float speed = DefaultSpeed);
      /**
       * @brief  �U����Ԃ̎擾
       * @return �U�����
       */
      const AttackState& GetState() {
        return _state;
      }
      /**
       * @brief  �����蔻����̎擾
       * @return �����蔻����
       */
      const std::shared_ptr<CollisionBase>& GetCollision()  {
        return _collision.front();
      }
      /**
       * @brief  �����蔻����̎擾
       * @return �����蔻�肪�i�[���ꂽ�R���e�i��Ԃ�
       */
      const std::vector<std::shared_ptr<CollisionBase>>& GetCollisions() {
        return _collision;
      }
      /**
       * @brief  �U����Ԃ��̔���
       * @return true:�U����� false:��U�����
       */
      inline bool IsAttack() const {
        return _state == AttackState::Active;
      }
      /**
       * @brief  �C���^�[�o����Ԃ��̔���
       * @return true:�C���^�[�o����� false:����ȊO�̏��
       */
      inline bool IsInterval() const {
        return _state == AttackState::Interval;
      }
      /**
       * @brief  �U����ԂɑJ�ڂł��邩�̔���
       * @return true:�J�ډ\ false:�s��
       */
      inline bool ToAttack() const {
        return _state == AttackState::NonActive;
      }
    protected:
      //!< �I�u�W�F�N�g�̏��L��
      ObjectBase& _owner;
      //!< �I�u�W�F�g�L�[
      std::string _objectKey;
      //!< �U�����
      AttackState _state;
      //!< �U������p�̃R���W���������i�[�������I�z��
      std::vector<std::shared_ptr<CollisionBase>> _collision;
      //!< ���[���h���W���i�[���邽�߂̃R���e�i
      std::vector<int> _indexs;
      //!< �C���^�[�o������
      float _time{0.0f};
      //!< �o�ߎ���
      float _speed{0.0f};
      /**
       * @brief ���[�J�����W�����[���h���W�ɕϊ�����
       */
      AppMath::Matrix44 LocalToWorld(const AppMath::Vector4& local) const;
      /**
       * @brief �C���^�[�o������
       */
      void Interval();
    };
  } // mamespace Object
} // namespace Gyro