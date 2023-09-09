#include <iostream>
#include <chrono>
#include <arm_neon.h>

#define SIZE_N 2048
// Define a macro to measure execution time of a function
#define MEASURE_TIME(func, ...)                           \
    do {                                                  \
        auto start_time = std::chrono::high_resolution_clock::now(); \
        func(__VA_ARGS__);                                \
        auto end_time = std::chrono::high_resolution_clock::now();   \
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); \
        std::cout << #func << " execution time: " << duration.count() << " us" << std::endl; \
    } while (0)

float goldenNCHW[SIZE_N] = {0.0, 8.0, 16.0, 24.0, 32.0, 40.0, 48.0, 56.0, 64.0, 72.0, 80.0, 88.0, 96.0, 104.0, 112.0, 120.0, 128.0, 136.0, 144.0, 152.0, 160.0, 168.0, 176.0, 184.0, 192.0, 200.0, 208.0, 216.0, 224.0, 232.0, 240.0, 248.0, 256.0, 264.0, 272.0, 280.0, 288.0, 296.0, 304.0, 312.0, 320.0, 328.0, 336.0, 344.0, 352.0, 360.0, 368.0, 376.0, 384.0, 392.0, 400.0, 408.0, 416.0, 424.0, 432.0, 440.0, 448.0, 456.0, 464.0, 472.0, 480.0, 488.0, 496.0, 504.0, 1.0, 9.0, 17.0, 25.0, 33.0, 41.0, 49.0, 57.0, 65.0, 73.0, 81.0, 89.0, 97.0, 105.0, 113.0, 121.0, 129.0, 137.0, 145.0, 153.0, 161.0, 169.0, 177.0, 185.0, 193.0, 201.0, 209.0, 217.0, 225.0, 233.0, 241.0, 249.0, 257.0, 265.0, 273.0, 281.0, 289.0, 297.0, 305.0, 313.0, 321.0, 329.0, 337.0, 345.0, 353.0, 361.0, 369.0, 377.0, 385.0, 393.0, 401.0, 409.0, 417.0, 425.0, 433.0, 441.0, 449.0, 457.0, 465.0, 473.0, 481.0, 489.0, 497.0, 505.0, 2.0, 10.0, 18.0, 26.0, 34.0, 42.0, 50.0, 58.0, 66.0, 74.0, 82.0, 90.0, 98.0, 106.0, 114.0, 122.0, 130.0, 138.0, 146.0, 154.0, 162.0, 170.0, 178.0, 186.0, 194.0, 202.0, 210.0, 218.0, 226.0, 234.0, 242.0, 250.0, 258.0, 266.0, 274.0, 282.0, 290.0, 298.0, 306.0, 314.0, 322.0, 330.0, 338.0, 346.0, 354.0, 362.0, 370.0, 378.0, 386.0, 394.0, 402.0, 410.0, 418.0, 426.0, 434.0, 442.0, 450.0, 458.0, 466.0, 474.0, 482.0, 490.0, 498.0, 506.0, 3.0, 11.0, 19.0, 27.0, 35.0, 43.0, 51.0, 59.0, 67.0, 75.0, 83.0, 91.0, 99.0, 107.0, 115.0, 123.0, 131.0, 139.0, 147.0, 155.0, 163.0, 171.0, 179.0, 187.0, 195.0, 203.0, 211.0, 219.0, 227.0, 235.0, 243.0, 251.0, 259.0, 267.0, 275.0, 283.0, 291.0, 299.0, 307.0, 315.0, 323.0, 331.0, 339.0, 347.0, 355.0, 363.0, 371.0, 379.0, 387.0, 395.0, 403.0, 411.0, 419.0, 427.0, 435.0, 443.0, 451.0, 459.0, 467.0, 475.0, 483.0, 491.0, 499.0, 507.0, 4.0, 12.0, 20.0, 28.0, 36.0, 44.0, 52.0, 60.0, 68.0, 76.0, 84.0, 92.0, 100.0, 108.0, 116.0, 124.0, 132.0, 140.0, 148.0, 156.0, 164.0, 172.0, 180.0, 188.0, 196.0, 204.0, 212.0, 220.0, 228.0, 236.0, 244.0, 252.0, 260.0, 268.0, 276.0, 284.0, 292.0, 300.0, 308.0, 316.0, 324.0, 332.0, 340.0, 348.0, 356.0, 364.0, 372.0, 380.0, 388.0, 396.0, 404.0, 412.0, 420.0, 428.0, 436.0, 444.0, 452.0, 460.0, 468.0, 476.0, 484.0, 492.0, 500.0, 508.0, 5.0, 13.0, 21.0, 29.0, 37.0, 45.0, 53.0, 61.0, 69.0, 77.0, 85.0, 93.0, 101.0, 109.0, 117.0, 125.0, 133.0, 141.0, 149.0, 157.0, 165.0, 173.0, 181.0, 189.0, 197.0, 205.0, 213.0, 221.0, 229.0, 237.0, 245.0, 253.0, 261.0, 269.0, 277.0, 285.0, 293.0, 301.0, 309.0, 317.0, 325.0, 333.0, 341.0, 349.0, 357.0, 365.0, 373.0, 381.0, 389.0, 397.0, 405.0, 413.0, 421.0, 429.0, 437.0, 445.0, 453.0, 461.0, 469.0, 477.0, 485.0, 493.0, 501.0, 509.0, 6.0, 14.0, 22.0, 30.0, 38.0, 46.0, 54.0, 62.0, 70.0, 78.0, 86.0, 94.0, 102.0, 110.0, 118.0, 126.0, 134.0, 142.0, 150.0, 158.0, 166.0, 174.0, 182.0, 190.0, 198.0, 206.0, 214.0, 222.0, 230.0, 238.0, 246.0, 254.0, 262.0, 270.0, 278.0, 286.0, 294.0, 302.0, 310.0, 318.0, 326.0, 334.0, 342.0, 350.0, 358.0, 366.0, 374.0, 382.0, 390.0, 398.0, 406.0, 414.0, 422.0, 430.0, 438.0, 446.0, 454.0, 462.0, 470.0, 478.0, 486.0, 494.0, 502.0, 510.0, 7.0, 15.0, 23.0, 31.0, 39.0, 47.0, 55.0, 63.0, 71.0, 79.0, 87.0, 95.0, 103.0, 111.0, 119.0, 127.0, 135.0, 143.0, 151.0, 159.0, 167.0, 175.0, 183.0, 191.0, 199.0, 207.0, 215.0, 223.0, 231.0, 239.0, 247.0, 255.0, 263.0, 271.0, 279.0, 287.0, 295.0, 303.0, 311.0, 319.0, 327.0, 335.0, 343.0, 351.0, 359.0, 367.0, 375.0, 383.0, 391.0, 399.0, 407.0, 415.0, 423.0, 431.0, 439.0, 447.0, 455.0, 463.0, 471.0, 479.0, 487.0, 495.0, 503.0, 511.0, 512.0, 520.0, 528.0, 536.0, 544.0, 552.0, 560.0, 568.0, 576.0, 584.0, 592.0, 600.0, 608.0, 616.0, 624.0, 632.0, 640.0, 648.0, 656.0, 664.0, 672.0, 680.0, 688.0, 696.0, 704.0, 712.0, 720.0, 728.0, 736.0, 744.0, 752.0, 760.0, 768.0, 776.0, 784.0, 792.0, 800.0, 808.0, 816.0, 824.0, 832.0, 840.0, 848.0, 856.0, 864.0, 872.0, 880.0, 888.0, 896.0, 904.0, 912.0, 920.0, 928.0, 936.0, 944.0, 952.0, 960.0, 968.0, 976.0, 984.0, 992.0, 1000.0, 1008.0, 1016.0, 513.0, 521.0, 529.0, 537.0, 545.0, 553.0, 561.0, 569.0, 577.0, 585.0, 593.0, 601.0, 609.0, 617.0, 625.0, 633.0, 641.0, 649.0, 657.0, 665.0, 673.0, 681.0, 689.0, 697.0, 705.0, 713.0, 721.0, 729.0, 737.0, 745.0, 753.0, 761.0, 769.0, 777.0, 785.0, 793.0, 801.0, 809.0, 817.0, 825.0, 833.0, 841.0, 849.0, 857.0, 865.0, 873.0, 881.0, 889.0, 897.0, 905.0, 913.0, 921.0, 929.0, 937.0, 945.0, 953.0, 961.0, 969.0, 977.0, 985.0, 993.0, 1001.0, 1009.0, 1017.0, 514.0, 522.0, 530.0, 538.0, 546.0, 554.0, 562.0, 570.0, 578.0, 586.0, 594.0, 602.0, 610.0, 618.0, 626.0, 634.0, 642.0, 650.0, 658.0, 666.0, 674.0, 682.0, 690.0, 698.0, 706.0, 714.0, 722.0, 730.0, 738.0, 746.0, 754.0, 762.0, 770.0, 778.0, 786.0, 794.0, 802.0, 810.0, 818.0, 826.0, 834.0, 842.0, 850.0, 858.0, 866.0, 874.0, 882.0, 890.0, 898.0, 906.0, 914.0, 922.0, 930.0, 938.0, 946.0, 954.0, 962.0, 970.0, 978.0, 986.0, 994.0, 1002.0, 1010.0, 1018.0, 515.0, 523.0, 531.0, 539.0, 547.0, 555.0, 563.0, 571.0, 579.0, 587.0, 595.0, 603.0, 611.0, 619.0, 627.0, 635.0, 643.0, 651.0, 659.0, 667.0, 675.0, 683.0, 691.0, 699.0, 707.0, 715.0, 723.0, 731.0, 739.0, 747.0, 755.0, 763.0, 771.0, 779.0, 787.0, 795.0, 803.0, 811.0, 819.0, 827.0, 835.0, 843.0, 851.0, 859.0, 867.0, 875.0, 883.0, 891.0, 899.0, 907.0, 915.0, 923.0, 931.0, 939.0, 947.0, 955.0, 963.0, 971.0, 979.0, 987.0, 995.0, 1003.0, 1011.0, 1019.0, 516.0, 524.0, 532.0, 540.0, 548.0, 556.0, 564.0, 572.0, 580.0, 588.0, 596.0, 604.0, 612.0, 620.0, 628.0, 636.0, 644.0, 652.0, 660.0, 668.0, 676.0, 684.0, 692.0, 700.0, 708.0, 716.0, 724.0, 732.0, 740.0, 748.0, 756.0, 764.0, 772.0, 780.0, 788.0, 796.0, 804.0, 812.0, 820.0, 828.0, 836.0, 844.0, 852.0, 860.0, 868.0, 876.0, 884.0, 892.0, 900.0, 908.0, 916.0, 924.0, 932.0, 940.0, 948.0, 956.0, 964.0, 972.0, 980.0, 988.0, 996.0, 1004.0, 1012.0, 1020.0, 517.0, 525.0, 533.0, 541.0, 549.0, 557.0, 565.0, 573.0, 581.0, 589.0, 597.0, 605.0, 613.0, 621.0, 629.0, 637.0, 645.0, 653.0, 661.0, 669.0, 677.0, 685.0, 693.0, 701.0, 709.0, 717.0, 725.0, 733.0, 741.0, 749.0, 757.0, 765.0, 773.0, 781.0, 789.0, 797.0, 805.0, 813.0, 821.0, 829.0, 837.0, 845.0, 853.0, 861.0, 869.0, 877.0, 885.0, 893.0, 901.0, 909.0, 917.0, 925.0, 933.0, 941.0, 949.0, 957.0, 965.0, 973.0, 981.0, 989.0, 997.0, 1005.0, 1013.0, 1021.0, 518.0, 526.0, 534.0, 542.0, 550.0, 558.0, 566.0, 574.0, 582.0, 590.0, 598.0, 606.0, 614.0, 622.0, 630.0, 638.0, 646.0, 654.0, 662.0, 670.0, 678.0, 686.0, 694.0, 702.0, 710.0, 718.0, 726.0, 734.0, 742.0, 750.0, 758.0, 766.0, 774.0, 782.0, 790.0, 798.0, 806.0, 814.0, 822.0, 830.0, 838.0, 846.0, 854.0, 862.0, 870.0, 878.0, 886.0, 894.0, 902.0, 910.0, 918.0, 926.0, 934.0, 942.0, 950.0, 958.0, 966.0, 974.0, 982.0, 990.0, 998.0, 1006.0, 1014.0, 1022.0, 519.0, 527.0, 535.0, 543.0, 551.0, 559.0, 567.0, 575.0, 583.0, 591.0, 599.0, 607.0, 615.0, 623.0, 631.0, 639.0, 647.0, 655.0, 663.0, 671.0, 679.0, 687.0, 695.0, 703.0, 711.0, 719.0, 727.0, 735.0, 743.0, 751.0, 759.0, 767.0, 775.0, 783.0, 791.0, 799.0, 807.0, 815.0, 823.0, 831.0, 839.0, 847.0, 855.0, 863.0, 871.0, 879.0, 887.0, 895.0, 903.0, 911.0, 919.0, 927.0, 935.0, 943.0, 951.0, 959.0, 967.0, 975.0, 983.0, 991.0, 999.0, 1007.0, 1015.0, 1023.0, 1024.0, 1032.0, 1040.0, 1048.0, 1056.0, 1064.0, 1072.0, 1080.0, 1088.0, 1096.0, 1104.0, 1112.0, 1120.0, 1128.0, 1136.0, 1144.0, 1152.0, 1160.0, 1168.0, 1176.0, 1184.0, 1192.0, 1200.0, 1208.0, 1216.0, 1224.0, 1232.0, 1240.0, 1248.0, 1256.0, 1264.0, 1272.0, 1280.0, 1288.0, 1296.0, 1304.0, 1312.0, 1320.0, 1328.0, 1336.0, 1344.0, 1352.0, 1360.0, 1368.0, 1376.0, 1384.0, 1392.0, 1400.0, 1408.0, 1416.0, 1424.0, 1432.0, 1440.0, 1448.0, 1456.0, 1464.0, 1472.0, 1480.0, 1488.0, 1496.0, 1504.0, 1512.0, 1520.0, 1528.0, 1025.0, 1033.0, 1041.0, 1049.0, 1057.0, 1065.0, 1073.0, 1081.0, 1089.0, 1097.0, 1105.0, 1113.0, 1121.0, 1129.0, 1137.0, 1145.0, 1153.0, 1161.0, 1169.0, 1177.0, 1185.0, 1193.0, 1201.0, 1209.0, 1217.0, 1225.0, 1233.0, 1241.0, 1249.0, 1257.0, 1265.0, 1273.0, 1281.0, 1289.0, 1297.0, 1305.0, 1313.0, 1321.0, 1329.0, 1337.0, 1345.0, 1353.0, 1361.0, 1369.0, 1377.0, 1385.0, 1393.0, 1401.0, 1409.0, 1417.0, 1425.0, 1433.0, 1441.0, 1449.0, 1457.0, 1465.0, 1473.0, 1481.0, 1489.0, 1497.0, 1505.0, 1513.0, 1521.0, 1529.0, 1026.0, 1034.0, 1042.0, 1050.0, 1058.0, 1066.0, 1074.0, 1082.0, 1090.0, 1098.0, 1106.0, 1114.0, 1122.0, 1130.0, 1138.0, 1146.0, 1154.0, 1162.0, 1170.0, 1178.0, 1186.0, 1194.0, 1202.0, 1210.0, 1218.0, 1226.0, 1234.0, 1242.0, 1250.0, 1258.0, 1266.0, 1274.0, 1282.0, 1290.0, 1298.0, 1306.0, 1314.0, 1322.0, 1330.0, 1338.0, 1346.0, 1354.0, 1362.0, 1370.0, 1378.0, 1386.0, 1394.0, 1402.0, 1410.0, 1418.0, 1426.0, 1434.0, 1442.0, 1450.0, 1458.0, 1466.0, 1474.0, 1482.0, 1490.0, 1498.0, 1506.0, 1514.0, 1522.0, 1530.0, 1027.0, 1035.0, 1043.0, 1051.0, 1059.0, 1067.0, 1075.0, 1083.0, 1091.0, 1099.0, 1107.0, 1115.0, 1123.0, 1131.0, 1139.0, 1147.0, 1155.0, 1163.0, 1171.0, 1179.0, 1187.0, 1195.0, 1203.0, 1211.0, 1219.0, 1227.0, 1235.0, 1243.0, 1251.0, 1259.0, 1267.0, 1275.0, 1283.0, 1291.0, 1299.0, 1307.0, 1315.0, 1323.0, 1331.0, 1339.0, 1347.0, 1355.0, 1363.0, 1371.0, 1379.0, 1387.0, 1395.0, 1403.0, 1411.0, 1419.0, 1427.0, 1435.0, 1443.0, 1451.0, 1459.0, 1467.0, 1475.0, 1483.0, 1491.0, 1499.0, 1507.0, 1515.0, 1523.0, 1531.0, 1028.0, 1036.0, 1044.0, 1052.0, 1060.0, 1068.0, 1076.0, 1084.0, 1092.0, 1100.0, 1108.0, 1116.0, 1124.0, 1132.0, 1140.0, 1148.0, 1156.0, 1164.0, 1172.0, 1180.0, 1188.0, 1196.0, 1204.0, 1212.0, 1220.0, 1228.0, 1236.0, 1244.0, 1252.0, 1260.0, 1268.0, 1276.0, 1284.0, 1292.0, 1300.0, 1308.0, 1316.0, 1324.0, 1332.0, 1340.0, 1348.0, 1356.0, 1364.0, 1372.0, 1380.0, 1388.0, 1396.0, 1404.0, 1412.0, 1420.0, 1428.0, 1436.0, 1444.0, 1452.0, 1460.0, 1468.0, 1476.0, 1484.0, 1492.0, 1500.0, 1508.0, 1516.0, 1524.0, 1532.0, 1029.0, 1037.0, 1045.0, 1053.0, 1061.0, 1069.0, 1077.0, 1085.0, 1093.0, 1101.0, 1109.0, 1117.0, 1125.0, 1133.0, 1141.0, 1149.0, 1157.0, 1165.0, 1173.0, 1181.0, 1189.0, 1197.0, 1205.0, 1213.0, 1221.0, 1229.0, 1237.0, 1245.0, 1253.0, 1261.0, 1269.0, 1277.0, 1285.0, 1293.0, 1301.0, 1309.0, 1317.0, 1325.0, 1333.0, 1341.0, 1349.0, 1357.0, 1365.0, 1373.0, 1381.0, 1389.0, 1397.0, 1405.0, 1413.0, 1421.0, 1429.0, 1437.0, 1445.0, 1453.0, 1461.0, 1469.0, 1477.0, 1485.0, 1493.0, 1501.0, 1509.0, 1517.0, 1525.0, 1533.0, 1030.0, 1038.0, 1046.0, 1054.0, 1062.0, 1070.0, 1078.0, 1086.0, 1094.0, 1102.0, 1110.0, 1118.0, 1126.0, 1134.0, 1142.0, 1150.0, 1158.0, 1166.0, 1174.0, 1182.0, 1190.0, 1198.0, 1206.0, 1214.0, 1222.0, 1230.0, 1238.0, 1246.0, 1254.0, 1262.0, 1270.0, 1278.0, 1286.0, 1294.0, 1302.0, 1310.0, 1318.0, 1326.0, 1334.0, 1342.0, 1350.0, 1358.0, 1366.0, 1374.0, 1382.0, 1390.0, 1398.0, 1406.0, 1414.0, 1422.0, 1430.0, 1438.0, 1446.0, 1454.0, 1462.0, 1470.0, 1478.0, 1486.0, 1494.0, 1502.0, 1510.0, 1518.0, 1526.0, 1534.0, 1031.0, 1039.0, 1047.0, 1055.0, 1063.0, 1071.0, 1079.0, 1087.0, 1095.0, 1103.0, 1111.0, 1119.0, 1127.0, 1135.0, 1143.0, 1151.0, 1159.0, 1167.0, 1175.0, 1183.0, 1191.0, 1199.0, 1207.0, 1215.0, 1223.0, 1231.0, 1239.0, 1247.0, 1255.0, 1263.0, 1271.0, 1279.0, 1287.0, 1295.0, 1303.0, 1311.0, 1319.0, 1327.0, 1335.0, 1343.0, 1351.0, 1359.0, 1367.0, 1375.0, 1383.0, 1391.0, 1399.0, 1407.0, 1415.0, 1423.0, 1431.0, 1439.0, 1447.0, 1455.0, 1463.0, 1471.0, 1479.0, 1487.0, 1495.0, 1503.0, 1511.0, 1519.0, 1527.0, 1535.0, 1536.0, 1544.0, 1552.0, 1560.0, 1568.0, 1576.0, 1584.0, 1592.0, 1600.0, 1608.0, 1616.0, 1624.0, 1632.0, 1640.0, 1648.0, 1656.0, 1664.0, 1672.0, 1680.0, 1688.0, 1696.0, 1704.0, 1712.0, 1720.0, 1728.0, 1736.0, 1744.0, 1752.0, 1760.0, 1768.0, 1776.0, 1784.0, 1792.0, 1800.0, 1808.0, 1816.0, 1824.0, 1832.0, 1840.0, 1848.0, 1856.0, 1864.0, 1872.0, 1880.0, 1888.0, 1896.0, 1904.0, 1912.0, 1920.0, 1928.0, 1936.0, 1944.0, 1952.0, 1960.0, 1968.0, 1976.0, 1984.0, 1992.0, 2000.0, 2008.0, 2016.0, 2024.0, 2032.0, 2040.0, 1537.0, 1545.0, 1553.0, 1561.0, 1569.0, 1577.0, 1585.0, 1593.0, 1601.0, 1609.0, 1617.0, 1625.0, 1633.0, 1641.0, 1649.0, 1657.0, 1665.0, 1673.0, 1681.0, 1689.0, 1697.0, 1705.0, 1713.0, 1721.0, 1729.0, 1737.0, 1745.0, 1753.0, 1761.0, 1769.0, 1777.0, 1785.0, 1793.0, 1801.0, 1809.0, 1817.0, 1825.0, 1833.0, 1841.0, 1849.0, 1857.0, 1865.0, 1873.0, 1881.0, 1889.0, 1897.0, 1905.0, 1913.0, 1921.0, 1929.0, 1937.0, 1945.0, 1953.0, 1961.0, 1969.0, 1977.0, 1985.0, 1993.0, 2001.0, 2009.0, 2017.0, 2025.0, 2033.0, 2041.0, 1538.0, 1546.0, 1554.0, 1562.0, 1570.0, 1578.0, 1586.0, 1594.0, 1602.0, 1610.0, 1618.0, 1626.0, 1634.0, 1642.0, 1650.0, 1658.0, 1666.0, 1674.0, 1682.0, 1690.0, 1698.0, 1706.0, 1714.0, 1722.0, 1730.0, 1738.0, 1746.0, 1754.0, 1762.0, 1770.0, 1778.0, 1786.0, 1794.0, 1802.0, 1810.0, 1818.0, 1826.0, 1834.0, 1842.0, 1850.0, 1858.0, 1866.0, 1874.0, 1882.0, 1890.0, 1898.0, 1906.0, 1914.0, 1922.0, 1930.0, 1938.0, 1946.0, 1954.0, 1962.0, 1970.0, 1978.0, 1986.0, 1994.0, 2002.0, 2010.0, 2018.0, 2026.0, 2034.0, 2042.0, 1539.0, 1547.0, 1555.0, 1563.0, 1571.0, 1579.0, 1587.0, 1595.0, 1603.0, 1611.0, 1619.0, 1627.0, 1635.0, 1643.0, 1651.0, 1659.0, 1667.0, 1675.0, 1683.0, 1691.0, 1699.0, 1707.0, 1715.0, 1723.0, 1731.0, 1739.0, 1747.0, 1755.0, 1763.0, 1771.0, 1779.0, 1787.0, 1795.0, 1803.0, 1811.0, 1819.0, 1827.0, 1835.0, 1843.0, 1851.0, 1859.0, 1867.0, 1875.0, 1883.0, 1891.0, 1899.0, 1907.0, 1915.0, 1923.0, 1931.0, 1939.0, 1947.0, 1955.0, 1963.0, 1971.0, 1979.0, 1987.0, 1995.0, 2003.0, 2011.0, 2019.0, 2027.0, 2035.0, 2043.0, 1540.0, 1548.0, 1556.0, 1564.0, 1572.0, 1580.0, 1588.0, 1596.0, 1604.0, 1612.0, 1620.0, 1628.0, 1636.0, 1644.0, 1652.0, 1660.0, 1668.0, 1676.0, 1684.0, 1692.0, 1700.0, 1708.0, 1716.0, 1724.0, 1732.0, 1740.0, 1748.0, 1756.0, 1764.0, 1772.0, 1780.0, 1788.0, 1796.0, 1804.0, 1812.0, 1820.0, 1828.0, 1836.0, 1844.0, 1852.0, 1860.0, 1868.0, 1876.0, 1884.0, 1892.0, 1900.0, 1908.0, 1916.0, 1924.0, 1932.0, 1940.0, 1948.0, 1956.0, 1964.0, 1972.0, 1980.0, 1988.0, 1996.0, 2004.0, 2012.0, 2020.0, 2028.0, 2036.0, 2044.0, 1541.0, 1549.0, 1557.0, 1565.0, 1573.0, 1581.0, 1589.0, 1597.0, 1605.0, 1613.0, 1621.0, 1629.0, 1637.0, 1645.0, 1653.0, 1661.0, 1669.0, 1677.0, 1685.0, 1693.0, 1701.0, 1709.0, 1717.0, 1725.0, 1733.0, 1741.0, 1749.0, 1757.0, 1765.0, 1773.0, 1781.0, 1789.0, 1797.0, 1805.0, 1813.0, 1821.0, 1829.0, 1837.0, 1845.0, 1853.0, 1861.0, 1869.0, 1877.0, 1885.0, 1893.0, 1901.0, 1909.0, 1917.0, 1925.0, 1933.0, 1941.0, 1949.0, 1957.0, 1965.0, 1973.0, 1981.0, 1989.0, 1997.0, 2005.0, 2013.0, 2021.0, 2029.0, 2037.0, 2045.0, 1542.0, 1550.0, 1558.0, 1566.0, 1574.0, 1582.0, 1590.0, 1598.0, 1606.0, 1614.0, 1622.0, 1630.0, 1638.0, 1646.0, 1654.0, 1662.0, 1670.0, 1678.0, 1686.0, 1694.0, 1702.0, 1710.0, 1718.0, 1726.0, 1734.0, 1742.0, 1750.0, 1758.0, 1766.0, 1774.0, 1782.0, 1790.0, 1798.0, 1806.0, 1814.0, 1822.0, 1830.0, 1838.0, 1846.0, 1854.0, 1862.0, 1870.0, 1878.0, 1886.0, 1894.0, 1902.0, 1910.0, 1918.0, 1926.0, 1934.0, 1942.0, 1950.0, 1958.0, 1966.0, 1974.0, 1982.0, 1990.0, 1998.0, 2006.0, 2014.0, 2022.0, 2030.0, 2038.0, 2046.0, 1543.0, 1551.0, 1559.0, 1567.0, 1575.0, 1583.0, 1591.0, 1599.0, 1607.0, 1615.0, 1623.0, 1631.0, 1639.0, 1647.0, 1655.0, 1663.0, 1671.0, 1679.0, 1687.0, 1695.0, 1703.0, 1711.0, 1719.0, 1727.0, 1735.0, 1743.0, 1751.0, 1759.0, 1767.0, 1775.0, 1783.0, 1791.0, 1799.0, 1807.0, 1815.0, 1823.0, 1831.0, 1839.0, 1847.0, 1855.0, 1863.0, 1871.0, 1879.0, 1887.0, 1895.0, 1903.0, 1911.0, 1919.0, 1927.0, 1935.0, 1943.0, 1951.0, 1959.0, 1967.0, 1975.0, 1983.0, 1991.0, 1999.0, 2007.0, 2015.0, 2023.0, 2031.0, 2039.0, 2047.0};






