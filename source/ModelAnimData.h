/*****************************************************************//**
 * @file   ModelAnimData.h
 * @brief  �A�j���[�V�������N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <string>
#include <tuple>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief ���f���A�j��
   */
  namespace ModelAnim {
    /**
     * @brief �A�j���[�V�������N���X
     */
    class ModelAnimData {
    public:
      /**
       * @brief  ��̃R���X�g���N�^
       */
      ModelAnimData();
      /**
       * @brief  �R���X�g���N�^
       * @param  name  �A�j���[�V������
       * @param  frame �u�����h�t���[��
       * @param  speed �Đ����x
       * @param  loop  ���[�v�t���O(�f�t�H���g��false)
       */
      ModelAnimData(std::string_view name, const float frame, const float speed, bool loop = false);
      /**
       * @brief  �A�j���[�V�������̎擾
       * @return �A�j���[�V������
       */
      std::string AnimName() const {
        return _name;
      }
      /**
       * @brief  �u�����h�t���[���̎擾
       * @return �u�����h�t���[��
       */
      float BlendFrame() const {
        return _blendFrame;
      }
      /**
       * @brief  �Đ����x�̎擾
       * @return �Đ����x
       */
      float Speed() const {
        return _speed;
      }
      /**
       * @brief  ���[�v�t���O�̎擾
       * @return ���[�v�t���O
       */
      bool Loop() const {
        return _loop;
      }
      /**
       * @brief  �A�j���[�V�������̎擾
       * @return �A�j���[�V�������
       */
      std::tuple<std::string, float, float, bool> ModelAnim() const {
        return std::make_tuple(_name, _blendFrame, _speed, _loop);
      }
    protected:
      std::string _name; //!< �A�j���[�V������
      float _blendFrame; //!< �u�����h�t���[��
      float _speed;      //!< �Đ����x
      bool _loop;        //!< ���[�v�t���O(true:���[�v���� false:���[�v���Ȃ�)
    };
  } // namespace ModelAnim
} // namespace Gyro