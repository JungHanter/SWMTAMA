/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.swm.vg;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.swm.vg.voicetoactions.VoiceRecognizer;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.PowerManager;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.Toast;

public class SWMTama extends Cocos2dxActivity{
	static private PowerManager.WakeLock mWakeLock;
	private static SWMTama nowActivity = null;
	private RecognitionManager mRecogManager = null;

	protected void onCreate(Bundle savedInstanceState){
		PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
		mWakeLock = pm.newWakeLock(PowerManager.FULL_WAKE_LOCK, "SWMTama");

		if (VoiceRecognizer.isSupport(this)) {
			mRecogManager = RecognitionManager.sharedRecognitionManager(this);
		} else {
			Log.d("activity", "don't support recognition");
			Toast.makeText(this, "don't support recognition",
					Toast.LENGTH_SHORT).show();
			finish();
		}
				
		super.onCreate(savedInstanceState);
		
		nowActivity = this;
	}
	
    static {
         System.loadLibrary("game");
    }
    
	@Override
	protected void onPause() {
		super.onPause();
		mRecogManager.pauseRecognitionManager();
	}

	@Override
	protected void onResume() {
		super.onResume();
		if(!mWakeLock.isHeld()) mWakeLock.acquire();
		mRecogManager.resumeRecognitionManager();
	}
	
	@Override
	protected void onDestroy() {
		mRecogManager.destoryRecognitionManager();
		mWakeLock.release();
		super.onDestroy();
	}
	
	/*
	@Override
	public void onBackPressed() {
		exitConfirm();
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		switch(keyCode) {
		case KeyEvent.KEYCODE_BACK:
			exitConfirm();
			return true;
		default:
			return super.onKeyDown(keyCode, event);
		}
	}
	
	private void exitConfirm() {
		new AlertDialog.Builder(this).setTitle("종료")
		.setMessage("정말 종료하시겠습니까?")
		.setPositiveButton("확인", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				finish();
			}
		}).setNeutralButton("취소", null).show();
	}*/
}