// // Function to convert NHWC data to NCHW data
// void convertData(float* input, float* output, int nChannels, int height, int width, float* output) {
//     // Calculate the total size of the new array
//     // int newSize = nChannels * height * width;

//     // Allocate a new array to hold the converted data
//     // *output = malloc(sizeof( char) * newSize);

//     // Copy the data from the input array to the output array
//     for (int i = 0; i < nChannels; i++) {
//         memcpy(*output + i * height * width, input + i * height * width, sizeof(float));
//     }
// }

// void nhwc_to_nchw(float* nhwc_data, float* nchw_data, const int n, const int h, const int w, const int c, const int size) {
//     // int size = n * h * w * c;
//     for (int i = 0; i < size; i++) {
//         int n_index = i / (h * w * c);
//         int c_index = (i / (h * w)) % c;
//         int hw_index = i % (h * w);
//         int h_index = hw_index / w;
//         int w_index = hw_index % w;
//         float* nhwc_ptr = nhwc_data + n_index * h * w * c + h_index * w * c + w_index * c + c_index;
//         float* nchw_ptr = nchw_data + n_index * c * h * w + c_index * h * w + h_index * w + w_index;
//         *nchw_ptr = *nhwc_ptr;
//     }
// }

// void nhwc_to_nchw(float* nhwc_data, float* nchw_data, const int n, const int h, const int w, const int c, const int size) {
//     int nhw = h * w;

