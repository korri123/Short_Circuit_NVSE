#include "nvse/PluginAPI.h"

#include "Hooks_ExpressionEvalOptimized.h"

IDebugLog		gLog("ShortCircuit.log");

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	_MESSAGE("query");

	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "ShortCircuit";
	info->version = 1;
	if (nvse->nvseVersion < NVSE_VERSION_INTEGER)
	{
		_ERROR("NVSE version too old (got %08X expected at least %08X)", nvse->nvseVersion, NVSE_VERSION_INTEGER);
		return false;
	}
	return true;
}

bool NVSEPlugin_Load(const NVSEInterface* nvse)
{
	if (nvse->isEditor)
		return true;

	Hook_Evaluator();
	return true;
}
