#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
DebugOutput* Debug::output = nullptr;
int Debug::logSize = 1000;
bool Debug::showDebug = false;
bool Debug::allowLogging = false;