//     for (int i = 0; i < size; i++) {
//         int n_index = i / (nhw * c);
//         int c_index = (i / nhw) % c;
//         int hw_index = i % nhw;

//         float* nhwc_ptr = nhwc_data + n_index * nhw * c + hw_index * c + c_index;
//         float* nchw_ptr = nchw_data + n_index * c * nhw + c_index * nhw + hw_index;
//         *nchw_ptr = *nhwc_ptr;

//         // Unroll the loop for better cache utilization
//         i++; // Move to the next element
//         n_index = i / (nhw * c);
//         c_index = (i / nhw) % c;
//         hw_index = i % nhw;

//         nhwc_ptr = nhwc_data + n_index * nhw * c + hw_index * c + c_index;
//         nchw_ptr = nchw_data + n_index * c * nhw + c_index * nhw + hw_index;
//         *nchw_ptr = *nhwc_ptr;
//     }
// }


// void NHWCtoNCHW_optimized(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
//     int nhw = height * width;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int c = 0; c < channels; ++c) {
//             for (int hw = 0; hw < nhw; ++hw) {
//                 int nhwcIndex = (n * nhw * channels) + (hw * channels) + c;
//                 int nchwIndex = (n * channels * nhw) + (c * nhw) + hw;
//                 nchwData[nchwIndex] = nhwcData[nhwcIndex];
//             }
//         }
//     }
// }

