// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#include "EmojAISettings.h"

namespace
{
	constexpr TCHAR MaterialPath[] =
		TEXT("/EmojAI/M_Widget_Passthrough.M_Widget_Passthrough");
}

UEmojAISettings::UEmojAISettings()
	: WidgetMaterial(FSoftObjectPath(MaterialPath))
{
	CategoryName = "Plugins";
}
