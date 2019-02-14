﻿/************************************************
MIT License
Copyright(c) 2017 CTCaer
Released under the MIT license
http://opensource.org/licenses/mit-license.php
************************************************/

#ifndef JOYCON_H_
#define JOYCON_H_
#include <cstdint>
#include <string>
#include <thread>
#include <d3dx9.h>

#include "hid/hidapi.h"

#pragma comment(lib, "SetupAPI")

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

class Joycon
{
public:
	enum CONTROLLER_TYPE
	{
		LEFT_CONTROLLER,
		RIGHT_CONTROLLER,
		MAX_CONTROLLER
	};

	enum RIGHT_BUTTON
	{
		Y_BUTTON = 1,
		X_BUTTON = 2,
		B_BUTTON = 4,
		A_BUTTON = 8,
		R_BUTTON = 64,
		ZR_BUTTON = 128,
	};

	enum LEFT_BUTTON
	{
		DOWN_BUTTON = 1,
		UP_BUTTON = 2,
		RIGHT_BUTTON = 4,
		LEFT_BUTTON = 8,
		L_BUTTON = 64,
		ZL_BUTTON = 128,
	};

	enum OTHER_BUTTON
	{
		SR_BUTTON = 16,
		SL_BUTTON = 32,
		HOME_BUTTON = ZR_BUTTON + 1, //right 16 left 32
		MINUS_PLUS_BUTTON, //minus 1 plus 2
		MAX_BUTTON
	};

	enum BUTTON_STATE
	{
		PUSH_BUTTON,
		RELEASE_BUTTON,
		HOLD_BUTTON,
		NEUTRAL_BUTTON
	};

	enum JOYCON_DIRECTION
	{
		UP_DIRECTION,
		DOWN_DIRECTION,
		LEFT_DIRECTION,
		RIGHT_DIRECTION,
		MAX_DIRECTION
	};

	enum ANALOG_STICK_STATE
	{
		PUSH_ANALOG_STICK,
		HOLD_ANALOG_STICK,
		RELEASE_ANALOG_STICK,
		NEUTRAL_ANALOG_STICK,
	};

	enum GYRO_SENSOR_STATE
	{
		INPUT_GYRO_SENSOR,
		MOVE_GYRO_SENSOR,
		STOP_GYRO_SENSOR,
		NEUTRAL_GYRO_SENSOR
	};

	Joycon();
	~Joycon();

	/**
	* @brief 接続する
	* @param[in] _controllerType 接続するコントローラ
	* @return 成功すればtrue 失敗すればfalse
	*/
	bool Connect(CONTROLLER_TYPE _controllerType);

	/**
	* @brief 接続を終了する 
	*/
	void Disconnect()
	{
		if (m_IsConnect)
		{
			m_IsConnect = false;
			m_Thread.join();
			hid_close(m_Handle[m_ControllerType]);
		}
	}

	/**
	* @brief ボタンの状態を更新する
	* @param[in] _button 更新するボタン
	*/
	void CheckButton(int _button);

	/**
	* @brief アナログステックの状態を更新する
	*/
	void CheckAnalogStick();

	/**
	* @brief ジャイロの状態を更新する
	*/
	void CheckGyroSensor();

	/**
	* @brief アナログスティックの値を取得する
	* @return アナログスティックの値
	*/
	D3DXVECTOR2 GetAnalogStick() const
	{
		return m_AnalogStick;
	}

	/**
	* @brief 角速度を取得する
	* @return 角速度
	*/
	D3DXVECTOR3 GetGyroSensor()const
	{
		return m_GyroSensor;
	}

	/**
	* @brief 加速度を取得する
	* @return 加速度
	*/
	D3DXVECTOR3 GetAccelerometer()const
	{
		return m_Accelerometer;
	}

	/**
	* @brief ボタンの状態を取得する
	* @param[in] _button 取得するボタン
	* @return ボタンの状態
	*/
	const BUTTON_STATE* GetButtonState() const
	{
		return m_ButtonState;
	}

	/**
	* @brief アナログステックの状態を取得する
	* @return アナログステックの状態 
	*/
	const ANALOG_STICK_STATE* GetAnalogStickState() const
	{
		return m_AnalogStickState;
	}

	/**
	* @brief ジャイロの状態を取得する
	* @return ジャイロの状態
	*/
	const GYRO_SENSOR_STATE* GetGyroSensorState() const
	{
		return m_GyroSensorState;
	}
	
	/**
	* @breif Joyconが繋がっているかを判断する
	* @return 繋がっているのか
	*/
	bool GetIsConnect() const
	{
		return m_IsConnect;
	}

	/**
	*@brief 振動させる
	*/
	void SendRumble();

private:
	void Update();

	bool InputDirectionAnalogStick(int Direction);

	bool InputDirectionGyroSensor(int Direction);

	hid_device*			m_Handle[MAX_CONTROLLER];
	CONTROLLER_TYPE		m_ControllerType;
	std::thread			m_Thread;
	BUTTON_STATE		m_ButtonState[MAX_BUTTON];
	BUTTON_STATE		m_OldButtonState[MAX_BUTTON];
	ANALOG_STICK_STATE  m_AnalogStickState[MAX_DIRECTION];
	GYRO_SENSOR_STATE	m_GyroSensorState[MAX_DIRECTION];
	D3DXVECTOR2			m_AnalogStick;
	D3DXVECTOR3			m_GyroSensor; //!< 回転速度センサー(m/s)
	D3DXVECTOR3			m_Accelerometer; //!< 加速度センサー(rad/s)
	bool				m_IsConnect;
	bool				m_IsFirstFrame;

	// サンプルコードより.

	int get_spi_data(u32 offset, const u16 read_len, u8 *test_buf);

	u8 timming_byte = 0x0;

	int res;
	int limit_output = 0;
	u8 buf_cmd[36];
	u8 buf_reply[0x170];
	float acc_cal_coeff[3];
	float gyro_cal_coeff[3];
	float cal_x[1];
	float cal_y[1];

	bool has_user_cal_stick_l = false;
	bool has_user_cal_stick_r = false;
	bool has_user_cal_sensor = false;

	unsigned char factory_stick_cal[0x12];
	unsigned char user_stick_cal[0x16];
	unsigned char sensor_model[0x6];
	unsigned char stick_model[0x24];
	unsigned char factory_sensor_cal[0x18];
	unsigned char user_sensor_cal[0x1A];
	u16 factory_sensor_cal_calm[0xC];
	u16 user_sensor_cal_calm[0xC];
	s16 sensor_cal[0x2][0x3];
	u16 stick_cal_x_l[0x3];
	u16 stick_cal_y_l[0x3];
	u16 stick_cal_x_r[0x3];
	u16 stick_cal_y_r[0x3];

};

#endif
