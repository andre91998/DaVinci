package com.daVinci.hub;

import static org.junit.Assert.assertNotNull;

import android.content.Intent;

import androidx.test.core.app.ActivityScenario;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class) // Use AndroidJUnit4 for instrumented tests
public class ViewTemperatureDataActivityTest {

    private ActivityScenario<ViewTemperatureDataActivity> scenario;

    @Before
    public void setUp() {
        // Launch the ViewTemperatureDataActivity
        scenario = ActivityScenario.launch(ViewTemperatureDataActivity.class);
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
    public void testActivityLaunch() {
        // Test if the activity launches successfully
        scenario.onActivity(activity -> {
            assertNotNull("ViewTemperatureDataActivity should not be null", activity);
        });
    }
}