// void NHWCtoNCHW_tiled(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels, const int tile_size) {
//     int nhw = height * width;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int c = 0; c < channels; ++c) {
//             for (int h_tile = 0; h_tile < height; h_tile += tile_size) {
//                 for (int w_tile = 0; w_tile < width; w_tile += tile_size) {
//                     for (int h = h_tile; h < h_tile + tile_size && h < height; ++h) {
//                         for (int w = w_tile; w < w_tile + tile_size && w < width; ++w) {
//                             for (int hw = 0; hw < nhw; ++hw) {
//                                 int nhwcIndex = (n * nhw * channels) + (hw * channels) + c;
//                                 int nchwIndex = (n * channels * nhw) + (c * nhw) + hw;
//                                 nchwData[nchwIndex] = nhwcData[nhwcIndex];
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }


void NHWCtoNCHW_optimized(const float* nhwcData, float* nchwData, const int batch_size,const int height, const int width,const int channels) {
    const int nhw = height * width;
    const int chw = nhw*channels;
    for (int n = 0; n < batch_size; ++n) {
        const int p = (n * chw);
        for (int hw = 0; hw < nhw; ++hw) {
            for (int c = 0; c < channels; ++c) {
                const int nhwcIndex = p + (hw * channels) + c;
                const int nchwIndex = p + (c * nhw) + hw;
                nchwData[nchwIndex] = nhwcData[nhwcIndex];
            }
        }
    }
}



