/*****************************************************************//**
 * @file   PrimitiveBase.cpp
 * @brief  �v���~�e�B�u�̃X�[�p�[�N���X�̒�`
 * 
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#include "PrimitiveBase.h"

namespace {
    constexpr auto DEGREE_TO_RADIAN = DX_PI_F / 180.0f;
    MATRIX Identity = MGetIdent();
}

namespace Gyro {
    namespace Primitive {

        PrimitiveBase::PrimitiveBase() {
            _handle = -1;
            /*_vertexNum = 0;
            _indexNum = 0;
            _polygonNum = 0;*/

            _vertex.reset(new std::vector<VERTEX3D>());
            _index.reset(new std::vector<unsigned short>());
        }

        PrimitiveBase::~PrimitiveBase() {
            _vertex->clear();
            _index->clear();
        }

        bool PrimitiveBase::Load(const TCHAR* fileName) {
            UnLoad();

            _handle = LoadGraph(fileName);

            return (-1 != _handle);
        }

        bool PrimitiveBase::UnLoad() {
            if (-1 == _handle) {
                return false;
            }

            return (-1 != DeleteGraph(_handle));
        }

        void PrimitiveBase::Process() {
            /*_vertexNum = static_cast<int>(_vertex->size());
            _indexNum = static_cast<int>(_index->size());
            _polygonNum = _indexNum / 3;*/
        }

        bool PrimitiveBase::Render() {
            auto vertexNum = static_cast<int>(_vertex->size());
            auto indexNum = static_cast<int>(_index->size());

            // �|���S�����P��������Ε`�悵�Ȃ�
            if (3 > vertexNum || 3 > indexNum) {
                return false;
            }

            auto polygonNum = indexNum / 3;
            auto useHandle = (_handle == -1) ? DX_NONE_GRAPH : _handle;

            //SetTransformToWorld(&_posture); // �p������p�̂��ߌ��݃R�����g�A�E�g

            DrawPolygonIndexed3D(_vertex->data(), vertexNum, _index->data(), polygonNum, useHandle, FALSE);
            //SetTransformToWorld(&Identity);

            return true;
        }
    }// namespace Primitive
}// namespace Gyro
