package com.daVinci.hub.util;

import com.github.mikephil.charting.components.AxisBase;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.text.DateFormat;
import java.util.Date;
import java.util.Locale;

@ExtendWith(MockitoExtension.class)
public class LineChartTimeAxisValueFormatterTest {

    private LineChartTimeAxisValueFormatter formatter;

    @BeforeEach
    public void setUp() {
        formatter = new LineChartTimeAxisValueFormatter();
    }

    @Test
    public void testGetFormattedValue() {
        float value = 1617187200f; // Corresponds to 2021-04-01T00:00:00Z
        AxisBase axis = null; // AxisBase is not used in the formatter

        String expectedDate = DateFormat.getDateInstance(DateFormat.MEDIUM, Locale.getDefault()).format(new Date(1617187200L * 1000));
        String actualDate = formatter.getFormattedValue(value, axis);

        assertEquals(expectedDate, actualDate);
    }
}