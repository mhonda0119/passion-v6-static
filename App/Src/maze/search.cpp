#include <iostream>

#include "search.hpp"

namespace maze{

Search::Search(std::unique_ptr<sensor::Wall>& wall,
std::unique_ptr<peripheral::Wait>& wait,
std::unique_ptr<drive::Core>& core,
std::unique_ptr<sensor::encoder::Combine>& encoder,
uint8_t goal_x,uint8_t goal_y):
goal_x_(goal_x),goal_y_(goal_y),wall_(wall),wait_(wait),
core_(core),encoder_(encoder){

}

void Search::SearchInit(){
    //----フラグの初期化----
    Flag::ResetAll();
    //----マップデータ初期化----
    this->MapInit();
    //----マウスの初期位置設定----
    mouse_.x = 0;
    mouse_.y = 0;
    mouse_.dir = 0x00;
}

void Search::AdvPos()
{
    switch (mouse_.dir)
    {
        case 0x00: // 北
            mouse_.y++;
            break;
        case 0x01: // 東
            mouse_.x++;
            break;
        case 0x02: // 南
            mouse_.y--;
            break;
        case 0x03: // 西
            mouse_.x--;
            break;
        default:
            break;
    }
}

void Search::GetWallInfo()
{
    //----壁情報の初期化----
    wall_info_ = 0x00;                 //壁情報を初期化
    //----前壁を見る----
    if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::F)]){
        //AD値が閾値より大きい（=壁があって光が跳ね返ってきている）場合
        wall_info_ |= 0x88;  //0x08              //壁情報を更新
    }
    //----右壁を見る----
    if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)]){
        //AD値が閾値より大きい（=壁があって光が跳ね返ってきている）場合
        wall_info_ |= 0x44; //0x04               //壁情報を更新
    }
    //----左壁を見る----
    if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)]){
        //AD値が閾値より大きい（=壁があって光が跳ね返ってきている）場合
        wall_info_ |= 0x11; //0x01               //壁情報を更新
    }
}

void Search::WriteMap()
{
  //====変数宣言====
  uint8_t m_temp;                               //絶対方向の壁情報格納変数
  //====壁情報の補正格納====
  m_temp = (wall_info_ >> mouse_.dir) & 0x0f;     //センサ壁情報をmouse_.dirで向きを補正させて下位4bit分を残す
  m_temp |= (m_temp << 4);                      //上位4bitに下位4bitをコピー。この作業でm_tempにNESW順で壁が格納

  //====データの書き込み====
  map_[mouse_.y][mouse_.x] = m_temp;               //現在地に壁情報書き込み
  //----周辺に書き込む----
  //北側について
  if(mouse_.y != 15){                            //現在最北端でないとき
    if(m_temp & 0x88){                          //北壁がある場合
      map_[mouse_.y + 1][mouse_.x] |= 0x22;        //北側の区画から見て南壁ありを書き込む
    }else{                                      //北壁がない場合
      map_[mouse_.y + 1][mouse_.x] &= 0xDD;        //北側の区画から見て南壁なしを書き込む
    }
  }
  //東側について
  if(mouse_.x != 15){                            //現在最東端でないとき
    if(m_temp & 0x44){                          //東壁がある場合
      map_[mouse_.y][mouse_.x + 1] |= 0x11;        //東側の区画から見て西壁ありを書き込む
    }else{                                      //東壁がない場合
      map_[mouse_.y][mouse_.x + 1] &= 0xEE;        //東側の区画から見て西壁なしを書き込む
    }
  }
  //南壁について
  if(mouse_.y != 0){                             //現在最南端でないとき
    if(m_temp & 0x22){                          //南壁がある場合
      map_[mouse_.y - 1][mouse_.x] |= 0x88;        //南側の区画から見て北壁ありを書き込む
    }else{                                      //南壁がない場合
      map_[mouse_.y - 1][mouse_.x] &= 0x77;        //南側の区画から見て北壁なしを書き込む
    }
  }
  //西側について
  if(mouse_.x != 0){                             //現在最西端でないとき
    if(m_temp & 0x11){                          //西壁がある場合
      map_[mouse_.y][mouse_.x - 1] |= 0x44;        //西側の区画から見て東壁ありを書き込む
    }else{                                      //西壁がない場合
      map_[mouse_.y][mouse_.x - 1] &= 0xBB;        //西側の区画から見て東壁なしを書き込む
    }
  }
}

