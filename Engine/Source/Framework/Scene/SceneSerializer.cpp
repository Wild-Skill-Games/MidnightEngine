#include "mepch.h"
#include "SceneSerializer.h"

#include "Actor.h"
#include "Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace MidnightEngine
{
	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}
	SceneSerializer::~SceneSerializer()
	{
	}

	static void SerializeActor(YAML::Emitter& out, Actor actor)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Actor" << YAML::Value << "1234567890";

		if (actor.HasComponent<Component::Tag>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;

			auto& tag = actor.GetComponent<Component::Tag>().TagString;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Actors" << YAML::Value << YAML::BeginSeq;

		m_Scene->m_Registry.each([&](auto actorID)
			{
				Actor actor(actorID, m_Scene.get());

				if (!actor)
				{
					return;
				}
				SerializeActor(out, actor);
			});

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		// TODO : Implement
		ME_CORE_ASSERT(false, "Not implemented yet, sry");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		return false;
	}
	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		// TODO : Implement
		ME_CORE_ASSERT(false, "Not implemented yet, sry");
		return false;
	}
}