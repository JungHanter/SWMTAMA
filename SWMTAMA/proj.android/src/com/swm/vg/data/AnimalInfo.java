package com.swm.vg.data;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

import com.swm.vg.voicetoactions.MyUtils;

public class AnimalInfo implements Comparable<AnimalInfo> {
	private final int id;
	private final String name;
	private final ArrayList<String> arrVoiceNames;
	private int namesCount;
	private final ArrayList<AnimalAction> arrAnimalActions;

	private static final int NUM_MAX_VOICENAME = 3;
	private static final int NUM_MAX_VOICEACTION = 3;
	
	public int getNamesCount() { return namesCount; }
	public String getName() { return name; }
	public int getId() { return id; }
	public ArrayList<String> getVoiceNames() { return arrVoiceNames; }
	public ArrayList<AnimalAction> getActionList() { return arrAnimalActions; }
	
	public void addVoiceNames(ArrayList<String> names) {
		namesCount++;
		int size = names.size();
		if(size > NUM_MAX_VOICENAME) size = NUM_MAX_VOICENAME;
		
		//리스트에 추가 하고
		String plusVoice = null;
		for(int i=0; i<size; i++) {
			String voice = MyUtils.convertNoSpace(names.get(i));
			plusVoice = null;
			if(!arrVoiceNames.contains(voice)) {
				if(voice.endsWith("이")) {
					//'이'로끝나면 ~아/~ 이걸로도 되게
					//ex) 애봉이 -> 애봉아/애봉
					plusVoice = voice.substring(0, voice.length()-1) + "아";
					if(!arrVoiceNames.contains(plusVoice)) {
						arrVoiceNames.add(plusVoice); 
					}
					plusVoice = voice.substring(0, voice.length()-1);
					if(!arrVoiceNames.contains(plusVoice)) {
						arrVoiceNames.add(plusVoice); 
					}
				}
				arrVoiceNames.add(voice);
			}
		}
		Collections.sort(arrVoiceNames);
		
		//파일에 쓰기
		File namesFile = new File(RecognizedData.DIR_NAMES_ROOT + '/' + id + ".txt");
		if(!namesFile.exists()) {
			new File(RecognizedData.DIR_NAMES_ROOT).mkdirs();
		}
		BufferedWriter bw = null;
		try {
			bw = new BufferedWriter(new OutputStreamWriter(
					new FileOutputStream(namesFile, false), "utf-8"));
			bw.write(name + ":" + namesCount);
			
			size = arrVoiceNames.size();
			for(int i=0; i<size; i++) {
				String nowVoice = arrVoiceNames.get(i);
				if(!nowVoice.equals(name)) {
					bw.write('\n' + nowVoice);
				}
			}
			
			bw.flush();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try { bw.close(); }
			catch(Exception e) {}
		}
	}
	
	
	private ArrayList<String> loadVoiceNames() {
		ArrayList<String> arrVoiceNames = new ArrayList<String>();
		
		File namesFile = new File(RecognizedData.DIR_NAMES_ROOT + '/' + id + ".txt");
		BufferedReader br = null;
		try {
			br = new BufferedReader(new InputStreamReader(
					new FileInputStream(namesFile), "utf-8"));
			String line = br.readLine();
			StringTokenizer token = new StringTokenizer(line, ":");
			String name = token.nextToken();
			arrVoiceNames.add(name);
			namesCount = Integer.parseInt(token.nextToken());
			while( (line=br.readLine()) != null ) {
				arrVoiceNames.add(line);
			}
		} catch (Exception e) {
			e.printStackTrace();
			arrVoiceNames = null;
		} finally {
			try { br.close(); }
			catch(Exception e) {}
		}
		
		return arrVoiceNames;
	}
	
	private void initVoiceName() {
		namesCount = 0;
		
		String plusName = null;
		if(name.endsWith("이")) {
			//ex) 애봉이 -> 애봉아; ~아 추가
			plusName = name.substring(0, name.length()-1) + "아";
			arrVoiceNames.add(plusName);
		}
		
		File namesFile = new File(RecognizedData.DIR_NAMES_ROOT + '/' + id + ".txt");
		if(!namesFile.exists()) {
			new File(RecognizedData.DIR_NAMES_ROOT).mkdirs();
		}
		BufferedWriter bw = null;
		try {
			bw = new BufferedWriter(new OutputStreamWriter(
					new FileOutputStream(namesFile, false), "utf-8"));
			bw.write(name + ":" + namesCount);
			
			if(plusName != null) {
				bw.write('\n' + plusName);
			}
			
			bw.flush();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try { bw.close(); }
			catch(Exception e) {}
		}
	}
	
