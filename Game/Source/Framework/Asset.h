#pragma once

#include "AssetType.h"

class Asset
{
public:

	virtual ~Asset()
	{

	}

	AssetType Type() const
	{
		return type;
	}

protected:

	Asset(AssetType type, const char* path)
	{
		this->type = type;
		this->path = path;
	}

protected:

	AssetType type = AssetType::AST_NULL;
	const char* path = nullptr;

};