// add include

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif

// find

ACMD(do_reload)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (*arg1)
	{

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
	    if (static_cast<std::string>(arg1) == "boss_dmg_ranking")
	    {
                bossdamageranking::boss_dmg_ranking_manager().reload();
	            ch->ChatPacket(CHAT_TYPE_INFO, "Reloading boss damage ranking.");
                return;
	    }
#endif