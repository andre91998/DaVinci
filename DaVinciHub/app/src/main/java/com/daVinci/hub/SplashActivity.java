package com.daVinci.hub;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import androidx.appcompat.app.AppCompatActivity;

public class SplashActivity extends AppCompatActivity {

    private static final String TAG = "SplashActivity";
    private static final int SPLASH_DISPLAY_LENGTH = 3000; // Duration for splash screen in milliseconds

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Set the content view for the splash screen
        setContentView(R.layout.activity_splash);

        // Ensure that Firebase is initialized before proceeding
        init();
    }

    private void init() {
        try {
            Thread.sleep(SPLASH_DISPLAY_LENGTH);
            proceedToNextActivity();
        } catch (Exception e) {
            Log.e(TAG, "Firebase initialization failed: " + e.getMessage(), e);
        }
    }

    private void proceedToNextActivity() {
        new Handler().postDelayed(() -> {
            Intent intent = new Intent(SplashActivity.this, MainActivity.class); // User is logged in, go to MainActivity
            startActivity(intent);
            finish();
        }, SPLASH_DISPLAY_LENGTH);
    }
}