void Search::ConfRoute()
{
  //----壁情報書き込み----
  this->WriteMap();

  //----最短経路上に壁があれば進路変更----
  if(wall_info_ & route_[r_cnt_]){
    this->MakeSmap();                    //歩数マップを更新
    this->MakeRoute();                   //最短経路を更新
    r_cnt_ = 0;                      //経路カウンタを0に
  }
}

void Search::MapInit()
{

  //====変数宣言====
  uint8_t x, y;                     //for文用変数

  //====初期化開始====
  //マップのクリア
  for(y = 0; y < 16; y++){          //各Y座標で実行
    for(x = 0; x < 16; x++){        //各X座標で実行
      map_[y][x] = 0xf0;             //上位4ビット（2次走行時）を壁あり，下位4ビット（1次走行時）を壁なしとする。
    }
  }

  //確定壁の配置
  for(y = 0; y < 16; y++){          //各Y座標で実行
    map_[y][0] |= 0xf1;              //最西に壁を配置
    map_[y][15] |= 0xf4;             //最東に壁を配置
  }
  for(x = 0; x < 16; x++){          //各X座標で実行
    map_[0][x] |= 0xf2;              //最南に壁を配置
    map_[15][x] |= 0xf8;             //最北に壁を配置
  }
}

void Search::TurnDir(uint8_t t_pat)
{
//====方向を変更====
  mouse_.dir = (mouse_.dir + t_pat) & 0x03;       //指定された分mouse.dirを回転させる
}

void Search::MakeSmap()
{
  //====変数宣言====
  uint8_t x, y;                                 //for文用変数

  //====歩数マップのクリア====
  for(y = 0; y <= 15; y++){                     //各Y座標で実行
    for( x = 0; x <= 15; x++){                  //各X座標で実行
      smap_[y][x] = 0xff;                        //未記入部分は歩数最大とする
    }
  }

  //====ゴール座標を0にする====
  uint8_t m_step = 0;                           //歩数カウンタを0にする
  smap_[goal_y_][goal_x_] = 0;

  //====自分の座標にたどり着くまでループ====
  do{
    //----マップ全域を捜索----
    for( y = 0; y <= 15; y++){                  //各Y座標で実行
      for( x = 0; x <= 15; x++){                //各X座標で実行
        //----現在最大の歩数を発見したとき----
        if( smap_[y][x] == m_step){              //歩数カウンタm_stepの値が現在最大の歩数
          uint8_t m_temp = map_[y][x];           //map配列からマップデータを取り出す
          if(Flag::Check(SCND)){                     //二次走行用のマップを作成する場合（二次走行時はMF.FLAG.SCNDが立っている）
           m_temp >>= 4;                       //上位4bitを使うので4bit分右にシフトさせる
          }
          //----北壁についての処理----
          if(!(m_temp & 0x08) && y != 15){      //北壁がなく現在最北端でないとき
            if(smap_[y+1][x] == 0xff){           //北側が未記入なら
              smap_[y+1][x] = m_step + 1;        //次の歩数を書き込む
            }
          }
          //----東壁についての処理----
          if(!(m_temp & 0x04) && x != 15){      //東壁がなく現在最東端でないとき
            if(smap_[y][x+1] == 0xff){           //東側が未記入なら
              smap_[y][x+1] = m_step + 1;        //次の歩数を書き込む
            }
          }
          //----南壁についての処理----
          if(!(m_temp & 0x02) && y != 0){       //南壁がなく現在最南端でないとき
            if(smap_[y-1][x] == 0xff){           //南側が未記入なら
              smap_[y-1][x] = m_step + 1;        //次の歩数を書き込む
            }
          }
          //----西壁についての処理----
          if(!(m_temp & 0x01) && x != 0){       //西壁がなく現在最西端でないとき
            if(smap_[y][x-1] == 0xff){           //西側が未記入なら
              smap_[y][x-1] = m_step + 1;        //次の歩数を書き込む
            }
          }
        }
      }
    }
    //====歩数カウンタのインクリメント====
    m_step++;
  }while(smap_[mouse_.y][mouse_.x] == 0xff);       //現在座標が未記入ではなくなるまで実行
}

