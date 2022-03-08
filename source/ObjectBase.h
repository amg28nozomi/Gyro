/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  �I�u�W�F�N�g�̃X�[�p�[�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class SpawnBase; //!< �X�|�[�����
    /**
     * @class ObjectBase
     * @brief �I�u�W�F�N�g�̃X�[�p�[�N���X
     */
    class ObjectBase {
    public:
      /**
       * @brief �I�u�W�F�N�g���ʔԍ��̗񋓌^�N���X
       */
      enum class ObjectId {
        Object,   //!< �I�u�W�F�N�g
        Player,   //!< �v���C���[
        Enemy,    //!< �G
        SkySphere //!< �X�J�C�X�t�B�A
      };
      /**
       * @brief �I�u�W�F�N�g�̏�Ԃ�\���񋓌^�N���X
       */
      enum class ObjectState {
        Active, //!< �������
        Paused, //!< ��~���
        Dead    //!< ���S���
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ObjectBase(Application::ApplicationMain& app);
      /**
       * @brief  ����������
       * @return true
       */
      virtual bool Init();
      /**
       * @brief  �X�V����
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  �`�揈��
       * @return true
       */
      virtual bool Draw() const;
      /**
       * @brief  �X�|�[�����̓ǂݎ��
       * @param  spawn �X�|�[�����
       */
      virtual void Set(SpawnBase& spawn);
      /**
       * @brief  �d�͏������s�����̃t���O���Z�b�g
       * @param  flag true:�d�͏������s�� false:�d�͏����𖳌�
       */
      virtual inline void GravitySet(const bool flag) {
        _gravity = flag;
      }
      /**
       * @brief �����x�N�g���̐ݒ�
       * @param forward �����x�N�g��
       */
      inline void SetForward(AppMath::Vector4 forward) {
        _forward = forward;
      }
      /**
       * @brief  �w�肵���t���[���̃��[���h���W���擾
       * @param  frame �t���[���ԍ�
       * @return ��̃x�N�g����Ԃ�
       */
      virtual AppMath::Vector4 GetFramePosition(int frame) {
        return AppMath::Vector4();
      }
      /**
       * @brief  ���ʔԍ��̎擾
       * @return ���ʔԍ�
       */
      ObjectId GetId() const {
        return _id;
      }
      /**
       * @brief  ��Ԃ̎擾
       * @return ���
       */
      ObjectState GetState() const {
        return _state;
      }
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S��� false:����ł��Ȃ�
       */
      virtual bool IsDead() const {
        return _state == ObjectState::Dead;
      }
      /**
       * @brief  ���[���h���W�s��̎擾
       * @return ���[���h���W�s��
       */
      AppMath::Matrix44 GetMatrix() const {
        return _world;
      }
      /**
       * @brief  ���[�J�����W�̎擾
       * @return ���[�J�����W
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  �����̎擾
       * @return ����
       */
      AppMath::Vector4 GetRotation() const {
        return _rotation;
      }
      /**
       * @brief  �g�嗦�̎擾
       * @return �X�P�[��
       */
      AppMath::Vector4 GetScale() const {
        return _scale;
      }
      /**
       * @brief  �����x�N�g���̎擾
       * @return �����x�N�g��
       */
      AppMath::Vector4 GetForward() const {
        return _forward;
      }
      /**
       * @brief  �A�v���P�[�V�����̎擾
       * @return �A�v���P�[�V�����̎Q��
       */
      Application::ApplicationMain& GetApplicaton() const {
        return _app;
      }
      /**
       * @brief  ���f���ɕR�Â���ꂽ������̎擾
       * @return ������
       */
      virtual std::string_view ModelKey() const {
        return "";
      }
      /**
       * @brief �����̐ݒ�
       * @param rotation �ݒ肷�����
       */
      inline void SetRotation(const AppMath::Vector4& rotation) {
        _rotation = rotation;
      }
      /**
       * @brief  �����x�N�g���̎擾
       * @return �����x�N�g��
       */
      inline AppMath::Vector4 Forward() const {
        return _forward;
      }
      /**
       * @brief  �\�[�g�p�̒l���擾
       * @return �\�[�g�p�̒l
       */
      int GetSort() {
        return _sort;
      }
    protected:
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �I�u�W�F�N�g�̎��ʔԍ�
      ObjectId _id{ObjectId::Object};
      //!< ���
      ObjectState _state{ObjectState::Active};
      //!< ���[���h���W
      AppMath::Matrix44 _world;
      //!< ���[�J�����W
      AppMath::Vector4 _position;
      //!< ��](Debug:�f�O���[ Release:���W�A��)
      AppMath::Vector4 _rotation;
      //!< �g�嗦
      AppMath::Vector4 _scale{0, 0, 0};
      //!< �����x�N�g��
      AppMath::Vector4 _forward{0, 0, 0};
      int _sort;            //!< �\�[�g�p
      bool _stand{false};   //!< �����t���O(true:���ɗ����Ă��� false:���ƐڐG���Ă��Ȃ�)
      bool _gravity{false}; //!< �d�͏������s����(true:�d�͏������s�� false:�d�͏������s��Ȃ�)
      float _mass{0.0f};    //!< ����
      float _gravityScale{0.0f}; //!< �d�̓X�P�[��
      /**
       * @brief �I�u�W�F�N�g�ɑ΂���d�͏���
       */
      virtual void Gravity();
      /**
       * @brief  �d�̓X�P�[���̍X�V
       */
      virtual void GravityScale();
      /**
       * @brief  ���Ƃ̏Փ˔���
       *         �h���N���X�ŏd�͏������s���ꍇ�͕K���Ē�`���s������
       * @return true:�Փ˂��Ă��� false:�Փ˂��Ă��Ȃ�
       */
      virtual bool IsStand();
      /**
       * @brief  �d�͏����̃��Z�b�g
       */
      virtual void GravityReset();
      /**
       * @brief  �����o������
       */
      virtual void Extrude(){}
      /**
       * @brief  ���[���h���W�̍X�V
       * @param  angle �p�x�t���O(true:�f�O���[ false:���W�A��)
       */
      void WorldMatrix(bool angle = AppMath::Degree);
#ifdef _DEBUG
      /**
       * @brief �f�o�b�O��p�̏o�͏���
       *        �A�v���P�[�V�����̃f�o�b�O�t���O��true�̏ꍇ�̂ݏ������s��
       */
      virtual bool DebugDraw() const;
#endif
    };
  } // namespace Object
} // namespace Gyro