#ifndef CLIENT_PYTHONBOSSDAMAGERANKING_HPP
#define CLIENT_PYTHONBOSSDAMAGERANKING_HPP

#include "packet.h"
#include "python_middleware.hpp"

namespace bossdamageranking {
class PythonBossDamageRanking final : public CSingleton<PythonBossDamageRanking> {
public:

    PythonBossDamageRanking();

    void set_ui_window(PyObject* p_ui_window) const;

    void open_window() const;

    void close_window() const;

    void update_ranking_info(const std::vector<SPacketGCBossDamageRankingInfo>& info_vec) const;

    [[nodiscard]] bool recv_boss_ranking_rank_info() const;
private:
    /**
     * @brief Middleware for abstracting Python calls
     */
    helpers::py_helper_t mp_py_middleware{};
};
}
#endif
