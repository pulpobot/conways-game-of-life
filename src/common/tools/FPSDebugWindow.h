//
// Created by Santiago Alvarez Vargas on 2018-12-16.
//

#ifndef PULPOBOT_FPS_DEBUG_WINDOW_H
#define PULPOBOT_FPS_DEBUG_WINDOW_H

#include <stddef.h> //NULL
#include <iostream>
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui-SFML.h"

namespace pulpobot
{
    void FPSDebugWindow(bool *p_open = NULL)
    {
        if (!(*p_open)) return;

        if (!ImGui::Begin("FPS", p_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
                                         ImGuiWindowFlags_AlwaysAutoResize))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        ImGui::Text("%.3f ms/frame\n(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

#endif //PULPOBOT_FPS_DEBUG_WINDOW_H
