SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for boss_dmg_ranking
-- ----------------------------
DROP TABLE IF EXISTS `boss_dmg_ranking`;
CREATE TABLE `boss_dmg_ranking`  (
  `boss_vnum` int UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`boss_vnum`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
