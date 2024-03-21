#pragma once
#include <graphics.h>
#include <conio.h>
#include<iostream>
#include <cmath>
#include <vector>
#include <random>
#include <time.h>
#define block_width width/40
#define block_height height/24
#define HONEY RGB(240,255,240)
#define Lavender RGB(255,240,245)
#define Azure RGB(240,255,255)
#define Champagne RGB(250,235,215)
#define NKU RGB(126,12,1110)
#define TJU RGB(3,79,163)




using namespace std;

const int width = 1200;
const int height = 742;

//随机数生成器,生成食物的随机x,y坐标
//用随机设备作为生成种子
std::random_device devseed;

std::mt19937 generator(devseed());

uniform_int_distribution<int> randomFoodCorrdinate_x(1,block_width);
uniform_int_distribution<int> randomFoodCorrdinate_y(0, block_height - 1);


class Snake {

private:
	struct snake_body_data
	{
		int x;
		int y;

		//重载+和-运算符
		snake_body_data operator+(const snake_body_data& other)
		{
			return { x + other.x,y + other.y };
		}

		snake_body_data operator-(const snake_body_data& other)
		{
			return { x - other.x,y - other.y };
		}

		//判空函数
		bool empty()const
		{
			return (x == 0 && y == 0);
		}

	};

	//开始先指定一些蛇坐标的基本数据，然后用vector存储
	//可不可以随机生成一串连续的数字然后把这个作为蛇的基本坐标？
	snake_body_data sd[14] = { {14,11},
	{13,11},
	{13,10},
	{12,10},
	{11,10},
	{11,9},
	{11,8},
	{11,7},
	{10,7},
	{9,7},
	{8,7},
	{7,7} };


	vector<snake_body_data> m_snake;

	//四个基向量,只能放这里，宏定义就无法使用这个结构
	snake_body_data UP = { 0,-1 };
	snake_body_data DOWN = { 0,1 };
	snake_body_data LEFT = { -1,0 };
	snake_body_data RIGHT = { 1,0 };

public:
	//用于创建蛇的身体,这里给定一些数据
	void creatSnake()
	{
		//从创建的结构体中逐个Pushback进去，效率低！
		int leng = sizeof(sd) / sizeof(snake_body_data);	//计算实际长度
		for (int i = 0; i < leng; i++)
		{
			m_snake.push_back(sd[i]);
		}

	}



public:
	//移动部分
		//蛇的自动移动
	void autoMove()
	{
		if (_kbhit())
			userMove();
		else
			dircMove(m_snake[0] - m_snake[1]);	//蛇头和蛇头后面一个元素的坐标向量可以表示蛇头的朝向，这也就是蛇自动移动的方向


	}


	//用户按下按键之后改变运动方向
	//怎么融入到automove中？
	//在每次调用autoMove之前判断是否有按下键盘如果有的话就调用userMove
	//判断无法移动就看移动方向是否和蛇头方向相加为0，为0就不调用userMove
	void userMove()
	{
		int userkey = _getch();

		//这个结构肯定可以优化的
		switch (userkey)
		{
		case'w':
		case'W':
			dircMove(UP);
			cout << "按下W键，蛇向上移动";
			break;
		case's':
		case'S':
			dircMove(DOWN);
			cout << "按下S键，蛇向上移动";
			break;
		case'a':
		case 'A':
			dircMove(LEFT);
			cout << "按下A键，蛇向上移动";
			break;
		case 'd':
		case'D':
			dircMove(RIGHT);
			cout << "按下D键，蛇向上移动";
			break;


		}
	}

	void dircMove(snake_body_data vec)
	{

		//蛇头和蛇头后面一个元素的坐标向量可以表示蛇头的朝向，这也就是蛇自动移动的方向
		snake_body_data snakeDirc = m_snake[0] - m_snake[1];

		//判断能否成功键入按键
		if (!vec.empty())
		{
			// 计算新的蛇头位置
			snake_body_data newHead = m_snake[0] + vec;

			// 将新的蛇头插入到蛇身体的最前面
			m_snake.insert(m_snake.begin(), newHead);

			// 移除蛇尾
			m_snake.pop_back();
		}
	}


	//蛇的增长部分

	//食物的产生，被吃掉，判定死亡部分


	//绘制部分
		//绘制每一个小方块，蛇的基础单元
	void DrawUintBlock(int x, int y)
	{
		fillrectangle(x * block_width, y * block_height, (x - 1) * block_width, (y + 1) * block_height);
	}

	//绘制蛇
	void DrawSnak()
	{
		for (int i = 0; i < m_snake.size(); i++)
		{
			if (0 == i)
				setfillcolor(NKU);
			else
				setfillcolor(TJU);
			DrawUintBlock(m_snake[i].x, m_snake[i].y);
		}

	}
public:
	//绘制背景
	void DrawBK()
	{
		//绘制背景图
		setlinecolor(RED);
		for (int i = 0; i <= 40; i++)
		{
			//Sleep(10);	//开屏还行，游戏中影响体验
			line(i * block_width, 0, i * block_width, height);
		}
		for (int i = 0; i <= 24; i++)
		{
			//Sleep(10);
			line(0, i * block_height, width, i * block_height);
		}

	}

	void disPlaySnakeCorrdinate()
	{
		for (int i = 0; i < m_snake.size(); i++)
			cout << "(" << m_snake[i].x << "," << m_snake[i].y << ")" << " ";
		cout << '\n';
	}

	

	//让Food成为Snake类的友元类
	class Food;
	friend class Food;

	//食物类的本质就是渲染后的方格，我们可以用产生随机数的方法在坐标范围内生成食物随机数坐标
	class Food
	{

	};
};




//判定蛇死亡函数
void deadJudge()
{

}