	public void addActionVoice(int actionId, ArrayList<String> actionVoiceStrings) {
		for(AnimalAction action : arrAnimalActions) {
			if(action.actionId == actionId) {
				action.addActionVoice(actionVoiceStrings);
				return;
			}
		}
		
		AnimalAction newAction = new AnimalAction(actionId);
		newAction.addActionVoice(actionVoiceStrings);
		arrAnimalActions.add(newAction);
	}
	
	private ArrayList<AnimalAction> loadActions() {
		ArrayList<AnimalAction> arrActions = new ArrayList<AnimalAction>();
		
		String myActionRoot = RecognizedData.DIR_ACTIONS_ROOT + "/" + id;
		File actionsDir = new File(myActionRoot);
		actionsDir.mkdirs();
		
		File[] actionFiles = actionsDir.listFiles(MyUtils.FILE_FILTER_GAMEDATA);
		for(File file : actionFiles) {
			arrActions.add(new AnimalAction(file));
		}
		
		return arrActions;
	}
	
	public AnimalInfo(int id) {
		this.id = id;
		this.arrVoiceNames = loadVoiceNames();
		this.name = arrVoiceNames.get(0);
		Collections.sort(arrVoiceNames);
		this.arrAnimalActions = loadActions();
	}
	
	//처음만드는 동물
	private AnimalInfo(int id, String name) {
		this.id = id;
		this.name = name;
		this.arrVoiceNames = new ArrayList<String>();
		this.arrAnimalActions = new ArrayList<AnimalAction>();
		arrVoiceNames.add(name);
		initVoiceName();
	}
	
	public static AnimalInfo makeNewAnimal(int id, String name) {
		return new AnimalInfo(id, name);
	}
	
	@Override
	public int compareTo(AnimalInfo another) {
		return ( id - another.id );
	}
	
	public class AnimalAction {
		final int actionId;
		final ArrayList<ActionVoice> arrActionVoice;
		int actionCount;
		
		public ArrayList<ActionVoice> getVoiceList() { return arrActionVoice; }
		public int getActionId() { return actionId; }
		public int getActionCount() { return actionCount; }
		
		public AnimalAction(File file) {
			StringTokenizer idToken = new StringTokenizer(file.getName(), ".");
			actionId = Integer.parseInt(idToken.nextToken());
			arrActionVoice = new ArrayList<ActionVoice>();
			actionCount = -1;
			
			BufferedReader br = null;
			try {
				br = new BufferedReader(new InputStreamReader(
						new FileInputStream(file), "utf-8"));
				String line = null;
				while( (line = br.readLine())!=null ) {
					StringTokenizer token = new StringTokenizer(line, ":");
					arrActionVoice.add(new ActionVoice(
							token.nextToken(), Integer.parseInt(token.nextToken())));
				}
				//Collections.sort(arrActionVoice);	//로드는 할필요 업당
				actionCount = getSumOfActionsVoiceCount();
			} catch (Exception e) {
				e.printStackTrace();
			} finally {
				try { br.close(); }
				catch(Exception e) {}
			}
		}
		
		//처음만드는거
		public AnimalAction(int actionId) {
			this.actionId = actionId;
			arrActionVoice = new ArrayList<ActionVoice>();
			actionCount = 0;
		}
		
		private void addActionVoiceConvert(String addingVoice, int exceptNum) {
			String convertVoice = addingVoice.substring(0, addingVoice.length()-exceptNum);	//먹어->먹, 먹자->먹, 먹어라->먹 등
			boolean bAlreadyExist = false;
			for(ActionVoice actionVoice : arrActionVoice) {
				if(actionVoice.getVoiceString().equals(convertVoice)) {
					actionVoice.addCount();
					bAlreadyExist = true;
					break;
				}
			}
			if(!bAlreadyExist)
				arrActionVoice.add( new ActionVoice(convertVoice));
		}
		
