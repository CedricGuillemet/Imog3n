#pragma once

void ShowNodeEditor();
void FitNodes();
void FitSelectedNodes();
void EditOptions();

bool ShowSDFEdit(float* viewMatrix, float length, float* currentMatrix, float* parameters);
void InvertMatrix(const float* sourceMatrix, float* destinationMatrix);