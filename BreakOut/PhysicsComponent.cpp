#include "PhysicsComponent.h"
#include "SoundManager.h"
#include "UBall.h"
#include "UPlayer.h"
#include "UBlock.h"
#include "../States/InGameState.h"


PhysicsComponent::PhysicsComponent(UObject* InOwner, FRect Incollider, FRect Inboundary) : collider(Incollider), boundary(Inboundary)
{
	owner = InOwner;

	Vector2 newCenter = Vector2(owner->GetLocation().x, owner->GetLocation().y);
	collider.SetCenter(newCenter);
}

void PhysicsComponent::SetVelocity(Vector3 newVelocity)
{
	velocity = newVelocity;
}

Vector3 PhysicsComponent::GetVelocity() const
{
	return velocity;
}


void PhysicsComponent::Update(double deltaTime)
{


	UpdateLocation(deltaTime);
	CheckBoundaryCollision();
}

void PhysicsComponent::UpdateLocation(double deltaTime)
{
	Vector3 newLocation = owner->GetLocation();
	newLocation.x += velocity.x * static_cast<float>(deltaTime);
	newLocation.y += velocity.y * static_cast<float>(deltaTime);
	owner->SetLocation(newLocation);
	Vector2 newCenter = Vector2(owner->GetLocation().x, owner->GetLocation().y);
	collider.SetCenter(newCenter);

}

Vector2 PhysicsComponent::CalculateOverlap(const FRect& collider, const FRect& otherCollider, const Vector3& objectLocation, const Vector3& otherObjectLocation)
{
	float overlapX = 0.0f;
	if (collider._max.x > otherCollider._min.x && collider._min.x < otherCollider._max.x)
	{
		if (objectLocation.x > otherObjectLocation.x)
		{
			overlapX = collider._min.x - otherCollider._max.x;
		}
		else
		{
			overlapX = collider._max.x - otherCollider._min.x;
		}
	}

	float overlapY = 0.0f;
	if (collider._max.y > otherCollider._min.y && collider._min.y < otherCollider._max.y)
	{
		if (objectLocation.y > otherObjectLocation.y)
		{
			overlapY = collider._min.y - otherCollider._max.y;
		}
		else
		{
			overlapY = collider._max.y - otherCollider._min.y;
		}
	}

	return Vector2(overlapX, overlapY);
}

bool PhysicsComponent::CheckCollision(const PhysicsComponent* other)
{
	return collider.Intersects(other->GetColliderBounds());
}

void PhysicsComponent::OnCollision(const PhysicsComponent* other)
{
	if (owner->GetType() != FObjectType::Ball)
		return;

	UBall* ball = static_cast<UBall*>(owner);
	UObject* otherObject = other->GetOwner();
	const FRect& otherCollider = other->GetColliderBounds();

	//물체가 파고들었는지 감지
	Vector2 overlap = CalculateOverlap(collider, otherCollider, ball->GetLocation(), otherObject->GetLocation());

	Vector3 newBallLocation = ball->GetLocation();
	Vector3 newBallVelocity = GetVelocity();

	//교정
	if (fabs(overlap.x) < fabs(overlap.y))
	{
		newBallLocation.x -= overlap.x;
	}
	else
	{
		newBallLocation.y -= overlap.y;
	}

	if (otherObject->GetType() == FObjectType::Player)
	{
		UPlayer* player = static_cast<UPlayer*>(otherObject);

		float ballCenterX = newBallLocation.x;
		float playerCenterX = player->GetLocation().x;

		float playerHalfWidth = player->GetScale().x;

		float relativeIntersectX = (ballCenterX - playerCenterX) / playerHalfWidth;
		Vector3 newDirection(relativeIntersectX, 0.3f, 0.0f);

		newBallVelocity = newDirection;
		newBallVelocity.Normalize();
		SoundManager::GetInstance()->PlaySFX(SOUND_KEY_PING_PONG);
	}

	if (otherObject->GetType() == FObjectType::Block)
	{
		UBlock* block = static_cast<UBlock*>(otherObject);
		
		float ballCenterX = newBallLocation.x;
		float blockCenterX = block->GetLocation().x;

		float blockHalfWidth = block->GetScale().x;

		float relativeIntersectX = (ballCenterX - blockCenterX) / blockHalfWidth;
		Vector3 newDirection(relativeIntersectX, -0.3f,0.0f);

		newBallVelocity = newDirection;
		newBallVelocity.Normalize();


		InGameState* ingameState = static_cast<InGameState*>(UApp::Ins->GetCurrentState());
		ingameState->AddScore(1);
		block->isActive = false;
		SoundManager::GetInstance()->PlaySFX(SOUND_KEY_PING_PONG);

	}

	ball->SetLocation(newBallLocation);
	SetVelocity(newBallVelocity);
}


void PhysicsComponent::CheckBoundaryCollision()
{
	// 1. 현재 콜라이더 범위와 위치, 속도를 미리 가져옵니다.
	Vector2 colliderMin = collider._min;
	Vector2 colliderMax = collider._max;

	Vector3 currentLoc = owner->GetLocation();
	Vector3 currentVel = this->GetVelocity(); // (주의: 실제 컴포넌트의 속도 변수명에 맞게 수정하세요)

	bool bIsCollided = false;

	// 2. X축 (좌우 벽) 충돌 검사
	if (colliderMin.x < boundary._min.x)
	{
		currentLoc.x = boundary._min.x + collider.GetWidth() / 2.0f; // 위치 보정
		currentVel.x *= -1.0f; // 속도 반전 (왼쪽 벽에 맞았으니 오른쪽으로 튕김)
		bIsCollided = true;
	}
	else if (colliderMax.x > boundary._max.x)
	{
		currentLoc.x = boundary._max.x - collider.GetWidth() / 2.0f;
		currentVel.x *= -1.0f; // 속도 반전 (오른쪽 벽에 맞았으니 왼쪽으로 튕김)
		bIsCollided = true;
	}

	// 3. Y축 (상하 벽) 충돌 검사
	if (colliderMin.y < boundary._min.y)
	{
		currentLoc.y = boundary._min.y + collider.GetHeight() / 2.0f;
		currentVel.y *= -1.0f; // 천장에 맞았으니 아래로 튕김
		bIsCollided = true;
	}
	else if (colliderMax.y > boundary._max.y)
	{
		currentLoc.y = boundary._max.y - collider.GetHeight() / 2.0f;
		currentVel.y *= -1.0f; // 바닥에 맞았으니 위로 튕김 (보통 바닥에 닿으면 게임 오버 처리를 하기도 합니다)
		bIsCollided = true;
	}

	// 4. 충돌이 발생했을 때만 최종적으로 위치와 속도를 한 번에 갱신합니다.
	if (bIsCollided)
	{
		owner->SetLocation(currentLoc);
		this->SetVelocity(currentVel); // 튕겨나가는 속도 적용

		Vector2 newCenter = { currentLoc.x, currentLoc.y };
		collider.SetCenter(newCenter);
	}
}

bool PhysicsComponent::isGrouned(float groundEpsilon)
{


	return (fabs(collider._min.y - boundary._min.y) < groundEpsilon);
}


