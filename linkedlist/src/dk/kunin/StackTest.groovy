package dk.kunin

/**
 * Created by 7times6 on 06.10.14.
 */
import org.junit.Test
import static org.junit.Assert.*

class StackTest {

    @Test
    void testStack() {
        Stack s = new Stack();
        10.times {
            s.push(it)
        }

        9.downto(0) {
            assertEquals(it, s.pop().data)
        }

        assertTrue s.isEmpty()
    }

    @Test
    void emptyTest() {
        Stack s = new Stack();
        assertTrue s.isEmpty()
    }

}
