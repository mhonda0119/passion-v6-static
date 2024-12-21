#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

#include <iostream>
#include <memory>
#include <cstdint>

#include "states.hpp"
#include "wall.hpp"
#include "flags.hpp"
#include "drive.hpp"
#include "encoder_creater.hpp"
#include "eeprom.hpp"

namespace maze{

    class Search{
        private:
        uint8_t map_[16][16];   //マップ格納配列
        uint8_t smap_[16][16]; //歩数マップ格納配列
        uint8_t wall_info_;    //壁情報格納変数
        uint8_t goal_x_, goal_y_;//ゴール座標
        uint8_t route_[256];  //最短経路格納配列
        uint8_t r_cnt_;      //経路カウンタ
        static constexpr uint8_t DIR_TURN_R90 = 0x01;
        static constexpr uint8_t DIR_TURN_L90 = 0xff;
        static constexpr uint8_t DIR_TURN_180 = 0x02;
        state::COORD_DIR mouse_;
        std::unique_ptr<sensor::Wall>& wall_;
        std::unique_ptr<peripheral::Wait>& wait_;
        std::unique_ptr<drive::Core>& core_;
        std::unique_ptr<sensor::encoder::Combine>& encoder_;
        std::unique_ptr<peripheral::EEPROM>& eeprom_;
        
        public:
        Search(std::unique_ptr<sensor::Wall>& wall,
               std::unique_ptr<peripheral::Wait>& wait,
               std::unique_ptr<drive::Core>& core,
               std::unique_ptr<sensor::encoder::Combine>& encoder,
               std::unique_ptr<peripheral::EEPROM>& eeprom,
               uint8_t goal_x,uint8_t goal_y);
        void AdvPos();    //マウスの位置情報を前進
        void GetWallInfo(); //壁情報取得
        void WriteMap();    //マップ書き込み
        void ConfRoute();     //次ルートの確認
        void MapInit();      //マップデータ初期化
        void TurnDir(uint8_t t_pat);//自機方向情報変更
        void MakeSmap();  //歩数マップ作成
        void MakeRoute();  //最短経路検索
        void set_goal(uint8_t x,uint8_t y); //ゴール座標設定
        void SearchInit();  //探索初期化
        void StoreMapEEPROM();  //マップ情報をEEPROMに保存
        void LoadMapEEPROM();  //マップ情報をEEPROMから読み込み

        void SearchB();    //足立法探索

        ~Search() = default;
    };
}


#endif // _SEARCH_HPP_
