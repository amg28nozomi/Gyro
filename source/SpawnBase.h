/*****************************************************************//**
 * @file   SpawnBase.h
 * @brief  �I�u�W�F�N�g�������Ɏg�p����p�����[�^�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <tuple>
#include <appframe.h>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    constexpr auto TypePlayer = 0;     //!< ���@
    constexpr auto TypeEnemyWheel = 1; //!< ����^�G�l�~�[

    constexpr auto TypeSkySphere = 5;  //!< �X�J�C�X�t�B�A
    /**
     * @brief Vector4�N���X�̏ȗ�
     */
    using Vector4 = AppFrame::Math::Vector4;
    /**
     * @class SpawanData
     * @brief �I�u�W�F�N�g�������Ɏg�p����p�����[�^�N���X
     */
    class SpawnBase {
    public:
      /**
       * @brief �I�u�W�F�N�g�̎�ނ�\��
       */
      enum class ObjectType {
        None,     // ����
        Player,   // ���@
        Enemy,    // �G
        SkySphere // �X�J�C�X�t�B�A
      };
      /**
       * @brief �R���X�g���N�^
       */
      SpawnBase();
      /**
       * @brief �R���X�g���N�^
       * @param type     �I�u�W�F�N�g�^�C�v
       * @param position �������W
       * @param rotation �������̌���
       * @param scale    �������̃X�P�[��
       */
      SpawnBase(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale);
      /**
       * @brief  �I�u�W�F�N�g�^�C�v�̎擾
       * @return �I�u�W�F�N�g�^�C�v
       */
      const ObjectType GetType() const {
        return _type;
      }
      /**
       * @brief  ���W���̎擾
       * @return ���W
       */
      const Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  �������̎擾
       * @return ����
       */
      const Vector4 GetRotation() const {
        return _rotation;
      }
      /**
       * @brief  �X�P�[�����̎擾
       * @return �X�P�[��
       */
      const Vector4 GetScale() const {
        return _scale;
      }
      /**
       * @brief  �g�����X�t�H�[���̎擾
       * @return 0:���W 1:���� 2:�X�P�[��
       */
      std::tuple<Vector4, Vector4, Vector4> GetTransform() const {
        return std::make_tuple(_position, _rotation, _scale);
      }
      /**
       * @brief  �������̎Q�Ƃ��擾
       * @return �Q�Ƃ�Ԃ�
       */
      SpawnBase& GetInstance() {
        return *this;
      }
    protected:
      ObjectType _type;  //!< �I�u�W�F�N�g�^�C�v
      Vector4 _position; //!< �������W
      Vector4 _rotation; //!< �p�x
      Vector4 _scale;    //!< �X�P�[��
      /**
       * @brief  �I�u�W�F�N�g�ԍ����I�u�W�F�N�g�^�C�v�ɕϊ�����
       * @param  number �I�u�W�F�N�g�^�C�v(����)
       * @return �I�u�W�F�N�g�^�C�v��Ԃ�
       */
      virtual const ObjectType NumberToType(const int number) const;
    };
  } // namespace Object
} // namespace Gyro