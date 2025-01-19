// add in includes

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif

// find

void CHARACTER::StartRecoveryEvent()
{
    if (m_pkRecoveryEvent) return;

    if (IsDead() || IsStun()) return;

    if (IsNPC() && GetHP() >= GetMaxHP()) return;

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    if (auto& boss_dmg_mng{bossdamageranking::boss_dmg_ranking_manager()};
        !IsPC() && boss_dmg_mng.is_boss_in_ranking(GetRaceNum()))
    {
        return;
    }
#endif
