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
package org.cocos2dx.cpp;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHandler;

import android.content.Context;
import android.os.Environment;
import android.util.Log;



public class AppActivity extends Cocos2dxActivity{
	
	static File dir;
	static String path;
	static String exDir;
	static String FileName = "/libabc.so";
	@Override
	protected void onLoadNativeLibraries() {
		// TODO Auto-generated method stub
		super.onLoadNativeLibraries();
		
		dir = getDir("libs", Context.MODE_PRIVATE);

		String newPath = dir + FileName;
		Log.e("main", "11111" +newPath);
		File soFile = new File(newPath);
		if (soFile.exists()) {
			try {
				System.load(soFile.getAbsolutePath());
			} catch (Exception e) {
			}
		}
	}

	public static String GetApkPath (){
		 exDir =Environment.getExternalStorageDirectory().getPath()+"/test";
		 File destDir = new File(exDir);
		 Log.e("installApk1", destDir.getAbsolutePath());
		  if (!destDir.exists()) {
			  destDir.mkdirs();
			  return destDir.getAbsolutePath();
		  }else{
			  return destDir.getAbsolutePath();
		  }

	}
	
	public static void load() {
		String oldPath = exDir + FileName;
		String newPath = dir + FileName;
		File soFile = new File(newPath);
		copyFile(oldPath, newPath);
        try {
            System.load(soFile.getAbsolutePath());
        } catch (Exception e) {
        }
    }
	
	public static void copyFile(String oldPath, String newPath) {   
	       try {   
	           int bytesum = 0;   
	           int byteread = 0;   
	           File oldfile = new File(oldPath);   
	           if (oldfile.exists()) { //文件存在时   
	               InputStream inStream = new FileInputStream(oldPath); //读入原文件   
	               FileOutputStream fs = new FileOutputStream(newPath);   
	               byte[] buffer = new byte[1024];   
	               int length;   
	               while ( (byteread = inStream.read(buffer)) != -1) {   
	                   bytesum += byteread; //字节数 文件大小   
	                   fs.write(buffer, 0, byteread);   
	               }   
	               System.out.println(bytesum); 
	               inStream.close();   
	           }   
	       }   
	       catch (Exception e) {   
	           System.out.println("复制单个文件操作出错");   
	           e.printStackTrace();   
	  
	       }   
	  
	   }   

}
