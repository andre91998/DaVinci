package com.daVinci.hub;
import static org.junit.Assert.assertNotNull;

import android.content.Context;

import androidx.test.core.app.ActivityScenario;
import androidx.appcompat.app.AppCompatActivity;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.platform.app.InstrumentationRegistry;

import com.daVinci.hub.SplashActivity;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class) // Use AndroidJUnit4 for instrumented tests
public class SplashActivityTest {

    private ActivityScenario<SplashActivity> scenario;

    @Before
    public void setUp() {
        // Get the instrumentation context (if needed)
        Context context = InstrumentationRegistry.getInstrumentation().getTargetContext();

        // Launch the SplashActivity
        scenario = ActivityScenario.launch(SplashActivity.class);
        assertNotNull("ActivityScenario should not be null", scenario);
    }

    @After
    public void tearDown() {
        // Close the scenario only if it is not null
        if (scenario != null) {
            scenario.close();
        }
    }

    @Test
    public void testSplashActivityLaunch() {
        // Example test to check if SplashActivity launches successfully
        scenario.onActivity(activity -> {
            assertNotNull("SplashActivity should not be null", activity);
        });
    }
}