// void NHWCtoNCHW(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
//     const int nhw = height * width;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int c = 0; c < channels; ++c) {
//             for (int hw = 0; hw < nhw; ++hw) {
//                 int nhwcIndex = (n * nhw * channels) + (hw * channels) + c;
//                 int nchwIndex = (n * channels * nhw) + (c * nhw) + hw;
//                 nchwData[nchwIndex] = nhwcData[nhwcIndex];
//             }
//         }
//     }
// }

void NHWCtoNCHW(const float* nhwc_data, float* nchw_data, int batch_size, int height, int width, int num_channels) {
    for (int b = 0; b < batch_size; ++b) {
        for (int c = 0; c < num_channels; ++c) {
            for (int h = 0; h < height; ++h) {
                for (int w = 0; w < width; ++w) {
                    int nhwc_idx = b * height * width * num_channels + h * width * num_channels + w * num_channels + c;
                    int nchw_idx = b * num_channels * height * width + c * height * width + h * width + w;
                    nchw_data[nchw_idx] = nhwc_data[nhwc_idx];
                }
            }
        }
    }
}




// void NHWCtoNCHW_neon(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
//     int nhw = height * width;
//     int chw = channels * nhw;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int c = 0; c < channels; ++c) {
//             for (int hw = 0; hw < nhw; ++hw) {
//                 // Calculate input and output indices
//                 int input_index = n * chw + hw * channels + c;
//                 int output_index = n * chw + c * nhw + hw;

