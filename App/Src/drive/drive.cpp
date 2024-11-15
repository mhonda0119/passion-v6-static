#include "drive.hpp"

// namespace drive{
//     Core::Core(){
//         objects_ = std::make_unique<Objects>();
//         design_ = std::make_unique<drive::Design>();
//     }
//     void Core::Init(){
//         objects_->md_->On();
//         objects_->md_->Dir(state::MOTOR::LEFT,state::MOTOR::FWD);
//         objects_->md_->Dir(state::MOTOR::RIGHT,state::MOTOR::FWD);
//         objects_->md_->Start();
//     }
//     void Core::AD(float dist , float spd_in , float spd_out){
//         //加速度を取得
//         design_->TrapeAccel(dist,spd_in,spd_out);
//         std::cout << "1" << std::endl;
//         //加速度を設定
//         peripheral::IT::r_maccel_ = design_->get_accel();
//         std::cout << "2" << std::endl;
//         //回転角度カウントをリセット
//         peripheral::IT::reg_motor_->motion_->val_->angle[static_cast<int>(state::Motion::AXIS::Z)] = 0;
//         std::cout << "3" << std::endl;
//         //IMUの積算値をリセット
//         objects_->imu_->Reset();
//         std::cout << "4" << std::endl;
//         //距離をリセット(そくていした距離と，エンコーダーのカウンタ)
//         peripheral::IT::reg_motor_->motion_->val_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
//         std::cout << "5" << std::endl;
//         //エンコーダーのカウンタをリセット
//         objects_->encoder_l_->Reset();
//         std::cout << "6" << std::endl;
//         objects_->encoder_r_->Reset();
//         std::cout << "7" << std::endl;
//         //走行を開始す
//         objects_->md_->Start();
//         objects_->md_->Duty(20,20);
//         std::cout << "8" << std::endl;
//         //実際の距離が目標距離になるまで走行
//         if(peripheral::IT::r_maccel_ >= 0){
//             std::cout << "r_maccel:" << peripheral::IT::r_maccel_ << std::endl;
//             while(peripheral::IT::reg_motor_->motion_->val_->dist[static_cast<int>(state::Motion::DIR::C)] < dist){
//             std::cout << "dist:" << peripheral::IT::reg_motor_->motion_->val_->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
//             };
//         std::cout << "9" << std::endl;
//         }else if(peripheral::IT::r_maccel_ < 0){
//             while(peripheral::IT::reg_motor_->motion_->val_->dist[static_cast<int>(state::Motion::DIR::C)] < dist
//             && peripheral::IT::reg_motor_->r_->spd[static_cast<int>(state::Motion::DIR::C)] > 0){
                
//             };
//         std::cout << "10" << std::endl;
//         }
//         //割込み内の変数をリセット
//         peripheral::IT::r_maccel_ = 0;
//         std::cout << "11" << std::endl;
//         peripheral::IT::reg_motor_->r_Reset();
//         std::cout << "12" << std::endl;
//         peripheral::IT::reg_motor_->PID_Reset();
//         std::cout << "13" << std::endl;
//         peripheral::IT::reg_motor_->Reset();
//         std::cout << "14" << std::endl;
//         //走行距離カウンタをリセット
//         peripheral::IT::reg_motor_->motion_->val_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
//         //std::cout << "reg_motor_ motion_ val_:" << peripheral::IT::reg_motor_->motion_->val_->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
//         std::cout << "15" << std::endl;
//         //エンコーダーのカウンタをリセット
//         objects_->encoder_l_->Reset();
//         std::cout << "16" << std::endl;
//         objects_->encoder_r_->Reset();
//         std::cout << "17" << std::endl;
//     }

// }