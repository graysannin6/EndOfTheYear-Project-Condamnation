#pragma once

#include <tinyxml2.h>

using namespace tinyxml2;

namespace Core::Interface
{
    class ISerializable
    {
	public :
		virtual ~ISerializable() = default;

		virtual void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept = 0;
		virtual void Deserialize(XMLElement* p_compSegment) const noexcept = 0;
    };
}