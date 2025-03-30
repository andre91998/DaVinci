package com.daVinci.hub;

import android.content.Intent;
import androidx.test.core.app.ActivityScenario;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;
import static org.junit.jupiter.api.Assertions.assertNotNull;

@ExtendWith(MockitoExtension.class)
public class ViewDimmerDataActivityTest {

    private ActivityScenario<ViewDimmerDataActivity> scenario;

    @BeforeEach
    public void setUp() {
        scenario = ActivityScenario.launch(ViewDimmerDataActivity.class);
    }

    @AfterEach
    public void tearDown() {
        scenario.close();
    }

    @Test
    public void testActivityLaunch() {
        scenario.onActivity(activity -> {
            assertNotNull(activity);
        });
    }

    @Test
    public void testIntent() {
        Intent intent = new Intent();
        scenario.onActivity(activity -> {
            activity.startActivity(intent);
            assertNotNull(activity.getIntent());
        });
    }
}