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
package com.hardworking.testjsbsample;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import com.easyjsb.classes.AndroidJSBHelper;
import com.easyndk.classes.AndroidNDKHelper;

import android.os.Bundle;
import android.util.Log;

public class EasyJsbSample extends Cocos2dxActivity{
	private String TAG = "[TestEasyJSB]";
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
        
        AndroidNDKHelper.SetNDKReciever(this);
	}
	
    public void helloNative(JSONObject prms){
		Log.i(TAG, TAG+" this is method: helloNative in native Android, prms: "+prms.toString());
		
		final JSONObject obj = new JSONObject();
		try {
			obj.put("message","I am message from native Android");
		} catch (JSONException e) {
			e.printStackTrace();
		}
		
		this.runOnGLThread(new Runnable(){
			@Override
			public void run()
			{
                //				AndroidNDKHelper.SendMessageWithParameters("helloCpp", obj);
				AndroidJSBHelper.SendMessageToJS("helloJS", obj);
			}
		});
	}
    
    static {
        System.loadLibrary("cocos2djs");
    }
}
