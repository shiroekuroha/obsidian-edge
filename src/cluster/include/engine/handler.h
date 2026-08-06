#pragma once

#include "core.h"

namespace ObsidianEdge {
template <typename ID, typename Data, auto Loader> class OE_API Handler {
public:
    static_assert(std::is_same_v<decltype(Loader(std::declval<const char *>())), Data>);

    Handler() = default;
    Handler(const Data &data) { setData(data); }
    Handler(const char *path) { setData(path); }
    Handler(ID id) { setData(id); }
    ~Handler() = default;

    constexpr Handler(const Handler &) = default;
    constexpr Handler(Handler &&) noexcept = default;

    constexpr auto operator=(const Handler &) -> Handler & = default;
    constexpr auto operator=(Handler &&) noexcept -> Handler & = default;

    [[nodiscard]] auto getData() const -> const Data & { return *m_data; }

    void setData(const Data &data) {
        m_id = s_keeper.loadData(data);
        m_data = s_keeper.getData(m_id);
    }

    void setData(const char *path) {
        m_id = s_keeper.loadData(path);
        m_data = s_keeper.getData(m_id);
    }

    void setData(ID id) {
        m_id = id;
        m_data = s_keeper.getData(id);
    }

private:
    ID m_id{};
    std::shared_ptr<const Data> m_data;

    class OE_API Keeper {
    public:
        Keeper() = default;
        ~Keeper() = default;

        Keeper(const Keeper &) = delete;
        Keeper(Keeper &&) noexcept = delete;

        auto operator=(const Keeper &) -> Keeper & = delete;
        auto operator=(Keeper &&) noexcept -> Keeper & = delete;

        auto getData(const char *path) const -> std::shared_ptr<const Data> {
            std::lock_guard<std::mutex> lock(mutex_);

            return m_dataTable.at(m_pathTable.at(path));
        }

        auto getData(ID id) const -> std::shared_ptr<const Data> {
            std::lock_guard<std::mutex> lock(mutex_);

            return m_dataTable.at(id);
        }

        auto loadData(const char *path) -> ID {
            std::lock_guard<std::mutex> lock(mutex_);

            auto it = m_pathTable.find(path);

            if (it != m_pathTable.end())
                return it->second;

            ID id = m_uniqueIdGen++;
            Data data = Loader(path);

            m_dataTable[id] = std::make_shared<const Data>(data);
            m_pathTable[path] = id;

            return id;
        }

        auto loadData(const Data &data) -> ID {
            std::lock_guard<std::mutex> lock(mutex_);

            ID id = m_uniqueIdGen++;

            m_dataTable[id] = std::make_shared<const Data>(data);

            return id;
        }

    private:
        mutable std::mutex mutex_;
        ID m_uniqueIdGen = 0;

        std::unordered_map<std::string, ID> m_pathTable;
        std::unordered_map<ID, std::shared_ptr<const Data>> m_dataTable;
    };

    inline static Keeper s_keeper;
};
} // namespace ObsidianEdge
