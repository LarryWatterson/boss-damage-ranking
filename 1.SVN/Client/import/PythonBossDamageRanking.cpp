
#include "StdAfx.h"
#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "PythonBossDamageRanking.hpp"
#include "PythonNetworkStream.h"
#include "PythonWrapper.hpp"

namespace bossdamageranking {

PythonBossDamageRanking::PythonBossDamageRanking() : mp_py_middleware(std::make_unique<helpers::PythonMiddleWare>()) {
}

void PythonBossDamageRanking::set_ui_window(PyObject* p_ui_window) const
{

    mp_py_middleware->set_ui_window(p_ui_window);
}

void PythonBossDamageRanking::open_window() const
{
    mp_py_middleware->call_window_func("open", nullptr);
}

void PythonBossDamageRanking::close_window() const
{
    mp_py_middleware->call_window_func("close", nullptr);
}

void PythonBossDamageRanking::update_ranking_info(const std::vector<SPacketGCBossDamageRankingInfo>& info_vec) const
{
    pythonwrapper::PythonObjectBuilder py_dict{pythonwrapper::PythonObjectType::List};

    for (const auto& [race, name, percent_damage, bad_affect_flag]: info_vec)
    {
        pythonwrapper::PythonObjectBuilder py_player_info{pythonwrapper::PythonObjectType::List};

        py_player_info.add_item(name).add_item(race).add_item(percent_damage).add_item(bad_affect_flag);
        py_dict.add_item(py_player_info.build());
    }   

    mp_py_middleware->call_window_func("update_ranking_info", py_dict.build());
}

bool PythonBossDamageRanking::recv_boss_ranking_rank_info() const
{
    auto& ins{CPythonNetworkStream::Instance()};

    SPacketGCRankingGeneralInfo subpacket{};
    if (!ins.Recv(sizeof(SPacketGCRankingGeneralInfo), &subpacket))
    {
        return false;
    }

    std::vector<SPacketGCBossDamageRankingInfo> info_vec{subpacket.rank_size};

    if (!ins.Recv(sizeof(SPacketGCBossDamageRankingInfo) * subpacket.rank_size, info_vec.data()))
    {
        TraceError("SPacketGCBossDamageRankingInfo Recv error");

        return false;
    }

    update_ranking_info(info_vec);

    return true;
}

namespace py_funcs {

PyObject* set_ui_window([[maybe_unused]] PyObject* po_self, PyObject* po_args)
{
    PyObject* po_window;
    if (!PyTuple_GetObject(po_args, 0, &po_window)) { return Py_BuildException(); }
    if (po_window == Py_None) { po_window = nullptr; }

    PythonBossDamageRanking::Instance().set_ui_window(po_window);

    return Py_BuildNone();
}
}

}

void initbossdamageranking()
{
    static std::vector<PyMethodDef> s_methods = {{
        {"set_ui_window", bossdamageranking::py_funcs::set_ui_window, METH_VARARGS},

        {nullptr, nullptr, NULL},
    }};

    [[maybe_unused]] PyObject* po_module{Py_InitModule("boss_damage_ranking", s_methods.data())};
}

#endif // !BOSS_DAMAGE_RANKING_PLUGIN