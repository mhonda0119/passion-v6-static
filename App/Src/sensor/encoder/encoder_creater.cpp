#include "encoder_creater.hpp"

namespace sensor::encoder{
	Creater::Creater(NAME name)
	:name_(name){}
	std::unique_ptr<Product> Creater::Create(TIM_HandleTypeDef* htim, uint32_t channel){
		switch(name_){
			case NAME::IEH24096:
				encoder_ = std::make_unique<IEH24096>(htim,channel);
				return std::move(encoder_);
			default:
				return nullptr;
		}
	}
}

namespace sensor::encoder{
    Combine::Combine():
	raw_(std::make_unique<state::Motion>()),
	val_(std::make_unique<state::Motion>())
	{
    std::unique_ptr<sensor::encoder::Creater> encoder_creater_ = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
        encoder_r_ = encoder_creater_->Create(&htim8, TIM_CHANNEL_ALL);
        encoder_l_ = encoder_creater_->Create(&htim4, TIM_CHANNEL_ALL);
    }
    
    void Combine::Init(){
        encoder_l_->Init();
        encoder_r_->Init();
    }

	void Combine::Start(){
		encoder_l_->Start();
		encoder_r_->Start();
	}

	void Combine::ReadVal(){
		encoder_l_->ReadVal();
		encoder_r_->ReadVal();
	}

	void Combine::Reset(){
		encoder_l_->Reset();
		encoder_r_->Reset();
	}

	void Combine::Stop(){
		encoder_l_->Stop();
		encoder_r_->Stop();
	}

	void Combine::GetOffset(){
		encoder_l_->GetOffset();
		encoder_r_->GetOffset();
	}

	void Combine::Update(){
		encoder_l_->Update();
		encoder_r_->Update();
	}

	std::unique_ptr<state::Motion>& Combine::get_raw_ref(){
		raw_->spd[static_cast<int>(state::Motion::DIR::L)] = encoder_l_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::C)];
		raw_->spd[static_cast<int>(state::Motion::DIR::R)] = -encoder_r_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::C)];//左右のエンコーダの向きが逆
		raw_->spd[static_cast<int>(state::Motion::DIR::C)] = (raw_->spd[static_cast<int>(state::Motion::DIR::L)] + raw_->spd[static_cast<int>(state::Motion::DIR::R)])/2;
		return raw_;
	}

	std::unique_ptr<state::Motion>& Combine::get_val_ref(){
		val_->spd[static_cast<int>(state::Motion::DIR::L)] = encoder_l_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)];
		val_->spd[static_cast<int>(state::Motion::DIR::R)] = -encoder_r_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)];//マイナスつけてるのは，右側は正方向が逆だから
		val_->spd[static_cast<int>(state::Motion::DIR::C)] = (val_->spd[static_cast<int>(state::Motion::DIR::L)] + val_->spd[static_cast<int>(state::Motion::DIR::R)])/2;
		val_->dist[static_cast<int>(state::Motion::DIR::L)] = encoder_l_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)];
		val_->dist[static_cast<int>(state::Motion::DIR::R)] = -encoder_r_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)];
		val_->dist[static_cast<int>(state::Motion::DIR::C)] = (val_->dist[static_cast<int>(state::Motion::DIR::L)] + val_->dist[static_cast<int>(state::Motion::DIR::R)])/2;
		return val_;
	}
}