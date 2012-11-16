package com.swm.vg.voicetoactions;

import java.util.ArrayList;
import java.util.Collections;

import com.swm.vg.data.ActionInfo;
import com.swm.vg.data.ActionList;
import com.swm.vg.data.AnimalInfo;


public class PatternMatcher2 {
	private static class SearchedAnimalInfo implements Comparable<SearchedAnimalInfo> {
		AnimalInfo info;
		String selectedName;
		
		SearchedAnimalInfo(AnimalInfo info, String seletedName) {
			this.info = info;
			this.selectedName = seletedName;
		}
		
		@Override
		public int compareTo(SearchedAnimalInfo another) {
			//내림차순으로
			int dif = (another.selectedName.length() - selectedName.length()) * 10000;
			if (dif == 0) {
				int cnt = another.info.getNamesCount() - info.getNamesCount();
				if(cnt > 9999) cnt = 9999;
				else if(cnt < -9999) cnt = -9999;
				dif += (cnt);
			}
			return dif;
		}
	}
	
	private static class SearchedActionInfo {
		int animalId;
		AnimalInfo.AnimalAction action;
		String selectedActionVoice;
		
		SearchedActionInfo(int animalId, AnimalInfo.AnimalAction action,
				String selectedActionVoice) {
			this.animalId = animalId;
			this.action = action;
			this.selectedActionVoice = selectedActionVoice;
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
		
		String seletedName = null;
		AnimalInfo selectedAnimal = null;
		AnimalInfo.AnimalAction selectedAction = null;
		
		for(AnimalInfo animal : arrAnimal) {
			//모든 동물을 대상으로
			seletedName = null;
			final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
			for(String name : arrVoiceNames) {
				if(str.contains(name)) {
					searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
				}
			}
		}
		
		//동물이 하나라도 검색됬으면
		if(searchedAnimalList.size() > 0) {
//			ArrayList<SearchedActionInfo> searchedActionInfo = new ArrayList<SearchedActionInfo>();
			SearchedActionInfo searchedActionInfo;
			int maxLen = -1;
			Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
			for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) {
				//서치된 동물을 기준으로 액션이 있는지 찾아본다
				String string = ""+str;
				selectedAction = null;
				
				String[][] splits = getSplitedStrings(string, searchedAnimal.selectedName);
				for(String[] splString : splits) {
					ArrayList<AnimalInfo.AnimalAction> arrAction = searchedAnimal.info.getActionList();
					//각 스플리트스트링(각 동물 기준)마다 액션 하나씩 검사
					for(AnimalInfo.AnimalAction action : arrAction) {
						final ArrayList<AnimalInfo.AnimalAction.ActionVoice> arrActionVoice = action.getVoiceList();
						//가장 긴 보이스 매치
						for(AnimalInfo.AnimalAction.ActionVoice actionVoice : arrActionVoice) {
							boolean bContain = false;
							String voice = actionVoice.getVoiceString();
							for(String eachString : splString) {
								if(eachString.contains(voice)) {
									bContain = true;
									String 이름 = "신재";
									break;
								}
							}
							
							if(bContain) {
								int nowLen = voice.length();
								if(nowLen > maxLen) {
									maxLen = nowLen;
									selectedAction = action;
								} else if (nowLen == maxLen) {
									if(action.getActionCount() > selectedAction.getActionCount())
										selectedAction = action;
								}
							}
						}
					}
				}
				
				if(selectedAction != null) {
					animalId = searchedAnimal.info.getId();
					actionId = selectedAction.getActionId();
					break;
					//selectedAction이 있으면 애니멀-액션 최장매치 된거임.
					//없으면 다음 최장매치된 애니멀부터 액션을 매치시켜 찾아낸다.
				}
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
