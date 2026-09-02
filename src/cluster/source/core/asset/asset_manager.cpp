#include <pch.h>

#include "core/asset/asset_manager.h"

namespace ObsidianEdge {
static std::shared_ptr<AssetManager> s_assetManager = std::make_shared<AssetManager>();

auto getAssetManager() -> AssetManager& {
    return *s_assetManager.get();
}
} // namespace ObsidianEdge