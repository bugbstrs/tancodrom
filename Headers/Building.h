#include "SceneObject.h"

class Building : public SceneObject
{
public:
	Building(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

	void TakeDamage(float damage);
private:
	float m_health = 80.0f;

	static Model* damagedModel;
	static Model* buildingModel;
};