// add includes

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif

// find

    if (bShow && !ch->Show(lMapIndex, x, y, z, bSpawnMotion))
    {
        M2_DESTROY_CHARACTER(ch);
        sys_log(0, "SpawnMob: cannot show monster");
        return NULL;
    }

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    if (const auto is_boss_in_ranking{
            bossdamageranking::boss_dmg_ranking_manager().is_boss_in_ranking(ch->GetRaceNum())};
        is_boss_in_ranking)
    {
        sys_err("add boss to list");
        bossdamageranking::BossDamageRankingBossInfo boss_info{};
        boss_info.mob_vnum = dwVnum;
        boss_info.mob_vid = ch->GetVID();
        boss_info.max_hp = ch->GetMaxHP();

        bossdamageranking::boss_dmg_ranking_manager().add_boss_to_list(boss_info);
    }
#endif