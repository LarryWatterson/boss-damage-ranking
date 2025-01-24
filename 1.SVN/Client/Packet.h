// find

    HEADER_GC_RESPOND_CHANNELSTATUS = 210,

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    HEADER_GC_BOSS_DMG_RANKING = 241,
#endif

// add anywhere

struct DynamicPacketInfo
{
    uint8_t header;
    uint8_t sub_header;
};

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
enum class BadAffectType : uint8_t {
    NONE = 0 << 0,
    POISON = 1 << 0,
    FIRE = 1 << 1,
#ifdef ENABLE_WOLFMAN_CHARACTER
    BLEED = 1 << 2,
#endif
};

enum class EPacketCGBossDamageRankingSubHeaderType : uint8_t {
    BOSS_DMG_RANKING_RANK_INFO,
    BOSS_DMG_RANKING_DAMAGE_INFO,
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