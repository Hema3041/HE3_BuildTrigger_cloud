package com.rtk.btconfigbluetooth.BTConfig;

import com.rtk.btconfigbluetooth.BTRfComm.BTRfComm;
import com.rtk.btconfigbluetooth.BTBle.BTBle;

import android.util.Log;

/**	The thread for receiving data from repeater and parsing the data **/
public class BTReceiveThread extends Thread{
	private String TAG = "BTReceiveThread";
	private boolean mIsPause = false;

	/** awake the thread **/
	public synchronized void awake(){
		this.notify();
	}
	
	/** make the thread wait **/
	public void onThreadWait(){		
		try {  
            synchronized (this) {  
                this.wait();  
            }  
        } catch (Exception e) {  
            e.printStackTrace();  
        }  
	}

	/**  receive message from repeater **/
	@Override
	public void run() {
		while(!mIsPause && !isInterrupted()){

			
			byte[] temp = new byte[10*1024];

			int len = BTConfig.mBTConfig.getBTRfComm().getBTResponse(temp);
		
			if(len == BTRfComm.STATE_BT_STREAM_FAIL){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_REPEATER_OFFLINE);
			
				onThreadWait();
			}else{
				byte[] temp_buf = new byte[len];
				System.arraycopy(temp, 0, temp_buf, 0, len);
			
				// parse the data received from repeater
				parseReceiveData(temp_buf, BTConfig.mBTConfig.getBTConfigState()); 
		
			}

		}
	}

	/** parse the data received from wifi's client **/
	private void parseReceiveData(byte[] buf,  int btConfigState){

		if(btConfigState == BTConfigState.STATE_BT_QUERY_WLAN_BAND){
	
			int ret = BTConfig.BTConfigLib.parse_wlan_band_reply(buf, buf.length);
			if(ret == 1){				
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_QUERY_WLAN_BAND_END);								
			}
			
		}
		else if(btConfigState == BTConfigState.STATE_BT_SCAN_WLAN_2G){
			
			int ret = BTConfig.BTConfigLib.parse_AP_results_2G_reply(buf, buf.length);
			if(ret == 1){
				BTConfig.wifi_list_ready = true;
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_SCAN_WLAN_2G_END);
			}else if(ret == 0){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_RECEIVE_WLAN_2G);
			}	
			
		}else if(btConfigState == BTConfigState.STATE_BT_RECEIVE_WLAN_2G){
						
			int ret = BTConfig.BTConfigLib.parse_AP_results_2G_reply(buf, buf.length);
			if(ret == 1){
				BTConfig.wifi_list_ready = true;
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_SCAN_WLAN_2G_END);
			}else if(ret == 0){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_RECEIVE_WLAN_2G);
			}

		}
		else if(btConfigState == BTConfigState.STATE_BT_SCAN_WLAN_5G){

			int ret = BTConfig.BTConfigLib.parse_AP_results_5G_reply(buf, buf.length);
			if(ret == 1){
				BTConfig.wifi_list_ready = true;
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_SCAN_WLAN_5G_END);
			}else if(ret == 0){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_RECEIVE_WLAN_5G);
			}				
		
		}
		else if(btConfigState == BTConfigState.STATE_BT_RECEIVE_WLAN_5G){

			int ret = BTConfig.BTConfigLib.parse_AP_results_5G_reply(buf, buf.length);
			if(ret == 1){
				BTConfig.wifi_list_ready = true;
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_SCAN_WLAN_5G_END);
			}else if(ret == 0){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_RECEIVE_WLAN_5G);
			}									
		
		}
		else if(btConfigState == BTConfigState.STATE_BT_SEND_WLAN_PROFILE){
			int ret = BTConfig.BTConfigLib.parse_AP_profile_ACK_reply(buf, buf.length);
			if(ret == 1){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_SEND_WLAN_PROFILE_END);
			}
			
		}
		else if(btConfigState == BTConfigState.STATE_BT_QUERY_REPEATER_STATUS){
			int ret = BTConfig.BTConfigLib.parse_repeater_status_reply(buf, buf.length);
			if(ret == 1){
				BTConfig.mBTConfig.setBTConfigState(BTConfigState.STATE_BT_QUERY_REPEATER_STATUS_END);

			}
		}
		else if(btConfigState == -1 || btConfigState == BTConfigState.STATE_BT_DISCONNECT){

		}
		else{
			return;
		}
			
	 }//parseReceiveData
	
}//BTReceiveThread
