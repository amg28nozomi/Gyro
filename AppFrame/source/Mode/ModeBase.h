/*****************************************************************//**
 * @file   ModeBase.h
 * @brief  ���[�h�̊��N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationBase;
    class InputOperation;
  } // namespace Application
  /**
   * @brief �t�@�C���T�[�o
   */
  namespace FileServer {
    class FileServer;
  } // namespace FileServer
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    /**
     * @class ModeBase
     * @brief ���[�h�̊��N���X
     */
    class ModeBase {
    public:
      /**
       * @brief ���[�h�̐���
       * @param app �A�v���P�[�V�����̎Q��
       */
      ModeBase(Application::ApplicationBase &app);
      /**
       * @brief ���[�h�̍폜
       */
      virtual ~ModeBase();
      /**
       * @brief  ���[�h�̏�����
       * @return true:���������� false:���������s
       */
      virtual bool Init();
      /**
       * @brief  ��������
       * @return true:�������� false:�������s
       */
      virtual bool Enter();
      /**
       * @brief  �o������
       * @return true:�������� false:���s
       */
      virtual bool Exit();
      /**
       * @brief  ���[�h��p�̓��͏���
       * @param  input �C���v�b�g�I�y���[�V�����̎Q��
       * @return true:�������� false:�������s
       */
      virtual bool Input(Application::InputOperation& input);
      /**
       * @brief  ���[�h�̍X�V
       * @return true:�X�V���� false:�X�V���s
       */
      virtual bool Process();
      /**
       * @brief  ���[�h�̕`��
       * @return true:�`�搬�� false:�`�掸�s
       */
      virtual bool Draw() const;
      /**
       * @brief  �o�߃t���[���̏�����
       */
      virtual void TimeClear();
      /**
       * @brief  �A�v���P�[�V�����̎擾
       * @return �A�v���P�[�V�����̎Q��
       */
      virtual Application::ApplicationBase& GetApplication();
      /**
       * @brief  ���[�h�T�[�o�̎擾
       * @return ���[�h�T�[�o�̎Q��
       */
      class ModeServer& GetModeServer();
      /**
       * @brief  �t�@�C���T�[�o�̎擾
       * @return �t�@�C���T�[�o�̎Q��
       */
      FileServer::FileServer& GetFileServer();
      /**
       * @brief  �{���[�h�̌o�߃t���[�������擾
       * @return �t���[���J�E���^
       */
      int GetFrameCount() const {
        return _count;
      }
      /**
       * @brief  �~���b�̎擾
       * @return �o�ߎ���(�~���b)
       */
      long double GetMilliSecond() const {
        return _milli;
      }
    protected:
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationBase& _app;
      //!< �{���[�h���ł̌o�ߎ���(�t���[��)
      int _count{0};
      //!< �{���[�h���ł̌o�ߎ���(�~���b)
      long double _milli{0.0};
      //!< ���\�[�X�̓ǂݍ��݃t���O
      bool _isLoad{false};
      /**
       * @brief ���Ԍo�ߏ���
       */
      virtual void StepTime();
    };
  } // namespace Mode
} // namespace AppFrame