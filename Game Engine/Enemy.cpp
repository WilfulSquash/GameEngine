#include "Enemy.h"
#include "../Engine/Engine.h"
#include "Player.h"



void Enemy::Update(float dt) {

	Player* player = m_scene->GetActorByName<Player>("Player");
	if (player) {
		nu::Vector2 direction = player->GetTransform().position - m_transform.position;
		float rotation = direction.Angle();
		SetRotation(rotation * nu::RadToDeg);

		nu::Vector2 forward{ 1, 0 };
		forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
		AddVelocity(forward * m_speed * dt);
	}

	float thrust = 0.0f;

	float rotate = 0.0f;

	//SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 forward{ 1, 0 };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
	AddVelocity(velocity * dt);

	//SetVelocity(GetVelocity() + (force * dt));
	Actor::Update(dt);
}
void Enemy::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}