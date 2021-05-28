package com.blogspot.prajbtc.smartcity;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class MainActivity extends AppCompatActivity {

    DatabaseReference myRef;
    TextView marketTv;
    int in, out, stay;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        marketTv=findViewById(R.id.market);
        myRef=FirebaseDatabase.getInstance().getReference("City");
        myRef.addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
                railMon(snapshot);
            }

            @Override
            public void onChildChanged(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
                railMon(snapshot);
            }

            @Override
            public void onChildRemoved(@NonNull DataSnapshot snapshot) {
                railMon(snapshot);
            }

            @Override
            public void onChildMoved(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }


    void railMon(DataSnapshot snapshot){

        String key=snapshot.getKey().toString();
        String data=snapshot.getValue().toString();

        if(key.equals("Light")){
            if(data.equals("1")){
                ((ImageView)findViewById(R.id.lightIv)).setImageDrawable(getResources().getDrawable(R.drawable.light_on));
            }else{
                ((ImageView)findViewById(R.id.lightIv)).setImageDrawable(getResources().getDrawable(R.drawable.light_off));
            }

        }else if(key.equals("Gas")){
            if(data.equals("1")){
                ((ImageView)findViewById(R.id.gasIv)).setImageDrawable(getResources().getDrawable(R.drawable.red));
            }else{
                ((ImageView)findViewById(R.id.gasIv)).setImageDrawable(getResources().getDrawable(R.drawable.blue));
            }

        }else if(key.equals("In")){
            in= Integer.parseInt(snapshot.getValue().toString());

        }else if(key.equals("Out")){
            out= Integer.parseInt(snapshot.getValue().toString());

        }

        marketTv.setText("In: "+in+"\nOut: "+out+"\nStay: "+(in-out));



    }
}