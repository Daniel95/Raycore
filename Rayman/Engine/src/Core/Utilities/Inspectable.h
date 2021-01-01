#pragma once

#include <rttr/registration>

#include <string>
#include <vector>

namespace Engine
{
    struct SubInspectable
    {
    public:
        SubInspectable() = delete; // Forces specialized constructor
        SubInspectable(std::string a_Name, bool* a_IsEnabled)
        { 
            m_Name = a_Name;
            m_IsEnabled = a_IsEnabled;
        };
        ~SubInspectable() { };

        inline std::string GetName() { return m_Name; };
        inline const bool* GetEnabled() { return m_IsEnabled; };
        inline void ToggleEnabled() { *m_IsEnabled = !(*m_IsEnabled); };

    private:
        std::string m_Name;
        bool* m_IsEnabled;

    };

    class Inspectable
    {
        RTTR_ENABLE();

    public:
        Inspectable() { };
        ~Inspectable() { };

        // Function that needs to be implemented if this optional class in inherited
        virtual void Inspect() = 0;

        inline const std::vector<SubInspectable>& GetAllInspectables() { return m_SubInspectables; };

    protected:
        std::vector<SubInspectable> m_SubInspectables;

    };
}
