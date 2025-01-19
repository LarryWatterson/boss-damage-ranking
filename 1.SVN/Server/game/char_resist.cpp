// add includes

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif

// find

void CHARACTER::AttackedByFire(LPCHARACTER pkAttacker, int amount, int count)
{
    if (m_pkFireEvent) return;

    AddAffect(AFFECT_FIRE, POINT_NONE, 0, AFF_FIRE, count * 3 + 1, 0, true);


// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    if (bossdamageranking::boss_dmg_ranking_manager().is_boss_in_ranking(GetRaceNum()))
    {
        bossdamageranking::boss_dmg_ranking_manager().set_bad_affect({GetRaceNum(), static_cast<DWORD>(GetVID())},
            pkAttacker->GetPlayerID(),
            bossdamageranking::BadAffectType::FIRE);
    }
#endif

// find

    m_bHasPoisoned = true;

    AddAffect(AFFECT_POISON, POINT_NONE, 0, AFF_POISON, POISON_LENGTH + 1, 0, true);

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    if (bossdamageranking::boss_dmg_ranking_manager().is_boss_in_ranking(GetRaceNum()))
    {
        bossdamageranking::boss_dmg_ranking_manager().set_bad_affect({GetRaceNum(), static_cast<DWORD>(GetVID())},
            pkAttacker->GetPlayerID(),
            bossdamageranking::BadAffectType::POISON);
    }
#endif

// find

    m_bHasBled = true;

    AddAffect(AFFECT_BLEEDING, POINT_NONE, 0, AFF_BLEEDING, BLEEDING_LENGTH + 1, 0, true);

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    if (bossdamageranking::boss_dmg_ranking_manager().is_boss_in_ranking(GetRaceNum()))
    {
        bossdamageranking::boss_dmg_ranking_manager().set_bad_affect({GetRaceNum(), static_cast<DWORD>(GetVID())},
            pkAttacker->GetPlayerID(),
            bossdamageranking::BadAffectType::BLEED);
    }
#endif