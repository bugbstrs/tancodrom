#include "SceneObject.h"

class Wall : public SceneObject
{
public:
	Wall(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation, int wallType);

	void Update() override;

	void TakeDamage(float damage);

	void Render(Shader& shader) override;
private:
	float m_health = 100.f;

	static Model* wallModel;
};