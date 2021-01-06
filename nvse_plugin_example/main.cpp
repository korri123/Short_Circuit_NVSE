#include "nvse/PluginAPI.h"

#include "Hooks_ExpressionEvalOptimized.h"

IDebugLog		gLog("ShortCircuit.log");
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

void MessageHandler(NVSEMessagingInterface::Message* msg)
{
	if (msg->type == NVSEMessagingInterface::kMessage_ClearScriptDataCache)
	{
		kEvaluator::TokenListMap::MarkForClear();
	}
}


bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	_MESSAGE("query");

	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "short_circuit";
	info->version = 1;
	if (nvse->nvseVersion < NVSE_VERSION_INTEGER)
	{
		_ERROR("NVSE version too old (got %08X expected at least %08X)", nvse->nvseVersion, NVSE_VERSION_INTEGER);
		return false;
	}
	if (nvse->isEditor)
		return false;
	return true;
}

bool NVSEPlugin_Load(const NVSEInterface* nvse)
{
	g_pluginHandle = nvse->GetPluginHandle();
	auto* messagingInterface = static_cast<NVSEMessagingInterface*>(nvse->QueryInterface(kInterface_Messaging));
	messagingInterface->RegisterListener(g_pluginHandle, "NVSE", MessageHandler);

	Hook_Evaluator();
	return true;
}
