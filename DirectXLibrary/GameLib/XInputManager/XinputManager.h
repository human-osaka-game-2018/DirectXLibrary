#ifndef XINPUT_MANAGER_H
#define XINPUT_MANAGER_H
/// <summary>
/// XinputManager関連処理
/// </summary>
/**
* @author Toshiya Matsuoka
*/

#include "Xinput/XinputDevice.h"

/// <summary>
/// XinputPADの管理
/// </summary>
class XinputManager
{
public:
	XinputManager();

	~XinputManager();

	/// <summary>
	/// PADの接続、入力状態の確認
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
	int GetAnalogTrigger(Xinput::AnalogTrigger Trigger, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetAnalogL(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetAnalogR(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetAnalogLValue(Xinput::AnalogAxis AnalogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetAnalogRValue(Xinput::AnalogAxis AnalogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetAnalogLState(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetAnalogRState(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerRState(Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerLState(Xinput::PLAYER_NUM num);

	/// <summary>
	/// 左右のバイブレーションモーターを動作させる
	/// </summary>
	/// <param name="LeftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <param name="RightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
	void RunVibration(Xinput::PLAYER_NUM num,unsigned int LeftValue = 0, unsigned int RightValue = 0);

private:
	static const int PLAYER_MAX = 4;
	XinputDevice* m_pXinputDevice[PLAYER_MAX];
};

#endif
