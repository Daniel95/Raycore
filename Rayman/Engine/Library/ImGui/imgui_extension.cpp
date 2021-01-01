#include <imgui_extension.h>

#include <imgui.h>

namespace ImGui
{
    static int ImGuiTextInputCallback(ImGuiInputTextCallbackData* a_Data)
    {
        if (a_Data->EventFlag == ImGuiInputTextFlags_CallbackResize) // Resize string callback
        {
            std::string* str = (std::string*) a_Data->UserData;
            IM_ASSERT(a_Data->Buf == str->c_str());
            str->resize(a_Data->BufTextLen);
            a_Data->Buf = (char*) str->c_str();
        }

        return 0;
    }

    IMGUI_API bool InputText(std::string a_Label, std::string& a_Buffer, ImGuiInputTextFlags a_Flags)
    {
        return InputText(a_Label.c_str(), a_Buffer, a_Flags);
    }

    IMGUI_API bool InputText(const char* a_Label, std::string& a_Buffer, ImGuiInputTextFlags a_Flags)
    {
        bool returnInputText = false;
        if ((a_Flags & ImGuiInputTextFlags_CallbackResize) == ImGuiInputTextFlags_CallbackResize)
        {
            returnInputText = InputText(a_Label, &a_Buffer[0], a_Buffer.capacity(), a_Flags, ImGuiTextInputCallback, (void*) &a_Buffer);
        }
        else
        {
            returnInputText = InputText(a_Label, &a_Buffer[0], a_Buffer.capacity(), a_Flags);
        }

        return returnInputText;
    }
}