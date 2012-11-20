package com.swm.vg.voicetoactions;

import java.util.ArrayList;
import java.util.Collections;

import android.util.Log;

import com.swm.vg.data.ActionInfo;
import com.swm.vg.data.ActionList;
import com.swm.vg.data.AnimalInfo;
import com.swm.vg.data.RecognizedData;


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
	
	private static interface Node {
		
	}
	
	private static class AnimalNode implements Node {
//		int animalId;
		AnimalInfo animalInfo;
		int findAction = ActionList.ACTION_EXTRA_UNKNOWN;
		boolean neg = false;
		AnimalNode(AnimalInfo animalInfo) {
			this.animalInfo = animalInfo;
		}
		void setFindAction(int actionId) {
			findAction = actionId;
		}
	}
	
	private static class ActionNode implements Node {
		int actionId;
		String actionVoice;
		ActionNode(int actionId, String actionVoice) {
			this.actionId = actionId;
			this.actionVoice = actionVoice;
		}
	}
	
	
	
	private static class SearchTree {
		public static final byte FLAG_NONE = -1;
		public static final byte FLAG_UNCONFIRMED = 0;
		public static final byte FLAG_ANIMAL = 1;
		public static final byte FLAG_ACTION = 2;
		public static final byte FLAG_ANIMAL_NEG = 3;
		public static final byte FLAG_ACTION_NEG = 4;
		public static final byte FLAG_NEG_STRING = 5;
		public static final byte FLAG_EXTRA = 6;
		
		public static final byte CHILDPOS_LEFT = 0;
		public static final byte CHILDPOS_ANYWHERE = 1;
		public static final byte CHILDPOS_RIGHT = 2;
		
		
		byte flag = FLAG_NONE;
		Object node = null;
		SearchTree leftChild = null, rightChild = null;
		
		public SearchTree(Object nodeData, byte flag) {
			this.node = nodeData;
			this.flag = flag;
		}
		
		void setData(Object nodeData, byte flag) {
			this.node = nodeData;
			this.flag = flag;
		}
		
		private static ArrayList<SearchTree> tempList =  null;
		static ArrayList<SearchTree> getNodeListByInOrder(SearchTree treeRoot) {
			tempList = new ArrayList<SearchTree>();
			inOrderSearchAdding(treeRoot);
			
//			ArrayList<SearchTree> nodeList = tempList;
//			tempList = null;
//			return nodeList;
			
			return tempList;
		}
		
		static ArrayList<SearchTree> getAnimalNodeListByInOrder(SearchTree treeRoot) {
			ArrayList<SearchTree> nodeList = getNodeListByInOrder(treeRoot);
			ArrayList<SearchTree> animalNodeList = new ArrayList<SearchTree>();
			for(SearchTree node : nodeList) {
				if(node.flag == FLAG_ANIMAL || node.flag == FLAG_ANIMAL_NEG)
					animalNodeList.add(node);
			}
			return animalNodeList;
		}
		
		private static void inOrderSearchAdding(SearchTree node) {
			if(node.leftChild != null) {
				inOrderSearchAdding(node.leftChild);
			}
			if (node.flag > FLAG_NONE) {
				tempList.add(node);
			}
			if (node.rightChild != null) {
				inOrderSearchAdding(node.rightChild);
			}
		}
		
		//this 기준으로 바로 왼쪽/오른쪽/아무데나
		void addChild(Object nodeData, byte flag, byte childPos) {
			switch(childPos) {
			case CHILDPOS_LEFT:
				if(leftChild == null) {
					leftChild = new SearchTree(nodeData, flag);
				} else {
					SearchTree nowNode = leftChild.rightChild;
					while(true) {
						if(nowNode == null) {
							nowNode = new SearchTree(nodeData, flag);
							break;
						} else {
							nowNode = nowNode.rightChild;
						}
					}
				}
				break;
			case CHILDPOS_RIGHT:
				if(rightChild == null) {
					rightChild = new SearchTree(nodeData, flag);
				} else {
					SearchTree nowNode = rightChild.leftChild;
					while(true) {
						if(nowNode == null) {
							nowNode = new SearchTree(nodeData, flag);
							break;
						} else {
							nowNode = nowNode.leftChild;
						}
					}
				}
				break;
			case CHILDPOS_ANYWHERE:
				if(leftChild == null) {
					leftChild = new SearchTree(nodeData, flag);
				} else if(rightChild == null) {
					rightChild = new SearchTree(nodeData, flag);
				} else {
					leftChild.addChild(nodeData, flag, CHILDPOS_ANYWHERE);
				}
				break;
			}
		}
	}
	
	private static SearchTree treeRoot = null;
	private static void inOrderPatternMatchTree(SearchTree node) {
		switch(node.flag) {
		case SearchTree.FLAG_UNCONFIRMED:
			break;
		case SearchTree.FLAG_ANIMAL:
			break;
		case SearchTree.FLAG_ACTION:
			break;
		case SearchTree.FLAG_EXTRA:
			break;
		case SearchTree.FLAG_NONE:
			break;
		}
	}
	
	private static void searchAnimalsAddTree(SearchTree node) {
		if(node == null) {
			return;
		}
		if(node.flag == SearchTree.FLAG_UNCONFIRMED) {
			boolean bFind = false;
			SearchedAnimalInfo searchedAnimal = null;
			for(SearchedAnimalInfo info : searchedAnimalList) {
				if( ((String)node.node).contains(info.selectedName) ) {
					if(((String)node.node).equals(info.selectedName)) {
						//같으면 그자체를 동물로
						node.setData(new AnimalNode(info.info), SearchTree.FLAG_ANIMAL); 
						return;
						//bFind = false;
						//break;
					}
					bFind = true;
					searchedAnimal = info;
					break;
				}
			}
			
			if(bFind) {
				String[] splits = getSplitedStringOnce((String)node.node, searchedAnimal.selectedName, true);
				if(splits != null) {
					if(!splits[0].equals("")) {
						node.addChild(splits[0], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_LEFT);
					}
					if(!splits[1].equals("")) {
						node.addChild(splits[1], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_RIGHT);
					}
					
					searchAnimalsAddTree(node.leftChild);
					searchAnimalsAddTree(node.rightChild);
					
					node.setData(new AnimalNode(searchedAnimal.info), SearchTree.FLAG_ANIMAL);
				}
			}
		}
		
//		if(node.flag == SearchTree.FLAG_UNCONFIRMED) {
//			String[] splits = getSplitedStringOnce((String)node.node, rex, byLeft)
//		}
	}
	
	public static ArrayList<ActionInfo> search2(String sentence, ArrayList<AnimalInfo> arrAnimal) {
		ArrayList<ActionInfo> searchList = new ArrayList<ActionInfo>();
		ArrayList<ActionInfo> searchListFirst = new ArrayList<ActionInfo>();
		boolean bSearchListFirst = true;
		
		String str = MyUtils.convertNoSpace(sentence);
		
		int animalId = -1, actionId = ActionList.ACTION_EXTRA_UNKNOWN;
		searchedAnimalList = new ArrayList<SearchedAnimalInfo>();
		
		String seletedName = null;
		
		for(AnimalInfo animal : arrAnimal) {
			//모든 동물을 대상으로
			seletedName = null;
			final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
			for(String name : arrVoiceNames) {
				if(str.contains(name)) {
					if(str.equals(name)) {
						searchList = new ArrayList<ActionInfo>();
						searchList.add(new ActionInfo(animal.getId(), actionId));
						return searchList;
					}
					searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
				}
			}
		}
		
		if(searchedAnimalList.size() > 0) {
			Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
			{
				//찾은동물들 로그찍고
				String aniList = "" + searchedAnimalList.size() + ":";
				for(SearchedAnimalInfo info : searchedAnimalList) {
					aniList += (info.info.getName() +'/');
				}
				Log.d("Searched Animal List", aniList);
			}
			
			searchAnimal:
			for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) { 
				String[][] splits = getSplitedStrings(""+str, searchedAnimal.selectedName);
				searchSplit:
				if(splits!=null)
				for(String[] splString : splits) {
					//메인 루틴 시작
					//트리루트 만듦
					treeRoot = new SearchTree(new AnimalNode(searchedAnimal.info), SearchTree.FLAG_ANIMAL);
					if(!splString[0].equals(""))
						treeRoot.leftChild = new SearchTree(splString[0], SearchTree.FLAG_UNCONFIRMED);
					if(!splString[1].equals(""))
						treeRoot.rightChild = new SearchTree(splString[1], SearchTree.FLAG_UNCONFIRMED);
					
					//동물들부터 다 찾아서 트리에 찰드 추가
					searchAnimalsAddTree(treeRoot.leftChild);
					searchAnimalsAddTree(treeRoot.rightChild);
					
					//찾아진 동물들 트리 리스트를 받아와서 액션을 찾아보자
					ArrayList<SearchTree> animalNodeList = SearchTree.getAnimalNodeListByInOrder(treeRoot);
					int animalListSize = animalNodeList.size();
					{
						String aniList = "";
						for(SearchTree info : animalNodeList) {
							aniList += (((AnimalNode)info.node).animalInfo.getName() +'/');
						}
						Log.d("now Animal List", aniList);
					}
					searchAnimalAction:for(int i=0; i<animalListSize; i++) {
						//동물 하나씩마다 액션을 찾는데...
						SearchTree nowAnimalNode = animalNodeList.get(i);
						AnimalInfo nowAnimalInfo = ((AnimalNode)nowAnimalNode.node).animalInfo;
						AnimalInfo.AnimalAction selectedAction = null;
						String selectedVoice = null;
						SearchTree selectedTreeNode = null;
						boolean selectedFindLeft = true;
						
						//DEBUG_treeroot->list 변환이 제대로 안되고있다.
						ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
						int treeSize = treeList.size();
						int animalPos = treeList.indexOf(nowAnimalNode);
						Log.d("search Voice Recog", "now Animal Pos : "+animalPos);
						
						boolean bFindLeft = true;
						int maxLen = -1, maxNum = -1, nearLeftPos = -1, nearRightPos = Integer.MAX_VALUE,
								nearNodePos = Integer.MAX_VALUE;
						searchNodeTree: for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
							SearchTree nowNode = treeList.get(nowNodePos);
							
							if(nowNode.flag == SearchTree.FLAG_UNCONFIRMED) {
								//미확인일경우에서 찾는다
								String nowSplString = (String)nowNode.node;
								ArrayList<AnimalInfo.AnimalAction> actionList = nowAnimalInfo.getActionList();
								boolean bFindFirst = true;
								
								if(animalPos > nowNodePos) {	//동물왼쪽
									bFindLeft = true;
								} else if(animalPos < nowNodePos) {	//동물 오른쪽
									bFindLeft = false;
								}
								
								for(AnimalInfo.AnimalAction action : actionList) {
									ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
									for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
										if(bFindFirst) {
											//nodePos검사
											bFindFirst = false;
											int nowNearNodePos = Math.abs(animalPos-nowNodePos);	// +에서 1, 이후 -1, -로 감, 앞에서 뒤로
											if( nowNearNodePos < nearNodePos ) {
												//현재값이 더 가까우면
												nearNodePos = nowNearNodePos;
											} else if ( nowNearNodePos == nearNodePos ) {
												//둘이 가까움이 같으면
												//continue;
												break searchNodeTree;	//어차피 점점 더 멀어지므로 오른쪽인데,
														//둘이 가까움이 같으면 왼쪽 우선으로 할것임.
											} else {
												//현재값이 더 멀면
												//continue;
												break searchNodeTree;	//어차피 점점 더 멀어지므로 한번 멀어지면 끝임
												
											}
										}
										
										String voice = actionVoice.getVoiceString();
										if(voice.equals(nowSplString)) {
											//같으면 node자체를 바로 액션으로.
											selectedTreeNode = nowNode;
											selectedAction = action;
											//Unconfirm->action으로 flag변환
											selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), voice),
													SearchTree.FLAG_ACTION);
											//animal node에 액션지정
											((AnimalNode)nowAnimalNode.node).setFindAction(selectedAction.getActionId());
											continue searchAnimalAction;
										}
										
										int nowPos = -1;
										if( (nowPos=nowSplString.indexOf(voice)) != -1) {
											//nodePos -> stringPos비교
											//동물에 따른 보이스 최장메치 찾기
											int nowLen = voice.length();
											int nowNum = action.getActionCount();
											
											if(bFindLeft) {
												//왼쪽 -> pos클수록 가까움
												nowPos = nowPos+voice.length();	//스트링의 끝 pos를 지정
												if(nowPos > nearLeftPos) {
													nearLeftPos = nowPos;
													maxLen = nowLen;
													nowNum = maxNum;
													selectedTreeNode = nowNode;
													selectedAction = action;
													selectedVoice = actionVoice.getVoiceString();
													selectedFindLeft = bFindLeft;
												} else if (nowPos == nearLeftPos) {
													//pos같으면 -> length비교
													if(nowLen > maxLen) {
														maxLen = nowLen;
														nowNum = maxNum;
														selectedTreeNode = nowNode;
														selectedAction = action;
														selectedVoice = actionVoice.getVoiceString();
														selectedFindLeft = bFindLeft;
													} else if (nowLen == maxLen) {
														//같은 최장길이일시 가르친 횟수로
														if(nowNum > maxNum) {
															nowNum = maxNum;
															selectedTreeNode = nowNode;
															selectedAction = action;
															selectedVoice = actionVoice.getVoiceString();
															selectedFindLeft = bFindLeft;
														}
													}
												}
											} else {
												//오른쪽 -> pos작을수록 가까움
												if(nowPos < nearRightPos) {
													nearRightPos = nowPos;
													maxLen = nowLen;
													nowNum = maxNum;
													selectedTreeNode = nowNode;
													selectedAction = action;
													selectedVoice = actionVoice.getVoiceString();
													selectedFindLeft = bFindLeft;
												} else if (nowPos == nearRightPos) {
													//pos같으면 -> length비교
													if(nowLen > maxLen) {
														maxLen = nowLen;
														nowNum = maxNum;
														selectedTreeNode = nowNode;
														selectedAction = action;
														selectedVoice = actionVoice.getVoiceString();
														selectedFindLeft = bFindLeft;
													} else if (nowLen == maxLen) {
														//같은 최장길이일시 가르친 횟수로
														if(nowNum > maxNum) {
															nowNum = maxNum;
															selectedTreeNode = nowNode;
															selectedAction = action;
															selectedVoice = actionVoice.getVoiceString();
															selectedFindLeft = bFindLeft;
														}
													}
												}
											}
											
											
										}
									}
								}
								
							}
						}//end of Label(for) searchLabelTree
						
						//찾은거 가지고 액션지정
						if(selectedAction != null) {
							String unconfirmString = (String)selectedTreeNode.node;
							String[] splitUnconfirm = null;
							if(selectedFindLeft) {	//왼쪽에서 찾았으면
								splitUnconfirm = getSplitedStringOnce(unconfirmString, selectedVoice, false);	//오른쪽에 자르고
							} else {		//오른쪽에서 찾았으면
								splitUnconfirm = getSplitedStringOnce(unconfirmString, selectedVoice, true);	//왼쪽에서자른다
							}
							
							if(!splitUnconfirm[0].equals(""))
								selectedTreeNode.addChild(splitUnconfirm[0], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_LEFT);
							if(!splitUnconfirm[1].equals(""))
								selectedTreeNode.addChild(splitUnconfirm[1], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_RIGHT);
							
							//부모노드는 액션으로 변경
							selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), selectedVoice), 
									SearchTree.FLAG_ACTION);
							//animal node에 액션지정
							((AnimalNode)nowAnimalNode.node).setFindAction(selectedAction.getActionId());
						}
						
					} //end of Label(for) searchAnimalAction
					
					
					
					//최종정리
					ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
					int treeSize = treeList.size();
					
					if(animalNodeList.size() == 1) {
						//동물 하나인거, 하나인데 액션을 못찾을린 없는거니까,
						//하나일경우엔 복합액션(연속액션)을 찾자
						AnimalNode animalNode = (AnimalNode)animalNodeList.get(0).node;
						if(animalNode.findAction == ActionList.ACTION_EXTRA_UNKNOWN) {
							//먼저 액션못찾은 동물 하나만 있는거면
							if(bSearchListFirst) {
								//처음맞춘거 냅두기
								bSearchListFirst = false;
								searchListFirst = new ArrayList<ActionInfo>();
								searchListFirst.add(new ActionInfo(animalNode.animalInfo.getId(), animalNode.findAction));
							}
						} else {
							//액션찾은동물이라면 더있는지 찾아보자
							ArrayList<Integer> actionIdList = new ArrayList<Integer>();
							actionIdList.add(Integer.valueOf(animalNode.findAction));
							for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
								SearchTree nowTreeNode = treeList.get(nowNodePos);
								if(nowTreeNode.flag == SearchTree.FLAG_UNCONFIRMED) {
									//미확인에서 액션들을 찾는다
									ArrayList<AnimalInfo.AnimalAction> actionList = animalNode.animalInfo.getActionList();
									for(AnimalInfo.AnimalAction action : actionList )  {
										ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
										for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
											if( ((String)nowTreeNode.node).contains(actionVoice.getVoiceString()) ) {
												//보이스스트링 포함하고있으면
												Integer nowActionId = Integer.valueOf(action.getActionId());
												if(!actionIdList.contains(nowActionId)) {
													actionIdList.add(nowActionId);
												}
												break;
											}
										}
									}
								}
							}
							
							//액션인포리스트만들어서 리턴
							searchList = new ArrayList<ActionInfo>();
							for(Integer nowActionId : actionIdList) {
								searchList.add(new ActionInfo(animalNode.animalInfo.getId(), nowActionId.intValue()));
							}
							
							return searchList;
						}
					} else {
						//하나이상일때는
						for(SearchTree animalNode : animalNodeList) {
							if(((AnimalNode)animalNode.node).findAction == ActionList.ACTION_EXTRA_UNKNOWN) {
								//아직 액션을 못찾았다?
								//->그러면 공통액션이거나 이름만 부르거나 인식을 못한거임
								//공통액션일 경우를 찾아보자.
								//공통액션인 경우
								boolean bFind = true;
								int nearNodePos = Integer.MAX_VALUE;
								SearchTree findActionNode = null;
								
								lastSearchNode:
								for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
									SearchTree nowTreeNode = treeList.get(nowNodePos);
									if(nowTreeNode.flag == SearchTree.FLAG_ACTION) {
										//액션인노드를 찾아서 액션보이스 검색
										int animalPos = treeList.indexOf(animalNode);
										ArrayList<AnimalInfo.AnimalAction> actionList = ((AnimalNode)animalNode.node).animalInfo.getActionList();
										String searchedActionVoice = ((ActionNode)nowTreeNode.node).actionVoice;
										
										bFind = false;
										lastSearchActionList:
										for(AnimalInfo.AnimalAction action : actionList )  {
											ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
											for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
	//											Log.d("find multi action", actionVoice.getVoiceString() + "/" + searchedActionVoice );
												if( actionVoice.getVoiceString().equals( searchedActionVoice ) ) {
													//찾음
													//DEBUG_
													int nowNearNodePos = Math.abs(animalPos-nowNodePos);	// +에서 1, 이후 -1, -로 감, 앞에서 뒤로
													if( nowNearNodePos < nearNodePos ) {
														//현재값이 더 가까우면
														nearNodePos = nowNearNodePos;
														findActionNode = nowTreeNode;
														if(nowNearNodePos == 1)
															break lastSearchNode;
														else
															break lastSearchActionList;
													}
												}
											}
										}
									}
								}
								
								if(findActionNode != null) {
									//찾아져있으면
									((AnimalNode)animalNode.node).setFindAction(((ActionNode)findActionNode.node).actionId);
								} else {
									((AnimalNode)animalNode.node).setFindAction(ActionList.ACTION_EXTRA_UNKNOWN);
								}
							}
						}
						
						
						int animalSize = animalNodeList.size();
						int noActionCount = 0;
						searchList = new ArrayList<ActionInfo>();
						for(SearchTree animalNode : animalNodeList) {
							AnimalNode nowAnimalNode = ((AnimalNode)animalNode.node);
							searchList.add(new ActionInfo(nowAnimalNode.animalInfo.getId(), nowAnimalNode.findAction));
							if(nowAnimalNode.findAction == ActionList.ACTION_EXTRA_UNKNOWN) noActionCount++;	//액션못찾은 동물 갯수세서
						}
						
						{
							String resultString = "";
							for(SearchTree animalNode : animalNodeList) {
								AnimalNode nowAnimalNode = ((AnimalNode)animalNode.node);
								resultString += ( nowAnimalNode.animalInfo.getName() + "/" );
							}
							Log.d("search result ", resultString);
						}
						
						if(animalSize == noActionCount) {
							//전부 액션을 못찾은 동물일 경우
							if(bSearchListFirst) {
								//처음맞춘거 냅두기
								bSearchListFirst = false;
								searchListFirst = searchList;
								searchList = new ArrayList<ActionInfo>();
							}
							searchList.clear();
						} else {
							//하나라도찾았으면, 그냥 리턴
							return searchList;
						}
					}//endof 하나이상일때 최종로직
					
				}//end of each string
			}
			
			
			
		}//end of (if seached animal)
		
		return searchListFirst;
	}
	
	//TODO check
	
	public static ArrayList<ActionInfo> searchAll(ArrayList<String> sentences, ArrayList<AnimalInfo> arrAnimal) {
		ArrayList<String> negatives = RecognizedData.sharedRecognizedData().getNegativeConjunctions();
		ArrayList<String> ands = RecognizedData.sharedRecognizedData().getAnds();
		
		ArrayList<ActionInfo> searchList = new ArrayList<ActionInfo>();
		ArrayList<ActionInfo> searchListFirst = new ArrayList<ActionInfo>();
		boolean bSearchListFirst = true;
		
		int sentencesSize = sentences.size();
		if(sentencesSize>5) sentencesSize = 5;
		else if(sentencesSize==0) return searchList;
		
		for(int sNum=0; sNum<sentencesSize; sNum++) {
			String str = MyUtils.convertNoSpace(sentences.get(sNum));
			Log.d("Search All", "nowSentence: "+str);
			
			int animalId = -1, actionId = ActionList.ACTION_EXTRA_UNKNOWN;
			searchedAnimalList = new ArrayList<SearchedAnimalInfo>();
			
			String seletedName = null;
			
			for(AnimalInfo animal : arrAnimal) {
				//모든 동물을 대상으로
				seletedName = null;
				final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
				for(String name : arrVoiceNames) {
					if(str.contains(name)) {
						if(str.equals(name)) {
							searchList = new ArrayList<ActionInfo>();
							searchList.add(new ActionInfo(animal.getId(), actionId));
							return searchList;
						}
						searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
					}
				}
			}
			
			if(searchedAnimalList.size() > 0) {
				Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
				{
					//찾은동물들 로그찍고
					String aniList = "" + searchedAnimalList.size() + ":";
					for(SearchedAnimalInfo info : searchedAnimalList) {
						aniList += (info.info.getName() +'/');
					}
					Log.d("Searched Animal List", aniList);
				}
				
				searchAnimal:
				for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) { 
					String[][] splits = getSplitedStrings(""+str, searchedAnimal.selectedName);
					searchSplit:
					if(splits!=null)
					for(String[] splString : splits) {
						//메인 루틴 시작
						//트리루트 만듦
						treeRoot = new SearchTree(new AnimalNode(searchedAnimal.info), SearchTree.FLAG_ANIMAL);
						if(!splString[0].equals(""))
							treeRoot.leftChild = new SearchTree(splString[0], SearchTree.FLAG_UNCONFIRMED);
						if(!splString[1].equals(""))
							treeRoot.rightChild = new SearchTree(splString[1], SearchTree.FLAG_UNCONFIRMED);
						
						//동물들부터 다 찾아서 트리에 찰드 추가
						searchAnimalsAddTree(treeRoot.leftChild);
						searchAnimalsAddTree(treeRoot.rightChild);
						
						//찾은 동물들 중 Negative 있는지 검사
						ArrayList<SearchTree> negSearchTreeList = SearchTree.getNodeListByInOrder(treeRoot);
						for(int n=0; n<negSearchTreeList.size()-1; n++) {
							SearchTree nowNode = negSearchTreeList.get(n);
							if(nowNode.flag == SearchTree.FLAG_ANIMAL) {
								SearchTree nextNode = negSearchTreeList.get(n+1);
								if(nextNode.flag == SearchTree.FLAG_UNCONFIRMED) {
									String nextString = ((String)nextNode.node);
									boolean bNegative = false;
									for(String neg : negatives) {
										if(nextString.startsWith(neg)) {
											bNegative = true;
											break;
										}
									}
									if(bNegative) {
										nowNode.flag = SearchTree.FLAG_ANIMAL_NEG;
										((AnimalNode)nowNode.node).neg = true;
									}
								}
							}
						}
						
						//찾아진 동물들 트리 리스트를 받아와서 액션을 찾아보자
						ArrayList<SearchTree> animalNodeList = SearchTree.getAnimalNodeListByInOrder(treeRoot);
						int animalListSize = animalNodeList.size();
						{
							String aniList = "";
							for(SearchTree info : animalNodeList) {
								aniList += (((AnimalNode)info.node).animalInfo.getName() +'/');
							}
							Log.d("now Animal List", aniList);
						}
						searchAnimalAction:for(int i=0; i<animalListSize; i++) {
							//동물 하나씩마다 액션을 찾는데...
							SearchTree nowAnimalNode = animalNodeList.get(i);
							AnimalInfo nowAnimalInfo = ((AnimalNode)nowAnimalNode.node).animalInfo;
							if(((AnimalNode)nowAnimalNode.node).neg) continue;
							
							AnimalInfo.AnimalAction selectedAction = null;
							String selectedVoice = null;
							SearchTree selectedTreeNode = null;
							boolean selectedFindLeft = true;
							
							ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
							int treeSize = treeList.size();
							int animalPos = treeList.indexOf(nowAnimalNode);
							Log.d("search Voice Recog", "now Animal Pos : "+animalPos);
							
							boolean bFindLeft = true;
							int maxLen = -1, maxNum = -1, nearLeftPos = -1, nearRightPos = Integer.MAX_VALUE,
									nearNodePos = Integer.MAX_VALUE, findPos = Integer.MAX_VALUE;
							searchNodeTree: for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
								SearchTree nowNode = treeList.get(nowNodePos);
								
								if(nowNode.flag == SearchTree.FLAG_UNCONFIRMED) {
									//미확인일경우에서 찾는다
									String nowSplString = (String)nowNode.node;
									ArrayList<AnimalInfo.AnimalAction> actionList = nowAnimalInfo.getActionList();
									boolean bFindFirst = true;
									nearNodePos = Integer.MAX_VALUE;
									
									if(animalPos > nowNodePos) {	//동물왼쪽
										bFindLeft = true;
									} else if(animalPos < nowNodePos) {	//동물 오른쪽
										bFindLeft = false;
									}
									
									for(AnimalInfo.AnimalAction action : actionList) {
										ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
										for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
											
											
											String voice = actionVoice.getVoiceString();
											/*if(voice.equals(nowSplString)) {
												//같으면 node자체를 바로 액션으로.
												selectedTreeNode = nowNode;
												selectedAction = action;
												//Unconfirm->action으로 flag변환
												selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), voice),
														SearchTree.FLAG_ACTION);
												//animal node에 액션지정
												((AnimalNode)nowAnimalNode.node).setFindAction(selectedAction.getActionId());
												continue searchAnimalAction;
											}*/
											
											int nowPos = -1;
											if( (nowPos=nowSplString.indexOf(voice)) != -1) {
												if(bFindFirst) {
													bFindFirst = false;
													
													int findNearNodePos = Math.abs(animalPos - findPos);	//동물위치와 찾은것 같의 거리
													int nowNearNodePos = Math.abs(animalPos - nowNodePos);
													
													if( nowNearNodePos < findNearNodePos ) {
														//더 가까우면
														findPos = nowNodePos;
													} else if (nowNearNodePos == findNearNodePos) {
														//같아졌으면
													} else {
														//더 멀어지면
														break searchNodeTree;
													}
													
													/*//nodePos검사
													bFindFirst = false;
													// +에서 1, 이후 -1, -로 감, 앞에서 뒤로
													int nowNearNodePos = animalPos-nowNodePos;
													int nowNearAbsNodePos = Math.abs(nowNearNodePos);	//현재 노드의 상대위치(거리)
													int nowNearFindNodePos = Math.abs(animalPos - findPos);	//마지막으로 찾은 노드의 상대위치
													if( nowNearAbsNodePos < nowNearFindNodePos ) {
														//현재값이 마지막으로 찾은 노드보다 더 가까우면
														nearNodePos = nowNearFindNodePos;
													} else if ( nowNearAbsNodePos == nowNearFindNodePos ) {
														//둘이 가까움이 같으면
														//continue;
//														break searchNodeTree;	//어차피 점점 더 멀어지므로 오른쪽인데,
																//둘이 가까움이 같으면 왼쪽X 오른쪽! 우선으로 할것임.
													} else {
														//현재값이 더 멀면
														//continue;
														break searchNodeTree;	//어차피 점점 더 멀어지므로 한번 멀어지면 끝임
														
													}*/
												}
												
												findPos = nowNodePos;
												
												//nodePos -> stringPos비교
												//동물에 따른 보이스 최장메치 찾기
												int nowLen = voice.length();
												int nowNum = action.getActionCount();
												
												if(bFindLeft) {
													//왼쪽 -> pos클수록 가까움
													nowPos = nowPos+voice.length();	//스트링의 끝 pos를 지정
													if(nowPos > nearLeftPos) {
														nearLeftPos = nowPos;
														maxLen = nowLen;
														nowNum = maxNum;
														selectedTreeNode = nowNode;
														selectedAction = action;
														selectedVoice = actionVoice.getVoiceString();
														selectedFindLeft = bFindLeft;
													} else if (nowPos == nearLeftPos) {
														//pos같으면 -> length비교
														if(nowLen > maxLen) {
															maxLen = nowLen;
															nowNum = maxNum;
															selectedTreeNode = nowNode;
															selectedAction = action;
															selectedVoice = actionVoice.getVoiceString();
															selectedFindLeft = bFindLeft;
														} else if (nowLen == maxLen) {
															//같은 최장길이일시 가르친 횟수로
															if(nowNum > maxNum) {
																nowNum = maxNum;
																selectedTreeNode = nowNode;
																selectedAction = action;
																selectedVoice = actionVoice.getVoiceString();
																selectedFindLeft = bFindLeft;
															}
														}
													}
												} else {
													//오른쪽 -> pos작을수록 가까움
													if(nowPos < nearRightPos) {
														nearRightPos = nowPos;
														maxLen = nowLen;
														nowNum = maxNum;
														selectedTreeNode = nowNode;
														selectedAction = action;
														selectedVoice = actionVoice.getVoiceString();
														selectedFindLeft = bFindLeft;
													} else if (nowPos == nearRightPos) {
														//pos같으면 -> length비교
														if(nowLen > maxLen) {
															maxLen = nowLen;
															nowNum = maxNum;
															selectedTreeNode = nowNode;
															selectedAction = action;
															selectedVoice = actionVoice.getVoiceString();
															selectedFindLeft = bFindLeft;
														} else if (nowLen == maxLen) {
															//같은 최장길이일시 가르친 횟수로
															if(nowNum > maxNum) {
																nowNum = maxNum;
																selectedTreeNode = nowNode;
																selectedAction = action;
																selectedVoice = actionVoice.getVoiceString();
																selectedFindLeft = bFindLeft;
															}
														}
													}
												}
												
											}
										}
									}
									
								}
							}//end of Label(for) searchLabelTree
							
							//찾은거 가지고 액션지정
							if(selectedAction != null) {
								String unconfirmString = (String)selectedTreeNode.node;
								String[] splitUnconfirm = null;
								String temp = "None";
								
								boolean bNega = false;
								
								if(selectedFindLeft) {	//왼쪽에서 찾았으면
									splitUnconfirm = getSplitedStringOnce(unconfirmString, selectedVoice, false);	//오른쪽에 자르고
								} else {		//오른쪽에서 찾았으면
									splitUnconfirm = getSplitedStringOnce(unconfirmString, selectedVoice, true);	//왼쪽에서자른다
								}
								
								if(!splitUnconfirm[0].equals(""))
									selectedTreeNode.addChild(splitUnconfirm[0], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_LEFT);
								if(!splitUnconfirm[1].equals("")) {
									selectedTreeNode.addChild(splitUnconfirm[1], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_RIGHT);
								
									for(String negative : negatives) {
										if(splitUnconfirm[1].startsWith(negative)) {	//액션오른쪽이 네거티브면
											bNega = true;
											temp = negative;
											break;
										}
									}
								}
								
								if(bNega) {
									//액션+네거티브
									Log.d("neg found", splitUnconfirm[1] + ":" + temp);
									selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), selectedVoice), 
											SearchTree.FLAG_ACTION_NEG);
									((AnimalNode)nowAnimalNode.node).neg = true;
								} else {
									//부모노드는 액션으로 변경
									selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), selectedVoice), 
											SearchTree.FLAG_ACTION);
									
								}
								Log.d("Action Mactch", ((AnimalNode)nowAnimalNode.node).animalInfo.getName() + ":" + selectedAction.getActionId());
								
								//animal node에 액션지정
								((AnimalNode)nowAnimalNode.node).setFindAction(selectedAction.getActionId());
							}
							
						} //end of Label(for) searchAnimalAction
						
						
						
						//최종정리
						ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
						int treeSize = treeList.size();
						
						if(animalNodeList.size() == 1) {
							//동물 하나인거, 하나인데 액션을 못찾을린 없는거니까,
							//하나일경우엔 복합액션(연속액션)을 찾자
							AnimalNode animalNode = (AnimalNode)animalNodeList.get(0).node;
							if(animalNode.findAction == ActionList.ACTION_EXTRA_UNKNOWN && !animalNode.neg) {
								//먼저 액션못찾은 동물 하나만 있는거면
								if(bSearchListFirst) {
									//처음맞춘거 냅두기
									bSearchListFirst = false;
									searchListFirst = new ArrayList<ActionInfo>();
									searchListFirst.add(new ActionInfo(animalNode.animalInfo.getId(), animalNode.findAction));
								}
							} else {
								//액션찾은동물이라면 더있는지 찾아보자
								ArrayList<Integer> actionIdList = new ArrayList<Integer>();
								
								if(animalNodeList.get(0).flag == SearchTree.FLAG_ANIMAL && !animalNode.neg) {
									actionIdList.add(Integer.valueOf(animalNode.findAction));
								
									for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
										SearchTree nowTreeNode = treeList.get(nowNodePos);
										if(nowTreeNode.flag == SearchTree.FLAG_UNCONFIRMED) {
											//미확인에서 액션들을 찾는다
											ArrayList<AnimalInfo.AnimalAction> actionList = animalNode.animalInfo.getActionList();
											for(AnimalInfo.AnimalAction action : actionList )  {
												ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
												for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
													if( ((String)nowTreeNode.node).contains(actionVoice.getVoiceString()) ) {
														//보이스스트링 포함하고있으면
														Integer nowActionId = Integer.valueOf(action.getActionId());
														if(!actionIdList.contains(nowActionId)) {
															actionIdList.add(nowActionId);
														}
														break;
													}
												}
											}
										}
									}
								}
								
								//액션인포리스트만들어서 리턴
								searchList = new ArrayList<ActionInfo>();
								for(Integer nowActionId : actionIdList) {
									searchList.add(new ActionInfo(animalNode.animalInfo.getId(), nowActionId.intValue()));
								}
								
								Log.d("searches", "search one aniaml done");
								return searchList;
							}
						} else {
							//하나이상일때는
							for(SearchTree animalNode : animalNodeList) {
								if(((AnimalNode)animalNode.node).findAction == ActionList.ACTION_EXTRA_UNKNOWN
										&& !((AnimalNode)animalNode.node).neg ) {
									//아직 액션을 못찾았다?
									//->그러면 공통액션이거나 이름만 부르거나 인식을 못한거임
									//공통액션일 경우를 찾아보자.
									//공통액션인 경우
									boolean bFind = true;
									int nearNodePos = Integer.MAX_VALUE;
									SearchTree findActionNode = null;
									
									lastSearchNode:
									for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
										SearchTree nowTreeNode = treeList.get(nowNodePos);
										if(nowTreeNode.flag == SearchTree.FLAG_ACTION) {
											//액션인노드를 찾아서 액션보이스 검색
											int animalPos = treeList.indexOf(animalNode);
											ArrayList<AnimalInfo.AnimalAction> actionList = ((AnimalNode)animalNode.node).animalInfo.getActionList();
											String searchedActionVoice = ((ActionNode)nowTreeNode.node).actionVoice;
											
											bFind = false;
											lastSearchActionList:
											for(AnimalInfo.AnimalAction action : actionList )  {
												ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
												for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
		//											Log.d("find multi action", actionVoice.getVoiceString() + "/" + searchedActionVoice );
													if( actionVoice.getVoiceString().equals( searchedActionVoice ) ) {
														//찾음
														//DEBUG_
														int nowNearNodePos = Math.abs(animalPos-nowNodePos);	// +에서 1, 이후 -1, -로 감, 앞에서 뒤로
														if( nowNearNodePos < nearNodePos ) {
															//현재값이 더 가까우면
															nearNodePos = nowNearNodePos;
															findActionNode = nowTreeNode;
															if(nowNearNodePos == 1)
																break lastSearchNode;
															else
																break lastSearchActionList;
														}
													}
												}
											}
										}
									}
									
									if(findActionNode != null) {
										//찾아져있으면
										((AnimalNode)animalNode.node).setFindAction(((ActionNode)findActionNode.node).actionId);
									} else {
										((AnimalNode)animalNode.node).setFindAction(ActionList.ACTION_EXTRA_UNKNOWN);
									}
								}
							}
							
							
							int animalSize = animalNodeList.size();
							int noActionCount = 0;
							searchList = new ArrayList<ActionInfo>();
							for(SearchTree animalNode : animalNodeList) {
								AnimalNode nowAnimalNode = ((AnimalNode)animalNode.node);
								if(!nowAnimalNode.neg) {
									searchList.add(new ActionInfo(nowAnimalNode.animalInfo.getId(), nowAnimalNode.findAction));
									if(nowAnimalNode.findAction == ActionList.ACTION_EXTRA_UNKNOWN) noActionCount++;	//액션못찾은 동물 갯수세서
								}
							}
							
							{
								String resultString = "";
								for(SearchTree animalNode : animalNodeList) {
									AnimalNode nowAnimalNode = ((AnimalNode)animalNode.node);
									resultString += ( nowAnimalNode.animalInfo.getName() + "/" );
								}
								Log.d("search result ", resultString);
							}
							
							Log.d("animals", "animals:" + animalSize + "/noActionAnimals:"+noActionCount);
							if(animalSize == noActionCount) {
								//전부 액션을 못찾은 동물일 경우
								if(bSearchListFirst) {
									//처음맞춘거 냅두기
									bSearchListFirst = false;
									searchListFirst = searchList;
									searchList = new ArrayList<ActionInfo>();
								}
								searchList.clear();
								Log.d("searches", "re search");
							} else {
								//하나라도찾았으면, 그냥 리턴
								Log.d("searches", "search done");
								return searchList;
							}
						}//endof 하나이상일때 최종로직
						
					}//end of each string
				}	
			}//end of (if seached animal)
		}//end of sentences
		
		Log.d("searches", "search with first done");
		return searchListFirst;
	}

	
	
	public static ArrayList<ActionInfo> searchAll1(ArrayList<String> sentences, ArrayList<AnimalInfo> arrAnimal) {
		ArrayList<String> negatives = RecognizedData.sharedRecognizedData().getNegativeConjunctions();
		
		ArrayList<ActionInfo> searchList = new ArrayList<ActionInfo>();
		ArrayList<ActionInfo> searchListFirst = new ArrayList<ActionInfo>();
		boolean bSearchListFirst = true;
		
		int sentencesSize = sentences.size();
		if(sentencesSize>5) sentencesSize = 5;
		else if(sentencesSize==0) return searchList;
		
		for(int sNum=0; sNum<sentencesSize; sNum++) {
			String str = MyUtils.convertNoSpace(sentences.get(sNum));
			Log.d("Search All", "nowSentence: "+str);
			
			int animalId = -1, actionId = ActionList.ACTION_EXTRA_UNKNOWN;
			searchedAnimalList = new ArrayList<SearchedAnimalInfo>();
			
			String seletedName = null;
			
			for(AnimalInfo animal : arrAnimal) {
				//모든 동물을 대상으로
				seletedName = null;
				final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
				for(String name : arrVoiceNames) {
					if(str.contains(name)) {
						if(str.equals(name)) {
							searchList = new ArrayList<ActionInfo>();
							searchList.add(new ActionInfo(animal.getId(), actionId));
							return searchList;
						}
						searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
					}
				}
			}
			
			if(searchedAnimalList.size() > 0) {
				Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
				{
					//찾은동물들 로그찍고
					String aniList = "" + searchedAnimalList.size() + ":";
					for(SearchedAnimalInfo info : searchedAnimalList) {
						aniList += (info.info.getName() +'/');
					}
					Log.d("Searched Animal List", aniList);
				}
				
				searchAnimal:
				for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) { 
					String[][] splits = getSplitedStrings(""+str, searchedAnimal.selectedName);
					searchSplit:
					if(splits!=null)
					for(String[] splString : splits) {
						//메인 루틴 시작
						//트리루트 만듦
						treeRoot = new SearchTree(new AnimalNode(searchedAnimal.info), SearchTree.FLAG_ANIMAL);
						if(!splString[0].equals(""))
							treeRoot.leftChild = new SearchTree(splString[0], SearchTree.FLAG_UNCONFIRMED);
						if(!splString[1].equals(""))
							treeRoot.rightChild = new SearchTree(splString[1], SearchTree.FLAG_UNCONFIRMED);
						
						//동물들부터 다 찾아서 트리에 찰드 추가
						searchAnimalsAddTree(treeRoot.leftChild);
						searchAnimalsAddTree(treeRoot.rightChild);
						
						//찾은 동물들 중 Negative 있는지 검사
						ArrayList<SearchTree> negSearchTreeList = SearchTree.getNodeListByInOrder(treeRoot);
						for(int n=0; n<negSearchTreeList.size()-1; n++) {
							SearchTree nowNode = negSearchTreeList.get(n);
							if(nowNode.flag == SearchTree.FLAG_ANIMAL) {
								SearchTree nextNode = negSearchTreeList.get(n+1);
								if(nextNode.flag == SearchTree.FLAG_UNCONFIRMED) {
									String nextString = ((String)nextNode.node);
									boolean bNegative = false;
									for(String neg : negatives) {
										if(nextString.startsWith(neg)) {
											bNegative = true;
											break;
										}
									}
									if(bNegative) {
										nowNode.flag = SearchTree.FLAG_ANIMAL_NEG;
										((AnimalNode)nowNode.node).neg = true;
									}
								}
							}
						}
						
						//찾아진 동물들 트리 리스트를 받아와서 액션을 찾아보자
						ArrayList<SearchTree> animalNodeList = SearchTree.getAnimalNodeListByInOrder(treeRoot);
						int animalListSize = animalNodeList.size();
						{
							String aniList = "";
							for(SearchTree info : animalNodeList) {
								aniList += (((AnimalNode)info.node).animalInfo.getName() +'/');
							}
							Log.d("now Animal List", aniList);
						}
						searchAnimalAction:for(int i=0; i<animalListSize; i++) {
							//동물 하나씩마다 액션을 찾는데...
							SearchTree nowAnimalNode = animalNodeList.get(i);
							AnimalInfo nowAnimalInfo = ((AnimalNode)nowAnimalNode.node).animalInfo;
							if(((AnimalNode)nowAnimalNode.node).neg) continue;
							
							AnimalInfo.AnimalAction selectedAction = null;
							String selectedVoice = null;
							SearchTree selectedTreeNode = null;
							boolean selectedFindLeft = true;
							
							ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
							int treeSize = treeList.size();
							int animalPos = treeList.indexOf(nowAnimalNode);
							Log.d("search Voice Recog", "now Animal Pos : "+animalPos);
							
							boolean bFindLeft = true;
							int maxLen = -1, maxNum = -1, nearLeftPos = -1, nearRightPos = Integer.MAX_VALUE,
									nearNodePos = Integer.MAX_VALUE, findPos = Integer.MAX_VALUE;
							searchNodeTree: for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
								SearchTree nowNode = treeList.get(nowNodePos);
								
								if(nowNode.flag == SearchTree.FLAG_UNCONFIRMED) {
									//미확인일경우에서 찾는다
									String nowSplString = (String)nowNode.node;
									ArrayList<AnimalInfo.AnimalAction> actionList = nowAnimalInfo.getActionList();
									boolean bFindFirst = true;
									nearNodePos = Integer.MAX_VALUE;
									
									if(animalPos > nowNodePos) {	//동물왼쪽
										bFindLeft = true;
									} else if(animalPos < nowNodePos) {	//동물 오른쪽
										bFindLeft = false;
									}
									
									for(AnimalInfo.AnimalAction action : actionList) {
										ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
										for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
											
											
											String voice = actionVoice.getVoiceString();
											/*if(voice.equals(nowSplString)) {
												//같으면 node자체를 바로 액션으로.
												selectedTreeNode = nowNode;
												selectedAction = action;
												//Unconfirm->action으로 flag변환
												selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), voice),
														SearchTree.FLAG_ACTION);
												//animal node에 액션지정
												((AnimalNode)nowAnimalNode.node).setFindAction(selectedAction.getActionId());
												continue searchAnimalAction;
											}*/
											
											int nowPos = -1;
											if( (nowPos=nowSplString.indexOf(voice)) != -1) {
												if(bFindFirst) {
													bFindFirst = false;
													
													int findNearNodePos = Math.abs(animalPos - findPos);	//동물위치와 찾은것 같의 거리
													int nowNearNodePos = Math.abs(animalPos - nowNodePos);
													
													if( nowNearNodePos < findNearNodePos ) {
														//더 가까우면
														findPos = nowNodePos;
													} else if (nowNearNodePos == findNearNodePos) {
														//같아졌으면
													} else {
														//더 멀어지면
														break searchNodeTree;
													}
													
													/*//nodePos검사
													bFindFirst = false;
													// +에서 1, 이후 -1, -로 감, 앞에서 뒤로
													int nowNearNodePos = animalPos-nowNodePos;
													int nowNearAbsNodePos = Math.abs(nowNearNodePos);	//현재 노드의 상대위치(거리)
													int nowNearFindNodePos = Math.abs(animalPos - findPos);	//마지막으로 찾은 노드의 상대위치
													if( nowNearAbsNodePos < nowNearFindNodePos ) {
														//현재값이 마지막으로 찾은 노드보다 더 가까우면
														nearNodePos = nowNearFindNodePos;
													} else if ( nowNearAbsNodePos == nowNearFindNodePos ) {
														//둘이 가까움이 같으면
														//continue;
//														break searchNodeTree;	//어차피 점점 더 멀어지므로 오른쪽인데,
																//둘이 가까움이 같으면 왼쪽X 오른쪽! 우선으로 할것임.
													} else {
														//현재값이 더 멀면
														//continue;
														break searchNodeTree;	//어차피 점점 더 멀어지므로 한번 멀어지면 끝임
														
													}*/
												}
												
												findPos = nowNodePos;
												
												//nodePos -> stringPos비교
												//동물에 따른 보이스 최장메치 찾기
												int nowLen = voice.length();
												int nowNum = action.getActionCount();
												
												if(bFindLeft) {
													//왼쪽 -> pos클수록 가까움
													nowPos = nowPos+voice.length();	//스트링의 끝 pos를 지정
													if(nowPos > nearLeftPos) {
														nearLeftPos = nowPos;
														maxLen = nowLen;
														nowNum = maxNum;
														selectedTreeNode = nowNode;
														selectedAction = action;
														selectedVoice = actionVoice.getVoiceString();
														selectedFindLeft = bFindLeft;
													} else if (nowPos == nearLeftPos) {
														//pos같으면 -> length비교
														if(nowLen > maxLen) {
															maxLen = nowLen;
															nowNum = maxNum;
															selectedTreeNode = nowNode;
															selectedAction = action;
															selectedVoice = actionVoice.getVoiceString();
															selectedFindLeft = bFindLeft;
														} else if (nowLen == maxLen) {
															//같은 최장길이일시 가르친 횟수로
															if(nowNum > maxNum) {
																nowNum = maxNum;
																selectedTreeNode = nowNode;
																selectedAction = action;
																selectedVoice = actionVoice.getVoiceString();
																selectedFindLeft = bFindLeft;
															}
														}
													}
												} else {
													//오른쪽 -> pos작을수록 가까움
													if(nowPos < nearRightPos) {
														nearRightPos = nowPos;
														maxLen = nowLen;
														nowNum = maxNum;
														selectedTreeNode = nowNode;
														selectedAction = action;
														selectedVoice = actionVoice.getVoiceString();
														selectedFindLeft = bFindLeft;
													} else if (nowPos == nearRightPos) {
														//pos같으면 -> length비교
														if(nowLen > maxLen) {
															maxLen = nowLen;
															nowNum = maxNum;
															selectedTreeNode = nowNode;
															selectedAction = action;
															selectedVoice = actionVoice.getVoiceString();
															selectedFindLeft = bFindLeft;
														} else if (nowLen == maxLen) {
															//같은 최장길이일시 가르친 횟수로
															if(nowNum > maxNum) {
																nowNum = maxNum;
																selectedTreeNode = nowNode;
																selectedAction = action;
																selectedVoice = actionVoice.getVoiceString();
																selectedFindLeft = bFindLeft;
															}
														}
													}
												}
												
											}
										}
									}
									
								}
							}//end of Label(for) searchLabelTree
							
							//찾은거 가지고 액션지정
							if(selectedAction != null) {
								String unconfirmString = (String)selectedTreeNode.node;
								String[] splitUnconfirm = null;
								String temp = "None";
								
								boolean bNega = false;
								
								if(selectedFindLeft) {	//왼쪽에서 찾았으면
									splitUnconfirm = getSplitedStringOnce(unconfirmString, selectedVoice, false);	//오른쪽에 자르고
								} else {		//오른쪽에서 찾았으면
									splitUnconfirm = getSplitedStringOnce(unconfirmString, selectedVoice, true);	//왼쪽에서자른다
								}
								
								if(!splitUnconfirm[0].equals(""))
									selectedTreeNode.addChild(splitUnconfirm[0], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_LEFT);
								if(!splitUnconfirm[1].equals("")) {
									selectedTreeNode.addChild(splitUnconfirm[1], SearchTree.FLAG_UNCONFIRMED, SearchTree.CHILDPOS_RIGHT);
								
									for(String negative : negatives) {
										if(splitUnconfirm[1].startsWith(negative)) {	//액션오른쪽이 네거티브면
											bNega = true;
											temp = negative;
											break;
										}
									}
								}
								
								if(bNega) {
									//액션+네거티브
									Log.d("neg found", splitUnconfirm[1] + ":" + temp);
									selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), selectedVoice), 
											SearchTree.FLAG_ACTION_NEG);
									((AnimalNode)nowAnimalNode.node).neg = true;
								} else {
									//부모노드는 액션으로 변경
									selectedTreeNode.setData(new ActionNode(selectedAction.getActionId(), selectedVoice), 
											SearchTree.FLAG_ACTION);
									
								}
								Log.d("Action Mactch", ((AnimalNode)nowAnimalNode.node).animalInfo.getName() + ":" + selectedAction.getActionId());
								
								//animal node에 액션지정
								((AnimalNode)nowAnimalNode.node).setFindAction(selectedAction.getActionId());
							}
							
						} //end of Label(for) searchAnimalAction
						
						
						
						//최종정리
						ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
						int treeSize = treeList.size();
						
						if(animalNodeList.size() == 1) {
							//동물 하나인거, 하나인데 액션을 못찾을린 없는거니까,
							//하나일경우엔 복합액션(연속액션)을 찾자
							AnimalNode animalNode = (AnimalNode)animalNodeList.get(0).node;
							if(animalNode.findAction == ActionList.ACTION_EXTRA_UNKNOWN && !animalNode.neg) {
								//먼저 액션못찾은 동물 하나만 있는거면
								if(bSearchListFirst) {
									//처음맞춘거 냅두기
									bSearchListFirst = false;
									searchListFirst = new ArrayList<ActionInfo>();
									searchListFirst.add(new ActionInfo(animalNode.animalInfo.getId(), animalNode.findAction));
								}
							} else {
								//액션찾은동물이라면 더있는지 찾아보자
								ArrayList<Integer> actionIdList = new ArrayList<Integer>();
								
								if(animalNodeList.get(0).flag == SearchTree.FLAG_ANIMAL && !animalNode.neg) {
									actionIdList.add(Integer.valueOf(animalNode.findAction));
								
									for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
										SearchTree nowTreeNode = treeList.get(nowNodePos);
										if(nowTreeNode.flag == SearchTree.FLAG_UNCONFIRMED) {
											//미확인에서 액션들을 찾는다
											ArrayList<AnimalInfo.AnimalAction> actionList = animalNode.animalInfo.getActionList();
											for(AnimalInfo.AnimalAction action : actionList )  {
												ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
												for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
													if( ((String)nowTreeNode.node).contains(actionVoice.getVoiceString()) ) {
														//보이스스트링 포함하고있으면
														Integer nowActionId = Integer.valueOf(action.getActionId());
														if(!actionIdList.contains(nowActionId)) {
															actionIdList.add(nowActionId);
														}
														break;
													}
												}
											}
										}
									}
								}
								
								//액션인포리스트만들어서 리턴
								searchList = new ArrayList<ActionInfo>();
								for(Integer nowActionId : actionIdList) {
									searchList.add(new ActionInfo(animalNode.animalInfo.getId(), nowActionId.intValue()));
								}
								
								Log.d("searches", "search one aniaml done");
								return searchList;
							}
						} else {
							//하나이상일때는
							for(SearchTree animalNode : animalNodeList) {
								if(((AnimalNode)animalNode.node).findAction == ActionList.ACTION_EXTRA_UNKNOWN
										&& !((AnimalNode)animalNode.node).neg ) {
									//아직 액션을 못찾았다?
									//->그러면 공통액션이거나 이름만 부르거나 인식을 못한거임
									//공통액션일 경우를 찾아보자.
									//공통액션인 경우
									boolean bFind = true;
									int nearNodePos = Integer.MAX_VALUE;
									SearchTree findActionNode = null;
									
									lastSearchNode:
									for(int nowNodePos=0; nowNodePos<treeSize; nowNodePos++) {
										SearchTree nowTreeNode = treeList.get(nowNodePos);
										if(nowTreeNode.flag == SearchTree.FLAG_ACTION) {
											//액션인노드를 찾아서 액션보이스 검색
											int animalPos = treeList.indexOf(animalNode);
											ArrayList<AnimalInfo.AnimalAction> actionList = ((AnimalNode)animalNode.node).animalInfo.getActionList();
											String searchedActionVoice = ((ActionNode)nowTreeNode.node).actionVoice;
											
											bFind = false;
											lastSearchActionList:
											for(AnimalInfo.AnimalAction action : actionList )  {
												ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
												for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
		//											Log.d("find multi action", actionVoice.getVoiceString() + "/" + searchedActionVoice );
													if( actionVoice.getVoiceString().equals( searchedActionVoice ) ) {
														//찾음
														//DEBUG_
														int nowNearNodePos = Math.abs(animalPos-nowNodePos);	// +에서 1, 이후 -1, -로 감, 앞에서 뒤로
														if( nowNearNodePos < nearNodePos ) {
															//현재값이 더 가까우면
															nearNodePos = nowNearNodePos;
															findActionNode = nowTreeNode;
															if(nowNearNodePos == 1)
																break lastSearchNode;
															else
																break lastSearchActionList;
														}
													}
												}
											}
										}
									}
									
									if(findActionNode != null) {
										//찾아져있으면
										((AnimalNode)animalNode.node).setFindAction(((ActionNode)findActionNode.node).actionId);
									} else {
										((AnimalNode)animalNode.node).setFindAction(ActionList.ACTION_EXTRA_UNKNOWN);
									}
								}
							}
							
							
							int animalSize = animalNodeList.size();
							int noActionCount = 0;
							searchList = new ArrayList<ActionInfo>();
							for(SearchTree animalNode : animalNodeList) {
								AnimalNode nowAnimalNode = ((AnimalNode)animalNode.node);
								if(!nowAnimalNode.neg) {
									searchList.add(new ActionInfo(nowAnimalNode.animalInfo.getId(), nowAnimalNode.findAction));
									if(nowAnimalNode.findAction == ActionList.ACTION_EXTRA_UNKNOWN) noActionCount++;	//액션못찾은 동물 갯수세서
								}
							}
							
							{
								String resultString = "";
								for(SearchTree animalNode : animalNodeList) {
									AnimalNode nowAnimalNode = ((AnimalNode)animalNode.node);
									resultString += ( nowAnimalNode.animalInfo.getName() + "/" );
								}
								Log.d("search result ", resultString);
							}
							
							Log.d("animals", "animals:" + animalSize + "/noActionAnimals:"+noActionCount);
							if(animalSize == noActionCount) {
								//전부 액션을 못찾은 동물일 경우
								if(bSearchListFirst) {
									//처음맞춘거 냅두기
									bSearchListFirst = false;
									searchListFirst = searchList;
									searchList = new ArrayList<ActionInfo>();
								}
								searchList.clear();
								Log.d("searches", "re search");
							} else {
								//하나라도찾았으면, 그냥 리턴
								Log.d("searches", "search done");
								return searchList;
							}
						}//endof 하나이상일때 최종로직
						
					}//end of each string
				}	
			}//end of (if seached animal)
		}//end of sentences
		
		Log.d("searches", "search with first done");
		return searchListFirst;
	}
	
	private static ArrayList<SearchedAnimalInfo> searchedAnimalList;
	public static ArrayList<ActionInfo> search(String sentence, ArrayList<AnimalInfo> arrAnimal) {
		ArrayList<ActionInfo> searchList = new ArrayList<ActionInfo>();
		String str = MyUtils.convertNoSpace(sentence);
		
		int animalId = -1, actionId = ActionList.ACTION_EXTRA_UNKNOWN;
		searchedAnimalList = new ArrayList<SearchedAnimalInfo>();
		
		String seletedName = null;
		
		for(AnimalInfo animal : arrAnimal) {
			//모든 동물을 대상으로
			seletedName = null;
			final ArrayList<String> arrVoiceNames = animal.getVoiceNames();
			for(String name : arrVoiceNames) {
				if(str.contains(name)) {
					if(str.equals(name)) {
						searchList = new ArrayList<ActionInfo>();
						searchList.add(new ActionInfo(animal.getId(), actionId));
						return searchList;
					}
					searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
				}
			}
		}
		
		if(searchedAnimalList.size() > 0) {
			Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
			
			searchAnimal:
			for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) { 
				String[][] splits = getSplitedStrings(""+str, searchedAnimal.selectedName);
				searchSplit:
				for(String[] splString : splits) {
					//메인 루틴 시작
					//트리루트 만듦
					treeRoot = new SearchTree(new AnimalNode(searchedAnimal.info), SearchTree.FLAG_ANIMAL);
					treeRoot.leftChild = new SearchTree(splString[0], SearchTree.FLAG_UNCONFIRMED);
					treeRoot.rightChild = new SearchTree(splString[1], SearchTree.FLAG_UNCONFIRMED);
					
					//동물들부터 다 찾아서 트리에 찰드 추가
					searchAnimalsAddTree(treeRoot.leftChild);
					searchAnimalsAddTree(treeRoot.rightChild);
					
					//리스트로 받아와서 액션을 찾아보자
					ArrayList<SearchTree> treeList = SearchTree.getNodeListByInOrder(treeRoot);
					int treeSize = treeList.size();
					
					boolean bFindRight = true;	//오른쪽에서 액션찾는지 왼쪽에서 찾는지
					AnimalNode selectedAnimalNode = null;
					searchTree:
					for(int i=0; i<treeSize; i++) {
						SearchTree nowNode = treeList.get(i);
						switch(nowNode.flag) {
						case SearchTree.FLAG_ANIMAL:
							selectedAnimalNode = (AnimalNode)nowNode.node;
							if(selectedAnimalNode.findAction != -1) {
								//animal이 action을 찾앗으면 넘어간다.
								selectedAnimalNode = null;
							} else {
								bFindRight = true;
							}
							break;
						case SearchTree.FLAG_UNCONFIRMED:
							boolean bExistAnimal = true;
							if(selectedAnimalNode == null) {
								bExistAnimal = false;
								for(int j=i+1; j<treeSize; j++) {
									SearchTree searchNode = treeList.get(j);
									if(searchNode.flag == SearchTree.FLAG_ANIMAL) {
										//앞에서 선택된 애니멀이 없으면 뒤에서 가장 가까운 애니멀을 찾는다.
										bFindRight = true;
										bExistAnimal = true;
										selectedAnimalNode = (AnimalNode)searchNode.node;
										break;
									}
								}
								//뒤에 동물이 아얘 없으면 -> 끝인데...
								if(!bExistAnimal)
									break searchTree;
							}
							if(bExistAnimal) {
								//현재선택되있는 동물의 액션을 찾자
								
								String nowSplString = (String)nowNode.node;
								ArrayList<AnimalInfo.AnimalAction> actionList = selectedAnimalNode.animalInfo.getActionList();
								
								int maxLen = -1, maxNum = -1, nearPos;
								AnimalInfo.AnimalAction selectedAction = null;
								
								for(AnimalInfo.AnimalAction action : actionList) {
									ArrayList<AnimalInfo.AnimalAction.ActionVoice> voiceList = action.getVoiceList();
									for(AnimalInfo.AnimalAction.ActionVoice actionVoice : voiceList) {
										String voice = actionVoice.getVoiceString();
										int nowPos = -1;
										if( (nowPos=nowSplString.indexOf(voice)) != -1) {
											//동물에 따른 보이스 최장메치 찾기
											int nowLen = voice.length();
											int nowNum = action.getActionCount();
											
											if(nowLen > maxLen) {
												maxLen = nowLen;
												selectedAction = action;
											} else if (nowLen == maxLen) {
												//같은 최장길이일시 가르친 횟수로
												if(nowNum > maxNum) {
													nowNum = maxNum;
													selectedAction = action;
												}
											}
										}
									}
								}
								//액션을 찾았으면
								if(selectedAction != null) {
									selectedAnimalNode.setFindAction(selectedAction.getActionId());
									selectedAnimalNode = null;
								}
							}
							break;
						}
					}
				}
			}
			
//			treeRoot = new SearchTree(""+str, SearchTree.FLAG_UNCONFIRMED);
		}
		
		
		return searchList;
	}
	
	//다중검색하자(뽀삐야 밥먹어 애봉아 똥싸)
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
					if(str.equals(name)) return new ActionInfo(animal.getId(), actionId);
					searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
				}
			}
		}
		
		//동물이 하나라도 검색됬으면
		boolean bOnceSearch = false;	//액션있는동물 하나라도있는지?
		if(searchedAnimalList.size() > 0) {
//				ArrayList<SearchedActionInfo> searchedActionInfo = new ArrayList<SearchedActionInfo>();
//			SearchedActionInfo searchedActionInfo;
			int maxLen = -1;
			int maxLeftLen = -1, maxRightLen = -1;
			Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
			SearchTree thisNode = null;
			
			searchAnimal:
			for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) {
				//서치된 동물을 기준으로 액션이 있는지 찾아본다
				String string = ""+str;
				selectedAction = null;
				SearchTree tree = new SearchTree(new AnimalNode(searchedAnimal.info), SearchTree.FLAG_ANIMAL);
				thisNode = tree;
				
				String[][] splits = getSplitedStrings(string, searchedAnimal.selectedName);
				if(splits == null) continue;
				
				searchSplit:
				for(String[] splString : splits) {
					ArrayList<AnimalInfo.AnimalAction> arrAction = searchedAnimal.info.getActionList();
					int nearFindPos = -1;
					int leftPos = -1, rightPos = -1;
					boolean bFindRight = false, bFindLeft = false;
//					SearchedActionInfo leftAction = null, rightAction = null;
					AnimalInfo.AnimalAction leftAction = null, rightAction = null;
					String leftVoice, rightVoice;
					
					//splits node로
//					tree.leftChild = new SearchTree(splString[0], SearchTree.FLAG_UNCONFIRMED);
//					tree.rightChild = new SearchTree(splString[1], SearchTree.FLAG_UNCONFIRMED);
					
					//각 스플리트스트링(각 동물 기준)마다 액션 하나씩 검사
					searchAction:
					for(AnimalInfo.AnimalAction action : arrAction) {
						final ArrayList<AnimalInfo.AnimalAction.ActionVoice> arrActionVoice = action.getVoiceList();
						boolean bContain = false;
						//가장 긴 보이스 매치
						matchVoice:
						for (AnimalInfo.AnimalAction.ActionVoice actionVoice : arrActionVoice) {
							String voice = actionVoice.getVoiceString();
							int findPos = -1;

							if ((findPos = splString[1].indexOf(voice)) != -1) {
								// 기준 오른쪽 발견 - 보통 동사가 뒤에있으므로
								bContain = true;
								bFindRight = true;
								if (findPos <= 1) {
									// 동물이름 바로 오른쪽에서 찾은거임. -> 바로 수행되는거지 이러면
									thisNode.rightChild.rightChild = new SearchTree(
											splString[1].substring(findPos + voice.length()), SearchTree.FLAG_UNCONFIRMED);
								}
								int nowLen = voice.length();

								// Pos->Len->Count 순으로 찾자
								if (rightPos > findPos) { // 더 가까울수록
									rightPos = findPos;
									rightAction = action;
									rightVoice = voice;
									maxRightLen = nowLen;
								} else if (rightPos == findPos) {
									if (nowLen > maxRightLen) {
										maxRightLen = nowLen;
										rightAction = action;
										rightVoice = voice;
									} else if (nowLen == maxRightLen) {
										if (action.getActionCount() > rightAction
												.getActionCount()) {
											rightAction = action;
											rightVoice = voice;
										}
									}
								}

							}
							if ((findPos = splString[0].indexOf(voice)) != -1) {
								// 기준 왼쪽 발견
								bContain = true;
								bFindLeft = true;
								int nowLen = voice.length();

								// Pos->Len->Count 순으로 찾자
								if (leftPos > findPos) { // 더 가까울수록
									leftPos = findPos;
									leftAction = action;
									leftVoice = voice;
									maxRightLen = nowLen;
								} else if (leftPos == findPos) {
									if (nowLen > maxLeftLen) {
										maxLeftLen = nowLen;
										leftAction = action;
										leftPos = findPos;
										leftVoice = voice;
									} else if (nowLen == maxLeftLen) {
										if (action.getActionCount() > leftAction
												.getActionCount()) {
											leftAction = action;
											leftPos = findPos;
											leftVoice = voice;

										}
									}
								}
							}
						}
					}
					//액션 검사 끝
					if(bFindLeft && bFindRight) {
						
					} else if(bFindRight) {
						
					} else if(bFindLeft) {
						
					}
				}
				
				if(selectedAction != null) {
					if(!bOnceSearch)
						bOnceSearch = true;
					animalId = searchedAnimal.info.getId();
					actionId = selectedAction.getActionId();
					break;
					//selectedAction이 있으면 애니멀-액션 최장매치 된거임.
					//없으면 다음 최장매치된 애니멀부터 액션을 매치시켜 찾아낸다.
				}
			}
			
			if(!bOnceSearch) {
				//하나라도 서치 안되면 액션을 몾찾은거임 > 서치된 리스트중 제일 앞에꺼
				animalId = searchedAnimalList.get(0).info.getId();
			}
		}
		
		return new ActionInfo(animalId, actionId);
	}
	
	//동물/액션 통합 검색, 중의성 추가한 패턴매칭
	public static ActionInfo patternMatchSecond(String sentence, ArrayList<AnimalInfo> arrAnimal) {
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
					if(str.equals(name)) return new ActionInfo(animal.getId(), actionId);
					searchedAnimalList.add(new SearchedAnimalInfo(animal, name));
				}
			}
		}
		
		//동물이 하나라도 검색됬으면
		boolean bOnceSearch = false;	//액션있는동물 하나라도있는지?
		if(searchedAnimalList.size() > 0) {
//				ArrayList<SearchedActionInfo> searchedActionInfo = new ArrayList<SearchedActionInfo>();
			SearchedActionInfo searchedActionInfo;
			int maxLen = -1;
			Collections.sort(searchedAnimalList); //내림차순 정렬 (1.최장매치/2.가르친횟수 기준)
			
			for( SearchedAnimalInfo searchedAnimal : searchedAnimalList ) {
				//서치된 동물을 기준으로 액션이 있는지 찾아본다
				String string = ""+str;
				selectedAction = null;
				
				String[][] splits = getSplitedStrings(string, searchedAnimal.selectedName);
				if(splits == null) continue;
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
					if(!bOnceSearch)
						bOnceSearch = true;
					animalId = searchedAnimal.info.getId();
					actionId = selectedAction.getActionId();
					break;
					//selectedAction이 있으면 애니멀-액션 최장매치 된거임.
					//없으면 다음 최장매치된 애니멀부터 액션을 매치시켜 찾아낸다.
				}
			}
			
			if(!bOnceSearch) {
				//하나라도 서치 안되면 액션을 몾찾은거임 > 서치된 리스트중 제일 앞에꺼
				animalId = searchedAnimalList.get(0).info.getId();
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
	
	private static String[][] getSplitedStrings(String str, String rex) {
		String[] spl = str.split(rex);
		if(str.endsWith(rex)){
			String[] spl2 = new String[spl.length+1];
			for(int i=0; i<spl.length; i++) {
				spl2[i] = spl[i];
			}
			spl2[spl.length] = "";
			spl = spl2;
		}
		int splSize = spl.length - 1;
		if(splSize <= 0) return null;
		
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
	
	private static String[] getSplitedStringOnce(String str, String rex, boolean byLeft) {
		if(str.equals(rex)) {
			String[] ss = new String[2];
			ss[0] = "";
			ss[1] = "";
			return ss;
		}
		
		String[] spl = str.split(rex);
		if(str.endsWith(rex)){
			String[] spl2 = new String[spl.length+1];
			for(int i=0; i<spl.length; i++) {
				spl2[i] = spl[i];
			}
			spl2[spl.length] = "";
			spl = spl2;
		}
		int splSize = spl.length - 1;
		if(splSize <= 0) return null;
		
		String[] splResultOnce = new String[2];
		int capa = str.length();
		
		StringBuilder before = new StringBuilder(capa);
		StringBuilder after = new StringBuilder(capa);
		
		int i = -1;
		if(byLeft) i = 0;		//left
		else i = splSize -1;	//right

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
		splResultOnce[0] = before.toString();
		splResultOnce[1] = after.toString();

//		for (int i=0; i<splResult.length; i++) {
//			Log.d("String split", i + " : " + splResult[i][0] + " / " + splResult[i][1]);
//		}
		return splResultOnce;
	}
	
}
