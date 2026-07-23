#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace nu {
	void Scene::AddActor(Actor* actor) { 
		actor->m_scene = this;
		m_pendingActors.push_back(actor); 
	}
	void Scene::Update(float dt) {
		//Update Actors
		for (auto actor : m_actors) {
			actor->Update(dt);
		}

		//Remove Destroyed Actors
		std::erase_if(m_actors, [](auto actor) {return actor->m_destroyed; });

		//Add Pending Actors
		m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());
		m_pendingActors.clear();
	};

	void Scene::Draw(const class Renderer& renderer) const {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}
	};
}