#pragma once
#include "Transform.h"

namespace nu {
    class Actor {
    public:
        Actor() = default;
        Actor(const Transform& transform) : m_transform{ transform } { };

        void Update(float dt);
        void Draw(class Renderer& renderer) const;

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.rotation = scale; }

        const Vector2& GetVelocity() const { return m_velocity; }
        const Vector2& SetVelocity(const Vector2& velocity) { return m_velocity = velocity; }
    protected:
        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
    };
}