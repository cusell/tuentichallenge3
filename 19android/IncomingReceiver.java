package com.tuenti.signal;

import android.annotation.TargetApi;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;


/*
 * The following XML has to be added to AndroidManifest.xml
<receiver android:name=".IncomingReceiver" android:enabled="true">
  <intent-filter>
    <action android:name="com.tuenti.signal"></action>
  </intent-filter>
</receiver>
 */

public class IncomingReceiver extends BroadcastReceiver {
  @Override
  public void onReceive(Context context, Intent intent) {
    
    Uri CODE_PROVIDER = Uri.parse("content://com.tuenti.lostchallenge.datamodel.provider.ContestProvider/contest");
    
    Bundle extras = intent.getExtras();
    byte[] arrayB = extras.getByteArray("SIGNAL_INFO");
    int arraySize = arrayB.length;
    //To get the images, print arrayB content.
    //Save some of the 5 cyclical shifts and get the .jpg image.
    
    String queryArg[] = new String[1];
    //Run 5 times for each of the keys hidden in the images
    queryArg[0] = new String("158");
    Cursor cur = getContentResolver().
      query(CODE_PROVIDER, null, "key = ?", queryArg, null);

    //Print query results in logcat.
    if (cur.moveToFirst()){
      do{
        String value = cur.getString(cur.getColumnIndex("value"));
        String id = cur.getString(cur.getColumnIndex("_id"));
        String key = cur.getString(cur.getColumnIndex("key"));
        Log.d("value", value);
        Log.d("id", id);
        Log.d("key", key);
      }while(cur.moveToNext());
    }
    cur.close()
  }
}