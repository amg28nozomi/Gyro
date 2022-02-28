/*****************************************************************//**
 * @file   ApplicationBase.h
 * @brief  �A�v���P�[�V�����̃X�[�p�[�N���X
 *         �S�ẴA�v���P�[�V�����͂��̃N���X��h������
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <tuple>
#include <memory>
#include "../FileServer/FileServer.h"
#include "../Mode/ModeServer.h"
#include "../SoundServer/SoundServer.h"
#include "../SoundServer/SoundComponent.h"
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  constexpr auto WindowWidth = 1920;  //!< �f�t�H���g�̉𑜓x���
  constexpr auto WindowHeight = 1080; //!< �f�t�H���g�̉𑜓x���
  constexpr auto BitColor32 = 32;     //!< 32�r�b�g�J���[
  constexpr auto BitColor16 = 16;     //!< 16�r�b�g�J���[
  constexpr auto Frame60 = 60;        //!< 60�t���[��
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    class ModeBase;
  } // namespace Mode
  /**
   * @brief ���f���x�[�X
   */
  namespace Model {
    class ModelServer;
  } // namespace Model
  /**
   * @brief ���\�[�X�x�[�X
   */
  namespace Resource {
    class ResourceServer;
  } // namespace Resource
  /**
   * @brief �T�E���h�x�[�X
   */
  namespace Sound {
    class SoundComponent; //!< �O���錾
  } // namespace Sound
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    /**
     * @class ApplicationBase
     * @brief �A�v���P�[�V�����̊��N���X
     */
    class ApplicationBase {
    public:
      /**
       * @brief  �A�v���P�[�V�����̏��
       */
      enum class State {
        Play,   //!< ���s��
        Paused, //!< �ꎞ��~
        Quit    //!< �I��
      };
      /**
       * @brief  ��ʃT�C�Y��\���񋓌^�N���X
       */
      enum class WindowType {
        Default //!< 1920*1080(�f�t�H���g)
      };
      /**
       * @brief �R���X�g���N�^
       * 
       */
      ApplicationBase();
      /**
       * @brief �f�X�g���N�^
       */
      virtual ~ApplicationBase();
      /**
       * @brief  �A�v���P�[�V�����̏�����
       * @return �������ɐ��������ꍇ��true
       *         ���s�����ꍇ��false��Ԃ�
       */
      virtual bool Init();
      /**
       * @brief �A�v���P�[�V�����̉��
       */
      virtual void Release();
      /**
       * @brief  ���s����
       */
      virtual void Run();
      /**
       * @brief  �I������
       */
      virtual void Terminate();
      /**
       * @brief  �A�v���P�[�V�����̏I���v��
       */
      virtual void RequestTerminate();
      /**
       * @brief  �A�v���P�[�V�����̎Q�Ƃ��擾
       * @return �A�v���P�[�V�����̎Q��
       */
      static std::shared_ptr<ApplicationBase> GetInstance() {
        return _instance;
      }
      /**
       * @brief  �C���v�b�g�I�y���[�V�����̎擾
       * @return �C���v�b�g�I�y���[�V�����̎Q��
       */
      class InputOperation& GetOperation() {
        return *_input;
      }
      /**
       * @brief  ���[�h�T�[�o�̎擾
       * @return ���[�h�T�[�o�̎Q��
       */
      Mode::ModeServer& GetModeServer() {
        return *_modeServer;
      }
      /**
       * @brief  �t�@�C���T�[�o�̎擾
       * @return �t�@�C���T�[�o�̎Q��
       */
      FileServer::FileServer& GetFileServer() {
        return *_fileServer;
      }
      /**
       * @brief  �T�E���h�T�[�o�̎擾
       * @return �T�E���h�T�[�o�̎Q��
       */
      Sound::SoundServer& GetSoundServer() {
        return *_soundServer;
      }
      /**
       * @brief  �T�E���h�R���|�[�l���g�̎擾
       * @return �T�E���h�R���|�[�l���g�̎Q��
       */
      Sound::SoundComponent& GetSoundComponent();
      /**
       * @brief  ���\�[�X�T�[�o�̎擾
       * @return ���\�[�X�T�[�o�̎Q��
       */
      Resource::ResourceServer& GetResourceServer();
      /**
       * @brief  ���f���T�[�o�̎擾
       * @return ���f���T�[�o�̎Q��
       */
      Model::ModelServer& GetModelServer() const;
      /**
       * @brief  ��ʃT�C�Y�̎擾
       * @return ��ʂ̏c���Ɖ�����Ԃ�
       */
      inline const std::pair<int, int> GetWindowSize() {
        return std::make_pair(_width, _height);
      }
      /**
       * @brief  �E�B���h�E���̎擾
       * @return �E�B���h�E�T�C�Y�E�J���[�r�b�g����Ԃ�
       */
      inline const std::tuple<int, int, int> GetWidnowData() {
        return std::make_tuple(_width, _height, _colorBit);
      }
      /**
       * @brief  �o�߃t���[���擾�p�̏������z�֐�
       * @return ���݌Ăяo����Ă��郂�[�h�̃t���[���J�E���g
       */
      virtual const int GetFrameCount() const = 0;
#ifdef _DEBUG
      /**
       * @brief  �f�o�b�O�t���O�̎擾
       * @return �f�o�b�O�t���O
       */
      static inline bool GetDebugFlag() {
        return _debug;
      }
      /**
       * @brief  �f�o�b�O�t���O�̐؂�ւ�
       */
      inline void ChengeDebugFlag() {
        _debug = !_debug;
      }
#endif
    protected:
      //!< �A�v���P�[�V�����̏��
      State _state{State::Paused};
      //!< �E�B���h�E���
      static inline WindowType _windowType{WindowType::Default};
      //!< �g�p����p�[�e�B�N�����
      static inline int _particleMax{0};
      //!< �E�B���h�E�T�C�Y(��)
      static inline int _width{0};
      //!< �E�B���h�E�T�C�Y(����)
      static inline int _height{0};
      static inline int _colorBit{0};       //!< �J���[�r�b�g��
      static inline bool _setInstance{false};   //!< �����t���O
      static inline bool _windowMode{false};    //!< �E�B���h�E���[�h
      //!< �A�v���P�[�V�����̎���
      static inline std::shared_ptr<ApplicationBase> _instance{nullptr};
      //!< �t�@�C���T�[�o
      std::unique_ptr<FileServer::FileServer> _fileServer{nullptr};
      //!< �C���v�b�g�I�y���[�V����
      std::unique_ptr<InputOperation> _input{nullptr};
      //!< ���[�h�T�[�o
      std::unique_ptr<Mode::ModeServer> _modeServer{nullptr};
      //!< �T�E���h�T�[�o
      std::unique_ptr<Sound::SoundServer> _soundServer{nullptr};
      //!< �T�E���h�R���|�[�l���g
      std::unique_ptr<Sound::SoundComponent> _soundComponent{nullptr};
      //!< ���\�[�X�T�[�o
      std::unique_ptr<Resource::ResourceServer> _resourceServer{nullptr};
      //!< ���f���T�[�o
      std::unique_ptr<Model::ModelServer> _modelServer{nullptr};
#ifdef _DEBUG
      //!< �f�o�b�O�t���O
      static inline bool _debug{false};
#endif
      /**
       * @brief  ���͏���
       * @return true:�������� false:�������s
       */
      virtual bool Input();
      /**
       * @brief  �X�V����
       * @return true:�������� false:�������s
       */
      virtual bool Process();
      /**
       * @brief  �`�揈��
       * @return true:�������� false:�������s
       */
      virtual bool Draw();
      /**
       * @brief  Instance�̐������s�����̔���
       * @return true:�����Ɉڍs false:���Ɏ��̂���`����Ă���
       */
      static bool SetInstance();
      /**
       * @brief  �E�B���h�E���̐ݒ�
       * @param  window �E�B���h�E�T�C�Y���
       * @param  bit    �J���[�r�b�g����ύX���邩�̃t���O
       *                true:32�r�b�g�J���[(�f�t�H���g)  false:16�r�b�g�J���[
       */
      void SetWindowSize(const WindowType& winodw, bool bit = true);
      /**
       * @brief  �A�v���P�[�V�������I�����邩�̔���
       */
      virtual void IsQuit();
      /**
       * @brief  �J���[�r�b�g���̐ݒ�
       * @param  bit �r�b�g�J���[�t���O(true:32�r�b�g�J���[(�f�t�H���g)  false:16�r�b�g�J���[)
       * @return �Ή�����J���[�r�b�g
       */
      int ColorBit(const bool bit) const;
      /**
       * @brief  �E�B���h�E���ƈ�v�����ʃT�C�Y�̎擾
       * @return first:���� second:�c��
       */
      virtual std::pair<int, int> WindowSize() const;
      /**
       * @brief Z�o�b�t�@�̐ݒ��L���ɂ��邩
       * @param flag true:�L����(�f�t�H���g) false:�L�������Ȃ�
       */
      virtual void SetZBuffer(bool flag = true);
    };
  } // namespace Application
} // namespace AppFrame