void Search::MakeRoute()
{
  //====変数宣言====
  uint8_t x, y;                                 //X，Y座標
  uint8_t dir_temp =  mouse_.dir;                //マウスの方角を表すmouse.dirの値をdir_temp変数に退避させる

  //====最短経路を初期化====
  uint16_t i;
  for(i = 0; i < 256; i++){
    route_[i] = 0xff;                            //routeを0xffで初期化
  }

  //====歩数カウンタをセット====
  uint8_t m_step = smap_[mouse_.y][mouse_.x];      //現在座標の歩数マップ値を取得

  //====x, yに現在座標を書き込み====
  x = mouse_.x;
  y = mouse_.y;

  //====最短経路を導出====
  i = 0;
  do{
    uint8_t m_temp = map_[y][x];                 //比較用マップ情報の格納
    if(Flag::Check(SCND)){                           //二次走行用のマップを作成する場合（二次走行時はMF.FLAG.SCNDが立っている）
      m_temp >>= 4;                             //上位4bitを使うので4bit分右にシフトさせる
    }

    //----北を見る----
    if(!(m_temp & 0x08) && (smap_[y+1][x] < m_step)){        //北側に壁が無く、現在地より小さい歩数マップ値であれば
      route_[i] = (0x00 - mouse_.dir) & 0x03;                 //route配列に進行方向を記録
      m_step = smap_[y+1][x];                                //最大歩数マップ値を更新
      y++;                                                  //北に進んだのでY座標をインクリメント
    }
    //----東を見る----
    else if(!(m_temp & 0x04) && (smap_[y][x+1] < m_step)){   //東側に壁が無く、現在地より小さい歩数マップ値であれば
      route_[i] = (0x01 - mouse_.dir) & 0x03;                 //route配列に進行方向を記録
      m_step = smap_[y][x+1];                                //最大歩数マップ値を更新
      x++;                                                  //東に進んだのでX座標をインクリメント
    }
    //----南を見る----
    else if(!(m_temp & 0x02) && (smap_[y-1][x] < m_step)){   //南側に壁が無く、現在地より小さい歩数マップ値であれば
      route_[i] = (0x02 - mouse_.dir) & 0x03;                 //route配列に進行方向を記録
      m_step = smap_[y-1][x];                                //最大歩数マップ値を更新
      y--;                                                  //南に進んだのでY座標をデクリメント
    }
    //----西を見る----
    else if(!(m_temp & 0x01) && (smap_[y][x-1] < m_step)){   //西側に壁が無く、現在地より小さい歩数マップ値であれば
      route_[i] = (0x03 - mouse_.dir) & 0x03;                 //route配列に進行方向を記録
      m_step = smap_[y][x-1];                                //最大歩数マップ値を更新
      x--;                                                  //西に進んだのでX座標をデクリメント
    }

    //----格納データ形式変更----
    switch(route_[i]){                 //route配列に格納した要素値で分岐
    case 0x00:                        //前進する場合
      route_[i] = 0x88;                //格納データ形式を変更
      break;
    case 0x01:                        //右折する場合
      TurnDir(DIR_TURN_R90);         //内部情報の方向を90度右回転
      route_[i] = 0x44;                //格納データ形式を変更
      break;
    case 0x02:                        //Uターンする場合
      TurnDir(DIR_TURN_180);         //内部情報の方向を180度回転
      route_[i] = 0x22;                //格納データ形式を変更
      break;
    case 0x03:                        //左折する場合
      TurnDir(DIR_TURN_L90);         //内部情報の方向を90度右回転
      route_[i] = 0x11;                //格納データ形式を変更
      break;
    default:                          //それ以外の場合
      route_[i] = 0x00;                //格納データ形式を変更
      break;
    }
    i++;                              //カウンタをインクリメント
  }while( smap_[y][x] != 0);           //進んだ先の歩数マップ値が0（=ゴール）になるまで実行
  mouse_.dir = dir_temp;               //dir_tempに退避させた値をmouse.dirにリストア
}

