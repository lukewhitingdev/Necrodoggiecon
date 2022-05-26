#include "CT_EditorWindows.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "Cerberus\Core\Environment\CWorld_Edit.h"
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

using json = nlohmann::json;



void CT_EditorWindows::LoadWeapons()
{

    std::ifstream file("Resources/Weapons.json");
    json storedFile;
    file >> storedFile;
    
  

    for (int i = 0; i < storedFile["TotalWeapons"]; i++)
    {
       
        WepList.push_back(storedFile["Weapons"][i]["Name"]);
      
        


        //weaponNames[i] = InName.c_str();
    }
  

}

void CT_EditorWindows::InitialiseMapSlot()
{
    levelToLoad = new int(CWorldManager::GetEditorWorld()->GetMapSlot());

}

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
                    std::string SlotName = "Slot " + std::to_string(i);
                 
                    if (ImGui::Button(SlotName.c_str()))
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
               
                if (ImGui::Button("Weapon Holder"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::WeaponHolder);
                }

                if (ImGui::Button("Goal"))
                {

                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Enemy Units"))
            {


                if (ImGui::Button("Grunt Enemy"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::EnemyEntity);
                    CWorldManager::GetEditorWorld()->SetEntityID(0);
                }
                if (ImGui::Button("Dog Enemy"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::EnemyEntity);
                    CWorldManager::GetEditorWorld()->SetEntityID(1);
                }
                if (ImGui::Button("Alarm Enemy"))
                {
                    CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::EnemyEntity);
                    CWorldManager::GetEditorWorld()->SetEntityID(2);
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
            if (CWorldManager::GetEditorWorld()->GetInspectedItemType() != EditorEntityType::None)
            {

              
                static const char* current_item = NULL;
                std::string Name = "Waypoint: ";

                switch (CWorldManager::GetEditorWorld()->GetInspectedItemType())
                {
                case EditorEntityType::Enemy:
                   

                    current_item = WepList[CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetAssignedWeapon()].c_str();

                    switch (CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetSlot())
                    {
                    case 0:
                        ImGui::Text("Grunt Enemy");
                      
                        if (ImGui::BeginCombo("Weapon", current_item))
                        {
                            for (int n = 0; n < WepList.size(); n++)
                            {
                                bool is_selected = (CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetAssignedWeapon() == n); // You can store your selection however you want, outside or inside your objects
                                if (ImGui::Selectable(WepList[n].c_str(), is_selected))
                                {
                                  
                                    current_item = WepList[n].c_str();
                                    CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->AssignWeapon((char*)WepList[n].c_str(), n);
                                    if (is_selected)
                                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                                }
                                  
                                  
                            }
                            ImGui::EndCombo();
                        }


                        break;
                    case 1: 
                        ImGui::Text("Dog Enemy");
                        break;
                    case 2:
                        ImGui::Text("Alarm Enemy");
                        break;
                    }

                   



                    if (ImGui::Button("Add Waypoint"))
                    {
                        CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Waypoints);
                    }
                    if (ImGui::Button("Toggle Waypoint"))
                    {
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->ToggleWaypoints(toggleWaypoints = !toggleWaypoints);
                    }

                    if (ImGui::TreeNode("Status"))
                    {
                        float* Health = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetHealth());
                        float* Mass = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetMass());
                        float* Speed = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetSpeed());
                        float* Range = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetRange());
                        float* ViewAngle = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetViewAngle());

                        float* RotationSpeed = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetRotationSpeed());
                        float* MaxSearchTime = new float(CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->GetMaxSearchTime());

                        ImGui::SliderFloat("Health", Health, 0.0f, 100.0f);
                        ImGui::SliderFloat("Mass", Mass, 0.0f, 100.0f);
                        ImGui::SliderFloat("Speed", Speed, 0.0f, 500.0f);
                        ImGui::SliderFloat("Range", Range, 0.0f, 1000.0f);
                        ImGui::SliderFloat("ViewAngle", ViewAngle, 0.0f, 360.0f);
                        ImGui::SliderFloat("RotationSpeed", RotationSpeed, 0.0f, 100.0f);
                        ImGui::SliderFloat("MaxSearchTime", MaxSearchTime, 0.0f, 100.0f);

                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetHealth(*Health);
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetMass(*Mass);
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetSpeed(*Speed);
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetRange(*Range);
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetViewAngle(*ViewAngle);
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetRotationSpeed(*RotationSpeed);
                        CWorldManager::GetEditorWorld()->GetInspectedItem_Enemy()->SetMaxSearchTime(*MaxSearchTime);


                        ImGui::TreePop();
                    }



                    break;
                case EditorEntityType::Waypoint:
                  
                 
                    Name += std::to_string(CWorldManager::GetEditorWorld()->GetInspectedItem_Waypoint()->waypointOrder).c_str();
                    ImGui::Text(Name.c_str());
                    break;
                case EditorEntityType::WeaponHolder:
                    ImGui::Text("Weapon Holder");
                  
                    current_item = WepList[CWorldManager::GetEditorWorld()->GetInspectedItem_WeaponHolder()->GetAssignedWeapon()].c_str();
                     if (ImGui::BeginCombo("Items", current_item))
                    {
                        for (int n = 0; n < WepList.size(); n++)
                        {
                            bool is_selected = (CWorldManager::GetEditorWorld()->GetInspectedItem_WeaponHolder()->GetAssignedWeapon() == n); // You can store your selection however you want, outside or inside your objects
                            if (ImGui::Selectable(WepList[n].c_str(), is_selected))
                            {

                                current_item = WepList[n].c_str();
                                CWorldManager::GetEditorWorld()->GetInspectedItem_WeaponHolder()->AssignWeapon((char*)WepList[n].c_str(), n);
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                            }


                        }
                        ImGui::EndCombo();
                    }
                  
                    break;
                  
                }
            }
           
           



            ImGui::End();

        }

    }
}
