// find

	Set(HEADER_GG_CHECK_AWAKENESS,		sizeof(TPacketGGCheckAwakeness),	"CheckAwakeness",		false);

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        Set(HEADER_GG_UPDATE_BOSS_DAMAGE_RANKING,		sizeof(uint8_t),	"BossDamageRanking",		false);
#endif