#pragma once

#include <unordered_map>
#include <vector>

namespace Engine
{
    class ISystem;
    class ImGuiSystem; // For the friendship

    class SystemManager
    {
    public:
        SystemManager();
        ~SystemManager();

        std::vector<ISystem*> GetAllSystems(); // Do not use every frame
        void InitializeSystems();
        void UpdateSystems(float a_DeltaTime);

        template<typename T, typename... Targs>
        T& CreateSystem(Targs&& ... a_Args);
        template<typename T>
        T& GetSystem();
        template<typename T>
        void DeleteSystem();

    private:
        std::unordered_map<unsigned short, ISystem*> m_Systems;
        friend class ImGuiSystem;

    };

    template<typename T, typename... Targs>
    T& SystemManager::CreateSystem(Targs&& ... a_Args)
    {
        static_assert(std::is_base_of<ISystem, T>::value, "Type must derive from ISystem");

        ISystem* system = nullptr;
        if (m_Systems.find(T::ID()) == m_Systems.end())
        {
            m_Systems.emplace(T::ID(), new T(*this, std::forward<Targs>(a_Args)...));
            system = m_Systems.at(T::ID());
        }

        return *static_cast<T*>(system);
    }

    template<typename T>
    T& SystemManager::GetSystem()
    {
        static_assert(std::is_base_of<ISystem, T>::value, "Type must derive from ISystem");

        ISystem* system = nullptr;
        if (m_Systems.find(T::ID()) != m_Systems.end())
        {
            system = m_Systems.at(T::ID());
        }

        return *static_cast<T*>(system);
    }

    template<typename T>
    void SystemManager::DeleteSystem()
    {
        static_assert(std::is_base_of<ISystem, T>::value, "Type must derive from ISystem");

        if (m_Systems.find(T::ID()) != m_Systems.end())
        {
            ISystem* system = m_Systems.at(T::ID());
            m_Systems.erase(T::ID());
            delete system;
        }
    }
}