void Search::SearchB()
{
  if(Flag::Check(SCND)){
    //load_map_from_eeprom();         //二次走行時はROMからマップ情報を取り出す
  }
    Objects::buzzer_->Play(500,200);  //スタート音を鳴らす
    Objects::led_->Toggle();          //LEDを点灯させる
    Objects::wait_->Ms(100);
    Objects::led_->Toggle();
    Objects::wait_->Ms(100);          //LEDを消灯させる  
    Objects::led_->Toggle();          //LEDを点灯させる
    Objects::wait_->Ms(100);
    Objects::led_->Toggle();          //LEDを消灯させる  
    //====スタート位置壁情報取得====
    this->GetWallInfo();                  //壁情報の初期化, 後壁はなくなる
    wall_info_ &= ~0x88;               //前壁は存在するはずがないので削除する
    this->WriteMap();                      //壁情報を地図に記入

    //====前に壁が無い想定で問答無用で前進====
    /*half_sectionA();*/
    core_->Straight(46+90,0,consts::software::SPD_SEARCH);
    //core_->Stop();
    //Objects::buzzer_->Start(500);  //スタート音を鳴らす
    this->GetWallInfo();                  //壁情報の取得
    this->AdvPos();
    this->WriteMap();

    //====歩数マップ・経路作成====
    r_cnt_ = 0;                        //経路カウンタの初期化
    this->MakeSmap();                      //歩数マップ作成
    this->MakeRoute();                     //最短経路探索（route配列に動作が格納される）

  //====探索走行====
  do{
    //----進行----
    switch(route_[r_cnt_++]){         //route配列によって進行を決定。経路カウンタを進める
      //----前進----
      case 0x88:
        //onesectionU();
        //Objects::buzzer_->Start(1000);  //前進音を鳴らす
        // core_->Straight(consts::software::ONE_BLOCK,
        // encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)],
        // encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        core_->Straight(consts::software::ONE_BLOCK,
        consts::software::SPD_SEARCH,
        consts::software::SPD_SEARCH);
        this->GetWallInfo();//壁情報の取得
        //core_->Stop();


        //Objects::buzzer_->Stop();      //前進音を止める
        break;
      //----右折----
      case 0x44:
        //Objects::buzzer_->Start(800);  //前進音を鳴らす
        core_->TurnR90(consts::software::SPD_SEARCH); //右回転
        this->TurnDir(DIR_TURN_R90);     //マイクロマウス内部位置情報でも右回転処理
        this->GetWallInfo();//壁情報の取得
        //Objects::buzzer_->Stop();      //前進音を止める

        break;
      //----180回転----
      case 0x22:
      //core_->Stop();
      //Objects::md_->Off();
      //Objects::buzzer_->Start(800,80);  //前進音を鳴らす
      //Objects::led_->On();
      
        //half_sectionD();  //半区間分減速しながら走行し停止
        core_->Straight(consts::software::HALF_BLOCK,
        consts::software::SPD_SEARCH,0);
        core_->Stop();
        Objects::wait_->Ms(100);
        core_->Spin();  //180度回転
        core_->Stop();
        this->TurnDir(DIR_TURN_180);  //マイクロマウス内部位置情報でも180度回転処理
        core_->Straight(consts::software::HALF_BLOCK,0,consts::software::SPD_SEARCH);  //半区画分加速しながら走行する
        this->GetWallInfo();//壁情報の取得
        break;
      //----左折----
      case 0x11:
        //Objects::buzzer_->Start(600);  //前進音を鳴らす
        //core_->TurnL90(encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)],0,0);
        core_->TurnL90(consts::software::SPD_SEARCH);             //左回転
        this->TurnDir(DIR_TURN_L90);     //マイクロマウス内部位置情報でも左回転処理
        this->GetWallInfo();//壁情報の取得
        //Objects::buzzer_->Stop();      //前進音を止める
        break;
    }

    this->AdvPos();                      //マイクロマウス内部位置情報でも前進処理
    this->ConfRoute();                   //最短経路で進行可能か判定

    }while((mouse_.x != goal_x_) || (mouse_.y != goal_y_));   //現在座標とgoal座標が等しくなるまで実行

    //halfsectionD
    core_->Straight(consts::software::HALF_BLOCK,consts::software::SPD_SEARCH,0);  //半区画分減速しながら走行し停止
    core_->Stop();
    this->GetWallInfo();//壁情報の取得

    Objects::wait_->Ms(1000);  //スタートでは***2秒以上***停止しなくてはならない
    //rotate_180();
    core_->Spin();  //180度回転
    this->TurnDir(DIR_TURN_180);  //マイクロマウス内部位置情報でも180度回転処理
    this->GetWallInfo();//壁情報の取得
    // if(Flag::Check(SCND)){
    // store_map_in_eeprom();          //一次探索走行時はROMにマップ情報を書き込む
    // }
    //====探索終了音を鳴らす====
    Objects::buzzer_->Play(987,200);  //探索終了音を鳴らす
    Objects::buzzer_->Play(783,500);
}

void Search::set_goal(uint8_t goal_x,uint8_t goal_y)
{
    goal_x_ = goal_x;
    goal_y_ = goal_y;

}

}
