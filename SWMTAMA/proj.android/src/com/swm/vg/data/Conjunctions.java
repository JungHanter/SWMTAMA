package com.swm.vg.data;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

public class Conjunctions {
	private final ArrayList<String> negativeConjunctions;
	private final ArrayList<String> andConjunctions;
	
	public Conjunctions() {
		negativeConjunctions = new ArrayList<String>(50);
		andConjunctions = new ArrayList<String>(30);
	}
	
	public boolean loadConjunctions(Context ctx) {
		BufferedReader br = null;
		try {
			br = new BufferedReader(new InputStreamReader(ctx.getAssets().open("negativeconjunction.txt", AssetManager.ACCESS_BUFFER), "utf-8"));	
			String line = null;
			
			while( (line=br.readLine()) != null ) {
				if(line.startsWith("#")) continue;	//주석라인
				negativeConjunctions.add(line);
//				Log.d("neg coj read", line);
			}
			
			br.close();
		} catch(Exception e) {
			e.printStackTrace();
			try {
				br.close();
			}catch(Exception e2) {}
			return false;
		}
		
		BufferedReader br2 = null;
		try {
			br2 = new BufferedReader(new InputStreamReader(ctx.getAssets().open("positiveconjunction.txt", AssetManager.ACCESS_BUFFER), "utf-8"));
			String line = null;
			
			while( (line=br2.readLine()) != null ) {
				if(line.startsWith("#")) continue;	//주석라인
				andConjunctions.add(line);
			}
			
			br2.close();
		} catch(Exception e) {
			e.printStackTrace();
			try {
				br2.close();
			}catch(Exception e2) {}
			return false;
		}
		
		return true;
	}
	
	public ArrayList<String> getNegatives() {
		return negativeConjunctions;
	}
	
	public ArrayList<String> getAnds() {
		return andConjunctions;
	}
}
