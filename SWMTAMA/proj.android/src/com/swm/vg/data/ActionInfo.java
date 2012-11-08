package com.swm.vg.data;

public class ActionInfo {
	public int animalId;
	public int actionId;
	
	public ActionInfo() {
		this(-1, -1);
	}
	
	public ActionInfo(int animalId, int actionId) {
		this.animalId = animalId;
		this.actionId = actionId;
	}
	
	public void init() {
		animalId = -1;
		actionId = -1;
	}
	
	public ActionInfo set(int animalId, int actionId) {
		this.animalId = animalId;
		this.actionId = actionId;
		return this;
	}
	
}
