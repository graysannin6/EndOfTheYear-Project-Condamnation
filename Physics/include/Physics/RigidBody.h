#pragma once

#include <vector>

#include <glm/ext.hpp>

#include <Physics/Export.h>

namespace Physics
{
    class API_PHYSICS RigidBody
    {
    public:
		RigidBody() = default;
		RigidBody(glm::vec3& p_pos);
        ~RigidBody() = default;

		[[nodiscard]] glm::vec3& GetPosition();

		void SetPosition(const glm::vec3& p_pos);

        void SetMaxX(const float value) { maxX = value; }
        void SetMaxY(const float value) { maxY = value; }
        void SetMaxZ(const float value) { maxZ = value; }

        void SetMinX(const float value) { minX = value; }
        void SetMinY(const float value) { minY = value; }
        void SetMinZ(const float value) { minZ = value; }

        float& GetMaxX() { return maxX; }
        float& GetMaxY() { return maxY; }
        float& GetMaxZ() { return maxZ; }

        float& GetMinX() { return minX; }
        float& GetMinY() { return minY; }
        float& GetMinZ() { return minZ; }

    private:
        glm::vec3 m_position;
        float maxX{97};
        float minX{-97};
        float maxY{40};
        float minY{0.5f};
        float maxZ{97};
        float minZ{-97};

    };
}

