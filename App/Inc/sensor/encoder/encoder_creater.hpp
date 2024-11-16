#ifndef _ENCODER_CREATER_HPP_
#define _ENCODER_CREATER_HPP_

#include "ieh24096.hpp"

namespace sensor::encoder{
	enum struct NAME{
		IEH24096 = 0,
	};
	class Creater{
	private:
		std::unique_ptr<Product> encoder_;
		NAME name_;
	public:
		Creater(NAME name);
		std::unique_ptr<Product> Create(TIM_HandleTypeDef* htim, uint32_t channel);
		~Creater() = default;
	};

	class Combine{
	private:
	std::unique_ptr<sensor::encoder::Product> encoder_l_;
	std::unique_ptr<sensor::encoder::Product> encoder_r_;
	public:
	Combine();
	void Init();
	void Start();
	void ReadVal();
	void Reset();
	void Stop();
	void GetOffset();
	void Update();
	std::unique_ptr<state::Motion>& get_raw_ref();
	std::unique_ptr<state::Motion>& get_val_ref();
	~Combine() = default;

	};
}

#endif /* _ENCODER_CREATER_HPP_ */