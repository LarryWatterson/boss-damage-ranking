// find

		Set(HEADER_GC_DRAGON_SOUL_REFINE,
		    CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
                Set(HEADER_GC_BOSS_DMG_RANKING, TPacketType(sizeof(DynamicPacketInfo), STATIC_SIZE_PACKET));
#endif
