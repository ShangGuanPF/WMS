/*
Navicat MySQL Data Transfer

Source Server         : aaa
Source Server Version : 50624
Source Host           : localhost:3306
Source Database       : wms

Target Server Type    : MYSQL
Target Server Version : 50624
File Encoding         : 65001

Date: 2018-06-24 17:39:41
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for biaoshi
-- ----------------------------
DROP TABLE IF EXISTS `biaoshi`;
CREATE TABLE `biaoshi` (
  `标签编号` int(255) NOT NULL,
  `标签标识` varchar(255) DEFAULT NULL,
  `标签类型` varchar(255) DEFAULT NULL,
  `标签状态` varchar(255) DEFAULT NULL,
  `生产厂商` varchar(255) DEFAULT NULL,
  `生产日期` date DEFAULT NULL,
  `备注` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`标签编号`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of biaoshi
-- ----------------------------
INSERT INTO `biaoshi` VALUES ('1', '1', '2', '使用中', '2', '2005-01-01', '');
INSERT INTO `biaoshi` VALUES ('2', '2', '2', '使用中', '2', '2000-01-01', '');
INSERT INTO `biaoshi` VALUES ('3', 'AAFFFEE', 'RFID', '使用中', 'dd', '2018-03-15', '没有');
INSERT INTO `biaoshi` VALUES ('4', '4', '2', '使用中', '34', '2011-05-04', '');
INSERT INTO `biaoshi` VALUES ('12', '12', '43', '未使用', '34', '2000-01-01', '');
INSERT INTO `biaoshi` VALUES ('23', 'AEEF', 'FR', '未使用', 'sda', '2018-04-03', null);
INSERT INTO `biaoshi` VALUES ('32', '34', '', '未使用', '', '2000-01-01', '');
INSERT INTO `biaoshi` VALUES ('314', '3412', '', '未使用', '', '2000-01-01', '');
INSERT INTO `biaoshi` VALUES ('432', '32', '3', '未使用', '1', '2019-04-03', '');
INSERT INTO `biaoshi` VALUES ('555', '555', '', '未使用', '', '2005-01-01', '');

-- ----------------------------
-- Table structure for outstorage
-- ----------------------------
DROP TABLE IF EXISTS `outstorage`;
CREATE TABLE `outstorage` (
  `订单号` char(7) DEFAULT NULL,
  `产品名称` varchar(50) DEFAULT NULL,
  `产品编号` char(15) DEFAULT NULL,
  `标签编号` char(15) DEFAULT NULL,
  `出库数量` varchar(7) DEFAULT NULL,
  `出库时间` varchar(50) DEFAULT NULL,
  `仓库` varchar(50) DEFAULT NULL,
  `管理员` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of outstorage
-- ----------------------------
INSERT INTO `outstorage` VALUES ('1002', 'ipad mini', '313', '131', '1', '2018-01-24 20:30:57', '13', '13');
INSERT INTO `outstorage` VALUES ('0012', '123', '12', '21', '2', '2018-01-24 20:31:05', '12', '122');
INSERT INTO `outstorage` VALUES ('0008', '电视', '0018', '0123', '4', '2018-01-24 20:31:12', '1122', 'stt');
INSERT INTO `outstorage` VALUES ('0003', '华为', '2235', '1232', '1', '2018-01-25 10:07:55', '0002', '小王');
INSERT INTO `outstorage` VALUES ('2018', '笔记本', '1233', '12', '12', '2018-01-25 16:48:45', '5', 'stt1');
INSERT INTO `outstorage` VALUES ('0001', '华为', '1234', '1232', '19', '2018-04-14 22:43:47', '0003', '小王');
INSERT INTO `outstorage` VALUES ('0002', '华为', '1234', '1', '10', '2018-04-21 16:17:09', '0002', '小王');
INSERT INTO `outstorage` VALUES ('0010', '三星', '2348', '1233', '11', '2018-04-23 14:47:11', '11', 'llj');
INSERT INTO `outstorage` VALUES ('0004', '华为', '1234', '1232', '1', '2018-04-23 15:03:01', '0002', '小王');
INSERT INTO `outstorage` VALUES ('0003', '华为', '2235', '1', '1', '2018-04-23 19:33:09', '0002', '小王');
INSERT INTO `outstorage` VALUES ('0003', '华为', '2235', '5', '24', '2018-04-24 14:55:23', '0002', '小王');
INSERT INTO `outstorage` VALUES ('5', '5', '5', '5', '5', '2018-04-25 19:26:14', '5', '5');
INSERT INTO `outstorage` VALUES ('0007', 'oppo', '1112', '6', '92', '2018-04-25 19:38:16', '1322', 'stt2018');
INSERT INTO `outstorage` VALUES ('15', '2', '1', '5', '1', '2018-04-25 19:58:13', '1', '1');
INSERT INTO `outstorage` VALUES ('1', '3', '3', '4', '3', '2018-04-25 19:58:56', '2', '2');
INSERT INTO `outstorage` VALUES ('6', '5', '5', '5', '4', '2018-04-25 20:00:17', '5', '5');
INSERT INTO `outstorage` VALUES ('6', '5', '5', '5', '1', '2018-04-25 20:02:01', '5', '5');
INSERT INTO `outstorage` VALUES ('4', '4', '44', '4', '4', '2018-04-25 20:02:07', '4', '4');
INSERT INTO `outstorage` VALUES ('0004', '华为', '12', '121', '3', '2018-04-25 20:02:16', '0002', '小王');
INSERT INTO `outstorage` VALUES ('0006', 'Iphone', '1112', '3', '2', '2018-04-25 20:02:26', '0008', 'bob');
INSERT INTO `outstorage` VALUES ('0006', 'Iphone', '1112', '3', '6', '2018-05-21 13:49:54', '0008', 'bob');
INSERT INTO `outstorage` VALUES ('0004', '华为', '12', '121', '1', '2018-05-29 08:24:48', '0002', '小王');
INSERT INTO `outstorage` VALUES ('0006', 'Iphone', '1112', '3', '1', '2018-05-29 10:44:43', '0008', 'bob');
INSERT INTO `outstorage` VALUES ('2', '2', '2', '22', '1', '2018-05-29 11:21:34', '2', '2');
INSERT INTO `outstorage` VALUES ('0006', 'Iphone', '1112', '3', '1', '2018-05-29 11:25:11', '0008', 'bob');
INSERT INTO `outstorage` VALUES ('0006', 'Iphone', '1112', '3', '1', '2018-05-29 11:25:22', '0008', 'bob');
INSERT INTO `outstorage` VALUES ('2', '2', '2', '22', '1', '2018-05-29 11:30:03', '2', '2');
INSERT INTO `outstorage` VALUES ('234', '2', '2', '1', '1', '2018-05-29 11:33:27', 'B仓', '1');
INSERT INTO `outstorage` VALUES ('323', '22', '11', '223', '4', '2018-05-29 11:34:45', 'A仓', '小张');
INSERT INTO `outstorage` VALUES ('3333', '小米', '121', '0', '1', '2018-06-13 10:29:53', 'A仓', 'sss');

-- ----------------------------
-- Table structure for product_imformation
-- ----------------------------
DROP TABLE IF EXISTS `product_imformation`;
CREATE TABLE `product_imformation` (
  `产品编号` varchar(255) NOT NULL,
  `产品名称` varchar(255) DEFAULT NULL,
  `类别` varchar(255) DEFAULT NULL,
  `单位` varchar(255) DEFAULT NULL,
  `数量` varchar(255) DEFAULT NULL,
  `进货价（元）` varchar(255) DEFAULT NULL,
  `批发价（元）` varchar(255) DEFAULT NULL,
  `零售价（元）` varchar(255) DEFAULT NULL,
  `生产日期` varchar(255) DEFAULT NULL,
  `生产厂商` varchar(255) DEFAULT NULL,
  `备注` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`产品编号`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of product_imformation
-- ----------------------------
INSERT INTO `product_imformation` VALUES ('1', '阿三', '电子产品', '袋', '43', '1', '1', '2', '2019/09/10', '111', '');
INSERT INTO `product_imformation` VALUES ('213', 'SSS', '五金', '箱', '23', '534', '222', '3435', '2016/01/01', 'FSFD', '');
INSERT INTO `product_imformation` VALUES ('34', '23', '服装', '箱', '223', '32', '34', '234', '2007/04/04', '234', '');
INSERT INTO `product_imformation` VALUES ('6959591500045', '12123', '电子产品', '吨', 'sdf', '1212', 'dfa', 'df', '2000/01/01', 'afd', 'adf');
INSERT INTO `product_imformation` VALUES ('978751241', '333', '服装', '箱', '33', '44', '1', '2', '2004/01/01', '44', '4');
INSERT INTO `product_imformation` VALUES ('9787512413122', '士大夫', '五金', '台', '的发', '发大水', '的萨芬s', '啊师傅', '2000/01/01', '阿斯蒂芬', '大师傅');

-- ----------------------------
-- Table structure for staff_management
-- ----------------------------
DROP TABLE IF EXISTS `staff_management`;
CREATE TABLE `staff_management` (
  `员工编号` int(255) NOT NULL AUTO_INCREMENT,
  `用户名` varchar(255) DEFAULT NULL,
  `姓名` varchar(255) DEFAULT NULL,
  `角色` varchar(255) DEFAULT NULL,
  `邮箱` varchar(255) DEFAULT NULL,
  `电话` int(255) DEFAULT NULL,
  `备注` varchar(255) DEFAULT NULL,
  `密码` varchar(255) DEFAULT NULL,
  `确认密码` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`员工编号`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=1024 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of staff_management
-- ----------------------------
INSERT INTO `staff_management` VALUES ('1003', '43', '', '员工', '43', '43', '', '43', '43');
INSERT INTO `staff_management` VALUES ('1005', 'as', '阿三', '主管', '432432', '2343234', '', '11', '11');
INSERT INTO `staff_management` VALUES ('1006', 'qw', '千瓦', '主管', '2323243', '4343', '', '23', '23');
INSERT INTO `staff_management` VALUES ('1007', '33', '环境', '员工', '43', '43', '', '22', '22');
INSERT INTO `staff_management` VALUES ('1008', '4fd', '热恩', '员工', 'asd', '213213', '', '3', '3');
INSERT INTO `staff_management` VALUES ('1009', '222', 'f对方的', '员工', '222', '3434', '', '33', '33');
INSERT INTO `staff_management` VALUES ('1010', 'fg', '规划', '员工', '34343', '232323', '', '3', '3');
INSERT INTO `staff_management` VALUES ('1011', '45454', '忽然', '员工', '5454', '22221', '', '22', '22');
INSERT INTO `staff_management` VALUES ('1012', 'gfd', '观湖国际', '员工', '34342', '3232', '', '22', '22');
INSERT INTO `staff_management` VALUES ('1014', 'sdfds', '共和国和', '员工', '2132', '1212', '', '232', '232');
INSERT INTO `staff_management` VALUES ('1015', '安安', '安安', '员工', '2131234', '312414', '', '23', '23');
INSERT INTO `staff_management` VALUES ('1017', '嗷嗷', '飒飒', '主管', '421413', '3141341', '', '21', '21');
INSERT INTO `staff_management` VALUES ('1018', '11', '32', '员工', '2223', '4343', '', '2', '2');
INSERT INTO `staff_management` VALUES ('1019', '阿三', '哎哎哎', '主管', '21414', '111223', '', '21', '21');
INSERT INTO `staff_management` VALUES ('1020', '请求', '全球', '主管', '1234343', '3431413', '', '2', '2');
INSERT INTO `staff_management` VALUES ('1021', 'stt', 'shi', '主管', 'ssss', '177', '', '123', '123');
INSERT INTO `staff_management` VALUES ('1022', '111', 'sss', '员工', '111', '111', '11', '111', '111');
INSERT INTO `staff_management` VALUES ('1023', '11', '11', '员工', '11', '11', '', '11', '11');

-- ----------------------------
-- Table structure for storage_copy
-- ----------------------------
DROP TABLE IF EXISTS `storage_copy`;
CREATE TABLE `storage_copy` (
  `订单号` int(11) NOT NULL AUTO_INCREMENT,
  `产品名称` varchar(50) DEFAULT NULL,
  `产品编号` char(15) DEFAULT NULL,
  `标签编号` int(15) DEFAULT NULL,
  `数量` int(7) DEFAULT NULL,
  `仓库` varchar(50) DEFAULT NULL,
  `管理员` varchar(50) DEFAULT NULL,
  `入库时间` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`订单号`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=123467 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of storage_copy
-- ----------------------------
INSERT INTO `storage_copy` VALUES ('1', '1', '1', '1', '0', 'C仓', '43', '2018-06-07 09:30:56');
INSERT INTO `storage_copy` VALUES ('5', '5', '5', '5', '5', 'e仓', '阿三', '2018-04-25 19:44:11');
INSERT INTO `storage_copy` VALUES ('6', 'Iphone', '1112', '3', '17', 'C仓', '安安', '2018-01-09');
INSERT INTO `storage_copy` VALUES ('323', '22', '11', '223', '7', 'C仓', '安安', '2018-04-28 11:31:59');
INSERT INTO `storage_copy` VALUES ('3333', '小米', '121', '0', '43', 'A仓', 'sss', 'dfadf');
INSERT INTO `storage_copy` VALUES ('123456', '零件', '1233', '4', '55', 'b仓', '安安', '2018-06-06 11:30:51');
INSERT INTO `storage_copy` VALUES ('123457', 'a\'d\'f', '多发发', '0', '0', 'C仓', '43', '2018-06-07 09:37:21');
INSERT INTO `storage_copy` VALUES ('123458', '1232', '23', '324', '234', 'C仓', '43', '2018-06-07 09:42:29');
INSERT INTO `storage_copy` VALUES ('123459', 'dsg', '爱的色放', '0', '0', 'C仓', '43', '2018-06-07 09:57:39');
INSERT INTO `storage_copy` VALUES ('123460', '1', '3', '3', '4', 'C仓', '43', '2018-06-07 09:59:16');
INSERT INTO `storage_copy` VALUES ('123461', '士大夫', '9787512413122', '2', '0', 'C仓', '43', '2018-06-07 11:03:01');
INSERT INTO `storage_copy` VALUES ('123462', '12123', '6959591500045', '3', '0', 'C仓', '43', '2018-06-07 11:03:18');
INSERT INTO `storage_copy` VALUES ('123463', '士大夫', '9787512413122', '3', '0', 'C仓', '43', '2018-06-07 11:07:48');
INSERT INTO `storage_copy` VALUES ('123464', '士大夫', '9787512413122', '7', '0', 'C仓', '43', '2018-06-07 11:08:45');
INSERT INTO `storage_copy` VALUES ('123465', '士大夫', '9787512413122', '7', '0', 'C仓', '43', '2018-06-07 11:09:02');
INSERT INTO `storage_copy` VALUES ('123466', '士大夫', '9787512413122', '1', '0', 'C仓', '43', '2018-06-07 15:34:29');

-- ----------------------------
-- Table structure for stores_management
-- ----------------------------
DROP TABLE IF EXISTS `stores_management`;
CREATE TABLE `stores_management` (
  `仓库编号` int(255) NOT NULL AUTO_INCREMENT,
  `仓库名称` varchar(255) DEFAULT NULL,
  `仓库类型` varchar(255) DEFAULT NULL,
  `现有库存` varchar(255) DEFAULT NULL,
  `库存容量` int(255) DEFAULT NULL,
  `状态` varchar(255) DEFAULT NULL,
  `管理员` varchar(255) DEFAULT NULL,
  `联系电话` int(255) DEFAULT NULL,
  `备注` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`仓库编号`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of stores_management
-- ----------------------------
INSERT INTO `stores_management` VALUES ('1', 'C仓', '冷冻库', '23', '500', '100', '33', '55', '');
INSERT INTO `stores_management` VALUES ('2', 'b仓', '电子产品', '300', '1000', '使用中', '嗷嗷', '3141341', '');
INSERT INTO `stores_management` VALUES ('3', 'd仓', '熟食', '200', '700', '使用中', '3', '4', '');
INSERT INTO `stores_management` VALUES ('4', 'e仓', '电子', '101', '1000', '使用中', 'qw', '4343', '');
