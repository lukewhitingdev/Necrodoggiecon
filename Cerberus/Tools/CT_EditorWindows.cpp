#include "CT_EditorWindows.h"
#include "Environment/CWorld_Edit.h"
#include "CWorldManager.h"



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
               
                CWorldManager::GetEditorWorld()->ToggleCellQueueLock(true);
            }
            else
            {

              
                CWorldManager::GetEditorWorld()->ToggleCellQueueLock(false);
            }


            if (ImGui::TreeNode("Grid Manipulation"))
            {
                if (ImGui::Button("Add Walkable (Box)"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Subtractive);
                    CWorldManager::GetEditorWorld()->ClearQueue();
                }
                if (ImGui::Button("Add Wall (Box)"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Additive);
                    CWorldManager::GetEditorWorld()->ClearQueue();
                }
                if (ImGui::Button("Add Walkable (Single)"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Subtractive_Single);
                    CWorldManager::GetEditorWorld()->ClearQueue();
                }
                if (ImGui::Button("Add Wall (Single)"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Additive_Single);
                    CWorldManager::GetEditorWorld()->ClearQueue();
                }
                if (ImGui::Button("None"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::None);
                    CWorldManager::GetEditorWorld()->ClearQueue();
                }

                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Debug"))
            {
                if (ImGui::Button("Toggle Debug"))
                {
                    CWorldManager::GetEditorWorld()->ToggleDebugMode(!debugModeToggle);
                    debugModeToggle = !debugModeToggle;
                }
                ImGui::TreePop();
            }


            if (ImGui::TreeNode("Utility"))
            {
                if (ImGui::Button("Clear Grid"))
                {
                    CWorldManager::GetEditorWorld()->PerformOperation_ClearSpace();
                    CWorldManager::GetEditorWorld()->ClearQueue();
                }
              

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Levels"))
            {
                ImGui::InputInt("Slot", levelToLoad, 1, 1);
                if (ImGui::Button("Load"))
                {
                    CWorldManager::LoadWorld(*levelToLoad, true);
                   
                }


                ImGui::TreePop();
            }
           


            if (ImGui::Button("Save"))
            {
                CWorldManager::GetEditorWorld()->SaveWorld(*levelToLoad);
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
            if (ImGui::TreeNode("Enemy Units"))
            {
                if (ImGui::Button("Mage Enemy"))
                {
                    CWorldManager::GetEditorWorld()->AddEditorEntity_EnemyCharacter(0);
                }
                if (ImGui::Button("Melee Enemy"))
                {
                    CWorldManager::GetEditorWorld()->AddEditorEntity_EnemyCharacter(1);
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
