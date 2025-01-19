// add includes

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
#include "bossdamagerankingmanager.hpp"
#endif

// find

        if (IsPC())
        {
            CGuild* g1 = GetGuild();
            CGuild* g2 = pkKiller->GetGuild();

            if (g1 && g2)
                if (g1->UnderWar(g2->GetID())) isUnderGuildWar = true;

            pkKiller->SetQuestNPCID(GetVID());
            quest::CQuestManager::instance().Kill(pkKiller->GetPlayerID(), quest::QUEST_NO_NPC);
            CGuildManager::instance().Kill(pkKiller, this);
        }


// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        if (const bool check_boss_and_map{!IsPC() && pkKiller->GetMapIndex() < 1000}; check_boss_and_map)
        {
            bossdamageranking::boss_dmg_ranking_manager().erase_boss_from_list({GetRaceNum(), static_cast<DWORD>(GetVID())});
        }
#endif

// find

        float damMul = this->GetDamMul();
        float tempDam = dam;
        dam = tempDam * damMul + 0.5f;

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        if (const auto is_boss_in_ranking{
                bossdamageranking::boss_dmg_ranking_manager().is_boss_in_ranking(GetRaceNum())};
            is_boss_in_ranking)
        {
            bossdamageranking::boss_dmg_ranking_manager().damage_process(
                pAttacker, {GetRaceNum(), static_cast<DWORD>(GetVID())}, dam);
        }
#endif

// find

    if (IsPC())
    {
        if (IS_SPEED_HACK(this, pkVictim, dwCurrentTime)) return false;

        if (bType == 0 && dwCurrentTime < GetSkipComboAttackByTime()) return false;
    }
    else { MonsterChat(MONSTER_CHAT_ATTACK); }

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
    if (IsPC())
    {
        if (const auto is_boss_in_ranking{
        bossdamageranking::boss_dmg_ranking_manager().is_boss_in_ranking(pkVictim->GetRaceNum())};
    is_boss_in_ranking)
        {
            bossdamageranking::boss_dmg_ranking_manager().add_player_to_list(
                this, {pkVictim->GetRaceNum(), static_cast<DWORD>(pkVictim->GetVID())});
        }
    }

#endif
