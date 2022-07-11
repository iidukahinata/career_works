/**
* @file    pch.h
* @brief
*
* @date	   2022/07/12 2022îNìxèâî≈
*/
#pragma once


#include <any>
#include <mutex>
#include <algorithm>
#include <functional>

// Core
#include "TypeDef.h"
#include "Macro.h"
#include "Tools/Tools.h"
#include "Tools/Array.h"
#include "Tools/String.h"
#include "Tools/Memory/Memory.h"

// Context
#include "SubSystem/Core/Context.h"

// Math System
#include"SubSystem/Core/Math/Vector2.h"
#include"SubSystem/Core/Math/Vector3.h"
#include"SubSystem/Core/Math/Vector4.h"
#include "SubSystem/Core/Math/Vector2T.h"
#include "SubSystem/Core/Math/Vector3T.h"
#include "SubSystem/Core/Math/Vector4T.h"
#include "SubSystem/Core/Math/Matrix.h"

// File System
#include "../IO/FileStream.h"
#include "../IO/FileSystem.h"

// Job System
#include "SubSystem/JobSystem/Sync/Job.h"
#include "SubSystem/JobSystem/Async/AsyncJob.h"