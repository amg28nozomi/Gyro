/*****************************************************************//**
 * @file   SpawnEnemy.h
 * @brief  �X�|�[���x�[�X�̃T�u�N���X
 *         �G�l�~�[�p�̃X�|�[�����N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "SpawnBase.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    constexpr auto EnemyWheel = 0; //!< ����^�G�l�~�[
    /**
     * @class SpawnEnemy
     * @brief �G�l�~�[�̃X�|�[�����
     */
    class SpawnEnemy : public SpawnBase {
    public:
      /**
       * @brief �G�l�~�[�̎��
       */
      enum class EnemyType {
        None, // �Y���Ȃ�
        Wheel // ����^
      };
      /**
       * @brief  ��̃R���X�g���N�^
       */
      SpawnEnemy();
      /**
       * @brief  �R���X�g���N�^
       * @param  type �I�u�W�F�N�g�^�C�v
       * @param  position �������W
       * @param  rotation ����
       * @param  scale    �g�嗦
       * 
       */
      SpawnEnemy(const int type, const Vector4& position, const Vector4& rotation, const Vector4& scale);
      /**
       * @brief ���[�u�R���X�g���N�^
       * @param spawn ���[�u�Ώ�
       */
      SpawnEnemy(SpawnEnemy&& spawn) = default;
      /**
       * @brief  �G�l�~�[�^�C�v�̎擾
       * @return �G�l�~�[�^�C�v��Ԃ�
       */
      const EnemyType GetEnemyType() const {
        return _enemyType;
      }
      /**
       * @brief  �G�l�~�[���̎Q�Ƃ̎擾
       * @return �Q�Ƃ�Ԃ�
       */
      SpawnEnemy& GetInstanceEnemy() {
        return *this;
      }
    private:
      EnemyType _enemyType; //!< �G�l�~�[�^�C�v
      /**
       * @brief  �ԍ����G�l�~�[�^�C�v�ɕϊ�����
       * @param  number �ԍ�
       * @return �Y������G�l�~�[�^�C�v��Ԃ�
       *         �ԍ����Y�����Ȃ��ꍇ��None��Ԃ�
       */
      const EnemyType NumberToEnemyType(const int number) const;
    };
  } // namespace Object
} // namespace Gyro

