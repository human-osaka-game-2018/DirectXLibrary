#ifndef XINPUT_DEVICE_H
#define XINPUT_DEVICE_H
/// <summary>
/// XinputDevice関連処理
/// </summary>
/**
* @author Toshiya Matsuoka
*/
#include <Windows.h>
#include<Xinput.h>
/// <summary>
/// Xinputでの列挙
/// </summary>
namespace Xinput {
	/// <summary>
	/// コントローラ番号
	/// </summary>
	enum PLAYER_NUM
	{
		PLAYER_01,
		PLAYER_02,
		PLAYER_03,
		PLAYER_04,
	};

	/// <summary>
	/// ボタンの押下状態
	/// </summary>
	enum PADSTATE
	{
		//! 押されていない
		PadOff,
		//! 押されている
		PadOn,
		//! 押された
		PadPush,
		//! 離された
		PadRelease
	};
	/// <summary>
	/// パッドのボタン番号
	/// </summary>
	enum ButtonIndex
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		//! R1ボタン
		ButtonRB,
		//! L1ボタン
		ButtonLB,
		ButtonStart,
		ButtonBack,
		ButtonUP,
		ButtonDOWN,
		ButtonLEFT,
		ButtonRIGHT,
		//!L3ボタン
		ButtonLeftThumb,
		//!R3ボタン
		ButtonRightThumb,
		ButtomIndexMAX
	};

	/// <summary>
	/// アナログスティックの傾き方向
	/// </summary>
	enum Analog
	{
		ANALOGUP,
		ANALOGDOWN,
		ANALOGLEFT,
		ANALOGRIGHT,
		ANALOGMAX
	};
	/// <summary>
	/// アナログスティックの傾き軸
	/// </summary>
	enum AnalogAxis
	{
		ANALOG_X,
		ANALOG_Y,
	};
	/// <summary>
	/// 左右のトリガー識別
	/// </summary>
	enum AnalogTrigger
	{
		LEFT_TRIGGER,
		RIGHT_TRIGGER
	};
};
/// <summary>
/// XinputPADの動作
/// </summary>
class XinputDevice {
	
public:
	
	explicit XinputDevice(Xinput::PLAYER_NUM number);

	~XinputDevice() {};

	/// <summary>
	/// 接続状態の取得
	/// </summary>
	DWORD GetInfo() const{
		return XINPUT_INFO;
	}

	/// <summary>
	/// GetControlとBottonCheckを纏めて行う
	/// </summary>
	/// <seealso cref="GetControl"/>
	/// <seealso cref="BottonCheck"/>
	void DeviceUpdate();

	/// <summary>
	/// XinputDeviceでゲームパッドのトリガーの入力取得
	/// </summary>
	/// <param name="Trigger">トリガーの左右認識番号</param>
	/// <returns>0～255の値、押してなければ0</returns>
	/// <seealso cref="Xinput::AnalogTrigger"/>
	int GetAnalogTrigger(Xinput::AnalogTrigger Trigger)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetAnalogL(Xinput::Analog AnalogState)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetAnalogR(Xinput::Analog AnalogState)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetAnalogLValue(Xinput::AnalogAxis AnalogState)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetAnalogRValue(Xinput::AnalogAxis AnalogState)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetAnalogLState(Xinput::Analog AnalogState)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetAnalogRState(Xinput::Analog AnalogState)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerRState()const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerLState()const;

	/// <summary>
	/// 左右のバイブレーションモーターを動作させる
	/// </summary>
	/// <param name="LeftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <param name="RightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
	void RunVibration(unsigned int LeftValue = 0, unsigned int RightValue = 0);

private:
	const Xinput::PLAYER_NUM ControlerNum;
	XINPUT_STATE m_Xinput = { NULL };

	Xinput::PADSTATE m_PadState[Xinput::ButtomIndexMAX] = { Xinput::PadOff };
	Xinput::PADSTATE m_PadOldState[Xinput::ButtomIndexMAX] = { Xinput::PadOff };

	Xinput::PADSTATE m_AnalogROldState[Xinput::ANALOGMAX] = { Xinput::PadOff };
	Xinput::PADSTATE m_AnalogRState[Xinput::ANALOGMAX] = { Xinput::PadOff };

	Xinput::PADSTATE m_AnalogLOldState[Xinput::ANALOGMAX] = { Xinput::PadOff };
	Xinput::PADSTATE m_AnalogLState[Xinput::ANALOGMAX] = { Xinput::PadOff };
	
	Xinput::PADSTATE m_TriggerROldState = Xinput::PadOff;
	Xinput::PADSTATE m_TriggerRState = Xinput::PadOff;

	Xinput::PADSTATE m_TriggerLOldState = Xinput::PadOff;
	Xinput::PADSTATE m_TriggerLState = Xinput::PadOff;

	//! デバイスの状態確認用
	DWORD XINPUT_INFO = -1;
	
	const int INCLINATION_THRESHOLD_VALUE = 65535 / 4;
	
	/// <summary>
	/// XinputDeviceでゲームパッドデバイスの取得
	/// </summary>
	void GetControl();

	/// <summary>
	/// XinputDeviceでゲームパッドの入力取得
	/// </summary>
	/// <param name="index">取得したいボタンの配列番号</param>
	/// <returns>PADSTATEの値</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetButton(Xinput::ButtonIndex index)const;

	/// <summary>
	/// 全てのボタンに対してCheckButtonStateを行う
	/// </summary>
	/// <seealso cref="CheckButtonState"/>
	void BottonCheck();

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態振り分け
	/// </summary>
	/// <param name="AnalogState">入力状態の欲しい方向</param>
	/// <seealso cref="Xinput::Analog"/>
	void AnalogLStateDivide(Xinput::Analog AnalogState);

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力状態振り分け
	/// </summary>
	/// <param name="AnalogState">入力状態の欲しい方向</param>
	/// <seealso cref="Xinput::Analog"/>
	void AnalogRStateDivide(Xinput::Analog AnalogState);

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態振り分け
	/// </summary>
	void TriggerRStateDivide();

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態振り分け
	/// </summary>
	void TriggerLStateDivide();

	/// <summary>
	/// Dinputでキーボードの状態取得
	/// </summary>
	/// <param name="ButtomID">取得したいXInputボタン番号</param>
	/// <param name="ButtomIndex">取得したいボタンの配列番号</param>
	/// <seealso cref="Xinput::ButtonIndex"/>
	void CheckButtonState(WORD ButtomID, Xinput::ButtonIndex ButtomIndex);


};
#endif
