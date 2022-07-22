/**
* @file    IThread.h
* @brief
*
* @date	   2022/07/22 2022”N“x‰”Å
*/
#pragma once


class IThread
{
	SUPER_CLASS(IThread)
public:

	~IThread() {};

	virtual void Run() = 0;
};