DROP TABLE IF EXISTS `customattributes_item_instance`;
CREATE TABLE `customattributes_item_instance` (
  `guid` int(11) unsigned NOT NULL,
  `quality` int(11) DEFAULT 1,
  `attr_type_1` int(11) DEFAULT 0,
  `attr_val_1` float DEFAULT 0,
  `attr_type_2` int(11) DEFAULT 0,
  `attr_val_2` float DEFAULT 0,
  `attr_type_3` int(11) DEFAULT 0,
  `attr_val_3` float DEFAULT 0,
  `attr_type_4` int(11) DEFAULT 0,
  `attr_val_4` float DEFAULT 0,
  `attr_type_5` int(11) DEFAULT 0,
  `attr_val_5` float DEFAULT 0,
  `attr_type_6` int(11) DEFAULT 0,
  `attr_val_6` float DEFAULT 0,
  `attr_type_7` int(11) DEFAULT 0,
  `attr_val_7` float DEFAULT 0,
  `attr_type_8` int(11) DEFAULT 0,
  `attr_val_8` float DEFAULT 0,
  `attr_type_9` int(11) DEFAULT 0,
  `attr_val_9` float DEFAULT 0,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;