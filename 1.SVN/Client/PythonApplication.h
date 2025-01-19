// add include

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "PythonBossDamageRanking.hpp"
#endif

// find

		CPythonMessenger			m_pyManager;

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
                bossdamageranking::PythonBossDamageRanking m_pyBossDamageRanking;
#endif
