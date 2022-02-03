/*****************************************************************//**
 * @file   ObjectServer.h
 * @brief  �I�u�W�F�N�g���Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <appframe.h>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  namespace AppMath = AppFrame::Math;

  namespace Player {
    class Player;
  }
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class ObjectBase; //!< �O���錾
    /**
     * @class ObjectServer
     * @brief �I�u�W�F�N�g���Ǘ�����T�[�o�N���X
     */
    class ObjectServer : public AppFrame::Server::ServerTemplateVector<std::shared_ptr<ObjectBase>> {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ObjectServer();
      /**
       * @brief �f�X�g���N�^
       */
      ~ObjectServer();
      /**
       * @brief  ���\�[�X�̉������
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �o�^�I�u�W�F�N�g�̍X�V
       * @return true
       */
      bool Process();
      /**
       * @brief  �`�揈���̌Ăяo��
       * @return true
       */
      bool Draw();
      /**
       * @brief  �O������I�u�W�F�N�g��o�^����
       * @param  object �I�u�W�F�N�g�̃X�}�[�g�|�C���^
       * @return true:�o�^���� false:�o�^���s
       */
      bool Register(std::shared_ptr<ObjectBase> object);

      std::vector<std::shared_ptr<ObjectBase>> GetObjects();
      /**
       * @brief  ���@�̎擾
       * @return ���@�|�C���^�̎Q��
       */
      std::shared_ptr<Player::Player> GetPlayer();
      /**
       * @brief  ���@�̃g�����X�t�H�[�����擾����
       * @param  position Vector4�N���X�̎Q��(���@���W�i�[�p)
       * @param  rotation Vector4�N���X�̎Q��(���@��]�ʊi�[�p)
       * @return true:�擾���� false:�擾���s
       */
      bool GetPlayerTransForm(AppMath::Vector4& position, AppMath::Vector4& rotation);
    private:
      bool _play{false}; //!< �I�u�W�F�N�g�T�[�o���񂵂Ă��邩�̃t���O
      std::vector<std::shared_ptr<ObjectBase>> _addObject; //!< �o�^�\��p
      /**
       * @brief  �I�u�W�F�N�g�̓o�^����
       * @param  obj �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^
       * @return true:�o�^���� false:�o�^���s
       */
      bool AddObject(std::shared_ptr<ObjectBase> obj);
      /**
       * @brief  �I�u�W�F�N�g���o�^����Ă���R���e�i���������
       * @param  container �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^���i�[���ꂽ�R���e�i�̎Q��
       */
      void DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& container);
      /**
       * @brief �R���e�i�̃I�u�W�F�N�g�����W�X�g���\�ɓo�^����
       * @param container �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^���i�[���ꂽ�R���e�i�̎Q��
       */
      void AddObjects(std::vector<std::shared_ptr<ObjectBase>>& container);
      /**
       * @brief  �I�u�W�F�N�g�̓o�^�\��
       * @param  object �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^
       * @return ture:�\�񐬌� false:�\�񎸔s
       */
      bool AddReserve(std::shared_ptr<ObjectBase> object);
    };
  } // namespace Object
} // namespace Gyro