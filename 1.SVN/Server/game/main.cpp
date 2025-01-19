// add include

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif


// find

	DSManager dsManager;

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        bossdamageranking::CBossDamageRankingManager boss_dmg_ranking_manager;
#endif

// find

	PanamaLoad();

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        if (!g_bAuthServer)
        {
                boss_dmg_ranking_manager.initialize();
        }
#endif