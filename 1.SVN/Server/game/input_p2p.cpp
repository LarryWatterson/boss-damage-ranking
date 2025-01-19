// add includes

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif

// find

		case HEADER_GG_CHECK_AWAKENESS:
			IamAwake(d, c_pData);
			break;

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
	    case HEADER_GG_UPDATE_BOSS_DAMAGE_RANKING:
	    {
	        bossdamageranking::boss_dmg_ranking_manager().initialize();
	        break;
	    }
#endif