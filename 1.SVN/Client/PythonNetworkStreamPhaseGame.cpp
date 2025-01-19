// find

        case HEADER_GC_DRAGON_SOUL_REFINE:
            ret = RecvDragonSoulRefine();
            break;

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        case HEADER_GC_BOSS_DMG_RANKING:
            ret = RecvBossDamageRankingPacket();
            break;
#endif

// add EOF

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
bool CPythonNetworkStream::RecvBossDamageRankingPacket()
{
    bool b_ret{false};

    DynamicPacketInfo pack{};
    if (!Recv(sizeof(pack), &pack))
    {
        TraceError("CPythonNetworkStream::RecvBossDamageRanking - Failed to recv packet");
        return b_ret;
    }

    switch (static_cast<EPacketCGBossDamageRankingSubHeaderType>(pack.sub_header))
    {
    case EPacketCGBossDamageRankingSubHeaderType::BOSS_DMG_RANKING_RANK_INFO:
        b_ret = bossdamageranking::PythonBossDamageRanking::Instance().recv_boss_ranking_rank_info();
        break;
    case EPacketCGBossDamageRankingSubHeaderType::BOSS_DMG_RANKING_DAMAGE_INFO:
        break;
    default:
        TraceError("CPythonNetworkStream::RecvBossDamageRanking - Unknown subheader %d", pack.sub_header);
        b_ret = false;
        break;
    }

    return b_ret;
}
#endif
