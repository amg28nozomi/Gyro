/*****************************************************************//**
 * @file   StageData.h
 * @brief  �X�e�[�W���N���X
 * 
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <tuple>
#include <string>
#include <appframe.h>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �X�e�[�W
   */
  namespace Stage {
    namespace AppMath = AppFrame::Math;
    class StageData {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param filename �t�@�C����
       * @param position ���W
       * @param ratation ��]
       * @param scale    �g�嗦
       */
      StageData(std::string filename, AppMath::Vector4 position, AppMath::Vector4 rotation, AppMath::Vector4 scale) : 
          _fileName(filename), _position(position), _rotation(rotation), _scale(scale) {
      };
      /**
       * @brief �R���X�g���N�^
       */
      StageData ();
      /**
       * @brief �f�X�g���N�^
       */
      ~StageData () = default;
      /**
       * @brief  �t�@�C�����̎擾
       * @return �t�@�C����
       */
      std::string_view FileName() const {
          return _fileName;
      }
      /**
       * @brief  �X�e�[�W���̎擾
       * @return ���W�A��]�A�g�嗦
       */
      std::tuple<AppMath::Vector4, AppMath::Vector4, AppMath::Vector4> GetStageParam() const {
          return { _position, _rotation, _scale };
      }
    private:
      std::string _fileName;      //!< �t�@�C����
      AppMath::Vector4 _position; //!< ���W
      AppMath::Vector4 _rotation; //!< ��](Debug:�f�O���[ Release:���W�A��)
      AppMath::Vector4 _scale;    //!< �g�嗦
    };
  } // Stage
} // Gyro