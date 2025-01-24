// find

    HEADER_GC_RESPOND_CHANNELSTATUS = 210,

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    HEADER_GC_BOSS_DMG_RANKING = 241,
#endif

// find

    HEADER_GG_CHECK_AWAKENESS = 29,

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    HEADER_GG_UPDATE_BOSS_DAMAGE_RANKING,
#endif

// find

#pragma pack()
#endif

// add above

struct DynamicPacketInfo
{
    uint8_t header;
    uint8_t sub_header;
};

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
enum class EPacketCGBossDamageRankingSubHeaderType : uint8_t
{
    BOSS_DMG_RANKING_RANK_INFO,
    BOSS_DMG_RANKING_DAMAGE_INFO,
};

struct SPacketCGBossDamageRanking
{
    SPacketCGBossDamageRanking() : header(HEADER_GC_BOSS_DMG_RANKING) {}
    uint8_t header;
};

struct SPacketGCRankingGeneralInfo
{
    uint8_t rank_size;
};

struct SPacketGCBossDamageRankingInfo
{
    uint8_t race;
    char name[CHARACTER_NAME_MAX_LEN + 1];
    uint8_t percent_damage;
    uint8_t bad_affect_flag;
};
#endif