		private void addActionVoiceConvert(String addingVoice, String postfix, int exceptNum) {
			String convertVoice = addingVoice.substring(0, addingVoice.length()-exceptNum) + postfix;	//먹어->먹으, 먹자->먹으 등
			boolean bAlreadyExist = false;
			for(ActionVoice actionVoice : arrActionVoice) {
				if(actionVoice.getVoiceString().equals(convertVoice)) {
					actionVoice.addCount();
					bAlreadyExist = true;
					break;
				}
			}
			if(!bAlreadyExist)
				arrActionVoice.add( new ActionVoice(convertVoice));
		}
		
		public void addActionVoice(ArrayList<String> arrVoiceString) {
			int size = arrVoiceString.size();
			boolean bNeedSort = false, bAlreadyExist = false;;
			if(size>NUM_MAX_VOICEACTION) size = NUM_MAX_VOICEACTION;
			for(int i=0; i<size; i++) {
				bAlreadyExist = false;
				String nowVoice = MyUtils.convertNoSpace(arrVoiceString.get(i));
				for(ActionVoice actionVoice : arrActionVoice) {
					if(actionVoice.getVoiceString().equals(nowVoice)) {
						actionVoice.addCount();
						bAlreadyExist = true;
						break;
					}
				}
				if(!bAlreadyExist) {
					arrActionVoice.add( new ActionVoice(nowVoice) );
					
					//TODO 접속사를 위해서
					if(nowVoice.endsWith("어")) {
						addActionVoiceConvert(nowVoice, 1);
						addActionVoiceConvert(nowVoice, "으", 1);
					} else if(nowVoice.endsWith("자")) {
						addActionVoiceConvert(nowVoice, 1);
						addActionVoiceConvert(nowVoice, "으", 1);
					} else if(nowVoice.endsWith("어라")) {
						addActionVoiceConvert(nowVoice, 2);
					} else if(nowVoice.endsWith("해")) {
						addActionVoiceConvert(nowVoice, 1);
					} else if(nowVoice.endsWith("었")) {
						addActionVoiceConvert(nowVoice, 1);
						addActionVoiceConvert(nowVoice, "으", 1);
					} else if(nowVoice.endsWith("거")) {
						addActionVoiceConvert(nowVoice, 1);
					}
					//일단 이정도만?
					
					bNeedSort = true;
				}
				
			}
			if(bNeedSort) Collections.sort(arrActionVoice);
			actionCount+=size;
			
			String actionDir = RecognizedData.DIR_ACTIONS_ROOT + '/' + id;
			File file = new File(actionDir + '/' + actionId + ".txt");
			if(!file.exists()) {
				new File(actionDir).mkdirs();
			}
			BufferedWriter bw = null;
			try {
				bw = new BufferedWriter(new OutputStreamWriter(
						new FileOutputStream(file, false),"utf-8"));
				size = arrActionVoice.size();
				for(int i=0; i<size; i++) {
					ActionVoice actionVoice = arrActionVoice.get(i);
					if(i!=0) bw.write('\n');
					bw.write(actionVoice.voice + ':' + actionVoice.count);
				}
				bw.flush();
			} catch(Exception e) {
				e.printStackTrace();
			} finally {
				try { bw.close(); }
				catch(Exception e) {}
			}
			
		}
		
		private int getSumOfActionsVoiceCount() {
			int sum = 0;
			for(ActionVoice av : arrActionVoice) {
				sum += av.count;
			}
			return sum;
		}
		
		public class ActionVoice implements Comparable<ActionVoice> {
			final String voice;
			int count;
			
			public void addCount() {
				count++;
			}
			
			public String getVoiceString() {
				return voice;
			}
			
			@Override
			public String toString() {
				return voice;
			}
			
			public ActionVoice(String voice, int count) {
				this.voice = voice;
				this.count = count;
			}
			
			public ActionVoice(String voice) {
				this.voice = voice;
				this.count = 1;
			}

			@Override
			public int compareTo(ActionVoice another) {
				//길이우선->이름순 정렬
				int comp = (another.voice.length() - voice.length()) * 100000;
				if(comp == 0) comp = voice.compareTo(another.voice);
				return comp;
			}
		}
	}
}
