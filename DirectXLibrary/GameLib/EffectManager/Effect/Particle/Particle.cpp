/// <filename>
/// Particle.cpp
/// </filename>
/// <summary>
/// パーティクルクラスのソース
/// </summary>

#include "Particle.h"

#include <Windows.h>

#include <d3dx9.h>

#include "IGameLibRenderer\IGameLibRenderer.h"
#include "VerticesParam.h"
#include "CustomVertex.h"
#include "Behavior/Behavior.h"
#include "Shape/Shape.h"

IGameLibRenderer* Particle::m_pIGameLibRenderer = nullptr;
