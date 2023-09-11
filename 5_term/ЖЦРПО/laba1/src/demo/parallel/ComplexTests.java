package demo.parallel;

import org.junit.Test;
import static org.junit.Assert.*;

public class ComplexTests {
    @Test
    public void minusTest() {
        Complex a = new Complex(6.7, 6.6);
        Complex b = new Complex(-11.4, 4.4);

        Complex result = a.minus(b);

        assertEquals(6.7 - (-11.4), result.getReal(), 0.0001);
        assertEquals(6.6 - 4.4, result.getImaginary(), 0.0001);
    }

    @Test
    public void offsetTest() {
        Complex a = new Complex(5.2, 3.4);
        double offsetNumber = 0.7;

        Complex result = a.offset(offsetNumber);

        assertEquals(5.2 + offsetNumber, result.getReal(), 0.0001);
        assertEquals(3.4 + offsetNumber, result.getImaginary(), 0.0001);
    }
}