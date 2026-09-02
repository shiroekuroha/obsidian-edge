#pragma once

#include "core.h"

#include "core/asset/asset_loader.h"
#include "core/asset/assets.h"

namespace ObsidianEdge {

using AssetPtr = std::shared_ptr<AssetContainer>;

class OE_API AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    AssetManager(const AssetManager& other) = delete;
    AssetManager(AssetManager&& other) noexcept = delete;

    auto operator=(const AssetManager& other) -> AssetManager& = delete;
    auto operator=(AssetManager&& other) noexcept -> AssetManager& = delete;

    template <typename T> auto get(AssetId assetId) const -> const AssetContainer& {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        std::lock_guard lock(m_mutex);

        return *m_dataTable.at(typeid(T)).at(assetId);
    }

    template <typename T> auto get(AssetId assetId) -> AssetContainer& {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        std::lock_guard lock(m_mutex);

        return *m_dataTable.at(typeid(T)).at(assetId);
    }

    template <typename T> auto add(T& asset) -> AssetId {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        std::lock_guard lock(m_mutex);

        AssetId newId = nextId<T>();
        getDataTable<T>()[newId] = std::make_shared<AssetContainer>(asset);

        return newId;
    }

    template <typename T> void remove(AssetId assetId) {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        std::lock_guard lock(m_mutex);

        auto it = getDataTable<T>().find(assetId);

        if (it != getDataTable<T>().end()) {
            getDataTable<T>().erase(it);
        }
    }

    template <typename T> auto load(const char* path) -> AssetId {
        OE_CORE_ERROR("Asset Management Error: Undefined type is not allowed!");
    }

    template <> auto load<Texture2D>(const char* path) -> AssetId {
        std::lock_guard lock(m_mutex);

        try {
            Texture2D saved = loadImage(path);

            return add(saved);
        } catch (std::runtime_error e) {
            return 0;
        }
    }

    template <typename T> void unload(const char* path) {
        std::lock_guard lock(m_mutex);
        auto it = getPathTable<T>().find(path);

        if (it != getPathTable<T>().end()) {
            remove(it);
            getPathTable<T>().erase(it);
        }
    }

private:
    template <typename T> auto getPathTable() const -> const std::unordered_map<std::string, AssetId>& {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        return m_pathtable.at(typeid(T));
    }
    template <typename T> auto getPathTable() -> std::unordered_map<std::string, AssetId>& {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        return m_pathtable.at(typeid(T));
    }
    template <typename T> auto getDataTable() const -> const std::unordered_map<AssetId, AssetPtr>& {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        return m_dataTable.at(typeid(T));
    }
    template <typename T> auto getDataTable() -> std::unordered_map<AssetId, AssetPtr>& {
        static_assert(!std::is_same_v<T, Texture>, "Abstract Texture Class is not allowed");
        return m_dataTable.at(typeid(T));
    }

    template <typename T> auto nextId() -> AssetId {
        static_assert(!std::is_same_v<T, Texture>, "Pure Texture Class is not allowed");
        static AssetId nextId = 1;

        return nextId++;
    }

    std::mutex m_mutex;

    std::unordered_map<std::type_index, std::unordered_map<std::string, AssetId>> m_pathtable;
    std::unordered_map<std::type_index, std::unordered_map<AssetId, AssetPtr>> m_dataTable;
};

static auto getAssetManager() -> AssetManager&;
} // namespace ObsidianEdge