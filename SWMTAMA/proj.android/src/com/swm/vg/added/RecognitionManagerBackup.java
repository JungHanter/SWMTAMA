package com.swm.vg.added;

import java.util.ArrayList;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;
import android.speech.SpeechRecognizer;
import android.util.Log;
import android.widget.Toast;

import com.swm.vg.voicetoactions.VoiceRecognizer;
import com.swm.vg.voicetoactions.VoiceRecognizerListener;

public class RecognitionManagerBackup {
	private VoiceRecognizerListener mRecogListener;
	private VoiceRecognizerListener mRecogTeachListener;
	private VoiceRecognizer mRecognizer;
	private Activity parent;
	
	public static final int NATIVECALL_RECOG_START = 100;
	public static final int NATIVECALL_RECOG_STOP = 101;
	public static final int NATIVECALL_TEACH_START = 102;
	public static final int NATIVECALL_TEACH_STOP = 103;
	public static final int NATIVECALL_TEACH_SPEECHING = 104;
	public static final int NATIVECALL_TEACH_NAME = 105;
	public static final int NATIVECALL_TEACH_CONFIRM = 106;
	
	private Handler manageHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch(msg.what) {
			case NATIVECALL_RECOG_START:
				mRecognizer = VoiceRecognizer.createVoiceRecognizer(parent, true);
				mRecognizer.setVoiceRecognizerListener(mRecogListener);
				mRecognizer.start();
				break;
			case NATIVECALL_RECOG_STOP:
			case NATIVECALL_TEACH_STOP:
				mRecognizer.closeVoiceRecognizer();
				mRecognizer = null;
				break;
			case NATIVECALL_TEACH_START:
				mRecognizer = VoiceRecognizer.createVoiceRecognizer(parent, false);
				mRecognizer.setVoiceRecognizerListener(mRecogTeachListener);
				break;
			case NATIVECALL_TEACH_SPEECHING:
				mRecognizer.start();
				break;
			case NATIVECALL_TEACH_NAME:
				mRecognizer.start();
				break;
			case NATIVECALL_TEACH_CONFIRM:
				boolean isSave = ((Boolean)msg.obj).booleanValue();
				break;
			}
		}
	};
	
	public static final int CALLBACK_RECOG_RESULT = 200;
	public static final int CALLBACK_RECOG_READY = 201;
	public static final int CALLBACK_RECOG_IDLE = 202;
	public static final int CALLBACK_RECOG_VOLUME = 203;
	public static final int CALLBACK_RECOG_ERROR = 204;
	public static final int CALLBACK_TEACH_READY = 205;
	public static final int CALLBACK_TEACH_RESULT = 206;
	public static final int CALLBACK_TEACH_VOLUME = 207;
	public static final int CALLBACK_TEST_TEXT = 208;
	
	private Handler callbackHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch(msg.what) {
			case CALLBACK_RECOG_RESULT:
				callbackOnVoiceRecognitionResult(msg.arg1, msg.arg2, -1);
//				callbackOnVoiceRecognitionResult(msg.arg1, msg.arg2, ((Integer)msg.obj).intValue());
				break;
			case CALLBACK_RECOG_READY:
				callbackOnRecognitionReady();
				break;
			case CALLBACK_RECOG_IDLE:
				callbackOnRecognitionIdle();
				break;
			case CALLBACK_RECOG_ERROR:
				callbackOnRecognitionError(msg.arg1);
				break;
			case CALLBACK_TEACH_READY:
				callbackOnTeachingReady();
				break;
			case CALLBACK_TEACH_RESULT:
				callbackOnTeachingResult(msg.arg1);
				break;
			case CALLBACK_RECOG_VOLUME:
				callbackOnRecognitionVolumeChanged(msg.arg1);
				break;
			case CALLBACK_TEACH_VOLUME:
				callbackOnTeachingVolumeChanged(msg.arg1);
				break;
			case CALLBACK_TEST_TEXT:
				callbackSetLabel((String)msg.obj);
				break;
			}
		}
	};
	
	
	//cpp -> java call methods
	public void startVoiceRecognition() {
		Log.d("native->java", "startVoiceRecognition");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_RECOG_START, -1, -1));
	}
	
	public void stopVoiceRecognition() {
		Log.d("native->java", "stopVoiceRecognition");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_RECOG_STOP, -1, -1));
	}
	
	public void startTeachRecogntion() {
		Log.d("native->java", "startTeachRecogntion");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_TEACH_START, -1, -1));
	}
	
	public void stopTeachRecogntion() {
		Log.d("native->java", "stopTeachRecogntion");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_TEACH_STOP, -1, -1));
	}
	
	public void teachSpeeching(int who, int action) {
		Log.d("native->java", "teachSpeeching");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_TEACH_SPEECHING, who, action));
	}
	
	public void teachNameSpeeching(int who) {
		Log.d("native->java", "teachNameSpeeching");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_TEACH_NAME, who, -1));
	}
	
	public void teachConfirm(boolean isSave) {
		Log.d("native->java", "teachConfirm");
		manageHandler.sendMessage(Message.obtain(manageHandler, NATIVECALL_TEACH_CONFIRM, -1, -1,
			Boolean.valueOf(isSave)));
	}
	
	
	//java -> cpp call functions
	private native void callbackOnVoiceRecognitionResult(int who, int action, int extra);
	private native void callbackOnRecognitionReady();
	private native void callbackOnRecognitionIdle();
	private native void callbackOnRecognitionVolumeChanged(int step);
	private native void callbackOnRecognitionError(int error);
	private native void callbackOnTeachingReady();
	private native void callbackOnTeachingResult(int resultCode);
	private native void callbackOnTeachingVolumeChanged(int step);
	
	private native void callbackSetLabel(String str);
	
	//method
	public void resumeRecognitionManager() {
		if (mRecognizer != null)
			mRecognizer.resume();
	}

	public void pauseRecognitionManager() {
		if (mRecognizer != null)
			mRecognizer.pause();
	}

	public void destoryRecognitionManager() {
		mRecognizer.closeVoiceRecognizer();
		mRecogListener = null;
		mRecogTeachListener = null;
		mRecognizer = null;
		sharedInstance = null;
	}
	
	private void makeListener() {
		mRecogListener = new VoiceRecognizerListener() {
			@Override
			public void onResults(ArrayList<String> results) {
				if (results.size() <= 0) {
					Log.d("VoiceRecognitionListener", "onResults - no result");
//					callbackSetLabel("No result");
//					callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_RESULT, 0, 0,
//							Integer.valueOf(0)));
					callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_TEST_TEXT, (Object)results.get(0)));
				} else {
					Log.d("VoiceRecognitionListener", "onResults - " + results.get(0));
					callbackSetLabel(results.get(0));
				}
			}

			@Override
			public void onVolumeChanged(int step) {
//				Log.d("VoiceRecognitionListener", "onVolumeChanged");
//				callbackOnRecognitionVolumeChanged(step);
//				callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_VOLUME, step, -1));
			}

			@Override
			public void onStartRecognition() {
				Log.d("VoiceRecognitionListener", "onStartRecognition");
			}

			@Override
			public void onTimeoutRecognition() {
				Log.d("VoiceRecognitionListener", "onTimeoutRecognition");
//				callbackOnRecognitionIdle();
				callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_IDLE));
			}

			@Override
			public void onBeginningOfSppech() {
				Log.d("VoiceRecognitionListener", "onBeginningOfSppech");
			}

			@Override
			public void onReady() {
				Log.d("VoiceRecognitionListener", "onReady");
//				callbackOnRecognitionReady();
				callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_READY));
			}

			@Override
			public void onEndOfSpeech() {
				Log.d("VoiceRecognitionListener", "onEndOfSpeech");
//				callbackOnRecognitionIdle();
				callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_IDLE));
			}

			@Override
			public void onFinishRecognition() {
				Log.d("VoiceRecognitionListener", "onFinishRecognition");
			}

			@Override
			public void onCancelRecognition() {
				Log.d("VoiceRecognitionListener", "onCancelRecognition");
//				callbackOnRecognitionIdle();
				callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_IDLE));
			}

			@Override
			public void onClosing() {
				Log.d("VoiceRecognitionListener", "onClosing");
			}

			@Override
			public void onError(int error) {
				String msg = null;

				switch (error) {
				case SpeechRecognizer.ERROR_AUDIO:
					msg = "오디오 입력 중 오류가 발생했습니다.";
					break;
				case SpeechRecognizer.ERROR_CLIENT:
					msg = "단말에서 오류가 발생했습니다.";
					break;
				case SpeechRecognizer.ERROR_INSUFFICIENT_PERMISSIONS:
					msg = "권한이 없습니다.";
					break;
				case SpeechRecognizer.ERROR_NETWORK:
				case SpeechRecognizer.ERROR_NETWORK_TIMEOUT:
					msg = "네트워크 오류가 발생했습니다.";
					break;
				case SpeechRecognizer.ERROR_NO_MATCH:
					msg = "일치하는 항목이 없습니다.";
					break;
				case SpeechRecognizer.ERROR_RECOGNIZER_BUSY:
					msg = "음성인식 서비스가 과부하 되었습니다.";
					break;
				case SpeechRecognizer.ERROR_SERVER:
					msg = "서버에서 오류가 발생했습니다.";
					break;
				case SpeechRecognizer.ERROR_SPEECH_TIMEOUT:
					msg = "입력이 없습니다.";
					break;
				default:
					msg = "알 수 없는 에러가 발생했습니다.";
					break;
				}
				
//				callbackOnRecognitionIdle();
				callbackHandler.sendMessage(Message.obtain(callbackHandler, CALLBACK_RECOG_IDLE));
				Toast.makeText(parent, msg, Toast.LENGTH_SHORT).show();
			}
		};
	}
	
	//must first init call
	public void setListener(VoiceRecognizerListener listener) {
		mRecogListener = listener;
	}
	
	//must first init call
	public void setTeachListener(VoiceRecognizerListener teachListener) {
		mRecogTeachListener = teachListener;
	}
	
	private RecognitionManagerBackup(Activity parent) {
		this.parent = parent;
		makeListener();
	}
	
	private static RecognitionManagerBackup sharedInstance = null;
	public static RecognitionManagerBackup sharedRecognitionManager(Activity parentActivity) {
		if(sharedInstance == null) {
			sharedInstance = new RecognitionManagerBackup(parentActivity);
		} else {
			sharedInstance.parent = parentActivity;
		}
		return sharedInstance;
	}
	
	public static Object getNowManager() {
		return (Object)sharedInstance;
	}
}
