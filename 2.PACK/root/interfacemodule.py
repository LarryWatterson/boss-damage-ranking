# import

if app.BOSS_DAMAGE_RANKING_PLUGIN:
	import uibossranking

# find
		self.wndGuildBuilding = None

# add below

		if app.BOSS_DAMAGE_RANKING_PLUGIN:
			self.wnd_boss_damage_ranking = None

# find

		self.wndChatLog = wndChatLog

# add below

		if app.BOSS_DAMAGE_RANKING_PLUGIN:
			self.wnd_boss_damage_ranking = uibossranking.BossDamageRanking()

# find

		# ACCESSORY_REFINE_ADD_METIN_STONE
		if self.wndItemSelect:
			self.wndItemSelect.Destroy()
		# END_OF_ACCESSORY_REFINE_ADD_METIN_STONE

# add below

		if app.BOSS_DAMAGE_RANKING_PLUGIN and self.wnd_boss_damage_ranking:
				self.wnd_boss_damage_ranking.Destroy()
				del self.wnd_boss_damage_ranking
