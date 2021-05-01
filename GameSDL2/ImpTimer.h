
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();

	void start();    //Dem thoi gian
	void stop();    
	void paused();   
	void unpaused();

	int get_ticks();  //Thoi gian thuc su troi qua

	bool is_started();
	bool is_paused();

private:
	int start_tick_;   //Thoi diem bat dau chay
	int paused_tick_;  //Khi tam dung

	bool is_paused_;
	bool is_started_;

};
#endif 
