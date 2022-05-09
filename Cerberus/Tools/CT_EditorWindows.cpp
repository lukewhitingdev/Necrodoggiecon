#include "CT_EditorWindows.h"
#include "Environment/CWorld_Edit.h"



void CT_EditorWindows::render()
{

    {
        if (*open)
        {

           
            ImGui::SetNextWindowSize(ImVec2(WindowScale.x, WindowScale.y), ImGuiCond_FirstUseEver);
            if (!ImGui::Begin(WindowTitle, open))
            {

                ImGui::End();
                return;
            }


           
            if (ImGui::GetIO().WantCaptureMouse)
            {
               
                CWorld_Editable::ToggleCellQueueLock(true);
            }
            else
            {

              
                CWorld_Editable::ToggleCellQueueLock(false);
            }


            if (ImGui::TreeNode("Grid Manipulation"))
            {
                if (ImGui::Button("Add Walkable (Box)"))
                {
                    CWorld_Editable::SetOperationMode(EditOperationMode::Subtractive);
                    CWorld_Editable::ClearQueue();
                }
                if (ImGui::Button("Add Wall (Box)"))
                {
                    CWorld_Editable::SetOperationMode(EditOperationMode::Additive);
                    CWorld_Editable::ClearQueue();
                }
                if (ImGui::Button("Add Walkable (Single)"))
                {
                    CWorld_Editable::SetOperationMode(EditOperationMode::Subtractive_Single);
                    CWorld_Editable::ClearQueue();
                }
                if (ImGui::Button("Add Wall (Single)"))
                {
                    CWorld_Editable::SetOperationMode(EditOperationMode::Additive_Single);
                    CWorld_Editable::ClearQueue();
                }
                if (ImGui::Button("None"))
                {
                    CWorld_Editable::SetOperationMode(EditOperationMode::None);
                    CWorld_Editable::ClearQueue();
                }

                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Debug"))
            {
                if (ImGui::Button("Toggle Debug"))
                {
                    CWorld_Editable::ToggleDebugMode(!debugModeToggle);
                    debugModeToggle = !debugModeToggle;
                }
                ImGui::TreePop();
            }


            if (ImGui::TreeNode("Utility"))
            {
                if (ImGui::Button("Clear Grid"))
                {
                    CWorld_Editable::PerformOperation_ClearSpace();
                    CWorld_Editable::ClearQueue();
                }
              

                ImGui::TreePop();
            }
           


            if (ImGui::Button("Save"))
            {
                CWorld_Editable::SaveWorld(0);
            }

            //AdditionalRenderLogic(*open);

            ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetStyle().ItemSpacing.y), false, ImGuiWindowFlags_HorizontalScrollbar);
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Clear")) ClearLog();
                ImGui::EndPopup();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            for (int i = 0; i < Items.Size; i++)
            {
                const char* item = Items[i];
                if (!Filter.PassFilter(item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                ImVec4 color;
                bool has_color = false;
                if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
                else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item);
                if (has_color)
                    ImGui::PopStyleColor();
            }

            if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            ImGui::PopStyleVar();
            ImGui::EndChild();

            // Auto-focus on window apparition
            ImGui::SetItemDefaultFocus();

            ImGui::End();




            ImGui::SetNextWindowSize(ImVec2(WindowScale.x, WindowScale.y), ImGuiCond_FirstUseEver);
            if (!ImGui::Begin("Content", open))
            {

                ImGui::End();
                return;
            }

            if (ImGui::TreeNode("Decoration"))
            {
                int ItemCount = 5;
                for (int i = 0; i < ItemCount; i++)
                {
                    if (ImGui::Button("Slot " + i))
                    {

                    }
                }


                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Gameplay Controllers"))
            {
                if (ImGui::Button("Player Start"))
                {

                }
               
                if (ImGui::Button("Item Holder"))
                {

                }

                if (ImGui::Button("Goal"))
                {

                }
                ImGui::TreePop();
            }



            ImGui::End();

            ImGui::SetNextWindowSize(ImVec2(WindowScale.x, WindowScale.y), ImGuiCond_FirstUseEver);
            if (!ImGui::Begin("Details", open))
            {

                ImGui::End();
                return;
            }

           



            ImGui::End();

        }

    }
}
