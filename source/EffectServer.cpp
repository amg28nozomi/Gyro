/*****************************************************************//**
 * @file    EffectServer.cpp
 * @brief   �G�t�F�N�g���Ǘ�����T�[�o�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "EffectServer.h"
#include "EffectBase.h"
#include "EffectPlayerDash.h"
#include "EffectPlayerJump.h"
#include "EffectPlayerLanding.h"
#include "EffectPlayerHit.h"
#include "EffectPlayerAvoidance.h"
#include "EffectPlayerWeakAttack1.h"
#include "EffectPlayerWeakAttack2.h"
#include "EffectPlayerWeakAttack3.h"
#include "EffectPlayerWeakAttackEX.h"
#include "EffectPlayerHeavyAttack1.h"
#include "EffectPlayerHeavyAttack2.h"
#include "EffectPlayerHeavyAttack3.h"
#include "EffectPlayerAirWeakAttack1.h"
#include "EffectPlayerAirWeakAttack2.h"
#include "EffectPlayerAirWeakAttack3.h"
#include "EffectPlayerAirHeavyAttack1.h"
#include "EffectPlayerAirHeavyAttack2.h"
#include "EffectPlayerUltActivate.h"
#include "EffectPlayerUltSlash.h"
#include "EffectEnemyEyeLight.h"
#include "EffectEnemyGroundAttack1.h"
#include "EffectEnemyGroundAttack2.h"
#include "EffectEnemyAirAttack.h"
#include "EffectEnemyHit.h"
#include "EffectEnemyExprosion.h"
#include "EffectEnemyBossEyeLight.h"
#include "EffectEnemyBossGroundAttack1.h"
#include "EffectEnemyBossGroundAttack2.h"
#include "EffectEnemyBossAirAttack.h"
#include "EffectEnemyBossHit.h"
#include "EffectEnemyBossExprosion.h"
#include "EffectStageBarrier.h"
#include "EffectStageBoxDestroy.h"
#include "EffectStageHeal.h"

namespace Gyro {
  namespace Effect {
    EffectServer::EffectServer(Application::ApplicationMain& app) : AppServer::ServerTemplateVector<std::shared_ptr<EffectBase>>(), _app(app) {
#ifdef _DEBUG
      SetServerName("EffectServer");
#endif
      // �e��R���e�i���������
      ServerTemplateVector<std::shared_ptr<EffectBase>>::_registry.clear();
    }

    EffectServer::~EffectServer() {
      // �G�t�F�N�g���������
      Release();
    }

    bool EffectServer::Release() {
      // �R���e�i�̒��g���������
      for (auto effect : _registry) {
        // �G�t�F�N�g�������Ăяo��
        effect->DeadEffect();
      }
      // �R���e�i�̒��g���������
      _registry.clear();
      return true;
    }

    bool EffectServer::Process() {
      for (auto effect : _registry) {
        // ���S��Ԃ�����
        if (!effect->IsDead()) {
          effect->Process(); // �X�V�����Ăяo��
        }
      }
      // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����
      Effekseer_Sync3DSetting();
      // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����
      UpdateEffekseer3D();
      // �s�v�ɂȂ����G�t�F�N�g���폜����
      std::erase_if(_registry, [](auto&& effect) {return effect->IsDead(); });
      return true;
    }

    bool EffectServer::Draw() {
      // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��
      DrawEffekseer3D();
      return true;
    }

    void EffectServer::MakeEffect(const int num, const AppMath::Vector4 position, const float radian) {
      // �G�t�F�N�g���ʐ���
      switch (num) {
      case EffectNum::PlayerDash:
        // �v���C���[�_�b�V��
        AddEffect(PlayerDash(position, radian));
        break;
      case EffectNum::PlayerJump:
        // �v���C���[�W�����v
        AddEffect(PlayerJump(position, radian));
        break;
      case EffectNum::PlayerLanding:
        // �v���C���[���n
        AddEffect(PlayerLanding(position, radian));
        break;
      case EffectNum::PlayerHit:
        // �v���C���[��_��
        AddEffect(PlayerHit(position, radian));
        break;
      case EffectNum::PlayerAvoidance:
        // �v���C���[���
        AddEffect(PlayerAvoidance(position, radian));
        break;
      case EffectNum::PlayerWeakAttack1:
        // �v���C���[��U��1
        AddEffect(PlayerWeakAttack1(position, radian));
        break;
      case EffectNum::PlayerWeakAttack2:
        // �v���C���[��U��2
        AddEffect(PlayerWeakAttack2(position, radian));
        break;
      case EffectNum::PlayerWeakAttack3:
        // �v���C���[��U��3
        AddEffect(PlayerWeakAttack3(position, radian));
        break;
      case EffectNum::PlayerWeakAttackEX:
        // �v���C���[��U��EX
        AddEffect(PlayerWeakAttackEX(position, radian));
        break;
      case EffectNum::PlayerHeavyAttack1:
        // �v���C���[���U��1
        AddEffect(PlayerHeavyAttack1(position, radian));
        break;
      case EffectNum::PlayerHeavyAttack2:
        // �v���C���[���U��2
        AddEffect(PlayerHeavyAttack2(position, radian));
        break;
      case EffectNum::PlayerHeavyAttack3:
        // �v���C���[���U��3
        AddEffect(PlayerHeavyAttack3(position, radian));
        break;
      case EffectNum::PlayerAirWeakAttack1:
        // �v���C���[�󒆎�U��1
        AddEffect(PlayerAirWeakAttack1(position, radian));
        break;
      case EffectNum::PlayerAirWeakAttack2:
        // �v���C���[�󒆎�U��2
        AddEffect(PlayerAirWeakAttack2(position, radian));
        break;
      case EffectNum::PlayerAirWeakAttack3:
        // �v���C���[�󒆎�U��3
        AddEffect(PlayerAirWeakAttack3(position, radian));
        break;
      case EffectNum::PlayerAirHeavyAttack1:
        // �v���C���[�󒆋��U��1
        AddEffect(PlayerAirHeavyAttack1(position, radian));
        break;
      case EffectNum::PlayerAirHeavyAttack2:
        // �v���C���[�󒆋��U��2
        AddEffect(PlayerAirHeavyAttack2(position, radian));
        break;
      case EffectNum::PlayerUltActivate:
        // �v���C���[�K�E����
        AddEffect(PlayerUltActivate(position, radian));
        break;
      case EffectNum::PlayerUltSlash:
        // �v���C���[�K�E�U��
        AddEffect(PlayerUltSlash(position, radian));
        SetUltSlashEnd(false);
        break;
      case EffectNum::EnemyEyeLight:
        // �G���
        AddEffect(EnemyEyeLight(position, radian));
        break;
      case EffectNum::EnemyGroundAttack1:
        // �G�n��U��1
        AddEffect(EnemyGroundAttack1(position, radian));
        break;
      case EffectNum::EnemyGroundAttack2:
        // �G�n��U��2
        AddEffect(EnemyGroundAttack2(position, radian));
        break;
      case EffectNum::EnemyAirAttack:
        // �G�󒆍U��
        AddEffect(EnemyAirAttack(position, radian));
        break;
      case EffectNum::EnemyHit:
        // �G��_��
        AddEffect(EnemyHit(position, radian));
        break;
      case EffectNum::EnemyExprosion:
        // �G����
        AddEffect(EnemyExprosion(position, radian));
        break;
      case EffectNum::EnemyBossEyeLight:
        // �G�{�X���
        AddEffect(EnemyBossEyeLight(position, radian));
        break;
      case EffectNum::EnemyBossGroundAttack1:
        // �G�{�X�n��U��1
        AddEffect(EnemyBossGroundAttack1(position, radian));
        break;
      case EffectNum::EnemyBossGroundAttack2:
        // �G�{�X�n��U��2
        AddEffect(EnemyBossGroundAttack2(position, radian));
        break;
      case EffectNum::EnemyBossAirAttack:
        // �G�{�X�󒆍U��
        AddEffect(EnemyBossAirAttack(position, radian));
        break;
      case EffectNum::EnemyBossHit:
        // �G�{�X��_��
        AddEffect(EnemyBossHit(position, radian));
        break;
      case EffectNum::EnemyBossExprosion:
        // �G�{�X����
        AddEffect(EnemyBossExprosion(position, radian));
        break;
      case EffectNum::StageBarrier:
        // �X�e�[�W�o���A
        AddEffect(StageBarrier(position, radian));
        break;
      case EffectNum::StageBoxDestroy:
        // �X�e�[�W���j��
        AddEffect(StageBoxDestroy(position, radian));
        break;
      case EffectNum::StageHeal:
        // �X�e�[�W��
        AddEffect(StageHeal(position, radian));
        break;
      default:
#ifdef _DEBUG
        throw ("�G�t�F�N�g���ʔԍ�������܂���");
#endif
        break;
      }
    }

    void EffectServer::AddEffect(std::shared_ptr<EffectBase> effect) {
      // �G�t�F�N�g��null�̏ꍇ�G���[
      if (effect == nullptr) {
#ifdef _DEBUG
        throw ("�G�t�F�N�g��nullptr�ł�");
#endif
        return;
      }
      // �o�^
      _registry.emplace_back(std::move(effect));
    }

    std::shared_ptr<EffectPlayerDash> EffectServer::PlayerDash(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�_�b�V���̐���
      auto playerDash = std::make_shared<EffectPlayerDash>(_app);
      // �ʒu�E�����ݒ�
      playerDash->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerDash);
    }

    std::shared_ptr<EffectPlayerJump> EffectServer::PlayerJump(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�W�����v�̐���
      auto playerJump = std::make_shared<EffectPlayerJump>(_app);
      // �ʒu�E�����ݒ�
      playerJump->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerJump);
    }

    std::shared_ptr<EffectPlayerLanding> EffectServer::PlayerLanding(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[���n�̐���
      auto playerLanding = std::make_shared<EffectPlayerLanding>(_app);
      // �ʒu�E�����ݒ�
      playerLanding->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerLanding);
    }

    std::shared_ptr<EffectPlayerHit> EffectServer::PlayerHit(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[��_���̐���
      auto playerHit = std::make_shared<EffectPlayerHit>(_app);
      // �ʒu�E�����ݒ�
      playerHit->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerHit);
    }

    std::shared_ptr<EffectPlayerAvoidance> EffectServer::PlayerAvoidance(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[����̐���
      auto playerAvoidance = std::make_shared<EffectPlayerAvoidance>(_app);
      // �ʒu�E�����ݒ�
      playerAvoidance->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerAvoidance);
    }

    std::shared_ptr<EffectPlayerWeakAttack1> EffectServer::PlayerWeakAttack1(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[��U��1�̐���
      auto playerWeakAttack1 = std::make_shared<EffectPlayerWeakAttack1>(_app);
      // �ʒu�E�����ݒ�
      playerWeakAttack1->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerWeakAttack1);
    }

    std::shared_ptr<EffectPlayerWeakAttack2> EffectServer::PlayerWeakAttack2(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[��U��2�̐���
      auto playerWeakAttack2 = std::make_shared<EffectPlayerWeakAttack2>(_app);
      // �ʒu�E�����ݒ�
      playerWeakAttack2->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerWeakAttack2);
    }

    std::shared_ptr<EffectPlayerWeakAttack3> EffectServer::PlayerWeakAttack3(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[��U��3�̐���
      auto playerWeakAttack3 = std::make_shared<EffectPlayerWeakAttack3>(_app);
      // �ʒu�E�����ݒ�
      playerWeakAttack3->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerWeakAttack3);
    }

    std::shared_ptr<EffectPlayerWeakAttackEX> EffectServer::PlayerWeakAttackEX(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[��U��EX�̐���
      auto playerWeakAttackEX = std::make_shared<EffectPlayerWeakAttackEX>(_app);
      // �ʒu�E�����ݒ�
      playerWeakAttackEX->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerWeakAttackEX);
    }

    std::shared_ptr<EffectPlayerHeavyAttack1> EffectServer::PlayerHeavyAttack1(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[���U��1�̐���
      auto playerHeavyAttack1 = std::make_shared<EffectPlayerHeavyAttack1>(_app);
      // �ʒu�E�����ݒ�
      playerHeavyAttack1->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerHeavyAttack1);
    }

    std::shared_ptr<EffectPlayerHeavyAttack2> EffectServer::PlayerHeavyAttack2(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[���U��2�̐���
      auto playerHeavyAttack2 = std::make_shared<EffectPlayerHeavyAttack2>(_app);
      // �ʒu�E�����ݒ�
      playerHeavyAttack2->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerHeavyAttack2);
    }

    std::shared_ptr<EffectPlayerHeavyAttack3> EffectServer::PlayerHeavyAttack3(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[���U��3�̐���
      auto playerHeavyAttack3 = std::make_shared<EffectPlayerHeavyAttack3>(_app);
      // �ʒu�E�����ݒ�
      playerHeavyAttack3->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerHeavyAttack3);
    }

    std::shared_ptr<EffectPlayerAirWeakAttack1> EffectServer::PlayerAirWeakAttack1(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�󒆎�U��1�̐���
      auto playerAirWeakAttack1 = std::make_shared<EffectPlayerAirWeakAttack1>(_app);
      // �ʒu�E�����ݒ�
      playerAirWeakAttack1->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerAirWeakAttack1);
    }

    std::shared_ptr<EffectPlayerAirWeakAttack2> EffectServer::PlayerAirWeakAttack2(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�󒆎�U��2�̐���
      auto playerAirWeakAttack2 = std::make_shared<EffectPlayerAirWeakAttack2>(_app);
      // �ʒu�E�����ݒ�
      playerAirWeakAttack2->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerAirWeakAttack2);
    }

    std::shared_ptr<EffectPlayerAirWeakAttack3> EffectServer::PlayerAirWeakAttack3(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�󒆎�U��3�̐���
      auto playerAirWeakAttack3 = std::make_shared<EffectPlayerAirWeakAttack3>(_app);
      // �ʒu�E�����ݒ�
      playerAirWeakAttack3->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerAirWeakAttack3);
    }

    std::shared_ptr<EffectPlayerAirHeavyAttack1> EffectServer::PlayerAirHeavyAttack1(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�󒆋��U��1�̐���
      auto playerAirHeavyAttack1 = std::make_shared<EffectPlayerAirHeavyAttack1>(_app);
      // �ʒu�E�����ݒ�
      playerAirHeavyAttack1->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerAirHeavyAttack1);
    }

    std::shared_ptr<EffectPlayerAirHeavyAttack2> EffectServer::PlayerAirHeavyAttack2(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�󒆋��U��2�̐���
      auto playerAirHeavyAttack2 = std::make_shared<EffectPlayerAirHeavyAttack2>(_app);
      // �ʒu�E�����ݒ�
      playerAirHeavyAttack2->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerAirHeavyAttack2);
    }

    std::shared_ptr<EffectPlayerUltActivate> EffectServer::PlayerUltActivate(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�K�E�����̐���
      auto playerUltActivate = std::make_shared<EffectPlayerUltActivate>(_app);
      // �ʒu�E�����ݒ�
      playerUltActivate->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerUltActivate);
    }

    std::shared_ptr<EffectPlayerUltSlash> EffectServer::PlayerUltSlash(const AppMath::Vector4 position, const float radian) const {
      // �v���C���[�K�E�U���̐���
      auto playerUltSlash = std::make_shared<EffectPlayerUltSlash>(_app);
      // �ʒu�E�����ݒ�
      playerUltSlash->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(playerUltSlash);
    }

    std::shared_ptr<EffectEnemyEyeLight> EffectServer::EnemyEyeLight(const AppMath::Vector4 position, const float radian) const {
      // �G����̐���
      auto enemyEyeLight = std::make_shared<EffectEnemyEyeLight>(_app);
      // �ʒu�E�����ݒ�
      enemyEyeLight->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyEyeLight);
    }

    std::shared_ptr<EffectEnemyGroundAttack1> EffectServer::EnemyGroundAttack1(const AppMath::Vector4 position, const float radian) const {
      // �G�n��U��1�̐���
      auto enemyGroundAttack1 = std::make_shared<EffectEnemyGroundAttack1>(_app);
      // �ʒu�E�����ݒ�
      enemyGroundAttack1->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyGroundAttack1);
    }

    std::shared_ptr<EffectEnemyGroundAttack2> EffectServer::EnemyGroundAttack2(const AppMath::Vector4 position, const float radian) const {
      // �G�n��U��2�̐���
      auto enemyGroundAttack2 = std::make_shared<EffectEnemyGroundAttack2>(_app);
      // �ʒu�E�����ݒ�
      enemyGroundAttack2->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyGroundAttack2);
    }

    std::shared_ptr<EffectEnemyAirAttack> EffectServer::EnemyAirAttack(const AppMath::Vector4 position, const float radian) const {
      // �G�󒆍U���̐���
      auto enemyAirAttack = std::make_shared<EffectEnemyAirAttack>(_app);
      // �ʒu�E�����ݒ�
      enemyAirAttack->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyAirAttack);
    }

    std::shared_ptr<EffectEnemyHit> EffectServer::EnemyHit(const AppMath::Vector4 position, const float radian) const {
      // �G��_���̐���
      auto enemyHit = std::make_shared<EffectEnemyHit>(_app);
      // �ʒu�E�����ݒ�
      enemyHit->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyHit);
    }

    std::shared_ptr<EffectEnemyExprosion> EffectServer::EnemyExprosion(const AppMath::Vector4 position, const float radian) const {
      // �G�����̐���
      auto enemyExprosion = std::make_shared<EffectEnemyExprosion>(_app);
      // �ʒu�E�����ݒ�
      enemyExprosion->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyExprosion);
    }

    std::shared_ptr<EffectEnemyBossEyeLight> EffectServer::EnemyBossEyeLight(const AppMath::Vector4 position, const float radian) const {
      // �G�{�X����̐���
      auto enemyBossEyeLight = std::make_shared<EffectEnemyBossEyeLight>(_app);
      // �ʒu�E�����ݒ�
      enemyBossEyeLight->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyBossEyeLight);
    }

    std::shared_ptr<EffectEnemyBossGroundAttack1> EffectServer::EnemyBossGroundAttack1(const AppMath::Vector4 position, const float radian) const {
      // �G�{�X�n��U��1�̐���
      auto enemyBossGroundAttack1 = std::make_shared<EffectEnemyBossGroundAttack1>(_app);
      // �ʒu�E�����ݒ�
      enemyBossGroundAttack1->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyBossGroundAttack1);
    }

    std::shared_ptr<EffectEnemyBossGroundAttack2> EffectServer::EnemyBossGroundAttack2(const AppMath::Vector4 position, const float radian) const {
      // �G�{�X�n��U��2�̐���
      auto enemyBossGroundAttack2 = std::make_shared<EffectEnemyBossGroundAttack2>(_app);
      // �ʒu�E�����ݒ�
      enemyBossGroundAttack2->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyBossGroundAttack2);
    }

    std::shared_ptr<EffectEnemyBossAirAttack> EffectServer::EnemyBossAirAttack(const AppMath::Vector4 position, const float radian) const {
      // �G�{�X�󒆍U���̐���
      auto enemyBossAirAttack = std::make_shared<EffectEnemyBossAirAttack>(_app);
      // �ʒu�E�����ݒ�
      enemyBossAirAttack->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyBossAirAttack);
    }

    std::shared_ptr<EffectEnemyBossHit> EffectServer::EnemyBossHit(const AppMath::Vector4 position, const float radian) const {
      // �G�{�X��_���̐���
      auto enemyBossHit = std::make_shared<EffectEnemyBossHit>(_app);
      // �ʒu�E�����ݒ�
      enemyBossHit->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyBossHit);
    }

    std::shared_ptr<EffectEnemyBossExprosion> EffectServer::EnemyBossExprosion(const AppMath::Vector4 position, const float radian) const {
      // �G�{�X�����̐���
      auto enemyBossExprosion = std::make_shared<EffectEnemyBossExprosion>(_app);
      // �ʒu�E�����ݒ�
      enemyBossExprosion->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(enemyBossExprosion);
    }

    std::shared_ptr<EffectStageBarrier> EffectServer::StageBarrier(const AppMath::Vector4 position, const float radian) const {
      // �X�e�[�W�o���A�̐���
      auto stageBarrier = std::make_shared<EffectStageBarrier>(_app);
      // �ʒu�E�����ݒ�
      stageBarrier->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(stageBarrier);
    }

    std::shared_ptr<EffectStageBoxDestroy> EffectServer::StageBoxDestroy(const AppMath::Vector4 position, const float radian) const {
      // �X�e�[�W���j��̐���
      auto stageBoxDestroy = std::make_shared<EffectStageBoxDestroy>(_app);
      // �ʒu�E�����ݒ�
      stageBoxDestroy->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(stageBoxDestroy);
    }

    std::shared_ptr<EffectStageHeal> EffectServer::StageHeal(const AppMath::Vector4 position, const float radian) const {
      // �X�e�[�W�񕜂̐���
      auto stageHeal = std::make_shared<EffectStageHeal>(_app);
      // �ʒu�E�����ݒ�
      stageHeal->SetEffectParameter(position, radian);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(stageHeal);
    }
  } // namespace Effect
} // namespace Gyro