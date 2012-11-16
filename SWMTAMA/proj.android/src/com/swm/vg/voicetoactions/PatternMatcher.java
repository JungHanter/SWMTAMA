package com.swm.vg.voicetoactions;

import java.util.ArrayList;
import java.util.Collections;

import android.util.Log;

import com.swm.vg.data.ActionInfo;
import com.swm.vg.data.ActionList;
import com.swm.vg.data.AnimalInfo;


public class PatternMatcher {
	private static class SearchedAnimalInfo implements Comparable<SearchedAnimalInfo> {
		AnimalInfo info;
		String seletedName;
		int maxLen;
		
		public SearchedAnimalInfo(AnimalInfo info, String seletedName, int maxLen) {
			this.info = info;
			this.seletedName = seletedName;
			this.maxLen = maxLen;
		}
		
		@Override
		public int compareTo(SearchedAnimalInfo another) {
			// TODO Auto-generated method stub
//			return (maxLen - another.maxLen);	//오름차순 정렬
			return (another.maxLen - maxLen);	//내림차순 정렬
		}
	}
	
	private static String[][] getSplitedStrings(String str, String rex) {
		String[] spl = str.split(rex);
		int splSize = spl.length - 1;
		
		String[][] splResult = new String[splSize][2];
		int capa = str.length();
		
		StringBuilder before = new StringBuilder(capa);
		StringBuilder after = new StringBuilder(capa);
		for (int i = 0; i < splSize; i++) {
			before.delete(0, capa);
			after.delete(0, capa);
			for (int j = 0; j < splSize + 1; j++) {
				if (j < i) {
					before.append(spl[j]).append(rex);
				} else if (j == i) {
					before.append(spl[j]);
				} else if (j == i + 1) {
					after.append(spl[j]);
				} else {
					after.append(rex).append(spl[j]);
				}
			}
			splResult[i][0] = before.toString();
			splResult[i][1] = after.toString();
		}

//		for (int i=0; i<splResult.length; i++) {
//			Log.d("String split", i + " : " + splResult[i][0] + " / " + splResult[i][1]);
//		}
		return splResult;
	}
	
	//동물/액션 통합 검색, 중의성 추가한 패턴매칭
	public static ActionInfo patternMatch(String sentence, ArrayList<AnimalInfo> arrAnimal) {
		int animalId = -1, actionId = ActionList.ACTION_EXTRA_UNKNOWN;
		String str = MyUtils.convertNoSpace(sentence);
		ArrayList<SearchedAnimalInfo> searchedAnimalList = new ArrayList<SearchedAnimalInfo>();
		
		int maxLen = -1, nowLen = -1;
		String seletedName = null;
		AnimalInfo seletedAnimal = null;
		for(AnimalInfo animal : arrAnimal) {
			//모든 동물을 대상으로
			maxLen = -1; nowLen = -1;
			seletedName = null;
			final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
			for(String name : arrVoiceNames) {
				if(str.contains(name)) {
					//최장매치방식
					nowLen = name.length();
					if(nowLen > maxLen) {
						maxLen = nowLen;
						seletedName = name;
					}
				}
			}
			
			//현재 동물 이름이 검색되었으면
			if(maxLen != -1) {
				searchedAnimalList.add(new SearchedAnimalInfo(animal, seletedName, maxLen));
			}
		}
		
		if(searchedAnimalList.size() > 0) {
			Collections.sort(searchedAnimalList); //내림차순 정렬
			for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) {
				String string = ""+str;
				String[][] splits = getSplitedStrings(str, searchedAnimal.seletedName);
				
			}
		}
		
		//temp
		seletedAnimal = new AnimalInfo(-1);
		if(seletedAnimal != null) {
			animalId = seletedAnimal.getId();
			String[] cuts = str.split(seletedName);
			ArrayList<AnimalInfo.AnimalAction> arrAction = seletedAnimal.getActionList();

			maxLen = 0;
			AnimalInfo.AnimalAction seletedAction = null;
			for(AnimalInfo.AnimalAction action : arrAction) {
				final ArrayList<AnimalInfo.AnimalAction.ActionVoice> arrActionVoice = action.getVoiceList();
				for(AnimalInfo.AnimalAction.ActionVoice actionVoice : arrActionVoice) {
					//동물이름 뺀 부분에서 액션이 있나 매칭시키기
					boolean bContain = false;
					String voice = actionVoice.getVoiceString();
					for(String cut : cuts) {
						if(cut.contains(voice)) {
							bContain = true;
							break;
						}
					}
					
					int maxNum = 0;
					if(bContain) {
						//최장매치
						nowLen = voice.length();
						if(nowLen > maxLen) {
							maxLen = nowLen;
							seletedAction = action;
						} else if (nowLen == maxLen) {
							//최장매치해도 같은 숫자면 다음엔 가르친 number
							int nowNum = seletedAction.getActionCount();
							if(nowNum > maxNum) {
								maxNum = nowNum;
								seletedAction = action;
							} else if (nowNum == maxNum) {
								//가르친 수까지 같으면...?
								if((int)(Math.random())%2 == 0) {
									seletedAction = action;
								}
							}
						}
					}
				}
			}
			
			if(seletedAction != null) {
				actionId = seletedAction.getActionId();
			}
		}
		
		return new ActionInfo(animalId, actionId);
	}
	
	//맨 처음 제작한 패턴매칭
	public static ActionInfo patternMatchOriginal(String sentence, ArrayList<AnimalInfo> arrAnimal) {
		int animalId = -1, actionId = ActionList.ACTION_EXTRA_UNKNOWN;
		String str = MyUtils.convertNoSpace(sentence);
		
		int maxLen = 0;
		String seletedName = null;
		AnimalInfo seletedAnimal = null;
		for(AnimalInfo animal : arrAnimal) {
			final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
			for(String name : arrVoiceNames) {
				if(str.contains(name)) {
					//최장매치방식
					int nowLen = name.length();
					if(nowLen > maxLen) {
						maxLen = nowLen;
						seletedAnimal = animal;
						seletedName = name;
					}
				}
			}
		}
		
		if(seletedAnimal != null) {
			animalId = seletedAnimal.getId();
			String cutStr = "";
			String[] cuts = str.split(seletedName);
			ArrayList<AnimalInfo.AnimalAction> arrAction = seletedAnimal.getActionList();

			maxLen = 0;
			AnimalInfo.AnimalAction seletedAction = null;
			for(AnimalInfo.AnimalAction action : arrAction) {
				final ArrayList<AnimalInfo.AnimalAction.ActionVoice> arrActionVoice = action.getVoiceList();
				for(AnimalInfo.AnimalAction.ActionVoice actionVoice : arrActionVoice) {
					boolean bContain = false;
					String voice = actionVoice.getVoiceString();
					for(String cut : cuts) {
						if(cut.contains(voice)) {
							bContain = true;
							break;
						}
					}
					
					if(bContain) {
						int nowLen = voice.length();
						if(nowLen > maxLen) {
							maxLen = nowLen;
							seletedAction = action;
						}
					}
				}
			}
			
			if(seletedAction != null) {
				actionId = seletedAction.getActionId();
			}
		}
		
		return new ActionInfo(animalId, actionId);
	}
	
}