//                 // Load NHWC value into a NEON register
//                 float32x4_t nhwc_value = vld1q_f32(&nhwcData[input_index]);

//                 // Store the value in NCHW format
//                 vst1q_lane_f32(&nchwData[output_index], nhwc_value, 0);
//             }
//         }
//     }
// }

// void NHWCtoNCHW_optimized_2(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
//     const int nhw = height * width;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int hw = 0; hw < nhw; ++hw) {
//             int nhwcIndexBase = (n * nhw * channels) + (hw * channels);
//             int nchwIndexBase = (n * channels * nhw) + (hw * channels);

//             // Unroll the inner loop by 4
//             for (int c = 0; c < channels; c += 4) {
//                 int nhwcIndex0 = nhwcIndexBase + c;
//                 int nchwIndex0 = nchwIndexBase + c;
//                 nchwData[nchwIndex0] = nhwcData[nhwcIndex0];

//                 int nhwcIndex1 = nhwcIndexBase + c + 1;
//                 int nchwIndex1 = nchwIndexBase + c + 1;
//                 nchwData[nchwIndex1] = nhwcData[nhwcIndex1];

//                 int nhwcIndex2 = nhwcIndexBase + c + 2;
//                 int nchwIndex2 = nchwIndexBase + c + 2;
//                 nchwData[nchwIndex2] = nhwcData[nhwcIndex2];

