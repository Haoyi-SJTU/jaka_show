#include <iostream>
#include <thread>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <boost/thread/thread.hpp>

#include <JAKAZuRobot.h>
#include <jkerr.h>
#include <jktypes.h>
#include <jakaAPI.h>

using namespace std;

const char ip[] = "10.5.5.100";
JAKAZuRobot test;

// #define RUN_HAND  //带手操作
// #define XUANCHUAN //节卡宣传片动作
#define APPLE   //苹果
#define BANANA  //香蕉
// #define TEST_EYE  //求逆解的测试

int start_JAKA(const char *ip)
{
    if (!abs(test.login_in(ip)))
    {
        if (!abs(test.power_on())) //
        {
            if (!abs(test.enable_robot())) //
            {
                return 1;
            }
            else
            {
                std::cout << "妹有使能成功！" << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "妹有上电啊" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "妹找到机器人啊！IP错了？" << std::endl;
        return 0;
    }
}

int print_pos()
{
	JointValue joint_position;
	CartesianPose goal;
	test.get_joint_position(&joint_position);
	test.get_tcp_position(&goal);
    std::cout << "关节角(" << joint_position.jVal[0] << "," << joint_position.jVal[1] << "," << joint_position.jVal[2] << "," << joint_position.jVal[3] << "," << joint_position.jVal[4] << "," << joint_position.jVal[5] << ")(rad)" << std::endl;
    std::cout << "笛卡尔坐标(" << goal.tran.x << "," << goal.tran.y << "," << goal.tran.z << "," << goal.rpy.rx << "," << goal.rpy.ry << "," << goal.rpy.rz << ")(rad)" << std::endl;
    return 1;
}

int main()
{

	if(start_JAKA(ip))
	{
		std::cout << "机器人已使能" << std::endl;

		JointValue joint_position;
		CartesianPose goal0({-182.259,-330.424,235.139,1.82203,0.822406,-0.298047});
		JointValue joint_position0_ref({0.2,0.15,1.7,-0.12,0,4.5});// ready to pick apple
		

		// CartesianPose goal1({-182.3,-330.4,235.1,1.82,0.82,-0.3});
        
		JointValue joint_position1_ref({0.2,0.15,1.7,-0.12,0,4.5});
        JointValue joint_position1({0.21661,0.692657,1.7094,-0.0285235,-0.3982,4.31342});// apple pick

        JointValue joint_position2_ref({-0.0113535,0.366626,1.97331,-0.0893074,-0.653788,3.9796});//ready to pick orange
        JointValue joint_position2({-0.0171779,0.965657,2.07581,-0.0588915,-1.35687,3.92999});//orange pick

		JointValue joint_position3({0.753168,0.318629,1.71913,-0.0720382,-0.384802,4.02232});// ready to open
        JointValue joint_position4({0.753264,0.669419,1.84591,-0.0356061,-0.861798,3.97872});// ready to open
        double speed = 0.8;
        uint8_t open[8] = {0xAA,0x55,0xDD,0x02,0xC8,0x01,0xA7};
		uint8_t stop[8] = {0xAA,0x55,0xDD,0x02,0xC8,0x03,0xA9};
        uint8_t close[8] = {0xAA,0x55,0xDD,0x02,0xC8,0x02,0xA8};	

        uint8_t open_five_finger[8] = {0xAA,0x55,0xDD,0x02,0xA1,0x01,0x80};
        uint8_t close_five_finger[8] = {0xAA,0x55,0xDD,0x02,0xA1,0x02,0x81};	

        test.send_tio_rs_command(1, open, 8);
        sleep(5);
        
        // test.joint_move(&joint_position0, ABS, TRUE, speed + 0.3);
        JointValue shenchu({0.103359,0.359088,1.1947,3.03872,-0.0233459,0.872222});// ready to open
        JointValue suohui({0.0976909,-0.398076,2.14758,0.0278743,-1.72373,3.97976});// ready to open
        print_pos();
#ifdef TEST_EYE
        CartesianPose goal({-182.3,-230.4,235.1,1,0.82,-0.3});//402.41,-145.31,310.94,0,0,0
        JointValue joint_position0;// ready to pick bana
        if(test.kine_inverse(&joint_position0_ref, &goal, &joint_position0))
        {std::cout<<"逆解计算失败！"<<std::endl;}
        test.joint_move(&joint_position0, ABS, TRUE, speed - 0.6);
        print_pos();
#endif

#ifdef XUANCHUAN
        sleep(0.5);
        // test.send_tio_rs_command(1, close, 8);
        test.send_tio_rs_command(1, open_five_finger, 8);
        // sleep(0.5);
        // test.joint_move(&suohui, ABS, TRUE, speed + 0.3);
        sleep(2);
        test.joint_move(&shenchu, ABS, TRUE, speed);
        test.send_tio_rs_command(1, close_five_finger, 8);
		// test.send_tio_rs_command(1, open, 8);
        sleep(1);
#endif

#ifdef APPLE
        test.joint_move(&joint_position0_ref, ABS, TRUE, speed + 0.3);
        test.joint_move(&joint_position1, ABS, TRUE, speed);

        print_pos();

		sleep(0.2);
		test.send_tio_rs_command(1, close, 8);
		sleep(0.2);
		test.send_tio_rs_command(1, stop, 8);
		sleep(1);
        test.joint_move(&joint_position3, ABS, TRUE, speed-0.1);
		test.joint_move(&joint_position4, ABS, TRUE, speed-0.1);
		test.send_tio_rs_command(1, open, 8);
        sleep(1);
#endif

#ifdef BANANA
        test.joint_move(&joint_position2_ref, ABS, TRUE, speed + 0.3);
        test.joint_move(&joint_position2, ABS, TRUE, speed);

        print_pos();

		sleep(0.2);
		test.send_tio_rs_command(1, close, 8);
		sleep(0.2);
		test.send_tio_rs_command(1, stop, 8);
		sleep(1);
        test.joint_move(&joint_position3, ABS, TRUE, speed-0.1);
		test.joint_move(&joint_position4, ABS, TRUE, speed-0.1);
		test.send_tio_rs_command(1, open, 8);
        sleep(1);
#endif

    	return 0;
	}
}

