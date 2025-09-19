package com.rtk.btconfig;

import java.io.Serializable;
import java.util.List;

import com.rtk.btconfig.BTConfigThread;
import com.rtk.btconfig.BTScanReceiver;
import com.rtk.btconfig.Cmd4BTConfigThread;
import com.rtk.Configuration.GlobalConfig;

import com.rtk.btconfigbluetooth.ScanResults.ScanObj;
import com.rtk.btconfigbluetooth.BTConfig.BTConfig;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * Handler of UI thread to handle the message/event from other thread
 * **/
@SuppressWarnings("serial")
public class UIMsgHandler extends Handler implements Serializable{
	String TAG = "UIMsgHandler";
	
	public BTConfig hBTConfig;
	
	public final static byte MSG_UPDATE_BTLIST	 			= 0x01;
	public final static byte MSG_CONNECT_BT_OK	 			= 0x02;

	/** repeater not support 2.4G/5G**/
	public final static byte MSG_NO_BAND_SUPPORT	 		= 0x04;
	
	/** show scan 2.4G+5G timeout **/
	public final static byte MSG_SHOW_SCAN_TIMEOUT 			= 0x05;
	
	/** update 2.4G/5G scan results on UI **/
	public final static byte MSG_DISMISS_SCAN_DIALOG		= 0x10;
	public final static byte MSG_UPDATE_WLAN_2G 			= 0x11;
	public final static byte MSG_UPDATE_WLAN_5G 			= 0x12;
	
	/** update Extended AP information on UI **/
	public final static byte MSG_UPDATE_EXTENDED_AP			= 0x15;
	
	/** repeater is offline **/
	public final static byte MSG_NO_RESPONSE	 			= 0x25;

	public final static byte MSG_UPDATE_APLIST  			= 0x70;
	public final static byte MSG_SHOW_HOMEAP_DIALOG   		= (byte) 0x80;
	public final static byte MSG_SHOW_HOME_BUTTON			= (byte) 0x90;
	
	public final static byte MSG_SCAN_DIALOG				= (byte) 0x91;
		
	@Override
	public void handleMessage(Message msg) {
		super.handleMessage(msg);
		switch(msg.what){
		// update Bluetooth Scan list
		case MSG_UPDATE_BTLIST:
			List<ScanObj> btScanList;
			
			if(BTConfig.flag){			
				btScanList = MainActivity.mMainAct.getmBTConfig().getBleScanResults();
			}else{
				btScanList = BTScanReceiver.getBTScanResults();
			}
			
			MainActivity.mMainAct.updateBTScanUI(btScanList);
			break;
		// connect to Bluetooth successfully
		case MSG_CONNECT_BT_OK:
			Log.d(TAG, "MSG_CONNECT_BT_OK");
			MainActivity.mMainAct.mActiveCloseSocket = false;
			
			if(GlobalConfig.CONFIG_SAVE_BT_PROFILE)
				MainActivity.mMainAct.savePreBT();

			MainActivity.mMainAct.hide_home_button();
			MainActivity.show_wifi_list = true;

			MainActivity.mMainAct.BTconnectOK();
			MainActivity.mMainAct.queryWlanBand();
			
			Cmd4BTConfigThread.sendCommonCmd(BTConfigThread.CMD_START_INPUTSTREAM_RECEIVE, MainActivity.mMainAct.mBTConfigHandler);
			
			break;
		// no band support	
		case MSG_NO_BAND_SUPPORT:
			MainActivity.mMainAct.stopWaiting();
			ToastOps.getToast("No Band Support...").show();
			break;
		// scan AP timeout
		case MSG_SHOW_SCAN_TIMEOUT:
			MainActivity.mMainAct.stopWaiting();
			break;
		// dismiss scan dialog
		case MSG_DISMISS_SCAN_DIALOG:
			MainActivity.mMainAct.stopWaiting();
			break;
		//update 2G wlan AP scan list	
		case MSG_UPDATE_WLAN_2G:
			if(!MainActivity.isHomeAP_exist){
				MainActivity.mMainAct.updateWlan2GScanUI();
				MainActivity.mMainAct.show_WiFiList();
			}
			else{
				MainActivity.mMainAct.hide_WiFiList();
			}
			
			break;
		//update 5G wlan AP scan list	
		case MSG_UPDATE_WLAN_5G:
			if(!MainActivity.isHomeAP_exist){
				MainActivity.mMainAct.updateWlan5GScanUI();
				MainActivity.mMainAct.show_WiFiList();
			}
			else{
				MainActivity.mMainAct.hide_WiFiList();
			}
			break;
		// update Extended AP
		case MSG_UPDATE_EXTENDED_AP:
			MainActivity.mMainAct.updateExtendedAPInfoUI();
			break;
		// repeater no response	
		case MSG_NO_RESPONSE:
			Log.w(TAG,"MSG_NO_RESPONSE");
			setExtendAPDisconnect();
			MainActivity.mMainAct.showBTdisconnection();
			break;
	
		case MSG_SHOW_HOME_BUTTON:
			MainActivity.mMainAct.stopWaiting();
			MainActivity.mMainAct.close_dialog();
			MainActivity.mMainAct.resetTargetData();
			MainActivity.mMainAct.show_home_button();
			//re-connect
			MainActivity.mMainAct.mBTConnectState 			= true;
			MainActivity.mMainAct.isHomeAP_check 			= true;
			MainActivity.mMainAct.isHomeAP_exist 			= false;
    		BTConfig.wifi_list_ready					 	= false;
    		
    		MainActivity.mMainAct.getmBTConfig().setBTConfigState(-1);
			break;
			
		case MSG_SHOW_HOMEAP_DIALOG:
			if(MainActivity.isHomeAP_check){
				MainActivity.isHomeAP_check = false;
				MainActivity.isHomeAP_exist = true;
				BTConfig.check_HomeAP 	= 0;
				MainActivity.mMainAct.showHomeAP_Dialog();				
			}			
			break;
					
		case MSG_UPDATE_APLIST:
			MainActivity.mMainAct.GetAllWifiList();
			break;	
			
		case MSG_SCAN_DIALOG:
			MainActivity.mMainAct.startWaiting("Scan WiFi AP", "Waiting...", 30,"Scan Timeout");
			break;
		}		
	}
	
	private void setExtendAPDisconnect(){
		List<ScanObj> extendAPs = MainActivity.mMainAct.mExtendAPScanObjs;
		if(extendAPs.isEmpty()){
			return;
		}else{
			String extendAPSSID = extendAPs.get(0).getSSID();
			byte extendAPEncrypt = extendAPs.get(0).getEncrpytType();
			MainActivity.mMainAct.setAPDisconnectOnUI(extendAPSSID, extendAPEncrypt);
		}
		
	}
}
