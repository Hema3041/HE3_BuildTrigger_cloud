package com.rtk.btconfig;

public class UIState {
	/* enable BT and scan BT */
	public static final int STATE_UI_TURN_ON_BT							=	0x01;
	public static final int STATE_UI_SCAN_BT							=	0x02;

	/* scan WiFi AP */
	public static final int STATE_UI_SHOW_SCAN_WLAN						=	0x20;
	public static final int STATE_UI_CANCEL_SCAN_WLAN					=	0x21;
	public static final int STATE_UI_DISMISS_SCAN_WLAN					=	0x22;
	
	/* choose remote AP for connected */
	public static final int STATE_UI_SHOW_CHOICE_FOR_AP					=	0x30;
	public static final int STATE_UI_CANCEL_CHOICE_FOR_AP				=	0x31;
	
	/* connecting to remote AP */
	public static final int STATE_UI_SHOW_CONNECTING_AP					=	0x35;
	public static final int STATE_UI_CANCEL_CONNECTING_AP				=	0x36;
	
	/* remote AP replies wrong password */
	public static final int STATE_UI_SHOW_WRONG_PASSWORD			    =	0x40;
	public static final int STATE_UI_CANCEL_WRONG_PASSWORD			    =	0x41;
	
	public static final int STATE_UI_CONNECT_AP_OK			    		=	0x42;
	
	/* adjust the repeater position */
	public static final int STATE_UI_SHOW_CHOICE_FOR_ADJUSTMENT			=	0x50;
	public static final int STATE_UI_DISMISS_CHOICE_FOR_ADJUSTMENT		=	0x51;
	
}
