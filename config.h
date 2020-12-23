#ifndef CONFIG_H
#define CONFIG_H

const int kBoardSize = 535; //棋盘大小
const int kBoardMargin = 23; // 棋盘边缘空隙
const int kRadius = 14; // 棋子半径
const int kPointR = 3; // 中心红点半径
const int kMarkSize = 8; // 落子标记边长
const int kBlockSize = 35; // 格子的大小
const int kPosDelta = 18; // 鼠标点击的模糊距离上限
const int kAIDelay = 5; // AI下棋的思考时间(s)
const int kBoardSizeNum = 15;

///** 连五 */
//const double kFive = 1e6;
///** 活四 */
//const double kAliveFour = 1e4;
///** 死四 */
//const double kBlockedFour = 1e3;
///** 活三 */
//const double kAliveThree = 1e3;
///** 死三 */
//const double kBlockedThree = 1e2;
///** 活二 */
//const double kAliveTwo = 20;
///** 死二 */
//const double kBlockedTwo = 2;
///** 无穷值表示胜利 */
//const double kInf = 1e9;
/** UCB中的探索参数 */
const double kConfidence = 1;


#endif //CONFIG_H
