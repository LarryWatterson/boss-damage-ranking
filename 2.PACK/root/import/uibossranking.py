__Author__ = "LWT"
__version__ = "1.0"

import ui
import wndMgr
import boss_damage_ranking
import chat


class PlayerInfo(object):
    def __init__(self, name, job, percent_damage, bad_affect_flag):
        self.name = name
        self.job = job
        self.percent_damage = percent_damage
        self.bad_affect_flag = bad_affect_flag


class PlayerRankingManager(object):
    def __init__(self):
        self.player_info_list = []

    def update_player_info(self, new_player_info):
        """
        Update the player info list with new data.
        :param new_player_info: List of tuples [(name, job, percent_damage, bad_affect_flag), ...]
        """
        self.player_info_list = [PlayerInfo(*info) for info in new_player_info]


class BossDamageRankingUI(object):
    def __init__(self):
        self.wnd_dict = {}

    def create_dialog(self, parent, player_info_list):
        """
        Create the UI elements for the ranking display.
        :param parent: Parent UI element
        :param player_info_list: List of PlayerInfo objects
        """
        # map(lambda wnd: wnd.Hide(), self.wnd_dict.values())
        self.wnd_dict.clear()

        y_inc_pos = 22

        for idx, player_info in enumerate(player_info_list):
            height_inc = y_inc_pos * idx

            player_race_img = ui.ImageBox()
            player_race_img.SetParent(parent)
            player_race_img.LoadImage("plugins/common/race/{}.tga".format(player_info.job))
            player_race_img.SetPosition(10, 10 + height_inc)
            player_race_img.Hide()
            self.wnd_dict["player_race_img{0}".format(idx)] = player_race_img

            player_name_text = ui.TextLine()
            player_name_text.SetParent(parent)
            player_name_text.SetPosition(42, 10 + height_inc)
            player_name_text.SetHorizontalAlignLeft()
            player_name_text.SetText(str(player_info.name))
            player_name_text.Hide()
            self.wnd_dict["player_name_text{0}".format(idx)] = player_name_text

            player_percent_dmg_text = ui.TextLine()
            player_percent_dmg_text.SetParent(parent)
            player_percent_dmg_text.SetPosition(170, 10 + height_inc)
            player_percent_dmg_text.SetHorizontalAlignLeft()
            player_percent_dmg_text.SetText("%{}".format(player_info.percent_damage))
            player_percent_dmg_text.Hide()
            self.wnd_dict["player_percent_dmg_text{0}".format(idx)] = player_percent_dmg_text

            gauge_color = "lime" if player_info.bad_affect_flag else "red"
            player_damage_gauge = ui.Gauge()
            player_damage_gauge.SetParent(parent)
            player_damage_gauge.SetPosition(205, 12 + height_inc)
            player_damage_gauge.MakeGauge(100, gauge_color)
            player_damage_gauge.SetPercentage(player_info.percent_damage, 100)
            player_damage_gauge.Hide()
            self.wnd_dict["player_damage_gauge{0}".format(idx)] = player_damage_gauge

        parent.SetSize(320, len(player_info_list) * 25)
        parent.SetPosition(wndMgr.GetScreenWidth() - 330, 310)
        # parent.Show()

    def update_dialog(self):
        map(lambda wnd: wnd.Show(), self.wnd_dict.values())


class BossDamageRanking(ui.ThinBoard):
    def __init__(self):
        super(BossDamageRanking, self).__init__()
        boss_damage_ranking.set_ui_window(self)
        self.manager = PlayerRankingManager()
        self.ui = BossDamageRankingUI()

    def __del__(self):
        super(BossDamageRanking, self).__del__()
        boss_damage_ranking.set_ui_window(None)

    def open(self):
        self.Show()
        self.SetTop()

    def close(self):
        self.Hide()

    def update_ranking_info(self, player_info_list):
        """
        Update rankings and refresh the UI.
        :param player_info_list: List of tuples [(name, job, percent_damage, bad_affect_flag), ...]
        """

        self.manager.update_player_info(player_info_list)
        self.ui.create_dialog(self, self.manager.player_info_list)
        self.ui.update_dialog()
        self.open()
