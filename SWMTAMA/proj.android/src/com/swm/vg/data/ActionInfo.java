package com.swm.vg.data;

public class ActionInfo {
	final int animalId;
	final int actionId;
	
	public ActionInfo(int animalId, int actionId) {
		this.animalId = animalId;
		this.actionId = actionId;
	}
	
	public int getAnimalId() { return animalId; }
	public int getActionId() { return actionId; }
	
}