//                 int nhwcIndex3 = nhwcIndexBase + c + 3;
//                 int nchwIndex3 = nchwIndexBase + c + 3;
//                 nchwData[nchwIndex3] = nhwcData[nhwcIndex3];
//             }
//         }
//     }
// }


void NHWCtoNCHW_optimized_2(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
    const int nhw = height * width;

    for (int n_hw = 0; n_hw < batch_size * nhw; ++n_hw) {
        for (int c = 0; c < channels; ++c) {
            int nhwcIndex = n_hw * channels + c;
            int nchwIndex = n_hw + c * batch_size * nhw;
            nchwData[nchwIndex] = nhwcData[nhwcIndex];
        }
    }
}





// void NHWCtoNCHW_neon_optimized_2(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
//     const int nhw = height * width;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int hw = 0; hw < nhw; hw += 4) {
//             for (int c = 0; c < channels; ++c) {
//                 int nhwcIndex = (n * nhw * channels) + (hw * channels) + c;
//                 int nchwIndex = (n * channels * nhw) + (c * nhw) + hw;

//                 float32x4_t nhwcValues = vld1q_f32(&nhwcData[nhwcIndex]);
//                 float32x4x4_t transposedValues = vtrnq_f32(nhwcValues, nhwcValues);
//                 vst1q_f32(&nchwData[nchwIndex], transposedValues.val[0]);
//                 vst1q_f32(&nchwData[nchwIndex + nhw], transposedValues.val[1]);
//                 vst1q_f32(&nchwData[nchwIndex + 2 * nhw], transposedValues.val[2]);
//                 vst1q_f32(&nchwData[nchwIndex + 3 * nhw], transposedValues.val[3]);
//             }
//         }
//     }
// }


