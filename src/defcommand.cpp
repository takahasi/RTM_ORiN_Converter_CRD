#include "defcommand.h"

//CaoProviderの設定
char* ControllerName;
char* CaoProvName;
char* ConnectionParam;
char* Manufactur;
char* RobotName;
int AxisNum;
char* AxialType[10];
bool IsGripper;

//CommonCommandの設定
//未実装の関数には"NOT_IMPLEMENTED"を代入する
//C1.アラームクリア
char* C1_Command;
//C2.アラーム情報の取得
char* C2_Command;
//C3.関節座標系の位置フィードバック情報の取得
char* C3_Command;
//C4.マニピュレータ情報の取得
char* C4_Command;
//C5.関節座標系のソフトリミット値を取得
char* C5_Command;
//C6.ユニットの状態取得
char* C6_Command;
//C7.全軸サーボOFF
char* C7_Command;
char* C7_Option;
//wchar_t* C7_Option;
//C8.全軸サーボON
char* C8_Command;
char* C8_Option;
//wchar_t* C8_Option;
//C9.関節座標系のソフトリミット値設定
char* C9_Command;

//MiddleLevelMotionCommandの設定
//M1.グリッパを閉じる
char* M1_Command;
//M2.マニピュレータの設定位置を取得
char* M2_Command;
//M3.直交座標系の位置フィードバック情報の取得
char* M3_Command;
//M4.直交動作時の最大動作速度を取得
char* M4_Command;
//M5.関節動作時の最大動作速度を取得
char* M5_Command;
//M6.直交動作時の最小動作加速速度を取得
char* M6_Command;
//M7.関節動作時の最小動作加速速度を取得
char* M7_Command;
//M8.直交座標系のソフトリミット値を取得
char* M8_Command;
//M9.グリッパの開閉動作
char* M9_Command;
//M10.直交座標系の直線補間(絶対指令)
char* M10_Command;
//M11.直交座標系の直線補間(相対指令)
char* M11_Command;
//M12.関節座標系の直線補間(直交・絶対指令)
char* M12_Command;
//M13.関節座標系の直線補間(直交・相対指令)
char* M13_Command;
//M14.関節座標系の直線補間(関節・絶対指令)
char* M14_Command;
//M15.関節座標系の直線補間(関節・相対指令)
char* M15_Command;
//M16.グリッパを開く
char* M16_Command;
//M17.動作の一時停止
char* M17_Command;
//M18.動作の再開
char* M18_Command;
//M19.動作の停止
char* M19_Command;
//M20.直交動作時の加速時間を設定
char* M20_Command;
//M21.関節動作時の加速時間を設定
char* M21_Command;
//M22.マニピュレータの設置位置を設定
char* M22_Command;
//M23.制御点のフランジ面からのオフセット量を設定
char* M23_Command;
//M24.直交動作時の最大動作速度を設定
char* M24_Command;
//M25.関節動作時の最大動作速度を設定
char* M25_Command;
//M26.直交動作時の最小動作加速時間を設定
char* M26_Command;
//M27.関節動作時の最小動作加速時間を設定
char* M27_Command;
//M28.直交座標系のソフトリミット値を設定
char* M28_Command;
//M29.直交動作時の速度を設定
char* M29_Command;
//M30.関節動作時の速度を設定
char* M30_Command;
//M31.直交座標系の円弧補間(絶対指令)
char* M31_Command;
//M32.直交座標系の円弧補間(相対指令)
char* M32_Command;
//M33.原点復帰時の位置・姿勢を設定
char* M33_Command;
//M34.原点復帰時の位置・姿勢を取得
char* M34_Command;
//M35.原点復帰動作
char* M35_Command;