void NHWCtoNCHW_neon_optimized_3(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
    const int nhw = height * width;

    for (int n = 0; n < batch_size; ++n) {
        for (int hw = 0; hw < nhw; hw += 4) {
            for (int c = 0; c < channels; ++c) {
                int nhwcIndex = (n * nhw * channels) + (hw * channels) + c;
                int nchwIndex = (n * channels * nhw) + (c * nhw) + hw;

                float32x4_t nhwcValues = vld1q_f32(&nhwcData[nhwcIndex]);
                float32x4x2_t transposedValues = vtrnq_f32(nhwcValues, nhwcValues);
                float32x4_t transposedValues1 = transposedValues.val[0];
                float32x4_t transposedValues2 = transposedValues.val[1];
                vst1q_f32(&nchwData[nchwIndex], transposedValues1);
                vst1q_f32(&nchwData[nchwIndex + nhw], transposedValues2);
            }
        }
    }
}

// void NHWCtoNCHW_neon_opt(const float* nhwcData, float* nchwData, int batch_size, int height, int width, int channels) {
//     int nhw = height * width;
//     int chw = channels * nhw;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int hw = 0; hw < nhw; ++hw) {
//             const float* nhwc_ptr = nhwcData + n * chw + hw * channels;
//             float* nchw_ptr = nchwData + n * chw + hw;
//             int c = 0;
//             for (; c + 3 < channels; c += 4) {
//                 float32x4x4_t nhwc_values = vld4q_f32(nhwc_ptr + c);
//                 float32x4x4_t nchw_values = vtrnq_f32(nhwc_values.val[0], nhwc_values.val[1]);
//                 nchw_values = vtrnq_f32(nchw_values.val[0], nchw_values.val[1]);
//                 vst4q_f32(nchw_ptr + c * nhw, nchw_values);
//             }
//             for (; c < channels; ++c) {
//                 nchw_ptr[c * nhw] = nhwc_ptr[c];
//             }
//         }
//     }
// }



bool matchGolden(const float* input , const float* golden, const int size){
   for (int i = 0; i < size; ++i) {
        if(input[i] != golden[i]){
            std::cout<<"ERROR::Golden MisMatch\n";
            return false;
        }
    }
    std::cout<<"SUCCESS::Golden Match\n";
    return true;

}


int main() {
    // Example usage:
    int batch_size = 1;
    int height = 384;
    int width = 384;
    int channels = 2;
    const int tile_size = 32;
    const int nhwcSize = batch_size * height * width * channels;

    float *nhwcData = new float[nhwcSize];
    float *nchwData = new float[nhwcSize];
    // float *nchwData_aritmetic = new float[nhwcSize];
    float *nchwData_optimized = new float[nhwcSize];

    // Initialize NHWC data (you should replace this with your actual data)
    for (int i = 0; i < nhwcSize; ++i) {
        nhwcData[i] = i;
    }

    // Convert NHWC to NCHW
    MEASURE_TIME(NHWCtoNCHW,nhwcData, nchwData, batch_size, height, width, channels);
    // MEASURE_TIME(NHWCtoNCHW_optimized_2, nhwcData, nchwData_aritmetic,  batch_size, height, width, channels);
    MEASURE_TIME(NHWCtoNCHW_optimized,nhwcData, nchwData_optimized, batch_size, height, width, channels);

    // Print the converted data (NCHW)
    //  for (int i = 0; i < nhwcSize; ++i) {
        // printf("%.1f ", nchwData[i]);
    // }

// Match golden
//    matchGolden(nchwData,goldenNCHW,nhwcSize);
//    matchGolden(nchwData_aritmetic,goldenNCHW,nhwcSize);
   matchGolden(nchwData_optimized,nchwData,nhwcSize);

    delete[] nhwcData;
    delete[] nchwData;
    // delete[] nchwData_aritmetic;
    delete[] nchwData_optimized;
    return 0;
}





// // Function to convert NHWC data to NCHW data
// void convertData(unsigned char* input, int nChannels, int height, int width, unsigned char** output) {
//     // Calculate the total size of the new array
//     int newSize = nChannels * height * width;

//     // Allocate a new array to hold the converted data
//     *output = malloc(sizeof(unsigned char) * newSize);

//     // Copy the data from the input array to the output array
//     for (int i = 0; i < nChannels; i++) {
//         memcpy(*output + i * height * width, input + i * height * width, sizeof(unsigned char));
//     }
// }
